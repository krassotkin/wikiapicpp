#ifndef PAGE_HPP
#define PAGE_HPP
/*
 Page.hpp represent response of The MediaWiki action API for get revisions information request for one page.

 Get revision information.

 May be used in several ways:

 1. Get data about a set of pages (last revision), by setting titles or pageids.
 2. Get revisions for one given page, by using titles or pageids with start, end, or limit.
 3. Get data about a set of revisions by setting their IDs with revids.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:Page

 Example:
https://en.wikipedia.org/w/api.php?action=query&prop=revisions&titles=User:Krassotkin&rvlimit=20&rvprop=ids|flags|timestamp|user|userid|size|sha1|contentmodel|comment|parsedcomment|content|tags|parsetree|flagged

"pages": {
            "24251508": {
                "pageid": 24251508,
                "ns": 2,
                "title": "User:Krassotkin",
                "revisions": [
                    {
                        "revid": 653894319,
                        "parentid": 628333333,
                        "user": "Krassotkin",
                        "userid": 10436237,
                        "timestamp": "2015-03-28T14:35:57Z",
                        "size": 667,
                        "sha1": "12bbfdec234f7412412b4d7f7ae88f7576a6f5a3",
                        "contentmodel": "wikitext",
                        "comment": "",
                        "parsedcomment": "",
                        "tags": [],
                        "parsetree": "<root>[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n<template lineStart=\"1\"><title>#babel:ru</title><part><name index=\"1\"/><value>uk</value></part><part><name index=\"2\"/><value>en-1</value></part></template>\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n<template lineStart=\"1\"><title>-</title></template>\n\n<template lineStart=\"1\"><title>userpage</title><part><name index=\"1\"/><value>User:Krassotkin</value></part></template>\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n{{#babel:ru|uk|en-1}}\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n{{-}}\n\n{{userpage|User:Krassotkin}}\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
                    },
                    ...
                ]
            }
        }
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
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
#include "Category.hpp"
#include "Revision.hpp"
#include "LogEvent.hpp"

class Page {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Servo
  string errJson;

  // Response
  int ns=-1;
  long int pageid=-1;
  string title;
  vector<Category> categories;
  map<string, Category> categoriesMap;
  vector<Revision> revisions;
  map<long int, Revision> revisionsMap;
  vector<LogEvent> logEvents;
  map<long int, LogEvent> logEventsMap;

  Page() {}
  
  Page(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Page(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   categories.clear();
   categoriesMap.clear();
   errJson.clear();
   ns = -1;
   pageid = -1;
   revisions.clear();
   revisionsMap.clear();
   logEvents.clear();
   logEventsMap.clear();
   title.clear();
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   ns = json["ns"].int_value();
   pageid = json["pageid"].int_value();
   title = json["title"].string_value();
   auto revisionsJson = json["revisions"].array_items();
   for(auto itr : revisionsJson) {
    Revision revision(itr);
    revision.ns = ns;
    revision.pageid = pageid;
    revision.title = title;
    if(revisionsMap.find(revision.revid) == revisionsMap.end()) {
     revisions.push_back(revision);
     revisionsMap[revision.revid] = revision;
    }
   }
   auto categoriesJson = json["categories"].array_items();
   for(auto ipr : categoriesJson) {
    Category category(ipr);
    if(categoriesMap.find(category.title) == categoriesMap.end()) {
     categories.push_back(category);
     categoriesMap[category.title] = category;
    }
   }
  }
  
  string toJson() {
   /* not implemented */
   return "{\"not implemented\":\"not implemented\"}";
  }

};

const string Page::versionMajor = "201512290030";
const string Page::versionMinor = "201512290030";

#endif // #ifndef PAGE_HPP
 
