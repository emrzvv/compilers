import scala.collection.mutable
import pprint._

import java.io.{File, FileOutputStream, PrintWriter}

object Main {
  def main(args: Array[String]): Unit = {
    val lexer = new Lexer("./input")
    val result = lexer.parse()
    result._1.foreach(println)
    println("------------")
    result._2.foreach(println)

    val parser = new Parser(result._1)
    val root = parser.parse()
    pprintln(x=root, height = 1000000)
    root.toGraphviz("parsed tree", "./output")
  }
}