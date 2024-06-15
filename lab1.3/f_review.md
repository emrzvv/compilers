% Лабораторная работа № 1.3 «Объектно-ориентированный
  лексический анализатор»
% 17 апреля 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является приобретение навыка реализации лексического анализатора на
объектно-ориентированном языке без применения каких-либо средств автоматизации решения задачи лексического
анализа.

# Индивидуальный вариант
- Числа: последовательности десятичных цифр.
- Знаки операций: «+», «-», «*», «/», «(», «)».
- Комментарии начинаются на «(*», заканчиваются на «*)», не могут быть вложенными.

# Реализация

Файл `Position.scala`
```scala
package domain

case class Position(line: Int, pos: Int, index: Int) {
  override def toString: String = s"($line, $pos)"
  def isEmpty: Boolean = line == -1 && pos == -1 && index == -1
  def equalTo(other: Position): Boolean = line == other.line && pos == other.pos && index == other.index
}

object Position {
  def apply(): Position = Position(1, 1, 0)
  def empty: Position = Position(-1, -1, -1)
}
```

Файл `Fragment.scala`
```scala
package domain

case class Fragment(start: Position, follow: Position) {
  override def toString: String = s"${start.toString}-${follow.toString}"
  def isEmpty: Boolean = start.isEmpty && follow.isEmpty
}

object Fragment {
  def empty(): Fragment = Fragment(Position.empty, Position.empty)
}
```

Файл `DomainTag.scala`
```scala
package domain

object DomainTag extends Enumeration {
  type Tag = Value
  val Numeric, Operation, Comment, EOF, Error = Value
}
```

