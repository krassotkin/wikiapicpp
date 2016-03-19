#ifndef LOGEVENTS_HPP
#define LOGEVENTS_HPP
/*
 LogEvents.hpp get events from logs. .

 Processed by MediaWikiActionAPI.hpp LogEventss(...) method.

 Help:
https://en.wikipedia.org/w/api.php?action=help&modules=query%2BLogEvents
https://www.mediawiki.org/wiki/API:LogEvents

Example:

Request:
https://ru.wikinews.org/w/api.php?action=query&list=logevents&leprop=ids|title|type|user|userid|timestamp|comment|parsedcomment|details|tags&lelimit=5

Response:
{
    "batchcomplete": "",
    "continue": {
        "lecontinue": "20160214000342|350244",
        "continue": "-||"
    },
    "query": {
        "logevents": [
            {
                "logid": 350249,
                "ns": 14,
                "title": "\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f:\u0413\u043b\u0430\u0432\u043d\u044b\u0439 \u0431\u043e\u0442\u0430\u043d\u0438\u0447\u0435\u0441\u043a\u0438\u0439 \u0441\u0430\u0434 \u0438\u043c\u0435\u043d\u0438 \u041d. \u0412. \u0426\u0438\u0446\u0438\u043d\u0430 \u0420\u0410\u041d",
                "pageid": 82907,
                "logpage": 82907,
                "params": {
                    "0": "427583",
                    "1": "0",
                    "2": "20160214022348"
                },
                "type": "review",
                "action": "approve-i",
                "user": "Krassotkin",
                "userid": 3944,
                "timestamp": "2016-02-14T07:15:02Z",
                "comment": "[\u0422\u043e\u0447\u043d\u043e\u0441\u0442\u044c: \u0412\u044b\u0431\u043e\u0440\u043e\u0447\u043d\u043e \u043f\u0440\u043e\u0432\u0435\u0440\u0435\u043d\u043e]",
                "parsedcomment": "[\u0422\u043e\u0447\u043d\u043e\u0441\u0442\u044c: \u0412\u044b\u0431\u043e\u0440\u043e\u0447\u043d\u043e \u043f\u0440\u043e\u0432\u0435\u0440\u0435\u043d\u043e]",
                "tags": []
            },
            {
                "logid": 350248,
                "ns": 2,
                "title": "\u0423\u0447\u0430\u0441\u0442\u043d\u0438\u043a:Aminought",
                "pageid": 0,
                "logpage": 0,
                "params": {
                    "userid": 24284
                },
                "type": "newusers",
                "action": "autocreate",
                "user": "Aminought",
                "userid": 24284,
                "timestamp": "2016-02-14T02:58:10Z",
                "comment": "",
                "parsedcomment": "",
                "tags": []
            },
            {
                "logid": 350247,
                "ns": 10,
                "title": "\u0428\u0430\u0431\u043b\u043e\u043d:\u0421\u0430\u043c\u044b\u0435 \u043f\u043e\u043f\u0443\u043b\u044f\u0440\u043d\u044b\u0435 \u043d\u043e\u0432\u043e\u0441\u0442\u0438",
                "pageid": 15158,
                "logpage": 15158,
                "params": {
                    "curid": 427581,
                    "previd": 427506,
                    "auto": ""
                },
                "type": "patrol",
                "action": "patrol",
                "user": "AKBot",
                "userid": 9781,
                "timestamp": "2016-02-14T01:35:08Z",
                "comment": "",
                "parsedcomment": "",
                "tags": []
            },
            {
                "logid": 350246,
                "ns": 10,
                "title": "\u0428\u0430\u0431\u043b\u043e\u043d:\u0421\u0430\u043c\u044b\u0435 \u043f\u043e\u043f\u0443\u043b\u044f\u0440\u043d\u044b\u0435 \u043d\u043e\u0432\u043e\u0441\u0442\u0438",
                "pageid": 15158,
                "logpage": 15158,
                "params": {
                    "0": "427581",
                    "1": "427506",
                    "2": "20160214013508"
                },
                "type": "review",
                "action": "approve-a",
                "user": "AKBot",
                "userid": 9781,
                "timestamp": "2016-02-14T01:35:08Z",
                "comment": "(\u0430\u0432\u0442\u043e\u043c\u0430\u0442\u0438\u0447\u0435\u0441\u043a\u0438) [\u0422\u043e\u0447\u043d\u043e\u0441\u0442\u044c: \u0412\u044b\u0431\u043e\u0440\u043e\u0447\u043d\u043e \u043f\u0440\u043e\u0432\u0435\u0440\u0435\u043d\u043e]",
                "parsedcomment": "(\u0430\u0432\u0442\u043e\u043c\u0430\u0442\u0438\u0447\u0435\u0441\u043a\u0438) [\u0422\u043e\u0447\u043d\u043e\u0441\u0442\u044c: \u0412\u044b\u0431\u043e\u0440\u043e\u0447\u043d\u043e \u043f\u0440\u043e\u0432\u0435\u0440\u0435\u043d\u043e]",
                "tags": []
            },
            {
                "logid": 350245,
                "ns": 0,
                "title": "14 \u0444\u0435\u0432\u0440\u0430\u043b\u044f",
                "pageid": 17282,
                "logpage": 17282,
                "params": {
                    "curid": 427576,
                    "previd": 374643,
                    "auto": ""
                },
                "type": "patrol",
                "action": "patrol",
                "user": "NewsBots",
                "userid": 19290,
                "timestamp": "2016-02-14T00:03:42Z",
                "comment": "",
                "parsedcomment": "",
                "tags": []
            }
        ]
    }
}

 Public Domain by authors: Alexander Krassotkin (http://www.krassotkin.com/), Simon Krassotkin
 since 2015-12-29
*/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// shared
#include "json11.hpp"

