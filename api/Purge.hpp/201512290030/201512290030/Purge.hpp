#ifndef Purge_HPP
#define Purge_HPP
/*
 Purge.hpp represent a Purge information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp Purges(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BPurge
https://www.mediawiki.org/wiki/API:Purges

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
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

class Purge {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  bool forcelinkupdate = 0; /* Update the links tables. Type: boolean*/

  bool forcerecursivelinkupdate = 0; /* Update the links table, and update the links tables for any page that uses this page as a template. Type: boolean*/

  string continueP; /* When more results are available, use this to continue.*/ 

  string titles; /*A list of titles to work on. Separate values with |. Maximum number of values is 50 (500 for bots).*/

  long int pageids = -1; /*A list of page IDs to work on. Type: list of integers    Separate values with |. Maximum number of values is 50 (500 for bots).*/
 
  long int revids = -1; /* A list of revision IDs to work on. Type: list of integers   Separate values with |. Maximum number of values is 50 (500 for bots).*/

  string generator; /* Get the list of pages to work on by executing the specified query module. Note: Generator parameter names must be prefixed with a "g", see examples. One of the following values: allcategories, alldeletedrevisions, allfileusages, allimages, alllinks, allpages, allredirects, allrevisions, alltransclusions, backlinks, categories, categorymembers, contenttranslation, contenttranslationsuggestions, deletedrevisions, duplicatefiles, embeddedin, exturlusage, fileusage, geosearch, gettingstartedgetpages, images, imageusage, iwbacklinks, langbacklinks, links, linkshere, listpages, oldreviewedpages, pageswithprop, prefixsearch, protectedtitles, querypage, random, recentchanges, redirects, revisions, search, templates, transcludedin, watchlist, watchlistraw*/

  bool redirects = 0;

  bool converttitles = 0;/* Convert titles to other variants if necessary. Only works if the wiki's content language supports variant conversion. Languages that support variant conversion include gan, iu, kk, ku, shi, sr, tg, uz, zh. Type: boolean (details)*/

   // Response
  string batchcomplete;
  
  string res;
  string purgeRes;

  Purge() {}
  
  Purge(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Purge(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   forcelinkupdate = 0;
   forcerecursivelinkupdate = 0;
   continueP = " " ;
   titles = " ";
   pageids = -1;
   revids = -1;
   generator = " ";
   redirects = 0;
   converttitles = 0;

   batchcomplete = "";
   res = "";
   purgeRes = "";
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString; 
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto purge = json["purge"].object_items();
   purgeRes = purge["purged"].string_value();
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Purge::versionMajor = "201512290030";
const string Purge::versionMinor = "201512290030";

#endif // #ifndef Purge_HPP
 
