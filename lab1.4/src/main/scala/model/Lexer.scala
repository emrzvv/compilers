package model

import scala.annotation.tailrec

class Lexer(text: String,
            dfa: DFA,
            val currentPosition: Position) {

  private def isNewLineAt(position: Position): Boolean = {
    if (text.charAt(position.index) == '\r' && position.index < text.length)
      text.charAt(position.index + 1) == '\n'
    else
      text.charAt(position.index) == '\n'
  }

  private def isEOLAt(position: Position): Boolean = {
    text.charAt(position.index) == '\u0000'
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

  @tailrec
  private def transit(currentDFA: DFA = dfa, currentPosition: Position, startPosition: Position)
                     (isCompleted: Boolean, completedPosition: Position, completedState: State): Token = {
    val currentChar = text.charAt(currentPosition.index)
//    println(currentChar)
    val nextPosition = nextPositionFrom(currentPosition)

    val (status, updatedDFA) = currentDFA.next(currentChar)
    status match {
      case Left(_) =>
        if (isCompleted) {
          CommonToken(
            completedState.name,
            Fragment(startPosition, completedPosition),
            Some(text.substring(startPosition.index, completedPosition.index + 1)))
        } else {
          ErrorToken(
            "Error",
            Fragment(startPosition, currentPosition),
            Some(text.substring(startPosition.index, currentPosition.index + 1)))
        }
      case Right(true) =>
        transit(updatedDFA, nextPosition, startPosition)(isCompleted = true, currentPosition, updatedDFA.currentState) // final
      case Right(false) =>
        transit(updatedDFA, nextPosition, startPosition)(isCompleted, completedPosition, completedState)
    }
  }

  def nextToken(): NextTokenResult = {
    val startPosition: Position = currentPosition.copy()

    if (isEOLAt(currentPosition)) {
      NextTokenResult(EndToken(), this)
    } else {
      val token = transit(DFA.start(), startPosition, startPosition)(isCompleted = false, Position.empty, Trap)
      NextTokenResult(token, new Lexer(text, DFA.start(), nextPositionFrom(token.fragment.follow)))
    }
  }
}

object Lexer {
  def apply(input: String): Lexer = {
    new Lexer(input + '\u0000', DFA.start(), Position())
  }

  def getTokens(lexer: Lexer): Vector[Token] = {
    @tailrec
    def loop(currentLexer: Lexer)(acc: Vector[Token] = Vector.empty): Vector[Token] = {
      val result = currentLexer.nextToken()
//      println(result.token)
//      println(result.lexer.currentPosition)
      result.token match {
        case EndToken(_, _, _) => acc
        case ct@CommonToken(_, _, _ ) =>
           loop(result.lexer)(acc :+ ct)
        case ErrorToken(name, fragment, value) =>
          println(s"ERROR: $fragment : $value")
          loop(result.lexer)(acc)
      }
    }

    loop(lexer)()
  }
}

trait Token {
  def name: String
  def fragment: Fragment
  def value: Option[String]
}
case class CommonToken(name: String, fragment: Fragment, value: Option[String] = None) extends Token
case class ErrorToken(name: String, fragment: Fragment, value: Option[String] = None) extends Token
case class EndToken(name: String = "End", fragment: Fragment = Fragment.empty(), value: Option[String] = None) extends Token
case class NextTokenResult(token: Token, lexer: Lexer)