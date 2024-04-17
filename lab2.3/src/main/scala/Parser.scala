import domain.{Fragment, Token}

import java.util.UUID
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Parser(val lexemes: Vector[Token]) {
  import Grammar._

  def parse(): Node = {
    val _lexemes: ArrayBuffer[Token] = mutable.ArrayBuffer.from(lexemes :+ Token(Eof, Fragment.empty(), "eof"))
    val root = Node(S)
    val stack = mutable.ArrayBuffer[Node](Node(Eof), root)

    var currentLexeme = _lexemes.head
    _lexemes.remove(0)
    var stop: Boolean = false
    while (!stop) {
      print("--------------")
      print(stack.map(_.value))
      val currentNode = stack.last
      stack.remove(stack.length - 1)

      if (currentNode.value == Eof && _lexemes.headOption.exists(_.name == Eof)) {
        stop = true
      } else {
        println(s"POPED ${currentNode.value} ${currentNode.uuid}")
        println(s"LEXEMES: ${_lexemes}")

        if (terminalSet.contains(currentNode.value)) {
          if (currentNode.value == currentLexeme.name) {
            currentNode.value = currentLexeme.value // TODO: replace " with \"
            println(s"-> READED ${currentLexeme}")
            currentLexeme = _lexemes.head
            _lexemes.remove(0)
          } else {
            println("ERROR 1")
            stop = true
          }
        } else if (table.contains((currentNode.value, currentLexeme.name))) {
          val tableValue = table((currentNode.value, currentLexeme.name))
          val newNodes = mutable.ArrayBuffer.from(tableValue.map(Node(_)))
          if (newNodes.isEmpty) {
            currentNode.addChild(Node("NOTHING"))
          }
          newNodes.foreach { node =>
            currentNode.addChild(node)
            stack += node
          }
        } else {
          println("ERROR 2")
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

  def toDot()
}