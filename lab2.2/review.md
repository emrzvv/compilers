% Лабораторная работа № 2.2 «Абстрактные синтаксические деревья»
% 15 мая 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является получение навыков составления грамматик и проектирования синтаксических деревьев.

# Индивидуальный вариант
Язык L3.

# Реализация

## Абстрактный синтаксис
Программа - последовательность функций и процедур:
```
Program -> (Functions|Procedure)*
```
Функция и процедура состоит из заголовка, тела и ключевого слово endfunc/endproc, 
завершающего тело функции. Тело функции - последовательность операторов:
```
Function -> FunctionHeader Statements endfunc
Procedure -> ProcedureHeader Statements endproc
```
Заголовки функции/процедуры содержат списки секций параметров и тип возвращаемого значения (только функция):
```
FunctionHeader -> func VARNAME (Sections) -> Type
ProcedureHeader -> proc VARNAME (Sections)
```
Тип может быть примитивным (int, char, bool) или массивом:
```
Type -> PrimitiveType | [Type]
PrimitiveType -> int | char | bool
```
Секция параметров представляет из себя список параметров одного типа, разделённых `,`. В заголовке может быть несколько секций, разделённых `;`.
```
Sections -> Section (; Section)*
Section -> VARNAME (, VARNAME)* -> Type 
```
Последовательность операторов разделена `;`:
```
Statements -> Statement*
```
Оператор - это:
1. Оъявление переменной
2. Присваивание значения переменной
3. Присваивание значения ячейке массива
4. Вызов функции
5. Условный оператор
6. Цикл с предусловием (while, for)
7. Цикл с постусловием
8. Оператор-предупреждение
```
Statement -> 
	DeclarationStatement |
	AssignmentStatement |
	ArrayAssignmentStatement |
	FunctionCallStatement |
	IfStatement | 
	LoopWithPreconditionStatements | 
	LoopWithPostconditionStatement |
	check Expression
```
Выражение Expression - это переменная (в т.ч. получение ячейки n-мерного массива)/вызов функции/константа/унарная и бинарная операции.
```
Expression -> Spec | Expression Binary Expression | Unary Expression

Spec -> FunctionCallStatement | ArrayCall | ArrayAllocation | VARNAME | Const
FunctionCallStatement -> VARNAME((Expression,)*Expression)
ArrayCall -> Spec[Expression]
ArrayAllocation -> [Type VARNAME] | [Type INT_CONST] | [Type Expression]
Const -> INT_CONST | CHAR_CONST | STRING_CONST | REF_CONST | TRUE | FALSE
Binary -> + | - | * | % | / | ^ | && | || | ^^ | == | != | < | > | <= | >=
Unary -> - | !
```

Условный оператор имеет возможность линейно записывать альтернативные условия:
```
IfStatement -> if Expression then Statements ElseBlock endif
ElseBlock -> else Statements | elseif Expression then Statements ElseBlock
```

Цикл с предусловием может быть двух видов, while и for:
```
LoopWithPreconditionStatements -> 
	while Expression do Statements endwhile |
	ForCycleHead step INT_CONST do Statements endfor |
	ForCycleHead do Statements endfor
```

Объявление цикла может содержать объявление переменной с указанием типа.
```
ForCycleVarDeclaration -> VARNAME = Expression | VARNAME = INT_CONST -> INTEGER | VARNAME = CHAR_CONST -> CHAR
```

Цикл с постусловием:
```
LoopWithPostconditionStatement -> repeat Statements until Expression
```
## Лексическая структура и конкретный синтаксис
Лексическая структура:
```
VARNAME = [a-zA-Z\_\?\$\@\.\#\~][a-zA-Z0-9\_\?\$\@\.\#\~]*
REF_CONST = nil
INT_CONST = (0x([0-9a-fA-F]{1,8}))|\d+
CHAR_CONST = \'.?\'
STRING_CONST = \"\.*\"
TRUE = tt
FALSE = ff
```
Перейдём к конкретной грамматике:
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

## Программная реализация

