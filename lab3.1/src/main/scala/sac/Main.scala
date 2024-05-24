
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