// api
#include "LogEvent.hpp"
#include "Page.hpp"

class LogEvents {

 private:

 public:

  static const string versionMajor;
  static const string versionMinor;

  const long rvlimitDefault = 10;

  // Servo
  string errJson;

  // Request 
  string leprop;       /* Which properties to get: ids Adds the ID of the log event. title Adds the title of the page for the log event.     type Adds the type of log event. user Adds the user responsible for the log event. userid Adds the user ID who was responsible for the log event. timestamp Adds the timestamp for the log event. comment Adds the comment of the log event. parsedcomment Adds the parsed comment of the log event. details Lists additional details about the log event. tags Lists tags for the log event. Values (separate with |): ids, title, type, user, userid, timestamp, comment, parsedcomment, details, tags Default: ids|title|type|user|timestamp|comment|details */   
  string letype;       /* Filter log entries to only this type. One of the following values: Can be empty, or spamblacklist, titleblacklist, renameuser, massmessage, thanks, usermerge, block, protect, rights, delete, upload, move, import, patrol, merge, suppress, tag, managetags, contentmodel, review, stable, gblblock, globalauth, gblrights, gblrename, abusefilter, pagetriage-curation, pagetriage-deletion, institution, course, student, online, campus, instructor, newusers. */
  string leaction;     /* Filter log actions to only this action. Overrides letype. In the list of possible values, values with the asterisk wildcard such as action/ can have different strings after the slash (/). One of the following values: usermerge/mergeuser, usermerge/deleteuser, review/approve, review/approve2, review/approve-i, review/approve2-i, review/approve-a, review/approve2-a, review/approve-ia, review/approve2-ia, review/unapprove, review/unapprove2, rights/erevoke, gblblock/gblock, gblblock/gblock2, gblblock/gunblock, gblblock/whitelist, gblblock/dwhitelist, gblblock/modify, globalauth/delete, globalauth/lock, globalauth/unlock, globalauth/hide, globalauth/unhide, globalauth/lockandhid, globalauth/setstatus, suppress/setstatus, suppress/cadelete, gblrights/usergroups, gblrights/groupperms, gblrights/groupprms2, gblrights/groupprms3, suppress/hide-afl, suppress/unhide-afl, spamblacklist/, titleblacklist/, renameuser/renameuser, massmessage/, massmessage/send, massmessage/failure, massmessage/skipoptout, massmessage/skipnouser, massmessage/skipbadns, gather/action, thanks/, block/block, block/reblock, block/unblock, contentmodel/change, delete/delete, delete/event, delete/restore, delete/revision, import/interwiki, import/upload, managetags/activate, managetags/create, managetags/deactivate, managetags/delete, merge/merge, move/move, move/move_redir, patrol/patrol, protect/modify, protect/move_prot, protect/protect, protect/unprotect, rights/autopromote, rights/rights, suppress/block, suppress/delete, suppress/event, suppress/reblock, suppress/revision, tag/update, upload/overwrite, upload/revert, upload/upload, stable/config, stable/modify, stable/reset, gblrights/grouprename, gblrename/rename, gblrename/promote, gblrename/merge, gblrights/newset, gblrights/setrename, gblrights/setnewtype, gblrights/setchange, gblrights/deleteset, abusefilter/modify, abusefilter/hit, pagetriage-curation/reviewed, pagetriage-curation/unreviewed, pagetriage-curation/tag, pagetriage-curation/delete, pagetriage-deletion/delete, institution/, course/, student/, student/add, student/remove, online/, online/add, online/remove, campus/, campus/add, campus/remove, instructor/, instructor/add, instructor/remove, eparticle/, delete/flow-delete-post, delete/flow-delete-topic, suppress/flow-suppress-post, suppress/flow-suppress-topic, lock/flow-lock-topic, delete/flow-restore-post, suppress/flow-restore-post, delete/flow-restore-topic, suppress/flow-restore-topic, lock/flow-restore-topic, import/lqt-to-flow-topic, newusers/newusers, newusers/create, newusers/create2, newusers/byemail, newusers/autocreate */
  string lestart;        /* The timestamp to start enumerating from. Type: timestamp (allowed formats) */
  string leend;          /* The timestamp to end enumerating. Type: timestamp (allowed formats) */
  string ledir;          /* In which direction to enumerate: newer List oldest first. Note: lestart has to be before leend. older List newest first (default). Note: lestart has to be later than leend. One of the following values: newer, older Default: older */
  string leuser;         /* Filter entries to those made by the given user. Type: user name */
  string letitle;        /* Filter entries to those related to a page. */
  long int lenamespace;  /* Filter entries to those in the given namespace. One of the following values: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 100, 101, 108, 109, 118, 119, 446, 447, 710, 711, 828, 829, 2300, 2301, 2302, 2303, 2600 */
  string leprefix;       /* Disabled due to miser mode. */
  string letag;          /* Only list event entries tagged with this tag. */
  long int lelimit;      /* How many total event entries to return. No more than 500 (5,000 for bots) allowed. Type: integer or max Default: 10 */
  string lecontinue;

/*
  long int pageid = -1;
  int ns = -1;
*/
 