Описание датаклассов:
```python
import enum
import abc
from dataclasses import dataclass
from typing import Any, Optional

class Type(abc.ABC):
    pass

class PrimitiveType(enum.Enum):
    Integer = 'int'
    Char = 'char'
    Boolean = 'bool'

@dataclass
class ArrayType:
    type: Type

class FunctionHeader(abc.ABC):
    pass

class ProcedureHeader(abc.ABC):
    pass

class Body(abc.ABC):
    pass

class Statement(abc.ABC):
    pass

class Expression(abc.ABC):
    pass

@dataclass
class IntExpression(Expression):
    value: Any

@dataclass
class BinOperatorExpression(Expression):
    left: Expression
    operator: str
    right: Expression

@dataclass
class UnaryOperatorExpression(Expression):
    operator: str
    expression: Expression

@dataclass
class VarDeclaration:
    name: Any
    expression: Optional[Expression]

@dataclass
class DeclarationStatement(Statement):
    type: Type or PrimitiveType
    var_declarations: list[VarDeclaration]

@dataclass
class AssignmentStatement(Statement):
    left: Any
    right: Any

@dataclass
class FunctionCallStatement(Statement):
    name: Any
    args: list[Expression]

@dataclass
class ElseBlock:
    condition: Optional[Expression] # elseif
    statements: list[Statement]

@dataclass
class IfStatement(Statement):
    condition: Expression
    statements: list[Statement]
    elseblocks: list[ElseBlock]


@dataclass
class WarningStatement(Statement):
    expr: Expression

@dataclass
class WhileDoStatement(Statement):
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
    head: ForCycleHead
    statements: list[Statement]

@dataclass
class RepeatUntilStatement(Statement):
    statements: list[Statement]
    condition: Expression

@dataclass
class ExtendedVar:
    value: Any

@dataclass
class ArrayCall:
    array: Any
    ref: Any

@dataclass
class ArrayAllocation:
    type: Type
    size: Any

@dataclass
class Const:
    value: Any

@dataclass
class Section:
    type: Type or PrimitiveType
    parameters: list[Any]

@dataclass
class Function:
    header: FunctionHeader
    body: Body

@dataclass
class Procedure:
    header: ProcedureHeader
    body: Body

@dataclass
class FunctionHeaderFull:
    name: Any
    sections: list[Section]
    return_type: Type or PrimitiveType

@dataclass
class ProcedureHeaderFull(ProcedureHeader):
    name: Any
    sections: list[Section]

```

Парсер:
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

NProgram, NFunction, NProcedure, NFunctionHeader, NProcedureHeader = \
    map(pe.NonTerminal, 'Program Func Procedure FunctionHeader ProcedureHeader'.split())

NSections, NSection, NParameters, NType, NPrimitiveType = \
    map(pe.NonTerminal, 'Sections Section Parameters Type PrimitiveType'.split())

NStatements, NStatement, NDeclarationStatement, NAssignmentStatement, NArrayAssignmentStatement, NArrayCall, NFunctionCallStatement = \
    map(pe.NonTerminal, 'Statements Statement DeclarationStatement AssignmentStatement NArrayAssignmentStatement NArrayCall FunctionCallStatement'.split())

NIfStatement, NElseBlock, NLoopWithPreconditionStatements, NLoopWithPostconditionStatement = \
    map(pe.NonTerminal, 'IfStatement ElseBlock LoopWithPreconditionStatements LoopWithPostconditionStatement'.split())

NVarDeclarations, NVarDeclaration, NExpression, NLogicalExpression = \
    map(pe.NonTerminal, 'VarDeclarations VarDeclaration Expression LogicalExpression'.split())

NCompareExpression, NCompareOperator, NArithmeticExpression, NPowExpression, NAdditiveOperator, NMultiplicativeOperator = \
    map(pe.NonTerminal, 'CompareExpression NCompareOperator ArithmeticExpression PowExpression AdditiveOperator MultiplicativeOperator'.split())

NTerm, NFactor, NSpec, NArgs, NExtendedVar, NConst = \
    map(pe.NonTerminal, 'Term Factor Spec Args ExtendedVar Const'.split())

