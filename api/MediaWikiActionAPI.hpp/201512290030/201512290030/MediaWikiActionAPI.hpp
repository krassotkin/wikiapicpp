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

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// shared
#include "CurlWrapper.hpp"
#include "json11.hpp"

// api
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "PageRevisions.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"
#include "Rollback.hpp"
#include "Tokens.hpp"

class MediaWikiActionAPI {

 private:

  CurlWrapper curlWrapper;

 public:

  static const string versionMajor;
  static const string versionMinor;

  const string endpointPart = "w/api.php";
  const string formatPart = "&format=json";

  MediaWikiActionAPI() {}


/***************************************************************************
*                             Servo                                        *
***************************************************************************/

 string escape(const string& s) {
  string res;
  /*
  for(char c : s) {
   if(c == ' ') res+='_';
   else res += c;
  }
  return curlWrapper.escape(res);
  */
  return curlWrapper.escape(s);
 }

/***************************************************************************
*                              API                                         *
***************************************************************************/

/*
 Edit:
https://en.wikipedia.org/w/api.php?action=help&modules=edit
https://www.mediawiki.org/wiki/API:Edit

 See Edit.hpp for details.
*/
 void edit(LoginInfo* loginInfo, Tokens* tokens, Edit* edit) {
  if(loginInfo->site.length() == 0) return;
  if(tokens->csrftoken.length() == 0) getTokens(loginInfo, tokens, "csrf");
  string fullUrl = loginInfo->site+endpointPart+"?"+"action=edit"+formatPart;
  //cout << "\t\ttmwaapi::edit fullUrl: " << fullUrl << endl;
  string postFields = edit->title.length() > 0 ? "title="+escape(edit->title) : "pageid="+to_string(edit->pageid);
  postFields += edit->section == -1 ? "" : "&section="+to_string(edit->section);
  postFields += edit->sectiontitle.length() == 0 ? "" : "&sectiontitle="+escape(edit->sectiontitle);
  postFields += edit->text.length() == 0 ? "" : "&text="+escape(edit->text);
  postFields += edit->summary.length() == 0 ? "" : "&summary="+escape(edit->summary);
  postFields += edit->tags.length() == 0 ? "" : "&tags="+escape(edit->tags);
  postFields += edit->minor == -1 ? "" : "&minor="+to_string(edit->minor);
  postFields += edit->notminor == -1 ? "" : "&notminor="+to_string(edit->notminor);
  postFields += edit->bot == -1 ? "" : "&bot="+to_string(edit->bot);
  postFields += edit->basetimestamp.length() == 0 ? "" : "&basetimestamp="+escape(edit->basetimestamp);
  postFields += edit->starttimestamp.length() == 0 ? "" : "&starttimestamp="+escape(edit->starttimestamp);
  postFields += edit->recreate == -1 ? "" : "&recreate="+to_string(edit->recreate);
  postFields += edit->createonly == -1 ? "" : "&createonly="+to_string(edit->createonly);
  postFields += edit->nocreate == -1 ? "" : "&nocreate="+to_string(edit->nocreate);
  postFields += edit->watchlist.length() == 0 ? "" : "&watchlist="+escape(edit->watchlist);
  postFields += edit->md5.length() == 0 ? "" : "&md5="+escape(edit->md5);
  postFields += edit->prependtext.length() == 0 ? "" : "&prependtext="+escape(edit->prependtext);
  postFields += edit->appendtext.length() == 0 ? "" : "&appendtext="+escape(edit->appendtext);
  postFields += edit->undo == -1 ? "" : "&undo="+to_string(edit->undo);
  postFields += edit->undoafter == -1 ? "" : "&undoafter="+to_string(edit->undoafter);
  postFields += edit->redirect == -1 ? "" : "&redirect="+to_string(edit->redirect);
  postFields += edit->contentformat.length() == 0 ? "" : "&contentformat="+escape(edit->contentformat);
  postFields += edit->contentmodel.length() == 0 ? "" : "&contentmodel="+escape(edit->contentmodel);
  postFields += edit->captchaword.length() == 0 ? "" : "&captchaword="+escape(edit->captchaword);
  postFields += edit->captchaid.length() == 0 ? "" : "&captchaid="+escape(edit->captchaid);
  postFields += "&token="+escape(tokens->csrftoken);
  //cout << "\t\ttmwaapi::edit postFields: " << postFields << endl;
  string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
  //cout << "\t\tmwaapi::edit res: " << res << endl;
  edit->fromJsonString(res);
 }

/*
  Tokens:
https://en.wikipedia.org/w/api.php?action=help&modules=tokens
https://en.wikinews.org/w/api.php?action=help&modules=query%2Btokens

  type
    Values (separate with |): block, centralauth, csrf, delete, deleteglobalaccount, edit, email, import, move, options, patrol, protect, rollback, setglobalaccountstatus, unblock, userrights, watch
*/
  void getTokens(LoginInfo* loginInfo, Tokens* tokens, const string& type) {
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=query&meta=tokens&type="+type+formatPart;
   //cout << "\t\tmwaapi::getTokens fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::getTokens res: " << res << endl;
   tokens->fromJsonString(res);
  }

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
   //cout << "\t\tmwaapi::login res: " << res << endl;
   loginInfo->fromJsonString(res);
   if(firstPass && loginInfo->result.compare("NeedToken")==0) this->login(loginInfo);
   //cout << "\t\tmwaapi::login loginInfo->token: " << loginInfo->token << endl;
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
   fullUrl+= revisions->titles.length()>0 ? "&titles="+escape(revisions->titles) : "&pageids="+revisions->pageids;
   fullUrl+= revisions->rvprop.length()==0 ? "" : "&rvprop=" + revisions->rvprop;
   fullUrl+= revisions->rvlimit == -1 ? "" : "&rvlimit=" + to_string(revisions->rvlimit);
   fullUrl+= revisions->rvexpandtemplates == -1 ? "" : "&rvexpandtemplates=" + to_string(revisions->rvexpandtemplates);
   fullUrl+= revisions->rvparse == -1 ? "" : "&rvparse=" + to_string(revisions->rvparse);
   fullUrl+= revisions->rvsection == -1 ? "" : "&rvsection=" + to_string(revisions->rvsection);
   fullUrl+= revisions->rvdiffto == -1 ? "" : "&rvdiffto=" + to_string(revisions->rvdiffto);
   fullUrl+= revisions->rvdifftotext == -1 ? "" : "&rvdifftotext=" + to_string(revisions->rvdifftotext);
   fullUrl+= revisions->rvdifftotextpst == -1 ? "" : "&rvdifftotextpst=" + to_string(revisions->rvdifftotextpst);
   fullUrl+= revisions->rvcontentformat.length()==0 ? "" : "&rvcontentformat=" + revisions->rvcontentformat;
   fullUrl+= revisions->rvstartid == -1 ? "" : "&rvstartid=" + to_string(revisions->rvstartid);
   fullUrl+= revisions->rvendid == -1 ? "" : "&rvendid=" + to_string(revisions->rvendid);
   fullUrl+= revisions->rvstart.length()==0 ? "" : "&rvstart=" + revisions->rvstart;
   fullUrl+= revisions->rvend.length()==0 ? "" : "&rvend=" + revisions->rvend;
   fullUrl+= revisions->rvdir.length()==0 ? "" : "&rvdir=" + revisions->rvdir;
   fullUrl+= revisions->rvuser.length()==0 ? "" : "&rvuser=" + revisions->rvuser;
   fullUrl+= revisions->rvexcludeuser.length()==0 ? "" : "&rvexcludeuser=" + revisions->rvexcludeuser;
   fullUrl+= revisions->rvtag.length()==0 ? "" : "&rvtag=" + revisions->rvtag;
   fullUrl+= revisions->rvcontinue.length()==0 ? "" : "&rvcontinue=" + revisions->rvcontinue;
   fullUrl+= formatPart;
   //cout << "\t\ttmwaapi::revisions fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\ttmwaapi::revisions res: " << res << endl;
   revisions->fromJsonString(res);
  } 

