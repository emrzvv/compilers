ThisBuild / version := "0.1.0-SNAPSHOT"

ThisBuild / scalaVersion := "2.13.13"

lazy val root = (project in file("."))
  .settings(
    name := "lab2.3"
  )

libraryDependencies += "org.scala-lang" %% "toolkit" % "0.2.1"
libraryDependencies += "com.lihaoyi" %% "pprint" % "0.9.0"