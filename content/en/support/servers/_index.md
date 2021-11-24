---
title: "NTP Public Time Servers"
type: archives
---

This section provides lists of Network Time Protocol (NTP) public time servers. **Please read the [Rules Of Engagement](/support/servers/rulesofengagement) before using servers from these lists.**

> **ALERT** These lists are updated frequently and should not be cached or scraped. To add a time server, modify or delete an existing time server entry, or to report an incorrect time server entry, email the details to the [webmaster](mailto:webmaster@nwtime.org).

* * *

#### Table of Contents

* [About the Public NTP Time Server Lists](#about-the-public-ntp-time-server-lists)
* [Finding A Time Server](#finding-a-time-server)
* [Finding A Time Server by Feature](#finding-a-time-server-by-feature)
* [Reporting Broken Time Servers](#reporting-broken-time-servers)

* * *

#### About the Public NTP Time Server Lists

The lists are provided for information purposes only and represent the best information available at the current date. The operators of the servers listed do not commit to provide time service other than on a volunteer basis and with no guarantee of accuracy or availability.

The list of primary ([stratum 1](/support/servers/stratumonetimeservers)) and secondary ([stratum 2](/support/servers/stratumtwotimeservers)) designates the NTP time servers available for public access under stated restrictions. Each entry gives the country code, state (US only), host name, Internet address, approximate location and geographic coordinates (if available), synchronization source (stratum, type of radio or satellite receiver and host type), suggested service area, access policy (as notified) and responsible person name and e-mail address. Most servers indicate the NTP version as well. It is always wise to consult the DNS to verify host addresses, which are changed from time to time. When more than one address is given, preference should given to each in order.

Please respect the access policy as stated by the responsible person. It is very important that potential clients avoid use of servers not listed as open access, unless approved first by the responsible person. This especially includes indiscriminate use of servers not listed in the list, since this can be disruptive. The responsible person should always be notified upon establishment of regular operations with servers listed as open access. Servers listed as closed access should NOT be used without prior permission, since this may disrupt ongoing activities in which these servers are involved.

All primary and secondary servers listed have no access restrictions, so that service is available for any client with a valid IP address. Where noted, some servers enforce a limit on the number of clients from any one network other than the server network itself. Where noted, some servers provide a cryptographic authentication service. Contact the site operators for further details.

* * *

#### Finding A Time Server

The _complete_ lists are available from the following links. For detailed information about a server click the hostname in the list.

*   [Public NTP Pool Time Servers](/support/servers/ntppoolservers)
*   [Public NTP Secondary (stratum 2) Time Servers](/support/servers/stratumtwotimeservers)
*   [Public NTP Primary (stratum 1) Time Servers](/support/servers/stratumonetimeservers)

* * *

#### Finding A Time Server by Feature

* [Time Servers supporting IPv6](/support/servers/publictimeserver000638)
* [Servers synchronized by CDMA](/support/servers/serverssynchronizedbycdma)
* [Servers synchronized by GPS](/support/servers/serverssynchronizedbygps)
* [Servers authenticated with Autokey](/support/servers/serversauthenticatedwithautokey)
* [Servers authenticated with MD5](/support/servers/serversauthenticatedwithmd5)
* Servers authenticated with DES

* * *

Anyone discovering [TimeServers](/support/TimeServer) that are broken (e.g. non-functional, incorrect stratum, etc.) for an extended period of time should contact [webmaster](mailto:webmaster@nwtime.org) only after attempting to contact the server operator.

Problems with the [NTP Pool](/support/NTPPoolServers) must be reported to the [NTP Pool Manager](mailto:ask@ntp.org).