package sac

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

  val S: String = "S"
  val K: String = "K"
  val L: String = "L"
  val R: String = "R"
  val A: String = "A"
  val T: String = "T"
  val F: String = "F"

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