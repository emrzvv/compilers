import copy
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
    def check(self, funcs, vars):
        pass

class Expression(abc.ABC):
    @abc.abstractmethod
    def check(self, funcs, vars):
        pass

@dataclass
class BinOperatorExpression(Expression):
    @pe.ExAction
    def create(attrs, coords, res_coord):
        left, operator, right = attrs
        return BinOperatorExpression(left, operator, coords[1].start, right, None)

    def check(self, funcs, vars):
        self.left.check(funcs, vars)
        self.right.check(funcs, vars)

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

    def check(self, funcs, vars):
        self.expression.check(funcs, vars)
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
    def check(self, funcs, vars):
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
    def check(self, funcs, vars):
        print('CHECKING ARRAY CALL')
        self.array.check(funcs, vars)
        self.ref.check(funcs, vars)

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
    def check(self, funcs, vars):
        for decl in self.var_declarations:
            if decl.name in vars:
                raise AlreadyExists(None, decl.name) # TODO: pos
            vars[decl.name] = self.type
        return vars

    type: Type or PrimitiveType
    var_declarations: list[VarDeclaration]

@dataclass
class AssignmentStatement(Statement):
    def check(self, funcs, vars):
        print('ASSIGNMENT STATEMENT')
        pprint(self.left)
        pprint(self.right)
        print('---------------')
        if type(self.left) == str and self.left in funcs:
            # print(f'{self.left} in funcs')
            # print("left == str and left in funcs")
            self.right.check(funcs, vars)
            if funcs[self.left].return_type != self.right.type:
                raise AssignTypeMismatch(self.assign_coord, funcs[self.left].return_type, self.right.type)
        elif type(self.left) == str and self.left in vars:
            self.left = Var(self.left, self.assign_coord, vars[self.left])
        elif type(self.left) == ArrayCall:
            self.left.check(funcs, vars)
            self.right.check(funcs, vars)
            if self.left.type != self.right.type:
                raise AssignTypeMismatch(self.assign_coord, self.left.type, self.right.type)
        elif self.left not in funcs and self.left not in vars:
            raise Exception('Unknown reference')
        else:
            # print('CHECKED LEFT AND RIGHT')
            self.left.check(funcs, vars)
            self.right.check(funcs, vars)
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
        return FunctionCallStatement(name, coords[0].start, args, coords[2].start, None)

    def check(self, funcs, vars):
        print(f'checking function call {self.name}')
        if self.name not in funcs:
            raise UndefinedFunction(self.name_coord, self.name)
        if len(self.args) != funcs[self.name].args_len():
            raise ArgumentsLenMismatch(self.args_coord,
                                       self.name,
                                       funcs[self.name].args_len(),
                                       len(self.args))
        self.type = funcs[self.name].return_type
        # print('PARAMETERS')
        params_map_types = funcs[self.name].params_map_types()
        # pprint(params_map_types)
        # print('ARGUMENTS:')
        for arg in self.args:
            arg.check(funcs, vars)
        # pprint(self.args)
        for param, arg in zip(params_map_types, self.args):
            if param[1] != arg.type: # TODO: prettify array error output
                raise ArgumentsTypeMismatch(self.args_coord, self.name, param[1].type, arg.type)
            # print(f'parameter: {param}\narg: {arg}\n')

    name: str
    name_coord: pe.Position
    args: list[Expression]
    args_coord: pe.Position
    type: Type or PrimitiveType


@dataclass
class WarningStatement(Statement):
    def check(self, funcs, vars):
        self.expr.check(funcs, vars)

    expr: Expression

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

    def check(self, funcs, vars):
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
        inner_vars = copy.deepcopy(vars)
        if return_type != "void":
            if not isinstance(self.statements[-1], AssignmentStatement):
                raise MissingReturnStatement(None)
        for stmt in self.statements:
            print(type(stmt))
            if isinstance(stmt, VarDeclaration):
                inner_vars = stmt.check(funcs, inner_vars)
            else:
                stmt.check(funcs, inner_vars)
            pprint(inner_vars)

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
class ElseBlock:
    condition: Optional[Expression] # elseif
    statements: Body

    def check(self, funcs, vars):
        if self.condition is not None:
            self.condition.check(funcs, vars)
        inner_vars = copy.deepcopy(vars)
        self.statements.check(funcs, inner_vars)

@dataclass
class IfStatement(Statement):
    def check(self, funcs, vars):
        self.condition.check(funcs, vars)
        inner_vars = copy.deepcopy(vars)
        self.statements.check(funcs, "void", inner_vars)
        inner_vars_else = copy.deepcopy(vars)
        self.elseblocks.check(funcs, inner_vars_else)

    condition: Expression
    statements: Body
    elseblocks: list[ElseBlock]

@dataclass
class WhileDoStatement(Statement):
    def check(self, funcs, vars):
        self.condition.check(funcs, vars)
        self.statements.check(funcs, "void", vars)

    condition: Expression
    statements: Body


@dataclass
class ForDoVarDeclaration:
    name: str
    value: Expression
    type: Type or PrimitiveType

    def check(self, funcs, vars):
        if self.name in vars:
            raise AlreadyExists(None, self.name)
        self.value.check(funcs, vars)
        if self.type is None:
            self.type = self.value.type
        vars[self.name] = self.type


@dataclass
class ForCycleHead:
    var_declaration: ForDoVarDeclaration
    to: Expression
    step: Optional[Const]

    def check(self, funcs, vars):
        # pprint(vars)
        self.var_declaration.check(funcs, vars)
        self.to.check(funcs, vars)
        if self.var_declaration.type != self.to.type:
            raise TypeMismatch(None, self.var_declaration.type, self.to.type)
        if self.step is not None and self.step.type != PrimitiveType.Integer:
            raise TypeMismatch(None, PrimitiveType.Integer, self.step)
        # pprint(vars)



@dataclass
class ForDoStatement(Statement):
    def check(self, funcs, vars):
        inner_vars = copy.deepcopy(vars)
        self.head.check(funcs, inner_vars)
        self.statements.check(funcs, "void", inner_vars)

    head: ForCycleHead
    statements: Body

@dataclass
class RepeatUntilStatement(Statement):
    def check(self, funcs, vars):
        self.condition.check(funcs, vars)
        self.statements.check(funcs, "void", vars)

    statements: Body
    condition: Expression

@dataclass
class Program:
    entities: list[Function | Procedure]

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
