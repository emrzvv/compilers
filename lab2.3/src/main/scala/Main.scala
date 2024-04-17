import parser.Parser

object Main {
  def main(args: Array[String]): Unit = {
    val lexer = new Lexer("./input")
    val result = lexer.parse()
    result._1.foreach(println)
    println("------------")
    result._2.foreach(println)

    val parser = new Parser(result._1.toVector)
    val root = parser.parse()

  }
}