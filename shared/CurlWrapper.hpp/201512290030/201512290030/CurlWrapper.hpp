#ifndef CURLWRAPPER_HPP
#define CURLWRAPPER_HPP

/*
Curlwrapper.hpp is a libcurl cpp wrapper.

 Public Domain by authors: Alexander Krassotkin
 since 2015-12-29
*/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

#include <curl/curl.h>

class CurlWrapper {

 public:

  static const string userAgent;
  static const string versionMajor;
  static const string versionMinor;

  
  CURL *curl;
  CURLcode res;

  curl_slist *cookies;

  CurlWrapper() {
   curl_global_init(CURL_GLOBAL_DEFAULT);
   curl = curl_easy_init();  
   if(curl) curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
  }

  ~CurlWrapper() {
   if(curl) curl_easy_cleanup(curl); 
   curl_global_cleanup();
  }

  static int curlPageWriter(char *data, size_t size, size_t nmemb, string *buffer) {
   int result = 0;
   if(buffer != NULL) {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
   }
   return result;
  } 

  string escape(const string& s) {
   char *output = curl_easy_escape(curl, s.c_str(), s.length());
   string res(output);
   if(output) curl_free(output);
   return res;
  }
 
  string getFirstPagePost(const string& url) {
   string postFields;
   map<string,string> headersMap;
   return getFirstPagePost(url, postFields, headersMap);
  }
 
  string getFirstPagePost(const string& url, const string& postFields, map<string,string>& headersMap) {
   string buffer = "";
   if(curl) { 
    curl_easy_setopt(curl, CURLOPT_ENCODING, "UTF-8");
    curl_easy_setopt(curl, CURLOPT_POST, true);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlPageWriter); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_perform(curl); 
   }  
   return buffer;
  }

};

const string CurlWrapper::versionMajor = "201512290030";
const string CurlWrapper::versionMinor = "201512290030";
const string CurlWrapper::userAgent = "wikiapicpp";

#endif // #ifndef CURLWRAPPER_HPP

