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

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <thread>
#include <vector>

// shared
#include "CurlWrapper.hpp"
#include "json11.hpp"

// api
#include "Categories.hpp"
#include "Category.hpp"
#include "CategoryMember.hpp"
#include "CategoryMembers.hpp"
#include "CreateAccount.hpp"
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Page.hpp"
#include "Purge.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"
#include "Rollback.hpp"
#include "Search.hpp"
#include "SearchItem.hpp"
#include "Tokens.hpp"

// abstract
#include "WikimediaProject.hpp"
#include "WikimediaProjects.hpp"

using namespace std;

const string versionMajor = "201512290030";
const string versionMinor = "201512290030";

const string consolePrefixDefault = "[anonymous]> ";

string consolePrefix = consolePrefixDefault;
LoginInfo loginInfo;
MediaWikiActionAPI mwaapi;
chrono::nanoseconds timeout = chrono::seconds(1);
Tokens tokens;

void showHelp();
void showVersions();

vector<string> getCommandVector() {
 string commandLine;
 getline(cin, commandLine);
 //cout << "\tcommandLine (" << commandLine.length() << "): " << commandLine << endl;
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

bool expectsCategories(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("categories")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"content\"." << endl;
  return true;
 }
 if (commandVector.size() < 2) {
  cout << "Very few arguments for searching..." << endl;
  cout << "Search format:" << endl;
  cout << "\tcategories \"Name or id of a page\"" << endl;
  cout << "Example:" << endl;
  cout << "\tcategories \"Category:Google\"" << endl;
  return true;
 }
 Categories categories;  
 try {
  long pageids = stol(commandVector[1]);
  categories.pageids = to_string(pageids);
 } catch(...) {
  categories.titles = commandVector[1];
 }
 mwaapi.categories(&loginInfo, &categories); 
 if(categories.pages.size()==0) {
  cout << "Page with the title not found." <<  endl << "Read server response:" <<  endl << categories.res << endl;
  return true;
 }
 if(categories.pages[0].categories.size()==0) {
  cout << "Categories not found..." << endl << "Read server response:" <<  endl << categories.res << endl;
  return true;
 }
 while(categories.clcontinue_res.length()>0) {
  categories.clcontinue=categories.clcontinue_res;
  mwaapi.categories(&loginInfo, &categories);
 }
 cout<< "We've found " << categories.pages[0].categories.size() << " categories with titles:" << endl;  
 for(Category ci : categories.pages[0].categories) cout << "• " << ci.getTitleClear() << endl;
 return true;
}

bool expectsCategoryMembers(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("categorymembers")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"content\"." << endl;
  return true;
 }
 if (commandVector.size() < 1) {
  cout << "Very few arguments for searching..." << endl;
  cout << "Search format:" << endl;
  cout << "\tcategorymembers title" << endl;
  cout << "Example:" << endl;
  cout << "\tcategorymembers Category:Google" << endl;
  return true;
 }
 CategoryMembers categoryMembers;  
 try {
  long cmpageid = stol(commandVector[1]);
  categoryMembers.cmpageid = cmpageid;
 } catch(...) {
  categoryMembers.cmtitle = commandVector[1];
 }
 mwaapi.categoryMembers(&loginInfo, &categoryMembers); 
 if(categoryMembers.items.size()==0) {
  cout << "Something went wrong..." << endl << "Read server response:" <<  endl;
  cout << categoryMembers.res << endl;
  return true;
 } 
 while(categoryMembers.cmcontinue_res.length()>0) {
  categoryMembers.cmcontinue=categoryMembers.cmcontinue_res;
  mwaapi.categoryMembers(&loginInfo, &categoryMembers);
 }
 cout<< "We've found " << categoryMembers.items.size() << " pages:" << endl; 
 for(CategoryMember si : categoryMembers.items) cout << "• " << si.title << endl;
 return true;
}

