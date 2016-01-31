#ifndef CATEGORIES_HPP
#define CATEGORIES_HPP
/*
 Categories.hpp return list all categories the pages belong to.

 Processed by MediaWikiActionAPI.hpp Categoriess(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BCategories
https://www.mediawiki.org/wiki/API:Categoriess

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
#include "Category.hpp"

class Categories {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string clprop;/*    Which additional properties to get for each category: sortkey       Adds the sortkey (hexadecimal string) and sortkey prefix (human-readable part) for the category. timestamp Adds timestamp of when the category was added. hidden Tags categories that are hidden with __HIDDENCAT__. Values (separate with |): sortkey, timestamp, hidden*/

  string clshow;/* Which kind of categories to show. Values (separate with |): hidden, !hidden*/

  string cllimit;/* How many categories to return. No more than 500 (5,000 for bots) allowed. Type: integer or max Default: 10*/

  string clcontinue;/* When more results are available, use this to continue.*/ 

  string clcategories;/* Only list these categories. Useful for checking whether a certain page is in a certain category. Separate values with |. Maximum number of values is 50 (500 for bots).*/

  string cldir;/* The direction in which to list. One of the following values: ascending, descending Default: ascending */ 

  string title;
  long int pageid = -1;
  int ns = -1;
 
  // Response
  string batchcomplete;
  vector <Category> items;
  string res;
  string clcontinue_res;
  string continue_res;

  Categories() {}
  
  Categories(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Categories(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   clprop = "";
   clshow = "";
   cllimit = "";
   clcontinue = "";
   clcategories = "";
   cldir = "";
   title = "";
   pageid = -1;
   ns = -1;

   batchcomplete = "";
   items.clear();
   res = "";
   continue_res = "";
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString; 
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto firstContinueJson = json["continue"].object_items();
   clcontinue_res = firstContinueJson["clcontinue"].string_value();
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto pagesJson = queryJson["pages"].object_items();
   for(auto page : pagesJson) {
    auto resJson = page.second; 
    title = resJson["title"].string_value();
    ns = resJson["ns"].int_value();
    pageid = resJson["pageid"].int_value();
    auto categoriesJson = resJson["categories"].array_items();
    for(auto ipr : categoriesJson) {
     Category itemCategories(ipr);
     items.push_back(itemCategories);
    }
   }
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Categories::versionMajor = "201512290030";
const string Categories::versionMinor = "201512290030";

#endif // #ifndef CATEGORIES_HPP
 
