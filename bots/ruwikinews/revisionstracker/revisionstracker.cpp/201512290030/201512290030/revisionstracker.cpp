/*
 revisiontracker is a console script for run tracking of all new wikinews revisions with RevisionTracker.hpp.

 Compiling:
 make

 For usage see:
 ./revisiontracker --help

 Tasks page example: 
 https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/RevisionsTracker

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin
 since 2015-12-29
*/

#include <iostream>
#include <string>

using namespace std;

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Tokens.hpp"
#include "RevisionsTracker.hpp"

const string versionMajor = "201512290030";
const string versionMinor = "201512290030";

const string SETTING_PAGE_DEFAULT = "User:Wikiapicpp/Settings/RevisionsTracker";
const string SITE_DEFAULT = "https://ru.wikinews.org/";

string showDescription() {
 return "revisiontracker is a console script for run tracking of all new wikinews revisions and processing of certain events.";
}

string showUsage() {
 return ((string)"Usage:\n"
         + "\tShow full help:\n"
         + "\t\t./revisiontracker --help\n"
         + "\tShow versions:\n"
         + "\t\t./revisiontracker --versions\n"
         + "\tRun for the last revisions:\n"
         + "\t\t./revisiontracker <botusername> <botuserpassword> <Name of settings page> <count of last revisions or date from>\n"
         + "\tRun as daemon:\n"
         + "\t\t./revisiontracker <botusername> <botuserpassword> <Name of settings page>\n"
         + "Example of settings page:\n"
         + "\tUser:Wikiapicpp/Settings/RevisionsTracker on RuWikinews (https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/RevisionsTracker)");
}

string showVersions() {
 return ((string)"Versions of welcome and components (major.minor):\n" 
         + "\trevisiontracker    " + versionMajor + "." + versionMinor + "\n"
         + "\tLoginInfo          " + LoginInfo::versionMajor + "." + LoginInfo::versionMinor + "\n"
         + "\tMediaWikiActionAPI " + MediaWikiActionAPI::versionMajor + "." + MediaWikiActionAPI::versionMinor + "\n"
         + "\tTokens             " + Tokens::versionMajor + "." + Tokens::versionMinor + "\n"
         + "\tRevisionsTracker   " + RevisionsTracker::versionMajor + "." + RevisionsTracker::versionMinor + "\n"
         + "\tWelcome            " + Welcome::versionMajor + "." + Welcome::versionMinor);
}

int main(int argc, char *argv[]) {
 cout << "[revisionstracker] argc:" << argc << endl;
 if(argc == 2) {
  string firstArg = argv[1];
  if(firstArg.compare("--help") == 0
     || firstArg.compare("-h") == 0
     || firstArg.compare("-help") == 0
     || firstArg.compare("help") == 0
     || firstArg.compare("h") == 0) {
   cout << showDescription() << endl << endl;
   cout << showVersions() << endl << endl;
   cout << showUsage() << endl;
   return 0;
  } else if(firstArg.compare("--version") == 0
            || firstArg.compare("--versions") == 0
            || firstArg.compare("-v") == 0
            || firstArg.compare("version") == 0
            || firstArg.compare("versions") == 0) {
   cout << showVersions() << endl;
   return 0;
  }
 } else if(argc < 4) {
  cout << "Very few arguments..." << endl;
  cout << showUsage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 MediaWikiActionAPI mwaapi;
 LoginInfo loginInfo(SITE_DEFAULT, argv[1], argv[2]);
 cout << "[revisionstracker] LoginInfo inited..." << endl;
 Tokens tokens;
 cout << "[revisionstracker] Tokens inited..." << endl;

 mwaapi.login(&loginInfo, &tokens);
 cout << "[revisionstracker] " << (loginInfo.isSuccess() ? "Success logined to " : "Login failed to ") << loginInfo.site << endl;

 RevisionsTracker revisionsTracker(&mwaapi, &loginInfo, &tokens, argv[3]);
 cout << "[revisionstracker] RevisionsTracker inited..." << endl;

 if(argc == 4) {
  revisionsTracker.runAsDaemon();
 } else if(argc == 5) {
  string argv4(argv[4]);
  cout << "[revisionstracker] argv4:" << argv4 << endl;
  try {
   int cnt = stoi(argv4);
   revisionsTracker.processLastRevisions(cnt);
  } catch(...) {
   revisionsTracker.processLastRevisions(argv4);
  }
 }

 cout << "All tasks are successfully completed." << endl;
 return 0;
}

