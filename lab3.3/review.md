% Лабораторная работа № 3.3 «Семантический анализ»
% 29 мая 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является получение навыков выполнения семантического анализа.

# Индивидуальный вариант
Язык L3
*Семантический анализ*:
- Вызываемые функции должны быть определены в программе.
- Переменные в выражениях должны быть определены ранее.
- Область видимости переменной начинается с оператора-объявления и заканчивается вместе с последовательностью операторов, где она определена.
- Операции применяются к операндам допустимых типов (таблица 3).
Операнды оператора присваивания должны быть совместимых типов.
Типы формальных параметров должны совпадать с типами фактических параметров.
# Реализация
Грамматика
```
Program -> Program Function | Program Procedure | Function | Procedure

Function -> FunctionHeader Statements endfunc
Procedure -> ProcedureHeader Statements endproc
FunctionHeader -> func VARNAME (Sections) -> Type
ProcedureHeader -> proc VARNAME (Sections)

Sections -> Sections; Section | Section
Section -> Parameters, VARNAME -> Type | VARNAME -> Type
Parameters -> Parameters, VARNAME | VARNAME

Type -> PrimitiveType | [Type]
PrimitiveType -> int | char | bool

Statements -> Statements; Statement | Statement
Statement -> 
	DeclarationStatement |
	AssignmentStatement |
	ArrayAssignmentStatement |
	FunctionCallStatement |
	IfStatement | 
	LoopWithPreconditionStatements | 
	LoopWithPostconditionStatement |
	check Expression
	
DeclarationStatement -> VarDeclarations, VarDeclaration -> Type | VarDeclaration -> Type
VarDeclarations ->  VarDeclarations, VarDeclaration | VarDeclaration
VarDeclaration -> VARNAME | AssignmentStatement

AssignmentStatement -> ExtendedVar = Expression
ArrayAssignmentStatement -> ArrayCall = Expression
FunctionCallStatement -> VARNAME(Args)
Args -> Args, Expression | Expression

ExtendedVar -> VARNAME 
ArrayCall -> Spec[Expression]
Spec -> FunctionCallStatement | [Type VARNAME] | [Type INT_CONST] | ExtendedVar | ArrayCall | Const


Const -> INT_CONST | CHAR_CONST | STRING_CONST | REF_CONST | TRUE | FALSE

Expression -> 
	LogicalExpression |
	Expression || LogicalExpression |
	Expression ^^ LogicalExpression
	
LogicalExpression -> LogicalExpression && CompareExpression | CompareExpression
CompareExpression -> ArithmeticExpression CompareOperator ArithmeticExpression | ArithmeticExpression
CompareOperator -> == | != | < | > | <= | >=
ArithmeticExpression -> PowExpression | ArithmeticExpression AdditiveOperator PowExpression
AdditiveOperator -> + | -
PowExpression -> Term | Term ^ PowExpression
Term -> Factor | Term MultiplicativeOperator Factor
MultiplicativeOperator -> * | / | %
Factor -> !Spec | -Spec | Spec


IfStatement -> if Expression then Statements ElseBlock endif
ElseBlock -> else Statements | elseif Expression then Statements ElseBlock

LoopWithPreconditionStatements -> 
	while Expression do Statements endwhile |
	ForCycleHead step INT_CONST do Statements endfor |
	ForCycleHead do Statements endfor
ForCycleHead -> for ForCycleVarDeclaration to ForCycleTo


ForCycleVarDeclaration -> VARNAME = Expression | VARNAME = INT_CONST -> INTEGER | VARNAME = CHAR_CONST -> CHAR
ForCycleTo = Expression

LoopWithPostconditionStatement -> repeat Statements until Expression
```
Лексическая структура
```
VARNAME = [a-zA-Z\_\?\$\@\.\#\~][a-zA-Z0-9\_\?\$\@\.\#\~]*
REF_CONST = nil
INT_CONST = (0x([0-9a-fA-F]{1,8}))|\d+
CHAR_CONST = \'.?\'
STRING_CONST = \"\.*\"
```
exceptions.py
```python
import edsl.parser_edsl as pe

class SemanticError(pe.Error):
    def __init__(self, pos, message):
        self.pos = pos
        self.__message = message

    @property
    def message(self):
        return self.__message

class AlreadyExists(SemanticError):
    def __init__(self, pos, name):
        self.pos = pos
        self.name = name

    @property
    def message(self):
        return f'Повторное объявление: {self.name}'

class MissingReturnStatement(SemanticError):
    def __init__(self, pos):
        self.pos = pos

    @property
    def message(self): # TODO: pos
        return 'Функция должна возвращать значение'

class UndefinedFunction(SemanticError):
    def __init__(self, pos, name):
        self.pos = pos
        self.name = name

    @property
    def message(self):
        return f'Функция {self.name} не была определена'

class ArgumentsLenMismatch(SemanticError):
    def __init__(self, args_pos, name, expected_len, found_len):
        self.pos = args_pos
        self.name = name
        self.expected_len = expected_len
        self.found_len = found_len

    @property
    def message(self):
        return f'В функции {self.name} ожидалось {self.expected_len} аргументов, получено {self.found_len}'

class ArgumentsTypeMismatch(SemanticError):
    def __init__(self, arg_pos, name, expected, found):
        self.pos = arg_pos
        self.name = name
        self.expected = expected
        self.found = found

    @property
    def message(self):
        return (f'Несоответствие типа аргумента в вызове функции {self.name}: '
                f'ожидалось {self.expected}, получено {self.found}')

class UndefinedVar(SemanticError):
    def __init__(self, pos, name):
        self.pos = pos
        self.name = name

    @property
    def message(self):
        return f'Переменная {self.name} не была определена'

class UnexpectedUnaryType(SemanticError):
    def __init__(self, pos, operator, type):
        self.pos = pos
        self.operator = operator
        self.type = type

    @property
    def message(self):
        return f'Несовместимый тип {self.type} для {self.operator}'

class IllegalArrayType(SemanticError):
    def __init__(self, pos, type):
        self.pos = pos
        self.type = type
    @property
    def message(self):
        return f'Ожидался тип массива, получено {type}'

class IllegalArrayRefType(SemanticError):
    def __init__(self, pos, type):
        self.pos = pos
        self.type = type

    @property
    def message(self):
        return f'Ожидался int или char, получено {type}'

class AssignTypeMismatch(SemanticError):
    def __init__(self, pos, left, right):
        self.pos = pos
        self.left = left
        self.right = right

    @property
    def message(self):
        return f'Неправильное присваивание: ожидалось {self.left}, получено {self.right}'

class BinaryOperatorTypeMismatch(SemanticError):
    def __init__(self, pos, left, operator, right):
        self.pos = pos
        self.left = left
        self.right = right
        self.operator = operator

    @property
    def message(self):
        return f'Неправильный тип бинарной операции {self.operator}: ожидалось {self.left}, получено {self.right}'


class TypeMismatch(SemanticError):
    def __init__(self, pos, left, right):
        self.pos = pos
        self.left = left
        self.right = right

    @property
    def message(self):
        return f'Неверный тип: ожидалось {self.left}, получено {self.right}'
```
main.py
```python
import sys
from pprint import pprint

import edsl.parser_edsl as pe
from model import *

# lexical structure
VARNAME = pe.Terminal('VARNAME', '[a-zA-Z_\\?\\$\\@\\.\\#\\~][a-zA-Z0-9_\\?\\$\\@\\.\\#\\~]*', str)
REF_CONST = pe.Terminal('REF_CONST', 'nil', str)
INT_CONST = pe.Terminal('INT_CONST', '(0x([0-9a-fA-F]{1,8}))|(\d+)', str, priority=7)
CHAR_CONST = pe.Terminal('CHAR_CONST', '(\'.?\')|(\\$.+\\$)', str)
STRING_CONST = pe.Terminal('STRING_CONST', '\".*\"', str)


def make_keyword(image):
    return pe.Terminal(image, image, lambda name: None, priority=10)


KW_INT, KW_CHAR, KW_BOOL = \
    map(make_keyword, 'int char bool'.split())
KW_XOR, KW_OR, KW_MOD, KW_AND, KW_NOT, KW_TRUE, KW_FALSE = \
    map(make_keyword, '^^ || % && ! tt ff'.split())

NProgram, NEntities, NFunction, NProcedure, NFunctionHeader, NProcedureHeader = \
    map(pe.NonTerminal, 'Program Entities Func Procedure FunctionHeader ProcedureHeader'.split())

NSections, NSection, NParameters, NType, NPrimitiveType, NBody = \
    map(pe.NonTerminal, 'Sections Section Parameters Type PrimitiveType FunctionBody'.split())

NStatements, NStatement, NDeclarationStatement, NAssignmentStatement, NArrayAssignmentStatement, NArrayCall, NFunctionCallStatement = \
    map(pe.NonTerminal, 'Statements Statement DeclarationStatement AssignmentStatement NArrayAssignmentStatement NArrayCall FunctionCallStatement'.split())

NIfStatement, NElseBlock, NLoopWithPreconditionStatements, NLoopWithPostconditionStatement = \
    map(pe.NonTerminal, 'IfStatement ElseBlock LoopWithPreconditionStatements LoopWithPostconditionStatement'.split())

NVarDeclarations, NVarDeclaration, NExpression, NLogicalExpression = \
    map(pe.NonTerminal, 'VarDeclarations VarDeclaration Expression LogicalExpression'.split())

NCompareExpression, NCompareOperator, NArithmeticExpression, NPowExpression, NAdditiveOperator, NMultiplicativeOperator = \
    map(pe.NonTerminal, 'CompareExpression NCompareOperator ArithmeticExpression PowExpression AdditiveOperator MultiplicativeOperator'.split())

NTerm, NFactor, NSpec, NArgs, NVar, NConst = \
    map(pe.NonTerminal, 'Term Factor Spec Args Var Const'.split())

NForCycleVarDeclaration, NForCycleTo, NForCycleHead, NMultiplicativeExpression = \
    map(pe.NonTerminal, 'ForCycleVarDeclaration ForCycleTo ForCycleHead MultiplicativeExpression'.split())

# grammar
NProgram |= NEntities, Program

NEntities |= NFunction, lambda fn: [fn]
NEntities |= NProcedure, lambda pr: [pr]
NEntities |= NEntities, NFunction, lambda entities, fn: entities + [fn]
NEntities |= NEntities, NProcedure, lambda entities, pr: entities + [pr]

NFunction |= NFunctionHeader, NBody, 'endfunc', Function
NProcedure |= NProcedureHeader, NBody, 'endproc', Procedure
NBody |= NStatements, Body
NFunctionHeader |= 'func', VARNAME, '(', NSections, ')', '->', NType, FunctionHeader.create
NProcedureHeader |= 'proc', VARNAME, '(', NSections, ')', ProcedureHeader.create

NType |= NPrimitiveType
NType |= '[', NType, ']', ArrayType
NPrimitiveType |= KW_INT, lambda: PrimitiveType.Integer
NPrimitiveType |= KW_CHAR, lambda: PrimitiveType.Char
NPrimitiveType |= KW_BOOL, lambda: PrimitiveType.Boolean

NSections |= NSection, lambda sec: [sec]
NSections |= NSections, ';', NSection, lambda secs, sec: secs + [sec]
NSection |= NVar, '->', NType, lambda p, t: Section(t, [p])
NSection |= NParameters, ',', NVar, '->', NType, lambda ps, p, t: Section(t, ps + [p])
NParameters |= NVar, lambda p: [p]
NParameters |= NParameters, ',', NVar, lambda ps, p: ps + [p]

# statements
NStatements |= NStatement, lambda st: [st]
NStatements |= NStatements, ';', NStatement, lambda stmts, st: stmts + [st]
NStatement |= NDeclarationStatement
NStatement |= NAssignmentStatement
NStatement |= NArrayAssignmentStatement
NStatement |= NFunctionCallStatement
NStatement |= NIfStatement
NStatement |= NLoopWithPreconditionStatements
NStatement |= NLoopWithPostconditionStatement
NStatement |= 'check', NExpression, WarningStatement
# end statements

NDeclarationStatement |= NVarDeclaration, '->', NType, lambda dec, t: DeclarationStatement(t, [dec])
NDeclarationStatement |= NVarDeclarations, ',', NVarDeclaration, '->', NType, lambda decls, dec, t: DeclarationStatement(t, decls + [dec])
NVarDeclarations |= NVarDeclaration, lambda dec: [dec]
NVarDeclarations |= NVarDeclarations, ',', NVarDeclaration, lambda decls, dec: decls + [dec]
NVarDeclaration |= VARNAME, lambda name: VarDeclaration(name, None)
NVarDeclaration |= VARNAME, '=', NExpression, lambda name, expr: VarDeclaration(name, expr)
#NVarDeclaration |= NAssignmentStatement # VARNAME, '=', NExpression, lambda name, expr: VarDeclaration(name, expr)

NAssignmentStatement |= VARNAME, '=', NExpression, AssignmentStatement.create  # <-
NArrayAssignmentStatement |= NArrayCall, '=', NExpression, AssignmentStatement.create
NFunctionCallStatement |= VARNAME, '(', NArgs, ')', FunctionCallStatement.create
NArgs |= NExpression, lambda arg: [arg]
NArgs |= NArgs, ',', NExpression, lambda args, arg: args + [arg]

NVar |= VARNAME, Var.create
NArrayCall |= NSpec, '[', NExpression, ']', ArrayCall.create

NSpec |= NFunctionCallStatement
NSpec |= '[', NType, VARNAME, ']', ArrayAllocation # todo: allocate by expression?
NSpec |= '[', NType, INT_CONST, ']', ArrayAllocation
NSpec |= NVar
NSpec |= NArrayCall
NSpec |= NConst

NConst |= INT_CONST, lambda v: Const(v, PrimitiveType.Integer)
NConst |= CHAR_CONST, lambda v: Const(v, PrimitiveType.Char)
NConst |= STRING_CONST, lambda s: String(s, String)
NConst |= REF_CONST, lambda r: RefConst(r, RefConst)
NConst |= KW_TRUE, lambda b: Const(True, PrimitiveType.Boolean)
NConst |= KW_FALSE, lambda f: Const(False, PrimitiveType.Boolean)

NExpression |= NLogicalExpression
NExpression |= NExpression, KW_OR, NLogicalExpression, BinOperatorExpression.create
NExpression |= NExpression, KW_XOR, NLogicalExpression, BinOperatorExpression.create

NLogicalExpression |= NCompareExpression
NLogicalExpression |= NLogicalExpression, KW_AND, NCompareExpression, BinOperatorExpression.create

def make_op_lambda(op):
    return lambda: op


for op in ('==', '!=', '<', '>', '<=', '>='):
    NCompareOperator |= op, make_op_lambda(op)

NCompareExpression |= NArithmeticExpression
NCompareExpression |= NCompareExpression, NCompareOperator, NArithmeticExpression, BinOperatorExpression.create

NAdditiveOperator |= '+', lambda: '+'
NAdditiveOperator |= '-', lambda: '-'

NArithmeticExpression |= NMultiplicativeExpression
NArithmeticExpression |= NMultiplicativeExpression, NAdditiveOperator, NMultiplicativeExpression, BinOperatorExpression.create
# NArithmeticExpression |= NPowExpression
# NArithmeticExpression |= NPowExpression, NAdditiveOperator, NPowExpression, BinOperatorExpression

NMultiplicativeExpression |= NTerm
NMultiplicativeExpression |= NMultiplicativeExpression, NMultiplicativeOperator, NTerm, BinOperatorExpression.create
# NPowExpression |= NTerm
# NPowExpression |= NTerm, '^', NPowExpression, lambda l, r: BinOperatorExpression(l, '^', r)

NMultiplicativeOperator |= '*', lambda: '*'
NMultiplicativeOperator |= '/', lambda: '/'
NMultiplicativeOperator |= '%', lambda: '%'

NTerm |= NFactor
NTerm |= NFactor, '^', NTerm, lambda l, r: BinOperatorExpression.create

# NFactor |= KW_NOT, NSpec, lambda expr: UnaryOperatorExpression('!', expr)
NFactor |= KW_NOT, NSpec, UnaryOperatorExpression.create('!')
# NFactor |= '-', NSpec, lambda expr: UnaryOperatorExpression('-', expr)
NFactor |= '-', NSpec, UnaryOperatorExpression.create('-')
NFactor |= NSpec

NIfStatement |= 'if', NExpression, 'then', NBody, 'endif', lambda expr, stmts: IfStatement(condition=expr, statements=stmts, elseblocks=list())
NIfStatement |= 'if', NExpression, 'then', NBody, NElseBlock, 'endif', IfStatement
NElseBlock |= 'else', NBody, lambda stmts: [ElseBlock(condition=None, statements=stmts)]
NElseBlock |= 'elseif', NExpression, 'then', NBody, NElseBlock, lambda expr, stmts, block: [ElseBlock(condition=expr, statements=stmts)] + block

NLoopWithPreconditionStatements |= 'while', NExpression, 'do', NBody, 'endwhile', WhileDoStatement

NLoopWithPreconditionStatements |= NForCycleHead, 'do', NBody, 'endfor', ForDoStatement

NForCycleHead |= 'for', NForCycleVarDeclaration, 'to', NForCycleTo, lambda decl, to: ForCycleHead(decl, to, step=None)
NForCycleHead |= 'for', NForCycleVarDeclaration, 'to', NForCycleTo, 'step', INT_CONST, lambda decl, to, step: ForCycleHead(decl, to, step=step)

NForCycleVarDeclaration |= VARNAME, '=', INT_CONST, '->', KW_INT, lambda name, expr: ForDoVarDeclaration(name=name, value=Const(expr, type=PrimitiveType.Integer), type=PrimitiveType.Integer)
NForCycleVarDeclaration |= VARNAME, '=', CHAR_CONST, '->', KW_CHAR, lambda name, expr: ForDoVarDeclaration(name=name, value=Const(expr, type=PrimitiveType.Char), type=PrimitiveType.Char)
NForCycleVarDeclaration |= VARNAME, '=', NExpression, lambda name, expr: ForDoVarDeclaration(name=name, value=expr, type=None)


NForCycleTo |= NExpression
# NForCycleTo |= INT_CONST, lambda i: i
# NForCycleTo |= CHAR_CONST, lambda c: c

NLoopWithPostconditionStatement |= 'repeat', NBody, 'until', NExpression, RepeatUntilStatement

parser = pe.Parser(NProgram)
# parser.print_table()
parser.add_skipped_domain('\s')
parser.add_skipped_domain('\\(\\*.*\\*\\)')
assert parser.is_lalr_one()

for filename in sys.argv[1:]:
    try:
        with open(filename) as f:
            tree = parser.parse(f.read())
            # pprint(tree)
            tree.check()
            print('Семантических ошибок не найдено')
    except pe.Error as e:
        print(f'Ошибка {e.pos}: {e.message}')
    except Exception as e:
        print(e)
```
model.py
```python
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

```
# Тестирование