bool expectsContent(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("content")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"content\"." << endl;
  return true;
 }
 if(commandVector.size() < 2) {
  cout << "Very few arguments for content..." << endl;
  cout << "Content format:" << endl;
  cout << "\tcontent \"Name or id of a page\"" << endl;
  cout << "Example:" << endl;
  cout << "\tcontent \"Main Page\"" << endl;
  cout << "\tcontent 15580374" << endl;
  return true;
 }
 Revisions revisions;
 try {
  long pageids = stol(commandVector[1]);
  revisions.pageids = to_string(pageids);
 } catch(...) {
  revisions.titles = commandVector[1];
 }
 //cout << "wikiconsole::expectsContent revisions.titles: " << revisions.titles << endl;
 revisions.prop="content";
 mwaapi.revisions(&loginInfo, &revisions);
 if(revisions.pages.size()==0) {
  cout << "Page not found..." << endl;
  return true;
 }
 cout << "Content of \"" << revisions.pages[0].title << "\" (" << revisions.pages[0].pageid  << ")" << endl;
 if(revisions.pages[0].revisions.size()==0) {
  cout << "Content not found." << endl;
  return true;
 }
 cout << revisions.pages[0].revisions[0].content << endl;
 return true;
}

bool expectsCreate(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("create") != 0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" before \"create\"." << endl;
  return true;
 }
 if(commandVector.size() < 2) {
  cout << "Very few arguments for content..." << endl;
  cout << "Content format:" << endl;
  cout << "\tcreate \"Name of page\"" << endl;
  cout << "Example:" << endl;
  cout << "\tcreate \"User:Test/Test\"" << endl;
  return true;
 }
 // Test page exists.
 Revisions revisions;
 revisions.titles = commandVector[1];
 revisions.prop="ids|timestamp";
 mwaapi.revisions(&loginInfo, &revisions);
 if(revisions.pages.size()>0 && revisions.pages[0].revisions.size() > 0) {
  cout << "Page \"" << revisions.titles << "\" already exists." << endl;
  cout << "Please use \"edit\" or \"upload\" for update." << endl;
  return true;
 }
 Edit edit;
 edit.title = commandVector[1];
 // One line editor
 vector<string> contentVector;
 cout << "Please type your conten of new page \"" << revisions.titles << "\" in this one line editor." << endl;
 cout << "Use commands from new line:" << endl;
 cout << "%EOF      To end editing and save." << endl;
 cout << "%QUIT     To quit from \"create\" wikiconsole command without save." << endl;
 while(true) {
  string s;
  cout << (contentVector.size()+1) << " <<< ";
  getline(cin, s);
  if(s.compare("%EOF") == 0) break;
  if(s.compare("%QUIT") == 0) {
   cout << "Creating the new page was interrupted without saving." << endl;
   return true;
  }
  contentVector.push_back(s);
 }
 for(string si : contentVector) edit.text += si+"\n";
 // Summary
 cout << "Please enter a summary (description) of the changes: " << endl;
 getline(cin, edit.summary);
 mwaapi.edit(&loginInfo, &tokens, &edit);
 if(edit.isSuccess()) {
  cout << "Page \"" << commandVector[1] << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else {
  cout << "Something went wrong..." << endl << "Read server response:" << endl;
  cout << edit.response << endl;
 }
 return true;
}

bool expectsCreateAccount(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("createaccount")!=0) return false;
 if(commandVector.size() < 6) {
  cout << "Very few arguments for content..." << endl;
  cout << "CreateAccount format:" << endl;
  cout << "createaccount \"Wikimedia site\" \"Username\" \"Password\" \"email\" \"reason\"" << endl;
  cout << "Example:" << endl;
  cout << "createaccount https://meta.wikimedia.org ExampleBot rte1EsB2 example.bot@gmail.ru \"For fun\"" << endl;
  return true;
 } 
 tokens.clear();
 loginInfo.clear();
 loginInfo.site = commandVector[1];
 loginInfo.lgname = commandVector[2];
 loginInfo.lgpassword = commandVector[3];
 CreateAccount createaccount;
 createaccount.site = commandVector[1];
 createaccount.name = commandVector[2];
 createaccount.password = commandVector[3];
 createaccount.email = commandVector[4];
 createaccount.reason = commandVector[5];
 mwaapi.createaccount(&loginInfo, &tokens, &createaccount);
 while(createaccount.result.compare("NeedCaptcha") == 0){
  cout << "Put answer " << createaccount.captchaUrl << " here." << endl;
  createaccount.captchaid = createaccount.captchaId;
  //cout << createaccount.captchaId << endl;
  //cout << createaccount.captchaid<<endl;
  string answer;
  cin>>answer;
  createaccount.captchaword = answer; 
  mwaapi.createaccount(&loginInfo, &tokens, &createaccount);
 }
 cout << "Account successfuly created." << endl; 
 cout << "Logining..." << endl; 
 loginInfo.site = createaccount.site;
 loginInfo.lgusername = createaccount.name;
 loginInfo.lgpassword = createaccount.password;
 mwaapi.login(&loginInfo, &tokens);
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

