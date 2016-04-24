#ifndef MEDIAWIKIACTIONAPI_HPP
#define MEDIAWIKIACTIONAPI_HPP

/*
 MediaWikiActionAPI.hpp is a  С++ interface to The MediaWiki action API.

 The MediaWiki action API: https://www.mediawiki.org/wiki/API:Main_page 
 The MediaWiki action API Help: https://en.wikipedia.org/w/api.php
 The MediaWiki action API Sandbox: https://en.wikipedia.org/wiki/Special:ApiSandbox

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
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
#include "AllPages.hpp"
#include "Categories.hpp"
#include "Category.hpp"
#include "CategoryMembers.hpp"
#include "CategoryMember.hpp"
#include "Compare.hpp"
#include "CreateAccount.hpp"
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "LogEvents.hpp"
#include "LogEvent.hpp"
#include "MediaWikiActionAPIParameters.hpp"
#include "Page.hpp"
#include "Purge.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"
#include "Rollback.hpp"
#include "Search.hpp"
#include "SearchItem.hpp"
#include "Sitematrix.hpp"
#include "SitematrixLanguage.hpp"
#include "Site.hpp"
#include "Tokens.hpp"

class MediaWikiActionAPI {
  
 private:
  
  CurlWrapper curlWrapper;

 public:

  static const string versionMajor;
  static const string versionMinor;
  
  const string endpointPart = "w/api.php";
  // const string formatPart = "&format=json";

  string lastFullUrl;
  string lastPostFields;
  string lastResponse;
  
  MediaWikiActionAPI() {}
  
  
/***************************************************************************
*                             Servo                                        *
***************************************************************************/
  
  string escape(const string& s) {
   return curlWrapper.escape(s);
  }
  
/***************************************************************************
*                              API                                         *
***************************************************************************/
/*
Allpages

https://en.wikipedia.org/w/api.php?action=help&modules=query%2Ballpages
https://www.mediawiki.org/wiki/API:Allpages


Enumerate all pages sequentially in a given namespace.  
*/
  void allpages(LoginInfo* loginInfo, AllPages* allPage) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&list=allpages"
                    + allPage->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::allPage fullUrl: " << fullUrl << endl;
   string postFields = (allPage->apcontinue.length() == 0 ? "" : "&apcontinue=" + allPage->apcontinue)
                       + (allPage->apdir.length() == 0 ? "" : "&apdir=" + allPage->apdir)
                       + (allPage->apprfiltercascade.length() == 0 ? "" : "&apprfiltercascade=" + allPage->apprfiltercascade)
                       + (allPage->apfilterlanglinks.length() == 0 ? "" : "&apfilterlanglinks=" + allPage->apfilterlanglinks)
                       + (allPage->apfilterredir.length() == 0  ? "" : "&apfilterredir=" + allPage->apfilterredir)
                       + (allPage->apfrom.length() == 0 ? "" : "&apfrom=" + allPage->apfrom)
                       + (allPage->aplimit == -1 ? "" : "&aplimit=" + to_string(allPage->aplimit))
                       + (allPage->apmaxsize == -1 ? "" : "&apmaxsize=" + to_string(allPage->apmaxsize))
                       + (allPage->apminsize == -1 ? "" : "&apminsize=" + to_string(allPage->apminsize))
                       + (allPage->apnamespace == -1 ? "" : "&apnamespace=" + to_string(allPage->apnamespace))
                       + (allPage->apprefix.length() == 0 ? "" : "&apprefix=" + allPage->apprefix)
                       + (allPage->apprexpiry.length() == 0 ? "" : "&apprexpiry=" + allPage->apprexpiry)
                       + (allPage->apprlevel.length() == 0 ? "" : "&apprlevel=" + allPage->apprlevel)
                       + (allPage->apprtype.length() == 0 ? "" : "&apprtype=" + allPage->apprtype)
                       + (allPage->apto.length() == 0 ? "" : "&apto=" + allPage->apto);
   //cout << "\t\tmwaapi::allPage postFields: " << postFields << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
   //cout << "\t\tmwaapi::allPage res:" << res << endl;
   allPage->fromJsonString(res);
  } 
 