## Входные данные

```
func SumVectors(A, B -> [int]; E, F -> bool) -> [int]
	size = length(A) -> int;
	check size == length(B);
	C = [int size] -> [int];
	for i = 0 -> int to size - 1 do
		C[i] = A[i] + B[i]
	endfor;
    a = 0 -> int;
	while a < 10 do
	    test -> char;
	    a = a + 1
    endwhile;

	(*e = 'A' -> char;C[0] = e;*)
	SumVectors = C
endfunc

func length(v -> [int]) -> int
    length = 10
endfunc

func main(a, b -> [int]) -> int
    F -> [[char]];
    (*SumVectors(a, b, c, d);*)
    c, d -> bool;
    SumVectors(a, b, c, d);
    main = 0
endfunc
```

## Вывод на `stdout`

```
Семантических ошибок не найдено
```

# Вывод
В ходе выполнения данной лабораторной работы был получен навык частичной реализации самого сложного этапа работы frontend'а компилятора, а именно - реализация семантического анализа (некоторых условий в соответствии с индивидуальным вариантом).
Поскольку индивидуальный вариант представляет собой почти целостный язык программирования с основными управляющими коснтрукциями (в некоторых моментах усложнёнными), реализация таких пунктов как контроль области видимости переменных, контроль за использованием объявленных переменных, контроль за использованием соответствующих типов оказалось трудоёмкой задачей (т.к. грамматика имеет много AST-сущностей, для каждой из которых надо прописывать проверки), но довольно поучительной в силу того, что в ранее выполненной лабораторной работе 2.2 не совсем объемлюще были описаны AST-dataclass'ы, которые пришлось перепроектировать, а также изменять грамматику в некоторых местах. 