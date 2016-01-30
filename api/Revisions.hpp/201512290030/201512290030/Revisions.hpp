#ifndef REVISIONS_HPP
#define REVISIONS_HPP
/*
 Revisions.hpp represent request and response of The MediaWiki action API for *get revisions information* (#1) and *list of all revisions* (#2) requests.

 #1 Get revision information.

 May be used in several ways:

 1. Get data about a set of pages (last revision), by setting titles or pageids.
 2. Get revisions for one given page, by using titles or pageids with start, end, or limit.
 3. Get data about a set of revisions by setting their IDs with revids.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:Revisions

 #2 List all revisions

 Processed by MediaWikiActionAPI.hpp allrevisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Ballrevisions
https://www.mediawiki.org/wiki/API:Allrevisions

 Example (#1):

 Request:
https://en.wikipedia.org/w/api.php?action=query&prop=revisions&titles=User:Krassotkin&rvlimit=20&rvprop=ids|flags|timestamp|user|userid|size|sha1|contentmodel|comment|parsedcomment|content|tags|parsetree|flagged

 Response:
{
    "batchcomplete": "",
    "query": {
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
                        "parsetree": "<root>[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n ... [[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n ... {{userpage|User:Krassotkin}}\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
                    },
                    ...
                ]
            }
        }
    }
}

 Example (#1):

 Request:
https://ru.wikinews.org/w/api.php?action=query&prop=revisions&titles=User:Krassotkin&rvprop=content

 Response:

{
    "batchcomplete": "",
    "query": {
        "normalized": [
            {
                "from": "User:Krassotkin",
                "to": "\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin"
            }
        ],
        "pages": {
            "8143": {
                "pageid": 8143,
                "ns": 2,
                "title": "\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin",
                "revisions": [
                    {
                        "contentformat": "text/x-wiki",
                        "contentmodel": "wikitext",
                        "*": "<table style=\"float:left;vertical-align:top;width:100%\">\n <tr>\n ... \n[[en:User:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
                    }
                ]
            }
        }
    }
}

 Example (#1 empty page):

 Response:
{"batchcomplete":"","query":{"normalized":[{"from":"test","to":"Test"}],"pages":{"-1":{"ns":0,"title":"Test","missing":""}}}}

 Example (#2)

 Request:
https://ru.wikinews.org/w/api.php?action=query&list=allrevisions&arvlimit=5&arvgeneratetitles&arvdir=older&arvprop=ids|flags|timestamp|user|userid|size|sha1|contentmodel|comment|parsedcomment|content|tags|parsetree

 Response:
{
    "batchcomplete": "",
    "continue": {
        "arvcontinue": "20160124012847|422848",
        "continue": "-||"
    },
    "warnings": {
        "allrevisions": {
            "*": "Conversion to XML is supported for wikitext only, \u041c\u043e\u0434\u0443\u043b\u044c:Weather/data uses content model Scribunto"
        }
    },
    "query": {
        "allrevisions": [
            {
                "pageid": 16100,
                "revisions": [
                    {
                        "revid": 422853,
                        "parentid": 422851,
                        "minor": "",
                        "user": "Krassotkin",
                        "userid": 3944,
                        "timestamp": "2016-01-24T07:26:32Z",
                        "size": 4163,
                        "sha1": "409377e0101980e0ff8a3c7368a745633fe02b0c",
                        "contentmodel": "wikitext",
                        "comment": "\u041e\u0442\u043a\u0430\u0442 \u043f\u0440\u0430\u0432\u043e\u043a [[Special:Contributions/95.30.134.174|95.30.134.174]] ([[User talk:95.30.134.174|\u043e\u0431\u0441\u0443\u0436\u0434\u0435\u043d\u0438\u0435]]) \u043a \u0432\u0435\u0440\u0441\u0438\u0438 [[User:Krassotkin|Krassotkin]]",
                        "parsedcomment": "\u041e\u0442\u043a\u0430\u0442 ... Krassotkin</a>",
                        "tags": [],
                        "parsetree": "<root><template><title>\u0434\u0430\u0442\u0430</title><part><name index=\"1\"/><value>8 \u043d\u043e\u044f\u0431\u0440\u044f 2011</value></part></template>\n<template lineStart=\"1\"> ... \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "{{\u0434\u0430\u0442\u0430|8 \u043d\u043e\u044f\u0431\u0440\u044f 2011}}\n{{\u041a\u0430\u043b\u0438\u0444\u043e\u0440\u043d\u0438\u044f}}\n[[\u0424\u0430\u0439\u043b:Michael-jackson-vector-2.jpg| ... \u0b95\u0bbe\u0bb0\u0ba3\u0bae\u0bcd, \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]"
                    },
                    {
                        "revid": 422851,
                        "parentid": 194811,
                        "user": "95.30.134.174",
                        "anon": "",
                        "userid": 0,
                        "timestamp": "2016-01-24T07:23:42Z",
                        "size": 4165,
                        "sha1": "3f11835c11accf6f6b84cd8b1dac5b8119897357",
                        "contentmodel": "wikitext",
                        "comment": "-",
                        "parsedcomment": "-",
                        "tags": [
                            "mobile edit",
                            "mobile web edit"
                        ],
                        "parsetree": "<root><template><title>\u0434\u0430\u0442\u0430</title><part><name index=\"1\"/><value>8 \u043d\u043e\u044f\u0431\u0440\u044f 2011</value></part></template>\n<template lineStart=\"1\"><title> ... \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "{{\u0434\u0430\u0442\u0430|8 \u043d\u043e\u044f\u0431\u0440\u044f 2011}}\n{{\u041a\u0430\u043b\u0438\u0444\u043e\u0440\u043d\u0438\u044f}}\n[[\u0424\u0430\u0439\u043b:Michael-jackson-vector-2.jpg|... \u0b95\u0bbe\u0bb0\u0ba3\u0bae\u0bcd, \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]"
                    }
                ],
                "ns": 0,
                "title": "\u0421\u0443\u0434 \u043f\u0440\u0438\u0437\u043d\u0430\u043b \u0432\u0438\u043d\u043e\u0432\u043d\u044b\u043c \u0432\u0440\u0430\u0447\u0430, \u043b\u0435\u0447\u0438\u0432\u0448\u0435\u0433\u043e \u041c\u0430\u0439\u043a\u043b\u0430 \u0414\u0436\u0435\u043a\u0441\u043e\u043d\u0430, \u0432 \u0435\u0433\u043e \u0441\u043c\u0435\u0440\u0442\u0438"
            },
            {
                "pageid": 47662,
                "revisions":  [...],
                "ns": 102,
                "title": "\u041a\u043e\u043c\u043c\u0435\u043d\u0442\u0430\u0440\u0438\u0438:\u0418\u0441\u043f\u043e\u043b\u043d\u0438\u043b\u043e\u0441\u044c 80 \u043b\u0435\u0442 \u0415\u0432\u0440\u0435\u0439\u0441\u043a\u043e\u0439 \u0430\u0432\u0442\u043e\u043d\u043e\u043c\u043d\u043e\u0439 \u043e\u0431\u043b\u0430\u0441\u0442\u0438"
            },
            {
                "pageid": 11916,
                "revisions": [...],
                "ns": 828,
                "title": "\u041c\u043e\u0434\u0443\u043b\u044c:Weather/data"
            }
        ]
    }
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
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
#include "PageRevisions.hpp"
#include "Revision.hpp"

class Revisions {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long limitDefault = 10;

  /* Servo */
  string errJson;

  /*
   Request

   Get revision information prefix: rv.
   List all revisions prefix: arv.

   For API gnored suffix _req (request) and _res (response).
  */                            
                                 
  string contentformat;        /* Serialization format used for rvdifftotext and expected for output of content.  of the following values: application/json, text/x-wiki, text/javascript, text/css, text/plain. */
  string continue_req;         /* When more results are available, use this to continue. */
  string diffto;               /* Revision ID to diff each revision to. Use prev, next and cur for the previous, next and current revision respectively. */
  string difftotext;           /* Text to diff each revision to. Only diffs a limited number of revisions. Overrides rvdiffto. If rvsection is set, only that section will be diffed against this text. */    
  string dir;                  /* In which direction to enumerate: "newer" -  list oldest first. Note: start has to be before end. "older" - List newest first (default). Note: start has to be later than end. */
  string difftotextpst;        /* Perform a pre-save transform on the text before diffing it. Only valid when used with rvdifftotext. */                   
  string end;                  /* Enumerate up to this timestamp. Type: string of timestamp (allowed formats). */
  long endid = -1;             /* Stop revision enumeration on this revision ID. List all revisions haven't alias. */
  int expandtemplates = -1;    /*  Expand templates in revision content (requires rvprop=content). */
  string excludeuser;          /* Exclude revisions made by user. Type: string of user name. */
  int generatetitles = -1;     /* When being used as a generator, generate titles rather than revision IDs. Get revision information haven't alias. */
  long limit = -1;             /* Limit how many revisions will be returned. May only be used with a single page (mode #2). No more than 500 (5,000 for bots) allowed.Type: integer or max. */          
  string namespace_req;        /* Only list pages in this namespace. Note: Due to miser mode, using this may result in fewer than arvlimit results returned before continuing; in extreme cases, zero results may be returned. Values (separate with |): 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600. Get revision information  haven't alias. */ 
  string pageids;              /* Id of pages for request. Conflict with titles. List all revisions haven't alias. */
  int parse = -1;              /* Parse revision content (requires rvprop=content). For performance reasons, if this option is used, rvlimit is enforced to 1. */
  string prop;                 /* Which properties to get for each revision (separate with |):
                                  ids - The ID of the revision.
                                  flags - Revision flags (minor).
                                  timestamp - The timestamp of the revision.
                                  user - User that made the revision.
                                  userid - User ID of the revision creator.
                                  size - Length (bytes) of the revision.
                                  sha1 - SHA-1 (base 16) of the revision.
                                  contentmodel - Content model ID of the revision.
                                  comment - Comment by the user for the revision.
                                  parsedcomment - Parsed comment by the user for the revision.
                                  content - Text of the revision.
                                  tags - Tags for the revision.
                                  parsetree - The XML parse tree of revision content (requires content model wikitext).
                                  flagged - (no description) - has not in list all revisions.
                               */
  long section = -1;           /* Only retrieve the content of this section number. */
  string start;                /* From which revision timestamp to start enumeration.Type: string of timestamp (allowed formats). List all revisions alias: arvcontentformat. */
  long startid = -1;           /* From which revision ID to start enumeration. List all revisions haven't alias. */
  string tag;                  /* Only list revisions tagged with this tag.  List all revisions haven't alias. */
  string titles;               /* Titles of pages for request. Conflict with pageids. List all revisions haven't alias. */
  string user;                 /* Only include revisions made by user. Type: string of user name. */
                                  
                                
  // Response                   
  string res;                  /* Last parsed string response. */
                               
  string batchcomplete;        
  string continue_res;         /* continue->rvcontinue or continue->arvcontinue in API */
  string continue_2_res;       /* continue->continue in API */
  vector<PageRevisions> pages; /* vector of all pages */


  // Interfaces
  map<long int, PageRevisions> pagesById;
  map<string, string> pagesNormalizedTitles;
  map<string, PageRevisions> pagesByTitle;
  vector<Revision> revisions;

  Revisions() {}
  
  Revisions(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Revisions(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson.clear();
   clearRequest();
   clearResponse();
  }

  void clearRequest() {
   contentformat.clear();
   continue_req.clear();
   diffto.clear();
   difftotext.clear();   
   dir.clear();
   difftotextpst.clear();
   end.clear();
   endid = -1;
   expandtemplates = -1;
   excludeuser.clear();
   generatetitles = -1;
   limit = -1;          
   namespace_req.clear();
   pageids = -1;
   parse = -1; 
   prop.clear();
   section = -1;
   start.clear();
   startid = -1;
   tag.clear();
   titles.clear();
   user.clear();
  }

  void clearResponse() {
   batchcomplete.clear();
   continue_res.clear();
   continue_2_res.clear();
   pages.clear();
   pagesById.clear();
   pagesByTitle.clear();
   pagesNormalizedTitles.clear();
   revisions.clear();
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   if(json.object_items().find("continue") != json.object_items().end()) {
    auto continueJson = json["continue"].object_items();
    if(continueJson.find("rvcontinue") != continueJson.end()) continue_res = continueJson["rvcontinue"].string_value();
    else if(continueJson.find("arvcontinue") != continueJson.end()) continue_res = continueJson["arvcontinue"].string_value();
    continue_2_res = continueJson["continue"].string_value();
   }
   //cout << "[[Revisions::fromJson]] continue_res: " << continue_res << endl;
   auto queryJson = json["query"].object_items();
   if(queryJson.find("normalized") != queryJson.end()) {
    auto normalizedJson = queryJson["normalized"].array_items();
    for(auto inor : normalizedJson) {
     string from = inor["from"].string_value();
     if(pagesNormalizedTitles.find(from) != pagesNormalizedTitles.end()) continue;
     string to = inor["to"].string_value();
     pagesNormalizedTitles[from] = to;
    }
   }
   map<string, json11::Json> pagesJsonObjects = queryJson["pages"].object_items();
   vector<json11::Json> pagesJsonArray = queryJson["allrevisions"].array_items();
   //if(queryJson.find("pages") != queryJson.end()) pagesJson = queryJson["pages"].object_items();
   //else if(queryJson.find("allrevisions") != queryJson.end()) pagesJson = queryJson["allrevisions"].array_items();
   //cout << "[[Revisions::fromJson]] pagesJsonObjects.size(): " << pagesJsonObjects.size() << endl;
   //cout << "[[Revisions::fromJson]] pagesJsonArray.size(): " << pagesJsonArray.size() << endl;
   for(auto ipro : pagesJsonObjects) {
    if(pagesById.find(stol(ipro.first)) == pagesById.end()) {
     PageRevisions pageRevisions(ipro.second);
     pages.push_back(pageRevisions);
     pagesById[pageRevisions.pageid] = pageRevisions;
     pagesByTitle[pageRevisions.title] = pageRevisions;
    } else {
     pagesById[stol(ipro.first)].fromJson(ipro.second);
    }
   }
   for(auto ipra : pagesJsonArray) {
    PageRevisions pageRevisions(ipra);
    if(pagesById.find(pageRevisions.pageid) == pagesById.end()) {
     pages.push_back(pageRevisions);
     pagesById[pageRevisions.pageid] = pageRevisions;
     pagesByTitle[pageRevisions.title] = pageRevisions;
    } else {
     pagesById[pageRevisions.pageid].fromJson(ipra);
    }
   }
   //cout << "[[Revisions::fromJson]] pages.size(): " << pages.size() << endl;
   for(PageRevisions prs : pages) {
    for(Revision r : prs.revisions) {
     revisions.push_back(r);
    }
   }
   //cout << "[[Revisions::fromJson]] revisions.size(): " << revisions.size() << endl;
   if(dir.compare("older") == 0) sort(revisions.begin( ), revisions.end( ), [] (const Revision& lhs, const Revision& rhs) {return lhs.revid < rhs.revid;});
   else sort(revisions.begin( ), revisions.end( ), [] (const Revision& lhs, const Revision& rhs) {return lhs.revid > rhs.revid;});   
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Revisions::versionMajor = "201512290030";
const string Revisions::versionMinor = "201512290030";

#endif // #ifndef REVISIONS_HPP
 
