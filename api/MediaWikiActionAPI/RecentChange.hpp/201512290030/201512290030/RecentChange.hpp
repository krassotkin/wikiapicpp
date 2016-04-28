#ifndef RECENTCHANGE_HPP
#define RECENTCHANGE_HPP
/*
 RecentChange.hpp represent a revision information of The MediaWiki action API.

 Processed by MediaWikiActionAPI.hpp revisions(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2Brevisions
https://www.mediawiki.org/wiki/API:RecentChanges

 Example:
                    }

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"

class RecentChange : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Response

  void clearRequest() {}

  void clearResponse() {
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
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
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string RecentChange::versionMajor = "201512290030";
const string RecentChange::versionMinor = "201512290030";

#endif // #ifndef RECENTCHANGE_HPP
 
