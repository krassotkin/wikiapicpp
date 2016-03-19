#ifndef CategoryMember_HPP
#define CategoryMember_HPP
/*
 CategoryMembers.hpp represent a item of CategoryMemers.itmems.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategorymembers
https://www.mediawiki.org/wiki/API:Categorymembers

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

class CategoryMember {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

 
  string errJson;
  
  long int pageid = -1;
  long int ns = -1;
  string timestamp;
  string title;

  CategoryMember() {}
  
  CategoryMember(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  CategoryMember(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   pageid = -1;
   ns=-1;
   timestamp="";
   title="";
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
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
 
