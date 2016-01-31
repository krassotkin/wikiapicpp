#ifndef CategoryMember_HPP
#define CategoryMember_HPP
/*
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
   title="";
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   pageid = json["pageid"].int_value();
   ns = json["ns"].int_value();
   title = json["title"].string_value();
  }
  
  string toJson() {
   return "{\"pageid\":" + to_string(pageid) + ",\"ns\":" + to_string(ns) + ",\"title\":"+title+"\"}";
  }

};

const string CategoryMember::versionMajor = "201512290030";
const string CategoryMember::versionMinor = "201512290030";

#endif // #ifndef CategoryMember_HPP
 
