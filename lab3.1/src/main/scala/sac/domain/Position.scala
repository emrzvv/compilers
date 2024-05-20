package sac.domain

case class Position(line: Int, pos: Int) {
  override def toString: String = s"($line, $pos)"
  def isEmpty: Boolean = line == -1 && pos == -1
  def equalTo(other: Position): Boolean = line == other.line && pos == other.pos
}

object Position {
  def apply(): Position = Position(1, 1)
  def empty: Position = Position(-1, -1)
}