#ifndef SITEMATRIX_HPP
#define SITEMATRIX_HPP
/*
 Sitematrix.hpp get Wikimedia sites list. The code (technically dbname/wikiid) is either the language code + project code for content projects or the subdomain + main domain for all the others.

 Processed by MediaWikiActionAPI.hpp Sitematrix(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix
https://www.mediawiki.org/wiki/API:Sitematrix/de (https://www.mediawiki.org/wiki/API:Sitematrix)

 Examples:

Request:
https://en.wikipedia.org/w/api.php?action=sitematrix

Response:
{
    "sitematrix": {
        "count": 895,
        "0": {
            "code": "aa",
            "name": "Qaf\u00e1r af",
            "site": [
                {
                    "url": "https://aa.wikipedia.org",
                    "dbname": "aawiki",
                    "code": "wiki",
                    "sitename": "Wikipedia",
                    "closed": ""
                },
                {
                    "url": "https://aa.wiktionary.org",
                    "dbname": "aawiktionary",
                    "code": "wiktionary",
                    "sitename": "Wiktionary",
                    "closed": ""
                },
                {
                    "url": "https://aa.wikibooks.org",
                    "dbname": "aawikibooks",
                    "code": "wikibooks",
                    "sitename": "Wikibooks",
                    "closed": ""
                }
            ],
            "localname": "Afar"
        },
        "1": {
            "code": "ab",
            "name": "\u0410\u04a7\u0441\u0448\u04d9\u0430",
            "site": [
                {
                    "url": "https://ab.wikipedia.org",
                    "dbname": "abwiki",
                    "code": "wiki",
                    "sitename": "\u0410\u0432\u0438\u043a\u0438\u043f\u0435\u0434\u0438\u0430"
                },
                {
                    "url": "https://ab.wiktionary.org",
                    "dbname": "abwiktionary",
                    "code": "wiktionary",
                    "sitename": "Wiktionary",
                    "closed": ""
                }
            ],
            "localname": "Abkhazian"
        },
<...>

        "291": {
            "code": "zu",
            "name": "isiZulu",
            "site": [
                {
                    "url": "https://zu.wikipedia.org",
                    "dbname": "zuwiki",
                    "code": "wiki",
                    "sitename": "Wikipedia"
                },
                {
                    "url": "https://zu.wiktionary.org",
                    "dbname": "zuwiktionary",
                    "code": "wiktionary",
                    "sitename": "Wiktionary"
                },
                {
                    "url": "https://zu.wikibooks.org",
                    "dbname": "zuwikibooks",
                    "code": "wikibooks",
                    "sitename": "Wikibooks",
                    "closed": ""
                }
            ],
            "localname": "Zulu"
        },
        "specials": [
            {
                "url": "https://advisory.wikimedia.org",
                "dbname": "advisorywiki",
                "code": "advisory",
                "sitename": "Advisory Board",
                "closed": ""
            },
            {
                "url": "https://ar.wikimedia.org",
                "dbname": "arwikimedia",
                "code": "arwikimedia",
                "sitename": "Wikimedia Argentina"
            },
<...>
            {
                "url": "https://collab.wikimedia.org",
                "dbname": "collabwiki",
                "code": "collab",
                "sitename": "Collab",
                "private": ""
            },
            {
                "url": "https://commons.wikimedia.org",
                "dbname": "commonswiki",
                "code": "commons",
                "sitename": "Wikimedia Commons"
            },
            {
                "url": "https://dk.wikimedia.org",
                "dbname": "dkwikimedia",
                "code": "dkwikimedia",
                "sitename": "Wikimedia Danmark"
            },
            {
                "url": "https://donate.wikimedia.org",
                "dbname": "donatewiki",
                "code": "donate",
                "sitename": "Donate",
                "fishbowl": ""
            },
<...>
            {
                "url": "https://www.wikidata.org",
                "dbname": "wikidatawiki",
                "code": "wikidata",
                "sitename": "Wikipedia"
            },
<...>
            {
                "url": "https://wikimania2017.wikimedia.org",
                "dbname": "wikimania2017wiki",
                "code": "wikimania2017",
                "sitename": "Wikipedia"
            },
            {
                "url": "https://wikimaniateam.wikimedia.org",
                "dbname": "wikimaniateamwiki",
                "code": "wikimaniateam",
                "sitename": "WikimaniaTeam",
                "private": ""
            },
            {
                "url": "https://zero.wikimedia.org",
                "dbname": "zerowiki",
                "code": "zero",
                "sitename": "Wikipedia",
                "private": ""
            }
        ]
    }
}


 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"
#include "SitematrixLanguage.hpp"
#include "Site.hpp"

class Sitematrix : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  
  // Request                         
  string smcontinue;     /* When more results are available, use this to continue. */               
  string smlangprop;     /* Which information about a language to return. 
                            Values (separate with |): code, name, site, localname 
                            Default: code|name|site|localname. 
                          */
  long int smlimit = -1; /* Maximum number of results. 
                            No more than 5,000 (5,000 for bots) allowed. 
                            Type: integer or max 
                            Default: 5000. 
                          */
  string smstate;        /* Filter the Site Matrix by wiki state: closed No write access, full read access. 
                             private Read and write restricted. 
                             fishbowl Restricted write access, full read access. 
                            Values (separate with |): all, closed, private, fishbowl 
                            Default: all. 
                          */
  string smsiteprop;     /* Which information about a site to return. 
                            Values (separate with |): url, dbname, code, sitename 
                            Default: url|dbname|code|sitename. 
                           */
  string smtype;         /* Filter the Site Matrix by type: 
                             special One off and multilingual Wikimedia projects. 
                             language Wikimedia projects under this language code. 
                            Values (separate with |): special, language 
                            Default: special|language. 
                          */
                  
  // Response                
  long int count = -1;
  vector <SitematrixLanguage> sitematrixLanguage;
  vector <Site> specials;
  
  void clearRequest() {
   smcontinue.clear();
   smlangprop.clear();
   smlimit = -1;
   smsiteprop.clear();
   smstate.clear();
   smtype.clear();
  }

  void clearResponse() {
   count = -1;
   sitematrixLanguage.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   count = json["count"].int_value();
   auto sitematrixJson=json["sitematrix"].object_items();
   for(auto element : sitematrixJson) {
    if(element.first.compare("specials") == 0) {
     //cout << "[Sitematrix:fromJsonSub] found secials" << endl;
     auto specialsJson=element.second.array_items();
     for(auto specialElement : specialsJson) {
      Site site;
      site.fromJson(specialElement);
      specials.push_back(site);
     }
    } else {
     auto pagesJson=element.second.object_items();
     SitematrixLanguage smLang;
     smLang.fromJson(element.second);
     sitematrixLanguage.push_back(smLang);
    }
   }
  }

  Site getSite(const string& val) {
   for(SitematrixLanguage sli : sitematrixLanguage)
    for(Site si : sli.sites)
     if(val.compare(si.dbname) == 0
        || val.compare(si.sitename) == 0
        || val.compare(si.url) == 0)
          return si;
   for(Site si : specials)
     if(val.compare(si.dbname) == 0
        || val.compare(si.sitename) == 0
        || val.compare(si.url) == 0)
          return si;
   Site si;
   return si;
  }

  bool isLangPrefix(string prefix){
   for(unsigned i=0; i<sitematrixLanguage.size(); i++) 
    if(prefix.compare(sitematrixLanguage[i].code) == 0) 
     return true;
   return false;
  }

  bool isDbname(string prefix){
   for(unsigned i=0; i<sitematrixLanguage.size(); i++) 
    for(unsigned j=0; j<sitematrixLanguage[i].sites.size(); j++)
     if(prefix.compare(sitematrixLanguage[i].sites[j].dbname) == 0) 
      return true;
   for(Site el : specials) 
     if(prefix.compare(el.dbname) == 0)  
      return true;
   return false;
  }

  bool isReady() {
   return (sitematrixLanguage.size() > 0) || (specials.size() > 0);
  }

  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Sitematrix::versionMajor = "201512290030";
const string Sitematrix::versionMinor = "201512290030";

#endif // #ifndef SITEMATRIX_HPP
 
