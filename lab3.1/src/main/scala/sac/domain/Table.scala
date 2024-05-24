package sac.domain

import java.io.{File, PrintWriter}
import scala.collection.mutable

class Table(nterms: Set[String], terms: Set[String]) {
  val error: Vector[String] = Vector("ERROR")
  val table: mutable.Map[(String, String), Vector[String]] = mutable.Map()

  // Initialize the table with error values
  def init(): Unit = {
//    println(nterms)
//    println(terms)
    for (n <- nterms; t <- terms) {
      println(s"$n, $t")
      table((n, t)) = error
    }
//    println(table.keySet)
  }

  // Add a sequence to the table
  def add(n: String, t: String, seq: Vector[String]): Unit = {
    println(s"$n, $t, $seq")
    if (table((n, t)) == error) {
      table((n, t)) = seq
    } else {
      throw new RuntimeException(s"conflict ($n, $t)")
    }
  }

  // Write the table to a file
  def toFile(filename: String): Unit = {
    val writer = new PrintWriter(new File(filename))

    writer.write("object GenTable {\n\tval table: Map[(String, String), Vector[String]] = Map(\n")
    for (((n, t), valSeq) <- table if valSeq != error) {
      val nQuoted = "\"" + n + "\""
      val tQuoted = "\"" + t.replace("\"", "") + "\""
      val formattedValSeq = valSeq.map(x => "\"" + x.replace("\"", "") + "\"").mkString(", ")

      writer.write(s"    (($nQuoted, $tQuoted), Vector($formattedValSeq)),\n")
    }
    writer.write("\t)\n}")
    writer.close()
  }

  def toImmutable = ???
}
