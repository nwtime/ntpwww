---
title: "DEC OSF/1 Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

Some major changes were necessary to make `xntp` v3 run on the DEC Alpha hardware running DEC OSF/1.  All `long` and `u_long` declarations and casts in the code were changed to `LONG` and `U_LONG` and a new header file (`include/ntp_types.h`) was added.  The new header file defines `LONG` as `int` and `U_LONG` as `u_int` for the Alpha hardware and as `long` and `u_long` for anything else.  A couple of `#if`s where changed in `ntpq` and `xntpdc` to get the result of a signal defined correctly.  The `Config.decosf1` file built the programs here with no problems.

I don't have a radio clock here, so none of that code has been tested. I have run `xntpd, xntpdc, xntpres, ntpq, ntpdate`, and `tickadj` under DEC OSF/1 v1.2-2 (BL10).

<pre>
Mike Iglesias                        Internet:    iglesias@draco.acs.uci.edu
University of California, Irvine     BITNET:      iglesias@uci
Office of Academic Computing         uucp:        ...!ucbvax!ucivax!iglesias
Distributed Computing Support        phone:       (714) 856-6926</pre>

* * *

Support for NTP Version 2 is included with the current OSF/1 release. If you are upgrading to NTP Version 3 with this distribution, you should not use the `xntpd` or `ntpq` programs that come with the OSF/1 release. The older programs should be replaced by the newer programs of the same name, either in situ or via a link to a tranquil spot like `/usr/local/bin`. The `make install` script in this distribution doesn't work due to a silly install program incompatibility, so you will need to copy the programs by
hand.

Don't use the `setup` utility to install or configure the `xntpd` installation, as it will cheerfully clobber your painstakingly crafted `ntp.conf` program. However, assuming you put this file in `/etc/ntp.conf`, you can use the `/sbin/init.d/xntpd` script to start and stop the daemon.

This distribution compiles with nominal murmur with the stock `cc` compiler that comes with OSF/1.

[Dave Mills](https://www.nwtime.org/tribute-to-david-l-mills/)
: Electrical Engineering Department
: Unibergisty of Delabunch