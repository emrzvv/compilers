import re
from pprint import pprint

class Lexer:
    def __init__(self, input_text):
        self.input_text = input_text
        self.pos = 0
        self.tokens = []
        self.token_specs = [
            ('NUMBER',   r'\d+'),           # Integer
            ('LPAREN',   r'\('),            # Left Parenthesis
            ('RPAREN',   r'\)'),            # Right Parenthesis
            ('DEFINE',   r'define'),        # 'define' keyword
            ('IF',       r'if'),            # 'if' keyword
            ('COND',     r'cond'),          # 'cond' keyword
            ('LET',      r'let'),           # 'let' keyword
            ('LAMBDA',   r'lambda'),        # 'lambda' keyword
            ('ID',       r'[a-zA-Z_][a-zA-Z0-9_]*'), # Identifiers
            ('BINOP',    r'[+\-*/]'),       # Binary operators
            ('COMP',     r'[<>]=?|='),      # Comparison operators
            ('WS',       r'\s+'),           # Whitespace
            ('MISMATCH', r'.')              # Any other character
        ]
        self.token_re = re.compile('|'.join(f'(?P<{pair[0]}>{pair[1]})' for pair in self.token_specs))

    def tokenize(self):
        prev_token = None
        for match in self.token_re.finditer(self.input_text):
            token_type = match.lastgroup
            token_value = match.group(token_type)
            if token_type == 'WS':
                continue
            elif token_type == 'MISMATCH':
                raise RuntimeError(f'Unexpected character: {token_value}')
            else:
                self.tokens.append((token_type, token_value))
            prev_token = (token_type, token_value)
        return self.tokens

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def current_token(self):
        if self.pos < len(self.tokens):
            return self.tokens[self.pos]
        return None

    def eat(self, token_type):
        token = self.current_token()
        if token and token[0] == token_type:
            self.pos += 1
        else:
            raise SyntaxError(f"Expected {token_type}, got {token}")

    def parse(self):
        return self.Program()

    def Program(self): # Program -> Definitions
        definitions = self.Definitions()
        return ('Program', definitions)

    def Definitions(self): # Definitions -> Define Definitions | .
        if self.current_token() and self.current_token()[0] == 'LPAREN':
            define = self.Define()
            definitions = self.Definitions()
            return ('Definitions', define, definitions)
        return # TODO: узнать как обрабатывать eps

    def Define(self): # Define -> "(" "define" DefinitionTail ")"
        self.eat('LPAREN')
        self.eat('DEFINE')
        definition_tail = self.DefinitionTail()
        self.eat('RPAREN')
        return ('Define', definition_tail)

    def DefinitionTail(self): # DefinitionTail -> FunctionDef | VariableDef
        if self.current_token() and self.current_token()[0] == 'LPAREN':
            function_def = self.FunctionDef()
            return ('FunctionDef', function_def)
        else:
            variable_def = self.VariableDef()
            return ('VariableDef', variable_def)

    def FunctionDef(self): # FunctionDef -> "(" identifier Parameters ")" ExpressionList
        self.eat('LPAREN')
        identifier = self.Identifier()
        parameters = self.Parameters()
        self.eat('RPAREN')
        expression_list = self.ExpressionList()
        return ('FunctionDef', identifier, parameters, expression_list)

    def VariableDef(self): # VariableDef -> identifier " " Expression
        identifier = self.Identifier()
        expression = self.Expression()
        return ('VariableDef', identifier, expression)

    def Parameters(self): # Parameters -> identifier ParametersTail
        identifier = self.Identifier()
        parameters_tail = self.ParametersTail()
        return ('Parameters', identifier, parameters_tail)

    def ParametersTail(self): # ParametersTail -> Parameters | .
        if self.current_token() and self.current_token()[0] == 'ID':
            parameters = self.Parameters()
            return ('ParametersTail', parameters)
        return

    def Expression(self): # Expression -> "(" ExpressionExt ")" | SimpleExpr
        if self.current_token() and self.current_token()[0] == 'LPAREN':
            self.eat('LPAREN')
            expression_ext = self.ExpressionExt()
            self.eat('RPAREN')
            return ('Expression', expression_ext)
        else:
            simple_expr = self.SimpleExpr()
            return ('Expression', simple_expr)

    def ExpressionExt(self): 
        '''
        ExpressionExt -> 
            IfExpr | CondExpr | LetExpr | LambdaDef | BinOpExpr | ComparisonExpr
        '''
        token = self.current_token()
        if token[0] == 'IF':
            return self.IfExpr()
        elif token[0] == 'COND':
            return self.CondExpr()
        elif token[0] == 'LET':
            return self.LetExpr()
        elif token[0] == 'LAMBDA':
            return self.LambdaDef()
        elif token[0] == 'BINOP':
            return self.BinOpExpr()
        elif token[0] == 'COMP':
            return self.ComparisonExpr()
        else:
            raise SyntaxError(f"Unexpected token {token} in ExpressionExt")

    def IfExpr(self): # IfExpr -> "if" Expression Expression Expression
        self.eat('IF')
        cond = self.Expression()
        expr_t = self.Expression()
        expr_f = self.Expression()
        return ('IfExpr', cond, expr_t, expr_f)

    def CondExpr(self): # CondExpr -> "cond" CondBody
        self.eat('COND')
        cond_body = self.CondBody()
        return ('CondExpr', cond_body)

    def CondBody(self): # CondBody -> CondOnly CondBody | .
        if self.current_token() and self.current_token()[0] == 'LPAREN':
            cond_only = self.CondOnly()
            cond_body = self.CondBody()
            return ('CondBody', cond_only, cond_body)
        return ('CondBody',)

    def CondOnly(self): # CondOnly -> "(" Expression Expression ")"
        self.eat('LPAREN')
        expr1 = self.Expression()
        expr2 = self.Expression()
        self.eat('RPAREN')
        return ('CondOnly', expr1, expr2)

    def LetExpr(self): # LetExpr -> "let" "(" LetBindings ")" ExpressionList
        self.eat('LET')
        self.eat('LPAREN')
        let_bindings = self.LetBindings()
        self.eat('RPAREN')
        expression_list = self.ExpressionList()
        return ('LetExpr', let_bindings, expression_list)

    def LetBindings(self): # LetBindings -> LetBinding LetBindings | .
        if self.current_token() and self.current_token()[0] == 'LPAREN':
            let_binding = self.LetBinding()
            let_bindings = self.LetBindings()
            return ('LetBindings', let_binding, let_bindings)
        return ('LetBindings',)

    def LetBinding(self): # LetBinding -> "(" identifier Expression ")"
        self.eat('LPAREN')
        identifier = self.Identifier()
        expression = self.Expression()
        self.eat('RPAREN')
        return ('LetBinding', identifier, expression)

    def LambdaDef(self): # LambdaDef -> "lambda (" Parameters ")" ExpressionList
        self.eat('LAMBDA')
        self.eat('LPAREN')
        parameters = self.Parameters()
        self.eat('RPAREN')
        expression_list = self.ExpressionList()
        return ('LambdaDef', parameters, expression_list)

    def BinOpExpr(self): # BinOpExpr -> BinOp ExpressionList
        bin_op = self.BinOp()
        expression_list = self.ExpressionList()
        return ('BinOpExpr', bin_op, expression_list)

    def ExpressionList(self): # ExpressionList -> Expression ExpressionListTail
        expression = self.Expression()
        expression_list_tail = self.ExpressionListTail()
        return ('ExpressionList', expression, expression_list_tail)

    def ExpressionListTail(self): # ExpressionListTail -> ExpressionList |
        if self.current_token() and self.current_token()[0] in {'LPAREN', 'ID', 'NUMBER'}:
            expression_list = self.ExpressionList()
            return ('ExpressionListTail', expression_list)
        return ('ExpressionListTail',)

    def ComparisonExpr(self): # ComparisonExpr -> ComparisonOp ExpressionList
        comparison_op = self.ComparisonOp()
        expression_list = self.ExpressionList()
        return ('ComparisonExpr', comparison_op, expression_list)

    def SimpleExpr(self): # SimpleExpr -> identifier | number
        token = self.current_token()
        if token[0] == 'ID':
            return self.Identifier()
        elif token[0] == 'NUMBER':
            return self.Number()
        else:
            raise SyntaxError(f"Unexpected token {token} in SimpleExpr")

    def BinOp(self): # BinOp -> "+" | "-" | "*" | "/"
        token = self.current_token()
        if token[0] == 'BINOP':
            self.eat('BINOP')
            return ('BinOp', token[1])
        else:
            raise SyntaxError(f"Unexpected token {token} in BinOp")

    def ComparisonOp(self): # ComparisonOp -> ">" | "<" | ">=" | "<=" | "="
        token = self.current_token()
        if token[0] == 'COMP':
            self.eat('COMP')
            return ('ComparisonOp', token[1])
        else:
            raise SyntaxError(f"Unexpected token {token} in ComparisonOp")

    def Identifier(self):
        token = self.current_token()
        if token[0] == 'ID':
            self.eat('ID')
            return ('Identifier', token[1])
        else:
            raise SyntaxError(f"Unexpected token {token} in Identifier")

    def Number(self):
        token = self.current_token()
        if token[0] == 'NUMBER':
            self.eat('NUMBER')
            return ('Number', token[1])
        else:
            raise SyntaxError(f"Unexpected token {token} in Number")


input_text = '''
(define (f x y)
  (if (> x y)
      (cond 
            ((> x 0) (- x))
            ((< y 0) (/ y))
      )
      (let ((a 1)
            (b 2))
        (* a b)
      )
  )
)

(define x (+ 100 500))

(define (f x)
  (lambda (y) (+ x y)))
'''
lexer = Lexer(input_text)
tokens = lexer.tokenize()
pprint(tokens)
parser = Parser(tokens)
parsed_program = parser.parse()
pprint(parsed_program)