bool expectsDownload(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("download")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"download\"." << endl;
  return true;
 }
 if(commandVector.size() < 3) {
  cout << "Very few arguments for content..." << endl;
  cout << "Download format:" << endl;
  cout << "\tdownload \"Name or id of a page\" \"Path to file\"" << endl;
  cout << "Example:" << endl;
  cout << "\tdownload \"Main Page\" \"wikipedia.main.page\"" << endl;
  cout << "\tdownload 15580374 \"wikipedia.15580374\"" << endl;
  return true;
 }
 Revisions revisions;
 try {
  long pageids = stol(commandVector[1]);
  revisions.pageids = to_string(pageids);
 } catch(...) {
  revisions.titles = commandVector[1];
 }
 //cout << "wikiconsole::expectsDownload revisions.titles: " << revisions.titles << endl;
 revisions.prop="content";
 mwaapi.revisions(&loginInfo, &revisions);
 if(revisions.pages.size()==0) {
  cout << "Page not found..." << endl;
  return true;
 }
 if(revisions.pages[0].revisions.size()==0) {
  cout << "Content not found." << endl;
  return true;
 }
 ofstream outfile(commandVector[2]);
 if(outfile) {
  outfile << revisions.pages[0].revisions[0].content;
  cout << "Page \"" << revisions.pages[0].title << "\" (" << revisions.pages[0].pageid  << ") saved to file \"" << commandVector[2] << "\"" << endl;
 } else {
  cout << "Cannot save to file: " << commandVector[2] << endl;
 }
 return true;
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
  //cout << "\thistory \"Name or id of a page\" <number of revisions> <from id or date> <to id or date>" << endl;
  cout << "\thistory \"Name or id of a page\" <number of revisions> <from id> <to id>" << endl;
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
  revisions.limit = revisions.limitDefault;
 } else {
  try {
   long limit = stol(commandVector[2]);
   revisions.limit = limit;
  } catch(...) {
   cout << "Can not parsed number of revisions (rvlimit)..." << endl;
   cout << "Must be number or \"-\"." << endl;
   return true;
  }
 }
 if(commandVector.size() > 3) {
  try {
   long startid = stol(commandVector[3]);
   revisions.startid = startid;
  } catch(...) {
   revisions.start = commandVector[3];
  }
 }
 if(commandVector.size() > 4) {
  try {
   long endid = stol(commandVector[4]);
   revisions.endid = endid;
  } catch(...) {
   revisions.end = commandVector[4];
  }
 }
 revisions.prop="ids|flags|timestamp|user|userid|size|sha1|comment|tags|flagged";
 mwaapi.revisions(&loginInfo, &revisions);
 if(revisions.pages.size()==0) {
  cout << "Page not found..." << endl;
  return true;
 }
 cout << "Revision history of \"" << revisions.pages[0].title << "\" (" << revisions.pages[0].pageid  << ")" << endl;
 if(revisions.pages[0].revisions.size()==0) {
  cout << "Revisions not found." << endl;
  return true;
 }
 for(Revision r : revisions.pages[0].revisions) {
  cout << "(" << to_string(r.revid) << "|" << to_string(r.parentid) << ")  ";
  cout << r.timestamp << "  ";
  cout << r.user;
  for(unsigned int i=r.user.length(); i<20; i++) cout << ' ';
  if(r.minor>0) cout << "m .. "; 
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
 mwaapi.login(&loginInfo, &tokens);
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

bool expectsLoginAll(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("loginall")!=0) return false;
 if(commandVector.size() < 3) {
  cout << "Very few arguments to loginall..." << endl;
  cout << "Loginall format:" << endl;
  cout << "\tloginall username userpassword" << endl;
  cout << "Example:" << endl;
  cout << "\tloginall bob bobsecretpass" << endl;
  return true;
 }
 for(WikimediaProject wikimediaProject : WikimediaProjects::list) {
  if(wikimediaProject.active == 0) continue;
  loginInfo.site = wikimediaProject.getSite();
  loginInfo.lgusername = commandVector[1];
  loginInfo.lgpassword = commandVector[2];
  cout << "Login to: " << loginInfo.site << " ... ";
  mwaapi.login(&loginInfo, &tokens);
  if(loginInfo.result.compare("Success") != 0) {
   cout << "failed!" << endl;
   cout << "\tResponse:" << endl;
   cout << loginInfo.toJson() << endl;
  } else {
   cout << "success .";
   mwaapi.logout(&loginInfo);
   cout << ".";
   this_thread::sleep_for(timeout);
   cout << ". logout" << endl;
  }
  this_thread::sleep_for(timeout);
 }
 return true;
}

