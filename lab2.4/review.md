% Лабораторная работа № 2.4 «Рекурсивный спуск»
% 18 июня 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является изучение алгоритмов построения парсеров методом рекурсивного спуска.

# Индивидуальный вариант
Написать парсер рекурсивным спуском для подмножества Scheme:
```scheme
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
```
# Реализация

## Лексическая структура
* IDENTIFIER = [a-zA-Z_][a-zA-Z0-9_]*

## Грамматика языка
```
Program -> (Definition)+
Definition -> "(" "define" DefinitionTail ")"
DefinitionTail -> FunctionDef | VariableDef

FunctionDef -> "(" IDENTIFIER Parameters ")" ExpressionList
VariableDef -> IDENTIFIER Expression

Parameters -> (IDENTIFIER)+

Expression -> "(" ExpressionExt ")" | SimpleExpression
SimpleExpression -> IDENTIFIER | NUMBER 

ExpressionExt -> 
    IfExpr | CondExpr | LetExpr | LambdaDef | BinOpExpr | ComparisonExpr

IfExpr -> "if" Expression Expression Expression
CondExpr -> "cond" (CondOnly)+
CondOnly -> "(" Expression Expression ")"

LetExpr -> "let" "(" (LetBinding)+ ")" ExpressionList
LetBinding -> "(" IDENTIFIER Expression ")"

LambdaDef -> "lambda" "(" Parameters ")" ExpressionList

BinOpExpr -> BinOp ExpressionList
ExpressionList -> (Expression)+

ComparisonExpr -> ComparisonOp ExpressionList

BinOp -> "+" | "-" | "*" | "/"
ComparisonOp -> ">" | "<" | ">=" | "<=" | "="
```
## Программная реализация

