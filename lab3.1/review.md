% Лабораторная работа № 3.1 «Самоприменимый генератор компиляторов
  на основе предсказывающего анализа»
% 22 мая 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является изучение алгоритма построения таблиц предсказывающего анализатора.

# Индивидуальный вариант
```
# ключевые слова
# начинаются с кавычки

F  -> "n" 'or "(" E ")" 'end
T  -> F T1 'end
T1 -> "*" F T1 'or 'epsilon 'end
'axiom E  -> T E1 'end
E1 -> "+" T E1 'or 'epsilon 'end
```
# Реализация

`Main.scala`:
```scala

import sac.Grammar.{table, terminalSet}
import sac.domain.{Rule, RulesProcessor}
import sac.{Lexer, Parser}


object Main {
  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      throw new RuntimeException()
    }
    val variants = List(
      ("AXIOM", """^\'axiom""".r),
      ("EPS", """^\'epsilon""".r),
      ("END", """^\'end""".r),
      ("OR", """^\'or""".r),
      ("NTERM", """^[A-Z][A-Z0-9]*""".r),
      ("ARROW", """^->""".r),
      ("STR", """^\"[^\"]*\"""".r),
      ("comment", """^#[^\n]*""".r)
    )
    val lexer = new Lexer(args(0), variants)
    val result = lexer.parse()
    result._1.foreach(println)
    println("------------")
    result._2.foreach(println)

    val parser = new Parser(result._1, terminalSet = terminalSet, table = table)
    val root = parser.parse()
    root.toGraphviz("parsed tree", "./graph")

    val rules = Rule.getRules(root)
    println("-------------")
    rules.foreach(r => println(s"${r.left.value} -> ${r.right.map(a => a.map(_.value).mkString(", ")).mkString(" | ")}"))
    println("-------------")
    RulesProcessor.buildTable(rules.map(_.simple), args(1))
  }
}
```
`Calculator.scala`:
```scala
import sac.domain.Node
import sac.{Lexer, Parser}

object Calculator {
  def main(args: Array[String]): Unit = {
    if (args.length != 1) throw new RuntimeException()
    val variants = List(
      ("(", """^\(""".r),
      (")", """^\)""".r),
      ("+", """^\+""".r),
      ("-", """^\-""".r),
      ("*", """^\*""".r),
      ("/", """^\/""".r),
      ("NUM", """^[0-9]+""".r),
    )
    val lexer = new Lexer(args(0), variants)
    val result = lexer.parse()
//    result._1.foreach(println)
    println("------------")
//    result._2.foreach(println)

    val terminalSet = Set("(", ")", "+", "-", "*", "/", "NUM")
    val parser = new Parser(result._1, terminalSet, GenTable.table)
    val root = parser.parse()
    root.toGraphviz("parsed tree", "./calc_graph")

    println(evaluate(root)._2)
  }

  def evaluate(root: Node): (Option[Char], Float) = {
    if (root.value == "S") {
      val left = evaluate(root.children(0))._2
      val (signOpt, right) = evaluate(root.children(1))
      if (signOpt.contains('+')) (None, left + right)
      else (None, left - right)
    } else if (root.value == "E2") {
      if (root.children.isEmpty) (Some('+'), 0)
      else {
        val signLeft =  root.children(0).children(0).value
        var left = evaluate(root.children(1))._2
        if (signLeft.contains('-')) {
          left *= -1
        }
        val (signRight, right) = evaluate(root.children(2))
        if (signRight.contains('+')) (Some('+'), left + right)
        else (Some('+'), left - right)
      }
    } else if (root.value == "T") {
      val left = evaluate(root.children(0))._2
      val (signOpt, right) = evaluate(root.children(1))
      if (signOpt.contains('*')) (None, left * right)
      else (None, left / right)
    } else if (root.value == "T2") {
      if (root.children.isEmpty) (Some('*'), 1)
      else {
        val signLeft =  root.children(0).children(0).value
        var left = evaluate(root.children(1))._2
        if (signLeft.contains('/')) {
          left  = 1 / left
        }
        val (signRight, right) = evaluate(root.children(2))
        if (signRight.contains('*')) (Some('*'), left * right)
        else (Some('*'), left / right)
      }
    } else if (root.value == "F") {
      if (root.children.length == 1) {
        (None, root.children(0).value.toFloat)
      } else {
        evaluate(root.children(1))
      }
    } else throw new RuntimeException("unexpected value")
  }
}

```
`Grammar.scala`:
```scala
package sac

object Grammar {
//  S -> K S | .
//  K -> L arrow R end.
//
//  L -> axiom n | n .
//
//  R -> F A T.
//  A -> eps A | n A | string A | .
//  T -> or F A T | .
//  F -> eps | n | string .

  val Axiom: String = "AXIOM"
  val Eps: String = "EPS"
  val End: String = "END"
  val Or: String = "OR"
  val Nterm: String = "NTERM"
  val Arrow: String = "ARROW"
  val Str: String = "STR"
  val Eof: String = "EOF"

  val S: String = "S"
  val K: String = "K"
  val L: String = "L"
  val R: String = "R"
  val A: String = "A"
  val T: String = "T"
  val F: String = "F"

  val terminalSet: Set[String] = Set(Axiom, Eps, End, Or, Nterm, Arrow, Str, Eof)
  val nonTerminalSet: Set[String] = Set(S, K, L, R, A, T, F)

  val table: Map[(String, String), Vector[String]] = Map(
    ((S, Axiom), Vector(K, S)),
    ((S, Nterm), Vector(K, S)),
    ((S, Eof), Vector.empty[String]),
    ((K, Axiom), Vector(L, Arrow, R, End)),
    ((K, Nterm), Vector(L, Arrow, R, End)),
    ((L, Axiom), Vector(Axiom, Nterm)),
    ((L, Nterm), Vector(Nterm)),
    ((R, Nterm), Vector(F, A, T)),
    ((R, Eps), Vector(F, A, T)),
    ((R, Str), Vector(F, A, T)),
    ((F, Nterm), Vector(Nterm)),
    ((F, Eps), Vector(Eps)),
    ((F, Str), Vector(Str)),
    ((A, Nterm), Vector(Nterm, A)),
    ((A, Eps), Vector(Eps, A)),
    ((A, Str), Vector(Str, A)),
    ((A, End), Vector.empty[String]),
    ((A, Or), Vector.empty[String]),
    ((T, End), Vector.empty[String]),
    ((T, Or), Vector(Or, F, A, T))
  )
}
```
`Lexer.scala`:
```scala
package sac

import domain.{Fragment, Position, Token}

import scala.io.Source
import scala.util.matching.Regex

class Lexer(file_name: String, variants: List[(String, Regex)]) {
  private val lines: List[String] = Source.fromFile(file_name).getLines.toList

  private def skipSpaces(line: String, i: Int): (String, Int) = {
    val newLine = line.dropWhile(_.isWhitespace)
    (newLine, i + line.length - newLine.length)
  }

  private def skip(line: String, s: String): (String, Int) = {
    (line.drop(s.length), s.length)
  }

  def parse(): (List[Token], List[Fragment]) = {

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

```

