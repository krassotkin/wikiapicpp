/*
 insertservicepage is a console tool of the wikiapicpp project used to insert service page in articles.

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
 return "insertservicepage is a console tool of the wikiapicpp project used to insert service page in articles.";
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

 MediaWikiActionAPI mwaapi;
 LoginInfo loginInfo;
 Revisions revisions;
 Edit edit;
 loginInfo.site = argv[1];
 loginInfo.lgname = argv[2];
 loginInfo.lgpassword = argv[3];
 try {
  long pageids = stol(argv[4]);
  revisions.pageids = to_string(pageids);
  edit.pageid = pageids;
 } catch(...) {
  revisions.titles = argv[4];
  edit.title = argv[4];
 }
 revisions.prop="content";
 edit.summary = "Insert service page";
 Tokens tokens;

 mwaapi.login(&loginInfo, &tokens);
 if(loginInfo.result.compare("Success") != 0) {
  cout << "Login failed..." << endl;
  cout << "Response:" << endl;
  cout << loginInfo.toJson() << endl;
  return 0;
 } else {
  cout << "Success logined..." << endl;
 }
 
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
 
 cout << "[insertservicepage] pageContent: \n" << pageContent << endl;

 long int positionOfSP = pageContent.find("{{Служебная информация}}");
 long int positionOfCategoryByFiguration = pageContent.find("{{Категории");
 long int positionOfCategoryBySquare = pageContent.find("[[Категория");
 long int positionOfCategoryByEnglish = pageContent.find("[[Category");
 long int positionOfCategoryByFigurationSmallRegiseter = pageContent.find("{{категории");
 long int positionOfCategoryBySquareSmallRegiseter = pageContent.find("[[категория");
 long int positionOfCategoryByEnglishSmallRegiseter = pageContent.find("[[category");
 long int minimumOfPosition=0;

 //cout << "[insertservicepage] positionOfSP: \n" << positionOfSP << endl;
 //cout << "[insertservicepage] positionOfHYS: \n" << positionOfHYS << endl;
 //cout << "[insertservicepage] positionOfCategoryByFiguration: \n" << positionOfCategoryByFiguration << endl;
 //cout << "[insertservicepage] positionOfCategoryBySquare: \n" << positionOfCategoryBySquare << endl;
 //cout << "[insertservicepage] positionOfCategoryByEnglish: \n" << positionOfCategoryByEnglish << endl;

 if (positionOfSP>0) {
 cout << " Service Page have ever belong to page" << endl;
 return 0;
 }
 if ( ( (positionOfCategoryByFiguration) < 0 ) && ( ( positionOfCategoryBySquare ) < 0 ) ) minimumOfPosition = positionOfCategoryByEnglish;
 else if ( ( (positionOfCategoryByEnglish) < 0 ) && ( ( positionOfCategoryByFiguration ) < 0 ) ) minimumOfPosition = positionOfCategoryBySquare;
 else if ( ( (positionOfCategoryByEnglish) < 0 ) && ( ( positionOfCategoryBySquare ) < 0 ) ) minimumOfPosition = positionOfCategoryByFiguration;
 else if ( ( (positionOfCategoryByFiguration) > 0 ) && ( ( positionOfCategoryBySquare ) > 0 ) ) minimumOfPosition = min(positionOfCategoryByFiguration, positionOfCategoryBySquare);
 else if ( ( (positionOfCategoryByFiguration) > 0 ) && ( ( positionOfCategoryByEnglish ) > 0 ) ) minimumOfPosition = min(positionOfCategoryByFiguration, positionOfCategoryByEnglish);
 else if ( ( (positionOfCategoryBySquare) > 0 ) && ( ( positionOfCategoryByEnglish ) > 0 ) ) minimumOfPosition = min(positionOfCategoryBySquare, positionOfCategoryByEnglish);
 else if(positionOfCategoryByFiguration < positionOfCategoryBySquare) {
  if(positionOfCategoryByFiguration < positionOfCategoryByEnglish) minimumOfPosition=min(positionOfCategoryByFiguration, positionOfCategoryByEnglish);
 } 
 else minimumOfPosition = min(positionOfCategoryBySquare, positionOfCategoryByEnglish);

 if ( ( (positionOfCategoryByFigurationSmallRegiseter) < 0 ) && ( ( positionOfCategoryBySquareSmallRegiseter ) < 0 ) ) minimumOfPosition = positionOfCategoryByEnglishSmallRegiseter;
 else if ( ( (positionOfCategoryByEnglishSmallRegiseter) < 0 ) && ( ( positionOfCategoryByFigurationSmallRegiseter ) < 0 ) ) minimumOfPosition = positionOfCategoryBySquareSmallRegiseter;
 else if ( ( (positionOfCategoryByEnglishSmallRegiseter) < 0 ) && ( ( positionOfCategoryBySquareSmallRegiseter ) < 0 ) ) minimumOfPosition = positionOfCategoryByFigurationSmallRegiseter;
 else if ( ( (positionOfCategoryByFigurationSmallRegiseter) > 0 ) && ( ( positionOfCategoryBySquareSmallRegiseter ) > 0 ) ) minimumOfPosition = min(positionOfCategoryByFigurationSmallRegiseter, positionOfCategoryBySquareSmallRegiseter);
 else if ( ( (positionOfCategoryByFigurationSmallRegiseter) > 0 ) && ( ( positionOfCategoryByEnglishSmallRegiseter ) > 0 ) ) minimumOfPosition = min(positionOfCategoryByFigurationSmallRegiseter, positionOfCategoryByEnglishSmallRegiseter);
 else if ( ( (positionOfCategoryBySquareSmallRegiseter) > 0 ) && ( ( positionOfCategoryByEnglishSmallRegiseter ) > 0 ) ) minimumOfPosition = min(positionOfCategoryBySquareSmallRegiseter, positionOfCategoryByEnglishSmallRegiseter);
 else if(positionOfCategoryByFigurationSmallRegiseter < positionOfCategoryBySquareSmallRegiseter) {
  if(positionOfCategoryByFigurationSmallRegiseter < positionOfCategoryByEnglishSmallRegiseter) minimumOfPosition=min(positionOfCategoryByFigurationSmallRegiseter, positionOfCategoryByEnglishSmallRegiseter);
 } 
 else minimumOfPosition = min(positionOfCategoryBySquare, positionOfCategoryByEnglish);

 //cout << "[insertservicepage] minimumOfPosition: \n" << minimumOfPosition << endl;

 pageContent = pageContent.insert(minimumOfPosition, "\n\n{{Служебная информация}}\n\n");

 edit.text = pageContent;
 mwaapi.edit(&loginInfo, &tokens, &edit);
 cout << "New version of page: " << pageContent << endl;

 edit.title="Викиновости:Статистика страниц/";
 edit.title+=argv[4];
 edit.text="{{Статистика страницы}}";
 mwaapi.edit(&loginInfo, &tokens, &edit);

 cout << "All tasks are successfully completed." << endl;

 return 0;
}
 

 
