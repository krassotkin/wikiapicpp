#ifndef SITEMATRIXLANGUAGE_HPP
#define SITEMATRIXLANGUAGE_HPP
/*
 SitematrixLanguage.hpp aggregates Wikimedia sites (Sites.hpp) like Sitematrix.hpp response do it.

 Used in Sitematrix.hpp.

 Examples:

        "218": {
            "code": "ru",
            "name": "\u0440\u0443\u0441\u0441\u043a\u0438\u0439",
            "site": [
                {
                    "url": "https://ru.wikipedia.org",
                    "dbname": "ruwiki",
                    "code": "wiki",
                    "sitename": "\u0412\u0438\u043a\u0438\u043f\u0435\u0434\u0438\u044f"
                },
                {
                    "url": "https://ru.wiktionary.org",
                    "dbname": "ruwiktionary",
                    "code": "wiktionary",
                    "sitename": "\u0412\u0438\u043a\u0438\u0441\u043b\u043e\u0432\u0430\u0440\u044c"
                },
                {
                    "url": "https://ru.wikibooks.org",
                    "dbname": "ruwikibooks",
                    "code": "wikibooks",
                    "sitename": "\u0412\u0438\u043a\u0438\u0443\u0447\u0435\u0431\u043d\u0438\u043a"
                },
                {
                    "url": "https://ru.wikinews.org",
                    "dbname": "ruwikinews",
                    "code": "wikinews",
                    "sitename": "\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438"
                },
                {
                    "url": "https://ru.wikiquote.org",
                    "dbname": "ruwikiquote",
                    "code": "wikiquote",
                    "sitename": "\u0412\u0438\u043a\u0438\u0446\u0438\u0442\u0430\u0442\u043d\u0438\u043a"
                },
                {
                    "url": "https://ru.wikisource.org",
                    "dbname": "ruwikisource",
                    "code": "wikisource",
                    "sitename": "\u0412\u0438\u043a\u0438\u0442\u0435\u043a\u0430"
                },
                {
                    "url": "https://ru.wikiversity.org",
                    "dbname": "ruwikiversity",
                    "code": "wikiversity",
                    "sitename": "\u0412\u0438\u043a\u0438\u0432\u0435\u0440\u0441\u0438\u0442\u0435\u0442"
                },
                {
                    "url": "https://ru.wikivoyage.org",
                    "dbname": "ruwikivoyage",
                    "code": "wikivoyage",
                    "sitename": "Wikivoyage"
                }
            ],
            "localname": "Russian"
        },
        "219": {
            "code": "rue",
            "name": "\u0440\u0443\u0441\u0438\u043d\u044c\u0441\u043a\u044b\u0439",
            "site": [
                {
                    "url": "https://rue.wikipedia.org",
                    "dbname": "ruewiki",
                    "code": "wiki",
                    "sitename": "\u0412\u0456\u043a\u0456\u043f\u0435\u0434\u0456\u044f"
                }
            ],
            "localname": "Rusyn"
        },


 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"
#include "Site.hpp"

class SitematrixLanguage : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Response
  string code;
  string localname;
  string name;
  vector<Site> sites;

  void clearRequest() {}

  void clearResponse() {
   code.clear();
   localname.clear();
   name.clear();
   sites.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {  
   code=json["code"].string_value();
   name=json["name"].string_value();
   auto siteJson=json["site"].array_items();
   for(auto is : siteJson) { 
    Site site;
    site.fromJson(is);
    sites.push_back(site);
   }
   localname=json["localname"].string_value();
  }
  
  string toJson() {
   string resSites;
   for(Site site : sites) {
    resSites += (resSites.length() > 0 ? "," : "") + site.toJson();
   }
   return (string) "{"
          + (code.length() > 0 ? "\"code\":\""+code+"\"," : "")
          + (localname.length() > 0 ? "\"localname\":\""+localname+"\"," : "")
          + (name.length() > 0 ? "\"code\":\""+name+"\"," : "");
          + "\"site\":[" + resSites + "]";
  }

};

const string SitematrixLanguage::versionMajor = "201512290030";
const string SitematrixLanguage::versionMinor = "201512290030";

#endif // #ifndef SITEMATRIXLANGUAGE_HPP
 
