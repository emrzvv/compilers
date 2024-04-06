package domain

import domain.DomainTag.Tag

trait Token{
  def tag: Tag
  def fragment: Fragment
}

case class NumericToken(fragment: Fragment, value: Long) extends Token {
  override val tag: Tag = DomainTag.Numeric

  override def toString: String = s"NUMERIC: $fragment : $value"
}
case class OperationToken(fragment: Fragment, value: Char) extends Token{
  override def tag: Tag = DomainTag.Operation

  override def toString: String = s"OPERATION: $fragment : $value"
}
case class CommentToken(fragment: Fragment, value: String) extends Token {
  override def tag: Tag = DomainTag.Comment

  override def toString: String = s"COMMENT: $fragment : $value"
}
case class EndToken(fragment: Fragment, value: String = "\u0000") extends Token {
  override def tag: Tag = DomainTag.EOF
}
case class Error(fragment: Fragment = Fragment.empty()) extends Token {

  override def tag: Tag = DomainTag.Error
}
object OperationToken {
  val values: Set[Char] = Set('+', '-', '*', '/', '(', ')')

  implicit class OperationOps(chr: Char) {
    def isOperation: Boolean = values.contains(chr)
  }
}