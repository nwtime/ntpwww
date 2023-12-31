---
title: "BSDi Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

Author:		Bdale Garbee, bdale@gag.com
: Last revision:	27Oct94 (Paul Vixie)

* * *

Included in this distribution of XNTP is a configuration file suitable for use with BSDI's BSD/OS 1.1 (formerly BSD/386 1.1).  On this system, the `cc` command is GCC 1.4x rather than PCC or GCC 2.x.  It is imperative that `cc` be used since it predefines the symbol <code>\_bsdi\_</code>; if you want to
use another compiler you will need to add <code>-D\_bsdi\_</code> to catch the various `#ifdef`'s required for this system.

The Kinemetrics/Truetime GPS-TM/TMD driver is known to work on this system. The GPS-805 and GOES should also work fine.  Hell, they should all work fine but it's hard to test very many locally.

Due to BNR2's strict interpretation of POSIX and XNTP's use of SIGIO, BSD/OS can only handle one refclock per daemon.  We're working this out with the system architects.

The config file is `machine/bsdi`, and the following steps should be all that are required to install and use the bits.

Note that you will need GNU `sed`; the version supplied with BSD/OS 1.1 loops endlessly during `make refconf`.  Likewise you should get GNU `make`, which the instructions below assume that you have put in `/usr/local/bin/gnumake.`

To build the software:

	rm -f Config.local
	gnumake refconf
	gnumake MAKE=gnumake

To install the software:

	gnumake install

This will place all of the executables in `/usr/local/etc`.  The config file is expected to be `/usr/local/etc/xntp.conf` and the key file for the optional authentication is `/etc/ntp.keys`.

Craft a config file and a key file, and put them in the right places. There is information on how to do this elsewhere in the documentation, the only thing I'll mention is that I put the drift file in
`/var/log/ntp.drift`, and the `authdelay` on my 486DX/50 system is 0.000064.  Your mileage will vary, learn to use the `authspeed` tools if you're going to authenticate.

In the file `/etc/rc.local`, make sure that the invocation of `ntpd` is commented out, and add an invocation of `xntpd`.  Here's what I'm using:

		echo -n 'starting local daemons:'

		if [ -f /etc/ntp.keys -a -f /usr/local/etc/xntp.conf ]; then
		    echo -n ' xntpd';           /usr/local/etc/xntpd
		fi

		#XXX# echo -n ' ntpd';          /usr/libexec/ntpd -t

At this point, you should be good to go.  Try running `/usr/local/etc/xntpd` and using `ntpq` or `xntpdc` to see if things are working, then pay attention the next time you reboot to make sure that `xntpd` is being invoked, and use `ntpq` or `xntpdc` again to make sure all is well.

Enjoy!