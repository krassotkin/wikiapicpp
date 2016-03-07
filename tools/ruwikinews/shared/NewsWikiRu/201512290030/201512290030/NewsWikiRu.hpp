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
 
 void init(LoginInfo* loginInfo, Tokens* tokens, Revisions* revisions) {
  readContent(loginInfo, tokens, revisions);
  parseContent(loginInfo, tokens);
 }

 void readContent(LoginInfo* loginInfo, Tokens* tokens, Revisions* revisions) {
  if(revisions->titles.length()>0) title = revisions->titles;
  else if(revisions->pageids.length()>0) id = stol(revisions->pageids);

  content = revisions->pages[0].revisions[0].content;
 }

 void parseContent(LoginInfo* loginInfo, Tokens* tokens) {
 cout<< "check" << endl;
 cout << "NewsWikiRu [NewsWikiRu] title: " << title << endl;
 cout<< "check" << endl;
 cout << "NewsWikiRu [NewsWikiRu] content: " << content << endl;
 cout<< "check" << endl;
  clearContent=content;
  size_t position;
  size_t end;
  string tmpArray="";
  cout<< "check0" << endl;

  position = clearContent.find("{{дата|");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end =clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  for(size_t i=(position+11);i<end;i++) {
   date+=clearContent[i];
   clearContent[i]=' ';
  }
  clearContent[end]=' '; clearContent[end+1]=' ';
  clearContent.erase(position,(end+1));
  cout << "NewsWikiRu [parseContent] content[2]: " << clearContent[2] << endl;
  cout << "NewsWikiRu [parseContent] date: " << date << endl;
  cout<< "check1" << endl;
  
  position = clearContent.find("{{тема|");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end=clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  for(size_t i=(position+7);i<end;i++) {
   if(clearContent[i]!='|') tmpArray+=clearContent[i];
   else {
     topics.push_back(tmpArray);
     tmpArray="";
   }
  }
  topics.push_back(tmpArray);
  //clearContent[end]=' '; clearContent[end+1]=' ';
  tmpArray="";
  //clearContent.erase(position,end); 
  cout<< "check2" << endl;

  
  /*position = clearContent.find("[[");
  while( (position > 0) && (position < clearContent.length() ) ){
   cout << "NewsWikiRu [parseContent] position: " << position << endl;
   cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   cout << "NewsWikiRu [parseContent] end: " << end << endl;
   cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+2);i<end;i++) {
    if(clearContent[i]!='|') tmpArray+=clearContent[i];
    else {
      newsLinks.push_back(tmpArray);
      tmpArray="";
      break;
    }
   }
   newsLinks.push_back(tmpArray);
   position = clearContent.find("[[", position);
  }
  cout << "check1 <03-07-16>" << endl;*/

   /*position = clearContent.find("[[w:");
   while (position > 0) {
   cout << "NewsWikiRu [parseContent] position: " << position << endl;
   cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   cout << "NewsWikiRu [parseContent] end: " << end << endl;
   cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+4);i<end;i++) {
    if(clearContent[i]!='|') tmpArray+=clearContent[i];
    else {
      wikiLinks.push_back(tmpArray);
      tmpArray="";
      break;
    }
   }
   wikiLinks.push_back(tmpArray);
   position = clearContent.find("[[w:", position);
  }
  cout << "check2 <03-07-16>" << endl;*/
    
  position = clearContent.find("[[Категория:");
  while( (position > 0 ) && (position < clearContent.length()) ){
   cout << "NewsWikiRu [parseContent] position: " << position << endl;
   cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   cout << "NewsWikiRu [parseContent] end: " << end << endl;
   cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+21);i<end;i++) tmpArray+=clearContent[i];
   categories.push_back(tmpArray);
   cout << "NewsWikiRu [parseContent] categories[0]: " << categories[0] << endl;
   clearContent[end]=' '; clearContent[end+1]=' ';
   tmpArray="";
   position = clearContent.find("[[Категория:");
   clearContent.erase(position, end);
  }
  cout << "check4-3" << endl;
  
  position = clearContent.find("yes");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end=clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  if((position>0) && (position<content.size())) {
   published=1;
   clearContent.erase((position-2), end);
  }
  else published=0;
  cout << "check3" << endl;

  position = clearContent.find("{{Категории|");
  size_t fPosition = position;
  while( (position > 0 ) && (position < clearContent.length()) ){
   cout << "NewsWikiRu [parseContent] position: " << position << endl;
   cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("}", position);
   cout << "NewsWikiRu [parseContent] end: " << end << endl;
   cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+21);i<end;i++) {
    if(clearContent[i]!='|') tmpArray+=clearContent[i];
    else {
      categories.push_back(tmpArray);
      tmpArray="";
    }
   }
   categories.push_back(tmpArray);
   clearContent[end]=' '; clearContent[end+1]=' ';
   tmpArray="";
   position = clearContent.find("{{Категории|", (position+1));
  }
  clearContent.erase(fPosition, end);
  cout << "check4-1" << endl;

  position = clearContent.find("[[Category:");
  while( (position > 0 ) && (position < clearContent.length() ) ) {
   cout << "NewsWikiRu [parseContent] position: " << position << endl;
   cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
   end=clearContent.find("]", position);
   cout << "NewsWikiRu [parseContent] end: " << end << endl;
   cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
   cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
   for(size_t i=(position+11);i<end;i++) tmpArray+=clearContent[i];
   categories.push_back(tmpArray);
   cout<< "NewsWikiRu [parseContent] tmpArray: " << tmpArray << endl;
   clearContent[end]=' '; clearContent[end+1]=' ';
   tmpArray="";
   position = clearContent.find("[[Category:");
   clearContent.erase(position, end);
  }
  cout << "NewsWikiRu [parseContent] categories[0]: " << categories[0] << endl;
  cout << "NewsWikiRu [parseContent] categories[1]: " << categories[1] << endl;
  cout << "check4-2" << endl;

  position = clearContent.find("{{Служебная информация");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end=clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  if((position>0) && (position<content.size())) {
   servicePage=1;
   clearContent.erase(position, end);
  }
  else servicePage=0;
  cout << "check5" << endl;
  cout << "servicePage" << servicePage << endl;

  position = clearContent.find("{{haveyoursay");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end=clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  if((position>0) && (position<content.size())) {
   haveyoursay=1;
   clearContent.erase(position, end);
  }
  else servicePage=0;
  cout << "check6" << endl;
  cout << "haveyoursay: " << haveyoursay << endl;

  position = clearContent.find("{{Комментарии");
  cout << "NewsWikiRu [parseContent] position: " << position << endl;
  cout << "NewsWikiRu [parseContent] content[position]: " << clearContent[position] << endl;
  end=clearContent.find("}", position);
  cout << "NewsWikiRu [parseContent] end: " << end << endl;
  cout << "NewsWikiRu [parseContent] content[end-1]: " << clearContent[end-1] << endl;
  cout << "NewsWikiRu [parseContent] content[end]: " << clearContent[end] << endl;
  if((position>0) && (position<content.size())) {
   comments=1;
   clearContent.erase(position, end);
  }
  else servicePage=0;
  cout << "check7" << endl;
  cout << "comments: " << comments << endl;
  
  /*
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
   } 
   oneImage.push_back(tmpArray);
   tmpArray="";
   images.push_back(oneImage);
   position = content.find("[[Файл:", position)+2;
  }
  tmpArray="";
  cout<< "check3" << endl;
  */

  /*
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
  cout<< "check4" << endl;
  */
 
  /*
  vector <string> externalSource;
  position = content.find("[") + 1;
  size_t positionNormal = content.find("Ссылки");
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
  cout<< "check5" << endl;
  */

  /*
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
  cout<< "check6" << endl;
  */
  
  /*
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
  cout<< "check7" << endl;
  */

  //cout << "NewsWikiRu [parseContent] clearContent: " << clearContent << endl;
  content = "";
 }

 void writeAsItIs() {
  edit.text = content;
  mwaapi.edit(&loginInfo, &tokens, &edit);

  cout << "Page have been written as it is." << endl;
 }
 
 void writeCanonical(string f, string s, string t) {
  LoginInfo loginInfo(f, s, t);
  mwaapi.login(&loginInfo, &tokens);
  edit.summary="Format";
  content+="{{дата|"+date+"}}\n";
  /*content+="{{тема|"; 
  for(unsigned i;i<(topics.size());i++){
   content+=topics[i]+"|";
  }
  content+="}}\n";*/
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

