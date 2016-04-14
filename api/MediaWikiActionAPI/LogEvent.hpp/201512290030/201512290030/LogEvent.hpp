#ifndef LOGEVENT_HPP
#define LOGEVENT_HPP
/*
 LogEvent.hpp represent a LogEvent information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://www.mediawiki.org/wiki/API:Logevents
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Blogevents

 Example of a response:
               {
                "logid": 350248,
                "ns": 2,
                "title": "\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Aminought",
                "pageid": 0,
                "logpage": 0,
                "params": {
                    "userid": 24284
                },
                "type": "newusers",
                "action": "autocreate",
                "user": "Aminought",
                "timestamp": "2016-02-14T02:58:10Z",
                "comment": ""
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
#include "LogEventParams.hpp"
#include "MediaWikiActionAPIParameters.hpp"

class LogEvent : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;
  
  long int logid=-1;
  long int ns=-1;
  string title;
  long int pageid=-1;
  long int logpage=-1;
  //vector<LogEventParams> logEventParams;
  /*long int userid=-1;*/
  long int first=-1;
  long int second=-1;
  long int third=-1;
  long int curid=-1;
  long int previd=-1;
  string resauto;
  string olduser;
  string newuser;
  long int edits=-1;
  string type;
  string action;
  string user;
  long int userid=-1;
  string timestamp;
  string comment;
  string parsedcomment;
  vector<string> tags;

  void clearRequest() {
   logid=-1;
   ns=-1;
   title.clear();
   pageid=-1;
   logpage=-1;
   //logEventParams.clear();
   /*userid=-1;*/
   first=-1;
   second=-1;
   third=-1;
   curid=-1;
   previd=-1;
   resauto.clear();
   olduser.clear();
   newuser.clear();
   edits=-1;
   type.clear();
   action.clear();
   user.clear();
   userid=-1;
   timestamp.clear();
   comment.clear();
   parsedcomment.clear();
   tags.clear();
  }

  void clearResponse() {
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   logid = json["logid"].int_value();
   ns = json["ns"].int_value();
   title = json["title"].string_value();
   pageid = json["pageid"].int_value();
   logpage = json["logpage"].int_value();
   auto jsonParams = json["params"].object_items();
   userid = jsonParams["userid"].int_value();
   first = jsonParams["first"].int_value();
   second = jsonParams["second"].int_value();
   third = jsonParams["third"].int_value();
   curid = jsonParams["curid"].int_value();
   previd = jsonParams["previd"].int_value();
   resauto = jsonParams["auto"].string_value();
   olduser = jsonParams["olduser"].string_value();
   newuser = jsonParams["newuser"].string_value();
   edits = jsonParams["edits"].int_value(); 
   type = json["type"].string_value();
   action = json["action"].string_value();
   user = json["user"].string_value();
   userid = json["userid"].int_value();
   timestamp = json["timestamp"].string_value();
   comment = json["comment"].string_value();
   parsedcomment = json["parsedcomment"].string_value();
   auto tagsJson = json["tags"].array_items();
   for(auto t : tagsJson) tags.push_back(t.string_value());   
  }

  string toJson() {
   string tagsString;
   for(string t : tags) tagsString = (tagsString.length() == 0 ? "" : ",") + t;
   tagsString = "["+tagsString+"]"; 
   /*string paramsString;
   for(string p : logEventParams) paramsString = (paramsString.length() == 0 ? "" : ",") + p;
   paramsString = "["+paramsString+"]";*/
   return "{\"logid\":"+to_string(logid)+ ",\"ns\":"+to_string(ns)+",\"title\":"+title+ ",\"pageid\":"+to_string(pageid)+",\"logpage\":"+to_string(logpage)+",\"params\": {" + ",\"userid\":"+to_string(userid)+ ",\"first\":"+to_string(first)+",\"second\":"+to_string(second)+ ",\"third\":"+to_string(third)+",\"curid\":"+to_string(curid)+",\"previd\":"+to_string(previd)+",\"resauto\":"+resauto+",\"olduser\":"+olduser+",\"newuser\":"+newuser+",\"edits\":"+ "}"+to_string(edits)+"}"+",\"type\":"+type+",\"action\":"+action+",\"user\":"+user+",\"userid\":"+to_string(userid)+",\"timestamp\":"+timestamp+",\"comment\":"+comment+",\"tags\":"+tagsString+"\"}";
  }

};

const string LogEvent::versionMajor = "201512290030";
const string LogEvent::versionMinor = "201512290030";

#endif // #ifndef LOGEVENT_HPP
 
