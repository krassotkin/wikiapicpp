#ifndef REVISIONSTRACKER_HPP
#define REVISIONSTRACKER_HPP
/*
 RevisionsTracker.hpp is a class for tracking all wikinews revisions and processing of certain events.

 Tasks page example: 
 User:Wikiapicpp/Settings/RevisionsTracker (https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/RevisionsTracker)

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin
 since 2015-12-29
*/

#include <chrono>  
#include <ctime>  
#include <iostream>
#include <map>
#include <string>
#include <thread>
//#include <time.h>
#include <tuple>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Revisions.hpp"
#include "Tokens.hpp"
#include "Welcome.hpp"

class RevisionsTracker {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const int COUNT_OF_LAST_CHANGES = 10;
  const string SWITCH_ON_STATUS = "on";
  chrono::milliseconds TIMEOUT_MS = chrono::milliseconds(1000);

  string errJson;
  MediaWikiActionAPI* mwaapi;
  string lastdatetimepage;
  string lastDateTimeString;
  int lastdatetimeupdate;
  int lastdatetimeupdate_i = 0;
  LoginInfo* loginInfo;
  string previousDateTimeString;
  string settingsPage; // content of setteings page
  map<string,string> settingPagesMap;
  string settingsPageName;
  int switchStatus = -1;
  int switchStatusPrevious = -1;
  chrono::milliseconds timeout_ms = TIMEOUT_MS;
  Tokens* tokens;
  Welcome* welcome;

  RevisionsTracker() {}

  RevisionsTracker(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& settingsPageName) : mwaapi(mwaapi), loginInfo(loginInfo), settingsPageName(settingsPageName), tokens(tokens) {
   init();
  }

  void init() {
   cout << "[RevisionsTracker::init] settingsPageName:" << settingsPageName << endl;
   loadSettingsPage();
   parseSettings();
   loadLastDateTime();
  }

  void loadLastDateTime() {
   cout << "[RevisionsTracker::loadLastDateTime]" << endl;
   lastDateTimeString.clear();
   if(loginInfo->site.length()==0) return;
   if(lastdatetimepage.length()==0) return;
   Revisions revisions;
   revisions.titles = lastdatetimepage;
   //cout << "[RevisionsTracker::loadLastDateTime] revisions.titles: " << revisions.titles << endl;
   revisions.prop="content";
   mwaapi->revisions(loginInfo, &revisions);
   //cout << "[RevisionsTracker::loadLastDateTime] revisions.pages.size(): " << revisions.pages.size() << endl;
   if(revisions.pages.size()==0) return;
   //cout << "[RevisionsTracker::loadLastDateTime] revisions.pages[0].revisions.size(): " << revisions.pages[0].revisions.size() << endl;
   if(revisions.pages[0]->revisions.size()==0) return;
   lastDateTimeString = revisions.pages[0]->revisions[0]->content;
   cout << "[RevisionsTracker::loadLastDateTime] lastDateTimeString:" << lastDateTimeString << endl;
  }

  void loadSettingsPage() {
   cout << "[RevisionsTracker::loadSettingsPage]" << endl;
   settingsPage.clear();
   //cout << "[RevisionsTracker::loadSettingsPage] loginInfo->site:" << loginInfo->site << endl;
   if(loginInfo->site.length()==0) return;
   //cout << "[RevisionsTracker::loadSettingsPage] settingsPageName:" << settingsPageName << endl;
   if(settingsPageName.length()==0) return;
   Revisions revisions;
   revisions.titles = settingsPageName;
   revisions.prop="content";
   mwaapi->revisions(loginInfo, &revisions);
   //cout << "[RevisionsTracker::loadSettingsPage] mwaapi->revisions requested..." << endl;
   //cout << "[RevisionsTracker::loadSettingsPage] lastFullUrl: " << mwaapi->lastFullUrl << endl;
   //cout << "[RevisionsTracker::loadSettingsPage] lastResponse: " << mwaapi->lastResponse << endl;
   if(revisions.pages.size()==0) return;
   if(revisions.pages[0]->revisions.size()==0) return;
   settingsPage = revisions.pages[0]->revisions[0]->content;
   //cout << "[RevisionsTracker::loadSettingsPage] settingsPage:" << endl << settingsPage << endl;
  }

  void parseSettings() {
   cout << "[RevisionsTracker::parseSettings]" << endl;
   settingPagesMap.clear();
   switchStatus = -1;
   //cout << "[RevisionsTracker::parseSettings] settingsPage.length():" << settingsPage.length() << endl;
   if(settingsPage.length()==0) return;
   auto json = json11::Json::parse(settingsPage, errJson);
   lastdatetimepage = json["lastdatetimepage"].string_value();
   lastdatetimeupdate = json["lastdatetimeupdate"].number_value();
   cout << "[RevisionsTracker::parseSettings] lastdatetimeupdate:" << lastdatetimeupdate << endl;
   auto settingPagesJson = json["settingpages"].object_items();
   //cout << "[RevisionsTracker::parseSettings] settingPagesJson.size():" << settingPagesJson.size() << endl;
   for(auto sp : settingPagesJson) {
    settingPagesMap[sp.first] = sp.second.string_value();
    if(sp.first.compare("Welcome") == 0) {
     cout << "[RevisionsTracker::parseSettings] found Welcome page" << endl;
     welcome = new Welcome(mwaapi, loginInfo, tokens, settingPagesMap[sp.first]);
    }
   }
   string switchString = json["switch"].string_value();
   //cout << "[RevisionsTracker::parseSettings] switchString:" << switchString << endl;
   switchStatus = (SWITCH_ON_STATUS.compare(switchString) == 0);
   //cout << "[RevisionsTracker::parseSettings] switchStatus:" << switchStatus << endl;
  }

