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
