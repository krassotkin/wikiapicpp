#ifndef NEWSWIKIRU_HPP
#define NEWSWIKIRU_HPP

/*
 newswikiru.hpp is a class-store information about news.

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin.
 since 2015-12-29
*/

// common
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <stdlib.h>

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Tokens.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"

using namespace std;

class NewsWikiRu { 
 public: 
 LoginInfo loginInfo;
 MediaWikiActionAPI mwaapi;
 Tokens tokens;
 Revisions revisions;
 Edit edit;

 string title;
 long int id;
 string content;
 string clearContent;
 string date="";
 vector<string> topics;
 vector<vector<string>> images;
 string text;
 vector<string> newsLinks;
 vector<string> wikiLinks;
 vector<string> externalLinks;
 vector<vector<string>> sources;
 vector<vector<string>> links;
 bool comments;
 bool haveyoursay;
 bool servicePage;
 vector<string> categories;
 bool published;
  
 NewsWikiRu() {}

 NewsWikiRu(const string& title) : title(title) {}
 
 NewsWikiRu(const long int& id) : id(id) {}
 
 bool init(string site, string login, string password, string text) {
  readContent(site, login, password, text);
  parseContent();
  
  return true;
 }

  bool readContent(string site, string login, string password, string text) {
   cout << "NewsWikiRu [readContent] site : " << site << endl;
   cout << "NewsWikiRu [readContent] login : " << login << endl;
   cout << "NewsWikiRu [readContent] password : " << password << endl;
   cout << "NewsWikiRu [readContent] text : " << text << endl;
   loginInfo.lgname=login;
   loginInfo.lgpassword=password;
   loginInfo.site=site;
   mwaapi.login(&loginInfo, &tokens);

   if(loginInfo.result.compare("Success") != 0) {
    cout << "Login failed..." << endl;
    cout << "Response:" << endl;
    cout << loginInfo.toJson() << endl;
    return 0;
   } else {
    cout << "Success logined..." << endl;
   }
  
   cout << "[insertservicepage.cpp] main argv[4]: " << text << endl;
   revisions.titles = text;
   revisions.prop="content";
 
   mwaapi.revisions(&loginInfo, &revisions);
   if(revisions.pages.size()==0) {
    revisions.pageids = text;
    revisions.titles="";
    mwaapi.revisions(&loginInfo, &revisions);
    if(revisions.pages.size()==0) {
     cout << "Page not found..." << endl;
     exit(EXIT_FAILURE);
    }
   }
   if(revisions.pages[0]->revisions.size()==0) {
     cout << "Content not found." << endl;
     exit(EXIT_FAILURE);
   }
 
   if(revisions.titles.length()>0) title = revisions.titles;
   else if(revisions.pageids.length()>0) id = stol(revisions.pageids);
 
   content = revisions.pages[0]->revisions[0]->content;

   return true;
 }