bool expectsLogEvents(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("logevents")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"content\"." << endl;
  return true;
 }
 LogEvents logEvents;
 if(commandVector.size() > 1) logEvents.lelimit = stol(commandVector[1]);
 mwaapi.logevents(&loginInfo, &logEvents);
 if(logEvents.events.size()==0) {
  cout << "Events not found..." << endl << "Read server response:" <<  endl << logEvents.res << endl;
  return true;
 }
 cout<< "We've found " << logEvents.events.size() << " events:" << endl;  
 for(LogEvent le : logEvents.events)  cout << "• " << le.toJson() << endl;
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

bool expectsPurge(const vector<string>& commandVector){
 if(commandVector.size()<1 || commandVector[0].compare("purge")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"history\"." << endl;
  return true;
 }
 if (commandVector.size() < 2) {
  cout << "Very few arguments for searching..." << endl;
  cout << "Purge format:" << endl;
  cout << "\tpurge title/id" << endl;
  cout << "Example:" << endl;
  cout << "\tpurge \"Main Page\"" << endl;
  return true;
 }
 Purge purge;  
 purge.titles=commandVector[1];
 mwaapi.purge(&loginInfo, &purge);
 if(purge.purgeRes != "") {
  cout << "Something went wrong..." << endl << "Read server response:" <<  endl;
  cout << purge.res << endl;
  return true;
 } else {
  cout<< "Success purge for \""+commandVector[1]+"\"" << endl;
 }
 return true;
}

bool expectsQuit(const vector<string>& commandVector) {
 if(commandVector[0].compare("bye") == 0
    || commandVector[0].compare("exit") == 0
    || commandVector[0].compare("quit") == 0
    || commandVector[0].compare("q") == 0
    || commandVector[0].compare("й") == 0)
  return true;
 return false;
}

bool expectsRecentChanges(const vector<string>& commandVector) {
 if(commandVector.size()<1) return false;
 if(commandVector[0].compare("recentchanges")!=0 && commandVector[0].compare("recent")!=0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" (can be a failed) before \"recentchanges\"." << endl;
  return true;
 }
 if(commandVector.size() < 2) {
  cout << "Very few arguments for recentchanges..." << endl;
  cout << "RecentChanges format:" << endl;
  cout << "\trecentchanges <number of revisions> <from date> <to date>" << endl;
  cout << "Example:" << endl;
  cout << "\trecentchanges 10" << endl;
  cout << "\trecentchanges 20 2015-12-29T00:30" << endl;
  cout << "\trecentchanges - 2015-12-29T00:30 2014-12-29T00:30" << endl;
  return true;
 }
 Revisions revisions;
 if(commandVector.size() < 2 || commandVector[1].compare("-")==0) {
  revisions.limit = revisions.limitDefault;
 } else {
  try {
   long limit = stol(commandVector[1]);
   revisions.limit = limit;
  } catch(...) {
   cout << "Can not parsed number of revisions (arvlimit)..." << endl;
   cout << "Must be number or \"-\"." << endl;
   return true;
  }
 }
 //cout << "[[wikiconsole::expectsRecentChanges]] revisions.limit: " << revisions.limit << endl;
 if(commandVector.size() > 2) revisions.start = commandVector[2];
 if(commandVector.size() > 3) revisions.end = commandVector[3];
 revisions.prop="ids|flags|timestamp|user|userid|size|sha1|comment|tags|flagged";
 mwaapi.allrevisions(&loginInfo, &revisions);
 if(revisions.revisions.size()==0) {
  cout << "Recent changes not found." << endl;
  return true;
 }
 // cout << "Revision history of \"" << revisions.pages[0].title << "\" (" << revisions.pages[0].pageid  << ")" << endl;
 for(Revision r : revisions.revisions) {
  cout << "(" << to_string(r.revid) << "|" << to_string(r.parentid) << ")  ";
  cout << r.timestamp << "  ";
  cout << r.user;
  for(unsigned int i=r.user.length(); i<20; i++) cout << ' ';
  if(r.minor>0) cout << "m .. "; 
  else cout << "  .. "; 
  cout << "(" << to_string(r.size) << " bytes)  ";
  cout << "(" << r.comment << ")";
  cout << endl;
 } 
 return true;
}

