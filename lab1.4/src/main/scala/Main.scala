import model.{Acceptable, Lexer}

object Main {
  def main(): Unit = {
    val input = os.read(os.Path("/home/egor/bmstu/compilers/lab1.4/input"))
    //      println(input)
    val lexer = Lexer(input)
    val result = Lexer.getTokens(lexer)
    println("=============================")
    result.foreach(println)
    println(Acceptable.any.chars.toVector.sorted)
  }
}