/*
List all revisions

 Processed by MediaWikiActionAPI.hpp allrevisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Ballrevisions
https://www.mediawiki.org/wiki/API:Allrevisions
*/
  void allrevisions(LoginInfo* loginInfo, Revisions* revisions) {
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&list=allrevisions"
                    + (revisions->titles.length()==0 ? "" : "&titles="+escape(revisions->titles))
                    + (revisions->pageids.length()==0 ? "" : "&pageids="+revisions->pageids)
                    + (revisions->prop.length()==0 ? "" : "&arvprop=" + revisions->prop)
                    + (revisions->limit == -1 ? "" : "&arvlimit=" + to_string(revisions->limit))
                    + (revisions->expandtemplates == -1 ? "" : "&arvexpandtemplates=" + to_string(revisions->expandtemplates))
                    + (revisions->parse == -1 ? "" : "&arvparse=" + to_string(revisions->parse))
                    + (revisions->section == -1 ? "" : "&arvsection=" + to_string(revisions->section))
                    + (revisions->diffto.length()==0 ? "" : "&arvdiffto=" + revisions->diffto)
                    + (revisions->difftotext.length()==0 ? "" : "&arvdifftotext=" + revisions->difftotext)
                    + (revisions->difftotextpst.length()==0 ? "" : "&arvdifftotextpst=" + revisions->difftotextpst)
                    + (revisions->contentformat.length()==0 ? "" : "&arvcontentformat=" + revisions->contentformat)
                    //+ (revisions->startid == -1 ? "" : "&arvstartid=" + to_string(revisions->startid))
                    //+ (revisions->endid == -1 ? "" : "&arvendid=" + to_string(revisions->endid))
                    + (revisions->start.length()==0 ? "" : "&arvstart=" + revisions->start)
                    + (revisions->end.length()==0 ? "" : "&arvend=" + revisions->end)
                    + (revisions->dir.length()==0 ? "" : "&arvdir=" + revisions->dir)
                    + (revisions->user.length()==0 ? "" : "&arvuser=" + revisions->user)
                    + (revisions->excludeuser.length()==0 ? "" : "&arvexcludeuser=" + revisions->excludeuser)
                    + (revisions->tag.length()==0 ? "" : "&arvtag=" + revisions->tag)
                    + (revisions->continue_req.length()==0 ? "" : "&arvcontinue=" + revisions->continue_req)
                    + revisions->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::revisions fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
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
                    + "action=query"
                    + "&prop=categories"
                    + categories->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::categories fullUrl: " << fullUrl << endl;
   string postFields = (categories->titles.length() == 0 ? "" : "&titles=" + categories->titles)
                       + (categories->pageids.length() == 0 ? "" : "&pageids=" + categories->pageids)
                       + (categories->clprop.length() == 0 ? "" : "&clprop=" + categories->clprop)
                       + (categories->clshow.length() == 0 ? "" : "&clshow=" + categories->clshow)
                       + (categories->cllimit == -1 ? "" : "&cllimit=" + to_string(categories->cllimit))
                       + (categories->clcontinue.length() == 0  ? "" : "&clcontinue=" + categories->clcontinue)
                       + (categories->clcategories.length() == 0 ? "" : "&clcategories=" + categories->clcategories)
                       + (categories->cldir.length() == 0 ? "" : "&cldir=" + categories->cldir);
   //cout << "\t\tmwaapi::categories postFields: " << postFields << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
   //cout << "\t\tmwaapi::categories res:" << res << endl;
   categories->fromJsonString(res);
  } 

