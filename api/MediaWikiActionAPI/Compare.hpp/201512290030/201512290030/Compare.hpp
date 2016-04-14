#ifndef COMPARE_HPP
#define COMPARE_HPP
/*
 Compare.hpp represent request and response to The MediaWiki action API for diff between 2 pages.

 Get the difference between 2 pages by titles, page ID, or revision number.

 A revision number, a page title, or a page ID for both "from" and "to" must be passed. 

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=compare

 Examples:

1)
 Request:
https://ru.wikinews.org/w/api.php?action=compare&fromrev=442524&torev=442553

 Response:
{
    "compare": {
        "fromrevid": 442524,
        "torevid": 442553,
        "*": "<...>"
    }
}

2)
 Request:
https://ru.wikinews.org/w/api.php?action=compare&fromtitle=Apple&totitle=Google

 Response:
{
    "compare": {
        "fromtitle": "Apple",
        "fromrevid": 75852,
        "totitle": "Google",
        "torevid": 115230,
        "*": "<...>"
    }
}

3)
 Request:
https://ru.wikinews.org/w/api.php?action=compare&fromid=15852&toid=18220

 Response:
{
    "compare": {
        "fromid": 15852,
        "fromrevid": 75852,
        "toid": 18220,
        "torevid": 115230,
        "*": "<...>"
    }
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"

class Compare : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  /* Request */
  long int fromid = -1;     /* First page ID to compare.  */
  long int fromrev = -1;    /* First revision to compare. */ 
  string fromtitle;         /* First title to compare. */
  long int toid = -1;       /* Second page ID to compare. */
  long int torev = -1;      /* Second revision to compare. */
  string totitle;           /* Second title to compare. */
  
  /* Response */
  string content;            /* Same that "*" in response. */
  long int fromid_res = -1;  /* First page ID to compare.  */
  long int fromrev_res = -1; /* First revision to compare. */ 
  string fromtitle_res;      /* First title to compare. */
  long int toid_res = -1;    /* Second page ID to compare. */
  long int torev_res = -1;   /* Second revision to compare. */
  string totitle_res;        /* Second title to compare. */

  void clearRequest() {
   fromid = -1;
   fromrev = -1;
   fromtitle.clear();  
   toid = -1;  
   torev = -1; 
   totitle.clear(); 
  }

  void clearResponse() {
   content.clear();         
   fromid_res = -1; 
   fromrev_res = -1;
   fromtitle_res.clear();          
   toid_res = -1; 
   torev_res = -1;
   totitle_res.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   auto compareJson = json["compare"].object_items();
   content = compareJson["*"].string_value();        
   fromid_res = compareJson["fromid"].number_value();  
   fromrev_res = compareJson["fromrevid"].number_value();  
   fromtitle_res = compareJson["fromtitle"].string_value();  
   toid_res = compareJson["toid"].number_value();   
   torev_res = compareJson["torevid"].number_value();  
   totitle_res = compareJson["totitle"].string_value();   
  }
  
  string toJson() {
   string tjs = (fromid_res > 0 ? string("\"fromid\":\"")+to_string(fromid_res)+"\"" : "");
   tjs += (fromrev_res > 0 ? string(tjs.length()>0?",":"") + "\"fromrev\":\""+to_string(fromrev_res)+"\"" : "");
   tjs += (fromtitle_res.length() > 0 ? string(tjs.length()>0?",":"") + "\"fromtitle\":\""+fromtitle_res+"\"" : "");
   tjs += (toid_res > 0 ? string(tjs.length()>0?",":"") + "\"toid\":\""+to_string(toid_res)+"\"" : "");
   tjs += (torev_res > 0 ? string(tjs.length()>0?",":"") + "\"torev\":\""+to_string(torev_res)+"\"" : "");
   tjs += (totitle_res.length() > 0 ? string(tjs.length()>0?",":"") + "\"totitle\":\""+totitle_res+"\"" : "");
   tjs += (tjs.length()>0 && content.length()>0 ? ", \"*\":\""+content+"\"" : "");
   return "{\"compare\":{"
           + tjs
           +"}}";
  }

};

const string Compare::versionMajor = "201512290030";
const string Compare::versionMinor = "201512290030";

#endif // #ifndef COMPARE_HPP
 
