#ifndef CATEGORY_HPP
#define CATEGORY_HPP
/*
 Category.hpp represent a revision information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BCategoriesItem
https://www.mediawiki.org/wiki/API:CategoriesItems

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

class Category {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

 
  string errJson;
  
  long int ns = -1;
  string title;

  Category() {}
  
  Category(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Category(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   ns=-1;
   title="";
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   ns = json["ns"].int_value();
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
   return "{\"ns\":"+to_string(ns)+ ",\"title\":"+title+"\"}";
  }

};

const string Category::versionMajor = "201512290030";
const string Category::versionMinor = "201512290030";

#endif // #ifndef CATEGORY_HPP
 
