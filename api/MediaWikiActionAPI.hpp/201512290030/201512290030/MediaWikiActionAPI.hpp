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
#include "Pages.hpp"
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
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query&list=allrevisions"
                    + (revisions->titles.length()>0 ? "&titles="+escape(revisions->titles) : "&pageids="+revisions->pageids)
                    + (revisions->prop.length()==0 ? "" : "&arvprop=" + revisions->prop)
                    + (revisions->limit == -1 ? "" : "&arvlimit=" + to_string(revisions->limit))
                    + (revisions->expandtemplates == -1 ? "" : "&arvexpandtemplates=" + to_string(revisions->expandtemplates))
                    + (revisions->parse == -1 ? "" : "&arvparse=" + to_string(revisions->parse))
                    + (revisions->section == -1 ? "" : "&arvsection=" + to_string(revisions->section))
                    + (revisions->diffto.length()==0 ? "" : "&arvdiffto=" + revisions->diffto)
                    + (revisions->difftotext.length()==0 ? "" : "&arvdifftotext=" + revisions->difftotext)
                    + (revisions->difftotextpst.length()==0 ? "" : "&arvdifftotextpst=" + revisions->difftotextpst)
                    + (revisions->contentformat.length()==0 ? "" : "&arvcontentformat=" + revisions->contentformat)
                    + (revisions->startid == -1 ? "" : "&arvstartid=" + to_string(revisions->startid))
                    + (revisions->endid == -1 ? "" : "&arvendid=" + to_string(revisions->endid))
                    + (revisions->start.length()==0 ? "" : "&arvstart=" + revisions->start)
                    + (revisions->end.length()==0 ? "" : "&arvend=" + revisions->end)
                    + (revisions->dir.length()==0 ? "" : "&arvdir=" + revisions->dir)
                    + (revisions->user.length()==0 ? "" : "&arvuser=" + revisions->user)
                    + (revisions->excludeuser.length()==0 ? "" : "&arvexcludeuser=" + revisions->excludeuser)
                    + (revisions->tag.length()==0 ? "" : "&arvtag=" + revisions->tag)
                    + (revisions->continue_req.length()==0 ? "" : "&arvcontinue=" + revisions->continue_req)
                    + formatPart;
   //cout << "\t\tmwaapi::revisions fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::revisions res: " << res << endl;
   revisions->fromJsonString(res);
  } 
  
/*
 Categories

https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategories
https://www.mediawiki.org/wiki/API:Categories


List all categories the pages belong to. 
*/
  void categories(LoginInfo* loginInfo, Categories* categories) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query&prop=categories"
                    + (categories->titles.length() > 0 ? "&titles=" + escape(categories->titles) : "")
                    + (categories->clprop.length() > 0 ? "&clprop=" + escape(categories->clprop) : "")
                    + (categories->clshow.length() > 0 ? "&clshow=" + escape(categories->clshow) : "")
                    + (categories->cllimit.length() > 0 ? "&cllimit=" + escape(categories->cllimit) : "")
                    + (categories->clcontinue.length() > 0 ? "&clcontinue=" + escape(categories->clcontinue) : "")
                    + (categories->clcategories.length() > 0 ? "&clcategories=" + escape(categories->clcategories) : "")
                    + (categories->cldir.length() > 0 ? "&cldir=" + categories->cldir : "")
                    + formatPart;
   cout << "\t\tmwaapi::categories fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   cout << "\t\tmwaapi::categories res:" << res << endl;
   categories->fromJsonString(res);
  } 
  
