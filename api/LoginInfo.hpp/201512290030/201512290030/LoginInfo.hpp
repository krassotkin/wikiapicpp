#ifndef LOGININFO_HPP
#define LOGININFO_HPP
/*
 LoginInfo.hpp represent login request and response of The MediaWiki action API.

 You must predefine site, lgusername, and lgpassword for login with MediaWikiActionAPI.hpp login(LoginInfo* loginInfo)

https://en.wikipedia.org/w/api.php?action=help&modules=login
https://www.mediawiki.org/wiki/API:LoginInfo .

First response:
{
    "login": {
        "result": "NeedToken",
        "token": "b5780b6e2f27e20b450921d9461010b4",
        "cookieprefix": "enwiki",
        "sessionid": "17ab96bd8ffbe8ca58a78657a918558e"
    }
}

Second response:
{
    "login": {
        "result": "Success",
        "lguserid": 12345,
        "lgusername": "Bob",
        "lgtoken": "b5780b6e2f27e20b450921d9461010b4",
        "cookieprefix": "enwiki",
        "sessionid": "17ab96bd8ffbe8ca58a78657a918558e"
    }
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

class LoginInfo {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Servo
  string errJson;

  // Request
  string lgname;
  string lgpassword;
  string site;

  // Response
  string res;                  /* Last parsed string response. */

  string cookieprefix;
  long int lguserid=-1;
  string lgusername;
  string result;
  string sessionid;

  LoginInfo() {}

  LoginInfo(const string& site, const string& lgname, const string& lgpassword) : lgname(lgname), lgpassword(lgpassword), site(site) {}
  
  LoginInfo(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  LoginInfo(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson.clear();

   lgname.clear();
   lgpassword.clear();
   site.clear();

   res.clear();
   cookieprefix.clear();
   lguserid=-1;
   lgusername.clear();
   result.clear();
   sessionid.clear();
  }

  LoginInfo clone() {
   LoginInfo loginInfo = cloneAccount();
   loginInfo.errJson = errJson;
   loginInfo.res = res;
   loginInfo.cookieprefix = cookieprefix;
   loginInfo.lguserid = lguserid;
   loginInfo.lgusername = lgusername;
   loginInfo.result = result;
   loginInfo.sessionid = sessionid;
   return loginInfo;
  }

  LoginInfo cloneAccount() {
   LoginInfo loginInfo(site, lgname, lgpassword);
   return loginInfo; 
  }

  bool isLogin() {
   return (result.compare("Success") == 0);
  }

  bool isSuccess() {
   return isLogin();
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   json11::Json::object login = json["login"].object_items();
   string tmpCooprefix = login["cookieprefix"].string_value();
   cookieprefix = (tmpCooprefix.length()>0) ? tmpCooprefix : cookieprefix;
   long tpmLguserid = login["lguserid"].int_value();
   lguserid = (tpmLguserid>0) ? tpmLguserid : lguserid;
   string tmpLgusername = login["lgusername"].string_value();
   lgusername = (tmpLgusername.length()>0) ? tmpLgusername : lgusername;
   result = login["result"].string_value();
   string tpmSessionid = login["sessionid"].string_value();
   sessionid = (tpmSessionid.length()>0) ? tpmSessionid : sessionid;
  }
  
  string toJson() {
    return "{\"login\":{\"result\":\""+result+"\","+"\"lguserid\":"+to_string(lguserid)+","+"\"lgusername\":\""+lgusername+"\","+"\"cookieprefix\":\""+cookieprefix+"\","+"\"sessionid\":\""+sessionid+"\"}}";
  }

  void update(const string& s, const string& n, const string& p) {
   clear();
   site = s, lgname = n, lgpassword = p;
  }

};

const string LoginInfo::versionMajor = "201512290030";
const string LoginInfo::versionMinor = "201512290030";

#endif // #ifndef LOGININFO_HPP
 
