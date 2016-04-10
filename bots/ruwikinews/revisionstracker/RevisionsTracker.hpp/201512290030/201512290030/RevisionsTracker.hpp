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
#include <iostream>
#include <map>
#include <string>
#include <thread>
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
  string lastChangesDateTimeString;
  LoginInfo* loginInfo;
  string settingsPage; // content of setteings page
  map<string,string> settingPagesMap;
  string settingsPageName;
  int switchStatus = -1;
  int switchStatusPrevious = -1;
  chrono::milliseconds timeout_ms = TIMEOUT_MS;
  Tokens* tokens;

  RevisionsTracker() {}

  RevisionsTracker(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& settingsPageName) : mwaapi(mwaapi), loginInfo(loginInfo), settingsPageName(settingsPageName), tokens(tokens) {
   init();
  }

  void init() {
   //cout << "[RevisionsTracker::init] settingsPageName:" << settingsPageName << endl;
   loadSettingsPage();
   parseSettings();
  }

  void loadSettingsPage() {
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
   if(revisions.pages[0].revisions.size()==0) return;
   settingsPage = revisions.pages[0].revisions[0].content;
   //cout << "[RevisionsTracker::loadSettingsPage] settingsPage:" << endl << settingsPage << endl;
  }

  void parseSettings() {
   settingPagesMap.clear();
   switchStatus = -1;
   //cout << "[RevisionsTracker::parseSettings] settingsPage.length():" << settingsPage.length() << endl;
   if(settingsPage.length()==0) return;
   auto json = json11::Json::parse(settingsPage, errJson);
   auto settingPagesJson = json["settingpages"].object_items();
   //cout << "[RevisionsTracker::parseSettings] settingPagesJson.size():" << settingPagesJson.size() << endl;
   for(auto sp : settingPagesJson) settingPagesMap[sp.first] = sp.second.string_value();
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
   revisions.start = lastChangesFromDateTime;
   processRevisions(&revisions);
  }

  void processRevisions(Revisions* revisions) {
   mwaapi->allrevisions(loginInfo, revisions);
   cout << "[RevisionsTracker::processRevisions] revisions->revisions.size(): " << revisions->revisions.size() << endl;
   if(revisions->revisions.size() == 0) {
    cout << "[RevisionsTracker::processRevisions] Revisions not found." << endl;
    return;
   }
  }

  void runAsDaemon() {
   cout << "[RevisionsTracker::runAsDaemon]..." << endl;
   if(switchStatus!=1) return;
   processLastRevisions(COUNT_OF_LAST_CHANGES);
   while(switchStatus) {
    testSwitch();
    processLastRevisions(lastChangesDateTimeString);
    this_thread::sleep_for(timeout_ms);
   }
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

