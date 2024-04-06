package domain

object DomainTag extends Enumeration {
  type Tag = Value
  val Numeric, Operation, Comment, EOF, Error = Value
}
