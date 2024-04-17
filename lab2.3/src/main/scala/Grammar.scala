object Grammar {
//  S -> K S | .
//  K -> L arrow R end.
//
//  L -> axiom n | n .
//
//  R -> F A T.
//  A -> eps A | n A | string A | .
//  T -> or F A T | .
//  F -> eps | n | string .

  val Axiom: String = "AXIOM"
  val Eps: String = "EPS"
  val End: String = "END"
  val Or: String = "OR"
  val Nterm: String = "NTERM"
  val Arrow: String = "ARROW"
  val Str: String = "STR"
  val Eof: String = "EOF"

  val S: String = "RULES"
  val K: String = "RULE"
  val L: String = "LEFT PART"
  val R: String = "RIGHT PART"
  val A: String = "TERMS"
  val T: String = "TERM or OR"
  val F: String = "TERM"

  val terminalSet: Set[String] = Set(Axiom, Eps, End, Or, Nterm, Arrow, Str, Eof)
  val nonTerminalSet: Set[String] = Set(S, K, L, R, A, T, F)

  val table: Map[(String, String), Vector[String]] = Map(
    ((S, Axiom), Vector(K, S)),
    ((S, Nterm), Vector(K, S)),
    ((S, Eof), Vector.empty[String]),
    ((K, Axiom), Vector(L, Arrow, R, End)),
    ((K, Nterm), Vector(L, Arrow, R, End)),
    ((L, Axiom), Vector(Axiom, Nterm)),
    ((L, Nterm), Vector(Nterm)),
    ((R, Nterm), Vector(F, A, T)),
    ((R, Eps), Vector(F, A, T)),
    ((R, Str), Vector(F, A, T)),
    ((F, Nterm), Vector(Nterm)),
    ((F, Eps), Vector(Eps)),
    ((F, Str), Vector(Str)),
    ((A, Nterm), Vector(Nterm, A)),
    ((A, Eps), Vector(Eps, A)),
    ((A, Str), Vector(Str, A)),
    ((A, End), Vector.empty[String]),
    ((A, Or), Vector.empty[String]),
    ((T, End), Vector.empty[String]),
    ((T, Or), Vector(Or, F, A, T))
  )


}

//trait GrammarEntity {
//  val name: String
//  def fromName(name: String): GrammarEntity = {
//    name match {
//      case "AXIOM" => Axiom
//      case "EPS" => Eps
//    }
//  }
//}
//trait Terminal extends GrammarEntity
//trait NonTerminal extends GrammarEntity
//
//case object Axiom extends Terminal {
//  override val name: String = "AXIOM"
//}
//case object Eps extends Terminal {
//  override val name: String = "EPS"
//}
//case object End extends Terminal {
//  override val name: String = "END"
//}
//case object Or extends Terminal {
//  override val name: String = "OR"
//}
//case object Nterm extends Terminal {
//  override val name: String = "NTERM"
//}
//case object Arrow extends Terminal {
//  override val name: String = "ARROW"
//}
//case object Str extends Terminal {
//  override val name: String = "STR"
//}
//case object Eof extends Terminal {
//  override val name: String = "EOF"
//}
//
//case object S extends NonTerminal {
//  override val name: String = "RULES"
//}
//case object K extends NonTerminal {
//  override val name: String = "RULE"
//}
//case object L extends NonTerminal {
//  override val name: String = "LEFT PART"
//}
//case object R extends NonTerminal {
//  override val name: String = "RIGHT PART"
//}
//case object A extends NonTerminal {
//  override val name: String = "TERMS"
//}
//case object T extends NonTerminal {
//  override val name: String = "TERM or OR"
//}
//case object F extends NonTerminal {
//  override val name: String = "TERM"
//}