#ifndef SITEMATRIXLANGUAGE_HPP
#define SITEMATRIXLANGUAGE_HPP
/*
 Sitematrix.hpp get Wikimedia sites list. The code (technically dbname/wikiid) is either the language code + project code for content projects or the subdomain + main domain for all the others. .

 Processed by MediaWikiActionAPI.hpp Sitematrix(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"
#include "Sitematrix.hpp"
#include "Site.hpp"

class SitematrixLanguage : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Response
  string code;
  string name;
  vector<Site> sites;
  string localname;

  void clearRequest() {}

  void clearResponse() {
   code.clear();
   name.clear();
   sites.clear();
   localname.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {  
   code=json["code"].string_value();
   //cout << "SitematrixLanguage:: code:" << code << endl;
   name=json["name"].string_value();
   auto siteJson=json["site"].array_items();
   for(auto is : siteJson) { 
    Site site;
    site.fromJson(is);
    sites.push_back(site);
   }
   localname=json["localname"].string_value();
  }
  
  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string SitematrixLanguage::versionMajor = "201512290030";
const string SitematrixLanguage::versionMinor = "201512290030";

#endif // #ifndef SITEMATRIXLANGUAGE_HPP
 
