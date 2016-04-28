#ifndef RECENTCHANGES_HPP
#define RECENTCHANGES_HPP
/*
 RecentChanges.hpp represent "recentchanges" request and response of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp recentchanges(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brecentchanges
https://www.mediawiki.org/wiki/API:RecentChanges

 Example:

 Requests:
https://en.wikipedia.org/w/api.php?action=query&list=recentchanges
https://en.wikipedia.org/w/api.php?action=query&list=recentchanges&rcprop=user|userid|comment|parsedcomment|flags|timestamp|title|ids|sizes|redirect|patrolled|loginfo|tags|sha1

 Responses:
{
    "batchcomplete": "",
    "continue": {
        "rccontinue": "20160425130336|819103296",
        "continue": "-||"
    },
    "query": {
        "recentchanges": [
            {
                "type": "edit",
                "ns": 0,
                "title": "2016 Perak FA season",
                "pageid": 50301702,
                "revid": 717052728,
                "old_revid": 717052316,
                "rcid": 819103304,
                "timestamp": "2016-04-25T13:03:40Z"
            },
            {
                "type": "log",
                "ns": 2,
                "title": "User:Kesala sudhakar",
                "pageid": 0,
                "revid": 0,
                "old_revid": 0,
                "rcid": 819103303,
                "timestamp": "2016-04-25T13:03:40Z"
            },
<...>
            {
                "type": "edit",
                "ns": 0,
                "title": "Ricochet (musician)",
                "pageid": 48268993,
                "revid": 717053065,
                "old_revid": 717052947,
                "rcid": 819103906,
                "user": "Behrami",
                "userid": 4816193,
                "oldlen": 1948,
                "newlen": 1969,
                "timestamp": "2016-04-25T13:06:30Z",
                "comment": "",
                "tags": [],
                "sha1": "ea81e59f613d839edc35a6eccdb8770434840432"
            },

<...>
            {
                "type": "categorize",
                "ns": 14,
                "title": "Category:AfD debates",
                "pageid": 50226812,
                "revid": 717052954,
                "old_revid": 716740615,
                "rcid": 819103714,
                "user": "Anthony Bradbury",
                "userid": 1188594,
                "oldlen": 0,
                "newlen": 0,
                "timestamp": "2016-04-25T13:05:34Z",
                "comment": "[[:Wikipedia:Articles for deletion/Art Resilience movement]] and [[Special:WhatLinksHere/Wikipedia:Articles for deletion/Art Resilience movement|7 pages]] removed from category",
                "parsedcomment": "<a href=\"/wiki/Wikipedia:Articles_for_deletion/Art_Resilience_movement\" title=\"Wikipedia:Articles for deletion/Art Resilience movement\">Wikipedia:Articles for deletion/Art Resilience movement</a> and <a href=\"/wiki/Special:WhatLinksHere/Wikipedia:Articles_for_deletion/Art_Resilience_movement\" title=\"Special:WhatLinksHere/Wikipedia:Articles for deletion/Art Resilience movement\">7 pages</a> removed from category",
                "patrolled": "",
                "tags": [],
                "sha1": "943179b552622e0f90aa6bc0cf76e42326353c0e"
            },
<...>

            {
                "type": "categorize",
                "ns": 14,
                "title": "Category:Redirects from modifications",
                "pageid": 50316576,
                "revid": 717053158,
                "old_revid": 0,
                "rcid": 819104074,
                "user": "AnomieBOT",
                "userid": 7611264,
                "bot": "",
                "oldlen": 0,
                "newlen": 0,
                "timestamp": "2016-04-25T13:07:14Z",
                "comment": "[[:Template talk:Montreal municipal election, 2005/Position/Councillor, Saint-Henri-La Petite-Bourgogne-Pointe-Saint-Charles]] added to category",
                "patrolled": "",
                "tags": [],
                "sha1": "ad4e9f531efbeb3a3b8f87ac460f596653d3bc34"
            },
            {
                "type": "new",
                "ns": 11,
                "title": "Template talk:Montreal municipal election, 2005/Position/Councillor, Saint-Henri-La Petite-Bourgogne-Pointe-Saint-Charles",
                "pageid": 50316576,
                "revid": 717053158,
                "old_revid": 0,
                "rcid": 819104073,
                "user": "AnomieBOT",
                "userid": 7611264,
                "bot": "",
                "new": "",
                "oldlen": 0,
                "newlen": 303,
                "timestamp": "2016-04-25T13:07:14Z",
                "comment": "Redirecting to [[:Template talk:Montreal municipal election, 2005/Position/Councillor, Saint-Henri\u2013La Petite-Bourgogne\u2013Pointe-Saint-Charles]] because titles with en-dashes are hard to type.  Errors? [[User:AnomieBOT/shutoff/EnDashRedirectCreator]]",
                "redirect": "",
                "patrolled": "",
                "tags": [],
                "sha1": "ad4e9f531efbeb3a3b8f87ac460f596653d3bc34"
            },
<...>
            {
                "type": "log",
                "ns": 10,
                "title": "Template:Cite pmid/7586824",
                "pageid": 31963458,
                "revid": 0,
                "old_revid": 0,
                "rcid": 819104387,
                "user": "AnomieBOT III",
                "userid": 20508333,
                "bot": "",
                "oldlen": 0,
                "newlen": 0,
                "timestamp": "2016-04-25T13:08:56Z",
                "comment": "Deleting per [[Wikipedia:Templates for discussion/Log/2016 April 16#Orphaned Template:Cite pmid and related subpages]]. If this bot is malfunctioning, please report it at [[User:AnomieBOT III/shutoff/MassDeleter]]",
                "patrolled": "",
                "logid": 74429224,
                "logtype": "delete",
                "logaction": "delete",
                "logparams": {},
                "tags": []
            },


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
#include "RecentChange.hpp"

class RecentChanges : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Request
               
  // Response  

  // Servo

  void clearRequest() {
  }

  void clearResponse() {
  }

  void clearServo() {
  }
  
  void fromJsonSub(const json11::Json& json) {
   //cout << "[[RecentChanges::fromJson]]..." << endl;
   batchcomplete = json["batchcomplete"].string_value();
   continue_res.clear();
   continue_2_res.clear();
   if(json.object_items().find("continue") != json.object_items().end()) {
    auto continueJson = json["continue"].object_items();
    if(continueJson.find("rvcontinue") != continueJson.end()) continue_res = continueJson["rvcontinue"].string_value();
    else if(continueJson.find("arvcontinue") != continueJson.end()) continue_res = continueJson["arvcontinue"].string_value();
    continue_2_res = continueJson["continue"].string_value();
   }
   //cout << "[[RecentChanges::fromJson]] continue_res: " << continue_res << endl;
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
   //cout << "[[RecentChanges::fromJson]] pagesJsonObjects.size(): " << pagesJsonObjects.size() << endl;
   for(auto ipro : pagesJsonObjects) {
    if(pagesById.find(stol(ipro.first)) == pagesById.end()) {
     //Page page(ipro.second);
     Page page;
     page.fromJson(ipro.second);
     pages.push_back(page);
     //cout << "[[RecentChanges::fromJson]] pages.size(): " << pages.size() << endl;
     //Page* pagePointer = &pages[pages.size()-1];
     //cout << "[[RecentChanges::fromJson]] page.pageid: " << page.pageid << endl;
     //pagesById[page.pageid] = pagePointer;
     //cout << "[[RecentChanges::fromJson]] page.title: " << page.title << endl;
     //pagesByTitle[page.title] = pagePointer;
     pagesById[page.pageid] = pages.size()-1;
     pagesByTitle[page.title] = pages.size()-1;
     /*
     pagesById[page.pageid] = page;
     pagesByTitle[page.title] = page;
     */
    } else {
     //cout << "[[RecentChanges::fromJson]] stol(ipro.first): " << stol(ipro.first) << endl;
     cout << "[[RecentChanges::fromJson]] pagesById[stol(ipro.first)]: " << pagesById[stol(ipro.first)] << endl;
     //pagesById[stol(ipro.first)]->fromJson(ipro.second);
     //pagesById[stol(ipro.first)].fromJson(ipro.second);
     pages[pagesById[stol(ipro.first)]].fromJson(ipro.second);
    }
   }

   vector<json11::Json> pagesJsonArray = queryJson["allrevisions"].array_items();;
   //cout << "[[RecentChanges::fromJson]] pagesJsonArray.size(): " << pagesJsonArray.size() << endl;
   for(auto ipra : pagesJsonArray) {
    //Page page(ipra);
    Page page;
    page.fromJson(ipra);
    //cout << "[[RecentChanges::fromJson]] page.pageid: " << page.pageid << endl;
    if(pagesById.find(page.pageid) == pagesById.end()) {
     pages.push_back(page);
     //cout << "[[RecentChanges::fromJson]] pages.size(): " << pages.size() << endl;
     //Page* pagePointer = &pages[pages.size()-1];
     //cout << "[[RecentChanges::fromJson]] pagePointer: " << pagePointer << endl;
     //cout << "[[RecentChanges::fromJson]] page.pageid (new): " << page.pageid << endl;
     //pagesById[page.pageid] = pagePointer;
     //cout << "[[RecentChanges::fromJson]] page.title: " << page.title << endl;
     //pagesByTitle[page.title] = pagePointer;
     pagesById[page.pageid] = pages.size()-1;
     pagesByTitle[page.title] = pages.size()-1;
     /*
     pagesById[page.pageid] = page;
     pagesByTitle[page.title] = page;
     */
    } else {
     //cout << "[[RecentChanges::fromJson]] page.pageid (old): " << page.pageid << endl;
     //Page* pagePointer = pagesById[page.pageid];
     //cout << "[[RecentChanges::fromJson]] pagesById[page.pageid]: pagePointer" << pagePointer << endl;
     //pagePointer->fromJson(ipra);
     pages[pagesById[page.pageid]].fromJson(ipra);
     //pagesById[page.pageid]->fromJson(ipra);
     //pagesById[pageRecentChanges.pageid].fromJson(ipra);
    }
   }

   //cout << "[[RecentChanges::fromJson]] pages.size(): " << pages.size() << endl;
   revisions.clear();
   for(Page prs : pages) {
    for(Revision r : prs.revisions) {
     revisions.push_back(r);
    }
   }

   //cout << "[[RecentChanges::fromJson]] revisions.size(): " << revisions.size() << endl;
   if(dir.compare("older") == 0) sort(revisions.begin( ), revisions.end( ), [] (const Revision& lhs, const Revision& rhs) {return lhs.revid < rhs.revid;});
   else sort(revisions.begin( ), revisions.end( ), [] (const Revision& lhs, const Revision& rhs) {return lhs.revid > rhs.revid;});   
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string RecentChanges::versionMajor = "201512290030";
const string RecentChanges::versionMinor = "201512290030";

#endif // #ifndef RECENTCHANGES_HPP
 
