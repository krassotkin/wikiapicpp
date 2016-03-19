#ifndef CategoryMembers_HPP
#define CategoryMembers_HPP
/*
 CategoryMembers.hpp represent list all pages in a given category. 

 Processed by MediaWikiActionAPI.hpp CategoryMemberss(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategorymembers
https://www.mediawiki.org/wiki/API:Categorymembers

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
#include "CategoryMember.hpp"

class CategoryMembers {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string cmtitle;              /* Which category to enumerate (required). Must include the Category: prefix. Cannot be used together with cmpageid. */
  long int cmpageid = -1;      /* Page ID of the category to enumerate. Cannot be used together with cmtitle. Type: integer*/
  string cmprop;               /* Which pieces of information to include: ids Adds the page ID. title Adds the title and namespace ID of the page. sortkey Adds the sortkey used for sorting in the category (hexadecimal string). sortkeyprefix Adds the sortkey prefix used for sorting in the category (human-readable part of the sortkey). type Adds the type that the page has been categorised as (page, subcat or file). timestamp Adds the timestamp of when the page was included. Values (separate with |): ids, title, sortkey, sortkeyprefix, type, timestamp Default: ids|title*/
  long int cmnamespace=-1;     /* Only include pages in these namespaces. Note that cmtype=subcat or cmtype=file may be used instead of cmnamespace=14 or 6. Note: Due to miser mode, using this may result in fewer than cmlimit results returned before continuing; in extreme cases, zero results may be returned.  Values (separate with |): 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600*/
  string cmtype;               /* Which type of category members to include. Ignored when cmsort=timestamp is set. Values (separate with |): page, subcat, file Default: page|subcat|file*/
  string cmcontinue;           /* When more results are available, use this to continue.*/ 
  long int cmlimit=-1;         /* The maximum number of pages to return. No more than 500 (5,000 for bots) allowed. Type: integer or max Default: 10*/
  string cmsort;               /* Property to sort by. One of the following values: sortkey, timestamp    Default: sortkey*/
  string cmdir;                /* In which direction to sort. One of the following values: asc, desc, ascending, descending, newer, older Default: ascending*/
  string cmstart;              /* Timestamp to start listing from. Can only be used with cmsort=timestamp. Type: timestamp (allowed formats)*/
  string cmend;                /* Timestamp to end listing at. Can only be used with cmsort=timestamp.   Type: timestamp (allowed formats)*/
  string cmstarthexsortkey;    /* Sortkey to start listing from, as returned by cmprop=sortkey. Can only be used with cmsort=sortkey.*/ 
  string cmendhexsortkey;      /* Sortkey to end listing at, as returned by cmprop=sortkey. Can only be used with cmsort=sortkey.*/
  string cmstartsortkeyprefix; /* Sortkey prefix to start listing from. Can only be used with cmsort=sortkey. Overrides cmstarthexsortkey.*/ 
  string cmendsortkeyprefix;   /* Sortkey prefix to end listing before (not at; if this value occurs it will not be included!). Can only be used with cmsort=sortkey. Overrides cmendhexsortkey.*/ 
 
  // Response
  string batchcomplete;
  vector <CategoryMember> items;
  string res;
  string cmcontinue_res;
  string continue_res;

  CategoryMembers() {}
  
  CategoryMembers(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  CategoryMembers(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   cmtitle = "";
   cmpageid = -1;
   cmprop = "";
   cmnamespace = -1;
   cmtype = "";
   cmcontinue = "";
   cmlimit = -1;
   cmsort = "";
   cmdir = "";

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
   cmcontinue_res = firstContinueJson["cmcontinue"].string_value();
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto CategoryMembersJson = queryJson["categorymembers"].array_items();
   for(auto ipr : CategoryMembersJson) {
    CategoryMember itemCategoryMembers(ipr);
    items.push_back(itemCategoryMembers);
   }
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string CategoryMembers::versionMajor = "201512290030";
const string CategoryMembers::versionMinor = "201512290030";

#endif // #ifndef CategoryMembers_HPP
 
