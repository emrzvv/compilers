import enum
import abc
from dataclasses import dataclass
from typing import Any, Optional
import edsl.parser_edsl as pe
from exceptions import *
from pprint import pprint


class Type(abc.ABC):
    pass

class PrimitiveType(enum.Enum):
    Integer = 'int'
    Char = 'char'
    Boolean = 'bool'

@dataclass
class ArrayType:
    type: Type


class Statement(abc.ABC):
    @abc.abstractmethod
    def check(self, funcs, ret_type, vars):
        pass

class Expression(abc.ABC):
    @abc.abstractmethod
    def check(self, funcs, ret_type, vars):
        pass

@dataclass
class BinOperatorExpression(Expression):
    @pe.ExAction
    def create(attrs, coords, res_coord):
        left, operator, right = attrs
        return BinOperatorExpression(left, operator, coords[1].start, right, None)

    def check(self, funcs, ret_type, vars):
        self.left.check(funcs, ret_type, vars)
        self.right.check(funcs, ret_type, vars)

        is_int = lambda a: a in (PrimitiveType.Integer, PrimitiveType.Char)
        lt = self.left.type
        rt = self.right.type
        if self.operator in ('<', '<=', '>', '>='):
            if is_int(lt) and is_int(rt):
                self.type = PrimitiveType.Boolean
        elif self.operator == '+' and (is_int(lt) or is_int(rt)):
            if lt == PrimitiveType.Integer and rt == PrimitiveType.Integer:
                self.type = PrimitiveType.Integer
            else:
                self.type = PrimitiveType.Char
        elif self.operator in ('||', '&&', '^^'):
            if lt == PrimitiveType.Boolean and rt == PrimitiveType.Boolean:
                self.type = PrimitiveType.Boolean
        elif self.operator in ('==', '!='):
            if lt != String and rt != String:
                if is_int(lt) and is_int(rt):
                    self.type = PrimitiveType.Boolean
                elif lt == rt:
                    self.type = PrimitiveType.Boolean
                elif (type(lt) == ArrayType or isinstance(self.left, RefConst)) and \
                        (type(rt) == ArrayType or isinstance(self.right, RefConst)):
                    self.type = PrimitiveType.Boolean
        elif self.operator in ('*', '/', '%', '^'):
            if lt == PrimitiveType.Integer and rt == PrimitiveType.Integer:
                self.type = PrimitiveType.Integer
        elif self.operator == '-':
            if is_int(lt) and is_int(rt):
                if lt == PrimitiveType.Char and rt == PrimitiveType.Integer:
                    self.type = PrimitiveType.Char
                else:
                    self.type = PrimitiveType.Integer
        else:
            raise BinaryOperatorTypeMismatch(self.operator_coord, self.left.type, self.operator, self.right.type)


    left: Expression
    operator: str
    operator_coord: pe.Position
    right: Expression
    type: PrimitiveType or Type

@dataclass
class UnaryOperatorExpression(Expression):
    @staticmethod
    def create(operator):
        @pe.ExAction
        def action(attrs, coords, res_coords):
            expression, = attrs
            return UnaryOperatorExpression(operator, expression, coords[0].start, None)
        return action

    def check(self, funcs, ret_type, vars):
        self.expression.check(funcs, ret_type, vars)
        if self.operator == '-':
            if self.expression.type not in (PrimitiveType.Integer, PrimitiveType.Char):
                raise UnexpectedUnaryType(self.operator_coord, self.operator, self.expression.type)
            else:
                self.type = PrimitiveType.Integer
        elif self.operator == '!':
            if self.expression.type not in PrimitiveType.Boolean:
                raise UnexpectedUnaryType(self.operator_coord, self.operator, self.expression.type)
            else:
                self.type = PrimitiveType.Boolean
    operator: str
    expression: Expression
    operator_coord: pe.Position
    type: PrimitiveType or Type

@dataclass
class Var(Expression):
    def check(self, funcs, ret_type, vars):
        if self.name not in vars:
            raise UndefinedVar(self.name_pos, self.name)
        self.type = vars[self.name]

    name: str
    name_pos: pe.Position
    type: PrimitiveType or Type

    @pe.ExAction
    def create(attrs, coords, res_coord):
        return Var(attrs[0], coords[0].start, None)