  // Response
  string batchcomplete;
  vector <LogEvent> events;
  string res;
  string clcontinue_res;
  string continue_res;

  LogEvents() {}
  
  LogEvents(const string& jsonString) {
   fromJsonString(jsonString);
  }
  
  LogEvents(const json11::Json& json) {
   fromJson(json);
  }

  void clear() {
   errJson = "";

   leprop = "";
   letype = "";
   leaction = "";
   lestart = "";
   leend = "";
   ledir = "";
   leuser = "";
   letitle = "";
   lenamespace = -1.;
   leprefix = "";
   letag = "";
   lelimit = -1;
   lecontinue = "";
   //pageid = -1;
   //ns = -1;

   batchcomplete = "";
   events.clear();
   res = "";
   continue_res = "";
  }
  
  void fromJsonString(const string& jsonString) {
   res = jsonString; 
   auto json = json11::Json::parse(jsonString, errJson);
   fromJson(json);
  }
  
  void fromJson(const json11::Json& json) {
   batchcomplete = json["batchcomplete"].string_value();
   auto firstContinueJson = json["continue"].object_items();
   clcontinue_res = firstContinueJson["clcontinue"].string_value();
   continue_res = firstContinueJson["continue"].string_value();
   auto queryJson = json["query"].object_items();
   auto logeventsJson = queryJson["logevents"].array_items();
   for(auto ile : logeventsJson) {
    LogEvent logEvent(ile);
    events.push_back(logEvent);
   }
  }
  
  string toJson() {
   /* not implemented */
   return "";
  }

};

const string LogEvents::versionMajor = "201512290030";
const string LogEvents::versionMinor = "201512290030";

#endif // #ifndef LOGEVENTS_HPP
 
