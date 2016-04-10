#ifndef CategoryMember_HPP
#define CategoryMember_HPP
/*
 CategoryMembers.hpp represent a item of CategoryMemers.itmems.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategorymembers
https://www.mediawiki.org/wiki/API:Categorymembers

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

class CategoryMember : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;
  
  // Response
  long int pageid = -1;
  long int ns = -1;
  string timestamp;
  string title;

/*
  CategoryMember() : MediaWikiActionAPIParameters() {}  
  CategoryMember(const string& jsonString) : MediaWikiActionAPIParameters(jsonString) {}
  CategoryMember(const json11::Json& json) : MediaWikiActionAPIParameters(json) {}
*/

  void clearRequest() {}

  void clearResponse() {
   ns=-1;
   pageid = -1;
   timestamp.clear();
   title.clear();
  }

  void clearServo() {}

  void fromJsonSub(const json11::Json& json) {
   pageid = json["pageid"].int_value();
   ns = json["ns"].int_value();
   timestamp = json["timestamp"].string_value();
   title = json["title"].string_value();
  }
  
  string toJson() {
   return "{\"pageid\":" + to_string(pageid) + ",\"ns\":" + to_string(ns) + ",\"title\":"+title+"\"}";
  }

};

const string CategoryMember::versionMajor = "201512290030";
const string CategoryMember::versionMinor = "201512290030";

#endif // #ifndef CategoryMember_HPP
 
