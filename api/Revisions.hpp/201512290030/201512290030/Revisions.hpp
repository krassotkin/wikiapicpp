#ifndef REVISIONS_HPP
#define REVISIONS_HPP
/*
 Revisions.hpp represent request and response of The MediaWiki action API for get revisions information request.

 Get revision information.

 May be used in several ways:

 1. Get data about a set of pages (last revision), by setting titles or pageids.
 2. Get revisions for one given page, by using titles or pageids with start, end, or limit.
 3. Get data about a set of revisions by setting their IDs with revids.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:Revisions

 Example:

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
                        "parsetree": "<root>[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n<template lineStart=\"1\"><title>#babel:ru</title><part><name index=\"1\"/><value>uk</value></part><part><name index=\"2\"/><value>en-1</value></part></template>\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n<template lineStart=\"1\"><title>-</title></template>\n\n<template lineStart=\"1\"><title>userpage</title><part><name index=\"1\"/><value>User:Krassotkin</value></part></template>\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n{{#babel:ru|uk|en-1}}\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n{{-}}\n\n{{userpage|User:Krassotkin}}\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
                    },
                    ...
                ]
            }
        }
    }
}

 Example:

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
                        "*": "<table style=\"float:left;vertical-align:top;width:100%\">\n <tr>\n  <td style=\"min-width:250px;vertical-align:top;width:80%\">\n'''\u0410\u043b\u0435\u043a\u0441\u0430\u043d\u0434\u0440 \u041a\u0440\u0430\u0441\u043e\u0442\u043a\u0438\u043d'''\n\n[[\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438:\u0411\u044e\u0440\u043e\u043a\u0440\u0430\u0442\u044b|\u0411\u044e\u0440\u043e\u043a\u0440\u0430\u0442]] \u0438 [[\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438:\u0410\u0434\u043c\u0438\u043d\u0438\u0441\u0442\u0440\u0430\u0442\u043e\u0440\u044b|\u0430\u0434\u043c\u0438\u043d\u0438\u0441\u0442\u0440\u0430\u0442\u043e\u0440]] \u0420\u0443\u0441\u0441\u043a\u0438\u0445 \u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0435\u0439, [[meta:Special:CentralAuth/Krassotkin|\u0443\u0447\u0430\u0441\u0442\u043d\u0438\u043a \u0434\u0440\u0443\u0433\u0438\u0445 \u043f\u0440\u043e\u0435\u043a\u0442\u043e\u0432 \u0412\u0438\u043a\u0438\u043c\u0435\u0434\u0438\u0430]].\n\n\u041a\u043e\u043d\u0442\u0430\u043a\u0442\u044b: [http://www.krassotkin.ru/ krassotkin.ru].\n\n\u0420\u0443\u0447\u043d\u043e\u0439 \u0431\u043e\u0442: [[\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:NewsBots|NewsBots]].\n  </td>\n  <td style=\"vertical-align:top;\">\n<div style=\"float:left;\">\n   {{Userbox/\u0420\u0430\u0434 \u043f\u043e\u043c\u043e\u0447\u044c \u043d\u043e\u0432\u0438\u0447\u043a\u0443}}\n   {{Userbox/\u041e\u0431\u0440\u0430\u0449\u0435\u043d\u0438\u0435 \u043d\u0430 \u0442\u044b}}\n   {{Userbox|id=\u0421\u0410\u0428\u0410|id-c=#FFFFFF|id-s=8|info=\u042d\u0442\u043e\u0442 \u0443\u0447\u0430\u0441\u0442\u043d\u0438\u043a  \u043f\u0440\u0435\u0434\u043f\u043e\u0447\u0438\u0442\u0430\u0435\u0442 \u043e\u0431\u0440\u0430\u0449\u0435\u043d\u0438\u0435 \u043f\u043e \u0438\u043c\u0435\u043d\u0438|info-c=#FFEF8F|border-c=#F1B7A8}}\n   {{Userbox/\u041f\u043e\u043f\u0440\u0430\u0432\u043b\u044f\u0439\u0442\u0435}}\n</div>\n  </td>\n  <td style=\"vertical-align:top;\"><div style=\"float:right\"><div>{{#babel:ru|uk|en-1}}</div></div></td>\n </tr>\n <tr>\n  <td colspan=\"4\" style=\"text-align:center;\">\n<inputbox>\ntype=create\npreload=\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a: Krassotkin/Create News\neditintro=\nwidth=42\nbgcolor=#ddf\n</inputbox>\n<div style=\"float:center;margin-left:auto;margin-right:auto;text-align:center;width:98%;\">{{Userpage}}</div>\n  </td>\n </tr>\n</table>\n\n[[\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438:\u0410\u0434\u043c\u0438\u043d\u0438\u0441\u0442\u0440\u0430\u0442\u043e\u0440\u044b]]\n[[\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\u0412\u0438\u043a\u0438\u043d\u043e\u0432\u043e\u0441\u0442\u0438:\u0411\u044e\u0440\u043e\u043a\u0440\u0430\u0442\u044b]]\n\n[[en:User:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
                    }
                ]
            }
        }
    }
}

 Example (empty page):

 Response:
{"batchcomplete":"","query":{"normalized":[{"from":"test","to":"Test"}],"pages":{"-1":{"ns":0,"title":"Test","missing":""}}}}

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
#include "PageRevisions.hpp"

class Revisions {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string titles;
  string pageids;

  string rvprop; /* Which properties to get for each revision (separate with |):
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
                    flagged - (no description) */
  long rvlimit = -1; /* Limit how many revisions will be returned. May only be used with a single page (mode #2). No more than 500 (5,000 for bots) allowed.Type: integer or max */
  int rvexpandtemplates = -1; /*  Expand templates in revision content (requires rvprop=content). */
  int rvparse = -1; /* Parse revision content (requires rvprop=content). For performance reasons, if this option is used, rvlimit is enforced to 1. */
  long rvsection = -1; /* Only retrieve the content of this section number. */
  long rvdiffto = -1; /* Revision ID to diff each revision to. Use prev, next and cur for the previous, next and current revision respectively. */
  long rvdifftotext = -1; /* Text to diff each revision to. Only diffs a limited number of revisions. Overrides rvdiffto. If rvsection is set, only that section will be diffed against this text. */
  int rvdifftotextpst = -1; /* Perform a pre-save transform on the text before diffing it. Only valid when used with rvdifftotext. */
  string rvcontentformat; /* Serialization format used for rvdifftotext and expected for output of content.  of the following values: application/json, text/x-wiki, text/javascript, text/css, text/plain */
  long rvstartid = -1; /* From which revision ID to start enumeration. */
  long rvendid = -1; /* Stop revision enumeration on this revision ID. */
  string rvstart; /* From which revision timestamp to start enumeration.Type: string of timestamp (allowed formats) */
  string rvend; /* Enumerate up to this timestamp. Type: string of timestamp (allowed formats) */
  string rvdir; /* In which direction to enumerate: "newer" -  List oldest first. Note: rvstart has to be before rvend. "older" - List newest first (default). Note: rvstart has to be later than rvend. */
  string rvuser; /* Only include revisions made by user. Type: string of user name. */
  string rvexcludeuser; /* Exclude revisions made by user. Type: string of user name. */
  string rvtag; /* Only list revisions tagged with this tag. */
  string rvcontinue; /* When more results are available, use this to continue. */

  // Response
  string batchcomplete;
  vector<PageRevisions> pages;
  map<long, PageRevisions> pagesById;
  map<string, PageRevisions> pagesByTitle;
  map<string, string> pagesNormalizedTitles;

  Revisions() {}
  
  Revisions(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Revisions(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   titles = "";
   pageids = "";

   rvprop = "";
   rvlimit = -1;
   rvexpandtemplates = -1;
   rvparse = -1;
   rvsection = -1;
   rvdiffto = -1;
   rvdifftotext = -1;
   rvdifftotextpst = -1;
   rvcontentformat = "";
   rvstartid = -1;
   rvendid = -1;
   rvstart = "";
   rvend = "";
   rvdir = "";
   rvuser = "";
   rvexcludeuser = "";
   rvtag = "";
   rvcontinue = "";

   batchcomplete = "";
   pages.clear();
   pagesById.clear();
   pagesByTitle.clear();
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto query = json["query"].object_items();
   auto normalizedJson = query["normalized"].array_items();
   for(auto inor : normalizedJson) {
    string from = inor["from"].string_value();
    string to = inor["to"].string_value();
    pagesNormalizedTitles[from] = to;
   }
   auto pagesJson = query["pages"].object_items();
   for(auto ipr : pagesJson) {
    PageRevisions pageRevisions(ipr.second);
    pages.push_back(pageRevisions);
    pagesById[pageRevisions.pageid] = pageRevisions;
    pagesByTitle[pageRevisions.title] = pageRevisions;
   }
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Revisions::versionMajor = "201512290030";
const string Revisions::versionMinor = "201512290030";

#endif // #ifndef REVISIONS_HPP
 
