% Лабораторная работа № 2.3 «Синтаксический анализатор на основе
  предсказывающего анализа»
% 17 апреля 2024 г.
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

## Неформальное описание синтаксиса входного языка
В качестве входного языка выступает язык представления правил грамматики, лексика и синтаксис которого восстан
авливаются из примера в индивидуальном варианте.

1. Правила (S): 
    - `S -> K S | .`
    - Это правило описывает, что множество правил грамматики (обозначаемое S) состоит из одного правила (обозн
ачаемого K) и оставшихся правил (S), или может быть пустым (.).
2. Отдельное правило (K):
    - `K -> L arrow R end .`
    - Каждое правило состоит из левой части (L), стрелки (arrow), правой части (R) и завершается ключевым слов
ом end.
3. Левая часть правила (L):
    - `L -> axiom n | n .`
    - Левая часть правила может быть либо начальным символом грамматики (обозначается ключевым словом axiom, з
а которым следует нетерминальный символ n), либо просто нетерминальным символом n.
4. Правая часть правила (R):
    - `R -> F A T .`
    - Правая часть правила состоит из начального элемента (F), последовательности дополнительных элементов (A)
 и завершения альтернативных вариантов (T).
5. Дополнительные элементы (A):
    - `A -> eps A | n A | string A | .`
    - Дополнительные элементы могут быть либо пустым символом (eps), либо нетерминальным символом (n), либо те
рминалом (строкой, обозначенной string), после которых может следовать ещё один дополнительный элемент (A). В 
конце может быть пустым (.).
6. Альтернативные варианты (T):
    - `T -> or F A T | .`
    - Альтернативные варианты начинаются с ключевого слова or, за которым следует начальный элемент (F), допол
нительные элементы (A) и далее ещё один альтернативный вариант (T). В конце может быть пустым (.).
7. Начальные элементы (F):
    - `F -> eps | n | string .`
    - Начальные элементы могут быть либо пустым символом (eps), либо нетерминальным символом (n), либо термина
лом (строкой, обозначенной string).

## Лексическая структура
```
axiom = `axiom
eps = `epsilon
end = `end
or = `or
n = [A-Z][A-Z0-9]*
arrow = ->
string = ^\"[^\"]\"
comment = ^#[^\n]* 
```

## Грамматика языка
```
S -> K S | .
K -> L arrow R end.

L -> axiom n | n .

R -> F A T.
A -> eps A | n A | string A | .
T -> or F A T | .
F -> eps | n | string .
```

## Программная реализация
Grammar.scala
```scala
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

Lexer.scala
```scala
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
                lexemes = lexemes :+ Token(name, Fragment(Position(lineIdx, i - newIndex + 1), Position(lineId
x, i)), result.trim)
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

Parser.scala
```scala
import domain.{Fragment, Token}

import java.io.{File, FileOutputStream, PrintWriter}
import java.util.UUID
import scala.annotation.tailrec
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Parser(val lexemes: List[Token]) {
  import Grammar._

  def parse(): Node = {
    val _lexemes: ArrayBuffer[Token] = mutable.ArrayBuffer.from(lexemes :+ Token(Eof, Fragment.empty(), "eof")
)
    val root = Node(S)
    val stack = mutable.ArrayBuffer[Node](Node(Eof), root)

    var currentLexeme = _lexemes.head
    _lexemes.remove(0)
    var stop: Boolean = false

    while (!stop) {
      println("--------------")
      println(s"STACK: ${stack.map(_.value)}")
      val currentNode = stack(stack.size - 1)
      stack.remove(stack.size - 1)
      if (currentNode.value == Eof && currentLexeme.name == Eof) {
        stop = true
      } else {
        println(s"POP ${currentNode.value}")
        println(s"LEXEMES: ${_lexemes.map(_.value)}")

        if (terminalSet.contains(currentNode.value)) {
          if (currentNode.value == currentLexeme.name) {
            currentNode.value = currentLexeme.value
            println(s"--> READ ${currentLexeme}")
            currentLexeme = _lexemes.head
            _lexemes.remove(0)
          } else {
            println(s"ERROR: EXPECTED ${currentNode.value} FOUND ${currentLexeme.name}")
            stop = true
          }
        } else if (table.contains((currentNode.value, currentLexeme.name))) {
          val tableValue = table((currentNode.value, currentLexeme.name))
          val newNodes = mutable.ArrayBuffer.from(tableValue.map(v => Node(v)))
          println(s"PUTTING ${newNodes.reverse} IN STACK")
          if (newNodes.isEmpty) {
            currentNode.addChild(Node("NOTHING"))
          }
          newNodes.reverse.foreach { node =>
            currentNode.addChild(node)
            stack += node
          }
        } else {
          println("ERROR") // TODO: throw Exception
          stop = true
        }
      }
    }
    root
  }
}

case class Node(var value: String,
                children: mutable.ArrayBuffer[Node] = mutable.ArrayBuffer(),
                var position: Int = -1,
                uuid: UUID = UUID.randomUUID()) {
  def addChild(child: Node): Unit = {
    this.children += child
  }

  private def toGraphvizHelper(node: Node): String = {
    val updNodeValue = if (node.value.isQuoted) node.value.unQuot else node.value
    val currentDefinition = s"${node.uuid.toString.quoted} [label=\"${updNodeValue}\"];\n"
    val edges = node.children.map(child => s"${node.uuid.toString.quoted} -- ${child.uuid.toString.quoted}").m
kString("\n")
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
}

object Node {
  var index: Int = 1
}
```

