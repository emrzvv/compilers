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
NSpec |= '[', NType, VARNAME, ']', ArrayAllocation
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
            # pprint(tree)
            tree.check()
    except pe.Error as e:
        print(f'Ошибка {e.pos}: {e.message}')
    except Exception as e:
        print(e)