/*
 CategoryMembers
  
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Bcategorymembers
https://www.mediawiki.org/wiki/API:Categorymembers
*/
  void categoryMembers(LoginInfo* loginInfo, CategoryMembers* categoryMembers) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query&list=categorymembers"
                    + (categoryMembers->cmtitle.length() > 0 ? "&cmtitle=" + escape(categoryMembers->cmtitle) : "")
                    + (categoryMembers->cmpageid == -1 ? "" : "&cmpageid=" + to_string(categoryMembers->cmpageid))
                    + (categoryMembers->cmprop.length() > 0 ? "&cmprop=" + escape(categoryMembers->cmprop) : "")
                    + (categoryMembers->cmnamespace == -1 ? "" : "&cmnamespace=" + to_string(categoryMembers->cmnamespace))
                    + (categoryMembers->cmtype.length() > 0 ? "&cmtype=" + escape(categoryMembers->cmtype) : "")
                    + (categoryMembers->cmlimit == -1 ? "" : "&cmlimit=" + to_string(categoryMembers->cmlimit))
                    + (categoryMembers->cmcontinue.length() > 0 ? "&cmcontinue=" + escape(categoryMembers->cmcontinue) : "")
                    + (categoryMembers->cmsort.length() > 0 ? "&cmsort=" + escape(categoryMembers->cmsort) : "")
                    + (categoryMembers->cmdir.length() > 0 ? "&cmdir=" + escape(categoryMembers->cmdir) : "")
                    + formatPart;
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
   string fullUrl = loginInfo->site+endpointPart+"?"
                    +"action=edit"
                    +formatPart;
   //cout << "\t\tmwaapi::edit fullUrl: " << fullUrl << endl;
   string postFields = (edit->title.length() > 0 ? "title="+escape(edit->title) : "pageid="+to_string(edit->pageid))
                       + (edit->section == -1 ? "" : "&section="+to_string(edit->section))
                       + (edit->sectiontitle.length() == 0 ? "" : "&sectiontitle="+escape(edit->sectiontitle))
                       + (edit->text.length() == 0 ? "" : "&text="+escape(edit->text))
                       + (edit->summary.length() == 0 ? "" : "&summary="+escape(edit->summary))
                       + (edit->tags.length() == 0 ? "" : "&tags="+escape(edit->tags))
                       + (edit->minor == -1 ? "" : "&minor="+to_string(edit->minor))
                       + (edit->notminor == -1 ? "" : "&notminor="+to_string(edit->notminor))
                       + (edit->bot == -1 ? "" : "&bot="+to_string(edit->bot))
                       + (edit->basetimestamp.length() == 0 ? "" : "&basetimestamp="+escape(edit->basetimestamp))
                       + (edit->starttimestamp.length() == 0 ? "" : "&starttimestamp="+escape(edit->starttimestamp))
                       + (edit->recreate == -1 ? "" : "&recreate="+to_string(edit->recreate))
                       + (edit->createonly == -1 ? "" : "&createonly="+to_string(edit->createonly))
                       + (edit->nocreate == -1 ? "" : "&nocreate="+to_string(edit->nocreate))
                       + (edit->watchlist.length() == 0 ? "" : "&watchlist="+escape(edit->watchlist))
                       + (edit->md5.length() == 0 ? "" : "&md5="+escape(edit->md5))
                       + (edit->prependtext.length() == 0 ? "" : "&prependtext="+escape(edit->prependtext))
                       + (edit->appendtext.length() == 0 ? "" : "&appendtext="+escape(edit->appendtext))
                       + (edit->undo == -1 ? "" : "&undo="+to_string(edit->undo))
                       + (edit->undoafter == -1 ? "" : "&undoafter="+to_string(edit->undoafter))
                       + (edit->redirect == -1 ? "" : "&redirect="+to_string(edit->redirect))
                       + (edit->contentformat.length() == 0 ? "" : "&contentformat="+escape(edit->contentformat))
                       + (edit->contentmodel.length() == 0 ? "" : "&contentmodel="+escape(edit->contentmodel))
                       + (edit->captchaword.length() == 0 ? "" : "&captchaword="+escape(edit->captchaword))
                       + (edit->captchaid.length() == 0 ? "" : "&captchaid="+escape(edit->captchaid))
                       + ("&token="+escape(tokens->csrftoken));
   //cout << "\t\tmwaapi::edit postFields: " << postFields << endl;
   string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::edit res: " << res << endl;
   edit->fromJsonString(res);
  }

