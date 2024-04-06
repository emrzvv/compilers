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
    println(s"ERROR: ${Fragment(position, endPosition)} : ${text.substring(position.index, endPosition.index)}")
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
          CommentToken(commentFragment, text.substring(commentFragment.start.index + 2, commentFragment.follow.index - 1)),
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
