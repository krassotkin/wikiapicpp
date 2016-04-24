#ifndef SITE_HPP
#define SITE_HPP
/*
 Site.hpp get Wikimedia sites list. The code (technically dbname/wikiid) is either the language code + project code for content projects or the subdomain + main domain for all the others. .

 Processed by MediaWikiActionAPI.hpp Sitematrix(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
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
#include "Sitematrix.hpp"
#include "SitematrixLanguage.hpp"

class Site : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  // Response
  string url;
  string dbname;
  string code;
  string sitename;
  string closed;

  void clearRequest() {}

  void clearResponse() {
   url.clear(); 
   dbname.clear();
   code.clear();
   sitename.clear();
   closed.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   url=json["url"].string_value();
   //cout<<"Site::fromJsonSub url: " << url<<endl;
   dbname=json["dbname"].string_value();
   //cout<<"Site::fromJsonSub dbname: " << dbname<<endl;
   code=json["code"].string_value();
   //cout<<"Site::fromJsonSub code: " <<code<<endl;
   sitename=json["sitename"].string_value();
   //cout<<"Site::fromJsonSub sitename: " <<sitename<<endl;
   closed=json["closed"].string_value();
   //cout<<"Site::fromJsonSub closed: " <<closed<<endl;
  }
  
  string toJson() {
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Site::versionMajor = "201512290030";
const string Site::versionMinor = "201512290030";

#endif // #ifndef SITE_HPP
 