/*
 CreateAccount
 Create a new user account.

https://en.wikipedia.org/w/api.php?action=help&modules=createaccount
https://www.mediawiki.org/wiki/API:Account_creation
*/
  void createaccount(LoginInfo* loginInfo, Tokens* tokens, CreateAccount* createAccount) {
   if(tokens->createaccounttoken.length() == 0) getTokens(loginInfo, tokens, "createaccount");
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=createaccount"
                    + createAccount->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::createaccount fullUrl: " << fullUrl << endl;
   string postFields = "name=" + createAccount->name
                       + "&password=" + createAccount->password
                       + (createAccount->domain.length() == 0 ? "" : "&domain=" + createAccount->domain)
                       + (tokens->createaccounttoken.length() == 0 ? "" : "&token=" + escape(tokens->createaccounttoken))
                       + (createAccount->email.length() == 0 ? "" : "&email=" + createAccount->email)
                       + (createAccount->realname.length() == 0  ? "" : "&realname=" + createAccount->realname)
                       + (createAccount->mailpassword == -1 ? "" : "&mailpassword=" + to_string(createAccount->mailpassword))
                       + (createAccount->reason.length() == 0 ? "" : "&reason=" + createAccount->reason)
                       + (createAccount->ignoreantispoof == -1 ? "" : "&ignoreantispoof=" + to_string(createAccount->ignoreantispoof))
                       + (createAccount->ignoretitleblacklist == -1 ? "" : "&ignoretitleblacklist=" + to_string(createAccount->ignoretitleblacklist))
                       + (createAccount->captchaword.length() == 0 ? "" : "&captchaword=" + createAccount->captchaword)
                       + (createAccount->captchaid.length() == 0 ? "" : "&captchaid=" + createAccount->captchaid)
                       + (createAccount->language.length() == 0 ? "" : "&language=" + createAccount->language);
   lastPostFields = postFields;
   //cout << "\t\tmwaapi::createaccount postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
   //cout << "\t\tmwaapi::createaccount res:" << res << endl;
   createAccount->fromJsonString(res);
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
                    + categoryMembers->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::categoryMembers fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   //cout << "\t\tmwaapi::categoryMembers res:" << res << endl;
   categoryMembers->fromJsonString(res);
  }
  
/*
 Compare:
  
 Get the difference between 2 pages by titles, page ID, or revision number.
  
 A revision number, a page title, or a page ID for both "from" and "to" must be passed. 
  
 https://en.wikipedia.org/w/api.php?action=help&modules=compare
*/
  void compare(LoginInfo* loginInfo, Compare* compare) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=compare"
                    + (compare->fromid > -1 ? "&fromid=" + to_string(compare->fromid) : "")
                    + (compare->fromrev > -1 ? "&fromrev=" + to_string(compare->fromrev) : "")
                    + (compare->fromtitle.length() > 0 ? "&fromtitle=" + compare->fromtitle : "")
                    + (compare->toid > -1 ? "&toid=" + to_string(compare->toid) : "")
                    + (compare->torev > -1 ? "&torev=" + to_string(compare->torev) : "")
                    + (compare->totitle.length() > 0 ? "&totitle=" + compare->totitle : "")
                    + compare->getSuperParameters();
   lastFullUrl = fullUrl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   compare->fromJsonString(res);
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
                    +edit->getSuperParameters();
   lastFullUrl = fullUrl;
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
   lastPostFields = postFields;
   //cout << "\t\tmwaapi::edit postFields: " << postFields << endl;
   string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
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
                    + tokens->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::getTokens fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
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
                    + "&lgname="+loginInfo->lgname
                    + "&lgpassword="+loginInfo->lgpassword
                    + "&lgtoken="+escape(tokens->logintoken)
                    + loginInfo->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "[mwaapi::login] fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   //cout << "[mwaapi::login] res: " << res << endl;
   loginInfo->fromJsonString(res);
  }

/*
 LogEvent
https://www.mediawiki.org/wiki/API:Logevents
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Blogevents
*/
  void logevents(LoginInfo* loginInfo, LogEvents* logEvents) {
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=query"
                    + "&list=logevents"
                    + (logEvents->leprop.length() == 0 ? "" : "leprop=" + logEvents->leprop)
                    + (logEvents->letype.length() == 0 ? "" : "letype=" + logEvents->letype)
                    + (logEvents->leaction.length() == 0 ? "" : "&leaction=" + logEvents->leaction)
                    + (logEvents->lestart.length() == 0 ? "" : "&lestart=" + logEvents->lestart)
                    + (logEvents->leend.length() == 0 ? "" : "&leend=" + logEvents->leend)
                    + (logEvents->ledir.length() == 0  ? "" : "&ledir=" + logEvents->ledir)
                    + (logEvents->leuser.length() == 0 ? "" : "&leuser=" + logEvents->leuser)
                    + (logEvents->letitle.length() == 0 ? "" : "&letitle=" + logEvents->letitle)
                    + (logEvents->lenamespace == -1 ? "" : "&lenamespace=" + to_string(logEvents->lenamespace))
                    + (logEvents->leprefix.length() == 0 ? "" : "&leprefix=" + logEvents->leprefix)
                    + (logEvents->letag.length() == 0 ? "" : "&letag=" + logEvents->letag)
                    + (logEvents->lelimit == -1 ? "" : "&lelimit=" + to_string(logEvents->lelimit))
                    + (logEvents->lecontinue.length() == 0 ? "" : "&lecontinue=" + logEvents->lecontinue)
                    + logEvents->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::logevent fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
    //cout << "\t\tmwaapi::logevent res:" << res << endl;
   logEvents->fromJsonString(res);
  }
  
