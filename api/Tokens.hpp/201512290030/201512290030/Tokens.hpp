#ifndef TOKENS_HPP
#define TOKENS_HPP
/*
 Tokens.hpp represent information about tokens of The MediaWiki action API.

 Help:
https://en.wikinews.org/w/api.php?action=help&modules=query%2Btokens
https://en.wikipedia.org/w/api.php?action=help&query=tokens
https://en.wikipedia.org/w/api.php?action=help&modules=tokens

  type
    Values (separate with |): block, centralauth, csrf, delete, deleteglobalaccount, edit, email, import, move, options, patrol, protect, rollback, setglobalaccountstatus, unblock, userrights, watch
                              createaccount, csrf, deleteglobalaccount, login, patrol, rollback, setglobalaccountstatus, userrights, watch

 Example:

request:
https://ru.wikinews.org/w/api.php?action=query&meta=tokens&type=csrf&format=json

response:
{"batchcomplete":"","query":{"tokens":{"csrftoken":"b772ba1230aea7cb3fe762612e35fed65692930f+\\"}}}

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

class Tokens {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const string allTokens = "block|centralauth|createaccount|csrf|delete|deleteglobalaccount|edit|email|import|login|move|options|patrol|protect|rollback|setglobalaccountstatus|unblock|userrights|watch";

  // Request
  string type;
  
  // Response
  string batchcomplete;
  string blocktoken;
  string centralauthtoken;  
  string createaccounttoken; 
  string csrftoken;
  string deletetoken;
  string deleteglobalaccounttoken;
  string edittoken;
  string emailtoken;
  string importtoken;
  string logintoken;
  string movetoken;
  string optionstoken;
  string patroltoken;
  string protecttoken;
  string rollbacktoken;
  string setglobalaccountstatustoken;
  string unblocktoken;
  string userrightstoken;
  string watchtoken;
  string errJson;

  Tokens() {}
  
  Tokens(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Tokens(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   batchcomplete.clear();
   errJson.clear();
   createaccounttoken.clear(); 
   csrftoken.clear();
   deletetoken.clear();
   deleteglobalaccounttoken.clear();
   edittoken.clear();
   emailtoken.clear();
   importtoken.clear();
   logintoken.clear();
   movetoken.clear();
   optionstoken.clear();
   patroltoken.clear();
   protecttoken.clear();
   rollbacktoken.clear();
   setglobalaccountstatustoken.clear();
   unblocktoken.clear();
   userrightstoken.clear();
   watchtoken.clear();
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto queryJson = json["query"].object_items();
   auto tokens = queryJson["tokens"].object_items();
   string csrftokenTmp = tokens["csrftoken"].string_value();
   string createaccounttokenTmp = tokens["createaccounttoken"].string_value();
   string deletetokenTmp = tokens["deletetoken"].string_value();
   string deleteglobalaccounttokenTmp = tokens["deleteglobalaccounttoken"].string_value();
   string edittokenTmp = tokens["edittoken"].string_value();
   string emailtokenTmp = tokens["emailtoken"].string_value();
   string importtokenTmp = tokens["importtoken"].string_value();
   string logintokenTmp = tokens["logintoken"].string_value();
   string movetokenTmp = tokens["movetoken"].string_value();
   string optionstokenTmp = tokens["optionstoken"].string_value();
   string patroltokenTmp = tokens["patroltoken"].string_value();
   string protecttokenTmp = tokens["protecttoken"].string_value();
   string rollbacktokenTmp = tokens["rollbacktoken"].string_value();
   string setglobalaccountstatustokenTmp = tokens["setglobalaccountstatustoken"].string_value();
   string unblocktokenTmp = tokens["unblocktoken"].string_value();
   string userrightstokenTmp = tokens["userrightstoken"].string_value();
   string watchtokenTmp = tokens["watchtoken"].string_value();
   csrftoken = (csrftokenTmp.length()>0) ? csrftokenTmp : csrftoken;
   createaccounttoken = (createaccounttokenTmp.length()>0) ? createaccounttokenTmp : createaccounttoken;
   deletetoken = (deletetokenTmp.length()>0) ? deletetokenTmp : deletetoken;
   deleteglobalaccounttoken = (deleteglobalaccounttokenTmp.length()>0) ? deleteglobalaccounttokenTmp : deleteglobalaccounttoken;
   edittoken = (edittokenTmp.length()>0) ? edittokenTmp : edittoken;
   emailtoken = (emailtokenTmp.length()>0) ? emailtokenTmp : emailtoken;
   importtoken = (importtokenTmp.length()>0) ? importtokenTmp : importtoken;
   logintoken = (logintokenTmp.length()>0) ? logintokenTmp : logintoken;
   movetoken = (movetokenTmp.length()>0) ? movetokenTmp : movetoken;
   optionstoken = (optionstokenTmp.length()>0) ? optionstokenTmp : optionstoken;
   patroltoken = (patroltokenTmp.length()>0) ? patroltokenTmp : patroltoken;
   protecttoken = (protecttokenTmp.length()>0) ? protecttokenTmp : protecttoken; 
   rollbacktoken = (rollbacktokenTmp.length()>0) ? rollbacktokenTmp : rollbacktoken;
   setglobalaccountstatustoken = (setglobalaccountstatustokenTmp.length()>0) ? setglobalaccountstatustokenTmp : setglobalaccountstatustoken;
   unblocktoken = (unblocktokenTmp.length()>0) ? unblocktokenTmp : unblocktoken;
   userrightstoken = (userrightstokenTmp.length()>0) ? userrightstokenTmp : userrightstoken;
   watchtokenTmp = (watchtokenTmp.length()>0) ? watchtokenTmp : watchtoken; 
  }
  
  string toJson() {
   /* not implemented */
   return "{\"not implemented\":\"not implemented\"}";
  }

};

const string Tokens::versionMajor = "201512290030";
const string Tokens::versionMinor = "201512290030";

#endif // #ifndef TOKENS_HPP
 
