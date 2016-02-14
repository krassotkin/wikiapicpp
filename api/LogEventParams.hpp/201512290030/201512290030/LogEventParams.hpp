#ifndef LOGEVENTPARAMS_HPP
#define LOGEVENTPARAMS_HPP
/*
 LogEventParams.hpp represent a params from LogEvent params.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 "params": {
                    "0": "427583",
                    "1": "0",
                    "2": "20160214022348"
                },

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

class LogEventParams {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

 
  string errJson;
  
  long int userid=-1;
  long int first=-1;
  long int second=-1;
  long int third=-1;
  long int curid=-1;
  long int previd=-1;
  string resauto;
  string olduser;
  string newuser;
  long int edits=-1;

  LogEventParams() {}
  
  LogEventParams(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  LogEventParams(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   userid=-1;
   first=-1;
   second=-1;
   third=-1;
   curid=-1;
   previd=-1;
   resauto="";
   olduser="";
   newuser="";
   edits=-1;
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   userid = json["userid"].int_value();
   first = json["first"].int_value();
   second = json["second"].int_value();
   third = json["third"].int_value();
   curid = json["curid"].int_value();
   previd = json["previd"].int_value();
   resauto = json["auto"].string_value();
   olduser = json["olduser"].string_value();
   newuser = json["newuser"].string_value();
   edits = json["edits"].int_value();  
  }
  
  string toJson() {
   return "{\"userid\":"+to_string(userid)+ ",\"first\":"+to_string(first)+",\"second\":"+to_string(second)+ ",\"third\":"+to_string(third)+",\"curid\":"+to_string(curid)+",\"previd\":"+to_string(previd)+",\"resauto\":"+resauto+",\"olduser\":"+olduser+",\"newuser\":"+newuser+",\"edits\":"+to_string(edits)+"\"}";
  }

};

const string LogEventParams::versionMajor = "201512290030";
const string LogEventParams::versionMinor = "201512290030";

#endif // #ifndef LOGEVENTPARAMS_HPP
 