/*
Undo the last edit to the page.

If the last user who edited the page made multiple edits in a row, they will all be rolled back. 

https://en.wikipedia.org/w/api.php?action=help&modules=rollback
https://www.mediawiki.org/wiki/API:Rollback
*/

  void rollback(LoginInfo* loginInfo, Tokens* tokens, Rollback* rollback) {
   if(loginInfo->site.length() == 0) return;
   if(tokens->rollbacktoken.length() == 0) getTokens(loginInfo, tokens, "rollback");
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=rollback";
   string postFields = rollback->title.length() > 0 ? "title="+escape(rollback->title) : "pageid="+escape(rollback->pageid);
   postFields += rollback->user.length() > 0 ? "&user="+escape(rollback->user) : "";
   postFields += rollback->summary.length() > 0 ? "&summary="+escape(rollback->summary) : "";
   postFields += rollback->markbot == -1 ? "" : "&markbot=" + rollback -> markbot;
   postFields += "&token="+escape(tokens->rollbacktoken);
   fullUrl+=formatPart;
   cout << "\t\ttmwaapi::rollback fullUrl: " << fullUrl << endl;
   cout << "\t\ttmwaapi::rollback postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   cout << "\t\ttmwaapi::rollback res: " << res << endl;
   rollback->fromJsonString(res);
  } 
 
  void undo(LoginInfo* loginInfo, Tokens* tokens, Edit* edit) {
   if(loginInfo->site.length() == 0) return;
   if(tokens->csrftoken.length() == 0) getTokens(loginInfo, tokens, "csrf");
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=edit"+formatPart;
   //cout << "\t\ttmwaapi::edit fullUrl: " << fullUrl << endl;
   string postFields = edit->title.length() > 0 ? "title="+escape(edit->title) : "pageid="+to_string(edit->pageid);
   postFields += edit->undo == -1 ? "" : "&undo="+to_string(edit->undo);
   postFields += "&token="+escape(tokens->csrftoken);
   //cout << "\t\ttmwaapi::edit postFields: " << postFields << endl;
   string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::edit res: " << res << endl;
   edit->fromJsonString(res);
  }

/*
  Thank:
https://www.mediawiki.org/wiki/Extension:Thanks#API_Documentation
https://en.wikipedia.org/w/api.php?action=help&modules=thank

  Must get csrf token before.
*/
  void thank(LoginInfo* loginInfo, Tokens* tokens, const string& revidString) {
   if(tokens->csrftoken.length() == 0) getTokens(loginInfo, tokens, "csrf");
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=thank&rev="+revidString+formatPart;
   //cout << "\t\tmwaapi::thank fullUrl: " << fullUrl << endl;
   string postFields = "token="+escape(tokens->csrftoken);
   //cout << "\t\tmwaapi::thank postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   cout << "\t\tmwaapi::thank res: " << res << endl;
  }

};

const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP
 
