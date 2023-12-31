---
title: "HP e3000 MPE/iX NTP Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

May 29, 2001

* * *

NTP was first ported to MPE several years ago, but those diffs were never submitted back to the official NTP distribution.

NTP was re-ported to MPE in May 2001.  What follows are hints learned from working with NTP 4.0.99k23.  

* * *

MPE lacks the clock-related APIs expected by NTP, so `adjtime(), gettimeofday()`, and `settimeofday()` all had to be implemented from scratch by calling privileged, undocumented internal OS functions.

Unfortunately the implementation of `adjtime()` has exposed a sub-second accuracy bug when slewing the system time.  This bug is documented in SR 5003462838, and exists on all current versions of MPE.  It has not been fixed at the time of this writing.  The `adjtime()` code may possibly need to be altered if/when this bug is fixed.

This bug has a side-effect whereby the `ntpd` daemon will screw up the hardware PDC clock time by many minutes if used for continuous clock adjustments or in the one-time `-q` mode.  But note that you can safely run `ntpd` in order to become a time server if you include `disable ntp` in the `ntp.conf` configuration file.

The one-time clock adjustment functionality of `ntpdate` and `ntp_timeset` is not affected by this bug side-effect.  You can safely use these commands to alter your system time with reasonable accuracy.

The only reference clock that has been tested on MPE is the local clock.  So building NTP with `--disable-all-clocks --enable-LOCAL_CLOCK` is strongly recommended.

NTP makes use of Privileged Mode (PM) capability in order to bind to the NTP network port (123) and to access the low-level clock functions.

NTP was ported using the `gcc` compiler.  Attempting to use the HP C/iX compiler is not recommended and has not been tested.

Please note that NTP is not an HP product and is NOT supported by HP.  The best place for asking MPE-specific questions about NTP is the [HP3000-L mailing list](https://raven.utc.edu/SCRIPTS/WA.EXE?A0=HP3000-L) or the associated [newsgroup comp.sys.hp.mpe](https://groups.google.com/g/comp.sys.hp.mpe).

* * *

The original author of this port is:

[Mark Bixby](mailto:mark_bixby@hp.com)
: HP CSY MPE Internet & Interoperability Engineer