`Parser.scala`:
```scala
package sac

import domain.{Fragment, Node, Token}
import sac.Grammar.{Eof, S}

import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Parser(val lexemes: List[Token],
             val terminalSet: Set[String],
             val table: Map[(String, String), Vector[String]]) {

  def parse(): Node = {
    val _lexemes: ArrayBuffer[Token] = mutable.ArrayBuffer.from(lexemes :+ Token(Eof, Fragment.empty(), "eof"))
    val root = Node(S)
    val stack = mutable.ArrayBuffer[Node](Node(Eof), root)

    var currentLexeme = _lexemes.head
    _lexemes.remove(0)
    var stop: Boolean = false

    while (!stop) {
//      println("--------------")
//      println(s"STACK: ${stack.map(_.value)}")
      val currentNode = stack(stack.size - 1)
      stack.remove(stack.size - 1)
      if (currentNode.value == Eof && currentLexeme.name == Eof) {
        stop = true
      } else {
//        println(s"POP ${currentNode.value}")
//        println(s"LEXEMES: ${_lexemes.map(_.value)}")

        if (terminalSet.contains(currentNode.value)) {
          if (currentNode.value == currentLexeme.name) {
            currentNode.value = currentLexeme.value
//            println(s"--> READ ${currentLexeme}")
            currentLexeme = _lexemes.head
            _lexemes.remove(0)
          } else {
//            println(s"ERROR: EXPECTED ${currentNode.value} FOUND ${currentLexeme.name}")
            stop = true
          }
        } else if (table.contains((currentNode.value, currentLexeme.name))) {
          val tableValue = table((currentNode.value, currentLexeme.name))
          val newNodes = mutable.ArrayBuffer.from(tableValue.map(v => Node(v)))
//          println(s"PUTTING ${newNodes.reverse} IN STACK")
//          if (newNodes.isEmpty) {
//            currentNode.addChild(Node("NOTHING"))
//          }
          newNodes.reverse.foreach { node =>
            currentNode.addChild(node)
            stack += node
          }
        } else {
//          println(s"${currentNode.value}, ${lexemes.head}")
//          println(table.keys)
//          println(s"NO SUCH VALUE IN TABLE: (${currentNode.value}, ${lexemes.head})")
          stop = true
        }
      }
    }
    root
  }
}
```
`Node.scala`:
```scala
package sac.domain

import java.io.{File, FileOutputStream, PrintWriter}
import java.util.UUID
import scala.collection.mutable

case class Node(var value: String,
                children: mutable.ArrayBuffer[Node] = mutable.ArrayBuffer(),
                var position: Int = -1,
                uuid: UUID = UUID.randomUUID()) {
  def addChild(child: Node): Unit = {
    this.children.prepend(child)
  }

  private def toGraphvizHelper(node: Node): String = {
    val updNodeValue = if (node.value.isQuoted) node.value.unQuot else node.value
    val currentDefinition = s"${node.uuid.toString.quoted} [label=\"${updNodeValue}\"];\n"
    val edges = node.children.map(child => s"${node.uuid.toString.quoted} -- ${child.uuid.toString.quoted}").mkString("\n")
    currentDefinition + edges + "\n" + node.children.map(child => toGraphvizHelper(child)).mkString("\n")
  }

  def toGraphviz(expression: String, output: String): Unit = {
    val pw = new PrintWriter(new FileOutputStream(new File(output)))
    val result = toGraphvizHelper(this)
    pw.write(
      s"""
         |graph \"\"
         |{
         |  fontname="Helvetica,Arial,sans-serif"
         |  node [fontname="Helvetica,Arial,sans-serif"]
         |  edge [fontname="Helvetica,Arial,sans-serif"]
         |  label="${expression}"
         |  ${result}
         |}
         |""".stripMargin)
    pw.close()
  }

  implicit class StringOps(value: String) {
    def quoted: String = s"\"$value\""
    def isQuoted: Boolean = value.isEmpty || value.charAt(0) == '"' && value.charAt(value.length - 1) == '"'
    def unQuot: String = value.substring(1, value.length - 1)
  }

  lazy val isNonTerminal: Boolean = {
    val v: Char = value.headOption.getOrElse('@')
    'A' <= v && v <= 'Z'
  }

  def debug(): String = {
    s"${value}, [ ${uuid} ], ${children.map(_.value)}"
  }
}

object Node {
  var index: Int = 1
  val eps = "eps$"
  val eof = "EOF"
}
```
`Table.scala`:
```scala
package sac.domain

import java.io.{File, PrintWriter}
import scala.collection.mutable

class Table(nterms: Set[String], terms: Set[String]) {
  val error: Vector[String] = Vector("ERROR")
  val table: mutable.Map[(String, String), Vector[String]] = mutable.Map()

  // Initialize the table with error values
  def init(): Unit = {
//    println(nterms)
//    println(terms)
    for (n <- nterms; t <- terms) {
      println(s"$n, $t")
      table((n, t)) = error
    }
//    println(table.keySet)
  }

  // Add a sequence to the table
  def add(n: String, t: String, seq: Vector[String]): Unit = {
    println(s"$n, $t, $seq")
    if (table((n, t)) == error) {
      table((n, t)) = seq
    } else {
      throw new RuntimeException(s"conflict ($n, $t)")
    }
  }

  // Write the table to a file
  def toFile(filename: String): Unit = {
    val writer = new PrintWriter(new File(filename))

    writer.write("object GenTable {\n\tval table: Map[(String, String), Vector[String]] = Map(\n")
    for (((n, t), valSeq) <- table if valSeq != error) {
      val nQuoted = "\"" + n + "\""
      val tQuoted = "\"" + t.replace("\"", "") + "\""
      val formattedValSeq = valSeq.map(x => "\"" + x.replace("\"", "") + "\"").mkString(", ")

      writer.write(s"    (($nQuoted, $tQuoted), Vector($formattedValSeq)),\n")
    }
    writer.write("\t)\n}")
    writer.close()
  }

  def toImmutable = ???
}
```
# Тестирование

