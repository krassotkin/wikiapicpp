/*
 activity.cpp is console tool to display the current activity on wikimedia projects.

 Compiling:
 make

 Usage:
 ./activity <-option> [<-option>] <url> [<-url>]

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <chrono> 
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <tuple>

using namespace std;

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Revisions.hpp"
#include "Tokens.hpp"

const chrono::milliseconds TIMEOUT_MS(1000);

struct ActivityTask {
 string lastTimestamp = "";
 LoginInfo loginInfo;
 Tokens tokens;
};

MediaWikiActionAPI mwaapi;
map<string,bool> options;
vector<ActivityTask> tasks;

string description() {
 return "activity is a console tool to display the current activity on wikimedia projects.";
}

void processTask(ActivityTask* task) {
 Revisions revisions;
 revisions.end = task->lastTimestamp;
 //cout << "\t\tactivity::processTask revisions.end: " << revisions.end << endl;
 //revisions.prop = "ids|flags|timestamp|user|userid|size|sha1|contentmodel|parsedcomment|content|tags|parsetree";
 revisions.prop = "comment|flags|ids|size|timestamp|user|userid";
 mwaapi.allrevisions(&task->loginInfo, &revisions);
 if(revisions.revisions.size() == 0) return;
 sort(revisions.revisions.begin(), 
      revisions.revisions.end(),
      [] (const Revision& a, const Revision& b) -> bool {return a.revid < b.revid;});
 for(unsigned ir =1; ir < revisions.revisions.size(); ir++) {
  Revision r = revisions.revisions[ir];
  // for(Revision r : revisions.revisions) {
  string tagsJsonString = "";
  for(string it : r.tags) tagsJsonString += (string)(tagsJsonString.length()==0 ? "" : ",") + "\""+it+"\"";
  cout << "• "
       << task->loginInfo.site << ": "
       << "{"
       << "\"revid\":" << r.revid
       << ",\"parentid\":" << r.parentid
       << ",\"timestamp\":\"" << r.timestamp << "\""
       << ",\"ns\":\"" << r.ns << "\""
       << ",\"pageid\":\"" << r.pageid << "\""
       << ",\"title\":\"" << r.title << "\""
       << (r.minor==-1 ? "" : ",\"minor\":\"\"") 
       << (r.anon==-1 ? "" : ",\"anon\"=\"\"")
       << ",\"user\":\"" << r.user << "\""
       << ",\"userid\":" << r.userid
       << ",\"size\":" << r.size
       << ",\"comment\":\"" << r.comment << "\""
       << (r.tags.size() == 0 ? "" : ",\"tags\":["+tagsJsonString + "]")
       << "}" << endl;
 }
 task->lastTimestamp = revisions.revisions.back().timestamp;
 //cout << "\t\tactivity::processTask task->lastTimestamp: " << task->lastTimestamp << endl;
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

 for(int ia=1; ia < argc; ia++) {
  string as(argv[ia]);
  if(as.length() == 0) continue;
  if(as[0] == '-' && options.find(as) == options.end()) {
   options[as] = true;
  } else {
   ActivityTask task;
   task.loginInfo.site = as;
   tasks.push_back(task);
  }
 }

 if(tasks.size() == 0) {
  cout << "Wikimedia sites (urls) for task not found..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -2;
 }

 cout << "Started..." << endl;
 cout << "Please press Ctrl+C to stop." << endl;
 while(true) {
  for(unsigned int it=0; it < tasks.size(); it++) {
   ActivityTask* task = &tasks[it];
   processTask(task);
   this_thread::sleep_for(TIMEOUT_MS);
  }
  /*
   for(ActivityTask task : tasks) {
    processTask(task);
    this_thread::sleep_for(TIMEOUT_MS);
   }
  */
 }

 return 0;
}
 
