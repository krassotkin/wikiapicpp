#ifndef REVISIONSTRACKER_HPP
#define REVISIONSTRACKER_HPP
/*
 RevisionsTracker.hpp is a class for tracking all wikinews revisions and processing of certain events.
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

class RevisionsTracker {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const int COUNT_OF_LAST_CHANGES = 10;

  string errJson;
  MediaWikiActionAPI* mwaapi;
  LoginInfo* loginInfo;
  chrono::milliseconds timeout_ms = chrono::milliseconds(1000);
  string tasksPageName;
  Tokens* tokens;

  RevisionsTracker() {}

  RevisionsTracker(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& tasksPageName) : mwaapi(mwaapi), loginInfo(loginInfo), tasksPageName(tasksPageName), tokens(tokens) {
   init();
  }

  void init() {
   loadTasksPage();
   parseTasks();
  }

  void loadTasksPage() {
  }

  void parseTasks() {
  }

  void processLastRevisions(const int& countOfLastChanges) {
  }

  void runAsDaemon() {
  }

};

const string RevisionsTracker::versionMajor = "201512290030";
const string RevisionsTracker::versionMinor = "201512290030";

#endif // #ifndef REVISIONSTRACKER_HPP