@dataclass
class ArrayCall(Expression):
    def check(self, funcs, ret_type, vars):
        self.array.check(funcs, ret_type, vars)
        self.ref.check(funcs, ret_type, vars)

        if isinstance(self.array.type, ArrayType):
            self.type = self.array.type.type
        else:
            raise IllegalArrayType(self.array_coord, self.type)

        if self.ref.type not in (PrimitiveType.Integer, PrimitiveType.Char):
            raise IllegalArrayRefType(self.ref_coord, self.type)

        if not isinstance(self.array.type, ArrayType):
            if self.array.name not in vars:
                raise UndefinedVar(self.array_coord, self.array.name)

    @pe.ExAction
    def create(attrs, coords, res_coord):
        array, ref = attrs
        return ArrayCall(array, ref, coords[0].start, coords[2].start, None)

    array: Expression
    ref: Expression
    array_coord: pe.Position
    ref_coord: pe.Position
    type: Type or PrimitiveType

@dataclass
class VarDeclaration:
    name: str
    expression: Optional[Expression]

@dataclass
class DeclarationStatement(Statement):
    def check(self, funcs, return_type, vars):
        for decl in self.var_declarations:
            if decl.name in vars:
                raise AlreadyExists(None, decl.name) # TODO: pos
            vars[decl.name] = self.type
        return vars

    type: Type or PrimitiveType
    var_declarations: list[VarDeclaration]

@dataclass
class AssignmentStatement(Statement):
    def check(self, funcs, return_type, vars):
        print('ASSIGNMENT STATEMENT')
        pprint(self.left)
        pprint(self.right)
        print('---------------')
        if type(self.left) == str and self.left in funcs:
            self.right.check(funcs, return_type, vars)
            if funcs[self.left].return_type != self.right.type:
                raise AssignTypeMismatch(self.assign_coord, funcs[self.left].return_type, self.right.type)
        elif self.left not in funcs:
            raise Exception('Unknown')
        else:
            self.left.check(funcs, return_type, vars)
            self.right.check(funcs, return_type, vars)
            if self.left.type != self.right.type:
                raise AssignTypeMismatch(self.assign_coord, self.left.type, self.right.type)


    @pe.ExAction
    def create(attrs, coords, res_coord):
        left, right = attrs
        return AssignmentStatement(left, right, coords[1])

    left: Var or ArrayCall
    right: Expression
    assign_coord: pe.Position

@dataclass
class FunctionCallStatement(Statement):
    @pe.ExAction
    def create(attrs, coords, res_coord):
        name, args = attrs
        # print(f'function call: {name} ')
        # pprint(coords)
        # print('--------')
        return FunctionCallStatement(name, coords[0].start, args, coords[2].start)

    def check(self, funcs, return_type, vars):
        print(f'checking function call {self.name}')
        if self.name not in funcs:
            raise UndefinedFunction(self.name_coord, self.name)
        if len(self.args) != funcs[self.name].args_len():
            raise ArgumentsLenMismatch(self.args_coord,
                                       self.name,
                                       funcs[self.name].args_len(),
                                       len(self.args))
        # print('PARAMETERS')
        params_map_types = funcs[self.name].params_map_types()
        # pprint(params_map_types)
        # print('ARGUMENTS:')
        for arg in self.args:
            arg.check(funcs, return_type, vars)
        # pprint(self.args)
        for param, arg in zip(params_map_types, self.args):
            if param[1] != arg.type: # TODO: prettify array error output
                raise ArgumentsTypeMismatch(self.args_coord, self.name, param[1].type, arg.type)
            # print(f'parameter: {param}\narg: {arg}\n')

    name: str
    name_coord: pe.Position
    args: list[Expression]
    args_coord: pe.Position


@dataclass
class ElseBlock:
    condition: Optional[Expression] # elseif
    statements: list[Statement]

@dataclass
class IfStatement(Statement):
    def check(self, funcs, return_type, vars):
        print("IF TODO")

    condition: Expression
    statements: list[Statement]
    elseblocks: list[ElseBlock]


