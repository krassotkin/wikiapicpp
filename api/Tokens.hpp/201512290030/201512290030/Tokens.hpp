#ifndef TOKENS_HPP
#define TOKENS_HPP
/*
 Tokens.hpp represent information about tokens of The MediaWiki action API.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=tokens
https://en.wikinews.org/w/api.php?action=help&modules=query%2Btokens

  type
    Values (separate with |): block, centralauth, csrf, delete, deleteglobalaccount, edit, email, import, move, options, patrol, protect, rollback, setglobalaccountstatus, unblock, userrights, watch

 Example:

request:
https://ru.wikinews.org/w/api.php?action=query&meta=tokens&type=csrf&format=json

response:
{"batchcomplete":"","query":{"tokens":{"csrftoken":"b772ba1230aea7cb3fe762612e35fed65692930f+\\"}}}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
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

  string batchcomplete;
  string csrftoken;
  string errJson;

  Tokens() {}
  
  Tokens(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Tokens(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   batchcomplete = "";
   errJson = "";
   csrftoken = "";
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
   csrftoken = (csrftokenTmp.length()>0) ? csrftokenTmp : csrftoken;
  }
  
  string toJson() {
   /* not implemented */
   return "{\"not implemented\":\"not implemented\"}";
  }

};

const string Tokens::versionMajor = "201512290030";
const string Tokens::versionMinor = "201512290030";

#endif // #ifndef TOKENS_HPP
 
