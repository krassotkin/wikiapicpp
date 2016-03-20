#ifndef WELCOME_HPP
#define WELCOME_HPP
/*
 Welcome.hpp is a class of the wikiapicpp project used to welcome new users.

 Tasks page example: 
 https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <chrono>  
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "Edit.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Revisions.hpp"
#include "Tokens.hpp"

struct WelcomeTask {
 LoginInfo loginInfo;
 string project;
 string summary;
 string temp; // welcome template
 Tokens tokens;
 vector<tuple<string,string>> users; //  username & signature
 unsigned int usersPointer = 0;
};

class Welcome {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const int COUNT_OF_LAST_CHANGES = 10;
  //const chrono::milliseconds TIMEOUT_MS(1000);

  string errJson;
  MediaWikiActionAPI* mwaapi;
  LoginInfo* loginInfo;
  map<long int, bool> processedRevisions;
  map<string,WelcomeTask*> siteTaskMap;
  vector<WelcomeTask> tasksVector;
  string tasksPage;
  string tasksPageName; // For example: User:Wikiapicpp/Settings/Welcome
  chrono::milliseconds timeout_ms = chrono::milliseconds(1000);
  Tokens* tokens;
  map<string, bool> processedUsers;

  Welcome() {}

  Welcome(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens) : mwaapi(mwaapi), loginInfo(loginInfo), tokens(tokens) {
   init();
  }

  Welcome(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& tasksPageName) : mwaapi(mwaapi), loginInfo(loginInfo), tasksPageName(tasksPageName), tokens(tokens) {
   init();
  }

  void init() {
   loadTasks();
  }

  void loadTasks() {
   loadTasksPage();
   parseTasks();
  }

  void loadTasksPage() {
   tasksPage.clear();
   if(loginInfo->site.length()==0) return;
   if(tasksPageName.length()==0) return;
   Revisions revisions;
   revisions.titles = tasksPageName;
   revisions.prop="content";
   mwaapi->revisions(loginInfo, &revisions);
   if(revisions.pages.size()==0) return;
   if(revisions.pages[0].revisions.size()==0) return;
   tasksPage = revisions.pages[0].revisions[0].content;
   cout << "[Welcome::loadTasksPage] tasksPage:" << endl << tasksPage << endl;
  }

  void parseTasks() {
   tasksVector.clear();
   if(tasksPage.length()==0) return;
   auto json = json11::Json::parse(tasksPage, errJson);
   auto tasksJson = json["tasks"].array_items();
   cout << "[Welcome::parseTasks] tasksJson.size(): " << tasksJson.size() << endl;
   for(auto ti : tasksJson) {
    auto tio = ti.object_items();
    cout << "[Welcome::parseTasks] tio.size(): " << tio.size() << endl;
    WelcomeTask task;
    task.project = tio["project"].string_value();
    task.loginInfo.update(tio["site"].string_value(), loginInfo->lgname, loginInfo->lgpassword);
    mwaapi->login(&task.loginInfo, &task.tokens);
    cout << (task.loginInfo.isSuccess() ? "Success logined to " : "Login failed to ") << task.loginInfo.site << endl;
    task.temp = tio["template"].string_value();
    task.summary = tio["summary"].string_value();
    vector<tuple<string,string>> usersVector;
    auto usersJson = tio["users"].array_items();
    for(auto ui : usersJson) {
     auto uio = ui.object_items();
     usersVector.push_back(make_tuple(uio["username"].string_value(),uio["signature"].string_value()));
    }
    task.users = usersVector;
    tasksVector.push_back(task);
    siteTaskMap[task.loginInfo.site] = &task;
   }
   //cout << "[Welcome::parseTasks] tasksToJson:" << endl << tasksToJson() << endl;
  }

  void processTask(WelcomeTask* task, const int& countOfLastChanges) {
   Revisions revisions;
   revisions.limit = countOfLastChanges;
   revisions.prop = "flags|ids|user|userid";
   mwaapi->allrevisions(&task->loginInfo, &revisions);
   //cout << "[Welcome::processTask] revisions.revisions.size():" << revisions.revisions.size() << endl;
   if(revisions.revisions.size() == 0) {
    cout << "[Welcome::processTask] Revisions not found." << endl;
    return;
   }
   for(Revision ir : revisions.revisions) {
    //cout << "[Welcome::processTask] (before) ir.toJson(): " << ir.toJson() << endl;
    if(processedRevisions.find(ir.revid) != processedRevisions.end()) continue;
    processedRevisions[ir.revid] = true;
    if(ir.anon == 1) continue;
    if(processedUsers.find(ir.user) != processedUsers.end()) continue;
    processedUsers[ir.user] = true;
    cout << "[Welcome::processTask] (after) ir.toJson(): " << ir.toJson() << endl;
    cout << "[Welcome::processTask] To welcomeUserRaw ir.user: " << ir.user << endl;
    welcomeUserRaw(task, ir.user);
   }
  }

  void runAsDaemon() {
   while(true) {
    welcomeLastUsers(COUNT_OF_LAST_CHANGES);
    this_thread::sleep_for(timeout_ms);
   }
  }

  string tasksToJson() {
   string res = "{\n";
   res+=" \"tasksVector\": [\n";
   for(WelcomeTask ti : tasksVector) {
    res += (string) "           {\n"
         + "            \"project\":\"" + ti.project + "\",\n"
         + "            \"site\":\"" + ti.loginInfo.site + "\",\n"
         + "            \"template\":\"" + ti.temp + "\",\n"
         + "            \"summary\":\"" + ti.summary + "\",\n"
         + "            \"users\":[";
    bool f = true;                 
    for(auto ui : ti.users) {   
     res += (string)(f ? "" : ",")
          + "\n                     "
          + "{\"username\":\"" + get<0>(ui) + "\",\"signature\":\"" + get<1>(ui) + "\"}";
     f = false;                   
    }                              
    res+="\n                    ]\n";
   }
   res += "           }\n";
   res += "          ]\n"; // tasksVector close
   res += "}\n\n";
   return res;
  }

  void welcomeLastUsers(const int& countOfLastChanges) {
   for(WelcomeTask task : tasksVector) processTask(&task, countOfLastChanges);
  }

  void welcomeRevision(LoginInfo* loginInfo, Revision* revision) {
   welcomeUserRaw(siteTaskMap[loginInfo->site], revision->user);
  }

  void welcomeUser(const string& userName) {
   for(WelcomeTask task : tasksVector)
    if(task.loginInfo.site.compare(loginInfo->site) == 0)
     welcomeUserRaw(&task, userName);
  }

  void welcomeUserRaw(WelcomeTask* task, const string& userName) {
   Revisions revisions;
   revisions.titles = "User talk: "+userName;
   cout << "[Welcome::welcomeUserRaw] revisions.title: " << revisions.titles << endl;
   revisions.prop="content";
   mwaapi->revisions(&task->loginInfo, &revisions);
   cout << "[Welcome::welcomeUserRaw] revisions.pages.size(): " << revisions.pages.size() << endl;
   if(revisions.pages.size() == 0) { // Not found... and strange error.
    cout << "[Welcome::welcomeUserRaw] Not found... and strange error." << endl;
    return;
   }
   cout << "[Welcome::welcomeUserRaw] revisions.pages[0].revisions.size(): " << revisions.pages[0].revisions.size() << endl;
   if(revisions.pages[0].revisions.size() != 0) { // Page exists
    cout << "[Welcome::welcomeUserRaw] Page exists." << endl;
    return; 
   }
   string signature;
   if(task->users.size() == 0) {
    signature = "~~~~";
   } else {
    if(task->usersPointer >= task->users.size()) task->usersPointer = 0;
    signature = get<1>(task->users[task->usersPointer]);
    task->usersPointer++;
   }
   Edit edit;
   edit.title = revisions.titles;
   edit.text = "{{"
             + task->temp
             + "}}\n"
             + signature
             + "\n";
   edit.summary = task->summary;
   cout << "[Welcome::welcomeUser] edit.text: \n" << edit.text << endl;
   if(!task->loginInfo.isLogin()) {
    cout << "[Welcome::welcomeUser] editLoginInfo->isLogin(): \n" << task->loginInfo.isLogin() << endl;
    return; // not logined
   }
   mwaapi->edit(&task->loginInfo, &task->tokens, &edit);   
  }

};

const string Welcome::versionMajor = "201512290030";
const string Welcome::versionMinor = "201512290030";

#endif // #ifndef WELCOME_HPP
 
