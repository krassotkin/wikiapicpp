#ifndef CREATEACCOUNT_HPP
#define CREATEACCOUNT_HPP
/*
 CreateAccount.hpp represent a create a new user account of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp CreateAccount(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=createaccount
https://www.mediawiki.org/wiki/API:Account_creation

 Success response example:
{"createaccount": { "result": "Success", "token": "8217b293a6bd0bba84cc1cb661a06a5d", "userid": 1234, "username": "Foo" } }

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
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

class CreateAccount : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Request
  string captchaid;                 /* CAPTCHA ID from previous request */
  string captchaword;               /* Answer to the CAPTCHA */
  string domain;                    /* Domain for external authentication (optional). */
  string email;                     /* Email address of user (optional). */
  long int ignoreantispoof=-1;      /* Ignore spoofing checks (requires the override-antispoof right). Type: boolean (details)*/
  long int ignoretitleblacklist=-1; /* Ignore spoofing checks (requires one of the following rights: tboverride, tboverride-account)  Type: boolean (details) */
  string language;                  /* Language code to set as default for the user (optional, defaults to content language). */
  long int mailpassword=-1;         /* If set to any value, a random password will be emailed to the user. Type: boolean (details).*/
  string name;                      /* Username. This parameter is required. Type: user name. */
  string realname;                  /* Real name of user (optional). */
  string reason;                    /* Optional reason for creating the account to be put in the logs. */
  string password;                  /* Password (ignored if mailpassword is set). */
  string site;
  string token;                     /* A "createaccount" token retrieved from action=query&meta=tokens */
  
  // Response
  string captchaId;
  string captchaQuestion;
  string captchaType;
  string captchaUrl;
  string resId;
  string resName;
  string resToken;
  string result;

  void clearRequest() {
   captchaid.clear();
   captchaword.clear();
   domain.clear();
   email.clear();
   ignoreantispoof = -1;
   ignoretitleblacklist = -1;
   language.clear();
   mailpassword = -1;
   name.clear();
   realname.clear();
   reason.clear();
   password.clear();
   site.clear();
   token.clear();
  }
   
  void clearResponse() {
   captchaId.clear();
   captchaQuestion.clear();
   captchaType.clear();
   captchaUrl.clear();
   resId.clear();
   resName.clear();
   resToken.clear();
   result.clear();
  }

  void clearServo() {}

  void fromJsonSub(const json11::Json& json) {
   auto createAccountJson = json["createaccount"].object_items();
   result = createAccountJson["result"].string_value();
   auto captcha = createAccountJson["captcha"].object_items();
   captchaId = captcha["id"].string_value();
   captchaUrl = captcha["url"].string_value();
   resId = createAccountJson["userid"].int_value();
   resName = createAccountJson["username"].string_value();
  }

  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string CreateAccount::versionMajor = "201512290030";
const string CreateAccount::versionMinor = "201512290030";

#endif // #ifndef CREATEACCOUNT_HPP
 
