#ifndef ROLLBACK_HPP
#define ROLLBACK_HPP
/*
 Rollback.hpp represent a rollback request and response of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp edit(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=rollback
https://www.mediawiki.org/wiki/API:Rollback

 Public Domain by authors: Simon Krassotkin, Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"

class Rollback : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;
   
  // Request
  int markbot=-1;   /* Mark the reverted edits and the revert as bot edits. */
  string pageid;    /* Page ID of the page to roll back. Cannot be used together with title. */
  string summary;   /* Custom edit summary. If empty, default summary will be used. */
  string title;    /* Title of the page to roll back. Cannot be used together with pageid. */
  string user;      /* Name of the user whose edits are to be rolled back. */
  string watchlist; /* Unconditionally add or remove the page from the current user's watchlist, use preferences or do not change watch. */
    
  // Response
  string last_revid;  
  string old_revid;
  string pageidres;
  string revid;
  string summaryres;
  string titleres;

  Rollback() : MediaWikiActionAPIParameters() {}   
  Rollback(const string& jsonString) : MediaWikiActionAPIParameters(jsonString) {} 
  Rollback(const json11::Json& json) : MediaWikiActionAPIParameters(json) {}

  void clearRequest() {
   markbot=-1;
   pageid.clear();
   summary.clear();
   title.clear(); 
   user.clear();
   watchlist.clear();
  }

  void clearResponse() {
   last_revid.clear();
   old_revid.clear(); 
   pageidres.clear();
   revid.clear();
   summaryres.clear();
   titleres.clear();    
  }

  void clearServo() {}
  
  void fromJson(const json11::Json& json) {
   auto rollbackJson = json["rollback"].object_items();
   pageidres = rollbackJson["pageid"].int_value();
   titleres = rollbackJson["title"].string_value();
   summaryres = rollbackJson["summary"].string_value();
   revid = rollbackJson["revid"].int_value();
   old_revid = rollbackJson["old_revid"].int_value();
   last_revid = rollbackJson["last_revid"].string_value();
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Rollback::versionMajor = "201512290030";
const string Rollback::versionMinor = "201512290030";

#endif // #ifndef ROLLBACK_HPP
 