Файл `Token.scala`
```scala
package domain

import domain.DomainTag.Tag

trait Token{
  def tag: Tag
  def fragment: Fragment
}

case class NumericToken(fragment: Fragment, value: Long) extends Token {
  override val tag: Tag = DomainTag.Numeric

  override def toString: String = s"NUMERIC: $fragment : $value"
}
case class OperationToken(fragment: Fragment, value: Char) extends Token{
  override def tag: Tag = DomainTag.Operation

  override def toString: String = s"OPERATION: $fragment : $value"
}
case class CommentToken(fragment: Fragment, value: String) extends Token {
  override def tag: Tag = DomainTag.Comment

  override def toString: String = s"COMMENT: $fragment : $value"
}
case class EndToken(fragment: Fragment, value: String = "\u0000") extends Token {
  override def tag: Tag = DomainTag.EOF
}
case class Error(fragment: Fragment = Fragment.empty()) extends Token {

  override def tag: Tag = DomainTag.Error
}
object OperationToken {
  val values: Set[Char] = Set('+', '-', '*', '/', '(', ')')

  implicit class OperationOps(chr: Char) {
    def isOperation: Boolean = values.contains(chr)
  }
}
```
Файл `Lexer.scala`
```scala
import domain.{CommentToken, EndToken, Error, Fragment, NumericToken, OperationToken, Position, Token}

import scala.annotation.tailrec

class Lexer(text: String, val currentPosition: Position) {
  import Lexer._

  private def raiseError(position: Position): Position = {
    @tailrec
    def loop(current: Position): Position = {
      if (isSpaceAt(current) || isNewLineAt(current) || isEOLAt(current)) {
        current
      } else {
        loop(nextPositionFrom(current))
      }
    }

    val endPosition = loop(position)
    println(s"ERROR: ${Fragment(position, endPosition)} : ${text.substring(position.index,
endPosition.index)}")
    endPosition
  }

  private def isNewLineAt(position: Position): Boolean = {
    if (text.charAt(position.index) == '\r' && position.index < text.length)
      text.charAt(position.index + 1) == '\n'
    else
      text.charAt(position.index) == '\n'
  }

  private def isSpaceAt(position: Position): Boolean = {
    text.charAt(position.index).isWhitespace || text.charAt(position.index) == '\n'
  }

  private def isEOLAt(position: Position): Boolean = {
    text.charAt(position.index) == '\u0000'
  }

  private def isDigitAt(position: Position): Boolean = {
    text.charAt(position.index).isDigit
  }

  private def isOperationAt(position: Position): Boolean = {
    import domain.OperationToken._
    text.charAt(position.index).isOperation
  }

  private def isCommentAt(position: Position): (Boolean, Fragment) = {
    // index == '(' && index + 1 < text.length && index + 1 == '*'
    // parse until index == '*' && index + 1 < text.length && index + 1 == ')'

    @tailrec
    def loop(current: Position): Position = {
      if (isEOLAt(current)) Position.empty // non-closed comment
      else if (text.charAt(current.index) == '(' &&
          current.index + 1 < text.length &&
          text.charAt(current.index + 1) == '*') {
        Position.empty // cannot be nested
      } else {
        if (text.charAt(current.index) == '*' &&
          current.index + 1 < text.length &&
          text.charAt(current.index + 1) == ')') {
          nextPositionFrom(current) // found comment closing at index + 1
        } else {
          loop(nextPositionFrom(current))
        }
      }
    }

    if (text.charAt(position.index) == '(' &&
        position.index + 1 < text.length &&
        text.charAt(position.index + 1) == '*') {
      val follow = loop(nextPositionFrom(position))
      if (follow.isEmpty) (false, Fragment.empty())
      else (true, Fragment(position, follow))
    } else (false, Fragment.empty())
  }

  private def nextPositionFrom(position: Position): Position = {
    val (updatedLine, updatedPos, updatedIndex) =
      if (position.index != text.length) {
        if (isNewLineAt(position)) {
          if (text.charAt(position.index) == '\r') {
            (position.line + 1, 1, position.index + 2)
          } else {
            (position.line + 1, 1, position.index + 1)
          }
        } else {
          (position.line, position.pos + 1, position.index + 1)
        }
      } else {
        (position.line, position.pos, position.index)
      }
    Position(updatedLine, updatedPos, updatedIndex)
  }
  private def skipSpaces(): Position = {
    @tailrec
    def skip(position: Position): Position = {
      if (isSpaceAt(position)) {
        val next = nextPositionFrom(position)
        if (position.equalTo(next)) {
          position
        } else {
          skip(next)
        }
      } else {
        position
      }
    }

    skip(currentPosition)
  }

  private def getDigit(current: Position): Either[Position, NumericToken] = {
    @tailrec
    def loop(position: Position)(acc: String = ""): (String, Position, Boolean) = {
      if (isSpaceAt(position) || isEOLAt(position)) {
        (acc, position, false)
      } else if (!isDigitAt(position)) {
        val updatedPosition = raiseError(position)
        (acc, updatedPosition, true)
      } else {
        loop(nextPositionFrom(position))(acc + text.charAt(position.index))
      }
    }

    val (result, follow, error) = loop(current)()
    if (error) Left(follow)
    else Right(NumericToken(Fragment(current, follow), result.toLong))
  }

  def nextToken(): NextTokenResult = {
    val position = skipSpaces()
    if (isEOLAt(position)) {
      NextTokenResult(EndToken(Fragment(position, position)), Lexer(text, position))
    } else if (isDigitAt(position)) {
      getDigit(position) match {
        case Right(token) => NextTokenResult(token, Lexer(text, token.fragment.follow))
        case Left(pos) => NextTokenResult(Error(Fragment(position, pos)), Lexer(text, pos))
      }
    } else {
      val (isComment, commentFragment) = isCommentAt(position)
      if (isComment) {
        NextTokenResult(
          CommentToken(commentFragment, text.substring(commentFragment.start.index + 2,
commentFragment.follow.index - 1)),
          Lexer(text, nextPositionFrom(commentFragment.follow)))
      } else if (isOperationAt(position)) {
        NextTokenResult(
          OperationToken(Fragment(position, position), text.charAt(position.index)),
          Lexer(text, nextPositionFrom(position))
        )
      } else {
        val updatedPos = raiseError(position)
        NextTokenResult(
          Error(Fragment(position, updatedPos)),
          Lexer(text, updatedPos)
        )
      }
    }
  }
}

object Lexer {
  def apply(input: String): Lexer = {
    new Lexer(text = input + '\u0000', currentPosition = Position())
  }

  def apply(text: String, position: Position): Lexer = {
    new Lexer(text = text, currentPosition = position)
  }

  def getTokens(lexer: Lexer): Vector[Token] = {
    @tailrec
    def loop(currentLexer: Lexer)(acc: Vector[Token] = Vector.empty): Vector[Token] = {
//      println(currentLexer.currentPosition)
//      println(acc)
      val nextTokenResult = currentLexer.nextToken()
      nextTokenResult.token match {
        case EndToken(_, _) => acc
        case Error(_) => loop(nextTokenResult.lexer)(acc)
        case _@token => loop(nextTokenResult.lexer)(acc :+ token)
      }
    }

    loop(lexer)()
  }

  case class NextTokenResult(token: Token, lexer: Lexer)
}
```
Файл `Main.scala`:
```scala
import domain.DomainTag

import scala.io.Source

object Main {
  def main(args: Array[String]): Unit = {
    import util.Control._
    using(Source.fromFile("./input")) { source =>
      val input = os.read(os.Path("/home/egor/bmstu/compilers/lab1.3/input"))
      //      println(input)
      val lexer = Lexer(input)
      val result = Lexer.getTokens(lexer)
      val tokens = result.filter(t => t.tag != DomainTag.Comment)
      val comments = result.filter(t => t.tag == DomainTag.Comment)
      println("=============================")
      tokens.foreach(println)
      println("=============================")
      comments.foreach(println)
    }
  }
}
```

