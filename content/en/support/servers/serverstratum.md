---
title: "Server Stratum"
type: archives
---

The Time Server stratum is the position at which a [Time Server](/support/servers/timeserver) operates in the NTP hierarchy.

A _Stratum One Time Server_ is directly connected to a reference clock and is at the top of the Time Server hierarchy.

A _Stratum Two Time Server_ receives the time from one or more Stratum One Time Servers. Stratum Two Time Servers are not significantly less accurate than Stratum One Time Servers.

> Use the `Inactive` option of Server Stratum to mark a Time Server as inactive. 