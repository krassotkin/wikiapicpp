#ifndef Search_HPP
#define Search_HPP
/*
 Search.hpp represent a Search information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp Searchs(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bsearch
https://www.mediawiki.org/wiki/API:Searchs

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
#include "SearchItem.hpp"

class Search {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string srsearch; /*    Search for page titles or content matching this value. You can use the search string to invoke special search features, depending on what the wiki's search backend implements. This parameter is required.*/

  long int srnamespace=-1; /*    Search only within these namespaces. Values (separate with |): 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600. Default: 0*/

  string srwhat; /*Which type of search to perform. One of the following values: title, text, nearmatch*/

  string srinfo; /*Which metadata to return. Values (separate with |): totalhits, suggestion, rewrittenquery. Default: totalhits|suggestion|rewrittenquery*/

  string srprop; /*Which properties to return: size Adds the size of the page in bytes. wordcount Adds the word count of the page. timestamp Adds the timestamp of when the page was last edited. snippet Adds a parsed snippet of the page. titlesnippet Adds a parsed snippet of the page title. redirecttitle Adds the title of the matching redirect. redirectsnippet Adds a parsed snippet of the redirect title. sectiontitle Adds the title of the matching section. sectionsnippet Adds a parsed snippet of the matching section title. isfilematch Adds a boolean indicating if the search matched file content. categorysnippet Adds a parsed snippet of the matching category. Values (separate with |): size, wordcount, timestamp, snippet, titlesnippet, redirecttitle, redirectsnippet, sectiontitle, sectionsnippet, isfilematch, categorysnippet. Default: size|wordcount|timestamp|snippet.
*/
 
   long int sroffset=-1; /*When more results are available, use this to continue. Type: integer. Default: 0*/

   long int srlimit = -1; /*How many total pages to return. No more than 50 (500 for bots) allowed. Type: integer or max. Default: 10*/

   bool srinterwiki; /*Include interwiki results in the search, if available. Type: boolean (details).*/

   bool srenablerewrites; /*Enable internal query rewriting. Some search backends can rewrite the query into one its thinks gives better results, such as correcting spelling errors. Type: boolean (details)*/

   // Response
  string batchcomplete;
  vector <SearchItem> items;
  string res;
  string continue_res;
  long int sroffset_res = -1;

  Search() {}
  
  Search(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Search(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   srsearch = "";
   srnamespace = -1;
   srwhat = "";
   srinfo = "";
   srprop = "";
   sroffset = -1;
   srlimit = -1;
   srinterwiki = false;
   srenablerewrites = false;

   batchcomplete = "";
   items.clear();
   res = "";
   continue_res = "";
   sroffset_res = -1;
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString; 
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto firstContinueJson = json["continue"].object_items();
   sroffset_res = firstContinueJson["sroffset"].int_value();
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto searchJson = queryJson["search"].array_items();
   for(auto ipr : searchJson) {
    SearchItem itemSearch(ipr);
    items.push_back(itemSearch);
   }
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Search::versionMajor = "201512290030";
const string Search::versionMinor = "201512290030";

#endif // #ifndef Search_HPP
 
