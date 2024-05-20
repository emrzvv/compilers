package sac.domain

import sac.domain.Node.{eof, eps}

import scala.annotation.tailrec
import scala.collection.mutable

case class Rule(left: Node, right: List[List[Node]], isAxiom: Boolean)

object Rule {
  @tailrec
  def getRules(root: Node, acc: List[Rule] = List.empty): List[Rule] = {
    if (root.children.isEmpty) acc.reverse // TODO: ???
    else if (root.children.length != 2) throw new RuntimeException()
    else {
      val ruleNode = root.children(0)
      val rulesNode =  root.children(1)
      getRules(rulesNode, getRule(ruleNode) +: acc)
    }
  }

  def getRule(root: Node): Rule =
    if (root.children.length != 4) throw new RuntimeException()
    else {
      val (left, isAxiom) = getLeft(root.children(0))
      val right = getRight(root.children(2))
      Rule(left, right.map(_.filterNot(_.value == "'epsilon")), isAxiom)
    }

  def getLeft(root: Node): (Node, Boolean) =
    if (root.children.length == 1) (root.children(0), false)
    else (root.children(1), true)

  def getRight(root: Node, shift: Int = 0): List[List[Node]] = {
    if (shift == 1 && root.children.isEmpty) List.empty
    val (f, a, t) = (root.children(0 + shift), root.children(1 + shift), root.children(2 + shift))
    val first = f.children(0) +: getTerms(a)
    val other = if (shift == 0) {
      getRight(t, 1)
    } else {
      getRight(t, 0)
    }
    first +: other
  }

  @tailrec
  def getTerms(root: Node, acc: List[Node] = List.empty): List[Node] = {
    if (root.children.isEmpty) acc.reverse
    else getTerms(root.children(1), root.children(0) +: acc)
  }
}

object RulesProcessor {
  val first: mutable.Map[Node, mutable.Set[Node]] = mutable.Map()
  val follow: mutable.Map[Node, mutable.Set[Node]] = mutable.Map()

  val bucks = "EOF"

  def getAxiom(rules: List[Rule]): Node = {
    val axioms = rules.filter(_.isAxiom).map(_.left).toSet
    if (axioms.isEmpty) throw new RuntimeException("не найдена аксиома")
    else if (axioms.size > 1) throw new RuntimeException("должна быть ровно одна аксиома")
    else axioms.head
  }

  def checkUnproductive(rules: List[Rule]): Unit = {
    val left = rules.map(_.left).toSet
    val right =
      rules
        .flatMap(_.right.flatten)
        .toSet
        .filter(_.isNonTerminal)

    if (right.diff(left).nonEmpty) throw new RuntimeException("невыводящий терминал")
  }

  def getFirst(rules: List[Rule]) = {
    val lefts = rules.map(_.left).toSet

    lefts.foreach(x => first(x) = mutable.Set())

    rules.foreach { rule =>
      val left = rule.left
      val right = rule.right
      right.foreach { r =>
        first(left) = first(left) union getFirstSeq(r.toSet)
      }
    }

    var changed = true
    while (changed) {
//      val old = first.mapValues(_.clone()).toMap
      val old = first
      rules.foreach { rule =>
        val left = rule.left
        val rights = rule.right
        rights.foreach {r =>
          first(left) = first(left) union (getFirstSeq(r.toSet) - eps)
        }
      }
      changed = old != first
    }
  }

  def getFirstSeq(right: Set[Node]): mutable.Set[Node]  = {
    if (right.isEmpty) mutable.Set(eps)
    else {
      val head = right.head
      val rest = right.tail

      if (!head.isNonTerminal) mutable.Set(head)
      else if (!first(head).contains(eps)) first(head)
      else (first(head) - eps) union getFirstSeq(rest)
    }
  }

  def getFollow(rules: List[Rule], axiom: Node): Unit = {
    val left = rules.map(_.left).toSet
    left.foreach { l =>
      follow(l) = mutable.Set()
    }

    follow(axiom) = mutable.Set(eof)

    rules.foreach { rule =>
      
    }
  }
}