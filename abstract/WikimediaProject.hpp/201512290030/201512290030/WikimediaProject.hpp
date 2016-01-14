#ifndef WIKIMEDIAPROJECT_HPP
#define WIKIMEDIAPROJECT_HPP
/*
 WikimediaProject.hpp represent a wikimedia project.
*/

#include <iostream>
#include <string>

using namespace std;

class WikimediaProject {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const string scheme = "https://";

  string zone;
  string domain;
  string subdomain;
  int active = 0;

  WikimediaProject() {}

  WikimediaProject(const string& zone, const string& domain, const string& subdomain, const int& active) : zone(zone), domain(domain), subdomain(subdomain), active(active) {}

  string getSite() {
   return scheme+subdomain+"."+domain+"."+zone+"/";
  }

};

const string WikimediaProject::versionMajor = "201512290030";
const string WikimediaProject::versionMinor = "201512290030";

#endif // #ifndef WIKIMEDIAPROJECT_HPP
 
