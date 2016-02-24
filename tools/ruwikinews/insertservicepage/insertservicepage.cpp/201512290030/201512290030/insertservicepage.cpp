/*
 insertservicepage is a console tool of the wikiapicpp project used to insert template {{Служебная информация}} in articles and creating pages of stats with template {{Статистика страницы}}.

 Compiling:
 make

 Usage:

 For insertservicepage:
 ./insertservicepage <site> <botusername> <botuserpassword> <title>

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Tokens.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"

string description() {
 return "insertservicepage is a console tool of the wikiapicpp project used to insert template {{Служебная информация}} in articles and creating pages of stats with template {{Статистика страницы}}.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\tShow this help:\n"
         + "\t\t./insertservicepage --help\n"
         + "\tinsertservicepage in article:\n"
         + "\t\t./insertservicepage <site> <botusername> <botuserpassword> <title>\n");
}

int main(int argc, char *argv[]) {
 if(argc == 2) {
  string firstArg = argv[1];
  if(firstArg.compare("--help") == 0
     || firstArg.compare("-h") == 0
     || firstArg.compare("-help") == 0
     || firstArg.compare("help") == 0
     || firstArg.compare("h") == 0) {
   cout << description() << endl << endl;
   cout << usage() << endl;
   return 0;
  }
 }

 if(argc < 5) {
  cout << "Very few arguments..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 LoginInfo loginInfo;
 loginInfo.site = argv[1];
 loginInfo.lgname = argv[2];
 loginInfo.lgpassword = argv[3];

 Tokens tokens;

 MediaWikiActionAPI mwaapi;
 mwaapi.login(&loginInfo, &tokens);

 if(loginInfo.result.compare("Success") != 0) {
  cout << "Login failed..." << endl;
  cout << "Response:" << endl;
  cout << loginInfo.toJson() << endl;
  return 0;
 } else {
  cout << "Success logined..." << endl;
 }

 Revisions revisions;
 revisions.titles = argv[4];
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
 string pageContent = revisions.pages[0].revisions[0].content;
 
 //cout << "[insertservicepage] pageContent: \n" << pageContent << endl;

 size_t pos = pageContent.find("{{Служебная информация}}");
 size_t pos1 = pageContent.find("{{служебная информация}}");
 if (pos != std::string::npos || pos1 != std::string::npos ) {
  cout << "Service Page have ever belong to page it position: " << pos << endl;
  return 0;
 }

 pos = pageContent.length();
 size_t findPos = pageContent.find("{{Категории|");
 //cout << "[insertservicepage] findPos (\"{{Категории|\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 findPos = pageContent.find("[[Категория:");
 //cout << "[insertservicepage] findPos (\"[[Категория:\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 findPos = pageContent.find("[[Category:");
 //cout << "[insertservicepage] findPos (\"[[Category:\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 findPos = pageContent.find("{{категории|");
 //cout << "[insertservicepage] findPos (\"{{категории|\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 findPos = pageContent.find("[[категория:");
 //cout << "[insertservicepage] findPos (\"[[категория:\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 findPos = pageContent.find("[[category:");
 //cout << "[insertservicepage] findPos (\"[[category:\"): \n" << findPos << endl;
 if(findPos != std::string::npos && findPos < pos) pos = findPos;
 //cout << "[insertservicepage] pos (\"minimum\"): \n" << pos << endl;

 if (pos == pageContent.length()) {
  cout << "Categories not found..." << pos << endl;
  return 0;
 }

 pageContent = pageContent.insert(pos, "\n\n{{-}}\n\n{{Служебная информация}}\n\n");
 // cout << "New version of page: " << pageContent << endl;

 Edit edit;
 edit.title = argv[4];
 edit.text = pageContent;
 edit.summary = "Добавление шаблона {{Служебная информация}}.";
 mwaapi.edit(&loginInfo, &tokens, &edit);

 edit.clear();
 edit.title=(string)"Викиновости:Статистика страниц/"+argv[4];
 edit.text="{{Статистика страницы}}";
 mwaapi.edit(&loginInfo, &tokens, &edit);

 cout << "All tasks are successfully completed." << endl;

 return 0;
}
 
