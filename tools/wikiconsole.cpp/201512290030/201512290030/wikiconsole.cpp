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

vector<string> commandsHistoryVector;
unsigned long commanHistoryIndex = 0;
string consolePrefix = consolePrefixDefault;
LoginInfo loginInfo;
MediaWikiActionAPI mwaapi;

void showHelp();
void showVersions();

char getch() {
 struct termios t;
 tcgetattr(0,&t);
 t.c_lflag&=~ECHO+~ICANON;
 tcsetattr(0,TCSANOW,&t);
 fflush(stdout);
 char c=getchar();
 t.c_lflag|=ICANON+ECHO;
 tcsetattr(0,TCSANOW,&t);
 return c;
}

string getCommandLine() {
 //cout << "\tcommanHistoryIndex: " << commanHistoryIndex << endl;
 string commandLine = "";
 int unsigned pos = 0;
 while(true) {
  char c = getch();
  if(c==27) {
   c = getch();
   if(c=='[') {
    c = getch();
    if(c=='A') {
     if(commanHistoryIndex>0) {
      if(commandLine.length()>0) {
       commandsHistoryVector.push_back(commandLine);
       commanHistoryIndex--;
      }
      printf("\r%c[2K", 27);
      commandLine = commandsHistoryVector[commanHistoryIndex];
      cout << consolePrefix << commandsHistoryVector[commanHistoryIndex];
      pos=commandLine.length();
     }
    } else if(c=='B') {
     if(commanHistoryIndex<commandsHistoryVector.size()-1) {
      commanHistoryIndex++;
      printf("\r%c[2K", 27);
      commandLine = commandsHistoryVector[commanHistoryIndex];
      cout << consolePrefix << commandsHistoryVector[commanHistoryIndex];
      pos=commandLine.length();
     }
    } else if(c=='D') {
     cout << "\b";
     pos--;
    } else {
     cout << " --> " << int(c);
    }
   }
   continue;
  }
  if(c == 127) { 
   if(pos==0) continue;
   cout << "\b \b";
   pos--;
   string cl;
   unsigned int i=0;
   for(; i<pos; i++) cl+=commandLine[i];
   for(; i<commandLine.length()-1; i++) cl+=commandLine[i];
   commandLine = cl;
   continue;
  }
  if(c == '\b') {   
   cout << '\b';
   pos--;
   continue;
  }
  putchar(c);
  pos++;
  if(c=='\n') return commandLine;
  commandLine+=c;
 }
}

vector<string> getCommandVector() {
 commanHistoryIndex = commandsHistoryVector.size()>0 ? commandsHistoryVector.size()-1 : 0;
 string commandLine = getCommandLine();
 cout << "\tcommandLine: " << commandLine << endl;
 vector<string> commandVector;
 if(commandLine.length() == 0) return commandVector;
 commandsHistoryVector.push_back(commandLine);
 commanHistoryIndex++;
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
 cout << "\tcommandVector: ";
 for(string s : commandVector) cout << "\"" << s << "\" ";
 cout << endl;
 commanHistoryIndex = commandsHistoryVector.size()-1;
 return commandVector;
}

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

bool parseCommandLine(const vector<string>& commandVector) {
 if(commandVector.size() == 0) return false;
 //for commands without options
 if(expectsHelp(commandVector[0])) return true;
 else if(expectsLogout(commandVector[0])) return true;
 else if(expectsVersions(commandVector[0])) return true;
 //for commands with options
 if(expectsLogin(commandVector))return true;
 return false;
}

void runConsole() {
 cout << "wikiconsole is runing..." << endl;
 while(true) {
  cout << consolePrefix;
  vector<string> commandVector = getCommandVector();
  if(commandVector.size() == 0) continue;
  if(!parseCommandLine(commandVector)) {
   if(expectsQuit(commandVector[0])) break;
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
 cout << endl << "The most commonly used wikiapicpp commands are:" << endl;
 cout << "  help        Show this help." << endl;
 cout << "              Aliases: --help, -h, h, help." << endl;
 cout << "  login       Login to a media wiki server." << endl;
 cout << "              Format: login site username userpassword" << endl;
 cout << "              Example: login https://en.wikipedia.org/ bob bobsecretpass" << endl;
 cout << "  logout      Log out and clear session data." << endl;
 cout << "  quit        Exit from console." << endl;
 cout << "              Aliases: bye, q." << endl;
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
  if(expectsVersions(argv[1]));
  else if(expectsHelp(argv[1]));
 } else {
  runConsole(); 
 } 
 return 0;
}

