package model

case class Acceptable(chars: Set[Char]) {
  def ++(other: Acceptable): Acceptable = Acceptable(chars ++ other.chars)
  def +(chr: Char): Acceptable = Acceptable(chars + chr)
  def --(other: Acceptable): Acceptable = Acceptable(chars -- other.chars)
  def -(chr: Char): Acceptable = Acceptable(chars - chr)
}

object Acceptable {
  val spaces: Acceptable = Acceptable(Set('\n', '\t', ' '))
  val digits: Acceptable = Acceptable('0'.toInt.to('9'.toInt).map(_.toChar).toSet)
  val lowerLetters: Acceptable = Acceptable('a'.toInt.to('z'.toInt).map(_.toChar).toSet)
  val upperLetters: Acceptable = Acceptable('A'.toInt.to('Z'.toInt).map(_.toChar).toSet)
  val any: Acceptable = Acceptable(32.to(126).map(_.toChar).toSet)
  val digitsAndLetters: Acceptable = digits ++ lowerLetters ++ upperLetters
  val letters: Acceptable = lowerLetters ++ upperLetters
}