/*
 Logout:
https://en.wikipedia.org/w/api.php?action=help&modules=logout
https://www.mediawiki.org/wiki/API:Logout
*/
  void logout(LoginInfo* loginInfo) {
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=logout"
                    + loginInfo->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::logout fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   //cout << "\t\tmwaapi::logout res: " << res << endl;
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
                    + purge->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::purge fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
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
                    + revisions->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::revisions fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
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
                    +"action=rollback"
                    + rollback->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::rollback fullUrl: " << fullUrl << endl;
   string postFields = (rollback->title.length() > 0 ? "title="+escape(rollback->title) : "pageid="+escape(rollback->pageid))
                       + (rollback->user.length() > 0 ? "&user="+escape(rollback->user) : "")
                       + (rollback->summary.length() > 0 ? "&summary="+escape(rollback->summary) : "")
                       + (rollback->markbot == -1 ? "" : "&markbot=" + rollback->markbot)
                       + ("&token="+escape(tokens->rollbacktoken));
   lastPostFields = postFields;
   //cout << "\t\tmwaapi::rollback postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
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
                    + search->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::search fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   //cout << "\t\tmwaapi::search res:" << res << endl;
   search->fromJsonString(res);
  }

/*
 Sitematrix:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix
*/

  void sitematrix(LoginInfo* loginInfo, Sitematrix* sitematrix){
   if(loginInfo->site.length() == 0) return;
   string fullUrl = loginInfo->site+endpointPart+"?"
                    + "action=sitematrix"
                    + (sitematrix->smtype.length() > 0 ? "&smtype=" + escape(sitematrix->smtype) : "")
                    + (sitematrix->smstate.length() > 0 ? "&smstate=" + escape(sitematrix->smstate) : "")
                    + (sitematrix->smlangprop.length() > 0 ? "&smlangprop=" + escape(sitematrix->smlangprop) : "")
                    + (sitematrix->smsiteprop.length() > 0 ? "&smsiteprop=" + escape(sitematrix->smsiteprop) : "")
                    + (sitematrix->smcontinue.length() > 0 ? "&smcontinue=" + escape(sitematrix->smcontinue) : "")
                    + (sitematrix->smlimit == -1 ? "" : "&smlimit=" + to_string(sitematrix->smlimit))
                    + sitematrix->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::sitematrix fullUrl: " << fullUrl << endl;
   lastPostFields = "";
   string res=curlWrapper.getFirstPagePost(fullUrl);
   lastResponse = res;
   //cout << "\t\tmwaapi::sitematrix res:" << res << endl;
   sitematrix->fromJsonString(res);
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
                    + loginInfo->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\tmwaapi::thank fullUrl: " << fullUrl << endl;
   string postFields = "token="+escape(tokens->csrftoken);
   lastPostFields = postFields;
   //cout << "\t\tmwaapi::thank postFields: " << postFields << endl;
   string res=curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
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
                    + edit->getSuperParameters();
   lastFullUrl = fullUrl;
   //cout << "\t\ttmwaapi::edit fullUrl: " << fullUrl << endl;
   string postFields = (edit->title.length() > 0 ? "title="+escape(edit->title) : "pageid="+to_string(edit->pageid))
                       + (edit->undo == -1 ? "" : "&undo="+to_string(edit->undo))
                       + ("&token="+escape(tokens->csrftoken));
   lastPostFields = postFields;
   //cout << "\t\ttmwaapi::edit postFields: " << postFields << endl;
   string res = curlWrapper.getFirstPagePost(fullUrl, postFields);
   lastResponse = res;
   //cout << "\t\tmwaapi::edit res: " << res << endl;
   edit->fromJsonString(res);
  }
  
}; 
  
const string MediaWikiActionAPI::versionMajor = "201512290030";
const string MediaWikiActionAPI::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPI_HPP

