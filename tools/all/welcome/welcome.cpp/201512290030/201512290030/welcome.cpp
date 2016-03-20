/*
 welcome is a console tool of the wikiapicpp project used to welcome new users.

 Compiling:
 make

 Usage:

 For welcome a user:
 ./welcome <site> <botusername> <botuserpassword> <newusername wit User: prefix>

 For process task page:
 ./welcome <site> <botusername> <botuserpassword> <tasksPageName>

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
#include "Welcome.hpp"

const string versionMajor = "201512290030";
const string versionMinor = "201512290030";

string showDescription() {
 return "welcome is a console tool of the wikiapicpp project used to welcome new users.";
}

string showUsage() {
 return ((string)"Usage:\n"
         + "\tShow full help:\n"
         + "\t\t./welcome --help\n"
         + "\tShow versions:\n"
         + "\t\t./welcome --versions\n"
         + "\tWelcome a user:\n"
         + "\t\t./welcome <site> <botusername> <botuserpassword> <Name of tasks page> <username without \"User:\" prefix>\n"
         + "\tWelcome the last users from projects:\n"
         + "\t\t./welcome <site> <botusername> <botuserpassword> <Name of tasks page> <count of last revisions>\n"
         + "\tWelcome last users as daemon:\n"
         + "\t\t./welcome <site> <botusername> <botuserpassword> <Name of tasks page>\n"
         + "\tTasks page example:\n"
         + "\t\tUser:Wikiapicpp/Settings/Welcome (https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome)");
}

string showVersions() {
 return ((string)"Versions of welcome and components (major.minor):\n" 
         + "\twelcome            " + versionMajor + "." + versionMinor + "\n"
         + "\tLoginInfo          " + LoginInfo::versionMajor + "." + LoginInfo::versionMinor + "\n"
         + "\tMediaWikiActionAPI " + MediaWikiActionAPI::versionMajor + "." + MediaWikiActionAPI::versionMinor + "\n"
         + "\tTokens             " + Tokens::versionMajor + "." + Tokens::versionMinor + "\n"
         + "\tWelcome            " + Welcome::versionMajor + "." + Welcome::versionMinor);
}

int main(int argc, char *argv[]) {
 cout << "[Welcome::welcome] argc:" << argc << endl;
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

 Welcome welcome(&mwaapi, &loginInfo, &tokens, argv[4]);

 if(argc == 5) {
  welcome.runAsDaemon();
 } else {
  string argv5(argv[5]);
  cout << "[Welcome::welcome] argv5:" << argv5 << endl;
  try {
   int cnt = stoi(argv5);
   welcome.welcomeLastUsers(cnt);
  } catch(...) {
   welcome.welcomeUser(argv5);
  }
 }

 cout << "All tasks are successfully completed." << endl;
 return 0;
}
 
