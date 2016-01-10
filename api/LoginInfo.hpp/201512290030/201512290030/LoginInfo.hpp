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

  string cookieprefix;
  string errJson;
  string lgname;
  string lgpassword;
  string lgtoken;
  long int lguserid;
  string lgusername;
  string result;
  string sessionid;
  string site;
  string token;

  LoginInfo() {}
  
  LoginInfo(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  LoginInfo(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   cookieprefix="";
   errJson="";
   lgname="";
   lgpassword="";
   lgtoken="";
   lguserid=0;
   lgusername="";
   result="";
   sessionid="";
   site="";
   token="";
  }

  bool isLogin() {
   return (result.compare("Success") == 0);
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   json11::Json::object login = json["login"].object_items();
   cookieprefix = login["cookieprefix"].string_value();
   string tmpToken = login["token"].string_value();
   if(tmpToken.length()!=0) token = tmpToken;
   lgtoken = login["lgtoken"].string_value();
   lguserid = login["lguserid"].int_value();
   string username = login["lgusername"].string_value();
   lgusername = (username.length()>0) ? username : lgusername;
   result = login["result"].string_value();
   sessionid = login["sessionid"].string_value();
  }
  
  string toJson() {
   if(result.compare("NeedToken")==0) {
    return "{\"login\":{\"result\":\""+result+"\","+"\"token\":\""+token+"\","+"\"cookieprefix\":\""+cookieprefix+"\","+"\"sessionid\":\""+sessionid+"\"}}";
   } else {
    return "{\"login\":{\"result\":\""+result+"\","+"\"lguserid\":"+to_string(lguserid)+","+"\"lgusername\":\""+lgusername+"\","+"\"lgtoken\":\""+lgtoken+"\","+"\"cookieprefix\":\""+cookieprefix+"\","+"\"sessionid\":\""+sessionid+"\"}}";
   }
  }

};

const string LoginInfo::versionMajor = "201512290030";
const string LoginInfo::versionMinor = "201512290030";

#endif // #ifndef LOGININFO_HPP
 
