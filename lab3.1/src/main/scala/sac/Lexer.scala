package sac

import domain.{Fragment, Position, Token}

import scala.io.Source
import scala.util.matching.Regex

class Lexer(file_name: String) {
  private val lines: List[String] = Source.fromFile(file_name).getLines.toList

  private def skipSpaces(line: String, i: Int): (String, Int) = {
    val newLine = line.dropWhile(_.isWhitespace)
    (newLine, i + line.length - newLine.length)
  }

  private def skip(line: String, s: String): (String, Int) = {
    (line.drop(s.length), s.length)
  }

  def parse(): (List[Token], List[Fragment]) = {
    val variants: List[(String, Regex)] = List(
      ("AXIOM", """^\'axiom""".r),
      ("EPS", """^\'epsilon""".r),
      ("END", """^\'end""".r),
      ("OR", """^\'or""".r),
      ("NTERM", """^[A-Z][A-Z0-9]*""".r),
      ("ARROW", """^->""".r),
      ("STR", """^\"[^\"]\"""".r),
      ("comment", """^#[^\n]*""".r)
    )

    var lexemes: List[Token] = List()
    var errors: List[Fragment] = List()

    for ((line, lineIdx) <- lines.zipWithIndex) {
      var currentLine = line.trim
      var i = 0

      while (currentLine.nonEmpty) {
        if (currentLine.head.isWhitespace) {
          val (newLine, newIndex) = skipSpaces(currentLine, i)
          currentLine = newLine
          i = newIndex
        } else {
          variants.find { case (_, pattern) => pattern.findFirstIn(currentLine).nonEmpty } match {
            case Some((name, pattern)) =>
              val result = pattern.findFirstIn(currentLine).get
              val (newLine, newIndex) = skip(currentLine, result)
              currentLine = newLine
              i += newIndex
              if (name != "comment")
                lexemes = lexemes :+ Token(name, Fragment(Position(lineIdx, i - newIndex + 1), Position(lineIdx, i)), result.trim)
            case None =>
              currentLine = currentLine.drop(1)
              errors = errors :+ Fragment(Position(lineIdx, i), Position.empty)
          }
        }
      }
    }

    (lexemes, errors)
  }
}
