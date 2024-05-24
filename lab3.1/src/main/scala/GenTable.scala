object GenTable {
	val table: Map[(String, String), Vector[String]] = Map(
    (("T", "NUM"), Vector("F", "T2")),
    (("F", "NUM"), Vector("NUM")),
    (("S1", "-"), Vector("-")),
    (("S2", "*"), Vector("*")),
    (("S", "("), Vector("T", "E2")),
    (("E2", "+"), Vector("S1", "T", "E2")),
    (("E2", "-"), Vector("S1", "T", "E2")),
    (("T2", "EOF"), Vector()),
    (("S", "NUM"), Vector("T", "E2")),
    (("T2", "*"), Vector("S2", "F", "T2")),
    (("T2", "-"), Vector()),
    (("S2", "/"), Vector("/")),
    (("F", "("), Vector("(", "S", ")")),
    (("T2", "+"), Vector()),
    (("E2", "EOF"), Vector()),
    (("S1", "+"), Vector("+")),
    (("T", "("), Vector("F", "T2")),
    (("T2", "/"), Vector("S2", "F", "T2")),
    (("E2", ")"), Vector()),
    (("T2", ")"), Vector()),
	)
}