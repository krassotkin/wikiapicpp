#ifndef EDIT_HPP
#define EDIT_HPP
/*
 Edit.hpp represent a edit request and response of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp edit(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=edit
https://www.mediawiki.org/wiki/API:Edit

 Success response example:
{"edit":{"result":"Success","pageid":88512,"title":"\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Test/Test","contentmodel":"wikitext","oldrevid":422740,"newrevid":422741,"newtimestamp":"2016-01-23T06:18:13Z"}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

class Edit {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string errJson;

  // Request
  string title; // Title of the page to edit. Cannot be used together with pageid. 
  long int pageid = -1; // Page ID of the page to edit. Cannot be used together with title. 
  long int section = -1; // Section number. 0 for the top section, new for a new section. 
  string sectiontitle; // The title for a new section. 
  string text; // Page content. 
  string summary; // Edit summary. Also section title when section=new and sectiontitle is not set. 
  string tags; // Change tags to apply to the revision. Values (separate with |): WPCleaner, huggle
  int minor = -1; // Minor edit. 
  int notminor = -1; // Non-minor edit. 
  int bot = -1; // Mark this edit as bot. 
  string basetimestamp; // Timestamp of the base revision, used to detect edit conflicts.
  string starttimestamp; // Timestamp when the editing process began, used to detect edit conflicts. 
                         // An appropriate value may be obtained using curtimestamp when beginning 
                         // the edit process (e.g. when loading the page content to edit). 
  int recreate = -1; // Override any errors about the page having been deleted in the meantime. 
  int createonly = -1; // Don't edit the page if it exists already. 
  int nocreate = -1; // Throw an error if the page doesn't exist. 
  string watchlist; // One of the following values: watch, unwatch, preferences, nochange
  string md5; // The MD5 hash of the text parameter, or the prependtext and appendtext parameters 
              // concatenated. If set, the edit won't be done unless the hash is correct. 
  string prependtext; // Add this text to the beginning of the page. Overrides text. 
  string appendtext; // Add this text to the end of the page. Overrides text.
                     // Use section=new to append a new section, rather than this parameter. 
  long int undo = -1; // Undo this revision. Overrides text, prependtext and appendtext. 
  long int undoafter = -1; // Undo all revisions from undo to this one. If not set, just undo one revision. 
  int redirect = -1; // Automatically resolve redirects. 
  string contentformat; // Content serialization format used for the input text. 
                        // One of the following values: 
                        // application/json, text/x-wiki, text/javascript, text/css, text/plain
  string contentmodel; // Content model of the new content. 
                       // One of the following values: 
                       // GadgetDefinition, MassMessageListContent, wikitext, 
                       // javascript, json, css, text, SecurePoll, flow-board, Scribunto, JsonSchema
  string token; // A "csrf" token retrieved from action=query&meta=tokens
                // The token should always be sent as the last parameter, 
                // or at least after the text parameter. 
  string captchaword; // Answer to the CAPTCHA 
  string captchaid; // CAPTCHA ID from previous request 

  // Response
  string response;
  string result;
  long int pageidres = -1;
  string titleres;
  string contentmodelres;
  long int oldrevidres = -1;
  long int newrevidres = -1;
  string newtimestampres;

  Edit() {}
  
  Edit(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Edit(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   title = "";
   pageid = -1;
   section = -1;
   sectiontitle = "";
   text = "";
   summary = "";
   tags = "";
   minor = -1;
   notminor = -1;
   bot = -1;
   basetimestamp = "";
   starttimestamp = "";
   recreate = -1;
   createonly = -1;
   nocreate = -1;
   watchlist = "";
   md5 = "";
   prependtext = "";
   appendtext = "";
   undo = -1; 
   undoafter = -1;
   redirect = -1;
   contentformat = "";
   contentmodel = "";
   token = "";
   captchaword = "";
   captchaid = "";

   response = "";
   result = "";
   pageidres = -1;
   titleres = "";
   contentmodelres = "";
   oldrevidres = -1;
   newrevidres = -1;
   newtimestampres = "";
  }
  
  void fromJsonString(const string& jsonString) {
   response = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   auto editJson = json["edit"].object_items();
   result = editJson["result"].string_value();
   //cout << "Edit::fromJson result" << result << endl;
   pageidres = editJson["pageid"].int_value();
   titleres = editJson["title"].string_value();
   contentmodelres = editJson["contentmodel"].string_value();
   oldrevidres = editJson["oldrevid"].int_value();
   newrevidres = editJson["newrevid"].int_value();
   newtimestampres = editJson["newtimestamp"].string_value();
  }

  bool isSuccess() {
   return result.compare("Success") == 0;
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string Edit::versionMajor = "201512290030";
const string Edit::versionMinor = "201512290030";

#endif // #ifndef EDIT_HPP
 
