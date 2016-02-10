#ifndef CATEGORIES_HPP
#define CATEGORIES_HPP
/*
 Categories.hpp return list all categories the pages belong to.

 Processed by MediaWikiActionAPI.hpp Categoriess(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategories
https://www.mediawiki.org/wiki/API:Categories

Example:

Request:
https://ru.wikinews.org/w/api.php?action=query&prop=categories&pageids=89144|89195&clprop=sortkey|timestamp|hidden

Response:
{
    "continue": {
        "clcontinue": "89195|5_\u0444\u0435\u0432\u0440\u0430\u043b\u044f_2016",
        "continue": "||"
    },
    "query": {
        "pages": {
            "89144": {
                "pageid": 89144,
                "ns": 0,
                "title": "Lookout: \u0425\u0440\u0430\u043d\u044f\u0449\u0438\u0435\u0441\u044f \u043d\u0430 \u0441\u043c\u0430\u0440\u0442\u0444\u043e\u043d\u0430\u0445 \u0434\u0430\u043d\u043d\u044b\u0435 \u0432 \u0441\u0440\u0435\u0434\u043d\u0435\u043c \u043e\u0446\u0435\u043d\u0438\u0432\u0430\u044e\u0442\u0441\u044f \u0432 $14 \u0442\u044b\u0441.",
                "categories": [
                    {
                        "ns": 14,
                        "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:5 \u0444\u0435\u0432\u0440\u0430\u043b\u044f 2016",
                        "sortkey": "3d43433b434f4d085b045ce0b40a94ff5d4523035c5a34baff5d4503045c940a03045cba8e0ab4c0dea4940ae003045c240a9494ff5d2f035c3403045c1803045cbab4342494348e03045ca4f834945a180aff5d3f035cc0baff5d4503045c1803040f0e141a045cc0ff5d2f035cba030901450d018f7e8f301800",
                        "sortkeyprefix": "",
                        "timestamp": "2016-02-05T08:06:59Z"
                    },
                    {
                        "ns": 14,
                        "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\u0411\u0435\u0437\u043e\u043f\u0430\u0441\u043d\u043e\u0441\u0442\u044c",
                        "sortkey": "3d43433b434f4d085b045ce0b40a94ff5d4523035c5a34baff5d4503045c940a03045cba8e0ab4c0dea4940ae003045c240a9494ff5d2f035c3403045c1803045cbab4342494348e03045ca4f834945a180aff5d3f035cc0baff5d4503045c1803040f0e141a045cc0ff5d2f035cba030901450d018f7e8f301800",
                        "sortkeyprefix": "",
                        "timestamp": "2016-02-05T08:06:59Z"
                    },

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
#include "PageRevisions.hpp"

class Categories {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string clprop;       /*    Which additional properties to get for each category: sortkey       Adds the sortkey (hexadecimal string) and sortkey prefix (human-readable part) for the category. timestamp Adds timestamp of when the category was added. hidden Tags categories that are hidden with __HIDDENCAT__. Values (separate with |): sortkey, timestamp, hidden*/
  string clshow;       /* Which kind of categories to show. Values (separate with |): hidden, !hidden*/
  string cllimit;      /* How many categories to return. No more than 500 (5,000 for bots) allowed. Type: integer or max Default: 10*/
  string clcontinue;   /* When more results are available, use this to continue.*/ 
  string clcategories; /* Only list these categories. Useful for checking whether a certain page is in a certain category. Separate values with |. Maximum number of values is 50 (500 for bots).*/
  string cldir;        /* The direction in which to list. One of the following values: ascending, descending Default: ascending */ 
  string pageids;
  string titles;

/*
  long int pageid = -1;
  int ns = -1;
*/
 
  // Response
  string batchcomplete;
  vector <PageRevisions> pages;
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
   titles = "";
   //pageid = -1;
   //ns = -1;

   batchcomplete = "";
   pages.clear();
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
   for(auto ipro : pagesJson) {
    PageRevisions pageRevisions(ipro.second);
    pages.push_back(pageRevisions);
/*
    auto resJson = page.second; 
    title = resJson["title"].string_value();
    ns = resJson["ns"].int_value();
    pageid = resJson["pageid"].int_value();
    auto categoriesJson = resJson["categories"].array_items();
    for(auto ipr : categoriesJson) {
     Category itemCategories(ipr);
     items.push_back(itemCategories);
    }
*/
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
 
