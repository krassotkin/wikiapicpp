#ifndef MEDIAWIKIACTIONAPIIPARAMETERS_HPP
#define MEDIAWIKIACTIONAPIIPARAMETERS_HPP
/*
 MediaWikiActionAPIParameters.hpp is a supre class for all parameters classes of MediaWikiActionAPI.

 See: 
https://en.wikipedia.org/w/api.php
https://www.mediawiki.org/wiki/API:Main_page

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/) and Simon Krassotkin.
 since 2015-12-29
*/

#include <iostream>
#include <string>

using namespace std;

// shared
#include "json11.hpp"

class MediaWikiActionAPIParameters {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  /* Servo */
  string errJson;           /* Error string of json11::Json::parse */
                            
  /* Request */             
  string assert;            /* Verify the user is logged in if set to user, or has the bot user right if bot. One of the following values: user, bot. */
  string centralauthtoken;  /* When accessing the API using a cross-domain AJAX request (CORS), use this to authenticate as the current SUL user. Use action=centralauthtoken on this wiki to retrieve the token, before making the CORS request. Each token may only be used once, and expires after 10 seconds. This should be included in any pre-flight request, and therefore should be included in the request URI (not the POST body). */
  int curtimestamp = -1;    /* Include the current timestamp in the result. Type: boolean (details) */
  string format = "json";   /* The format of the output. One of the following values: json, jsonfm, none, php, phpfm, rawfm, xml, xmlfm */
  long int maxage = -1;     /* Set the max-age HTTP cache control header to this many seconds. Errors are never cached. Default: 0 */
  long int maxlag = -1;     /* Maximum lag can be used when MediaWiki is installed on a database replicated cluster. To save actions causing any more site replication lag, this parameter can make the client wait until the replication lag is less than the specified value. In case of excessive lag, error code maxlag is returned with a message like Waiting for $host: $lag seconds lagged. See Manual: Maxlag parameter for more information. */
  string origin;            /* When accessing the API using a cross-domain AJAX request (CORS), set this to the originating domain. This must be included in any pre-flight request, and therefore must be part of the request URI (not the POST body). This must match one of the origins in the Origin header exactly, so it has to be set to something like https://en.wikipedia.org or https://meta.wikimedia.org. If this parameter does not match the Origin header, a 403 response will be returned. If this parameter matches the Origin header and the origin is whitelisted, an Access-Control-Allow-Origin header will be set. */
  string requestid;         /* Any value given here will be included in the response. May be used to distinguish requests. */ 
  long int smaxage = -1;    /* Set the s-maxage HTTP cache control header to this many seconds. Errors are never cached. Default: 0 */
  int servedby = -1;        /* Include the hostname that served the request in the results. Type: boolean. */
  string uselang;           /* Language to use for message translations. action=query&meta=siteinfo with siprop=languages returns a list of language codes, or specify user to use the current user's language preference, or specify content to use this wiki's content language. Default: user. */
                            
  /* Response */            
  string res;               /* RAW response string. */
  string requestid_res;
  
  MediaWikiActionAPIParameters() {}

  /*
  MediaWikiActionAPIParameters(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  MediaWikiActionAPIParameters(const json11::Json& json) {
   fromJsonThis(json);
  }
  */

  void clear() {
   clearServoSup();
   clearServo();
   clearRequestSup();
   clearRequest();
   clearResponseSup();
   clearResponse();
  }

  virtual void clearRequest() = 0;

  void clearRequestSup() { 
   assert.clear();
   centralauthtoken.clear();
   curtimestamp = -1;
   format = "json";
   maxage = -1;
   maxlag = -1;
   origin.clear();
   requestid.clear();
   smaxage = -1; 
   servedby = -1;
   uselang.clear();
  }

  virtual void clearResponse() = 0;

  void clearResponseSup() {
   requestid_res.clear();
   res.clear();
  }

  virtual void clearServo() = 0;

  void clearServoSup() {
   errJson.clear();
  }

  void fromJson(const json11::Json& json) { 
   //cout << "[[MediaWikiActionAPIParameters::fromJson]]..." << endl;
   fromJsonSuper(json);
   fromJsonSub(json);
  }
  
  void fromJsonString(const string& jsonString) {
   //cout << "[[MediaWikiActionAPIParameters::fromJsonString]]..." << endl;
   res = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  virtual void fromJsonSub(const json11::Json& json) = 0;

  void fromJsonSuper(const json11::Json& json) {
   //cout << "[[MediaWikiActionAPIParameters::fromJsonThis]]..." << endl;
   requestid_res = json["requestid"].string_value();      
  }

  string getSuperParameters() {
   return (assert.length() > 0 ? "&assert=" + assert : "")
          + (centralauthtoken.length() > 0 ? "&centralauthtoken=" + centralauthtoken : "")
          + (curtimestamp == 1 ? "&curtimestamp=1" : "")
          + (maxage > -1 ? "&maxage="+to_string(maxage) : "")
          + (maxlag > -1 ? "&maxage="+to_string(maxlag) : "")
          + (origin.length() > 0 ? "&origin=" + origin : "")
          + (requestid.length() > 0 ? "&requestid=" + requestid : "")
          + (smaxage > -1 ? "&smaxage="+to_string(smaxage) : "")
          + (servedby == 1 ? "&servedby=1" : "")
          + (uselang.length() > 0 ? "&uselang=" + uselang : "")
          + (format.length() > 0 ? "&format=" + format : "");
  }
  
  string toJson() {
   return "{\"warning\":\"not implemented\"}";
  }

};

const string MediaWikiActionAPIParameters::versionMajor = "201512290030";
const string MediaWikiActionAPIParameters::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPIIPARAMETERS_HPP
 
