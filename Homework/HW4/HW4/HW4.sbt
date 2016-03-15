lazy val root = (project in file(".")).
  settings(
    name := "HW4",
    version := "1.0",
    scalaVersion := "2.11.7"
  )

val json4sNative = "org.json4s" %% "json4s-native" % "3.3.0"
libraryDependencies += json4sNative
