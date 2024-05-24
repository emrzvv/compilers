package sac.domain

import sac.domain.Node.{eof, eps}
import sac.domain.Rule.StringOps

import scala.annotation.tailrec
import scala.collection.mutable

case class Rule(left: Node, right: List[List[Node]], isAxiom: Boolean)
case class RuleSimple(left: String, right: List[List[String]], isAxiom: Boolean)


object Rule {
  implicit class RuleOps(val rule: Rule) {
    def simple: RuleSimple =
      RuleSimple(rule.left.value, rule.right.map(_.map(_.value)), isAxiom = rule.isAxiom)
  }

  implicit class StringOps(val value: String) {
    def isNonTerminal: Boolean =
      value.headOption.exists(_.isUpper)
  }

  def getRules(root: Node, acc: List[Rule] = List.empty): List[Rule] = {
    if (root.children.isEmpty) List.empty
    else if (root.children.length != 2) throw new RuntimeException(root.debug())
    else {
      val ruleNode = root.children(0)
      val rulesNode = root.children(1)
      val rule = getRule(root.children(0))
      getRule(ruleNode) +: getRules(rulesNode)
    }
  }

  def getRule(root: Node): Rule =
    if (root.children.length != 4) throw new RuntimeException(root.debug())
    else {
      val (left, isAxiom) = getLeft(root.children(0))
      val right = getRight(root.children(2))
      Rule(left, right.map(_.filterNot(_.value == "'epsilon")), isAxiom)
    }

  def getLeft(root: Node): (Node, Boolean) =
    if (root.children.length == 1) (root.children(0), false)
    else (root.children(1), true)

  def getRight(root: Node): List[List[Node]] = {
    val (f, a, t) = (root.children(0), root.children(1), root.children(2))
    val alt1 = f.children(0) +: getTerms(a)
    val other = getRight2(t)
    alt1 +: other
  }

  def getRight2(root: Node): List[List[Node]] = {
    if (root.children.isEmpty) List.empty
    else {
      val (f, a, t) = (root.children(1), root.children(2), root.children(3))
      val alt1 = f.children(0) +: getTerms(a)
      val other = getRight2(t)
      alt1 +: other
    }
  }

  @tailrec
  def getTerms(root: Node, acc: List[Node] = List.empty): List[Node] = {
    if (root.children.isEmpty) acc.reverse
    else getTerms(root.children(1), root.children(0) +: acc)
  }
}

object RulesProcessor {
  val first: mutable.Map[String, mutable.Set[String]] = mutable.Map()
  val follow: mutable.Map[String, mutable.Set[String]] = mutable.Map()

  def getAxiom(rules: List[RuleSimple]): String = {
    val axioms = rules.filter(_.isAxiom).map(_.left).toSet
    if (axioms.isEmpty) throw new RuntimeException("не найдена аксиома")
    else if (axioms.size > 1) throw new RuntimeException("должна быть ровно одна аксиома")
    else axioms.head
  }

  def checkUnproductive(rules: List[RuleSimple]): Unit = {
    val left = rules.map(_.left).toSet
    val right =
      rules
        .flatMap(_.right.flatten)
        .toSet
        .filter(_.isNonTerminal)
    println(s"${left.map(_.value)}")
    println(s"${right.map(_.value)}")
    if (right.map(_.value).diff(left.map(_.value)).nonEmpty) throw new RuntimeException(s"невыводящий терминал: ${right.diff(left).map(_.value)}")
  }

  def getFirst(rules: List[RuleSimple]) = {
    val lefts = rules.map(_.left).toSet

    lefts.foreach(x => first(x) = mutable.Set())

    rules.foreach{ rule =>
      val left = rule.left
      val rights = rule.right
      rights.foreach { right =>
        first(left) = first(left) union getFirstSeq(right)
      }
    }

    var changed = true
    while (changed) {
      println("COUNTING FIRST")
//      val old = first.view.mapValues(_.clone()).toMap // TODO: simple .clone()?
      val old = first.map { case (k, v) => (k, v.clone()) }
      rules.foreach { rule =>
        val left = rule.left
        val rights = rule.right
        rights.foreach { right =>
          first(left) = first(left) union (getFirstSeq(right) - eps)
        }
      }
//      println("==========")
//      old.foreach { case (k, v) => println(s"$k -> ${v}")}
//      println("----------")
//      first.foreach { case (k, v) => println(s"$k -> ${v}")}
//      println("==========")
      changed = (old.toSet diff first.toSet).nonEmpty
//      println(changed)
    }
  }

  def getFirstSeq(right: List[String]): mutable.Set[String]  = {
    if (right.isEmpty) mutable.Set(eps)
    else {
      val head = right.head
      val rest = right.tail

      if (!head.isNonTerminal) mutable.Set(head)
      else if (!first(head).contains(eps)) first(head)
      else (first(head) - eps) union getFirstSeq(rest)
    }
  }

  def getFollow(rules: List[RuleSimple], axiom: String): Unit = {
    val left = rules.map(_.left).toSet
    left.foreach { l =>
      follow(l) = mutable.Set()
    }

    follow(axiom) = mutable.Set(eof)

    rules.foreach { rule =>
      val rights = rule.right
      rights.foreach { right =>
        for ((x, i) <- right.zipWithIndex) {
          if (x.isNonTerminal) {
            val v = right.drop(i + 1)
            val f = getFirstSeq(v).filterNot(_ == eps)
            follow(x) = follow(x) ++ f
          }
        }
      }
    }

    // println(follow)

    var changed = true
    while (changed) {
      println("COUNTING FOLLOW")
      val old = follow.map { case (k, v) => (k, v.clone()) }
      rules.foreach { rule =>
        val x = rule.left
        rule.right.foreach { right =>
          for ((y, i) <- right.zipWithIndex) {
            if (y.isNonTerminal) {
              if (getFirstSeq(right.drop(i + 1)).contains(eps)) {
                follow(y) = follow(y) ++ follow(x)
              }
            }
          }
        }
      }
      println("==========")
      old.foreach { case (k, v) => println(s"$k -> ${v}")}
      println("----------")
      follow.foreach { case (k, v) => println(s"$k -> ${v}")}
      println("==========")
      changed = (old.toSet diff follow.toSet).nonEmpty
//      println(old.toSet diff follow.toSet)
    }
  }

  def buildTable(rules: List[RuleSimple], src: String): Table = {
    val axiom = getAxiom(rules)
    checkUnproductive(rules)
    getFirst(rules)
    getFollow(rules, axiom)

    val table = buildTableHelper(rules)
    table.toFile(src)
    table
  }

  def buildTableHelper(rules: List[RuleSimple]): Table = {
    val lefts = rules.map(_.left).toSet
    val rights = rules
      .flatMap(_.right.flatten)
      .toSet

    println(s"lefts ${lefts}")
    println(s"rights ${rights}")
    val nonTerminals = lefts union rights.filter(_.isNonTerminal)
    val terminals = rights diff nonTerminals
    val table = new Table(nonTerminals, terminals + eof)
    table.init()
    rules.foreach { rule =>
      val x = rule.left
      rule.right.foreach { right =>
        (getFirstSeq(right) - eps).foreach { a =>
          table.add(x.value, a.value, right.map(_.value).toVector)
        }
        if (getFirstSeq(right).contains(eps)) {
          follow(x).foreach { b =>
            table.add(x.value, b.value, right.map(_.value).toVector)
          }
        }
      }
    }

    table
  }
}