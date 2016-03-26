/*
 revisiontracker is a console script for run tracking of all new wikinews revisions with RevisionTracker.hpp.

 Compiling:
 make

 For usage see:
 ./revisiontracker --help

 Tasks page example: 
 https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
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
         + "\t\t./revisiontracker <site> <botusername> <botuserpassword> <Name of tasks page> <count of last revisions>\n"
         + "\tRun as daemon:\n"
         + "\t\t./revisiontracker <site> <botusername> <botuserpassword> <Name of tasks page>\n"
         + "\tTasks page example:\n"
         + "\t\tUser:Wikiapicpp/Settings/Welcome (https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome)");
}

string showVersions() {
 return ((string)"Versions of welcome and components (major.minor):\n" 
         + "\trevisiontracker            " + versionMajor + "." + versionMinor + "\n"
         + "\tLoginInfo          " + LoginInfo::versionMajor + "." + LoginInfo::versionMinor + "\n"
         + "\tMediaWikiActionAPI " + MediaWikiActionAPI::versionMajor + "." + MediaWikiActionAPI::versionMinor + "\n"
         + "\tTokens             " + Tokens::versionMajor + "." + Tokens::versionMinor + "\n"
         + "\tRevisionsTracker   " + RevisionsTracker::versionMajor + "." + RevisionsTracker::versionMinor);
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
 } else if(argc < 5) {
  cout << "Very few arguments..." << endl;
  cout << showUsage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 MediaWikiActionAPI mwaapi;
 LoginInfo loginInfo(argv[1], argv[2], argv[3]);
 Tokens tokens;

 RevisionsTracker revisionsTracker(&mwaapi, &loginInfo, &tokens, argv[4]);

 if(argc == 5) {
  revisionsTracker.runAsDaemon();
 } else {
  string argv5(argv[5]);
  cout << "[revisionstracker] argv5:" << argv5 << endl;
  try {
   int cnt = stoi(argv5);
   revisionsTracker.processLastRevisions(cnt);
  } catch(...) {
    cout << "Five argument must be number." << endl;
  }
 }

 cout << "All tasks are successfully completed." << endl;
 return 0;
}
 
