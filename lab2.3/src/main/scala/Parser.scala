import domain.{Fragment, Token}

import java.io.{File, FileOutputStream, PrintWriter}
import java.util.UUID
import scala.annotation.tailrec
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Parser(val lexemes: List[Token]) {
  import Grammar._

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
          if (newNodes.isEmpty) {
            currentNode.addChild(Node("NOTHING"))
          }
          newNodes.reverse.foreach { node =>
            currentNode.addChild(node)
            stack += node
          }
        } else {
//          println("ERROR 2")
          stop = true
        }
      }
    }
    root
  }
}

case class Node(var value: String,
                children: mutable.ArrayBuffer[Node] = mutable.ArrayBuffer(),
                uuid: UUID = UUID.randomUUID()) {

  def addChild(child: Node): Unit = {
    this.children += child
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
}

object Node {
  var index: Int = 1
}