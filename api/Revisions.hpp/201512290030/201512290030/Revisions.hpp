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
https://en.wikipedia.org/w/api.php?action=query&prop=revisions&titles=User:Krassotkin&rvlimit=20&rvprop=ids|flags|timestamp|user|userid|size|sha1|contentmodel|comment|parsedcomment|content|tags|parsetree|flagged

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
  long rvlimit; /* Limit how many revisions will be returned. May only be used with a single page (mode #2). No more than 500 (5,000 for bots) allowed.Type: integer or max */
  bool rvexpandtemplates; /*  Expand templates in revision content (requires rvprop=content). */
  bool rvparse; /* Parse revision content (requires rvprop=content). For performance reasons, if this option is used, rvlimit is enforced to 1. */
  long rvsection; /* Only retrieve the content of this section number. */
  long rvdiffto; /* Revision ID to diff each revision to. Use prev, next and cur for the previous, next and current revision respectively. */
  long rvdifftotext; /* Text to diff each revision to. Only diffs a limited number of revisions. Overrides rvdiffto. If rvsection is set, only that section will be diffed against this text. */
  bool rvdifftotextpst; /* Perform a pre-save transform on the text before diffing it. Only valid when used with rvdifftotext. */
  string rvcontentformat; /* Serialization format used for rvdifftotext and expected for output of content.  of the following values: application/json, text/x-wiki, text/javascript, text/css, text/plain */
  long rvstartid; /* From which revision ID to start enumeration. */
  long rvendid; /* Stop revision enumeration on this revision ID. */
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
   rvlimit = 0;
   rvexpandtemplates = false;
   rvparse = false;
   rvsection = 0;
   rvdiffto = 0;
   rvdifftotext = 0;
   rvdifftotextpst = false;
   rvcontentformat = "";
   rvstartid = 0;
   rvendid = 0;
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
   auto pagesJson = json["pages"].object_items();
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
 
