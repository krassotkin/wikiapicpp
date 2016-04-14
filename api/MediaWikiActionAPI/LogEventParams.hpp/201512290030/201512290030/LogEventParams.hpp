#ifndef LOGEVENTPARAMS_HPP
#define LOGEVENTPARAMS_HPP
/*
 LogEventParams.hpp represent a params from LogEvent params.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://www.mediawiki.org/wiki/API:Logevents
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Blogevents

 "params": {
                    "0": "427583",
                    "1": "0",
                    "2": "20160214022348"
                },

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

class LogEventParams : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;
  
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

  void clearRequest() {}

  void clearResponse() {
   userid=-1;
   first=-1;
   second=-1;
   third=-1;
   curid=-1;
   previd=-1;
   resauto.clear();
   olduser.clear();
   newuser.clear();
   edits=-1;
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
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
 
