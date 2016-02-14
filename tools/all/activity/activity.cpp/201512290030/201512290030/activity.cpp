/*
 activity.cpp is console tool to display the current activity on wikimedia projects.

 Compiling:
 make

 Usage:
 ./activity <-option> [<-option>] <url> [<-url>]

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

string description() {
 return "activity is a console tool to display the current activity on wikimedia projects.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\t./activity <-option> [<-option>] <url> [<-url>]\n"
         + "Example:\n"
         + "\t./activity https://ru.wikinews.org/");
}

int main(int argc, char *argv[]) {
 if(argc < 2) {
  cout << "Very few arguments..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }
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

 MediaWikiActionAPI mwaapi;
 return 0;
}
 