bool expectsRollback(const vector<string>& commandVector) {
 if(commandVector[0].compare("rollback") !=0) return false;
 if (commandVector.size() < 3) {
  cout << "Very few arguments to rallback..." << endl;
  cout << "Rollback format:" << endl;
  cout << "\trollback title/pageid username summary" << endl;
  cout << "Example:" << endl;
  cout << "\trollback \"Main Page\" DonSimon vandalism" << endl;
  return true;
 }
 Rollback rollback;
 try {
  long int pageid = stol(commandVector[1]);
  rollback.pageid = pageid;
 } catch(...) {
  rollback.title = commandVector[1];
 }
 rollback.user = commandVector[2];
 if(commandVector.size() < 4 && commandVector[3].length() == 0) {
  cout << "Please enter a summary (description) of the changes: " << endl;
  getline(cin, rollback.summary);
 } else {
  rollback.summary = commandVector[3];
 }
 mwaapi.rollback(&loginInfo, &tokens, &rollback);
 cout << "Read server response:" << endl << rollback.response << endl;
 return true;
}

bool expectsSearch(const vector<string>& commandVector){
 if(commandVector.size()<1 || commandVector[0].compare("search")!=0) return false;
 if (commandVector.size() < 1) {
  cout << "Very few arguments for searching..." << endl;
  cout << "Search format:" << endl;
  cout << "\tsearch srsearch" << endl;
  cout << "Example:" << endl;
  cout << "\tsearch ruble" << endl;
  return true;
 }
 Search search;  
 search.srsearch=commandVector[1];
 if(commandVector.size()>2) search.sroffset = stol(commandVector[2]);
 //cout << "wikiconsole::expectsSearch search.sroffset: " << search.sroffset << endl;
 mwaapi.search(&loginInfo, &search);
 if(search.items.size()==0) {
  cout << "Something went wrong..." << endl << "Read server response:" <<  endl;
  cout << search.res << endl;
  return true;
 } else {
  cout<< "We've found " << search.sroffset << " pages:" << endl;
  for(SearchItem si : search.items) cout << "• " << si.title << endl;
  if(search.sroffset_res > 0) cout << "To continue type: search \"" << commandVector[1] << "\" " << to_string(search.sroffset_res) << endl;
 }
 return true;
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

bool expectsSites(const vector<string>& commandVector) {
 if(commandVector.size()<1 || commandVector[0].compare("sites")!=0) return false;
 for(WikimediaProject wp : WikimediaProjects::list) cout << wp.getSite() << endl;
 return true;
}

bool expectsTokens(const vector<string>& commandVector){
 if(commandVector[0].compare("tokens") != 0) return false;
 if(!loginInfo.isLogin()) {
  cout << "You are not logined..." << endl;
  return true;
 };
 tokens.type = (commandVector.size()>1) ? commandVector[1] : tokens.allTokens;
 mwaapi.getTokens(&loginInfo, &tokens);
 if(tokens.centralauthtoken.length() != 0) cout << "centralauthtoken: " << tokens.centralauthtoken << endl;
 if(tokens.createaccounttoken.length() != 0) cout << "createaccounttoken: " << tokens.createaccounttoken << endl;
 if(tokens.csrftoken.length() != 0) cout << "csrftoken: " << tokens.csrftoken << endl;
 if(tokens.deletetoken.length() != 0) cout << "deletetoken: " << tokens.deletetoken << endl;
 if(tokens.deleteglobalaccounttoken.length() != 0) cout << "deleteglobalaccounttoken: " << tokens.deleteglobalaccounttoken << endl;
 if(tokens.edittoken.length() != 0) cout << "edittoken: " << tokens.edittoken << endl;
 if(tokens.emailtoken.length() != 0) cout << "emailtoken: " << tokens.emailtoken << endl;
 if(tokens.importtoken.length() != 0) cout << "importtoken: " << tokens.importtoken << endl;
 if(tokens.logintoken.length() != 0) cout << "logintoken: " << tokens.logintoken << endl;
 if(tokens.movetoken.length() != 0) cout << "movetoken: " << tokens.movetoken << endl;
 if(tokens.optionstoken.length() != 0) cout << "optionstoken: " << tokens.optionstoken << endl;
 if(tokens.patroltoken.length() != 0) cout << "patroltoken: " << tokens.patroltoken << endl;
 if(tokens.protecttoken.length() != 0) cout << "protecttoken: " << tokens.protecttoken << endl;
 if(tokens.rollbacktoken.length() != 0) cout << "rollbacktoken: " << tokens.rollbacktoken << endl;
 if(tokens.setglobalaccountstatustoken.length() != 0) cout << "setglobalaccountstatustoken: " << tokens.setglobalaccountstatustoken << endl;
 if(tokens.unblocktoken.length() != 0) cout << "unblocktoken: " << tokens.unblocktoken << endl;
 if(tokens.userrightstoken.length() != 0) cout << "userrightstoken: " << tokens.userrightstoken << endl;
 if(tokens.watchtoken.length() != 0) cout << "watchtoken: " << tokens.watchtoken << endl;
 return true;
}

bool expectsThank(const vector<string>& commandVector){
 if(commandVector[0].compare("thank") != 0) return false;
 if(commandVector.size() < 2) {
  cout << "Very few arguments to thank..." << endl;
  cout << "Thank format:" << endl;
  cout << "\tthank id" << endl;
  cout << "Example:" << endl;
  cout << "\tthank 419305" << endl;
  return true;
 }
 if(loginInfo.result.compare("Success") != 0) {
  cout << "You are not logined..." << endl;
  return true;
 };
 mwaapi.thank(&loginInfo, &tokens, commandVector[1]);
 return true;
}

bool expectsUndo(const vector<string>& commandVector){
 if(commandVector[0].compare("undo") !=0) return false;
 if (commandVector.size() < 3) {
  cout << "Very few arguments to rallback..." << endl;
  cout << "Rollback format:" << endl;
  cout << "\tundo \"Name of page\" \"Revision id\"" << endl;
  cout << "Example:" << endl;
  cout << "\tundo \"Main Page\" 123" << endl;
  return true;
 }
 Edit edit;
 try {
  long int pageid = stol(commandVector[1]);
  edit.pageid = pageid;
 } catch(...) {
  edit.title = commandVector[1];
 }
 //long int undo = stol(commandVector[2]);
 //edit.undo = undo;
 edit.undo = stol(commandVector[2]);
 mwaapi.edit(&loginInfo, &tokens, &edit);
 if(edit.isSuccess()) {
  cout << "Edit from page \"" << commandVector[1] << "\" (" << edit.pageidres << ") has been successfully undoded" << endl;
 } else {
  cout << "Something went wrong..." << endl << "Read server response:" << endl;
  cout << edit.response << endl;
 }
 return true;
}

bool expectsUpload(const vector<string>& commandVector){
 if(commandVector.size()<1 || commandVector[0].compare("upload") != 0) return false;
 if(loginInfo.site.length()==0) {
  cout << "You are not logged in..." << endl;
  cout << "Use \"login\" before \"upload\"." << endl;
  return true;
 }
 if(commandVector.size() < 3) {
  cout << "Very few arguments for upload..." << endl;
  cout << "Upload format:" << endl;
  cout << "\tupload \"Name of page\" \"Path to file\" <\"Summary (description) of the changes\">" << endl;
  cout << "Example:" << endl;
  cout << "\tupload \"User:Test/Test\" \"test\" \"update data\"" << endl;
  return true;
 }
 // Test file exists.
 struct stat buffer;   
 if (stat(commandVector[2].c_str(), &buffer) != 0) {
  cout << "File \"" + commandVector[2] + "\" not found.";
  return true;
 }
 Edit edit;
 try {
  long int pageid = stol(commandVector[1]);
  edit.pageid = pageid;
 } catch(...) {
  edit.title = commandVector[1];
 }
 ifstream infile(commandVector[2]);
 if(infile) {
  string l = "";
  while (getline(infile, l)) edit.text += l + "\n";
 } else {
  cout << "Cannot open file: " << commandVector[2] << endl;
 }
 // Summary
 if(commandVector.size() < 4 && commandVector[3].length() == 0) {
  cout << "Please enter a summary (description) of the changes: " << endl;
  getline(cin, edit.summary);
 } else {
  edit.summary = commandVector[3];
 }
 mwaapi.edit(&loginInfo, &tokens, &edit);
 if(edit.isSuccess()) {
  cout << "Page \"" << commandVector[1] << "\" (" << edit.pageidres << ") has been successfully updated with content from file \"" << commandVector[2] << "\"." << endl;
 } else {
  cout << "Something went wrong..." << endl << "Read server response:" << endl;
  cout << edit.response << endl;
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
 if(expectsCategories(commandVector)) return true;
 if(expectsCategoryMembers(commandVector)) return true;
 if(expectsContent(commandVector)) return true;
 if(expectsCreate(commandVector)) return true;
 if(expectsCreateAccount(commandVector)) return true;
 if(expectsDownload(commandVector)) return true;
 if(expectsEcho(commandVector)) return true;
 if(expectsHelp(commandVector)) return true;
 if(expectsHistory(commandVector)) return true;
 if(expectsLogin(commandVector))return true;
 if(expectsLoginAll(commandVector))return true;
 if(expectsLogout(commandVector)) return true;
 if(expectsLogEvents(commandVector)) return true;
 if(expectsPurge(commandVector)) return true;
 if(expectsRecentChanges(commandVector)) return true;
 if(expectsRollback(commandVector)) return true;
 if(expectsSite(commandVector)) return true;
 if(expectsSites(commandVector)) return true;
 if(expectsSearch(commandVector)) return true;
 if(expectsTokens(commandVector)) return true;
 if(expectsThank(commandVector)) return true;
 if(expectsUndo(commandVector)) return true;
 if(expectsUpload(commandVector)) return true;
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
 cout << "  categories      List all categories the pages belong to." << endl;
 cout << "                  Format: categories \"Name or id of a page\"" << endl;
 cout << "                  Example: categories \"Category:Google\"" << endl;
 cout << "  categorymembers List all pages in a given category." << endl;
 cout << "                  Format: categorymembers \"Name or id of a page\"" << endl;
 cout << "                  Example: categorymembers \"Category:Google\"" << endl;
 cout << "  content         Return content of a wikipage. Use after \"login\"." << endl;
 cout << "                  Format: content \"Name or id of a page\"" << endl;
 cout << "                  Example: content \"Main Page\"" << endl;
 cout << "  create          Create a wikipage. Use after \"login\"." << endl;
 cout << "                  Format: create \"User:Wikiapicpp/test page\"" << endl;
 cout << "                  Example: content \"Main Page\"" << endl;
 cout << "  createaccount   Create a new user account." << endl;
 cout << "                  Format: createaccount username password email reason" << endl;
 cout << "                  Example: createaccount https://meta.wikimedia.org ExampleBot rte1EsB2 example.bot@gmail.ru \"For fun\"" << endl;
 cout << "  download        Download and save content of a wikipage to a local disc. Use after \"login\"." << endl;
 cout << "                  Format: download \"Name or id of a page\" \"Path to file\"" << endl;
 cout << "                  Example: download \"Main Page\" \"wikipedia.main.page\"" << endl;
 cout << "  echo            Show parsed command line with options." << endl;
 cout << "  help            Show this help." << endl;
 cout << "                  Aliases: --help, -h, h, help." << endl;
 cout << "  history         Show standard history of page. Use after \"login\"." << endl;
 cout << "                  Format: history \"Name or id of a page\" <number of revisions> <from id or date> <to id or date>" << endl;
 cout << "                  Example: history \"Main Page\"" << endl;
 cout << "                  Type \"history\" without quotes and options for more information." << endl;
 cout << "  login           Login to a media wiki server." << endl;
 cout << "                  Format: login site username userpassword" << endl;
 cout << "                  Example: login https://en.wikipedia.org/ bob bobsecretpass" << endl;
 cout << "  loginall        Login to all media wiki projects." << endl;
 cout << "                  Format: loginall username userpassword" << endl;
 cout << "                  Example: loginall bob bobsecretpass" << endl;
 cout << "  logout          Log out and clear session data." << endl;
 cout << "  logevents       Get events from logs." << endl;
 cout << "  purge           Purge the cache for the given titles." << endl;
 cout << "                  Example: purge \"Main Page\"" << endl;
 cout << "  quit            Exit from console." << endl;
 cout << "                  Aliases: bye, exit, q." << endl;
 cout << "  recentchanges   Return recent changes of seledted wiki." << endl;
 cout << "                  Format: recentchanges <number of revisions> <from date> <to date>" << endl;
 cout << "                  Aliases: recent." << endl;
 cout << "  rollback        Roll back the last edits of the user of the page." << endl;
 cout << "                  Format: rollback \"Title or id of a page\" UserName \"Summary\"" << endl;
 cout << "  search          Perform a full text search." << endl;
 cout << "  site            Print url of connected site (after login or empty)." << endl;
 cout << "  sites           Print urls of all wikimedia projects." << endl;
 cout << "  tokens          Get tokens for data-modifying actions." << endl;
 cout << "                  Format: tokens <type>" << endl; 
 cout << "                   <type>  (separate with |): block, centralauth, csrf, delete, deleteglobalaccount, edit, email, import, move, options, patrol, protect, rollback, setglobalaccountstatus, unblock, userrights, watch." << endl;
 cout << "                  Example: tokens csrf" << endl;
 cout << "  thank           Send a thank-you notification to an editor." << endl; 
 cout << "  undo            Undo a revision." << endl;
 cout << "                  Format: undo \"Name or id of a page\" \"Id of revision\"" << endl;
 cout << "  upload          Upload content of a file from local disc to a wikipage. Use after \"login\"." << endl;
 cout << "                  Format: upload \"Name or id of a page\" \"Path to file\" <\"Summary (description) of the changes\">" << endl;
 cout << "                  Example: upload \"Main Page\" \"apage\" \"update data\"" << endl;
 cout << "  versions        Show versions of wikiconsole and components (major.minor)." << endl;
 cout << "                  Aliases: --version, --versions, -v, version, versions." << endl;
 cout << endl;
}

void showVersions() {
 cout << endl << "Versions of wikiconsole and components (major.minor):" << endl << endl;
 cout << "\twikiconsole " << versionMajor << "." << versionMinor << endl << endl;
 cout << "\tCategories " << Categories::versionMajor << "." << Categories::versionMinor << endl;
 cout << "\tCategoryMembers " << CategoryMembers::versionMajor << "." << CategoryMembers::versionMinor << endl;
 cout << "\tCategoryMember " << CategoryMember::versionMajor << "." << CategoryMember::versionMinor << endl;
 cout << "\tCurlWrapper " << CurlWrapper::versionMajor << "." << CurlWrapper::versionMinor << endl;
 cout << "\tEdit " << Edit::versionMajor << "." << Edit::versionMinor << endl;
 cout << "\tLoginInfo " << LoginInfo::versionMajor << "." << LoginInfo::versionMinor << endl;
 cout << "\tMediaWikiActionAPI " << MediaWikiActionAPI::versionMajor << "." << MediaWikiActionAPI::versionMinor << endl;
 cout << "\tPage " << Page::versionMajor << "." << Page::versionMinor << endl;
 cout << "\tPurge " << Purge::versionMajor << "." << Purge::versionMinor << endl;
 cout << "\tRevision " << Revision::versionMajor << "." << Revision::versionMinor << endl;
 cout << "\tRevisions " << Revisions::versionMajor << "." << Revisions::versionMinor << endl;
 cout << "\tRollback " << Rollback::versionMajor << "." << Rollback::versionMinor << endl;
 cout << "\tSearch " << Search::versionMajor << "." << Search::versionMinor << endl;
 cout << "\tSearchItem " << SearchItem::versionMajor << "." << SearchItem::versionMinor << endl;
 cout << "\tTokens " << Tokens::versionMajor << "." << Tokens::versionMinor << endl;
 cout << "\tWikimediaProject " << WikimediaProject::versionMajor << "." << WikimediaProject::versionMinor << endl;
 cout << "\tWikimediaProjects " << WikimediaProjects::versionMajor << "." << WikimediaProjects::versionMinor << endl;
 cout << endl;
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