Fragment.scala
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
Position.scala
```
package domain

case class Position(line: Int, pos: Int) {
  override def toString: String = s"($line, $pos)"
  def isEmpty: Boolean = line == -1 && pos == -1
  def equalTo(other: Position): Boolean = line == other.line && pos == other.pos
}

object Position {
  def apply(): Position = Position(1, 1)
  def empty: Position = Position(-1, -1)
}
```

Token.scala
```scala
package domain

case class Token(name: String, fragment: Fragment, value: String)
```
Main.scala
```scala
import scala.collection.mutable

object Main {
  def main(args: Array[String]): Unit = {
    val lexer = new Lexer("./input")
    val result = lexer.parse()
    result._1.foreach(println)
    println("------------")
    result._2.foreach(println)

    val parser = new Parser(result._1)
    val root = parser.parse()
    root.toGraphviz("parsed tree", "./output")
  }
}
```

# Тестирование

Входные данные

```
# ключевые слова
# начинаются с кавычки

F  -> "n" 'or "(" E ")" 'end
T  -> F T1 'end
T1 -> "*" F T1 'or 'epsilon 'end
'axiom E  -> T E1 'end
E1 -> "+" T E1 'or 'epsilon 'end
```

Вывод на `stdout`

```
Token(NTERM,(3, 1)-(3, 1),F)
Token(ARROW,(3, 4)-(3, 5),->)
Token(STR,(3, 7)-(3, 9),"n")
Token(OR,(3, 11)-(3, 13),'or)
Token(STR,(3, 15)-(3, 17),"(")
Token(NTERM,(3, 19)-(3, 19),E)
Token(STR,(3, 21)-(3, 23),")")
Token(END,(3, 25)-(3, 28),'end)
Token(NTERM,(4, 1)-(4, 1),T)
Token(ARROW,(4, 4)-(4, 5),->)
Token(NTERM,(4, 7)-(4, 7),F)
Token(NTERM,(4, 9)-(4, 10),T1)
Token(END,(4, 12)-(4, 15),'end)
Token(NTERM,(5, 1)-(5, 2),T1)
Token(ARROW,(5, 4)-(5, 5),->)
Token(STR,(5, 7)-(5, 9),"*")
Token(NTERM,(5, 11)-(5, 11),F)
Token(NTERM,(5, 13)-(5, 14),T1)
Token(OR,(5, 16)-(5, 18),'or)
Token(EPS,(5, 20)-(5, 27),'epsilon)
Token(END,(5, 29)-(5, 32),'end)
Token(AXIOM,(6, 1)-(6, 6),'axiom)
Token(NTERM,(6, 8)-(6, 8),E)
Token(ARROW,(6, 11)-(6, 12),->)
Token(NTERM,(6, 14)-(6, 14),T)
Token(NTERM,(6, 16)-(6, 17),E1)
Token(END,(6, 19)-(6, 22),'end)
Token(NTERM,(7, 1)-(7, 2),E1)
Token(ARROW,(7, 4)-(7, 5),->)
Token(STR,(7, 7)-(7, 9),"+")
Token(NTERM,(7, 11)-(7, 11),T)
Token(NTERM,(7, 13)-(7, 14),E1)
Token(OR,(7, 16)-(7, 18),'or)
Token(EPS,(7, 20)-(7, 27),'epsilon)
Token(END,(7, 29)-(7, 32),'end)
------------
Node(
  value = "S",
  children = ArrayBuffer(
    Node(
      value = "S",
      children = ArrayBuffer(
        Node(
          value = "S",
          children = ArrayBuffer(
            Node(
              value = "S",
              children = ArrayBuffer(
                Node(
                  value = "S",
                  children = ArrayBuffer(
                    Node(
                      value = "S",
                      children = ArrayBuffer(
                        Node(
                          value = "NOTHING",
                          children = ArrayBuffer(),
                          uuid = 0066ee2e-4530-4762-86c4-ef7ef17e0641
                        )
                      ),
                      uuid = 07e23e1f-2920-4766-95d1-97c0c40cc504
                    ),
                    Node(
                      value = "K",
                      children = ArrayBuffer(
                        Node(
                          value = "'end",
                          children = ArrayBuffer(),
                          uuid = 766b5922-460c-4ddc-b828-675a792be292
                        ),
                        Node(
                          value = "R",
                          children = ArrayBuffer(
                            Node(
                              value = "T",
                              children = ArrayBuffer(
                                Node(
                                  value = "T",
                                  children = ArrayBuffer(
                                    Node(
                                      value = "NOTHING",
                                      children = ArrayBuffer(),
                                      uuid = f06eacdf-a972-4cb8-a766-3bf822da2cf9
                                    )
                                  ),
                                  uuid = 577f3b45-551f-4e2d-ac60-289d1610e9da
                                ),
                                Node(
                                  value = "A",
                                  children = ArrayBuffer(
                                    Node(
                                      value = "NOTHING",
                                      children = ArrayBuffer(),
                                      uuid = 462d91b1-d008-47e6-8fb8-3cf1d824fc10
                                    )
                                  ),
                                  uuid = ae6585b0-3a8d-4968-a9d1-d3e35be38f32
                                ),
                                Node(
                                  value = "F",
                                  children = ArrayBuffer(
                                    Node(
                                      value = "'epsilon",
                                      children = ArrayBuffer(),
                                      uuid = 3ee07039-bbbb-4062-b6d1-24da15ebaef1
                                    )
                                  ),
                                  uuid = 27ab50ec-4475-4865-8941-a48bb00137f9
                                ),
                                Node(
                                  value = "'or",
                                  children = ArrayBuffer(),
                                  uuid = de596815-4368-46f1-8a0f-599603e72c48
                                )
                              ),
                              uuid = 55925513-3c58-4c29-a481-7d272a703c1c
                            ),
                            Node(
                              value = "A",
                              children = ArrayBuffer(
                                Node(
                                  value = "A",
                                  children = ArrayBuffer(
                                    Node(
                                      value = "A",
                                      children = ArrayBuffer(
                                        Node(
                                          value = "NOTHING",
                                          children = ArrayBuffer(),
                                          uuid = 591aab64-6580-49ca-a3fe-89773d136a7d
                                        )
                                      ),
                                      uuid = 5ad505e8-1b7e-4f78-9160-f254b716c337
                                    ),
                                    Node(
                                      value = "E1",
                                      children = ArrayBuffer(),
                                      uuid = 6a8a6c56-f7a7-48aa-aeed-8c5f597f80d3
                                    )
                                  ),
                                  uuid = b813e426-a4ee-4ca3-bdcf-297b98063499
                                ),
                                Node(
                                  value = "T",
                                  children = ArrayBuffer(),
                                  uuid = ccbf98a0-c3cb-43d6-a64c-843e62a7b2cc
                                )
                              ),
                              uuid = 12b39e83-7410-446c-97e8-7ffee4a021db
                            ),
                            Node(
                              value = "F",
                              children = ArrayBuffer(
                                Node(
                                  value = "\"+\"",
                                  children = ArrayBuffer(),
                                  uuid = 3c8585ba-204f-4c8e-8512-b783b68b530e
                                )
                              ),
                              uuid = cf852553-df38-4429-bbaa-e431d2e10051
                            )
                          ),
                          uuid = 17714432-242a-4aec-bf6b-844890bdae4a
                        ),
                        Node(
                          value = "->",
                          children = ArrayBuffer(),
                          uuid = 10f6b36b-f772-4983-b822-c87a2e3fdb12
                        ),
                        Node(
                          value = "L",
                          children = ArrayBuffer(
                            Node(
                              value = "E1",
                              children = ArrayBuffer(),
                              uuid = a4fabded-7851-47b2-bfcc-11d485327763
                            )
                          ),
                          uuid = 6dc2866d-649b-45b7-985a-c36ecc9a5e19
                        )
                      ),
                      uuid = 956f1192-4ed0-485b-ba7e-35272f21b405
                    )
                  ),
                  uuid = d70460d9-c5d4-4b99-868d-33c24588c56f
                ),
                Node(
                  value = "K",
                  children = ArrayBuffer(
                    Node(
                      value = "'end",
                      children = ArrayBuffer(),
                      uuid = c2663269-ab4e-4df5-8fa9-b3636005222e
                    ),
                    Node(
                      value = "R",
                      children = ArrayBuffer(
                        Node(
                          value = "T",
                          children = ArrayBuffer(
                            Node(
                              value = "NOTHING",
                              children = ArrayBuffer(),
                              uuid = 5c7289a7-bfe4-4954-ad99-fb454d64ef34
                            )
                          ),
                          uuid = f2857dcd-b297-408c-a396-b6e85cea214e
                        ),
                        Node(
                          value = "A",
                          children = ArrayBuffer(
                            Node(
                              value = "A",
                              children = ArrayBuffer(
                                Node(
                                  value = "NOTHING",
                                  children = ArrayBuffer(),
                                  uuid = 47ea5d76-e9c2-4993-8f6f-1380311d9d58
                                )
                              ),
                              uuid = 2f5edeb3-c7f6-4850-bdcf-ac14bf5fafa0
                            ),
                            Node(
                              value = "E1",
                              children = ArrayBuffer(),
                              uuid = 8fbf958c-d430-4f7b-89ff-9a3db8028805
                            )
                          ),
                          uuid = 7968ea6a-f17a-4c16-9f04-c69fde96c547
                        ),
                        Node(
                          value = "F",
                          children = ArrayBuffer(
                            Node(
                              value = "T",
                              children = ArrayBuffer(),
                              uuid = 83bf8672-0f9e-4b25-88a2-a8efef23e21f
                            )
                          ),
                          uuid = 0c446b48-de98-4db8-8b40-409b7b607d2c
                        )
                      ),
                      uuid = a36dab65-54ea-4108-9464-43f51280dff3
                    ),
                    Node(
                      value = "->",
                      children = ArrayBuffer(),
                      uuid = 1a504b49-6330-4e4a-8b8c-25c754f1a5e1
                    ),
                    Node(
                      value = "L",
                      children = ArrayBuffer(
                        Node(
                          value = "E",
                          children = ArrayBuffer(),
                          uuid = 1bdf345e-0047-45a9-8cff-96b3b6a1f067
                        ),
                        Node(
                          value = "'axiom",
                          children = ArrayBuffer(),
                          uuid = 1fb85a3b-840d-4187-9d2b-93343408331d
                        )
                      ),
                      uuid = 43f91391-7b84-4ddf-8f16-02635432c7e1
                    )
                  ),
                  uuid = 69d80026-0c5d-42dd-8ced-820a89ecba6a
                )
              ),
              uuid = ff0b34bb-f218-42ce-9bfd-e215308ad3f1
            ),
            Node(
              value = "K",
              children = ArrayBuffer(
                Node(
                  value = "'end",
                  children = ArrayBuffer(),
                  uuid = 79a56edb-5956-4b0d-a630-e9a00cd02244
                ),
                Node(
                  value = "R",
                  children = ArrayBuffer(
                    Node(
                      value = "T",
                      children = ArrayBuffer(
                        Node(
                          value = "T",
                          children = ArrayBuffer(
                            Node(
                              value = "NOTHING",
                              children = ArrayBuffer(),
                              uuid = 98942765-73a4-4ef3-9346-6e237cbd3111
                            )
                          ),
                          uuid = 7e2adb3c-bfad-49ff-a817-88e7ea374423
                        ),
                        Node(
                          value = "A",
                          children = ArrayBuffer(
                            Node(
                              value = "NOTHING",
                              children = ArrayBuffer(),
                              uuid = 0233b170-14a9-4c83-ace6-b464a136bd68
                            )
                          ),
                          uuid = 5d91a0ba-1b5f-4413-80e0-b08ebd62e2dc
                        ),
                        Node(
                          value = "F",
                          children = ArrayBuffer(
                            Node(
                              value = "'epsilon",
                              children = ArrayBuffer(),
                              uuid = 82f0503b-007b-4e6b-a95b-f916d12b7aaa
                            )
                          ),
                          uuid = 8c23c417-233e-4717-8abb-21d0d6ddc8bc
                        ),
                        Node(
                          value = "'or",
                          children = ArrayBuffer(),
                          uuid = 7b2d07ef-3c21-408f-8775-f0c0da25f05a
                        )
                      ),
                      uuid = e920861f-d715-4a37-a9b0-6439614cd954
                    ),
                    Node(
                      value = "A",
                      children = ArrayBuffer(
                        Node(
                          value = "A",
                          children = ArrayBuffer(
                            Node(
                              value = "A",
                              children = ArrayBuffer(
                                Node(
                                  value = "NOTHING",
                                  children = ArrayBuffer(),
                                  uuid = a025c8ef-e8d7-4fbf-b465-ac4864c0712d
                                )
                              ),
                              uuid = c216cb5e-84e6-4b0e-a103-d3ab76184697
                            ),
                            Node(
                              value = "T1",
                              children = ArrayBuffer(),
                              uuid = 4dc47aa1-be28-4113-8db4-58ba880abd70
                            )
                          ),
                          uuid = 18b52006-0fc6-42f5-871a-46fac831a1dc
                        ),
                        Node(
                          value = "F",
                          children = ArrayBuffer(),
                          uuid = 707e313d-9d35-4d1e-b202-a9261d297922
                        )
                      ),
                      uuid = 8c277fab-116b-4064-a100-624a25e46940
                    ),
                    Node(
                      value = "F",
                      children = ArrayBuffer(
                        Node(
                          value = "\"*\"",
                          children = ArrayBuffer(),
                          uuid = e426289e-26de-481e-b0cb-7916c23e57ea
                        )
                      ),
                      uuid = 27c7a6ae-da98-4ca2-9050-4576a157b7e0
                    )
                  ),
                  uuid = 31881644-a70f-4ef5-8f63-bb315ce64e74
                ),
                Node(
                  value = "->",
                  children = ArrayBuffer(),
                  uuid = 009f5bde-8880-44d8-90b7-38c8f4090c9b
                ),
                Node(
                  value = "L",
                  children = ArrayBuffer(
                    Node(
                      value = "T1",
                      children = ArrayBuffer(),
                      uuid = 3f15c85d-c371-42be-b813-10370c01a157
                    )
                  ),
                  uuid = 45064887-ae91-414f-b1ee-d822efa6bcdf
                )
              ),
              uuid = 66f3b13f-9370-46ea-b2a3-db926906774b
            )
          ),
          uuid = 7f448fa1-1df5-427c-b550-ff0ff1d98f7d
        ),
        Node(
          value = "K",
          children = ArrayBuffer(
            Node(
              value = "'end",
              children = ArrayBuffer(),
              uuid = 02814e77-e540-464e-888b-4d9dfe8f739a
            ),
            Node(
              value = "R",
              children = ArrayBuffer(
                Node(
                  value = "T",
                  children = ArrayBuffer(
                    Node(
                      value = "NOTHING",
                      children = ArrayBuffer(),
                      uuid = b7b0a99d-5ff4-4ca3-afad-4915be80cb5d
                    )
                  ),
                  uuid = 4bff6b75-2d9e-478a-86ee-70740fb3b300
                ),
                Node(
                  value = "A",
                  children = ArrayBuffer(
                    Node(
                      value = "A",
                      children = ArrayBuffer(
                        Node(
                          value = "NOTHING",
                          children = ArrayBuffer(),
                          uuid = d8900534-d14c-401a-b397-16c581bc88ad
                        )
                      ),
                      uuid = 90028569-13a9-48a1-b6c0-237860b3e657
                    ),
                    Node(
                      value = "T1",
                      children = ArrayBuffer(),
                      uuid = 91667733-25b2-44c8-980b-cce0e97c04b6
                    )
                  ),
                  uuid = 64a40c1e-d4df-4431-a6f5-d14dc5251514
                ),
                Node(
                  value = "F",
                  children = ArrayBuffer(
                    Node(
                      value = "F",
                      children = ArrayBuffer(),
                      uuid = f00c29c4-08db-4d35-a90d-ba5870359731
                    )
                  ),
                  uuid = 5a42b315-a7fe-4c51-85cf-23a684944a6c
                )
              ),
              uuid = c5f79398-9dbe-48e2-88df-3750ab9baa1f
            ),
            Node(
              value = "->",
              children = ArrayBuffer(),
              uuid = 014e632a-a360-4efb-91ea-0a1e267bb58f
            ),
            Node(
              value = "L",
              children = ArrayBuffer(
                Node(
                  value = "T",
                  children = ArrayBuffer(),
                  uuid = bce7cbc1-4c42-4d70-8ea7-cc55e9046597
                )
              ),
              uuid = 2a32af8f-fff7-4839-b9f7-beb05c7c7578
            )
          ),
          uuid = 615f8d2a-5898-4e86-804f-93feb5f8d3e9
        )
      ),
      uuid = 19597535-9e11-415d-ad3b-301f257b2290
    ),
    Node(
      value = "K",
      children = ArrayBuffer(
        Node(value = "'end", children = ArrayBuffer(), uuid = cc2cc45d-e240-4890-a980-13bc9c0220b2),
        Node(
          value = "R",
          children = ArrayBuffer(
            Node(
              value = "T",
              children = ArrayBuffer(
                Node(
                  value = "T",
                  children = ArrayBuffer(
                    Node(
                      value = "NOTHING",
                      children = ArrayBuffer(),
                      uuid = ebb74aaf-787f-47d1-8ff5-6a5860e6b014
                    )
                  ),
                  uuid = c0a6d8e3-68d5-4932-ba26-499d8b39dddf
                ),
                Node(
                  value = "A",
                  children = ArrayBuffer(
                    Node(
                      value = "A",
                      children = ArrayBuffer(
                        Node(
                          value = "A",
                          children = ArrayBuffer(
                            Node(
                              value = "NOTHING",
                              children = ArrayBuffer(),
                              uuid = 15df05de-086a-4479-97bd-d8629171f596
                            )
                          ),
                          uuid = 961f95e9-ae3f-44fc-8158-20ae5809adbd
                        ),
                        Node(
                          value = "\")\"",
                          children = ArrayBuffer(),
                          uuid = bb4a6363-135e-48a4-a953-1f5a260a0dcd
                        )
                      ),
                      uuid = 3d1a1a2f-2dd2-42cf-a803-de9c9bda467f
                    ),
                    Node(
                      value = "E",
                      children = ArrayBuffer(),
                      uuid = f8b75f92-e0ad-4c51-a0c7-d6f6a41ad6ef
                    )
                  ),
                  uuid = 03d847c1-87fe-4856-be49-84a31d5e4da7
                ),
                Node(
                  value = "F",
                  children = ArrayBuffer(
                    Node(
                      value = "\"(\"",
                      children = ArrayBuffer(),
                      uuid = 8432bd4c-245e-4df9-9b17-52b12544f8b4
                    )
                  ),
                  uuid = 72d09ffc-732d-46b8-ab67-323679a752af
                ),
                Node(
                  value = "'or",
                  children = ArrayBuffer(),
                  uuid = f078012b-28cc-4026-bcb9-b744f6d928e1
                )
              ),
              uuid = 20f49bae-82fc-4437-b351-2a0f8bd9aec1
            ),
            Node(
              value = "A",
              children = ArrayBuffer(
                Node(
                  value = "NOTHING",
                  children = ArrayBuffer(),
                  uuid = 0407ef54-0405-4f34-b656-75a7826998f9
                )
              ),
              uuid = c6d1668d-dec1-4abf-b2be-2ccbb2d89fc6
            ),
            Node(
              value = "F",
              children = ArrayBuffer(
                Node(
                  value = "\"n\"",
                  children = ArrayBuffer(),
                  uuid = 3e9c0515-d624-45cc-8473-825fa96c6ec3
                )
              ),
              uuid = 69e5cd1a-9b07-4525-bc63-d8ba89046565
            )
          ),
          uuid = 67a89546-6094-4657-98cd-06205fe7de41
        ),
        Node(value = "->", children = ArrayBuffer(), uuid = 38a841ad-44bc-4fb1-98b9-9b51a033de87),
        Node(
          value = "L",
          children = ArrayBuffer(
            Node(value = "F", children = ArrayBuffer(), uuid = 7edfd93c-e7de-4e99-acfb-ea98d6aa8e08)
          ),
          uuid = b94c7fcb-1c2f-423c-a56b-ee72fdfbaac1
        )
      ),
      uuid = c72c2e2b-dc48-4c3a-b0b6-45188f0b3fe0
    )
  ),
  uuid = 8f726ca2-29e5-4996-a1c9-a96d2bbaf301
)
```

# Вывод
В результате выполнения лабораторной работы были изучены и применены на практике:
1. алгоритм построения таблиц предсказывающего анализа (вручную)
2. алгоритм порождения дерева вывода

Также был использован лексический анализатор, реализованный
в одной из предыдущих лабораторных работ первого модуля.

Основная сложность в выполнении лабораторной работы заключалась в осознании
момента, что необходимо составлять грамматику к грамматике.