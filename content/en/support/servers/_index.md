---
title: "NTP Public Time Servers"
type: archives
---

This section provides lists of Network Time Protocol (NTP) public Time Servers. **Please read the [Rules Of Engagement](/support/servers/rulesofengagement/) before using servers from these lists.**

> **ALERT** These lists are updated frequently and should not be cached or scraped.

* * *

#### Table of Contents

* [About the Public NTP Time Server Lists](#about-the-public-ntp-time-server-lists)
* [Finding A Time Server](#finding-a-time-server)
* [Finding A Time Server by Feature](#finding-a-time-server-by-feature)
* [Adding, Modifying, or Deleting your Server Entry](#adding-modifying-or-deleting-your-server-entry)
* [Reporting Broken Time Servers](#reporting-broken-time-servers)

* * *

#### About the Public NTP Time Server Lists

The lists are provided for information purposes only and represent the best information available at the current date. The operators of the listed Time Servers do not commit to provide time service other than on a volunteer basis and with no guarantee of accuracy or availability.

The primary ([Stratum One](/support/servers/stratumonetimeservers/)) and secondary ([Stratum Two](/support/servers/stratumtwotimeservers/)) Time Servers lists designate the NTP Time Servers available for public access under stated restrictions. Each entry gives the country code, state (US only), hostname or IP address, approximate location and geographic coordinates (if available), synchronization source, suggested service area, access policy, and server contact.

Please respect the access policy as stated by the responsible person. It is important that clients avoid the use of servers not listed as open access, unless approved by the responsible person. The responsible person should be notified upon establishment of regular operations with servers listed as open access. Servers listed as closed access should NOT be used without prior permission. Where noted, some servers enforce a limit on the number of clients from any one network. Where noted, some servers provide a cryptographic authentication service. Contact the site operators for further details.

* * *

#### Finding A Time Server

The Time Server lists are available from the following links. For detailed information about a server, click the ISO hyperlink in the list entry.

*   [Public NTP Pool Time Servers](/support/servers/ntppoolservers/)
*   [Public NTP Secondary (Stratum Two) Time Servers](/support/servers/stratumtwotimeservers/)
*   [Public NTP Primary (Stratum One) Time Servers](/support/servers/stratumonetimeservers/)

* * *

#### Finding A Time Server by Feature

* [Time Servers supporting IPv6](/support/servers/publictimeserver000638/)
* [Servers synchronized by CDMA](/support/servers/serverssynchronizedbycdma/)
* [Servers synchronized by GPS](/support/servers/serverssynchronizedbygps/)
* [Servers authenticated with Autokey](/support/servers/serversauthenticatedwithautokey/)
* [Servers authenticated with MD5](/support/servers/serversauthenticatedwithmd5/)

* * *

#### Adding, Modifying, or Deleting your Server Entry

To add a Time Server, modify, or inactivate an existing Time Server entry, email the following details to the [webmaster](mailto:webmaster@nwtime.org). Click an Item entry for a full description.

| Item | Value | Required |
| ----- | ----- | ----- |
| [Server Stratum](/support/servers/serverstratum/) | Indicate if the server is [Stratum One](/support/servers/stratumonetimeservers/), [Stratum Two](/support/servers/stratumtwotimeservers/), or [Inactive](/support/servers/inactivetimeservers/) | Required |
| [Country Code](/support/servers/countrycode/) | 2 digit country code; for US, indicate 2 digit state code | Required |
| Hostname, IP Address, IPv6 Address | | At least one is required |
| [Use DNS](/support/servers/usedns/) | Yes or No | Required |
| [Pool Member](/support/servers/poolmember/) | Yes or No | Optional |
| [Server Location](/support/servers/serverlocation/) | | Optional |
| [Host Organization](/support/servers/hostorganization/) | | Optional |
| [ Geographic Coordinates](/support/servers/geographiccoordinates/) |  | Optional |
| [Server Synchronization](/support/servers/serversynchronization/) | | Optional |
| [Service Area](/support/servers/servicearea/) | | Recommended |
| [Access Policy](/support/servers/accesspolicy/) | One of [Open](/support/servers/openaccess/), [Closed](/support/servers/closedaccess/), or [Restricted](/support/servers/restrictedaccess/) | Required |
| [Access Details](/support/servers/accessdetails/) |  | Optional |
| [Notification Message](/support/servers/notificationmessage/) | Yes or No | Required |
| [Autokey](/support/servers/autokey/) | Yes or No | Optional |
| [Autokey URL](/support/servers/autokeyurl/) | Yes or No | Optional |
| [Symmetric Key](/support/servers/symmetrickey/) | Yes or No | Optional |
| [Symmetric Key Type](/support/servers/symmetrickeytype/) | Yes or No | Optional |
| [Symmetric Key URL](/support/servers/symmetrickeyurl/) | Yes or No | Optional |
| [Server Contact](/support/servers/servercontact/) | | Required  |

Please also indicate if the server entry should appear in any of the [Server Feature lists](#finding-a-time-server-by-feature).

* * *

#### Reporting Broken Time Servers

Anyone discovering [Time Servers](/support/servers/timeserver/) that are broken for an extended period of time should contact the [webmaster](mailto:webmaster@nwtime.org) only after attempting to contact the server operator.

Problems with the [NTP Pool](/support/servers/ntppoolservers/) must be reported to the [NTP Pool Manager](mailto:ask@ntp.org).