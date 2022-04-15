---
title: "parse"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Compilation

Usual thing: `rm -f Config.local ; make` for vanilla and `make refconf` for reference clock (e. g. DCF77).

* * *

#### Directory Contents

<code>**hints/PARSE**</code>
: This file.

<code>**xntpd/refclock_parse.c**</code>
: Reference clock support for DCF77/GPS in `xntp`.

<code>**parse/parse.c**</code>
: Reference clock data parser framework.

<code>**parse/parse_conf.c**</code>
: Parser configuration (clock types).

<code>**parse/clk_meinberg.c**</code>
: Meinberg clock formats (DCF U/A 31, PZF 535, GPS166).

<code>**parse/clk_schmid.c**</code>
: Schmid receiver (DCF77).

<code>**parse/clk_rawdcf.c**</code>
: 100/200ms pulses via 50 Baud line (DCF77).

<code>**parse/clk_dcf7000.c**</code>
: ELV DCF7000 (DCF77).

<code>**parse/clk_trimble.c**</code>
: Trimble SV6 GPS receiver. If you want to add new clock types please check with kardel@informatik.uni-erlangen.de. These files implement the conversion of RS232 data streams into timing information used by `refclock_parse.c` which is mostly generic except for NTP configuration constants.

<code>**parse/Makefile.kernel**</code>
: *SIMPLE* makefile to build a loadable STREAMS module for SunOS 4.x / SunOS 5.x systems.

<code>**parse/parsestreams.c**</code>
: SUN Streams module (loadable) for radio clocks. This streams module is designed for SunOS 4.1.X.

<code>**parse/parsesolaris.c**</code>
: SUN Streams module (loadable) for radio clocks. This streams module is designed for SunOS 5.x. Beware this is still new - so it might crash your machine (we have seen it working, though).

<code>**parse/parsetest.c**</code>
: Simple test program for STREAMS module. It's so simple, that it doesn't even set TTY-modes, thus they got to be correct on startup - works for Meinberg receivers.

<code>**parse/testdcf.c**</code>
: Test program for raw DCF77 (100/200ms pulses) receivers.

<code>**include/parse.h**</code>
: Interface to `parse` module and more.

<code>**include/parse_conf.h**</code>
: Interface to `parse` configuration.

<code>**include/sys/parsestreams.h**</code>
: STREAMS specific definitions.

<code>**scripts/support**</code>
: Scripts (`perl` and `sh`) for statistics and `rc` startup. The startup scripts are used in Erlangen for
starting the daemon on a variety of Suns and HPs and for Reference Clock startup on Suns. These scripts may or may not be helpful to you.

* * *

#### Supported Clocks

* Meinberg DCF U/A 31
* Meinberg PZF535/TCXO	(Software revision PZFUERL 4.6)
* Meinberg PZF535/OCXO	(Software revision PZFUERL 4.6)
* Meinberg GPS166		(Software version for Uni-Erlangen)
* ELV DCF7000		(not recommended - casual/emergency use only)
* Conrad DCF77 receiver	(email: time@informatik.uni-erlangen.de) + level converter
* TimeBrick		(email: time@informatik.uni-erlangen.de)
* Schmid Receiver Kit
* Trimble SV6 GPS receiver

* * *

#### Addresses

Meinberg Funkuhren
: Auf der Landwehr 22
: 31812 Bad Pyrmont
: Germany
: Tel.: 05281/20 18
: FAX:  05281/60 81 80

ELV Kundenservice
: Postfach 1000
: 26787 Leer
: Germany
: Tel.: 0491/60 08 88

Walter Schmidt
: Eichwisrain 14
: 8634 Hombrechtikon
: Switzerland

If you have problems mail to: <time@informatik.uni-erlangen.de> and we'll help (conditions permitting).

</pre>