NForCycleVarDeclaration, NForCycleTo, NForCycleHead, NMultiplicativeExpression = \
    map(pe.NonTerminal, 'ForCycleVarDeclaration ForCycleTo ForCycleHead MultiplicativeExpression'.split())

# grammar
NProgram |= NFunction, lambda fn: [fn]
NProgram |= NProcedure, lambda pr: [pr]
NProgram |= NProgram, NFunction, lambda _, fn: _ + [fn]
NProgram |= NProgram, NProcedure, lambda _, pr: _ + [pr]

NFunction |= NFunctionHeader, NStatements, 'endfunc', Function
NProcedure |= NProcedureHeader, NStatements, 'endproc', Procedure
NFunctionHeader |= 'func', VARNAME, '(', NSections, ')', '->', NType, FunctionHeaderFull
NProcedureHeader |= 'proc', VARNAME, '(', NSections, ')', ProcedureHeaderFull

NType |= NPrimitiveType
NType |= '[', NType, ']', ArrayType
NPrimitiveType |= KW_INT, lambda: PrimitiveType.Integer
NPrimitiveType |= KW_CHAR, lambda: PrimitiveType.Char
NPrimitiveType |= KW_BOOL, lambda: PrimitiveType.Boolean

NSections |= NSection, lambda sec: [sec]
NSections |= NSections, ';', NSection, lambda secs, sec: secs + [sec]
NSection |= VARNAME, '->', NType, lambda p, t: Section(t, [p])
NSection |= NParameters, ',', VARNAME, '->', NType, lambda ps, p, t: Section(t, ps + [p])
NParameters |= VARNAME, lambda p: [p]
NParameters |= NParameters, ',', VARNAME, lambda ps, p: ps + [p]

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

NAssignmentStatement |= VARNAME, '=', NExpression, lambda l, r: AssignmentStatement(l, r)
NArrayAssignmentStatement |= NArrayCall, '=', NExpression, lambda l, r: AssignmentStatement(l, r)
NFunctionCallStatement |= VARNAME, '(', NArgs, ')', FunctionCallStatement
NArgs |= NExpression, lambda arg: [arg]
NArgs |= NArgs, ',', NExpression, lambda args, arg: args + [arg]

NExtendedVar |= VARNAME, ExtendedVar
NArrayCall |= NSpec, '[', NExpression, ']', ArrayCall

NSpec |= NFunctionCallStatement
NSpec |= '[', NType, VARNAME, ']', ArrayAllocation
NSpec |= '[', NType, INT_CONST, ']', ArrayAllocation
NSpec |= NExtendedVar
NSpec |= NArrayCall
NSpec |= NConst

NConst |= INT_CONST, Const
NConst |= CHAR_CONST, Const
NConst |= STRING_CONST, Const
NConst |= REF_CONST, Const
NConst |= KW_TRUE, Const
NConst |= KW_FALSE, Const

NExpression |= NLogicalExpression
NExpression |= NExpression, KW_OR, NLogicalExpression, BinOperatorExpression
NExpression |= NExpression, KW_XOR, NLogicalExpression, BinOperatorExpression

NLogicalExpression |= NCompareExpression
NLogicalExpression |= NLogicalExpression, KW_AND, NCompareExpression, BinOperatorExpression

def make_op_lambda(op):
    return lambda: op


for op in ('==', '!=', '<', '>', '<=', '>='):
    NCompareOperator |= op, make_op_lambda(op)

NCompareExpression |= NArithmeticExpression
NCompareExpression |= NCompareExpression, NCompareOperator, NArithmeticExpression, BinOperatorExpression

NAdditiveOperator |= '+', lambda: '+'
NAdditiveOperator |= '-', lambda: '-'

NArithmeticExpression |= NMultiplicativeExpression
NArithmeticExpression |= NMultiplicativeExpression, NAdditiveOperator, NMultiplicativeExpression, BinOperatorExpression
# NArithmeticExpression |= NPowExpression
# NArithmeticExpression |= NPowExpression, NAdditiveOperator, NPowExpression, BinOperatorExpression