```python
import re
import pprint
import json

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
            return token[1]
        else:
            raise SyntaxError(f"Expected {token_type}, got {token}")

    def parse(self): # Program -> (Definition)+
        definitions = []
        while self.pos < len(self.tokens):
            definitions.append(self.parse_definition())
        return {'Program': definitions}

    def parse_definition(self): # Definition -> "(" "define" DefinitionTail ")"
        self.eat('LPAREN')
        self.eat('DEFINE')
        definition_tail = self.parse_definition_tail()
        self.eat('RPAREN')
        return {'Definition': definition_tail}

    def parse_definition_tail(self): # DefinitionTail -> FunctionDef | VariableDef
        if self.current_token()[0] == 'LPAREN':
            return self.parse_function_def()
        else:
            return self.parse_variable_def()

    def parse_function_def(self): # FunctionDef -> "(" IDENTIFIER Parameters ")" ExpressionList
        self.eat('LPAREN')
        identifier = self.eat('ID')
        parameters = self.parse_parameters()
        self.eat('RPAREN')
        expression_list = self.parse_expression_list()
        return {'FunctionDef': {'Identifier': identifier, 'Parameters': parameters, 'ExpressionList': expression_list}}

    def parse_variable_def(self): # VariableDef -> IDENTIFIER Expression
        identifier = self.eat('ID')
        expression = self.parse_expression()
        return {'VariableDef': {'Identifier': identifier, 'Expression': expression}}

    def parse_parameters(self): # Parameters -> (IDENTIFIER)+
        parameters = []
        while self.current_token()[0] == 'ID':
            parameters.append(self.eat('ID'))
        return parameters

    def parse_expression(self): # Expression -> "(" ExpressionExt ")" | SimpleExpression
        if self.current_token()[0] == 'LPAREN':
            self.eat('LPAREN')
            expression_ext = self.parse_expression_ext()
            self.eat('RPAREN')
            return expression_ext
        else:
            return self.parse_simple_expression()

    def parse_simple_expression(self): # SimpleExpression -> IDENTIFIER | NUMBER 
        if self.current_token()[0] == 'ID':
            return {'SimpleExpression': {'Identifier': self.eat('ID')}}
        elif self.current_token()[0] == 'NUMBER':
            return {'SimpleExpression': {'Number': self.eat('NUMBER')}}
        else:
            raise SyntaxError('Expected ID or NUMBER')

    def parse_expression_ext(self): # ExpressionExt -> IfExpr | CondExpr | LetExpr | LambdaDef | BinOpExpr | ComparisonExpr
        token_type = self.current_token()[0]
        if token_type == 'IF':
            return self.parse_if_expr()
        elif token_type == 'COND':
            return self.parse_cond_expr()
        elif token_type == 'LET':
            return self.parse_let_expr()
        elif token_type == 'LAMBDA':
            return self.parse_lambda_def()
        elif token_type == 'BINOP':
            return self.parse_bin_op_expr()
        elif token_type == 'COMP':
            return self.parse_comparison_expr()
        else:
            raise SyntaxError(f'Unexpected token: {token_type}')

    def parse_if_expr(self): # IfExpr -> "if" Expression Expression Expression
        self.eat('IF')
        expr1 = self.parse_expression()
        expr2 = self.parse_expression()
        expr3 = self.parse_expression()
        return {'IfExpr': {'Condition': expr1, 'True': expr2, 'False': expr3}}

    def parse_cond_expr(self): # CondExpr -> "cond" (CondOnly)+
        self.eat('COND')
        cond_only_list = []
        while self.current_token()[0] == 'LPAREN':
            cond_only_list.append(self.parse_cond_only())
        return {'CondExpr': cond_only_list}

    def parse_cond_only(self): # CondOnly -> "(" Expression Expression ")"
        self.eat('LPAREN')
        expr1 = self.parse_expression()
        expr2 = self.parse_expression()
        self.eat('RPAREN')
        return {'CondOnly': {'Expr1': expr1, 'Expr2': expr2}}

    def parse_let_expr(self): # LetExpr -> "let" "(" (LetBinding)+ ")" ExpressionList
        self.eat('LET')
        self.eat('LPAREN')
        let_bindings = []
        while self.current_token()[0] == 'LPAREN':
            let_bindings.append(self.parse_let_binding())
        self.eat('RPAREN')
        expression_list = self.parse_expression_list()
        return {'LetExpr': {'LetBindings': let_bindings, 'ExpressionList': expression_list}}

    def parse_let_binding(self): # LetBinding -> "(" IDENTIFIER Expression ")"
        self.eat('LPAREN')
        identifier = self.eat('ID')
        expression = self.parse_expression()
        self.eat('RPAREN')
        return {'LetBinding': {'Identifier': identifier, 'Expression': expression}}

    def parse_lambda_def(self): # LambdaDef -> "lambda" "(" Parameters ")" ExpressionList
        self.eat('LAMBDA')
        self.eat('LPAREN')
        parameters = self.parse_parameters()
        self.eat('RPAREN')
        expression_list = self.parse_expression_list()
        return {'LambdaDef': {'Parameters': parameters, 'ExpressionList': expression_list}}

    def parse_bin_op_expr(self): # BinOpExpr -> BinOp ExpressionList
        bin_op = self.eat('BINOP')
        expression_list = self.parse_expression_list()
        return {'BinOpExpr': {'BinOp': bin_op, 'ExpressionList': expression_list}}

    def parse_comparison_expr(self): # ComparisonExpr -> ComparisonOp ExpressionList
        comp_op = self.eat('COMP')
        expr1 = self.parse_expression()
        expr2 = self.parse_expression()
        # expression_list = self.parse_expression_list()
        return {'ComparisonExpr': {'CompOp': comp_op, 'Expr1': expr1, 'Expr2': expr2}}

    def parse_expression_list(self): # ExpressionList -> (Expression)+
        expressions = []
        while self.current_token()[0] in ('LPAREN', 'ID', 'NUMBER'):
            expressions.append(self.parse_expression())
        return expressions

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
pprint.pp(tokens)
parser = Parser(tokens)
parsed_program = parser.parse()
# pprint.pprint(parsed_program, width=80)
print(json.dumps(parsed_program, indent=2))

```

# Тестирование

Входные данные

```
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
```

Вывод на `stdout`

