#ifndef MEDIAWIKIACTIONAPI_HPP
#define MEDIAWIKIACTIONAPI_HPP

/*
 MediaWikiActionAPI.hpp is a  С++ interface to The MediaWiki action API.

 The MediaWiki action API: https://www.mediawiki.org/wiki/API:Main_page 
 The MediaWiki action API Help: https://en.wikipedia.org/w/api.php
 The MediaWiki action API Sandbox: https://en.wikipedia.org/wiki/Special:ApiSandbox

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin.
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
#include "Categories.hpp"
#include "Category.hpp"
#include "CategoryMembers.hpp"
#include "CategoryMember.hpp"
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "PageRevisions.hpp"
#include "Purge.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"
#include "Rollback.hpp"
#include "Search.hpp"
#include "SearchItem.hpp"
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
List all revisions

 Processed by MediaWikiActionAPI.hpp allrevisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Ballrevisions
https://www.mediawiki.org/wiki/API:Allrevisions
*/
  void allrevisions(LoginInfo* loginInfo, Revisions* revisions) {
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=query&list=allrevisions";
   fullUrl+= revisions->titles.length()>0 ? "&titles="+escape(revisions->titles) : "&pageids="+revisions->pageids;
   fullUrl+= revisions->prop.length()==0 ? "" : "&arvprop=" + revisions->prop;
   fullUrl+= revisions->limit == -1 ? "" : "&arvlimit=" + to_string(revisions->limit);
   fullUrl+= revisions->expandtemplates == -1 ? "" : "&arvexpandtemplates=" + to_string(revisions->expandtemplates);
   fullUrl+= revisions->parse == -1 ? "" : "&arvparse=" + to_string(revisions->parse);
   fullUrl+= revisions->section == -1 ? "" : "&arvsection=" + to_string(revisions->section);
   fullUrl+= revisions->diffto.length()==0 ? "" : "&arvdiffto=" + revisions->diffto;
   fullUrl+= revisions->difftotext.length()==0 ? "" : "&arvdifftotext=" + revisions->difftotext;
   fullUrl+= revisions->difftotextpst.length()==0 ? "" : "&arvdifftotextpst=" + revisions->difftotextpst;
   fullUrl+= revisions->contentformat.length()==0 ? "" : "&arvcontentformat=" + revisions->contentformat;
   fullUrl+= revisions->startid == -1 ? "" : "&arvstartid=" + to_string(revisions->startid);
   fullUrl+= revisions->endid == -1 ? "" : "&arvendid=" + to_string(revisions->endid);
   fullUrl+= revisions->start.length()==0 ? "" : "&arvstart=" + revisions->start;
   fullUrl+= revisions->end.length()==0 ? "" : "&arvend=" + revisions->end;
   fullUrl+= revisions->dir.length()==0 ? "" : "&arvdir=" + revisions->dir;
   fullUrl+= revisions->user.length()==0 ? "" : "&arvuser=" + revisions->user;
   fullUrl+= revisions->excludeuser.length()==0 ? "" : "&arvexcludeuser=" + revisions->excludeuser;
   fullUrl+= revisions->tag.length()==0 ? "" : "&arvtag=" + revisions->tag;
   fullUrl+= revisions->continue_req.length()==0 ? "" : "&arvcontinue=" + revisions->continue_req;
   fullUrl+= formatPart;
   //cout << "\t\tmwaapi::revisions fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::revisions res: " << res << endl;
   revisions->fromJsonString(res);
  } 
  
/*
 Categories

https://www.mediawiki.org/wiki/API:Categories
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategories

List all categories the pages belong to. 
*/
  void categories(LoginInfo* loginInfo, Categories* categories) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=query&prop=categories";
   fullUrl += categories->title.length() > 0 ? "&titles=" + escape(categories->title) : "";
   fullUrl += categories->clprop.length() > 0 ? "&clprop=" + escape(categories->clprop) : "";
   fullUrl += categories->clshow.length() > 0 ? "&clshow=" + escape(categories->clshow) : "";
   fullUrl += categories->cllimit.length() > 0 ? "&cllimit=" + escape(categories->cllimit) : "";
   fullUrl += categories->clcontinue.length() > 0 ? "&clcontinue=" + escape(categories->clcontinue) : "";
   fullUrl += categories->clcategories.length() > 0 ? "&clcategories=" + escape(categories->clcategories) : "";
   fullUrl += categories->cldir.length() > 0 ? "&cldir=" + escape(categories->cldir) : ""; 
   fullUrl += formatPart;
   //cout << "\t\tmwaapi::categories fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::categories res:" << res << endl;
   categories->fromJsonString(res);
  } 
  
