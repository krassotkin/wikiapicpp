#ifndef MEDIAWIKIACTIONAPI_HPP
#define MEDIAWIKIACTIONAPI_HPP

/*
 MediaWikiActionAPI.hpp is a  С++ interface to The MediaWiki action API.

 The MediaWiki action API: https://www.mediawiki.org/wiki/API:Main_page 
 The MediaWiki action API Help: https://en.wikipedia.org/w/api.php
 The MediaWiki action API Sandbox: https://en.wikipedia.org/wiki/Special:ApiSandbox

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
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
#include "Revisions.hpp"

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

/*
 Get revision information.

 May be used in several ways:

 1. Get data about a set of pages (last revision), by setting titles or pageids.
 2. Get revisions for one given page, by using titles or pageids with start, end, or limit.
 3. Get data about a set of revisions by setting their IDs with revids.

https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:Revisions
*/
  void revisions(LoginInfo* loginInfo, Revisions* revisions) {
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=query&prop=revisions";
   fullUrl+= "&" + (revisions->titles.length()>0 ? revisions->titles : revisions->pageids);
   fullUrl+= revisions->rvprop.length()==0 ? "" : "&rvprop=" + revisions->rvprop;
   fullUrl+= "&rvlimit=" + to_string(revisions->rvlimit);
   fullUrl+= "&rvexpandtemplates=" + to_string(revisions->rvexpandtemplates);
   fullUrl+= "&rvparse=" + to_string(revisions->rvparse);
   fullUrl+= "&rvsection=" + to_string(revisions->rvsection);
   fullUrl+= "&rvdiffto=" + to_string(revisions->rvdiffto);
   fullUrl+= "&rvdifftotext=" + to_string(revisions->rvdifftotext);
   fullUrl+= "&rvdifftotextpst=" + to_string(revisions->rvdifftotextpst);
   fullUrl+= revisions->rvcontentformat.length()==0 ? "" : "&rvcontentformat=" + revisions->rvcontentformat;
   fullUrl+= "&rvstartid=" + to_string(revisions->rvstartid);
   fullUrl+= "&rvendid=" + to_string(revisions->rvendid);
   fullUrl+= revisions->rvstart.length()==0 ? "" : "&rvstart=" + revisions->rvstart;
   fullUrl+= revisions->rvend.length()==0 ? "" : "&rvend=" + revisions->rvend;
   fullUrl+= revisions->rvdir.length()==0 ? "" : "&rvdir=" + revisions->rvdir;
   fullUrl+= revisions->rvuser.length()==0 ? "" : "&rvuser=" + revisions->rvuser;
   fullUrl+= revisions->rvexcludeuser.length()==0 ? "" : "&rvexcludeuser=" + revisions->rvexcludeuser;
   fullUrl+= revisions->rvtag.length()==0 ? "" : "&rvtag=" + revisions->rvtag;
   fullUrl+= revisions->rvcontinue.length()==0 ? "" : "&rvcontinue=" + revisions->rvcontinue;
   fullUrl+= formatPart;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   revisions->fromJsonString(res);
  } 

};

const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP
 
