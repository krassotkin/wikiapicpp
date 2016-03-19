#ifndef SearchItem_HPP
#define SearchItem_HPP
/*
 SearchItem.hpp represent a revision information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BSearchItem
https://www.mediawiki.org/wiki/API:SearchItems

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

class SearchItem {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

 
  string errJson;
  
  int ns=-1;
  long int size=-1;
  long int wordcount=-1;
  string title;
  string timestamp;
  string snippet;
  string titlesnippet;
  string redirecttitle;
  string redirectsnippet;
  string sectiontitle;
  string sectionsnippet;
  int isfilematch; 
  string categorysnippet;

  SearchItem() {}
  
  SearchItem(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  SearchItem(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   ns=-1;
   size=-1;
   wordcount=-1;
   timestamp="";
   snippet="";
   titlesnippet="";
   redirecttitle="";
   redirectsnippet="";
   sectiontitle="";
   sectionsnippet="";
   title="";
   isfilematch=-1; 
   categorysnippet="";
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   ns = json["ns"].int_value();
   title = json["title"].string_value();
   size = json["size"].int_value();
   wordcount = json["wordcount"].int_value();
   timestamp = json["timestamp"].string_value();
   snippet = json["snippet"].string_value();
   titlesnippet = json["titlesnippet"].string_value();
   redirecttitle = json["redirecttitle"].string_value();
   redirectsnippet = json["redirectsnippet"].string_value();
   sectiontitle = json["sectiontitle"].string_value();
   sectionsnippet = json["sectionsnippet"].string_value();
   isfilematch = json["isfilematch"].bool_value(); 
   categorysnippet = json["categorysnippet"].string_value();
  }
  
  string toJson() {
   return "{\"ns\":"+to_string(ns)+ ",\"title\":"+title+",\"snippet\":"+snippet+",\"size\":"+to_string(size)+",\"wordcount\":"+to_string(wordcount)+",\"timestamp\":"+timestamp+",\"titlesnippet\":"+titlesnippet+",\"redirecttitle\":"+redirecttitle+",\"redirectsnippet\":"+redirectsnippet+",\"sectiontitle\":"+sectiontitle+",\"sectionsnippet\":"+sectionsnippet+",\"isfilematch\":"+to_string(isfilematch)+",\"categorysnippet\":"+categorysnippet+"\"}";
  }

};

const string SearchItem::versionMajor = "201512290030";
const string SearchItem::versionMinor = "201512290030";

#endif // #ifndef SearchItem_HPP
 
