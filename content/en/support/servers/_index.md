---
title: "NTP Public Time Servers"
type: archives
---

This section provides lists of Network Time Protocol (NTP) public time servers. **Please read the [Rules Of Engagement](/support/servers/rulesofengagement) before using servers from these lists.**

> **ALERT** These lists are updated frequently and should not be cached or scraped. To add a time server or to edit your current time server entry, email [these details]() to the [webmaster](mailto:webmaster@nwtime.org).

* * *

#### Table of Contents

* [About the Public NTP Time Server Lists](#about-the-public-ntp-time-server-lists)
* [Finding A Time Server](#finding-a-time-server)
* [Searching for A Time Server](#searching-for-a-time-server)
* [Adding your Server to the Lists](#adding-your-server-to-the-lists)
* [Removing your Server from the Lists](#removing-your-server-from-the-lists)
* [Reporting Broken Time Servers](#reporting-broken-time-servers)

* * *

#### About the Public NTP Time Server Lists

The lists are provided for information purposes only and represent the best information available at the current date. The operators of the servers listed do not commit to provide time service other than on a volunteer basis and with no guarantee of accuracy or availability.

The list of primary ([stratum 1](/support/servers/stratumonetimeservers)) and secondary ([stratum 2](/support/servers/stratumtwo)) designates the NTP time servers available for public access under stated restrictions. Each entry gives the country code, state (US only), host name, Internet address, approximate location and geographic coordinates (if available), synchronization source (stratum, type of radio or satellite receiver and host type), suggested service area, access policy (as notified) and responsible person name and e-mail address. Most servers indicate the NTP version as well. It is always wise to consult the DNS to verify host addresses, which are changed from time to time. When more than one address is given, preference should given to each in order.

Please respect the access policy as stated by the responsible person. It is very important that potential clients avoid use of servers not listed as open access, unless approved first by the responsible person. This especially includes indiscriminate use of servers not listed in the list, since this can be disruptive. The responsible person should always be notified upon establishment of regular operations with servers listed as open access. Servers listed as closed access should NOT be used without prior permission, since this may disrupt ongoing activities in which these servers are involved.

All primary and secondary servers listed have no access restrictions, so that service is available for any client with a valid IP address. Where noted, some servers enforce a limit on the number of clients from any one network other than the server network itself. Where noted, some servers provide a cryptographic authentication service. Contact the site operators for further details.

* * *

#### Finding A Time Server

The _complete_ lists are available from the following links. For detailed information about a server click the hostname in the list.

*   [Public NTP Pool Time Servers](/support/servers/NTPPoolServers)
*   [Public NTP Secondary (stratum 2) Time Servers](/support/servers/StratumTwoTimeServers)
*   [Public NTP Primary (stratum 1) Time Servers](/support/servers/stratumonetimeservers)

* * *

#### Searching for A Time Server

Use [this page](/support/WebSearch) to search the Time Server Lists based on various criteria.

You may also search for your List entry by entering a portion of your host name (e.g. the domain) as _lower case_ text in the **Search** box at the top of any page.

* * *

#### Adding your Server to the Lists

Time Server operators may add, and maintain, their own List entries. **This is the recommended means of managing your List entries.** Please read [ManagingYourListEntries](/support/ManagingYourListEntries) for more information.

Time Server operators may choose to submit their List entries via e-mail to [webmaster](mailto:webmaster@nwtime.org). List entries submitted in this fashion will be entered by a volunteer when time permits. Please read [SubmittingYourListEntriesViaEmail](/support/SubmittingYourListEntriesViaEmail) for more information.

* * *

#### Removing your Server from the Lists

Time Server operators who wish to remove their servers from the list may to so by editing their List entries and changing the [ServerStratum](/support/ServerStratum) to _Inactive_.

Time Server operators may choose submit a removal request via e-mail to [webmaster](mailto:webmaster@nwtime.org). Removal requests submitted in this fashion will be processed by a volunteer when time permits.

* * *

#### Reporting Broken Time Servers

Anyone discovering [TimeServers](/support/TimeServer) that are broken (e.g. non-functional, incorrect stratum, etc.) for an extended period of time should contact [webmaster](mailto:webmaster@nwtime.org) only after attempting to contact the server operator.

Problems with the [NTP Pool](/support/NTPPoolServers) must be reported to the [NTP Pool Manager](mailto:ask@ntp.org).