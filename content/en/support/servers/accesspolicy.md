---
title: "Access Policy"
type: archives
---

The general access policy of a [Time Server](/support/servers/timeserver). The following choices are available:

* [Open Access](/support/servers/openaccess) - This Time Server is open to any client complying with the [Usage Guidelines](#usage-guidelines).
* [Restricted Access](/support/servers/restrictedaccess) - This Time Server has some access restrictions in addition to the [Usage Guidelines](#usage-guidelines).
* [Closed Access](/support/servers/closedaccess) - This Time Server is closed or requires prior arrangement for use.

#### Usage Guidelines

 The following usage guidelines apply to all Time Servers unless modified by the Time Server operator:

1. `iburst` may be used.
2. `burst` may not be used.
3. `minpoll/maxpoll` may not be changed below the defaults of 64 seconds and 1024 seconds, respectively.
4. Clients should honor the KOD message.
5. Time Server IP addresses and/or hostnames may not be hard-coded in any hardware, firmware, or software without advance explicit written permission from the Time Server operator.