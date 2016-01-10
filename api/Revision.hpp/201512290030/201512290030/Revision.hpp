#ifndef REVISION_HPP
#define REVISION_HPP
/*
 Revision.hpp represent a revision information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:Revisions

 Example:
https://en.wikipedia.org/w/api.php?action=query&prop=revisions&titles=User:Krassotkin&rvlimit=20&rvprop=ids|flags|timestamp|user|userid|size|sha1|contentmodel|comment|parsedcomment|content|tags|parsetree|flagged

{
                        "revid": 653894319,
                        "parentid": 628333333,
                        "user": "Krassotkin",
                        "userid": 10436237,
                        "timestamp": "2015-03-28T14:35:57Z",
                        "size": 667,
                        "sha1": "12bbfdec234f7412412b4d7f7ae88f7576a6f5a3",
                        "contentmodel": "wikitext",
                        "comment": "",
                        "parsedcomment": "",
                        "tags": [],
                        "parsetree": "<root>[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n<template lineStart=\"1\"><title>#babel:ru</title><part><name index=\"1\"/><value>uk</value></part><part><name index=\"2\"/><value>en-1</value></part></template>\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n<template lineStart=\"1\"><title>-</title></template>\n\n<template lineStart=\"1\"><title>userpage</title><part><name index=\"1\"/><value>User:Krassotkin</value></part></template>\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "[[File:Premia Runeta 2012 - Aleksandr Krassotkin.jpg|right|250px]]\n{{#babel:ru|uk|en-1}}\n'''Alexander N Krassotkin'''\n\nUser of [[n:ru:User:Krassotkin|Russian Wikinews]] and [[w:ru:User:Krassotkin|Russian Wikipedia]], [[c:User:Krassotkin|Wikimedia Commons]], [[d:User:Krassotkin|Wikidata]] and [https://tools.wmflabs.org/quentinv57-tools/tools/sulinfo.php?username=Krassotkin other projects].\n\nContacts: [http://krassotkin.com/ krassotkin.com].\n\n{{-}}\n\n{{userpage|User:Krassotkin}}\n\n[[fr:Utilisateur:Krassotkin]]\n[[it:Utente:Krassotkin]]\n[[pl:Wikipedysta:Krassotkin]]\n[[pt:Usu\u00e1rio:Krassotkin]]\n[[ru:\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Krassotkin]]\n[[uk:\u041a\u043e\u0440\u0438\u0441\u0442\u0443\u0432\u0430\u0447:Krassotkin]]"
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

class Revision {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  string comment;
  string content; // *
  string contentformat;
  string contentmodel;
  string errJson;
  string minor = "not";
  long int parentid;
  string parsedcomment;
  string parsetree;
  long int revid;
  long int size;
  string sha1;
  string timestamp; // ISO time string
  vector<string> tags;
  string user;
  long int userid;

  Revision() {}
  
  Revision(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Revision(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   comment = "";
   content = "";
   contentformat = "";
   contentmodel = "";
   minor = "not";
   parentid = 0;
   parsedcomment = "";
   parsetree = "";
   revid = 0;
   size = 0;
   sha1 = "";
   timestamp = "";
   tags.clear();
   user = "";
   userid = 0;
  }
  
  void fromJsonString(const string& jsonString) {
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   comment = json["comment"].string_value();
   content = json["*"].string_value();
   contentformat = json["contentformat"].string_value();
   contentmodel = json["contentmodel"].string_value();
   minor = json["minor"].string_value();
   parentid = json["parentid"].int_value();
   parsedcomment = json["parsedcomment"].string_value();
   parsetree = json["parsetree"].string_value();
   revid = json["revid"].int_value();
   size = json["size"].int_value();
   sha1 = json["sha1"].string_value();
   timestamp = json["timestamp"].string_value();
   auto tagsJson = json["tags"].array_items();
   for(auto it : tagsJson) tags.push_back(it.string_value());
   user = json["user"].string_value();
   userid = json["userid"].int_value();
  }
  
  string toJson() {
   string tagsJsonString = "";
   for(string it : tags) {
    tagsJsonString+= (tagsJsonString.length()>0) ? "," : "";
    tagsJsonString+= "\""+it+"\"";
   }
   return "{\"revid\":"+to_string(revid)+",\"parentid\":"+to_string(parentid)+(minor.compare("not")==0 ? ",\"minor\":\"\"" : "") +",\"user\":\""+user+"\",\"userid\":"+to_string(userid)+",\"timestamp\":\""+timestamp+"\",\"size\":"+to_string(size)+",\"sha1\":\""+sha1+"\",\"contentmodel\":\""+contentmodel+"\",\"comment\":\""+comment+"\",\"parsedcomment\":\""+parsedcomment+"\",to_string(\"tags\":["+tagsJsonString+"],\"parsetree\":\""+parsetree+"\",\"contentformat\":\""+contentformat+"\",\"*\":\""+content+"\"}";
  }

};

const string Revision::versionMajor = "201512290030";
const string Revision::versionMinor = "201512290030";

#endif // #ifndef REVISION_HPP
 
