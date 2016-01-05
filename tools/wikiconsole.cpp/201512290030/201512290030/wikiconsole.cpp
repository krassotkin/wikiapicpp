/*
wikiconsole is a console for the MediaWiki APIs.

Compiling:
make

Usage:
./wikiconsole
./wikiconsole <command> <options>

Examples:
./wikiconsole -h
./wikiconsole -v
./wikiconsole

 Public Domain by authors: Alexander Krassotkin, Simon Krassotkin
 since 2015-12-29
*/ 

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"

using namespace std;

const string versionMajor = "201512290030";
const string versionMinor = "201512290030";

const string consolePrefixDefault = "[anonymous]> ";
string consolePrefix = consolePrefixDefault;
LoginInfo loginInfo;
MediaWikiActionAPI mwaapi;

void showHelp();
void showVersions();

bool expectsHelp(const string& commandLine) {
 if(string(commandLine).compare("--help") == 0
    || string(commandLine).compare("-h") == 0
    || string(commandLine).compare("h") == 0
    || string(commandLine).compare("help") == 0) {
  showHelp(); 
  return true;
 }
 return false;
}

bool expectsLogin(const vector<string>& commandVector) {
 if(commandVector[0].compare("login") != 0) return false;
 if(commandVector.size() < 4) {
  cout << "Very few arguments to login..." << endl;
  cout << "Login format:" << endl;
  cout << "\tlogin site username userpassword" << endl;
  cout << "Example:" << endl;
  cout << "\tlogin https://en.wikipedia.org/ bob bobsecretpass" << endl;
  return true;
 }
 loginInfo.site = commandVector[1];
 loginInfo.lgusername = commandVector[2];
 loginInfo.lgpassword = commandVector[3];
 mwaapi.login(&loginInfo);
 if(loginInfo.result.compare("Success") != 0) {
  cout << "Login failed..." << endl;
  cout << "Response:" << endl;
  cout << loginInfo.toJson() << endl;
  consolePrefix = consolePrefixDefault;
 } else {
  cout << "Success logined..." << endl;
  consolePrefix = "["+loginInfo.lgusername+"@"+loginInfo.cookieprefix+"]> ";
 }
 return true;
}

bool expectsLogout(const string& commandLine) {
 if(commandLine.compare("logout") != 0) return false;
 if(loginInfo.result.compare("Success") != 0) {
  cout << "You are not logined..." << endl;
  return true;
 };
 mwaapi.logout(&loginInfo);
 consolePrefix = consolePrefixDefault;
 return true;
}

bool expectsQuit(const string& commandLine) {
 if(string(commandLine).compare("bye") == 0
    || string(commandLine).compare("quit") == 0
    || string(commandLine).compare("q") == 0)
  return true;
 return false;
}

bool expectsVersions(const string& commandLine) {
 if(string(commandLine).compare("--version") == 0
    || string(commandLine).compare("--versions") == 0
    || string(commandLine).compare("-v") == 0
    || string(commandLine).compare("version") == 0
    || string(commandLine).compare("versions") == 0) {
  showVersions(); 
  return true;
 }
 return false;
}

bool parseCommandLine(const string& commandLine) {
 //for commands without options
 if(expectsHelp(commandLine)) return true;
 else if(expectsLogout(commandLine)) return true;
 else if(expectsVersions(commandLine)) return true; 
 vector<string> commandVector;
 //for commands with options
 string commandLinePart;
 for(char ci : commandLine) {
  if(ci==' ') {
   commandVector.push_back(commandLinePart);
   commandLinePart = "";
  } else {
   commandLinePart+=ci;
  }
 }
 commandVector.push_back(commandLinePart);
 if(expectsLogin(commandVector))return true;
 return false;
}

void runConsole() {
 cout << "wikiconsole is runing..." << endl;
 string commandLine;
 while(true) {
  cout << consolePrefix;
  getline(cin, commandLine);
  if(!parseCommandLine(commandLine)) {
   if(expectsQuit(commandLine)) break;
   cout << "Command not found. Type \"h\" for help or \"q\" for quit." << endl;
  }
 }
 cout << "wikiconsole stopped..." << endl;
}

void showHelp() {
 cout << endl << "wikiconsole is a console for the MediaWiki APIs (https://www.mediawiki.org/wiki/API:Main_page)." << endl << endl;
 cout << "Command line format:" << endl;
 cout << "\twikiconsole <command> <options>" << endl;
 cout << "\t\tWithout command and options run console." << endl;
 cout << endl << "Console format:" << endl;
 cout << "\t<command> <options>" << endl;
 cout << endl << "Commands:" << endl;
 cout << "\thelp - show this help." << endl;
 cout << "\t\taliases: --help, -h, h, help." << endl;
 cout << "\tlogin - login to a media wiki server." << endl;
 cout << "\t\tformat: login site username userpassword" << endl;
 cout << "\t\texample: login https://en.wikipedia.org/ bob bobsecretpass" << endl;
 cout << "\tlogout - log out and clear session data." << endl;
 cout << "\tquit - exit from console." << endl;
 cout << "\t\taliases: bye, q." << endl;
 cout << "\tversions - show versions of wikiconsole and components (major.minor)." << endl; 
 cout << "\t\taliases: --version, --versions, -v, version, versions." << endl;
 cout << endl;
}

void showVersions() {
 cout << endl << "Versions of wikiconsole and components (major.minor):" << endl;
 cout << "\twikiconsole " << versionMajor << "." << versionMinor << endl;
 cout << "\tCurlWrapper " << CurlWrapper::versionMajor << "." << CurlWrapper::versionMinor << endl;
 cout << "\tLoginInfo " << LoginInfo::versionMajor << "." << LoginInfo::versionMinor << endl;
 cout << "\tMediaWikiActionAPI " << MediaWikiActionAPI::versionMajor << "." << MediaWikiActionAPI::versionMinor << endl << endl;
}

int main(int argc, char *argv[]) {
 if(argc > 1) {
  if(expectsVersions(argv[1]));
  else if(expectsHelp(argv[1]));
 } else {
  runConsole(); 
 } 
 return 0;
}