```json
{
  "Program": [
    {
      "Definition": {
        "FunctionDef": {
          "Identifier": "f",
          "Parameters": [
            "x",
            "y"
          ],
          "ExpressionList": [
            {
              "IfExpr": {
                "Condition": {
                  "ComparisonExpr": {
                    "CompOp": ">",
                    "Expr1": {
                      "SimpleExpression": {
                        "Identifier": "x"
                      }
                    },
                    "Expr2": {
                      "SimpleExpression": {
                        "Identifier": "y"
                      }
                    }
                  }
                },
                "True": {
                  "CondExpr": [
                    {
                      "CondOnly": {
                        "Expr1": {
                          "ComparisonExpr": {
                            "CompOp": ">",
                            "Expr1": {
                              "SimpleExpression": {
                                "Identifier": "x"
                              }
                            },
                            "Expr2": {
                              "SimpleExpression": {
                                "Number": "0"
                              }
                            }
                          }
                        },
                        "Expr2": {
                          "BinOpExpr": {
                            "BinOp": "-",
                            "ExpressionList": [
                              {
                                "SimpleExpression": {
                                  "Identifier": "x"
                                }
                              }
                            ]
                          }
                        }
                      }
                    },
                    {
                      "CondOnly": {
                        "Expr1": {
                          "ComparisonExpr": {
                            "CompOp": "<",
                            "Expr1": {
                              "SimpleExpression": {
                                "Identifier": "y"
                              }
                            },
                            "Expr2": {
                              "SimpleExpression": {
                                "Number": "0"
                              }
                            }
                          }
                        },
                        "Expr2": {
                          "BinOpExpr": {
                            "BinOp": "/",
                            "ExpressionList": [
                              {
                                "SimpleExpression": {
                                  "Identifier": "y"
                                }
                              }
                            ]
                          }
                        }
                      }
                    }
                  ]
                },
                "False": {
                  "LetExpr": {
                    "LetBindings": [
                      {
                        "LetBinding": {
                          "Identifier": "a",
                          "Expression": {
                            "SimpleExpression": {
                              "Number": "1"
                            }
                          }
                        }
                      },
                      {
                        "LetBinding": {
                          "Identifier": "b",
                          "Expression": {
                            "SimpleExpression": {
                              "Number": "2"
                            }
                          }
                        }
                      }
                    ],
                    "ExpressionList": [
                      {
                        "BinOpExpr": {
                          "BinOp": "*",
                          "ExpressionList": [
                            {
                              "SimpleExpression": {
                                "Identifier": "a"
                              }
                            },
                            {
                              "SimpleExpression": {
                                "Identifier": "b"
                              }
                            }
                          ]
                        }
                      }
                    ]
                  }
                }
              }
            }
          ]
        }
      }
    },
    {
      "Definition": {
        "VariableDef": {
          "Identifier": "x",
          "Expression": {
            "BinOpExpr": {
              "BinOp": "+",
              "ExpressionList": [
                {
                  "SimpleExpression": {
                    "Number": "100"
                  }
                },
                {
                  "SimpleExpression": {
                    "Number": "500"
                  }
                }
              ]
            }
          }
        }
      }
    },
    {
      "Definition": {
        "FunctionDef": {
          "Identifier": "f",
          "Parameters": [
            "x"
          ],
          "ExpressionList": [
            {
              "LambdaDef": {
                "Parameters": [
                  "y"
                ],
                "ExpressionList": [
                  {
                    "BinOpExpr": {
                      "BinOp": "+",
                      "ExpressionList": [
                        {
                          "SimpleExpression": {
                            "Identifier": "x"
                          }
                        },
                        {
                          "SimpleExpression": {
                            "Identifier": "y"
                          }
                        }
                      ]
                    }
                  }
                ]
              }
            }
          ]
        }
      }
    }
  ]
}

```

# Вывод
В результате выполнения данной лабораторной работы ознакомился с алгоритмом нисходящего парсинга - рекурсивным спуском.
Поскольку изначальное индивидуальное задание (язык L3) было очень объёмным (множество нетерминалов и правил, трудоёмкий процесс 
перестроения грамматики из LALR(1) в LL(1) + переписывание в РБНФ), оно было заменено на подмножество языка Scheme.

Лабораторная работа оказалось несложной, рекурсивный спуск - довольно простой способ построить дерево разбора, однако
для его применения сильно ограничен класс грамматик. Также, наверно, он плохо подходит для больших/длинных грамматик, что требует 
больших времязатрат.