/*
  Tokens:
https://en.wikipedia.org/w/api.php?action=help&modules=tokens
https://en.wikinews.org/w/api.php?action=help&modules=query%2Btokens
*/
  void getTokens(LoginInfo* loginInfo, Tokens* tokens) {
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&meta=tokens"
                    + "&type="+tokens->type
                    + formatPart;
   //cout << "\t\tmwaapi::getTokens fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::getTokens res: " << res << endl;
   tokens->fromJsonString(res);
  }

  void getTokens(LoginInfo* loginInfo, Tokens* tokens, const string& type) {
   tokens->type = type;
   getTokens(loginInfo, tokens);
  }
  
/*
 Login: 
https://en.wikipedia.org/w/api.php?action=help&modules=login
https://www.mediawiki.org/wiki/API:Login 
*/
  void login(LoginInfo* loginInfo, Tokens* tokens) {
   if(tokens->logintoken.length() == 0) getTokens(loginInfo, tokens, "login");
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=login"
                    + "&lgname="+loginInfo->lgusername
                    + "&lgpassword="+loginInfo->lgpassword
                    + "&lgtoken="+escape(tokens->logintoken)
                    + formatPart;
   //cout << "\t\tmwaapi::login fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   //cout << "\t\tmwaapi::login res: " << res << endl;
   loginInfo->fromJsonString(res);
  }
  
/*
 Logout:
https://en.wikipedia.org/w/api.php?action=help&modules=logout
https://www.mediawiki.org/wiki/API:Logout
*/
  void logout(LoginInfo* loginInfo) {
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=logout"
                    + formatPart;
   cout << "\t\tmwaapi::logout fullUrl: " << fullUrl << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl);
   cout << "\t\tmwaapi::logout res: " << res << endl;
   loginInfo->clear();
  }
  
/*
  Purge:  
https://en.wikipedia.org/w/api.php?action=help&modules=purge
https://www.mediawiki.org/wiki/API:Purge
*/
  
  void purge(LoginInfo* loginInfo, Purge* purge) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=purge"
                    + (purge->forcelinkupdate == 0 ? "" : "&forcelinkupdate=" + to_string(purge->forcelinkupdate))
                    + (purge->forcerecursivelinkupdate == 0 ? "" : "&forcerecursivelinkupdate=" + to_string(purge->forcerecursivelinkupdate))
                    + (purge->continueP.length() > 0 ? "&continueP=" + escape(purge->continueP) : "")
                    + (purge->titles.length() > 0 ? "&titles=" + escape(purge->titles) : "")
                    + (purge->pageids == -1 ? "" : "&pageids=" + to_string(purge->pageids))
                    + (purge->revids == -1 ? "" : "&revids=" + to_string(purge->revids))
                    + (purge->generator.length() > 0 ? "&generator=" + escape(purge->generator) : "")  
                    + formatPart;
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
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&prop=revisions"
                    + (revisions->titles.length()>0 ? "&titles="+escape(revisions->titles) : "&pageids="+revisions->pageids)
                    + (revisions->prop.length()==0 ? "" : "&rvprop=" + revisions->prop)
                    + (revisions->limit == -1 ? "" : "&rvlimit=" + to_string(revisions->limit))
                    + (revisions->expandtemplates == -1 ? "" : "&rvexpandtemplates=" + to_string(revisions->expandtemplates))
                    + (revisions->parse == -1 ? "" : "&rvparse=" + to_string(revisions->parse))
                    + (revisions->section == -1 ? "" : "&rvsection=" + to_string(revisions->section))
                    + (revisions->diffto.length()==0 ? "" : "&rvdiffto=" + revisions->diffto)
                    + (revisions->difftotext.length()==0 ? "" : "&rvdifftotext=" + revisions->difftotext)
                    + (revisions->difftotextpst.length()==0 ? "" : "&rvdifftotextpst=" + revisions->difftotextpst)
                    + (revisions->contentformat.length()==0 ? "" : "&rvcontentformat=" + revisions->contentformat)
                    + (revisions->startid == -1 ? "" : "&rvstartid=" + to_string(revisions->startid))
                    + (revisions->endid == -1 ? "" : "&rvendid=" + to_string(revisions->endid))
                    + (revisions->start.length()==0 ? "" : "&rvstart=" + revisions->start)
                    + (revisions->end.length()==0 ? "" : "&rvend=" + revisions->end)
                    + (revisions->dir.length()==0 ? "" : "&rvdir=" + revisions->dir)
                    + (revisions->user.length()==0 ? "" : "&rvuser=" + revisions->user)
                    + (revisions->excludeuser.length()==0 ? "" : "&rvexcludeuser=" + revisions->excludeuser)
                    + (revisions->tag.length()==0 ? "" : "&rvtag=" + revisions->tag)
                    + (revisions->continue_req.length()==0 ? "" : "&rvcontinue=" + revisions->continue_req)
                    + formatPart;
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
   if(tokens->rollbacktoken.length() == 0) {
    tokens->type = "rollback";
    getTokens(loginInfo, tokens);
   }
   string fullUrl = loginInfo->site+endpointPart+"?"
                    +"action=rollback";
   //cout << "\t\tmwaapi::rollback fullUrl: " << fullUrl << endl;
   string postFields = (rollback->title.length() > 0 ? "title="+escape(rollback->title) : "pageid="+escape(rollback->pageid))
                       + (rollback->user.length() > 0 ? "&user="+escape(rollback->user) : "")
                       + (rollback->summary.length() > 0 ? "&summary="+escape(rollback->summary) : "")
                       + (rollback->markbot == -1 ? "" : "&markbot=" + rollback->markbot)
                       + ("&token="+escape(tokens->rollbacktoken))
                       + formatPart;
   //cout << "\t\tmwaapi::rollback postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::rollback res: " << res << endl;
   rollback->fromJsonString(res);
  } 
   