NMultiplicativeExpression |= NTerm
NMultiplicativeExpression |= NMultiplicativeExpression, NMultiplicativeOperator, NTerm, BinOperatorExpression
# NPowExpression |= NTerm
# NPowExpression |= NTerm, '^', NPowExpression, lambda l, r: BinOperatorExpression(l, '^', r)

NMultiplicativeOperator |= '*', lambda: '*'
NMultiplicativeOperator |= '/', lambda: '/'
NMultiplicativeOperator |= '%', lambda: '%'

NTerm |= NFactor
NTerm |= NFactor, '^', NTerm, lambda l, r: BinOperatorExpression(l, '^', r)

NFactor |= KW_NOT, NSpec, lambda expr: UnaryOperatorExpression('!', expr)
NFactor |= '-', NSpec, lambda expr: UnaryOperatorExpression('-', expr)
NFactor |= NSpec

NIfStatement |= 'if', NExpression, 'then', NStatements, 'endif', lambda expr, stmts: IfStatement(condition=expr, statements=stmts, elseblocks=list())
NIfStatement |= 'if', NExpression, 'then', NStatements, NElseBlock, 'endif', IfStatement
NElseBlock |= 'else', NStatements, lambda stmts: [ElseBlock(condition=None, statements=stmts)]
NElseBlock |= 'elseif', NExpression, 'then', NStatements, NElseBlock, lambda expr, stmts, block: [ElseBlock(condition=expr, statements=stmts)] + block

NLoopWithPreconditionStatements |= 'while', NExpression, 'do', NStatements, 'endwhile', WhileDoStatement

NLoopWithPreconditionStatements |= NForCycleHead, 'do', NStatements, 'endfor', ForDoStatement

NForCycleHead |= 'for', NForCycleVarDeclaration, 'to', NForCycleTo, lambda decl, to: ForCycleHead(decl, to, step=None)
NForCycleHead |= 'for', NForCycleVarDeclaration, 'to', NForCycleTo, 'step', INT_CONST, lambda decl, to, step: ForCycleHead(decl, to, step=step)

NForCycleVarDeclaration |= VARNAME, '=', INT_CONST, '->', KW_INT, lambda name, expr: ForDoVarDeclaration(name=name, value=expr, type=PrimitiveType.Integer)
NForCycleVarDeclaration |= VARNAME, '=', CHAR_CONST, '->', KW_CHAR, lambda name, expr: ForDoVarDeclaration(name=name, value=expr, type=PrimitiveType.Char)
NForCycleVarDeclaration |= VARNAME, '=', NExpression, lambda name, expr: ForDoVarDeclaration(name=name, value=expr, type=None)


NForCycleTo |= NExpression
# NForCycleTo |= INT_CONST, lambda i: i
# NForCycleTo |= CHAR_CONST, lambda c: c

NLoopWithPostconditionStatement |= 'repeat', NStatements, 'until', NExpression, RepeatUntilStatement

parser = pe.Parser(NProgram)
# parser.print_table()
parser.add_skipped_domain('\s')
parser.add_skipped_domain('\\(\\*.*\\*\\)')
assert parser.is_lalr_one()

for filename in sys.argv[1:]:
    try:
        with open(filename) as f:
            tree = parser.parse(f.read())
            pprint(tree)
    except pe.Error as e:
        print(f'Ошибка {e.pos}: {e.message}')
    except Exception as e:
        print(e)
```

# Тестирование

## Входные данные

```
func sumIntegers(a -> int; b -> int) -> int
	c -> char;
	c = 'A';
	A = [int 5], B = [int 10] -> [int];
	x, y = B[3], z = y -> int;
	y = y % 10;
	x = a * 2 + 10 / 5;
	if a < b then
		a = a + 1
	else
		b = b + 1
	endif;
	
	if a < b then
		a = a + 1
	elseif a == b + 1 then
		b = b + 1
	elseif a > b + 1 then
		a = a * 10
	else
		b = b * 10
	endif

