import scala.io.Source

object Main {
  def main(): Unit = {
    import util.Control._
    using(Source.fromFile("./input")) { source =>
      val input = os.read(os.Path("/home/egor/bmstu/compilers/lab1.3/input"))
//      println(input)
      val lexer = Lexer(input)
      val result = Lexer.getTokens(lexer)
      println("=============================")
      result.foreach(println)
    }
  }
}
