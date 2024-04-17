import domain.DomainTag

import scala.io.Source

object Main {
  def main(args: Array[String]): Unit = {
    import util.Control._
    using(Source.fromFile("./input")) { source =>
      val input = os.read(os.Path("/home/egor/bmstu/compilers/lab1.3/input"))
      //      println(input)
      val lexer = Lexer(input)
      val result = Lexer.getTokens(lexer)
      val tokens = result.filter(t => t.tag != DomainTag.Comment)
      val comments = result.filter(t => t.tag == DomainTag.Comment)
      println("=============================")
      tokens.foreach(println)
      println("=============================")
      comments.foreach(println)
    }
  }
}