@dataclass
class WarningStatement(Statement):
    def check(self, funcs, return_type, vars):
        print("WARNING TODO")

    expr: Expression

@dataclass
class WhileDoStatement(Statement):
    def check(self, funcs, return_type, vars):
        print("WHILE TODO")

    condition: Expression
    statements: list[Statement]


@dataclass
class ForDoVarDeclaration:
    name: Any
    value: Any
    type: Optional[Type]

@dataclass
class ForCycleHead:
    var_declaration: ForDoVarDeclaration
    to: Any
    step: Optional[Any]

@dataclass
class ForDoStatement(Statement):
    def check(self, funcs, return_type, vars):
        print("FOR DO TODO")

    head: ForCycleHead
    statements: list[Statement]

@dataclass
class RepeatUntilStatement(Statement):
    def check(self, funcs, return_type, vars):
        print("REPEAT UNTIL TODO")

    statements: list[Statement]
    condition: Expression

@dataclass
class ArrayAllocation:
    type: Type
    size: Any

@dataclass
class String(Type):
    value: str
    type: Type

    def check(self):
        pass

@dataclass
class RefConst(Type):
    value: str
    type: Type

    def check(self):
        pass

@dataclass
class Const(Expression):
    value: Any
    type: PrimitiveType or Type

    def check(self, funcs, ret_type, vars):
        pass

@dataclass
class Section:
    type: Type or PrimitiveType
    parameters: list[Var]

@dataclass
class FunctionHeader:
    name: str
    sections: list[Section]
    return_type: Type or PrimitiveType
    name_pos: pe.Position

    @pe.ExAction
    def create(attrs, coords, res_coord):
        name, sections, return_type = attrs
        return FunctionHeader(name, sections, return_type, coords[2].start)

    def args_len(self):
        n = 0
        for section in self.sections:
            n += len(section.parameters)
        return n

    def params_map_types(self):
        ps = []
        for section in self.sections:
            ps += ((p, section.type) for p in section.parameters)
        return ps

@dataclass
class ProcedureHeader:
    name: str
    sections: list[Section]
    name_pos: pe.Position

    @pe.ExAction
    def create(attrs, coords, res_coord):
        name, sections = attrs
        return ProcedureHeader(name, sections, coords[1].start)


@dataclass
class Body(abc.ABC):
    statements: list[Statement]

    def check(self, funcs, return_type, vars):
        # last statement - assign statement funcname = expression
        if return_type != "void":
            if not isinstance(self.statements[-1], AssignmentStatement):
                raise MissingReturnStatement(None)
        for stmt in self.statements:
            print(type(stmt))
            if isinstance(stmt, VarDeclaration):
                vars = stmt.check(funcs, return_type, vars)
            else:
                stmt.check(funcs, return_type, vars)
            pprint(vars)

@dataclass
class Function:
    header: FunctionHeader
    body: Body

    def check(self, funcs):
        vars = {}
        sections = self.header.sections
        for section in sections:
            for param in section.parameters:
                if param.name in vars and section.type == vars[param.name]:
                    raise AlreadyExists(param.name_pos, param.name)
                vars[param.name] = section.type
        vars[self.header.name] = self.header.return_type
        print(f'\nchecking function {self.header.name}')
        pprint(vars)
        self.body.check(funcs, self.header.return_type, vars)

@dataclass
class Procedure:
    header: ProcedureHeader
    body: Body

    def check(self, funcs):
        vars = {}
        sections = self.header.sections
        for section in sections:
            for param in section.parameters:
                if param.name in vars and section.type == vars[param.name]:
                    raise AlreadyExists(param.name_pos, param.name)
                vars[param.name] = section.type
        # print("checking")
        # pprint(self.header.name)
        # pprint(vars)
        self.body.check(funcs, "void", vars)

@dataclass
class Program:
    entities: list[Function or Procedure]

    def check(self):
        funcs = {}
        for func in self.entities:
            if func.header.name in funcs:
                raise AlreadyExists(func.header.name_pos, func.header.name)
            funcs[func.header.name] = func.header

        pprint(funcs)
        for func in self.entities:
            vars = {}
            func.check(funcs)