/* 
*/ 
  void search(LoginInfo* loginInfo, Search* search){
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&list=search"
                    + (search->srsearch.length() > 0 ? "&srsearch=" + escape(search->srsearch) : "")
                    + (search->srnamespace == -1 ? "" : "&srnamespace=" + to_string(search->srnamespace))
                    + (search->srwhat.length() > 0 ? "&srwhat=" + escape(search->srwhat) : "")
                    + (search->srinfo.length() > 0 ? "&srinfo=" + escape(search->srinfo) : "")
                    + (search->srprop.length() > 0 ? "&srprop=" + escape(search->srprop) : "")
                    + (search->sroffset == -1 ? "" : "&sroffset=" + to_string(search->sroffset))
                    + (search->srlimit == -1 ? "" : "&srlimit=" + to_string(search->srlimit)) 
                    + formatPart;
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
   if(tokens->csrftoken.length() == 0) {
    tokens->type = "csrf";
    getTokens(loginInfo, tokens);
   }
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=thank"
                    + "&rev="+revidString
                    + formatPart;
   //cout << "\t\tmwaapi::thank fullUrl: " << fullUrl << endl;
   string postFields = "token="+escape(tokens->csrftoken);
   //cout << "\t\tmwaapi::thank postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::thank res: " << res << endl;
  }
  
/*
*/ 
  void undo(LoginInfo* loginInfo, Tokens* tokens, Edit* edit) {
   if(loginInfo->site.length() == 0) return;
   if(tokens->csrftoken.length() == 0) {
    tokens->type = "csrf";
    getTokens(loginInfo, tokens);
   }
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=edit"
                    + formatPart;
   //cout << "\t\ttmwaapi::edit fullUrl: " << fullUrl << endl;
   string postFields = (edit->title.length() > 0 ? "title="+escape(edit->title) : "pageid="+to_string(edit->pageid))
                       + (edit->undo == -1 ? "" : "&undo="+to_string(edit->undo))
                       + ("&token="+escape(tokens->csrftoken));
   //cout << "\t\ttmwaapi::edit postFields: " << postFields << endl;
   string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
   //cout << "\t\tmwaapi::edit res: " << res << endl;
   edit->fromJsonString(res);
  }
  
}; 
  
const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP

