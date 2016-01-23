#ifndef ROLLBACK_HPP
#define ROLLBACK_HPP
/*
 Rollback.hpp represent a rollback request and response of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp edit(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=rollback
https://www.mediawiki.org/wiki/API:Rollback

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), DonSimon
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

class Rollback {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string errJson;

  // Request
   string title; //Title of the page to roll back. Cannot be used together with pageid. 
   string pageid; //Page ID of the page to roll back. Cannot be used together with title.
   string user; //Name of the user whose edits are to be rolled back.
   string summary; //Custom edit summary. If empty, default summary will be used.
   int markbot=-1; //Mark the reverted edits and the revert as bot edits.
   string watchlist; //Unconditionally add or remove the page from the current user's watchlist, use preferences or do not change watch.

  // Response
   string response;
   string result;
   string titleres;
   string pageidres;
   string summaryres; 
   string revid;
   string old_revid;
   string last_revid; 

  Rollback() {}
  
  Rollback(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Rollback(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   title = ""; 
   pageid = "";
   user = "";
   summary = "";
   markbot=-1;
   watchlist = "";

   titleres = "";
   pageidres = "";
   summaryres = ""; 
   revid = "";
   old_revid = "";
   last_revid = ""; 

   response = "";
   result = "";
   
  }
  
  void fromJsonString(const string& jsonString) {
   response = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   auto rollbackJson = json["rollback"].object_items();
   //cout << "Rollback::fromJson result" << result << endl;
   pageidres = rollbackJson["pageid"].int_value();
   titleres = rollbackJson["title"].string_value();
   summaryres = rollbackJson["summary"].string_value();
   revid = rollbackJson["revid"].int_value();
   old_revid = rollbackJson["old_revid"].int_value();
   last_revid = rollbackJson["last_revid"].string_value();
  }

  bool isSuccess() {
   return result.compare("Success") == 0;
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Rollback::versionMajor = "201512290030";
const string Rollback::versionMinor = "201512290030";

#endif // #ifndef ROLLBACK_HPP
 
