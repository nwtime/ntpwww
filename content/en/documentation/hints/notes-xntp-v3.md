---
title: "Notes for NTPv3"
type: archives
noindex: true 
sitemap_exclude: true
---

This version operates in much the same manner as Version 2 with the following changes and additions:

1. The protocol machinery operates in conformance with the [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) NTP Version 3 specification. The most visible characteristic of this version is that the poll intervals for all polls, even selected ones, is significantly increased. This is especially desirable when serving a large client population. This implementation supports previous versions as non-configured peers; for version-2 configured peers a `version 2` keyword should be included on the `peer` line.

2. The configuration file has a new keyword: <code>statfile \<file></code>, where <code>\<file></code> is the name of a statistics file. When present, each clock update generates an entry of the form:

   <code>\<day> \<sec>.\<frac> \<addr> \<status> \<offset> \<delay> \<disp></code>

   where <code>\<day></code> is the modified Julian day, <code>\<sec>.\<frac></code> is the time of day, <code>\<addr></code> is the peer address and <code>\<status></code> is the peer status. The <code>\<offset>, \<delay></code> and <code>\<disp></code> are the measured offset, delay and dispersion, respectively, of the peer clock relative to the local clock. About once per day the current file is closed and a new one created with names <code>\<file>.\<gen></code>, where <code>\<gen></code> starts at one and increments for each new generation.

3. A number of additional platforms are supported. See `./Config` file for details.

4. A driver for the TrueTime 468DC GOES Synchronized Clock is included. This driver (`refclock_goes.c`) should also work for other TrueTime radio clocks, since all use the same format.

5. A replacement driver for the Spectracom 8170 WWVB Synchronized Clock is included. This driver (`refclock_wwvb.c`) (a) does not require a 1-pulse-per-second signal, (b) supports both format 0 (original 8170) and format 2 (Netclock/2 and upgraded 8170), (c) can be connected to more than one computer and (d) automatically compensates for all serial baud rates.

6. A driver for the German time/frequency station DCF77 is included. This requires a special STREAMS module.

7. In Version 2 special line-discipline modules were required for the CHU and WWVB drivers. This code continues to work in Version 3, although it is no longer needed for the WWVB driver. However, this code does not work under STREAMS, as used in SunOS 4.1.1. Equivalent STREAMS modules are supplied with Version 3.

8. Support for an external 1-pulse-per-second (pps) signal is provided. The signal is connected to a serial port (see `xntpd/ntp_loopfilter.c` for details). When present the leading edge of the pulse establishes the on-time epoch within an interval established by the selected radio clock or other NTP time server. Use of the pps is indicated when the tattletale displayed by `ntpq` changes from `*` to `o`.

9. The clock-selection and poll-update procedures have been modified slightly in order to achieve better performance on high speed LANs with compromise in performance on typical WANs.

10. In order to comply with U.S. Commerce Department regulations, the DES encryption routine `lib/authdes.c` cannot be exported. For exportable versions of this distribution a DES-encrypted version of this routine `lib/authdes.c.des` is included along with an unencrypted version `lib/authdes.c.export`, which allows normal operation, but without the NTP authentication feature. Further information is available in the `lib/authdes.c.export` file.

11. As an alternative to the DES-based authentication mechanism, an implementation of the RSA Message Digest 5 algorithm is provided. (see applicable copyright information in the library files).

12. A driver for the Magnavox MX4200 GPS clock.

13. A STREAMS module which captures carrier-detect data-lead transitions to connect a precision source of 1-pps, yet avoid the ugly overhead in the usual STREAMS processing. See the `ppsclock` subdirectory.

14. Support for the Apple A/UX operating system and enhanced support for the Hewlet-Packard HP/UX operating system. See the various `README` and `Config` files for further information.

See the `COPYRIGHT` file for authors and copyright information. Note that some modules in this distribution contain copyright information that supersedes the copyright information in that file.

If I missed something or neglected to give due credit, please advise.

David L. Mills
: University of Delaware
: 31 May 1992, amended 23 July 1992, 25 October 1992

#### Bugs and notes

A bug in the original `tty_clk_STREAMS.c` module has been fixed.

The poll-interval randomization feature of poll_update (in `xntpd/ntp_proto.c`) has been extended to apply when the poll interval is increased, as well as reduced. This spreads the update messages in time
and helps avoid unpleasant bursts of messages.

In the `clock_select` algorithm the peers selected for combining are limited to those survivors at the lowest stratum, not the entire list. This helps avoid whiplash when large numbers of peers are at the same
stratum.

The number formerly displayed by `ntpq` as "compliance" is now the time constant of integration.

The DNS resolver `xntpd/ntp_intres.c` is now integrated into `xntpd`, making configuration of multiple hosts easier.

System and peer events are now written to the system log at priority `LOG_INFO`.

The leap-second code was fixed to avoid broadcasting leap warnings on all except the last day of June and December.