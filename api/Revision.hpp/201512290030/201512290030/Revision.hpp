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

 Example with anon user:

                    {
                        "revid": 422851,
                        "parentid": 194811,
                        "user": "95.30.134.174",
                        "anon": "",
                        "userid": 0,
                        "timestamp": "2016-01-24T07:23:42Z",
                        "size": 4165,
                        "sha1": "3f11835c11accf6f6b84cd8b1dac5b8119897357",
                        "contentmodel": "wikitext",
                        "comment": "-",
                        "parsedcomment": "-",
                        "tags": [
                            "mobile edit",
                            "mobile web edit"
                        ],
                        "parsetree": "<root><template><title>\u0434\u0430\u0442\u0430</title><part><name index=\"1\"/><value>8 \u043d\u043e\u044f\u0431\u0440\u044f 2011</value></part></template>\n<template lineStart=\"1\"><title> ... \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]</root>",
                        "contentformat": "text/x-wiki",
                        "*": "{{\u0434\u0430\u0442\u0430|8 \u043d\u043e\u044f\u0431\u0440\u044f 2011}}\n{{\u041a\u0430\u043b\u0438\u0444\u043e\u0440\u043d\u0438\u044f}}\n[[\u0424\u0430\u0439\u043b:Michael-jackson-vector-2.jpg|... \u0b95\u0bbe\u0bb0\u0ba3\u0bae\u0bcd, \u0ba8\u0bc0\u0ba4\u0bbf\u0bae\u0ba9\u0bcd\u0bb1\u0bae\u0bcd \u0ba4\u0bc0\u0bb0\u0bcd\u0baa\u0bcd\u0baa\u0bc1]]\n[[tr:Michael Jackson'un doktoru su\u00e7lu bulundu]]"
                    }

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
 since 2015-12-29
*/

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

  int anon = -1;
  string comment;
  string content; // *
  string contentformat;
  string contentmodel;
  string errJson;
  int minor = -1;
  long int parentid = -1;
  long int pageid=-1;
  string parsedcomment;
  string parsetree;
  long int revid = -1;
  long int size = -1;
  string sha1;
  vector<string> tags;
  string timestamp; // ISO time string
  string user;
  long int userid = -1;

  Revision() {}
  
  Revision(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  Revision(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   anon = -1;
   comment.clear();
   content.clear();
   contentformat.clear();
   contentmodel.clear();
   minor = -1;
   pageid=-1;
   parentid = -1;
   parsedcomment.clear();
   parsetree.clear();
   revid = -1;
   size = -1;
   sha1.clear();
   tags.clear();
   timestamp.clear();
   user.clear();
   userid = -1;
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
   if(json.object_items().find("minor") != json.object_items().end()) minor = 1;
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
   if(json.object_items().find("anon") != json.object_items().end()) anon = 1;
  }
  
  string toJson() {
   string tagsJsonString = "";
   for(string it : tags) {
    tagsJsonString+= (tagsJsonString.length()>0) ? "," : "";
    tagsJsonString+= "\""+it+"\"";
   }
   return "{\"revid\":"+to_string(revid)
           +",\"parentid\":"+to_string(parentid)
           +(minor!=-1 ? ",\"minor\":\"\"" : "") 
           + ",\"user\":\""+user
           +(anon==1?",\"anon\"=\"\"":"")
           +"\",\"userid\":"+to_string(userid)
           +",\"timestamp\":\""+timestamp
           +"\",\"size\":"+to_string(size)
           +",\"sha1\":\""+sha1
           +"\",\"contentmodel\":\""+contentmodel
           +"\",\"comment\":\""+comment
           +"\",\"parsedcomment\":\""+parsedcomment
           +"\",\"tags\":["+tagsJsonString
           +"],\"parsetree\":\""+parsetree
           +"\",\"contentformat\":\""+contentformat
           +"\",\"*\":\""+content
           +"\"}";
  }

};

const string Revision::versionMajor = "201512290030";
const string Revision::versionMinor = "201512290030";

#endif // #ifndef REVISION_HPP
 
