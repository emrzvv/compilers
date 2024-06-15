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
