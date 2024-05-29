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