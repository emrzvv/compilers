package model

class DFA(currentState: State,
          val startState: State,
          val finalStates: Vector[State],
          val table: Map[State, Vector[(Acceptable, State)]]) {
  def next(symbol: Char): (Either[Unit, Boolean], DFA) = {
    table(currentState).find(_._1.chars.contains(symbol)) match {
      case Some(dest) => (Right(finalStates.contains(dest._2)), new DFA(dest._2, startState, finalStates, table))
      case None => (Left(()), this)
    }
  }
}

object DFA {
  def start(): DFA = new DFA(Start, Start, finalStates, table)

  val finalStates: Vector[State] = Vector(Space, Numeric, KeywordBrace, Keyword, Ident, String, Escape)
  val table: Map[State, Vector[(Acceptable, State)]] = Map(
    (Start,
      Vector(
        (Acceptable.spaces, Space),
        (Acceptable.digits, Numeric),
        (Acceptable(Set('{', '}')), KeywordBrace),
        (Acceptable(Set('\\')), EscapeRead),
        (Acceptable(Set('b')), B_egin),
        (Acceptable(Set('e')), E_nd),
        (Acceptable(Set('$')), StringRead),
        (Acceptable.letters - 'b' - 'e', Ident)
      )
    ),
    (Space,
      Vector(
        (Acceptable.spaces, Space)
      )
    ),
    (Numeric,
      Vector(
        (Acceptable.digits, Numeric)
      )
    ),
    (EscapeRead,
      Vector(
        (Acceptable.any, Escape)
      )
    ),
    (StringRead,
      Vector(
        (Acceptable.any, StringRead),
        (Acceptable(Set('$')), String)
      )
    ),
    (B_egin,
      Vector(
        (Acceptable.digitsAndLetters - 'e', Ident),
        (Acceptable(Set('e')), Be_gin)
      )
    ),
    (Be_gin,
      Vector(
        (Acceptable.digitsAndLetters - 'g', Ident),
        (Acceptable(Set('g')), Beg_in)
      )
    ),
    (Beg_in,
      Vector(
        (Acceptable.digitsAndLetters - 'i', Ident),
        (Acceptable(Set('i')), Begi_n)
      )
    ),
    (Begi_n,
      Vector(
        (Acceptable.digitsAndLetters - 'n', Ident),
        (Acceptable(Set('n')), Keyword)
      )
    ),
    (E_nd,
      Vector(
        (Acceptable.digitsAndLetters - 'n', Ident),
        (Acceptable(Set('n')), En_d)
      )
    ),
    (En_d,
      Vector(
        (Acceptable.digitsAndLetters - 'd', Ident),
        (Acceptable(Set('d')), Keyword)
      )
    ),
    (Keyword,
      Vector(
        (Acceptable.digitsAndLetters, Ident)
      )
    ),
    (Ident,
      Vector(
        (Acceptable.digitsAndLetters, Ident)
      )
    )
  )
}