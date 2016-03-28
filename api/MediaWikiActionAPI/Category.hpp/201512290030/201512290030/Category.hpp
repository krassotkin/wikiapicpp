#ifndef CATEGORY_HPP
#define CATEGORY_HPP
/*
 Category.hpp represent a category information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategories
https://www.mediawiki.org/wiki/API:Categories

 Example of a response:
                    {
                        "ns": 14,
                        "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\u0418\u0441\u0441\u043b\u0435\u0434\u043e\u0432\u0430\u043d\u0438\u044f",
                        "sortkey": "3d43433b434f4d085b045ce0b40a94ff5d4523035c5a34baff5d4503045c940a03045cba8e0ab4c0dea4940ae003045c240a9494ff5d2f035c3403045c1803045cbab4342494348e03045ca4f834945a180aff5d3f035cc0baff5d4503045c1803040f0e141a045cc0ff5d2f035cba030901450d018f7e8f301800",
                        "sortkeyprefix": "",
                        "timestamp": "2016-02-05T08:06:59Z"
                    }

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"

class Category : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;
  
  // Response
  long int ns = -1;
  string sortkey;
  string sortkeyprefix;
  string timestamp;
  string title;

  Category() : MediaWikiActionAPIParameters() {}  
  Category(const string& jsonString) : MediaWikiActionAPIParameters(jsonString) {}  
  Category(const json11::Json& json) : MediaWikiActionAPIParameters(json) {}

  void clearRequest() {}

  void clearResponse() {
   ns=-1;
   sortkey.clear();
   sortkeyprefix.clear();
   timestamp.clear();
   title.clear();
  }

  void clearServo() {}
  
  void fromJson(const json11::Json& json) {
   ns = json["ns"].int_value();
   sortkey = json["sortkey"].string_value();
   sortkeyprefix = json["sortkeyprefix"].string_value();
   timestamp = json["timestamp"].string_value();
   title = json["title"].string_value();
  }

  string getTitleClear() {
   string res;
   bool f = false;
   for(char c : title)
    if(!f && c==':') f=true;
    else if(f) res+=c;
   return res;
  }
  
  string toJson() {
   return "{\"ns\":"+to_string(ns)+ ",\"title\":"+title+ ",\"sortkey\":"+sortkey+ ",\"sortkeyprefix\":"+sortkeyprefix+ ",\"timestamp\":"+timestamp+"\"}";
  }

};

const string Category::versionMajor = "201512290030";
const string Category::versionMinor = "201512290030";

#endif // #ifndef CATEGORY_HPP
 
