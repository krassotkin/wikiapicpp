#ifndef MEDIAWIKIACTIONAPIIPARAMETERS_HPP
#define MEDIAWIKIACTIONAPIIPARAMETERS_HPP
/*
 MediaWikiActionAPIParameters.hpp is a supre class for all parameters classes of MediaWikiActionAPI.

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/)
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
  string errJson; /* Error string of json11::Json::parse */

  /* Response */
  string res;    /* RAW response string. */


  MediaWikiActionAPIParameters() {}
  
  MediaWikiActionAPIParameters(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  MediaWikiActionAPIParameters(const json11::Json& json) {
   fromJsonThis(json);
  }

  void clear() {
   clearServoThis();
   clearServo();
   clearRequestThis();
   clearRequest();
   clearResponseThis();
   clearResponse();
  }

  void clearRequestThis() { 
  }

  virtual void clearRequest() = 0;

  void clearResponseThis() {
   res.clear();
  }

  virtual void clearResponse() = 0;

  void clearServoThis() {
   errJson.clear();
  }

  virtual void clearServo() = 0;
  
  void fromJsonString(const string& jsonString) {
   res = jsonString;
   auto json = json11::Json::parse(jsonString, errJson);
   fromJsonAll(json);
  }

  void fromJsonAll(const json11::Json& json) {
   fromJsonThis(json);
   fromJson(json);
  }

  void fromJsonThis(const json11::Json& json) {
  }
  
  virtual void fromJson(const json11::Json& json) = 0;
  
  string toJson() {
   return "{\"warning\":\"not implemented\"}";
  }

};

const string MediaWikiActionAPIParameters::versionMajor = "201512290030";
const string MediaWikiActionAPIParameters::versionMinor = "201512290030";

#endif // #ifndef MEDIAWIKIACTIONAPIIPARAMETERS_HPP
 