  void processLastRevisions(const int& lastChangesCount) {
   cout << "[RevisionsTracker::processLastRevisions (int)]..." << endl;
   if(switchStatus!=1) return;
   Revisions revisions;
   revisions.prop = revisions.PROP_ARV_ALL;
   revisions.limit = lastChangesCount;
   processRevisions(&revisions);
  }

  void processLastRevisions(const string& lastChangesFromDateTime) {
   cout << "[RevisionsTracker::processLastRevisions (string)]..." << endl;
   if(switchStatus!=1) return;
   Revisions revisions;
   revisions.prop = revisions.PROP_ARV_ALL;
   revisions.end = lastChangesFromDateTime;
   processRevisions(&revisions);
  }

  void processRevisions(Revisions* revisions) {
   mwaapi->allrevisions(loginInfo, revisions);
   //cout << "[RevisionsTracker::processRevisions] mwaapi->lastFullUrl: " << mwaapi->lastFullUrl << endl;
   //cout << "[RevisionsTracker::processRevisions] mwaapi->lastPostFields: " << mwaapi->lastPostFields << endl;
   //cout << "[RevisionsTracker::processRevisions] mwaapi->lastResponse:\n" << mwaapi->lastResponse << endl;
   cout << "[RevisionsTracker::processRevisions] revisions->revisions.size(): " << revisions->revisions.size() << endl;
   while(revisions->continue_res.length()>0) {
    revisions->continue_req = revisions->continue_res;
    mwaapi->allrevisions(loginInfo, revisions);
    //cout << "[RevisionsTracker::processRevisions] mwaapi->lastFullUrl: " << mwaapi->lastFullUrl << endl;
    //cout << "[RevisionsTracker::processRevisions] mwaapi->lastPostFields: " << mwaapi->lastPostFields << endl;
    //cout << "[RevisionsTracker::processRevisions] mwaapi->lastResponse:\n" << mwaapi->lastResponse << endl;
    cout << "[RevisionsTracker::processRevisions] revisions->revisions.size(): " << revisions->revisions.size() << endl;
   }
   if(revisions->revisions.size() == 0) {
    cout << "[RevisionsTracker::processRevisions] Revisions not found." << endl;
    return;
   }
   time_t lastTime = 0;
   for(Revision revision : revisions->revisions) {
    cout << "[RevisionsTracker::processRevisions] revision.title: " << revision.title << endl; 
    if(revision.title.compare(lastdatetimepage)==0) {
     cout << "[RevisionsTracker::processRevisions] skiped saveLastDateTime()" << endl; 
     continue; // skip saveLastDateTime()
    }
    welcome->welcomeRevision(loginInfo, &revision);
    struct tm tmTime;
    strptime(revision.timestamp.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tmTime);
    time_t newTime = mktime(&tmTime);
    if(newTime > lastTime) lastTime = newTime;
   }
   if(lastTime > 0) {
    cout << "[RevisionsTracker::processRevisions] lastTime: " << lastTime << endl;
    char buf[sizeof "2015-12-29T00:30:00Z"];
    strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%SZ", localtime(&lastTime)); // gmtime(&lastTime));
    //string lastTimeString(buf);
    lastDateTimeString = string(buf);
    cout << "[RevisionsTracker::processRevisions] lastDateTimeString: " << lastDateTimeString << endl;
   }
  }

  void runAsDaemon() {
   cout << "[RevisionsTracker::runAsDaemon]..." << endl;
   //if(switchStatus!=1) return;
   //processLastRevisions(COUNT_OF_LAST_CHANGES);
   while(switchStatus) {
    testSwitch();
    processLastRevisions(lastDateTimeString);
    lastdatetimeupdate_i++;
    cout << "[RevisionsTracker::runAsDaemon] lastdatetimeupdate_i: " << lastdatetimeupdate_i << endl;
    if(lastdatetimeupdate_i > lastdatetimeupdate) {
     saveLastDateTime();
     lastdatetimeupdate_i = 0;
    }
    this_thread::sleep_for(timeout_ms);
   }
  }

  void saveLastDateTime() {
   if(lastDateTimeString.length() == 0) return;
   if(lastDateTimeString.compare(previousDateTimeString) == 0) return;
   Edit edit;
   edit.bot = 1;
   edit.minor = 1;
   edit.summary = "Update last DateTime of RevisionsTracker.";
   edit.text = lastDateTimeString;
   edit.title = lastdatetimepage;
   cout << "[RevisionsTracker::saveLastDateTime] edit.text: \n" << edit.text << endl;
   if(!loginInfo->isLogin()) {
    cout << "[RevisionsTracker::saveLastDateTime] loginInfo->isLogin(): " << loginInfo->isLogin() << endl;
    return; // not logined
   }
   mwaapi->edit(loginInfo, tokens, &edit); 
   previousDateTimeString = lastDateTimeString;
  }

  void testSwitch() {
   switchStatusPrevious = switchStatus;
   switchStatus = -1;
   loadSettingsPage();
   auto json = json11::Json::parse(settingsPage, errJson);
   string switchString = json["switch"].string_value();
   cout << "[RevisionsTracker::testSwitch] switchString:" << switchString << endl;
   switchStatus = (SWITCH_ON_STATUS.compare(switchString) == 0);
   if(switchStatusPrevious!=switchStatus) {
    cout << "[RevisionsTracker::testSwitch] switchStatusPrevious: " << switchStatusPrevious << "; switchStatus: " << switchStatus;
    cout << (switchStatus == 1 ? " -> started" : " -> stopped") << endl; 
   }   
  }

};

const string RevisionsTracker::versionMajor = "201512290030";
const string RevisionsTracker::versionMinor = "201512290030";

#endif // #ifndef REVISIONSTRACKER_HPP

