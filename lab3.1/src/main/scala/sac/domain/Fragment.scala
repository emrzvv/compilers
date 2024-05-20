package sac.domain

case class Fragment(start: Position, follow: Position) {
  override def toString: String = s"${start.toString}-${follow.toString}"
  def isEmpty: Boolean = start.isEmpty && follow.isEmpty
}

object Fragment {
  def empty(): Fragment = Fragment(Position.empty, Position.empty)
}