/*
 CategoryMembers
  
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategorymembers
https://www.mediawiki.org/wiki/API:Categorymembers
*/
  void categoryMembers(LoginInfo* loginInfo, CategoryMembers* categoryMembers) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=query&list=categorymembers";
   fullUrl += categoryMembers->cmtitle.length() > 0 ? "&cmtitle=" + escape(categoryMembers->cmtitle) : "";
   fullUrl += categoryMembers->cmpageid == -1 ? "" : "&cmpageid=" + to_string(categoryMembers->cmpageid); 
   fullUrl += categoryMembers->cmprop.length() > 0 ? "&cmprop=" + escape(categoryMembers->cmprop) : "";
   fullUrl += categoryMembers->cmnamespace == -1 ? "" : "&cmnamespace=" + to_string(categoryMembers->cmnamespace);
   fullUrl += categoryMembers->cmtype.length() > 0 ? "&cmtype=" + escape(categoryMembers->cmtype) : "";
   fullUrl += categoryMembers->cmcontinue.length() > 0 ? "&cmcontinue=" + escape(categoryMembers->cmcontinue) : "";
   //cout << "\t\tmwaapi::categories fullUrl (1): " << fullUrl << endl;
   fullUrl += categoryMembers->cmsort.length() > 0 ? "&cmsort=" + escape(categoryMembers->cmsort) : ""; 
   fullUrl += "&cmsort=timestamp&cmdir=desc";
   fullUrl += formatPart;
   //cout << "\t\tmwaapi::categoryMembers fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::categoryMembers res:" << res << endl;
   categoryMembers->fromJsonString(res);
  }
  
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
   //cout << "\t\tmwaapi::edit fullUrl: " << fullUrl << endl;
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
   //cout << "\t\tmwaapi::edit postFields: " << postFields << endl;
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
  Purge:
  
  https://en.wikipedia.org/w/api.php?action=help&modules=purge
  https://www.mediawiki.org/wiki/API:Purge
*/
  
  void purge(LoginInfo* loginInfo, Purge* purge) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=purge";
   fullUrl += purge->forcelinkupdate == 0 ? "" : "&forcelinkupdate=" + to_string(purge->forcelinkupdate);
   fullUrl += purge->forcerecursivelinkupdate == 0 ? "" : "&forcerecursivelinkupdate=" + to_string(purge->forcerecursivelinkupdate);
   fullUrl += purge->continueP.length() > 0 ? "&continueP=" + escape(purge->continueP) : "";
   fullUrl += purge->titles.length() > 0 ? "&titles=" + escape(purge->titles) : "";
   fullUrl += purge->pageids == -1 ? "" : "&pageids=" + to_string(purge->pageids);
   fullUrl += purge->revids == -1 ? "" : "&revids=" + to_string(purge->revids);
   fullUrl += purge->generator.length() > 0 ? "&generator=" + escape(purge->generator) : "";  
   fullUrl += formatPart;
   //cout << "\t\tmwaapi::purge fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::purge res:" << res << endl;
   purge->fromJsonString(res);
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
   fullUrl+= revisions->prop.length()==0 ? "" : "&rvprop=" + revisions->prop;
   fullUrl+= revisions->limit == -1 ? "" : "&rvlimit=" + to_string(revisions->limit);
   fullUrl+= revisions->expandtemplates == -1 ? "" : "&rvexpandtemplates=" + to_string(revisions->expandtemplates);
   fullUrl+= revisions->parse == -1 ? "" : "&rvparse=" + to_string(revisions->parse);
   fullUrl+= revisions->section == -1 ? "" : "&rvsection=" + to_string(revisions->section);
   fullUrl+= revisions->diffto.length()==0 ? "" : "&rvdiffto=" + revisions->diffto;
   fullUrl+= revisions->difftotext.length()==0 ? "" : "&rvdifftotext=" + revisions->difftotext;
   fullUrl+= revisions->difftotextpst.length()==0 ? "" : "&rvdifftotextpst=" + revisions->difftotextpst;
   fullUrl+= revisions->contentformat.length()==0 ? "" : "&rvcontentformat=" + revisions->contentformat;
   fullUrl+= revisions->startid == -1 ? "" : "&rvstartid=" + to_string(revisions->startid);
   fullUrl+= revisions->endid == -1 ? "" : "&rvendid=" + to_string(revisions->endid);
   fullUrl+= revisions->start.length()==0 ? "" : "&rvstart=" + revisions->start;
   fullUrl+= revisions->end.length()==0 ? "" : "&rvend=" + revisions->end;
   fullUrl+= revisions->dir.length()==0 ? "" : "&rvdir=" + revisions->dir;
   fullUrl+= revisions->user.length()==0 ? "" : "&rvuser=" + revisions->user;
   fullUrl+= revisions->excludeuser.length()==0 ? "" : "&rvexcludeuser=" + revisions->excludeuser;
   fullUrl+= revisions->tag.length()==0 ? "" : "&rvtag=" + revisions->tag;
   fullUrl+= revisions->continue_req.length()==0 ? "" : "&rvcontinue=" + revisions->continue_req;
   fullUrl+= formatPart;
   //cout << "\t\tmwaapi::revisions fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::revisions res: " << res << endl;
   revisions->fromJsonString(res);
  } 
  
