#ifndef WIKIMEDIAPROJECTS_HPP
#define WIKIMEDIAPROJECTS_HPP
/*
 WikimediaProjects.hpp represent all wikimedia projects.

 Source of Complete list of Wikimedia projects:
https://meta.wikimedia.org/wiki/Complete_list_of_Wikimedia_projects
*/

#include <iostream>
#include <string>

// abstract
#include "WikimediaProject.hpp"

using namespace std;

class WikimediaProjects {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  static const vector<WikimediaProject> list;

  WikimediaProjects() {}

};

const string WikimediaProjects::versionMajor = "201512290030";
const string WikimediaProjects::versionMinor = "201512290030";

const vector<WikimediaProject> WikimediaProjects::list = 
{
 {"org", "mediawiki", "www", 1},

 {"org", "wikimedia", "ca", 1},
 {"org", "wikimedia", "incubator", 1},
 {"org", "wikimedia", "login", 1},
 {"org", "wikimedia", "meta", 1},
 {"org", "wikimedia", "nl", 1},
 {"org", "wikimedia", "no", 1},
 {"org", "wikimedia", "outreach", 1},
 {"org", "wikimedia", "pl", 1},
 {"org", "wikimedia", "rs", 1},
 {"org", "wikimedia", "ru", 1},
 {"org", "wikimedia", "ua", 1},
 {"org", "wikimedia", "wikimania2009", 1},
 {"org", "wikimedia", "wikimania2010", 1},
 {"org", "wikimedia", "wikimania2011", 1},
 {"org", "wikimedia", "wikimania2012", 1},
 {"org", "wikimedia", "wikimania2013", 1},
 {"org", "wikimedia", "wikimania2014", 1},
 {"org", "wikimedia", "wikimania2015", 1},
 {"org", "wikimedia", "wikimania2016", 1},
 {"org", "wikimedia", "wikimania2017", 1},

 {"org", "wikipedia", "aa", 1},
 {"org", "wikipedia", "ab", 1},
 {"org", "wikipedia", "ace", 1},
 {"org", "wikipedia", "af", 1},
 {"org", "wikipedia", "ak", 1},
 {"org", "wikipedia", "als", 1},
 {"org", "wikipedia", "an", 1},
 {"org", "wikipedia", "ang", 1},
 {"org", "wikipedia", "ast", 1},
 {"org", "wikipedia", "av", 1},
 {"org", "wikipedia", "ay", 1},
 {"org", "wikipedia", "az", 1},
 {"org", "wikipedia", "bar", 1},
 {"org", "wikipedia", "bcl", 1},
 {"org", "wikipedia", "bi", 1},
 {"org", "wikipedia", "bjn", 1},
 {"org", "wikipedia", "bm", 1},
 {"org", "wikipedia", "br", 1},
 {"org", "wikipedia", "bs", 1},
 {"org", "wikipedia", "bug", 1},
 {"org", "wikipedia", "ca", 1},
 {"org", "wikipedia", "cbk-zam", 1},
 {"org", "wikipedia", "ceb", 1},
 {"org", "wikipedia", "ch", 1},
 {"org", "wikipedia", "cho", 1},
 {"org", "wikipedia", "co", 1},
 {"org", "wikipedia", "cs", 1},
 {"org", "wikipedia", "csb", 1},
 {"org", "wikipedia", "cy", 1},
 {"org", "wikipedia", "da", 1},
 {"org", "wikipedia", "de", 1},
 {"org", "wikipedia", "dsb", 1},
 {"org", "wikipedia", "ee", 1},
 {"org", "wikipedia", "eml", 1},
 {"org", "wikipedia", "en", 1},
 {"org", "wikipedia", "eo", 1},
 {"org", "wikipedia", "es", 1},
 {"org", "wikipedia", "et", 1},
 {"org", "wikipedia", "eu", 1},
 {"org", "wikipedia", "ext", 1},
 {"org", "wikipedia", "ff", 1},
 {"org", "wikipedia", "fi", 1},
 {"org", "wikipedia", "fj", 1},
 {"org", "wikipedia", "fo", 1},
 {"org", "wikipedia", "fr", 1},
 {"org", "wikipedia", "frp", 1},
 {"org", "wikipedia", "frr", 1},
 {"org", "wikipedia", "fur", 1},
 {"org", "wikipedia", "fy", 1},
 {"org", "wikipedia", "gn", 1},
 {"org", "wikipedia", "hif", 1},
 {"org", "wikipedia", "id", 1},
 {"org", "wikipedia", "jv", 1},
 {"org", "wikipedia", "lad", 1},
 {"org", "wikipedia", "map-bms", 1},
 {"org", "wikipedia", "mh", 1},
 {"org", "wikipedia", "na", 1},
 {"org", "wikipedia", "nv", 1},
 {"org", "wikipedia", "ny", 1},
 {"org", "wikipedia", "ms", 1},
 {"org", "wikipedia", "pdc", 1},
 {"org", "wikipedia", "roa-rup", 1},
 {"org", "wikipedia", "sm", 1},
 {"org", "wikipedia", "sn", 1},
 {"org", "wikipedia", "su", 1},
 {"org", "wikipedia", "test", 1},
 {"org", "wikipedia", "test2", 1},
 {"org", "wikipedia", "to", 1},
 {"org", "wikipedia", "tum", 1},
 {"org", "wikipedia", "za", 1},
 {"org", "wikipedia", "zh", 1},
 {"org", "wikipedia", "zh-classical", 1},
 {"org", "wikipedia", "zh-min-nan", 1},

 {"org", "wikipedia", "ga", 1},
 {"org", "wikipedia", "gv", 1},
 {"org", "wikipedia", "gag", 1},
 {"org", "wikipedia", "gd", 1},
 {"org", "wikipedia", "gl", 1},
 {"org", "wikipedia", "ki", 1},
 {"org", "wikipedia", "haw", 1},
 {"org", "wikipedia", "ho", 1},
 {"org", "wikipedia", "hsb", 1},
 {"org", "wikipedia", "hr", 1},
 {"org", "wikipedia", "io", 1},
 {"org", "wikipedia", "ig", 1},
 {"org", "wikipedia", "rw", 1},
 {"org", "wikipedia", "ilo", 1},
 {"org", "wikipedia", "ia", 1},
 {"org", "wikipedia", "ie", 1},
 {"org", "wikipedia", "ik", 1},
 {"org", "wikipedia", "xh", 1},
 {"org", "wikipedia", "zu", 1},
 {"org", "wikipedia", "is", 1},
 {"org", "wikipedia", "it", 1},
 {"org", "wikipedia", "kl", 1},
 {"org", "wikipedia", "kr", 1},
 {"org", "wikipedia", "pam", 1},
 {"org", "wikipedia", "kw", 1},
 {"org", "wikipedia", "kg", 1},
 {"org", "wikipedia", "rn", 1},
 {"org", "wikipedia", "sw", 1},
 {"org", "wikipedia", "ht", 1},
 {"org", "wikipedia", "kj", 1},
 {"org", "wikipedia", "ku", 1},
 {"org", "wikipedia", "ltg", 1},
 {"org", "wikipedia", "la", 1},
 {"org", "wikipedia", "lv", 1},
 {"org", "wikipedia", "lb", 1},
 {"org", "wikipedia", "lt", 1},
 {"org", "wikipedia", "lij", 1},
 {"org", "wikipedia", "li", 1},
 {"org", "wikipedia", "ln", 1},
 {"org", "wikipedia", "jbo", 1},
 {"org", "wikipedia", "lg", 1},
 {"org", "wikipedia", "lmo", 1},
 {"org", "wikipedia", "hu", 1},
 {"org", "wikipedia", "mg", 1},
 {"org", "wikipedia", "mt", 1},
 {"org", "wikipedia", "mi", 1},
 {"org", "wikipedia", "min", 1},
 {"org", "wikipedia", "cdo", 1},
 {"org", "wikipedia", "mwl", 1},
 {"org", "wikipedia", "mus", 1},
 {"org", "wikipedia", "nah", 1},
 {"org", "wikipedia", "nl", 1},
 {"org", "wikipedia", "nds-nl", 1},
 {"org", "wikipedia", "cr", 1},
 {"org", "wikipedia", "nap", 1},
 {"org", "wikipedia", "pih", 1},
 {"org", "wikipedia", "no", 1},
 {"org", "wikipedia", "nrm", 1},
 {"org", "wikipedia", "nov", 1},
 {"org", "wikipedia", "nn", 1},
 {"org", "wikipedia", "uz", 1},
 {"org", "wikipedia", "oc", 1},
 {"org", "wikipedia", "om", 1},
 {"org", "wikipedia", "ng", 1},
 {"org", "wikipedia", "hz", 1},
 {"org", "wikipedia", "pfl", 1},
 {"org", "wikipedia", "pag", 1},
 {"org", "wikipedia", "pap", 1},
 {"org", "wikipedia", "pcd", 1},
 {"org", "wikipedia", "pms", 1},
 {"org", "wikipedia", "nds", 1},
 {"org", "wikipedia", "pl", 1},
 {"org", "wikipedia", "pt", 1},
 {"org", "wikipedia", "kaa", 1},
 {"org", "wikipedia", "crh", 1},
 {"org", "wikipedia", "ty", 1},
 {"org", "wikipedia", "ksh", 1},
 {"org", "wikipedia", "ro", 1},
 {"org", "wikipedia", "rmy", 1},
 {"org", "wikipedia", "rm", 1},
 {"org", "wikipedia", "qu", 1},
 {"org", "wikipedia", "se", 1},
 {"org", "wikipedia", "sg", 1},
 {"org", "wikipedia", "sc", 1},
 {"org", "wikipedia", "sco", 1},
 {"org", "wikipedia", "stq", 1},
 {"org", "wikipedia", "nso", 1},
 {"org", "wikipedia", "st", 1},
 {"org", "wikipedia", "tn", 1},
 {"org", "wikipedia", "sq", 1},
 {"org", "wikipedia", "scn", 1},
 {"org", "wikipedia", "simple", 1},
 {"org", "wikipedia", "ss", 1},
 {"org", "wikipedia", "sk", 1},
 {"org", "wikipedia", "sl", 1},
 {"org", "wikipedia", "szl", 1},
 {"org", "wikipedia", "so", 1},
 {"org", "wikipedia", "ckb", 1},
 {"org", "wikipedia", "srn", 1},
 {"org", "wikipedia", "sh", 1},
 {"org", "wikipedia", "sv", 1},
 {"org", "wikipedia", "tl", 1},
 {"org", "wikipedia", "kab", 1},
 {"org", "wikipedia", "roa-tara", 1},
 {"org", "wikipedia", "tt", 1},
 {"org", "wikipedia", "tet", 1},
 {"org", "wikipedia", "vi", 1},
 {"org", "wikipedia", "tpi", 1},
 {"org", "wikipedia", "chy", 1},
 {"org", "wikipedia", "ve", 1},
 {"org", "wikipedia", "tr", 1},
 {"org", "wikipedia", "tw", 1},
 {"org", "wikipedia", "vec", 1},
 {"org", "wikipedia", "vep", 1},
 {"org", "wikipedia", "vo", 1},
 {"org", "wikipedia", "fiu-vro", 1},
 {"org", "wikipedia", "wa", 1},
 {"org", "wikipedia", "vls", 1},
 {"org", "wikipedia", "war", 1},
 {"org", "wikipedia", "wo", 1},
 {"org", "wikipedia", "ts", 1},
 {"org", "wikipedia", "yo", 1},
 {"org", "wikipedia", "diq", 1},
 {"org", "wikipedia", "zea", 1},
 {"org", "wikipedia", "bat-smg", 1},
 {"org", "wikipedia", "el", 1},
 {"org", "wikipedia", "pnt", 1},
 {"org", "wikipedia", "kbd", 1},
 {"org", "wikipedia", "ba", 1},
 {"org", "wikipedia", "be", 1},
 {"org", "wikipedia", "be-x-old", 1},
 {"org", "wikipedia", "bxr", 1},
 {"org", "wikipedia", "bg", 1},
 {"org", "wikipedia", "os", 1},
 {"org", "wikipedia", "kv", 1},
 {"org", "wikipedia", "krc", 1},
 {"org", "wikipedia", "ky", 1},
 {"org", "wikipedia", "mrj", 1},
 {"org", "wikipedia", "kk", 1},
 {"org", "wikipedia", "lbe", 1},
 {"org", "wikipedia", "lez", 1},
 {"org", "wikipedia", "mk", 1},
 {"org", "wikipedia", "mdf", 1},
 {"org", "wikipedia", "mo", 1},
 {"org", "wikipedia", "mn", 1},
 {"org", "wikipedia", "ce", 1},
 {"org", "wikipedia", "mhr", 1},
 {"org", "wikipedia", "koi", 1},
 {"org", "wikipedia", "rue", 1},
 {"org", "wikipedia", "ru", 1},
 {"org", "wikipedia", "sah", 1},
 {"org", "wikipedia", "cu", 1},
 {"org", "wikipedia", "sr", 1},
 {"org", "wikipedia", "tg", 1},
 {"org", "wikipedia", "tyv", 1},
 {"org", "wikipedia", "udm", 1},
 {"org", "wikipedia", "uk", 1},
 {"org", "wikipedia", "xal", 1},
 {"org", "wikipedia", "cv", 1},
 {"org", "wikipedia", "myv", 1},
 {"org", "wikipedia", "hy", 1},
 {"org", "wikipedia", "xmf", 1},
 {"org", "wikipedia", "ka", 1},
 {"org", "wikipedia", "got", 1},
 {"org", "wikipedia", "yi", 1},
 {"org", "wikipedia", "he", 1},
 {"org", "wikipedia", "ur", 1},
 {"org", "wikipedia", "ar", 1},
 {"org", "wikipedia", "ps", 1},
 {"org", "wikipedia", "tk", 1},
 {"org", "wikipedia", "sd", 1},
 {"org", "wikipedia", "pnb", 1},
 {"org", "wikipedia", "fa", 1},
 {"org", "wikipedia", "glk", 1},
 {"org", "wikipedia", "mzn", 1},
 {"org", "wikipedia", "arz", 1},
 {"org", "wikipedia", "ha", 1},
 {"org", "wikipedia", "ug", 1},
 {"org", "wikipedia", "arc", 1},
 {"org", "wikipedia", "dv", 1},
 {"org", "wikipedia", "ks", 1},
 {"org", "wikipedia", "new", 1},
 {"org", "wikipedia", "ne", 1},
 {"org", "wikipedia", "pi", 1},
 {"org", "wikipedia", "bh", 1},
 {"org", "wikipedia", "mai", 1},
 {"org", "wikipedia", "mr", 1},
 {"org", "wikipedia", "sa", 1},
 {"org", "wikipedia", "hi", 1},
 {"org", "wikipedia", "as", 1},
 {"org", "wikipedia", "bpy", 1},
 {"org", "wikipedia", "bn", 1},
 {"org", "wikipedia", "pa", 1},
 {"org", "wikipedia", "gu", 1},
 {"org", "wikipedia", "or", 1},
 {"org", "wikipedia", "ta", 1},
 {"org", "wikipedia", "te", 1},
 {"org", "wikipedia", "kn", 1},
 {"org", "wikipedia", "ml", 1},
 {"org", "wikipedia", "si", 1},
 {"org", "wikipedia", "th", 1},
 {"org", "wikipedia", "my", 1},
 {"org", "wikipedia", "dz", 1},
 {"org", "wikipedia", "bo", 1},
 {"org", "wikipedia", "lo", 1},
 {"org", "wikipedia", "km", 1},
 {"org", "wikipedia", "iu", 1},
 {"org", "wikipedia", "chr", 1},
 {"org", "wikipedia", "ti", 1},
 {"org", "wikipedia", "am", 1},
 {"org", "wikipedia", "ii", 1},
 {"org", "wikipedia", "ko", 1},
 {"org", "wikipedia", "wuu", 1},
 {"org", "wikipedia", "hak", 1},
 {"org", "wikipedia", "ja", 1},
 {"org", "wikipedia", "zh-yue", 1},
 {"org", "wikipedia", "gan", 1},
 {"org", "wikipedia", "aa", 1},
 {"org", "wikipedia", "cho", 1},
 {"org", "wikipedia", "mh", 1},
 {"org", "wikipedia", "ho", 1},
 {"org", "wikipedia", "kr", 1},
 {"org", "wikipedia", "kj", 1},
 {"org", "wikipedia", "mus", 1},
 {"org", "wikipedia", "ng", 1},
 {"org", "wikipedia", "hz", 1},
 {"org", "wikipedia", "mo", 1},
 {"org", "wikipedia", "ii", 1},

 {"org", "wiktionary", "ang", 1},
 {"org", "wiktionary", "af", 1},
 {"org", "wiktionary", "als", 1},
 {"org", "wiktionary", "an", 1},
 {"org", "wiktionary", "roa-rup", 1},
 {"org", "wiktionary", "ast", 1},
 {"org", "wiktionary", "gn", 1},
 {"org", "wiktionary", "ay", 1},
 {"org", "wiktionary", "az", 1},
 {"org", "wiktionary", "id", 1},
 {"org", "wiktionary", "ms", 1},
 {"org", "wiktionary", "zh-min-nan", 1},
 {"org", "wiktionary", "jv", 1},
 {"org", "wiktionary", "su", 1},
 {"org", "wiktionary", "bs", 1},
 {"org", "wiktionary", "br", 1},
 {"org", "wiktionary", "ca", 1},
 {"org", "wiktionary", "cs", 1},
 {"org", "wiktionary", "co", 1},
 {"org", "wiktionary", "cy", 1},
 {"org", "wiktionary", "da", 1},
 {"org", "wiktionary", "de", 1},
 {"org", "wiktionary", "na", 1},
 {"org", "wiktionary", "et", 1},
 {"org", "wiktionary", "en", 1},
 {"org", "wiktionary", "es", 1},
 {"org", "wiktionary", "eo", 1},
 {"org", "wiktionary", "eu", 1},
 {"org", "wiktionary", "fo", 1},
 {"org", "wiktionary", "fr", 1},
 {"org", "wiktionary", "fy", 1},
 {"org", "wiktionary", "ga", 1},
 {"org", "wiktionary", "gv", 1},
 {"org", "wiktionary", "sm", 1},
 {"org", "wiktionary", "gd", 1},
 {"org", "wiktionary", "gl", 1},
 {"org", "wiktionary", "ha", 1},
 {"org", "wiktionary", "hr", 1},
 {"org", "wiktionary", "io", 1},
 {"org", "wiktionary", "ia", 1},
 {"org", "wiktionary", "ie", 1},
 {"org", "wiktionary", "ik", 1},
 {"org", "wiktionary", "zu", 1},
 {"org", "wiktionary", "is", 1},
 {"org", "wiktionary", "it", 1},
 {"org", "wiktionary", "kl", 1},
 {"org", "wiktionary", "csb", 1},
 {"org", "wiktionary", "kw", 1},
 {"org", "wiktionary", "rw", 1},
 {"org", "wiktionary", "sw", 1},
 {"org", "wiktionary", "ku", 1},
 {"org", "wiktionary", "la", 1},
 {"org", "wiktionary", "lv", 1},
 {"org", "wiktionary", "lb", 1},
 {"org", "wiktionary", "lt", 1},
 {"org", "wiktionary", "li", 1},
 {"org", "wiktionary", "ln", 1},
 {"org", "wiktionary", "jbo", 1},
 {"org", "wiktionary", "hu", 1},
 {"org", "wiktionary", "mg", 1},
 {"org", "wiktionary", "mt", 1},
 {"org", "wiktionary", "mi", 1},
 {"org", "wiktionary", "fj", 1},
 {"org", "wiktionary", "nah", 1},
 {"org", "wiktionary", "nl", 1},
 {"org", "wiktionary", "no", 1},
 {"org", "wiktionary", "nn", 1},
 {"org", "wiktionary", "oc", 1},
 {"org", "wiktionary", "om", 1},
 {"org", "wiktionary", "uz", 1},
 {"org", "wiktionary", "nds", 1},
 {"org", "wiktionary", "pl", 1},
 {"org", "wiktionary", "pt", 1},
 {"org", "wiktionary", "ro", 1},
 {"org", "wiktionary", "qu", 1},
 {"org", "wiktionary", "sg", 1},
 {"org", "wiktionary", "st", 1},
 {"org", "wiktionary", "tn", 1},
 {"org", "wiktionary", "sq", 1},
 {"org", "wiktionary", "scn", 1},
 {"org", "wiktionary", "simple", 1},
 {"org", "wiktionary", "ss", 1},
 {"org", "wiktionary", "sk", 1},
 {"org", "wiktionary", "sl", 1},
 {"org", "wiktionary", "so", 1},
 {"org", "wiktionary", "sh", 1},
 {"org", "wiktionary", "fi", 1},
 {"org", "wiktionary", "sv", 1},
 {"org", "wiktionary", "tl", 1},
 {"org", "wiktionary", "vi", 1},
 {"org", "wiktionary", "tpi", 1},
 {"org", "wiktionary", "tr", 1},
 {"org", "wiktionary", "tk", 1},
 {"org", "wiktionary", "za", 1},
 {"org", "wiktionary", "vo", 1},
 {"org", "wiktionary", "wa", 1},
 {"org", "wiktionary", "wo", 1},
 {"org", "wiktionary", "ts", 1},
 {"org", "wiktionary", "el", 1},
 {"org", "wiktionary", "be", 1},
 {"org", "wiktionary", "bg", 1},
 {"org", "wiktionary", "ky", 1},
 {"org", "wiktionary", "kk", 1},
 {"org", "wiktionary", "mk", 1},
 {"org", "wiktionary", "mn", 1},
 {"org", "wiktionary", "ru", 1},
 {"org", "wiktionary", "sr", 1},
 {"org", "wiktionary", "tt", 1},
 {"org", "wiktionary", "tg", 1},
 {"org", "wiktionary", "uk", 1},
 {"org", "wiktionary", "hy", 1},
 {"org", "wiktionary", "ka", 1},
 {"org", "wiktionary", "yi", 1},
 {"org", "wiktionary", "he", 1},
 {"org", "wiktionary", "ur", 1},
 {"org", "wiktionary", "ar", 1},
 {"org", "wiktionary", "ps", 1},
 {"org", "wiktionary", "pnb", 1},
 {"org", "wiktionary", "sd", 1},
 {"org", "wiktionary", "fa", 1},
 {"org", "wiktionary", "ug", 1},
 {"org", "wiktionary", "dv", 1},
 {"org", "wiktionary", "ks", 1},
 {"org", "wiktionary", "ne", 1},
 {"org", "wiktionary", "mr", 1},
 {"org", "wiktionary", "sa", 1},
 {"org", "wiktionary", "hi", 1},
 {"org", "wiktionary", "bn", 1},
 {"org", "wiktionary", "pa", 1},
 {"org", "wiktionary", "gu", 1},
 {"org", "wiktionary", "or", 1},
 {"org", "wiktionary", "ta", 1},
 {"org", "wiktionary", "te", 1},
 {"org", "wiktionary", "kn", 1},
 {"org", "wiktionary", "ml", 1},
 {"org", "wiktionary", "si", 1},
 {"org", "wiktionary", "th", 1},
 {"org", "wiktionary", "my", 1},
 {"org", "wiktionary", "bo", 1},
 {"org", "wiktionary", "lo", 1},
 {"org", "wiktionary", "km", 1},
 {"org", "wiktionary", "iu", 1},
 {"org", "wiktionary", "chr", 1},
 {"org", "wiktionary", "ti", 1},
 {"org", "wiktionary", "am", 1},
 {"org", "wiktionary", "ko", 1},
 {"org", "wiktionary", "ja", 1},
 {"org", "wiktionary", "zh", 1},
 {"org", "wiktionary", "ak", 1},
 {"org", "wiktionary", "bo", 1},
 {"org", "wiktionary", "bm", 1},
 {"org", "wiktionary", "bi", 1},
 {"org", "wiktionary", "ch", 1},
 {"org", "wiktionary", "sn", 1},
 {"org", "wiktionary", "mh", 1},
 {"org", "wiktionary", "xh", 1},
 {"org", "wiktionary", "rn", 1},
 {"org", "wiktionary", "to", 1},
 {"org", "wiktionary", "cr", 1},
 {"org", "wiktionary", "aa", 1},
 {"org", "wiktionary", "rm", 1},
 {"org", "wiktionary", "sc", 1},
 {"org", "wiktionary", "tw", 1},
 {"org", "wiktionary", "yo", 1},
 {"org", "wiktionary", "av", 1},
 {"org", "wiktionary", "ab", 1},
 {"org", "wiktionary", "ba", 1},
 {"org", "wiktionary", "mo", 1},
 {"org", "wiktionary", "pi", 1},
 {"org", "wiktionary", "bh", 1},
 {"org", "wiktionary", "as", 1},
 {"org", "wiktionary", "dz", 1},
 {"org", "wiktionary", "bo", 1},
 {"org", "wiktionary", "cho", 1},
 {"org", "wiktionary", "ny", 1},
 {"org", "wiktionary", "tum", 1},
 {"org", "wiktionary", "nv", 1},
 {"org", "wiktionary", "lad", 1},
 {"org", "wiktionary", "ff", 1},
 {"org", "wiktionary", "fur", 1},
 {"org", "wiktionary", "haw", 1},
 {"org", "wiktionary", "ho", 1},
 {"org", "wiktionary", "ig", 1},
 {"org", "wiktionary", "ilo", 1},
 {"org", "wiktionary", "kr", 1},
 {"org", "wiktionary", "pam", 1},
 {"org", "wiktionary", "kg", 1},
 {"org", "wiktionary", "ki", 1},
 {"org", "wiktionary", "ht", 1},
 {"org", "wiktionary", "kj", 1},
 {"org", "wiktionary", "lg", 1},
 {"org", "wiktionary", "lmo", 1},
 {"org", "wiktionary", "mus", 1},
 {"org", "wiktionary", "nap", 1},
 {"org", "wiktionary", "pih", 1},
 {"org", "wiktionary", "nrm", 1},
 {"org", "wiktionary", "ng", 1},
 {"org", "wiktionary", "hz", 1},
 {"org", "wiktionary", "pms", 1},
 {"org", "wiktionary", "ty", 1},
 {"org", "wiktionary", "ksh", 1},
 {"org", "wiktionary", "se", 1},
 {"org", "wiktionary", "sco", 1},
 {"org", "wiktionary", "ceb", 1},
 {"org", "wiktionary", "tet", 1},
 {"org", "wiktionary", "ve", 1},
 {"org", "wiktionary", "chy", 1},
 {"org", "wiktionary", "vec", 1},
 {"org", "wiktionary", "fiu-vro", 1},
 {"org", "wiktionary", "war", 1},
 {"org", "wiktionary", "cv", 1},
 {"org", "wiktionary", "os", 1},
 {"org", "wiktionary", "kv", 1},
 {"org", "wiktionary", "ce", 1},
 {"org", "wiktionary", "udm", 1},
 {"org", "wiktionary", "got", 1},
 {"org", "wiktionary", "arc", 1},
 {"org", "wiktionary", "syr", 1},
 {"org", "wiktionary", "bug", 1},
 {"org", "wiktionary", "ii", 1},
 {"org", "wiktionary", "zh-yue", 1}
};

#endif // #ifndef WIKIMEDIAPROJECTS_HPP
 