 void parseContent() {
 cout<< "check" << endl;
 cout << "NewsWikiRu [NewsWikiRu] title: " << title << endl;
 cout<< "check" << endl;
 cout << "NewsWikiRu [NewsWikiRu] content: " << content << endl;
 cout<< "check" << endl;
  clearContent=content;
  size_t position;
  size_t end;
  size_t delPos;
  string tmpArray="";
  cout<< "check0" << endl;

  position = clearContent.find("{{дата|");
  if(position == std::string::npos) position = clearContent.find("{{:Дата|");
  if(position != std::string::npos) { 
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end =clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+11);i<end;i++) {
    date+=clearContent[i];
    clearContent[i]=' ';
   }
   clearContent[end]=' '; clearContent[end+1]=' ';
   clearContent.erase(position,(end+1));
   //cout << "NewsWikiRu [parseContent] content[2]: " << clearContent[2] << endl;
   //cout << "NewsWikiRu [parseContent] date: " << date << endl;
  }
  cout<< "check1" << endl;
  
  position = clearContent.find("{{тема|");
  if(position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+11);i<end;i++) {
    if(clearContent[i]!='|') tmpArray+=clearContent[i];
    else {
      topics.push_back(tmpArray);
      tmpArray="";
    }
   }
   topics.push_back(tmpArray);
   clearContent[end]=' '; clearContent[end+1]=' ';
   tmpArray="";
   clearContent.erase(position,end);
  }
  //for(unsigned i=0;i<topics.size();i++) cout << "NewsWikiRu [parseContent] topics[i]: " << i << "  " << topics[i] << endl;
  cout<< "check2" << endl;

  position = clearContent.find("{{haveyoursay");  
  if(position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   haveyoursay=1;
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
  }  
  else haveyoursay=0;
  //cout << "NewsWikiRu [parseContent] haveyoursay: " << haveyoursay << endl;
  cout << "check3" << endl;

  position = clearContent.find("{{Комментарии");  
  if(position != std::string::npos) {
   delPos=position;
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   comments=1;
   for(size_t i=position;i<(end+4);i++) clearContent[i] = ' ';
  }  
  else comments=0;
  //cout << "NewsWikiRu [parseContent] commetns: " << comments << endl;
  cout << "check4" << endl;

  position = clearContent.find("{{Служебная информация");  
  if(position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   servicePage=1;
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
  }  
  else comments=0;
  cout << "NewsWikiRu [parseContent] servicePage: " << servicePage << endl;
  cout << "check5" << endl;

  position = clearContent.find("{{yes");  
  if(position == std::string::npos) position = clearContent.find("{{публиковать");
  if(position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   published=1;
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
  }  
  else published=0;
  cout << "NewsWikiRu [parseContent] published: " << published << endl;
  cout << "check6" << endl;

  position = clearContent.find("[[Категория:");
  while (position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+21);i<end;i++) tmpArray+=clearContent[i];
   categories.push_back(tmpArray);
   tmpArray="";
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
   position = clearContent.find("[[Категория:");
  }
  //for(unsigned i=0;i<categories.size();i++) cout << "NewsWikiRu [parseContent] categories[i]: " << i << "  " << categories[i] << endl;
  cout << "check7" << endl;

  position = clearContent.find("[[Category:");
  while (position != std::string::npos) {
   //cout << "NewsWikiRu [parseContent] position: " << position << endl;
   //cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   //cout << "NewsWikiRu [parseContent] end: " << end << endl;
   //cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   //cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+19);i<end;i++) tmpArray+=clearContent[i];
   categories.push_back(tmpArray);
   tmpArray="";
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
   position = clearContent.find("[[Category:");
  }
  //for(unsigned i=0;i<categories.size();i++) cout << "NewsWikiRu [parseContent] categories[i]: " << i << "  " << categories[i] << endl;
  cout << "check8" << endl;

  position = clearContent.find("{{Категории|");
  while (position != std::string::npos) {
   end=clearContent.find("}}", position);
   for (size_t i=(position+21);i<end;i++) {
    if(clearContent[i]!='|') tmpArray+=clearContent[i];
    else {
      categories.push_back(tmpArray);
      tmpArray="";
    }
   }
   categories.push_back(tmpArray);
   tmpArray="";
   for(size_t i=position;i<(end+2);i++) clearContent[i] = ' ';
   position = clearContent.find("{{Категории|");
  }
  //for(unsigned i=0;i<categories.size();i++) cout << "NewsWikiRu [parseContent] categories[i]: " << i << "  " << categories[i] << endl;
  cout << "check7" << endl;
   
  if(delPos != 0) clearContent.erase(delPos,end);
  cout << "NewsWikiRu [parseContent] clearContent: " << clearContent << endl;
  content = "";
 }

 void writeAsItIs() {
  edit.text = content;
  mwaapi.edit(&loginInfo, &tokens, &edit);

  cout << "Page have been written as it is." << endl;
 }
 
 void writeCanonical() {
  mwaapi.login(&loginInfo, &tokens);
  edit.summary="Format";
  if(date.length()>0) content+="{{дата|"+date+"}}\n";
  if(topics.size()>0) { 
   content+="{{тема|"; 
   for(unsigned i;i<(topics.size());i++){
    content+=topics[i]+"|";
   }
   content+="}}\n";
  }
  content+=clearContent;
  content+="{{Комментарии:{{PAGENAME}}}}\n";
  content+="\n{{-}}\n\n"; 
  content+="{{haveyoursay}}\n";
  content+="\n{{-}}\n\n";
  content+="{{Служебная информация}}\n";
  content+="\n{{-}}\n\n";
  unsigned u=0; 
  std::sort (categories.begin(), categories.end());
  for(string c : categories) {
  if(u == 0) content+="{{Категории";
  content+="|"+c;
  u++;
  if(u==50){
   content+="}}\n";
   u=0;
  }
  }
  if(u!=0) content+="}}\n";
  if(published) content+="\n{{yes}}";
  cout << "NewsWikiRu [writeCanonical] content: " << content << endl;

  if (title.length() > 0) edit.title = title;
  if (id > 0) edit.pageid = id;
  edit.text = content;
  mwaapi.edit(&loginInfo, &tokens, &edit);
  
  edit.clear();
  edit.title=(string)"Викиновости:Статистика страниц/"+title;
  edit.text="{{Статистика страницы}}";
  mwaapi.edit(&loginInfo, &tokens, &edit);

  cout << "Page have been written canonically." << endl;
 }
}; 
  
#endif // #ifndef NEWSWIKIRU_HPP

