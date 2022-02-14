---
title: "Restricted Access"
type: archives
---

A restricted access Time Server does not require a prior arrangement before use but has some usage restrictions in addition to the [Usage Guidlines](#usage-guidelines). These restrictions include, but are not limited to:

* Requiring a [Notification Message](/support/servers/notificationmessage/) prior to use
* Service only to clients within a specified [Service Area](/support/servers/servicearea/)
* Service only to certain types of institutions
* Maximum number of clients
* Minimum poll interval 

Users are reponsible for reviewing and following the information in the Time Server's list entry prior to use.

#### Usage Guidelines

 The following usage guidelines apply to all Time Servers unless modified by the Time Server operator:

1. `iburst` may be used.
2. `burst` may not be used.
3. `minpoll/maxpoll` may not be changed below the defaults of 64 seconds and 1024 seconds, respectively.
4. Clients should honor the KOD message.
5. Time Server IP addresses and/or hostnames may not be hard-coded in any hardware, firmware, or software without advance explicit written permission from the Time Server operator.