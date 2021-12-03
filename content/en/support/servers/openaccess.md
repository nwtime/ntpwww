---
title: "Open Access"
type: archives
---

An open access Time Server may be polled by any client complying with the [Usage Guidelines](#usage-guidelines).

Clients should respect any declared [Service Area](/support/servers/servicearea), but are not required to do so.

Operators of open access Time Servers may request, but may not require, a [Notification Message](/support/servers/notificationmessage) prior to use.

#### Usage Guidelines

 The following usage guidelines apply to all Time Servers unless modified by the Time Server operator:

1. `iburst` may be used.
2. `burst` may not be used.
3. `minpoll/maxpoll` may not be changed below the defaults of 64 seconds and 1024 seconds, respectively.
4. Clients should honor the KOD message.
5. Time Server IP addresses and/or hostnames may not be hard-coded in any hardware, firmware, or software without advance explicit written permission from the Time Server operator.