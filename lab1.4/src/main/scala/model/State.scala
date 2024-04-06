package model

trait State {
  def name: String
}

case object Start extends State {
  override def name: String = "Start"
}
case object Space extends State {
  override def name: String = "Space"
}
case object Numeric extends State {
  override def name: String = "Numeric"
}
case object KeywordBrace extends State {
  override def name: String = "Keyword"
}
case object Keyword extends State {
  override def name: String = "Keyword"
}
case object StringRead extends State {

  override def name: String = "String read"
}
case object String extends State {
  override def name: String = "String"
}
case object EscapeRead extends State {
  override def name: String = "escape"
}
case object Escape extends State {
  override def name: String = "Escape"
}
case object Ident extends State {
  override def name: String = "Ident"
}
case object B_egin extends State {
  override def name: String = "b_egin"
}
case object Be_gin extends State {
  override def name: String = "be_gin"
}
case object Beg_in extends State {
  override def name: String = "beg_in"
}
case object Begi_n extends State {
  override def name: String = "begi_n"
}
case object E_nd extends State {
  override def name: String = "E_nd"
}
case object En_d extends State {
  override def name: String = "En_d"
}
