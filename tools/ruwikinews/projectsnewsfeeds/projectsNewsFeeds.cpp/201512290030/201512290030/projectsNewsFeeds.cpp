/*
 projectsNewsFeeds.cpp is a console tool of the wikiapicpp project for test ProjectNewsFeeds.hpp.

 Compiling:
 make

 Usage:
 ./projectsNewsFeeds <username> <userpassword> <tasksPageName>

 Tasks page example: 
 https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/ProjectsNewsFeeds

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <iostream>
#include <string>

using namespace std;

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "ProjectsNewsFeeds.hpp"
#include "Tokens.hpp"

const string siteName = "https://ru.wikinews.org/";

string description() {
 return "projectsNewsFeeds is a console tool for update projects wikinews feeds.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\t./projectsNewsFeeds <username> <userpassword> <tasksPageName>\n"
         + "Tasks page example:\n"
         + "\thttps://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/ProjectsNewsFeeds (User:Wikiapicpp/Settings/ProjectsNewsFeeds)");
}

int main(int argc, char *argv[]) {

 string firsArgv = argv[1];
 if(argc == 2) {
  string firsArgv = argv[1];
  if(firsArgv.compare("--help") == 0
     || firsArgv.compare("-h") == 0
     || firsArgv.compare("-help") == 0
     || firsArgv.compare("help") == 0
     || firsArgv.compare("h") == 0) {
   cout << description() << endl << endl;
   cout << usage() << endl;
   return 0;
  }
 }
 if(argc < 4) {
  cout << "Very few arguments..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 MediaWikiActionAPI mwaapi;

 // Login
 LoginInfo loginInfo;
 loginInfo.site = siteName;
 loginInfo.lgusername = argv[1];
 loginInfo.lgpassword = argv[2];
 Tokens tokens;
 mwaapi.login(&loginInfo, &tokens);
 if(!loginInfo.isSuccess()) {
  cout << "Login failed..." << endl;
  cout << "Response:" << endl;
  cout << loginInfo.toJson() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -2;
 }
 
 // Update projects news feeds
 ProjectsNewsFeeds projectsNewsFeeds(&mwaapi, &loginInfo, &tokens, argv[3]);
 projectsNewsFeeds.run();
 if(!projectsNewsFeeds.status) {
  cout << "Something went wrong..." << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -3;
 }

 cout << "All tasks are successfully completed." << endl;
 return 0;
}
 
