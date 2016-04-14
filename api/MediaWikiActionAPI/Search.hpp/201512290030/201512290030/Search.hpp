#ifndef Search_HPP
#define Search_HPP
/*
 Search.hpp represent a Search information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp Searchs(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bsearch
https://www.mediawiki.org/wiki/API:Searchs

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
#include "SearchItem.hpp"

class Search : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // const long rvlimitDefault = 10;

  // Request 
  int srenablerewrites = -1; /* Enable internal query rewriting. Some search backends can rewrite the query into one its thinks gives better results, such as correcting spelling errors. Type: boolean (details)*/
  string srinfo;             /* Which metadata to return. Values (separate with |): totalhits, suggestion, rewrittenquery. Default: totalhits|suggestion|rewrittenquery*/            
  int srinterwiki = -1;     /* Include interwiki results in the search, if available. Type: boolean (details).*/
  long int srlimit = -1;    /* How many total pages to return. No more than 50 (500 for bots) allowed. Type: integer or max. Default: 10*/
  long int srnamespace=-1;  /* Search only within these namespaces. Values (separate with |): 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600. Default: 0*/
  long int sroffset=-1;     /* When more results are available, use this to continue. Type: integer. Default: 0*/
  string srprop;            /* Which properties to return: size Adds the size of the page in bytes. wordcount Adds the word count of the page. timestamp Adds the timestamp of when the page was last edited. snippet Adds a parsed snippet of the page. titlesnippet Adds a parsed snippet of the page title. redirecttitle Adds the title of the matching redirect. redirectsnippet Adds a parsed snippet of the redirect title. sectiontitle Adds the title of the matching section. sectionsnippet Adds a parsed snippet of the matching section title. isfilematch Adds a boolean indicating if the search matched file content. categorysnippet Adds a parsed snippet of the matching category. Values (separate with |): size, wordcount, timestamp, snippet, titlesnippet, redirecttitle, redirectsnippet, sectiontitle, sectionsnippet, isfilematch, categorysnippet. Default: size|wordcount|timestamp|snippet.
*/                               
  string srsearch;          /* Search for page titles or content matching this value. You can use the search string to invoke special search features, depending on what the wiki's search backend implements. This parameter is required.*/
  string srwhat;            /* Which type of search to perform. One of the following values: title, text, nearmatch*/
   
   // Response
  string batchcomplete;
  string continue_res;
  vector <SearchItem> items;
  long int sroffset_res = -1;

  void clearRequest() {
   srenablerewrites = -1;
   srinfo.clear();
   srinterwiki = -1;
   srlimit = -1;
   srnamespace = -1;
   sroffset = -1;
   srprop.clear();
   srsearch.clear();
   srwhat.clear();
  }

  void clearResponse() {
   batchcomplete.clear();
   continue_res.clear();
   items.clear();
   sroffset_res = -1;
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto firstContinueJson = json["continue"].object_items();
   sroffset_res = firstContinueJson["sroffset"].int_value();
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto searchJson = queryJson["search"].array_items();
   for(auto ipr : searchJson) {
    //SearchItem itemSearch(ipr);
    SearchItem itemSearch;
    itemSearch.fromJson(ipr);
    items.push_back(itemSearch);
   }
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Search::versionMajor = "201512290030";
const string Search::versionMinor = "201512290030";

#endif // #ifndef Search_HPP
 
