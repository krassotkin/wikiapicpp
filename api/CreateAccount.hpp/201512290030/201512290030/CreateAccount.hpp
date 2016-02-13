#ifndef CREATEACCOUNT_HPP
#define CREATEACCOUNT_HPP
/*
 CreateAccount.hpp represent a create a new user account.  of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp CreateAccount(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=createaccount
https://www.mediawiki.org/wiki/API:Account_creation

 Success response example:
{ "createaccount": { "result": "Success", "token": "8217b293a6bd0bba84cc1cb661a06a5d", "userid": 1234, "username": "Foo" } }

 Public Domain by authors: Alexander Krassotkin, Simon Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

class CreateAccount {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string errJson;

  // Request
  string site;
  string name;                     /* Username. This parameter is required. Type: user name. */
  string password;                 /* Password (ignored if mailpassword is set). */
  string domain;                   /* Domain for external authentication (optional). */
  string token;                    /* A "createaccount" token retrieved from action=query&meta=tokens */
  string email;                    /* Email address of user (optional). */
  string realname;                 /* Real name of user (optional). */
  long int mailpassword=-1;        /* If set to any value, a random password will be emailed to the user. Type: boolean (details).*/
  string reason;                   /* Optional reason for creating the account to be put in the logs. */
  string language;                 /* Language code to set as default for the user (optional, defaults to content language). */
  long int ignoreantispoof=-1;     /* Ignore spoofing checks (requires the override-antispoof right). Type: boolean (details)*/
  long int ignoretitleblacklist=-1;/* Ignore spoofing checks (requires one of the following rights: tboverride, tboverride-account)  Type: boolean (details) */
  string captchaword;              /* Answer to the CAPTCHA */
  string captchaid;                /* CAPTCHA ID from previous request */

  // Response
  string response;
  string result;
  string resToken;
  string resName;
  string resId;
  string captchaType;
  string captchaQuestion;
  string captchaUrl;
  string captchaId;

  CreateAccount() {}
  
  CreateAccount(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  CreateAccount(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   name = "";
   password = "";
   domain = "";
   token = "";
   email = "";
   realname = "";
   mailpassword = -1;
   reason = "";
   language = "";
   ignoreantispoof = -1;
   ignoretitleblacklist = -1;
   captchaword = "";
   captchaid = "";

   response = "";
   result = "";
   resToken = "";
   resName = "";
   resId = "";
   captchaType = "";
   captchaQuestion = "";
   captchaUrl = "";
   captchaId = "";
  }
  
  void fromJsonString(const string& jsonString) {
   response = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   auto createAccountJson = json["createaccount"].object_items();
   result = createAccountJson["result"].string_value();
   auto captcha = createAccountJson["captcha"].object_items();
   captchaId = captcha["id"].string_value();
   captchaUrl = captcha["url"].string_value();
   //cout<<"CreateAccount:: captchaId : " << captchaId << endl;
   //cout<<"CreateAccount:: captchaUrl : " << captchaUrl << endl;
   resId = createAccountJson["userid"].int_value();
   resName = createAccountJson["username"].string_value();
  }

  string toJson() {
   /* not implemented */
   return "";
  }

};

const string CreateAccount::versionMajor = "201512290030";
const string CreateAccount::versionMinor = "201512290030";

#endif // #ifndef CREATEACCOUNT_HPP
 
