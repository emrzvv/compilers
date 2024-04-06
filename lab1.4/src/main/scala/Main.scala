import model.{Acceptable}

object Main {
  def main(): Unit = {
    println(Acceptable.any.chars.toVector.sorted)
  }
}