/*
Roll back the last edits of the user of the page.
  
If the last user who edited the page made multiple edits in a row, they will all be rolled back. 
  
https://en.wikipedia.org/w/api.php?action=help&modules=rollback
https://www.mediawiki.org/wiki/API:Rollback
*/
  void rollback(LoginInfo* loginInfo, Tokens* tokens, Rollback* rollback) {
   if(loginInfo->site.length() == 0) return;
   if(tokens->rollbacktoken.length() == 0) getTokens(loginInfo, tokens, "rollback");
   string fullUrl = loginInfo->site+endpointPart+"?"+"action=rollback";
   //cout << "\t\tmwaapi::rollback fullUrl: " << fullUrl << endl;
   string postFields = rollback->title.length() > 0 ? "title="+escape(rollback->title) : "pageid="+escape(rollback->pageid);
   postFields += rollback->user.length() > 0 ? "&user="+escape(rollback->user) : "";
   postFields += rollback->summary.length() > 0 ? "&summary="+escape(rollback->summary) : "";
   postFields += rollback->markbot == -1 ? "" : "&markbot=" + rollback->markbot;
   postFields += "&token="+escape(tokens->rollbacktoken);
   fullUrl+=formatPart;
   //cout << "\t\tmwaapi::rollback postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::rollback res: " << res << endl;
   rollback->fromJsonString(res);
  } 
  
  void search(LoginInfo* loginInfo, Search* search){
   if(loginInfo->site.length() == 0) return;
   string fullUrl=loginInfo->site+endpointPart+"?"+"action=query&list=search";
   fullUrl += search->srsearch.length() > 0 ? "&srsearch=" + escape(search->srsearch) : "";
   fullUrl += search->srnamespace == -1 ? "" : "&srnamespace=" + to_string(search->srnamespace);
   fullUrl += search->srwhat.length() > 0 ? "&srwhat=" + escape(search->srwhat) : "";
   fullUrl += search->srinfo.length() > 0 ? "&srinfo=" + escape(search->srinfo) : "";
   fullUrl += search->srprop.length() > 0 ? "&srprop=" + escape(search->srprop) : "";
   fullUrl += search->sroffset == -1 ? "" : "&sroffset=" + to_string(search->sroffset);
   //cout << "\t\tmwaapi::search fullUrl (1): " << fullUrl << endl;
   fullUrl += search->srlimit == -1 ? "" : "&srlimit=" + to_string(search->srlimit); 
   fullUrl += formatPart;
   //cout << "\t\tmwaapi::search fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::search res:" << res << endl;
   search->fromJsonString(res);
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
   //cout << "\t\tmwaapi::thank res: " << res << endl;
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
  
}; 
  
const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP

