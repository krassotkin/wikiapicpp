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

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/ 

#ifndef _TERMIOS_H
#include <termios.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif

#include <algorithm>
//#include <conio.h> 
#include <iostream>
#include <string>
#include <vector>

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Revisions.hpp"

using namespace std;

const string versionMajor = "201512290030";
const string versionMinor = "201512290030";

const string consolePrefixDefault = "[anonymous]> ";

string consolePrefix = consolePrefixDefault;
LoginInfo loginInfo;
MediaWikiActionAPI mwaapi;

void showHelp();
void showVersions();

vector<string> getCommandVector() {
 string commandLine;
 //cin >> commandLine;
 getline(cin, commandLine);
 //cout << "\tcommandLine: " << commandLine << endl;
 vector<string> commandVector;
 if(commandLine.length() == 0) return commandVector;
 string commandLinePart;
 bool inQuotes1 = false;
 bool inQuotes2 = false;
 for(char c : commandLine) {
  if(!inQuotes1 && !inQuotes2 && c == ' ') {
   if(commandLinePart.length()>0) commandVector.push_back(commandLinePart);
   commandLinePart.clear();
   continue;
  }
  if(!inQuotes2 && c == '\'') {
   if(inQuotes1) inQuotes1 = false;
   else inQuotes1 = true;
  } else if(!inQuotes1 && c == '\"') {
   if(inQuotes2) inQuotes2 = false;
   else inQuotes2 = true;
  } else {
   commandLinePart+=c;
  }
 }
 if(commandLinePart.length()>0) commandVector.push_back(commandLinePart);
 /*
 cout << "\tcommandVector: ";
 for(string s : commandVector) cout << "\"" << s << "\" ";
 cout << endl;
 */
 return commandVector;
}

bool expectsEcho(const vector<string>& commandVector) {
 if(commandVector[0].compare("echo") != 0) return false;
 for(unsigned int ic = 1; ic < commandVector.size(); ic++) cout << "\"" << commandVector[ic] << "\" ";
 cout << endl;
 return true;
}

bool expectsHelp(const vector<string>& commandVector) {
 if(commandVector[0].compare("--help") == 0
    || commandVector[0].compare("-h") == 0
    || commandVector[0].compare("h") == 0
    || commandVector[0].compare("help") == 0) {
  showHelp(); 
  return true;
 }
 return false;
}

bool expectsHistory(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("history")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"history\"." << endl;
  return true;
 }
 if(commandVector.size() < 2) {
  cout << "Very few arguments for history..." << endl;
  cout << "History format:" << endl;
  //cout << "\thistory \"Name or id of page\" <number of revisions> <from id or date> <to id or date>" << endl;
  cout << "\thistory \"Name or id of page\" <number of revisions> <from id> <to id>" << endl;
  cout << "Example:" << endl;
  cout << "\thistory \"Main Page\"" << endl;
  cout << "\thistory 15580374" << endl;
  cout << "\thistory \"Main Page\" 10" << endl;
  //cout << "\thistory \"Main Page\" 20 2015-12-29T00:30" << endl;
  //cout << "\thistory \"Main Page\" - 2015-12-29T00:30 2014-12-29T00:30" << endl;
  cout << "\thistory \"Main Page\" 10 696846920" << endl;
  cout << "\thistory \"Main Page\" - 696846920 289122024" << endl;
  return true;
 }
 Revisions revisions;
 try {
  long pageids = stol(commandVector[1]);
  revisions.pageids = to_string(pageids);
 } catch(...) {
  revisions.titles = commandVector[1];
 }
 if(commandVector.size() < 3 || commandVector[2].compare("-")==0) {
  revisions.rvlimit = revisions.rvlimitDefault;
 } else {
  try {
   long rvlimit = stol(commandVector[2]);
   revisions.rvlimit = rvlimit;
  } catch(...) {
   cout << "Can not parsed number of revisions (rvlimit)..." << endl;
   cout << "Must be number or \"-\"." << endl;
   return true;
  }
 }
 if(commandVector.size() > 3) {
  try {
   long rvstartid = stol(commandVector[3]);
   revisions.rvstartid = rvstartid;
  } catch(...) {
   revisions.rvstart = commandVector[3];
  }
 }
 if(commandVector.size() > 4) {
  try {
   long rvendid = stol(commandVector[4]);
   revisions.rvendid = rvendid;
  } catch(...) {
   revisions.rvend = commandVector[4];
  }
 }
 revisions.rvprop="ids|flags|timestamp|user|userid|size|sha1|comment|tags|flagged";
 mwaapi.revisions(&loginInfo, &revisions);
 if(revisions.pages.size()==0) {
  cout << "Page not found..." << endl;
  return true;
 }
 cout << "Revision history of \"" << revisions.pages[0].title << "\" (" << revisions.pages[0].pageid  << ")" << endl;
 if(revisions.pages[0].revisions.size()==0) {
  cout << "Not found." << endl;
  return true;
 }
 for(Revision r : revisions.pages[0].revisions) {
  cout << "(" << to_string(r.revid) << "|" << to_string(r.parentid) << ")  ";
  cout << r.timestamp << "  ";
  cout << r.user;
  for(unsigned int i=r.user.length(); i<20; i++) cout << ' ';
  if(r.minor.compare("not")==0) cout << "m .. "; 
  else cout << "  .. "; 
  cout << "(" << to_string(r.size) << " bytes)  ";
  cout << "(" << r.comment << ")";
  cout << endl;
 } 
 return true;
}