# Тестирование

Входные данные

```


(*a*) (*b*) (*c*)
1 + 2
33 + 890 / 78 * 09
abacaba eee // <- error
(* comment (* nested comment *) *)
```

Вывод на `stdout`

```
ERROR: (6, 1)-(6, 8) : abacaba
ERROR: (6, 9)-(6, 12) : eee
ERROR: (6, 16)-(6, 18) : <-
ERROR: (6, 19)-(6, 24) : error
ERROR: (7, 4)-(7, 11) : comment
=============================
NUMERIC: (4, 1)-(4, 2) : 1
OPERATION: (4, 3)-(4, 3) : +
NUMERIC: (4, 5)-(4, 6) : 2
NUMERIC: (5, 1)-(5, 3) : 33
OPERATION: (5, 4)-(5, 4) : +
NUMERIC: (5, 6)-(5, 9) : 890
OPERATION: (5, 10)-(5, 10) : /
NUMERIC: (5, 12)-(5, 14) : 78
OPERATION: (5, 15)-(5, 15) : *
NUMERIC: (5, 17)-(5, 19) : 9
OPERATION: (6, 13)-(6, 13) : /
OPERATION: (6, 14)-(6, 14) : /
OPERATION: (7, 1)-(7, 1) : (
OPERATION: (7, 2)-(7, 2) : *
OPERATION: (7, 33)-(7, 33) : *
OPERATION: (7, 34)-(7, 34) : )
=============================
COMMENT: (3, 1)-(3, 5) : a
COMMENT: (3, 7)-(3, 11) : b
COMMENT: (3, 13)-(3, 17) : c
COMMENT: (7, 12)-(7, 31) :  nested comment 
```

# Вывод
Научился разрабатывать объектно-ориентированный лексический анализатор для числовых выражений с поддержкой
различных типов токенов: чисел, операций и комментариев. Лексический анализатор был разработан в чисто
функциональной парадигме (с погрешностью на ООП-подмножество scala). Единственным сложным моментом оказалось
распознавание комментариев (т.к. они НЕ могут быть вложенными), поэтому пришлось прописать витиеватый
алгоритм, чтобы лексер распознавал внешний(ие) комментарии как ошибку, а вложенный - как правильный
комментарий. Также в качестве оптимизации обнаружение и получение комментариев было объединено в одну
функциональность.