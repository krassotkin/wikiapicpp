/*
 sortcategories is a console tool of the wikiapicpp project used to sort categories in articles.

 Compiling:
 make

 Usage:

 For sortcategories:
 ./sortcategories <site> <botusername> <botuserpassword> <title>

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Tokens.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"

string description() {
 return "sortcategories is a console tool of the wikiapicpp project used to sort categories in articles.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\tShow this help:\n"
         + "\t\t./sortcategories --help\n"
         + "\tsortcategories in article:\n"
         + "\t\t./sortcategories <site> <botusername> <botuserpassword> <title>\n");
}

vector<string> listOfArrays;

string pushArrayByFigur(string content, long int position) {
 string tmpArray="";
 while(position > 0) {
  long int border=content.find("|", position);
  long int end=content.find("}", position);
  content.erase(position,position+11);
  for(int i=position;i<13;i++)content[i]=' ';
  for(int i=border;i<end;i++) {
   if(content[i]!='|') tmpArray+=content[i];
   else {
     listOfArrays.push_back(tmpArray);
     tmpArray="";
   }
   content[i]=' ';
  }
  content[end]=' '; content[end+1]=' ';
  listOfArrays.push_back(tmpArray);
  position=content.find("{{Категории|"); 
 }
 return content;
}

string pushArrayBySquare(string content, long int position) {
 string tmpArray="";
 while(position > 0) {
  long int border=content.find(":", position);
  long int end=content.find("]", position);
  content.erase(position,position+11);
  for(int i=position;i<13;i++)content[i]=' ';
  for(int i=border;i<end;i++) {
   if(content[i]!=':') tmpArray+=content[i];
   else {
     listOfArrays.push_back(tmpArray);
     tmpArray="";
   }
   content[i]=' ';
  }
  content[end]=' '; content[end+1]=' ';
  listOfArrays.push_back(tmpArray);
  position=content.find("[[Категории:"); 
 }
 return content;
}

string pushArrayByEnglish(string content, long int position) {
 string tmpArray="";
 while(position > 0) {
  long int border=content.find(":", position);
  long int end=content.find("]", position);
  content.erase(position,position+11);
  for(int i=position;i<13;i++)content[i]=' ';
  for(int i=border;i<end;i++) {
   if(content[i]!=':') tmpArray+=content[i];
   else {
     listOfArrays.push_back(tmpArray);
     tmpArray="";
   }
   content[i]=' ';
  }
  content[end]=' '; content[end+1]=' ';
  listOfArrays.push_back(tmpArray);
  position=content.find("[[Category:"); 
 }
 return content;
}

string rewritePage(string content, size_t yes) {
 cout<< "[rewritePage] content: " << content<<endl;
 std::sort(listOfArrays.begin(), listOfArrays.end()); 
 //for(unsigned i=0;i<listOfArrays.size();i++) cout << "[rewritePage] listOfArrays[i]: \n" << i << "   " << listOfArrays[i] << endl;

 string subContent=" ";
 unsigned u=0;
 for(string c : listOfArrays) {
  if(u == 0) subContent+="{{Категории";
  subContent+="|"+c;
  u++;
  if(u==50){
   subContent+="}}\n";
   u=0;
  }
 }
 if(u!=0) subContent+="}}\n";
/*
 long int length = listOfArrays.size();
 long int groups=length/50 + 1;
 for(int i=0;i<groups;i++) {
  subContent+="{{Категории|";
  for(int j=0;j<50;j++) {
   subContent += listOfArrays[j]; subContent += "|";
  }
  subContent+="}}\n";
 } 
*/
 cout<< "[rewritePage] subContent: " << subContent<<endl;
 content+=subContent;
 if(yes > 0)content+="{{yes}}"; 
 return content;
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
 edit.summary = "Sort categories";
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
 
 cout << "[sortcategories] pageContent: \n" << pageContent << endl;

 
 long int positioncategoryFiguration=0;
 long int positioncategorySquare=0;
 long int positioncategoryEnglish=0;
 size_t positionYes=0;
 long int lengthYes;
 
 positioncategoryFiguration=pageContent.find("{{Категории|");
 positioncategorySquare=pageContent.find("[[Категория:");
 positioncategoryEnglish=pageContent.find("[[Category:");
 
 positionYes=pageContent.find("{{yes}}");
 if (positionYes <= 0) {
  positionYes=pageContent.find("{{Опубликовать}}");
  lengthYes=16;
  pageContent.erase(positionYes,positionYes+lengthYes);
 }
 else {
  lengthYes=7;
  pageContent.erase(positionYes,positionYes+lengthYes);
 }
 
 pageContent=pushArrayByFigur(pageContent, positioncategoryFiguration);
 pushArrayBySquare(pageContent, positioncategorySquare);
 pushArrayByEnglish(pageContent, positioncategoryEnglish);
  
 //for(unsigned i=0;i<listOfArrays.size();i++) cout << "[sortcategories] listOfArrays[i]: \n" << i << "   " << listOfArrays[i] << endl;
 //cout << "[sortcategories] pageContent: \n" << pageContent << endl;

 pageContent=rewritePage(pageContent, positionYes);

 //cout << "[sortcategories] pageContent: \n" << pageContent << endl;
 edit.text = pageContent;
 mwaapi.edit(&loginInfo, &tokens, &edit);
 cout << "New version of page: " << pageContent << endl;

 cout << "All tasks are successfully completed." << endl;
 return 0;
}
 

 
