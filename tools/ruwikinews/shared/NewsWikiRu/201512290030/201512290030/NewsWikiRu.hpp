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

// api
#include "LoginInfo.hpp"
#include "MediaWikiActionAPI.hpp"
#include "Tokens.hpp"
#include "Revision.hpp"
#include "Revisions.hpp"

using namespace std;

class NewsWikiRu {
  
 public:
 string title;
 long int id;
 string content;
 string clearContent;
 string date="";
 vector<string> topics;
 vector<vector<string>> images;
 string text;
 vector<vector<string>> wikiSources;
 vector<vector<string>> externalSources;
 vector<vector<string>> sources;
 vector<vector<string>> links;
 bool comments;
 bool haveyoursay;
 bool servicePage;
 vector<string> categories;
 bool published;

 MediaWikiActionAPI mwaapi;
 LoginInfo loginInfo;
 Revisions revisions;
 Token tokens;
 Edit edit;
  
 NewsWikiRu() {}

 NewsWikiRu(const string& title) : title(title) {}

 NewsWikiRu(const long int& id) : id(id) {}

 bool init() {
  readСontent();
  parseContent();
 }
 
 void readContent() {  
  if (title.length() > 0) revisions.titles = title;
  if (id > 0) revisions.pageids = id;
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
 
  string content = revisions.pages[0].revisions[0].content;
 }

 void parseContent() {
  clearContent=content;
  size_t position;
  size_t end;
  string tmpArray="";

  position = clearContent.find("{{дата|")+7;
  content.erase(position,position+7);
  end =clearContent.find("}", position);
  for(size_t i=position;i<end;i++) {
   date+=clearContent[i];
   clearContent[i]=" ";
  }
  clearContent[end]=" "; clearContent[end+1]=" ";
  
  position = clearContent.find("{{тема|")+7;
  content.erase(position,position+7);
  end=clearContent.find("}", position);
  for(size_t i=position;i<end;i++) {
   if(clearContent[i]!='|') tmpArray+=clearContent[i];
   else {
     topics.push_back(tmpArray);
     tmpArray="";
   }
   clearContent[i]=' ';
  }
  clearContent[end]=" "; clearContent[end+1]=" ";
  tmpArray="";

  vector<string> oneImage;
  position = content.find("[[Файл:")+2;
  while(position > 0){
   end=content.find("]]", position);
   for(size_t i=position;i<end;i++){
    if(content[i] != '|') tmpArray+=content[i];
    else {
     oneImage.push_back(tmpArray);
     tmpArray="";
    }
   } tmpArray+=content[i];
   oneImage.push_back(tmpArray);
   tmpArray="";
   images.push_back(oneImage);
   position = content.find("[[Файл:", position)+2;
  }
  tmpArray="";

  vector <string> wikiSource;
  position = content.find("[[", position) + 2;
  while(position > 0){
   end=content.find("|", position);
   for(size_t i=position;i<end;i++) {
    tmpArray+=content[i];
   }
   wikiSource.push_back(tmpArray);
   tmpArray="";
   position = content.find("[[", position)+2;
   wikiSources.push_back(wikiSource);
  }
  tmpArray="";
 
  vector <string> externalSource;
  position = content.find("[") + 1;
  positionNormal = content.find("Ссылки");
  if( (position>=positionNormal) or (content[position]=='[') ) position = content.find("[", position) + 1;
  while(position > 0){
   end=content.find("]", position);
   for(size_t i=position;i<end;i++) {
    tmpArray+=content[i];
   }
   externalSource.push_back(tmpArray);
   tmpArray="";
   externalSources.push_back(externalSource);
   position = content.find("[") + 1;
   if( (position>=positionNormal) or (content[position]=='[') ) position = content.find("[", position) + 1;
  }
  tmpArray="";

  vector <string> link;
  position = content.find("Ссылки");
  position = content.find("* [", position) + 3;
  while(position > 0){
   end=content.find("]", position);
   for(size_t i=position;i<end;i++) {
    tmpArray+=content[i];
   }
   link.push_back(tmpArray);
   tmpArray="";
   position = content.find("[", position)+3;
   links.push_back(link);
  }
  tmpArray="";
  
  vector<string> source;
  position = content.find("* {{источник|")+13;
  while(position > 0){
   end=content.find("}}", position);
   for(size_t i=position;i<end;i++) {
    if(content[i] != '|') tmpArray+=content[i];
    else {
     source.push_back(tmpArray);
     tmpArray="";
    } 
   }
   source.push_back(tmpArray);
   tmpArray="";
   sources.push_back(source);
   position = clearContent.find("* {{источник|", position)+13;
  }
  tmpArray="";

  position = clearContent.find("{{Комментарии:{{PAGENAME}}}}");
  end=clearContent.find("}}", position);
  if(position > 0) {
   clearContent.erase(position,end+2);
   comments=1;
  }
  else comments=0;

  position = clearContent.find("{{haveyoursay}}");
  end=clearContent.find("}}", position);
  if(position > 0){
   clearContent.erase(position,end+2);
   comments=1;
  } 
  else comments=0;

  position = clearContent.find("{{Служебная информация}}");
  end=clearContent.find("}}", position);
  if(position > 0){
   clearContent.erase(position,end+2);
   comments=1;
  } 
  else comments=0;

  vector<string> oneCategory;
  position = clearContent.find("{{Категории|")+13;
  while(position > 0){
   clearContent.erase(position,position+13);
   end=clearContent.find("}}", position);
   for(size_t i=position;i<end;i++) {
   if(content[i]!='|') tmpArray+=clearContent[i];
   else {
     oneCategory.push_back(tmpArray);
     tmpArray="";
   }
   clearContent[i]=' ';
   }
   oneCategory.push_back(tmpArray);
   tmpArray="";
   clearContent[end]=' '; clearContent[end+1]=' ';
   categories.push_back(oneCategory);
   position = clearContent.find("{{Категории|", position)+13;
  }
  categories.push_back(oneCategory);
  tmpArray="";
  
  position = clearContent.find("{{yes}}");
  end=clearContent.find("}}", position);
  if(position > 0){
   clearContent.erase(position,end+2);
   comments=1;
  }
  else comments=0;
 }

