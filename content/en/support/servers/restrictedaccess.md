---
title: "Restricted Access"
type: archives
---

A restricted access time server does not require prior arrangements before use but has some restrictions on its use in addition to the usage guidlines listed below. These restrictions include, but are not limited to:

* [Notification Message](/support/servers/notificationmessage)
* Service only to clients within a specified [Service Area](/support/servers/servicearea)
* Service only to certain types of institutions
* Maximum number of clients
* Minimum poll interval 

Users are reponsible for reviewing the list entry for a Restricted Access server prior to using it.

#### Usage Guidelines

 The following usage guidelines apply to all time servers unless modified by the time server operator:

1. `iburst` may be used.
2. `burst` may not be used.
3. `minpoll/maxpoll` may not be changed below the defaults of 64 seconds and 1024 seconds respectively.
4. Clients should honor the KOD message.
5. Time Server IP addresses and/or hostnames may not be hard-coded in any hardware, firmware, or software without advance explicit written permission from the time server operator.