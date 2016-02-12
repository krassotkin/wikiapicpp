#ifndef PROJECTSNEWSFEEDS_HPP
#define PROJECTSNEWSFEEDS_HPP
/*
 ProjectsNewsFeeds.hpp update projects wikinews feeds in Wikipedia.

 Tasks page example: https://ru.wikinews.org/wiki/User:Wikiapicpp/Settings/ProjectsNewsFeeds

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "CategoryMember.hpp"
#include "CategoryMembers.hpp"
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Revisions.hpp"

struct ProjectsNewsFeedsTask {
 vector<string> categories;
 string goal;
 unsigned int limit;
 string site;
};

class ProjectsNewsFeeds {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string errJson;
  MediaWikiActionAPI* mwaapi;
  LoginInfo* loginInfo;
  bool status=false;
  vector<ProjectsNewsFeedsTask> tasks;
  string tasksPage;
  string tasksPageName; // For example: User:Wikiapicpp/Settings/ProjectsNewsFeeds
  Tokens* tokens;

  ProjectsNewsFeeds() {}

  ProjectsNewsFeeds(MediaWikiActionAPI* mwaapi, LoginInfo* loginInfo, Tokens* tokens, const string& tasksPageName) : mwaapi(mwaapi), loginInfo(loginInfo), tasksPageName(tasksPageName), tokens(tokens) {
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
   //cout << "\t\tProjectsNewsFeeds::loadTasksPage tasksPage:" << endl << tasksPage << endl;
  }

  void parseTasks() {
   tasks.clear();
   if(tasksPage.length()==0) return;
   auto json = json11::Json::parse(tasksPage, errJson);
   auto tasksJson = json["tasks"].array_items();
   //cout << "\t\tProjectsNewsFeeds::parseTasks tasksJson.size(): " << tasksJson.size() << endl;
   for(auto ti : tasksJson) {
    auto tio = ti.object_items();
    //cout << "\t\tProjectsNewsFeeds::parseTasks tio.size(): " << tio.size() << endl;
    ProjectsNewsFeedsTask task;
    task.site = tio["site"].string_value();
    task.goal = tio["goal"].string_value();
    task.limit = tio["limit"].number_value();
    vector<string> categoriesVector;
    auto categoriesJson = tio["categories"].array_items();
    for(auto ci : categoriesJson) {
     categoriesVector.push_back(ci.string_value());
    }
    task.categories = categoriesVector;
    tasks.push_back(task);
   }
   //cout << "\t\tProjectsNewsFeeds::parseTasks tasksToJson:" << endl << tasksToJson() << endl;
  }

  void processTask(ProjectsNewsFeedsTask* task) {
   vector<Pages> goodNews;
   if(task->categories.size()==0) return;

   // Select last news from first category in task
   CategoryMembers categoryMembers;
   categoryMembers.cmsort="timestamp";
   categoryMembers.cmdir="desc";
   categoryMembers.cmlimit = 50;
   categoryMembers.cmnamespace=0;
   categoryMembers.cmprop="ids|title|timestamp";
   categoryMembers.cmtitle="Category:"+task->categories[0];
   mwaapi->categoryMembers(loginInfo, &categoryMembers);

   selectGoodNews(task, &categoryMembers, &goodNews);

   while(goodNews.size() < task->limit && categoryMembers.cmcontinue_res.length()>0) {
    categoryMembers.items.clear();
    categoryMembers.cmcontinue=categoryMembers.cmcontinue_res;
    mwaapi->categoryMembers(loginInfo, &categoryMembers);
    selectGoodNews(task, &categoryMembers, &goodNews);
   } 

   if(goodNews.size() == 0) {
    status &= false;
    return;
   }

   // Sort articles by id desc
   sort(goodNews.begin(), 
        goodNews.end(), 
        [](const Pages& a, const Pages& b) -> bool {return a.pageid > b.pageid;});
 
   // Post last news to goal
   LoginInfo loginInfoForEdit;
   loginInfoForEdit.lgusername = loginInfo->lgusername;
   loginInfoForEdit.lgpassword = loginInfo->lgpassword;
   loginInfoForEdit.site = task->site;
   Tokens tokensForEdit;
   mwaapi->login(&loginInfoForEdit, &tokensForEdit);
   Edit edit;
   edit.title = task->goal;
   for(unsigned int ig=0; ig<task->limit; ig++) edit.text += "* [[n:" + goodNews[ig].title + "|" + goodNews[ig].title + "]]\n";
   edit.summary = "Update news feed (test)";
   edit.bot = 1;
   mwaapi->edit(&loginInfoForEdit, &tokensForEdit, &edit);
   status &= edit.isSuccess();
  }

  void run() {
   status = true;
   for(ProjectsNewsFeedsTask task : tasks) processTask(&task);
  }

  void runForCategories(map<string,bool>* categoriesMap) {
  }

  void selectGoodNews(ProjectsNewsFeedsTask* task, CategoryMembers* categoryMembers, vector<Pages>* goodNews) {
   const string CATEGORY_PREFIX = "Category:";
   Categories categories;
   for(CategoryMember cm : categoryMembers->items) categories.pageids += (categories.pageids.length()==0?"":"|")+to_string(cm.pageid);
   for(string cs : task->categories) categories.clcategories += (categories.clcategories.length()==0?"":"|")+CATEGORY_PREFIX+cs;
   categories.cllimit = 50;
   categories.cldir = "descending";
   mwaapi->categories(loginInfo, &categories);
   while(categories.clcontinue_res.length()>0) {
    categories.clcontinue=categories.clcontinue_res;
    mwaapi->categories(loginInfo, &categories);
   }
   for(Pages p : categories.pages) {
    if(p.categories.size() == task->categories.size()) goodNews->push_back(p);
   }
  }

  string tasksToJson() {
   string res = "{\n";
   res+=" \"tasks\": [\n";
   for(ProjectsNewsFeedsTask ti : tasks) {
    res+="           {";
    res+="\"site\":\"" + ti.site + "\", ";
    res+="\"goal\":\"" + ti.goal + "\", ";
    res+="\"limit\":\"" + to_string(ti.limit) + "\", ";
    res+="\"categories\":[";
    bool f = true;
    for(string ci : ti.categories) {
     res+= (string)(f ? "" : ", ") + "\"" + ci + "\"";
     f = false;
    }
    res+="]\n";
   }
   res+="          ]\n"; // tasks close
   res+="}\n\n";
   return res;
  }

};

const string ProjectsNewsFeeds::versionMajor = "201512290030";
const string ProjectsNewsFeeds::versionMinor = "201512290030";

#endif // #ifndef PROJECTSNEWSFEEDS_HPP
 