endfunc

proc example(a -> [int])
	for letter = 'A' -> char to 'Z' do
		print(letter)
	endfor
endproc

func SumVectors(A, B -> [int]) -> [int]
	size = length(A) -> int;
	check size == length(B);
	C = [int size] -> [int];
	for i = 0 -> int to size - 1 do
		C[i] = A[i] + B[i]
	endfor;
	SumVectors = C
endfunc

proc example4(a -> char)
	string = "We say \"Hello, World!\"\n" -> [char]
endproc
```

## Вывод на `stdout`

<!-- ENABLE LONG LINES -->

```
[Function(header=FunctionHeaderFull(name='sumIntegers',
                                    sections=[Section(type=<PrimitiveType.Integer: 'int'>,
                                                      parameters=['a']),
                                              Section(type=<PrimitiveType.Integer: 'int'>,
                                                      parameters=['b'])],
                                    return_type=<PrimitiveType.Integer: 'int'>),
          body=[DeclarationStatement(type=<PrimitiveType.Char: 'char'>,
                                     var_declarations=[VarDeclaration(name='c',
                                                                      expression=None)]),
                AssignmentStatement(left='c', right=Const(value="'A'")),
                DeclarationStatement(type=ArrayType(type=<PrimitiveType.Integer: 'int'>),
                                     var_declarations=[VarDeclaration(name='A',
                                                                      expression=ArrayAllocation(type=<PrimitiveType.Integer: 'int'>,
                                                                                                 size='5')),
                                                       VarDeclaration(name='B',
                                                                      expression=ArrayAllocation(type=<PrimitiveType.Integer: 'int'>,
                                                                                                 size='10'))]),
                DeclarationStatement(type=<PrimitiveType.Integer: 'int'>,
                                     var_declarations=[VarDeclaration(name='x',
                                                                      expression=None),
                                                       VarDeclaration(name='y',
                                                                      expression=ArrayCall(array=ExtendedVar(value='B'),
                                                                                           ref=Const(value='3'))),
                                                       VarDeclaration(name='z',
                                                                      expression=ExtendedVar(value='y'))]),
                AssignmentStatement(left='y',
                                    right=BinOperatorExpression(left=ExtendedVar(value='y'),
                                                                operator='%',
                                                                right=Const(value='10'))),
                AssignmentStatement(left='x',
                                    right=BinOperatorExpression(left=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                           operator='*',
                                                                                           right=Const(value='2')),
                                                                operator='+',
                                                                right=BinOperatorExpression(left=Const(value='10'),
                                                                                            operator='/',
                                                                                            right=Const(value='5')))),
                IfStatement(condition=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                            operator='<',
                                                            right=ExtendedVar(value='b')),
                            statements=[AssignmentStatement(left='a',
                                                            right=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                        operator='+',
                                                                                        right=Const(value='1')))],
                            elseblocks=[ElseBlock(condition=None,
                                                  statements=[AssignmentStatement(left='b',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='b'),
                                                                                                              operator='+',
                                                                                                              right=Const(value='1')))])]),
                IfStatement(condition=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                            operator='<',
                                                            right=ExtendedVar(value='b')),
                            statements=[AssignmentStatement(left='a',
                                                            right=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                        operator='+',
                                                                                        right=Const(value='1')))],
                            elseblocks=[ElseBlock(condition=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                  operator='==',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='b'),
                                                                                                              operator='+',
                                                                                                              right=Const(value='1'))),
                                                  statements=[AssignmentStatement(left='b',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='b'),
                                                                                                              operator='+',
                                                                                                              right=Const(value='1')))]),
                                        ElseBlock(condition=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                  operator='>',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='b'),
                                                                                                              operator='+',
                                                                                                              right=Const(value='1'))),
                                                  statements=[AssignmentStatement(left='a',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='a'),
                                                                                                              operator='*',
                                                                                                              right=Const(value='10')))]),
                                        ElseBlock(condition=None,
                                                  statements=[AssignmentStatement(left='b',
                                                                                  right=BinOperatorExpression(left=ExtendedVar(value='b'),
                                                                                                              operator='*',
                                                                                                              right=Const(value='10')))])])]),
 Procedure(header=ProcedureHeaderFull(name='example',
                                      sections=[Section(type=ArrayType(type=<PrimitiveType.Integer: 'int'>),
                                                        parameters=['a'])]),
           body=[ForDoStatement(head=ForCycleHead(var_declaration=ForDoVarDeclaration(name='letter',
                                                                                      value="'A'",
                                                                                      type=<PrimitiveType.Char: 'char'>),
                                                  to=Const(value="'Z'"),
                                                  step=None),
                                statements=[FunctionCallStatement(name='print',
                                                                  args=[ExtendedVar(value='letter')])])]),
 Function(header=FunctionHeaderFull(name='SumVectors',
                                    sections=[Section(type=ArrayType(type=<PrimitiveType.Integer: 'int'>),
                                                      parameters=['A', 'B'])],
                                    return_type=ArrayType(type=<PrimitiveType.Integer: 'int'>)),
          body=[DeclarationStatement(type=<PrimitiveType.Integer: 'int'>,
                                     var_declarations=[VarDeclaration(name='size',
                                                                      expression=FunctionCallStatement(name='length',
                                                                                                       args=[ExtendedVar(value='A')]))]),
                WarningStatement(expr=BinOperatorExpression(left=ExtendedVar(value='size'),
                                                            operator='==',
                                                            right=FunctionCallStatement(name='length',
                                                                                        args=[ExtendedVar(value='B')]))),
                DeclarationStatement(type=ArrayType(type=<PrimitiveType.Integer: 'int'>),
                                     var_declarations=[VarDeclaration(name='C',
                                                                      expression=ArrayAllocation(type=<PrimitiveType.Integer: 'int'>,
                                                                                                 size='size'))]),
                ForDoStatement(head=ForCycleHead(var_declaration=ForDoVarDeclaration(name='i',
                                                                                     value='0',
                                                                                     type=<PrimitiveType.Integer: 'int'>),
                                                 to=BinOperatorExpression(left=ExtendedVar(value='size'),
                                                                          operator='-',
                                                                          right=Const(value='1')),
                                                 step=None),
                               statements=[AssignmentStatement(left=ArrayCall(array=ExtendedVar(value='C'),
                                                                              ref=ExtendedVar(value='i')),
                                                               right=BinOperatorExpression(left=ArrayCall(array=ExtendedVar(value='A'),
                                                                                                          ref=ExtendedVar(value='i')),
                                                                                           operator='+',
                                                                                           right=ArrayCall(array=ExtendedVar(value='B'),
                                                                                                           ref=ExtendedVar(value='i'))))]),
                AssignmentStatement(left='SumVectors',
                                    right=ExtendedVar(value='C'))]),
 Procedure(header=ProcedureHeaderFull(name='example4',
                                      sections=[Section(type=<PrimitiveType.Char: 'char'>,
                                                        parameters=['a'])]),
           body=[DeclarationStatement(type=ArrayType(type=<PrimitiveType.Char: 'char'>),
                                      var_declarations=[VarDeclaration(name='string',
                                                                       expression=Const(value='"We '
                                                                                              'say '
                                                                                              '\\"Hello, '
                                                                                              'World!\\"\\n"'))])])]

```

# Вывод
В результате выполнения данной лабораторной работы была составлена грамматика для "игрушечного" языка L3, представляющего собой минимальный набор функционала, который присутствует в каждом языке программирования. 

Также, на мой взгляд, данный язык был усложнён возможностью разделять объявление переменных (а также параметры функций/процедур) на секции типов; возможностью записывать несколько видов циклов (например, несколько видов циклов с предусловием с опциональным step или возможностью указывать тип итератора цикла).

В ходе защиты лабораторной работы выяснилось, что изначальное описание языка, подразумевающее запись умножения через пробел приводит к многим неоднозначностям и затруднениям в разрешении конфликтов грамматики. Поэтому было принято решение использовать звёздочку в качестве оператора умножения.