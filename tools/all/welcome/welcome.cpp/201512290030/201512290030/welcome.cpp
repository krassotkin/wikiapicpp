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

const int countOfLastChanges = 100;

string description() {
 return "welcome is a console tool of the wikiapicpp project used to welcome new users.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\tShow this help:\n"
         + "\t\t./welcome --help\n"
         + "\tWelcome a user:\n"
         + "\t\t./welcome <site> <botusername> <botuserpassword> <Name of tasks page> <username without \"User:\" prefix>\n"
         + "\tWelcome the last users from projects:\n"
         + "\t\t./welcome <site> <botusername> <botuserpassword> <Name of tasks page>\n"
         + "\tTasks page example:\n"
         + "\t\tUser:Wikiapicpp/Settings/Welcome (https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome)");
}

int main(int argc, char *argv[]) {
 if(argc == 2) {
  string firstArg = argv[1];
  if(firstArg.compare("--help") == 0
     || firstArg.compare("-h") == 0
     || firstArg.compare("-help") == 0
     || firstArg.compare("help") == 0
     || firstArg.compare("h") == 0) {
   cout << description() << endl << endl;
   cout << usage() << endl;
   return 0;
  }
 }
 if(argc < 5) {
  cout << "Very few arguments..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 MediaWikiActionAPI mwaapi;
 LoginInfo loginInfo(argv[1], argv[2], argv[3]);
 //cout << "[welcome.cpp] loginInfo.lgname = " << loginInfo.lgname << endl;
 Tokens tokens;

 Welcome welcome(&mwaapi, &loginInfo, &tokens, argv[4]);
 welcome.init();
 cout << "[welcome.cpp] argc = " << argc << endl;
 if(argc == 5) {
  welcome.welcomeLastUsers(countOfLastChanges);
  if(!welcome.status) {
   cout << "Something went wrong..." << endl;
   cout << "Nothing to do. Stopped." << endl;
   return -3;
  }
 } else if(argc == 6) {
  if(!welcome.welcomeUser(argv[5])) {
   cout << "Something went wrong..." << endl;
   cout << "Nothing to do. Stopped." << endl;
   return -4;
  }
 } else {
  cout << "The task is not defined...." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -5;
 }

 cout << "All tasks are successfully completed." << endl;
 return 0;
}
 
