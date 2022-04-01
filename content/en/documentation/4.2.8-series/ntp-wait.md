---
title: "ntp-wait - waits until ntpd is in synchronized state"
type: archives
---

Last update: 12-Jul-2011 22:03 UTC

* * *

#### Synopsis

<code>ntp-wait [ -v ] [ -n _tries_ ] [ -s _seconds_ ]</code>

* * *

#### Description

The `ntp-wait` program blocks until `ntpd` is in synchronized state. This can be useful at boot time, to delay the boot sequence until after `ntpd -g` has set the time.

* * *

#### Command Line Options

<code>**-n _tries_**</code>

: Number of tries before giving up. The default is 1000.

<code>**-s _seconds_**</code>

: Seconds to sleep between tries. The default is 6 seconds.

<code>**-v**</code>

: Be verbose.