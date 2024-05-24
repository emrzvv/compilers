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