bool expectsLogin(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("login")!=0) return false;
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

bool expectsLogout(const vector<string>& commandVector) {
 if(commandVector[0].compare("logout") != 0) return false;
 if(loginInfo.result.compare("Success") != 0) {
  cout << "You are not logined..." << endl;
  return true;
 };
 mwaapi.logout(&loginInfo);
 consolePrefix = consolePrefixDefault;
 return true;
}

bool expectsQuit(const vector<string>& commandVector) {
 if(commandVector[0].compare("bye") == 0
    || commandVector[0].compare("quit") == 0
    || commandVector[0].compare("q") == 0)
  return true;
 return false;
}

bool expectsSite(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("site")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not connected to any wiki site..." << endl;
  cout << "Use \"login\" for connect (can be a failed)." << endl;
 } else {
  cout << "Connected site: " << loginInfo.site << endl;
 }
 return true;
}

bool expectsVersions(const vector<string>& commandVector) {
 if(commandVector[0].compare("--version") == 0
    || commandVector[0].compare("--versions") == 0
    || commandVector[0].compare("-v") == 0
    || commandVector[0].compare("version") == 0
    || commandVector[0].compare("versions") == 0) {
  showVersions(); 
  return true;
 }
 return false;
}

bool parseCommandLine(const vector<string>& commandVector) {
 if(commandVector.size() == 0) return false;
 if(expectsEcho(commandVector)) return true;
 if(expectsHelp(commandVector)) return true;
 if(expectsHistory(commandVector)) return true;
 if(expectsLogin(commandVector))return true;
 if(expectsLogout(commandVector)) return true;
 if(expectsSite(commandVector)) return true;
 if(expectsVersions(commandVector)) return true;
 return false;
}

void runConsole() {
 cout << "wikiconsole is runing..." << endl;
 while(true) {
  cout << consolePrefix;
  vector<string> commandVector = getCommandVector();
  if(commandVector.size() == 0) continue;
  if(!parseCommandLine(commandVector)) {
   if(expectsQuit(commandVector)) break;
   cout << "Command not found. Type \"h\" for help or \"q\" for quit." << endl;
  }
 }
 cout << "wikiconsole stopped..." << endl;
}

void showHelp() {
 cout << endl << "wikiconsole is a console for the MediaWiki APIs (https://www.mediawiki.org/wiki/API:Main_page)." << endl << endl;
 cout << "Command line format:" << endl;
 cout << "\twikiconsole <command> <options>" << endl;
 cout << endl << "Without command and options run console." << endl;
 cout << endl << "Console format:" << endl;
 cout << "\t<command> <options>" << endl;
 cout << endl << "The most commonly used wikiapicpp commands are:" << endl;
 cout << "  echo        Show parsed command line with options." << endl;
 cout << "  help        Show this help." << endl;
 cout << "              Aliases: --help, -h, h, help." << endl;
 cout << "  history     Show standard history of page. Use after \"login\"." << endl;
 cout << "              Format: history \"Name or id of page\" <number of revisions> <from id or date> <to id or date>" << endl;
 cout << "              Example: history \"Main Page\"" << endl;
 cout << "              Type \"history\" without quotes and options for more information." << endl;
 cout << "  login       Login to a media wiki server." << endl;
 cout << "              Format: login site username userpassword" << endl;
 cout << "              Example: login https://en.wikipedia.org/ bob bobsecretpass" << endl;
 cout << "  logout      Log out and clear session data." << endl;
 cout << "  quit        Exit from console." << endl;
 cout << "              Aliases: bye, q." << endl;
 cout << "  site        Print url of connected site (after login or empty)." << endl;
 cout << "  versions    Show versions of wikiconsole and components (major.minor)." << endl;
 cout << "              Aliases: --version, --versions, -v, version, versions." << endl;
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
  vector<string> commandVector;
  for(int iarg=1; iarg < argc; iarg++) commandVector.push_back(argv[iarg]);
  parseCommandLine(commandVector);
 } else {
  runConsole(); 
 } 
 return 0;
}

