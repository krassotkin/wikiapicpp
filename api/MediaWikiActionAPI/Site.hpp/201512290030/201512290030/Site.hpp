#ifndef SITE_HPP
#define SITE_HPP
/*
 Site.hpp represents Wikimedia site.

 Used in SetematrixLanguage.hpp/Sitematrix.hpp.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix

 Examples from Sitematrix.hpp response:
                {
                    "url": "https://ru.wikipedia.org",
                    "dbname": "ruwiki",
                    "code": "wiki",
                    "sitename": "\u0412\u0438\u043a\u0438\u043f\u0435\u0434\u0438\u044f"
                },
<...>
                {
                    "url": "https://ru.wikinews.org",
                    "dbname": "ruwikinews",
                    "code": "wikinews",
                    "sitename": "\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438"
                },
<...>

            {
                "url": "https://advisory.wikimedia.org",
                "dbname": "advisorywiki",
                "code": "advisory",
                "sitename": "Advisory Board",
                "closed": ""
            },
<...>

            {
                "url": "https://donate.wikimedia.org",
                "dbname": "donatewiki",
                "code": "donate",
                "sitename": "Donate",
                "fishbowl": ""
            },
<...>
            {
                "url": "https://wikimaniateam.wikimedia.org",
                "dbname": "wikimaniateamwiki",
                "code": "wikimaniateam",
                "sitename": "WikimaniaTeam",
                "private": ""
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

class Site : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Response
  int closed = -1;
  string code;
  string dbname;
  int fishbowl = -1;     /* Restricted write access, full read access. */
  int privateField = -1; /* Read and write restricted. */
  string sitename;
  string url;

  void clearRequest() {}

  void clearResponse() {
   closed = -1;
   code.clear();
   dbname.clear();
   fishbowl = -1;
   privateField = -1;
   sitename.clear();
   url.clear(); 
  }

  void clearServo() {}

  bool isClosed() {
   return (1 == closed);
  }
 
  bool isFishbowl() {
   return (1 == fishbowl);
  }

  bool isPrivate() {
   return (1 == privateField);
  }
  
  void fromJsonSub(const json11::Json& json) {
   code=json["code"].string_value();
   if(json.object_items().find("closed") != json.object_items().end()) closed = 1;
   dbname=json["dbname"].string_value();
   if(json.object_items().find("fishbowl") != json.object_items().end()) fishbowl = 1;
   if(json.object_items().find("private") != json.object_items().end()) privateField = 1;
   sitename=json["sitename"].string_value();
   url=json["url"].string_value();
  }
  
  string toJson() {
   return (string)"{"
           + (closed == 1 ? "\"closed\":\"\"," : "")
           + (code.length() > 0 ? "\"code\":\""+code+"\"," : "")
           + (dbname.length() > 0 ? "\"dbname\":\""+dbname+"\"," : "")
           + (fishbowl == 1 ? "\"fishbowl\":\"\"," : "")
           + (privateField == 1 ? "\"private\":\"\"," : "")
           + (sitename.length() > 0 ? "\"sitename\":\""+sitename+"\"," : "")
           + (url.length() > 0 ? "\"url\":\""+url+"\"" : "")
           + "}";
  }

};

const string Site::versionMajor = "201512290030";
const string Site::versionMinor = "201512290030";

#endif // #ifndef SITE_HPP
 
