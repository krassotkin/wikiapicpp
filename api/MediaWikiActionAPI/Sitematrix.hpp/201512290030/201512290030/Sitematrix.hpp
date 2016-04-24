#ifndef SITEMATRIX_HPP
#define SITEMATRIX_HPP
/*
 Sitematrix.hpp get Wikimedia sites list. The code (technically dbname/wikiid) is either the language code + project code for content projects or the subdomain + main domain for all the others. .

 Processed by MediaWikiActionAPI.hpp Sitematrix(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=sitematrix

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 Since 2015-12-29.
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "MediaWikiActionAPIParameters.hpp"
#include "SitematrixLanguage.hpp"
#include "Site.hpp"

class Sitematrix : public MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  
  // Request                         
  string smtype;/*Filter the Site Matrix by type: special One off and multilingual Wikimedia projects. language Wikimedia projects under this language code. Values (separate with |): special, language Default: special|language*/

  string smstate;/*Filter the Site Matrix by wiki state: closed No write access, full read access. private Read and write restricted. fishbowl Restricted write access, full read access. Values (separate with |): all, closed, private, fishbowl Default: all*/
  
  string smlangprop;/* Which information about a language to return. Values (separate with |): code, name, site, localname Default: code|name|site|localname*/

  string smsiteprop;/* Which information about a site to return. Values (separate with |): url, dbname, code, sitename Default: url|dbname|code|sitename*/

  long int smlimit=-1; // Maximum number of results. No more than 5,000 (5,000 for bots) allowed. Type: integer or max Default: 5000

  string smcontinue;// When more results are available, use this to continue.                
                  
  // Response                
  long int count=-1;
  vector <SitematrixLanguage> sitematrixLanguage;
  
  void clearRequest() {
   smtype.clear();
   smstate.clear();
   smlangprop.clear();
   smsiteprop.clear();
   smlimit=-1;
   smcontinue.clear();
  }

  void clearResponse() {
   count=-1;
   sitematrixLanguage.clear();
  }

  void clearServo() {}
  
  void fromJsonSub(const json11::Json& json) {
   auto sitematrixJson=json["sitematrix"].object_items();
   //count=sitematrixJson["count"].int_value();
   for(auto element : sitematrixJson) {
    //cout<<"[Sitematrix::fromJsonSub] element: "<<element.first<<endl;
    auto pagesJson=element.second.object_items();
    SitematrixLanguage smLang;
    smLang.fromJson(element.second);
    sitematrixLanguage.push_back(smLang);
   }
  }

  bool isLangPrefix(string prefix){
   for(unsigned i=0;i<sitematrixLanguage.size();i++) if(prefix.compare(sitematrixLanguage[i].code) == 0) return true;
   return false;
  }

  bool isDbname(string prefix){
   //cout << "Sitematrix::isDbname in\n";
   for(unsigned i=0;i<sitematrixLanguage.size();i++) {
    for(unsigned j=0;j<sitematrixLanguage[i].sites.size();j++) {
     //cout << "in\n";
     //cout << sitematrixLanguage[i].sites[j].dbname<<endl;
     if(prefix.compare(sitematrixLanguage[i].sites[j].dbname) == 0)  return true;
    } 
   }
   return false;
  }

  string toJson() {
   /* not implemented */
   return MediaWikiActionAPIParameters::toJson();
  }

};

const string Sitematrix::versionMajor = "201512290030";
const string Sitematrix::versionMinor = "201512290030";

#endif // #ifndef SITEMATRIX_HPP
 
