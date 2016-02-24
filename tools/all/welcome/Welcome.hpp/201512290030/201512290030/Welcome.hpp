#ifndef WELCOME_HPP
#define WELCOME_HPP
/*
 Welcome.hpp is a class of the wikiapicpp project used to welcome new users.

 Tasks page example: 
 https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/Welcome

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <iostream>
#include <string>
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
};

class Welcome {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string errJson;
  MediaWikiActionAPI* mwaapi;
  LoginInfo* loginInfo;
  bool status=false;
  vector<WelcomeTask> tasks;
  string tasksPage;
  string tasksPageName; // For example: User:Wikiapicpp/Settings/Welcome
  Tokens* tokens;

  Welcome() {}

  Welcome(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens) : mwaapi(mwaapi), loginInfo(loginInfo), tokens(tokens) {
   loadTasks();
  }

  Welcome(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& tasksPageName) : mwaapi(mwaapi), loginInfo(loginInfo), tasksPageName(tasksPageName), tokens(tokens) {
   loadTasks();
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
   tasks.clear();
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
/*
    task.loginInfo.lgname = loginInfo->lgname;
    cout << "[Welcome::parseTasks] loginInfo->lgname: " << loginInfo->lgname << endl;
    cout << "[Welcome::parseTasks] task.loginInfo.lgname: " << task.loginInfo.lgname << endl;
    task.loginInfo.lgpassword = loginInfo->lgpassword;
    task.loginInfo.site = tio["site"].string_value();
*/
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
    tasks.push_back(task);
   }
   cout << "[Welcome::parseTasks] tasksToJson:" << endl << tasksToJson() << endl;
  }

  void processTask(WelcomeTask* task) {
   //status &= edit.isSuccess();
   status = false;
  }

  void run() {
   status = true;
   for(WelcomeTask task : tasks) processTask(&task);
  }

  string tasksToJson() {
   string res = "{\n";
   res+=" \"tasks\": [\n";
   for(WelcomeTask ti : tasks) {
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
   res += "          ]\n"; // tasks close
   res += "}\n\n";
   return res;
  }

  bool welcomeUser(const string& userName) {
   Revisions revisions;
   revisions.titles = "User talk:"+userName;
   cout << "[Welcome::welcomeUser] revisions.title:" << revisions.titles << endl;
   revisions.prop="content";
   mwaapi->revisions(loginInfo, &revisions);
   cout << "[Welcome::welcomeUser] revisions.pages.size():" << revisions.pages.size() << endl;
   if(revisions.pages.size() == 0) return false; // Not found... and strange error.
   cout << "[Welcome::welcomeUser] revisions.pages[0].revisions.size():" << revisions.pages[0].revisions.size() << endl;
   if(revisions.pages[0].revisions.size() != 0) return false; // Exists
   LoginInfo *editLoginInfo;
   Edit edit;
   edit.title = revisions.titles;
   cout << "[Welcome::welcomeUser] loginInfo->site:" << loginInfo->site << endl;
   for(WelcomeTask task : tasks) {
    cout << "[Welcome::welcomeUser] task.loginInfo.site:" << task.loginInfo.site << endl;
    if(task.loginInfo.site.compare(loginInfo->site) == 0) {
     edit.text = "{{"
               + task.temp
               + "}}\n"
               + "~~~~\n";
     edit.summary = task.summary;
     editLoginInfo = &task.loginInfo;
     break;
    }
   }
   cout << "[Welcome::welcomeUser] edit.text:\n" << edit.text << endl;
   if(!editLoginInfo->isLogin()) {
   cout << "[Welcome::welcomeUser] editLoginInfo->isLogin():\n" << editLoginInfo->isLogin() << endl;
    return false; // not logined
   }
   mwaapi->edit(editLoginInfo, tokens, &edit);
   if(edit.isSuccess()) return true;
   return false;
  }

};

const string Welcome::versionMajor = "201512290030";
const string Welcome::versionMinor = "201512290030";

#endif // #ifndef WELCOME_HPP
 
