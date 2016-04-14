#ifndef ALLPAGES_HPP
#define ALLPAGES_HPP
/*
 AllPage.hpp return list of all pages by namespace (enumerate all pages sequentially in a given namespace).

 Processed by MediaWikiActionAPI.hpp allpages(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Ballpages
https://www.mediawiki.org/wiki/API:AllPages

Example:

Request:
https://ru.wikinews.org/w/api.php?action=query&list=allpages&apnamespace=14

Response:
{
 {
    "batchcomplete": "",
    "continue": {
        "apcontinue": "\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\"_\u0432_\u041f\u0435\u0442\u0440\u0413\u0423_2014_(OlyaNadler)",
        "continue": "-||"
    },
    "query": {
        "allpages": [
            {
                "pageid": 88871,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0411\u0430\u0448\u0438\u043d\u0444\u043e\u0440\u043c\""
            },
            {
                "pageid": 86262,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0414\u0435\u0442\u0441\u043a\u0438\u0439 \u043c\u0438\u0440\" \u043d\u0430 \u041b\u0443\u0431\u044f\u043d\u0441\u043a\u043e\u0439 \u043f\u043b\u043e\u0449\u0430\u0434\u0438"
            },
            {
                "pageid": 53774,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014"
            },
            {
                "pageid": 53785,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (Andrew Krizhanovsky)"
            },
            {
                "pageid": 55471,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (Buravlev-arthur)"
            },
            {
                "pageid": 56418,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (D kotofeya)"
            },
            {
                "pageid": 55531,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (KateRysh)"
            },
            {
                "pageid": 55692,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (KotBegemot1078)"
            },
            {
                "pageid": 56518,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (Lokirewwil)"
            },
            {
                "pageid": 57930,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\"\u0418\u043d\u0442\u0435\u0440\u043d\u0435\u0442-\u043c\u0430\u0442\u0435\u043c\u0430\u0442\u0438\u043a\u0430\" \u0432 \u041f\u0435\u0442\u0440\u0413\u0423 2014 (Nikita-kun-i)"
            }
        ]
    }
}
},

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"
#include "Page.hpp"

class AllPages : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Request 
  string apcontinue;         /* When more results are available, use this to continue. */  
  string apdir;              /*The direction in which to list. One of the following values: ascending, descending Default: ascending. */ 
  string apprfiltercascade;  /* Filter protections based on cascadingness (ignored when apprtype isn't set). One of the following values: cascading, noncascading, all Default: all. */ 
  string apfilterlanglinks;  /* Filter based on whether a page has langlinks. Note that this may not consider langlinks added by extensions. One of the following values: withlanglinks, withoutlanglinks, all Default: all. */ 
  string apfilterredir;      /* Which pages to list. One of the following values: all, redirects, nonredirects Default: all. */ 
  string apfrom;             /* The page title to start enumerating from. */ 
  long int aplimit = -1;     /* How many total pages to return. No more than 500 (5,000 for bots) allowed. Type: integer or max Default: 10. */ 
  long int apmaxsize = -1;   /* Limit to pages with at most this many bytes. Type: integer. */ 
  long int apminsize = -1;   /* Limit to pages with at least this many bytes. Type: integer. */ 
  long int apnamespace = -1; /* The namespace to enumerate. One of the following values: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600 Default: 0. */  
  string apprefix;           /* Search for all page titles that begin with this value. */  
  string apprexpiry;         /* Which protection expiry to filter the page on: indefinite Get only pages with indefinite protection expiry. definite Get only pages with a definite (specific) protection expiry. all Get pages with any protections expiry. One of the following values: indefinite, definite, all Default: all. */ 
  string apprlevel;          /* Filter protections based on protection level (must be used with apprtype= parameter). Values (separate with |): Can be empty, or autoconfirmed, extendedconfirmed, templateeditor, sysop. */ 
  string apprtype;           /* Limit to protected pages only. Values (separate with |): edit, move, upload. */ 
  string apto;               /* The page title to stop enumerating at. */ 
  
  // Response
  string apcontinue_res;
  string batchcomplete;
  string continue_res;
  vector <Page> pages;
  map<long int, Page*> pagesById;

  void clearRequest() {
   apcontinue.clear();
   apdir.clear();
   apprfiltercascade.clear();
   apfilterlanglinks.clear();
   apfilterredir.clear();
   apfrom.clear();
   aplimit = -1;
   apmaxsize = -1;
   apminsize = -1;
   apnamespace = -1;
   apprefix.clear();
   apprexpiry.clear();
   apprlevel.clear();
   apprtype.clear();
   apto.clear();
  }

  void clearResponse() {
   batchcomplete.clear();
   apcontinue_res.clear();
   continue_res.clear();
   pages.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   //cout << "[Allpages::fromJsonSub] batchcomplete: " << batchcomplete << endl;
   auto firstContinueJson = json["continue"].object_items();
   apcontinue_res = firstContinueJson["apcontinue"].string_value();
   //cout << "[Allpages::fromJsonSub] apcontinue_res: " << apcontinue_res << endl;
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto pagesJson = queryJson["allpages"].array_items();
   for(auto ipro : pagesJson) {
    //cout << "Allpages HERE" << endl;
    //Page pageRevisions(ipro.second);
    Page page;
    page.fromJson(ipro);
    //cout << "[Allpages::fromJsonSub] page.pageid: " << page.pageid << endl;
    if(pagesById.find(page.pageid) == pagesById.end()) {
     pages.push_back(page);
     pagesById[page.pageid] = &pages[pages.size()-1];
    }
   }
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string AllPages::versionMajor = "201512290030";
const string AllPages::versionMinor = "201512290030";

#endif // #ifndef ALLPAGES_HPP
 