 void writeAsItIs() {
  edit.text = content;
  mwaapi.edit(&loginInfo, &tokens, &edit);

  cout << "Page have been written as it is." << endl;
 }
 
 void writeCanonical() {
  edit.summary="Format";
  content+="{{дата|"+date+"}}\n";
  content+="{{тема|";
  std::sort(topics.begin(), topics.end()); 
  for(unsigned i;i<(topics.size());i++){
   content+=topics[i]+"|";
  }
  content+="}}\n";
  for(vector<string> i : images){
   content+="[[";
   for(string j : vector<string> i) {
    content+=j+"|";
   }
   content+="]]\n";
  }
  content+=clearContent;
  content+="\n{{-}}\n";
  content+="{{Комментарии:{{PAGENAME}}}}";
  content+="\n{{-}}\n";
  content+="{{haveyoursay}}";
  content+="\n{{-}}\n";
  content+="{{Служебная информация}}";
  content+="\n{{-}}\n";
  unsigned u=0;
  for(string c : listOfArrays) {
  if(u == 0) content+="{{Категории";
  content+="|"+c;
  u++;
  if(u==50){
   content+="}}\n";
   u=0;
  }
  }
  if(u!=0) content+="}}\n";
  content+="{{yes}}";

  if (title.length() > 0) edit.titles = title;
  if (id > 0) edit.pageids = id;
  edit.text = content;
  mwaapi.edit(&loginInfo, &tokens, &edit);

  cout << "Page have been written canonically." << endl;
 }

  void newsDate(string newDate) {  
   date=newDate;
   newiru.writeAsItIs();
 }

 void newsTopic(vector<string> tops, string capture) {
  if(capture == "deletion"){
   for(unsigned i=0; i<tops.size(); i++) {
    for(string tT : topics) {
     if(tT==tops[i]){
      topics[topics.size()]=tT;
      topics.pop_back();
     }
    }
   }
  }

  if(capture == "addition"){
   for(unsigned i=0;i<tops.size(); i++){ 
    topics.push_back(tops[i]);
   }
  }

  newiru.writeAsItIs();
 }

 void newsImage(vector<vector<string>> im, string capture) {  
  if(capture = "deletion"){
   for(unsigned i=0; i<im.size();i++) {
    for(string tI : im[i][0]) {
     if(tI == images[i][0]) {
      images[images.size()]=images[i];
      images.pop_back();
     }
    }
   }
  }
  
  if(capture = "addition"){
   for(unsigned i=0;i<images.size();i++){
    images.push_back(im[i]);
   }
  }  

  newiru.writeAsItIs();
 }
 
 void newsWikification() {
  size_t start = tmpContent.find("[[File:")+3;
  while(start > 0){
   clearContent[i]='Ф';clearContent[i+1]='а';clearContent[i+2]='й';clearContent[i+3]='л';
   size_t start = clearContent.find("[[File:")+3;
  }
  
  size_t start = clearContent.find('"')+1;
  size_t end = clearContent.find('"', start)+1;
  while(start > 0){
   clearContent[start]='«';clearContent[i+1]='»';
   size_t start = clearContent.find('"')+1;
   size_t end = clearContent.find('"', start)+1;
  }

  newiru.writeAsItIs();
 } 

 void addSource(vector<vector<string>> s, string capture) {  
  if(capture = "deletion"){
   for(unsigned i=0; i<s.size();i++) {
    for(string tS : s[i][0]) {
     if(tS == sources[i][0]) {
      sources[sources.size()]=sources[i];
      sources.pop_back();
     }
    }
   }
  }
  
  if(capture = "addition"){
   for(unsigned i=0;i<sources.size();i++){
    sources.push_back(s[i]);
   }
  }  

  newiru.writeAsItIs();
 }

 void addCategory(vector<string> c, string capture) {
  if(capture == "deletion"){
   for(unsigned i=0; i<c.size(); i++) {
    for(string tC : categories) {
     if(tC==c[i]){
      categories[categories.size()]=tC;
      categories.pop_back();
     }
    }
   }
  }

  if(capture == "addition"){
   for(unsigned i=0;i<c.size(); i++){ 
    categories.push_back(c[i]);
   }
  }

  newiru.writeAsItIs();
 }
 
 void newsPublished() {
  if(newiru.published == 0 ) newiru.published = 1;
  newiru.writeAsItIs();
 }
}; 
  
const string newswikiru::versionMajor = "201512290030";
const string newswikiru::versionMinor = "201512290030";

#endif // #ifndef NEWSWIKIRU_HPP

