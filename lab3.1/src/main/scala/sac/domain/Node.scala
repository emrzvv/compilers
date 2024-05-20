package sac.domain

import java.io.{File, FileOutputStream, PrintWriter}
import java.util.UUID
import scala.collection.mutable

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
}

object Node {
  var index: Int = 1
  val eps = Node(value = "eps$")
  val eof = Node(value = "EOF")
}