Входные данные

```
# грамматика калькулятора

'axiom S -> T E2 'end
E2 -> S1 T E2 'or 'epsilon 'end
T -> F T2 'end
T2 -> S2 F T2 'or 'epsilon 'end
F -> "NUM" 'or "(" S ")" 'end
S1 -> "+" 'or "-" 'end
S2 -> "*" 'or "/" 'end
```

`GenTable.scala`:
```scala
object GenTable {
	val table: Map[(String, String), Vector[String]] = Map(
    (("T", "NUM"), Vector("F", "T2")),
    (("F", "NUM"), Vector("NUM")),
    (("S1", "-"), Vector("-")),
    (("S2", "*"), Vector("*")),
    (("S", "("), Vector("T", "E2")),
    (("E2", "+"), Vector("S1", "T", "E2")),
    (("E2", "-"), Vector("S1", "T", "E2")),
    (("T2", "EOF"), Vector()),
    (("S", "NUM"), Vector("T", "E2")),
    (("T2", "*"), Vector("S2", "F", "T2")),
    (("T2", "-"), Vector()),
    (("S2", "/"), Vector("/")),
    (("F", "("), Vector("(", "S", ")")),
    (("T2", "+"), Vector()),
    (("E2", "EOF"), Vector()),
    (("S1", "+"), Vector("+")),
    (("T", "("), Vector("F", "T2")),
    (("T2", "/"), Vector("S2", "F", "T2")),
    (("E2", ")"), Vector()),
    (("T2", ")"), Vector()),
	)
}
```
Входное выражение для калькулятора:
```
10 * (5 + 4 - 3 + 1)
```
Вывод на `stdout`:
```
70
```
# Вывод
В результате выполнения лабораторной работы реализовал алгоритм построения таблиц предсказывающего разбора.
Генератор способен автоматически создавать таблицы для любой заданной грамматики в нотации варианта.

Генератор был протестирован на т.н. "калькуляторе", который использует таблицу, сгенерированную по грамматике калькулятора.
Самым сложным в лабораторной работе было осознать последовательность действий и сделать всё правильно.