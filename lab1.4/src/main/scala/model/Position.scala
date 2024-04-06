package model

case class Position(line: Int, pos: Int, index: Int) {
  override def toString: String = s"($line, $pos)"
  def isEmpty: Boolean = line == -1 && pos == -1 && index == -1
  def equalTo(other: Position): Boolean = line == other.line && pos == other.pos && index == other.index
}

object Position {
  def apply(): Position = Position(1, 1, 0)
  def empty: Position = Position(-1, -1, -1)
}