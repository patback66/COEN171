/*
* Matthew Koken <mkoken@scu.edu>
* COEN 171 HW4
* THIS PROJECT IS COMPILED AND RUN USING sbt.
*/
package maskoken.hw4

import scala.util.matching.Regex
import scala.io.Source
import org.json4s._
import org.json4s.native.JsonMethods._
import org.json4s.Formats
import scala.collection.mutable.ListBuffer

//3.3.0-11-gcade980

//regex: #([^\s|:|"|,]+) to grab hashtag from text
// parse for something like: {"hashtags":[{"text":"pisces","indices":[28,35]}], to get the hashtags
//\"hashtags\":.*?(\]\}\]\,\")

object Parser {
  var hashtags = collection.mutable.Map[String, Int]()
  var countTotalHashtags : Int = 0
  var countUniqueHashtags : Int =  0
  var highestUsedHashtag : String = ""
  var countHighestUsed : Int = 0
  implicit val format = DefaultFormats

  def findAndIncrement(key: String){
    countTotalHashtags+=1
    if(hashtags.contains(key)){ //already contained
      val uses = hashtags(key)+1
      hashtags += (key -> uses) //update uses

      //update tracking data
      if(uses > countHighestUsed) {
        countHighestUsed = uses
        highestUsedHashtag = key
      }
    } else { //new unique hashtag
      countUniqueHashtags+=1
      hashtags += (key -> 1)
      if( 1 > countHighestUsed){ //for the first hashtag
        highestUsedHashtag = key
        countHighestUsed = 1
      }
    }
  }

  def printMostUsed() {
    hashtags.keys.foreach{ i=>
      if(hashtags(i) == countHighestUsed)
        println("Most used: " + i)
    }
  }

  def main(args: Array[String]) {
    //val jsonName = "38.json"//the twitter json file to parse
    val source = scala.io.Source.fromFile("38.json")
    //val src = scala.util.parsing.json
    //list of maps
    //val lines = try source.getLines finally source.close()

    val tweetRegex = "\"id\":(.*),\"text\":\"(.*)\"".r
    val hashtagRegex = "\"hashtags\":.*?(/]/}/]/,\")".r //get the section with hashtags, then parse it for the tags

    //val twitterJson = parse(source.mkString)
    //println(twitterJson)

    for (line <- source.getLines()) {
      val json = parse(line)
      //println(compact(render(json \\ "hashtags")))
      //extract the nested hashtag json
      val hashtagJson = json \\ "hashtags"
      //extract the text portion of the hashtag json
      val extractedText = hashtagJson \ "text"

      //ignore values of None -> these didn't have hashtags
      if(extractedText != None && extractedText != JNothing){
        //if it's a string there's only one hashtag
        if(extractedText.isInstanceOf[org.json4s.JsonAST$JString]){
          val hashtag = extractedText.extract[String]
          //we have the hashtag, now check if already seen, evaluate the data
          findAndIncrement(hashtag)
        } else {
          //we have a list of hashtag strings
          val strs = extractedText.extract[List[String]]
          //iterate through all
          for(str <- strs){
            //we have the hashtag, now check if already seen, evaluate the data
            findAndIncrement(str)
          }
        }
      }
    }

    println("Total number of hashtags: " + countTotalHashtags)
    println("Total unique hashtags: " + countUniqueHashtags)
    println("Highest used hashtag:" + highestUsedHashtag)
    println("Number of uses: " + countHighestUsed)
    hashtags.keys.foreach{ i =>
                           print( "Hashtag = " + i )
                           println(", Uses = " + hashtags(i) )}
    printMostUsed()
  }
}
