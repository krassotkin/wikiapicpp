#ifndef MEDIAWIKIACTIONAPI_HPP
#define MEDIAWIKIACTIONAPI_HPP

/*
 MediaWikiActionAPI.hpp is a  С++ interface to The MediaWiki action API.

 The MediaWiki action API: https://www.mediawiki.org/wiki/API:Main_page 
 The MediaWiki action API Help: https://en.wikipedia.org/w/api.php
 The MediaWiki action API Sandbox: https://en.wikipedia.org/wiki/Special:ApiSandbox

 Public Domain by authors: Alexander Krassotkin, Simon Krassotkin
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// shared
#include "CurlWrapper.hpp"

// api
#include "LoginInfo.hpp"

class MediaWikiActionAPI {

 private:

  CurlWrapper curlWrapper;

 public:

  static const string versionMajor;
  static const string versionMinor;

  const string endpointPart = "w/api.php";
  const string formatPart = "&format=json";

  MediaWikiActionAPI() {}

/*
 Login: 
https://en.wikipedia.org/w/api.php?action=help&modules=login
https://www.mediawiki.org/wiki/API:Login 
*/
  void login(LoginInfo* loginInfo) {
   bool firstPass = true;
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=login&lgname="+loginInfo->lgusername+"&lgpassword="+loginInfo->lgpassword;
   if(loginInfo->result.compare("NeedToken")==0) {
    firstPass = false;
    fullUrl+="&lgtoken="+loginInfo->token;
   }
   fullUrl+= formatPart;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   loginInfo->fromJsonString(res);
   if(firstPass && loginInfo->result.compare("NeedToken")==0) this->login(loginInfo);
  }

/*
 Logout:
https://en.wikipedia.org/w/api.php?action=help&modules=logout
https://www.mediawiki.org/wiki/API:Logout
*/
  void logout(LoginInfo* loginInfo) {
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=logout";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   loginInfo->clear();
  }

};

const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP
 
