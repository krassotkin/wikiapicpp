/*
 generatorCategoryByYear is a console tool of the wikiapicpp project used to creat categories.
 Compiling:
 make
 Usage:
 For generatorCategoryByYear:
 ./generatorCategoryByYear <site> <botusername> <botuserpassword> <text> <limit>
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
#include "Edit.hpp"

string description() {
 return "generatorCategoryByYear is a console tool of the wikiapicpp project used to creat categories.";
}

string usage() {
 return ((string)"Usage:\n"
         + "\tShow this help:\n"
         + "\t\t./generatorCategoryByYear --help\n"
         + "\tgeneratorCategoryByYear in article:\n"
         + "\tstatus 1 - Родившияся 0 - Умершие:\n"
         + "\t\t./generatorCategoryByYear <site> <botusername> <botuserpassword> <date> <limit> <status>\n");
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

 if(argc < 7) {
  cout << "Very few arguments..." << endl;
  cout << usage() << endl;
  cout << "Nothing to do. Stopped." << endl;
  return -1;
 }

 LoginInfo loginInfo(argv[1], argv[2], argv[3]);
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

 Edit edit;
 string title="";
 long int date=stol(argv[4]);
 long int status= stol(argv[6]);
 long int limit = stol(argv[5]);
 string text="";
 cout << "Start to work" << endl;

 for(long int i=0;i<limit;i++) {
  if(status == 0) {
   title="Категория:Умершие в " + to_string(date) + " году";
   text="{{Умершие по годам|"+to_string(date/10)+"|"+to_string(date%10)+"|Викиданные=}}";
   edit.text=text;
   edit.title = title;
   edit.createonly=1;
   edit.summary = "Создание категории.";
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title=(string)"Викиновости:Статистика страниц/"+title;
   edit.text="{{Статистика страницы}}";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title="Умершие в " + to_string(date) + " году";
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title="Умершие в " + to_string(date);
   edit.text = "#REDIRECT[["+title+"]]";   
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
  } else if(status == 1) {
   title="Категория:Родившиеся в " + to_string(date) + " году";
   text="{{Родившиеся по годам|"+to_string(date/10)+"|"+to_string(date%10)+"|Викиданные=}}";
   edit.text=text;
   edit.title = title;
   edit.summary = "Создание категории.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title=(string)"Викиновости:Статистика страниц/"+title;
   edit.text="{{Статистика страницы}}";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title="Родившиеся в " + to_string(date) + " году";
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title="Родившиеся в " + to_string(date);
   edit.text = "#REDIRECT[["+title+"]]";   
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
  }
  else if(status == 2) {
   title="Категория:Сюжеты " + to_string(date) + " года";
   text="{{Сюжеты по годам|"+to_string(date/10)+"|"+to_string(date%10)+"}}";
   edit.text=text;
   edit.title = title;
   edit.createonly=1;
   edit.summary = "Создание категории.";
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title=(string)"Викиновости:Статистика страниц/"+title;
   edit.text="{{Статистика страницы}}";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title="Сюжеты " + to_string(date) + " года";
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title="Сюжеты " + to_string(date);
   edit.text = "#REDIRECT[["+title+"]]";   
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
 }
  else if(status == 3) {
   title="Категория:" + to_string(date);
   text="{{Категория года|"+to_string(date/10)+"|"+to_string(date%10)+"}}";
   edit.text=text;
   edit.title = title;
   edit.createonly=1;
   edit.summary = "Создание категории.";
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title=(string)"Викиновости:Статистика страниц/"+title;
   edit.text="{{Статистика страницы}}";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title=to_string(date) ; 
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title=to_string(date)+" год"; 
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
  }
  else if(status == 4) {
   title="Категория:Архив " + to_string(date);
   text="{{Категория архива года|"+to_string(date/10)+"|"+to_string(date%10)+"}}";
   edit.text=text;
   edit.title = title;
   edit.createonly=1;
   edit.summary = "Создание категории.";
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.title=(string)"Викиновости:Статистика страниц/"+title;
   edit.text="{{Статистика страницы}}";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title="Архив "+to_string(date) ; 
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
   edit.text = "#REDIRECT[["+title+"]]";
   edit.title="Архив "+to_string(date)+" года"; 
   edit.summary = "Создание перенаправления.";
   edit.createonly=1;
   cout << title << " is prepeare to work\n";
   mwaapi.edit(&loginInfo, &tokens, &edit);
   if(edit.isSuccess()) {
  cout << "Page \"" << edit.title << "\" (" << edit.pageidres << ") has been successfully created." << endl;
 } else cout << "sorry\n";
  }
  date--;
 }
 
 cout<<"Work is end\n";
 
 return 0;
}

