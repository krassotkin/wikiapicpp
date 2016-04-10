#ifndef PURGE_HPP
#define PURGE_HPP
/*
 Purge.hpp represent a Purge information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp Purges(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BPurge
https://www.mediawiki.org/wiki/API:Purges

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

//#include <chrono>
//#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"

class Purge : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  //const long rvlimitDefault = 10;

  // Request 
  string continueP;                  /* When more results are available, use this to continue.*/ 
  int converttitles = -1;            /* Convert titles to other variants if necessary. Only works if the wiki's content language supports variant conversion. Languages that support variant conversion include gan, iu, kk, ku, shi, sr, tg, uz, zh. Type: boolean (details)*/
  int forcelinkupdate = -1;          /* Update the links tables. Type: boolean*/
  int forcerecursivelinkupdate = -1; /* Update the links table, and update the links tables for any page that uses this page as a template. Type: boolean*/
  string generator;                  /* Get the list of pages to work on by executing the specified query module. Note: Generator parameter names must be prefixed with a "g", see examples. One of the following values: allcategories, alldeletedrevisions, allfileusages, allimages, alllinks, allpages, allredirects, allrevisions, alltransclusions, backlinks, categories, categorymembers, contenttranslation, contenttranslationsuggestions, deletedrevisions, duplicatefiles, embeddedin, exturlusage, fileusage, geosearch, gettingstartedgetpages, images, imageusage, iwbacklinks, langbacklinks, links, linkshere, listpages, oldreviewedpages, pageswithprop, prefixsearch, protectedtitles, querypage, random, recentchanges, redirects, revisions, search, templates, transcludedin, watchlist, watchlistraw*/
  long int pageids = -1;             /* A list of page IDs to work on. Type: list of integers    Separate values with |. Maximum number of values is 50 (500 for bots).*/                                 
  long int revids = -1;              /* A list of revision IDs to work on. Type: list of integers   Separate values with |. Maximum number of values is 50 (500 for bots).*/                               
  int redirects = -1;
  string titles;                     /* A list of titles to work on. Separate values with |. Maximum number of values is 50 (500 for bots).*/
                   
   // Response
  string batchcomplete;  
  string purged;

/*
  Purge() : MediaWikiActionAPIParameters() {}   
  Purge(const string& jsonString) : MediaWikiActionAPIParameters(jsonString) {} 
  Purge(const json11::Json& json) : MediaWikiActionAPIParameters(json) {}
*/

  void clearRequest() {
   continueP.clear();
   converttitles = -1;
   forcelinkupdate = -1;
   forcerecursivelinkupdate = -1;
   generator.clear();
   pageids = -1;
   redirects = -1;
   revids = -1;
   titles.clear();
  }

  void clearResponse() {
   batchcomplete.clear();
   purged.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto purge = json["purge"].object_items();
   purged = purge["purged"].string_value();
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Purge::versionMajor = "201512290030";
const string Purge::versionMinor = "201512290030";

#endif // #ifndef PURGE_HPP
 
