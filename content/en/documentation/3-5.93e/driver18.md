---
title: "NIST Modem Time Service"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver18/#synopsis)
*   [Description](/documentation/3-5.93e/driver18/#description)
*   [Call Management](/documentation/3-5.93e/driver18/#call-management)
*   [Monitor Data](/documentation/3-5.93e/driver18/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver18/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver18/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.18._u_</code>  
: **Reference ID:** <code>ACTS</code>
: **Driver ID:** <code>NIST_ACTS</code>
: **Serial Port:** <code>/dev/acts\__u_</code>; 1200 baud, 8-bits, no parity
: **Features:** <code>tty_clk</code>
: **Requires:** <code>/usr/include/sys/termios.h</code> header file with modem control

* * *

#### Description

This driver supports the NIST Automated Computer Time Service (ACTS). It periodically dials a prespecified telephone number, receives the NIST timecode data and calculates the local clock correction. It designed primarily for use when neither a radio clock nor connectivity to Internet time servers is available. For the best accuracy, the individual telephone line/modem delay needs to be calibrated using outside sources.

The ACTS is located at NIST Boulder, CO, telephone 303 494 4774. A toll call from Newark, DE, costs between three and four cents, although it is not clear what carrier and time of day discounts apply. The modem dial string will differ depending on local telephone configuration, etc., and is specified by the phone command in the configuration file. The argument to this command is an AT command for a Hayes compatible modem.

The driver can operate in either of two modes, as determined by the mode parameter in the server configuration command. In mode 0 the driver operates continuously at intervals determined by the fudge time1 parameter, as described above. In mode 1 the driver is enabled only when no other sources of synchronization are available and when we have gone more than MAXOUTAGE (3600 s) since last synchronized by other sources of synchronization.

The accuracy produced by this driver should be in the range of a millisecond or two, but may need correction due to the delay characteristics of the individual modem involved. For undetermined reasons, some modems work with the ACTS echo-delay measurement scheme and some don't. This driver tries to do the best it can with what it gets. Initial experiments with a Practical Peripherals 9600SA modem here in Delaware suggest an accuracy of a millisecond or two can be achieved without the scheme by using a fudge time1 value of 65.0 ms. In either case, the dispersion for a single call involving ten samples is about 1.3 ms.

For reliable call management, this driver requires a 1200-bps modem with a Hayes-compatible command set and control over the modem data terminal ready (DTR) control line. Present restrictions require the use of a POSIX-compatible programming interface, although other interfaces may work as well. The ACTS telephone number and modem setup string are hard-coded in the driver and may require changes for nonstandard modems or special circumstances.

The fudge time1 parameter represents a propagation-delay correction factor which is added to the value computed by ACTS when the echo-delay scheme is used. This scheme does not work with all modems; for those that don't, fudge flag2 should be set to disable the feature. In this case the fudge time1 parameter represents the total propagation delay due to all causes and must be determined by external calibration.

The ACTS call interval is determined by a counter initially set to the fudge time2 parameter. At each poll interval, minpoll (usually 64 s) is subtracted from the counter. When the counter is equal to or less than zero, the fudge flag1 is set, which causes up to three call attempts to be made to ACTS. The fudge flag1 is reset after a valid clock update has been determined or by a device fault, timeout or manually using `xntpdc`. After a valid clock update, the counter is reset for the next interval. Setting the `fudge time2` parameter to zero disables automatic call attempts. Manual call attempts can be made at any time by setting `fudge flag1` using <code>xntpdc</code>.

The NIST timecode message is transmitted at 1200 bps in the following format:

<pre>
jjjjj yy-mm-dd hh:mm:ss tt l uuu mmmmm UTC(NIST) *

jjjjj = modified Julian day
yy-mm-dd = year, month, day
hh:mm:ss = hours, minutes, seconds
tt = DST indicator (see driver listing)
l = leap-second warning (see driver listing)
uuu = DUT1 correction (see driver listing)
mmmmm = modem calibration (see driver listing)
on-time = '*'
</pre>

The timecode message is transmitted continuously after a signon banner, which this driver ignores. The driver also ignores all but the yy-mm-dd, hh:mm:ss and on-time character `*` fields, although it checks the format of all fields of the message. A timestamp is captured at the `*` character, as required by the ACTS specification, and used as the reference time of the timecode. If a message with an on-time character of `#` is received, the driver updates the propagation delay. The driver disconnects when (a) ten valid messages have been received, (b) no message has been received for 15 s, (c) an on-time character of `#` is received. These messages are processed by a trimmed-mean filter to reduce timing noise and then by the usual NTP algorithms to develop the clock correction.

Since the accumulated error grows with the interval between calls, it is important that the intrinsic frequency error be minimized. This can be done by observing difference in offsets between two calls placed some hours apart and calculating the uncorrected frequency error. This error, as a fixed-point value in parts-per-million, should be installed in the ntp.drift file before the daemon is started. Some experimentation may be necessary in order to reduce the intrinsic frequency error to the order of 1 ppm.

The behavior of the clock selection algorithm is modified when this driver is in use. The algorithm is designed so that this driver will never be selected unless no other discipline source is available. This can be overridden with the prefer keyword of the server configuration command, in which case only this driver will be selected for synchronization and all other discipline sources will be ignored.

Unlike other drivers, each ACTS call generates one clock correction and that correction is processed immediately. There is no wait to allow the clock filter to accumulate samples. In addition, the watchdog timeout of the local clock algorithm is disabled, so that a correction received from this driver that exceeds <code>CLOCK_MAX</code> (128 ms) causes an immediate step/slew.

Since the interval between updates can be much longer than used with ordinary NTP peers, the local clock procedure has been modified to operate in either of two modes, depending on whether the interval between updates is less than or greater than <code>CLOCK_MAXSEC</code> (1200 s). If less than this value, the local clock procedure operates using the standard NTP phase-lock loop as with other NTP peers. If greater than this value, the procedure operates using a modified frequency-lock loop suggested by Judah Levine in his lockclock algorithm designed specifically for ACTS.

* * *

#### Call Management

Since ACTS will be a toll call in most areas of the country, it is necessary to carefully manage the call frequency. This can be done in two ways, by specifying the interval between calls, or by setting a flag bit manually or via a <code>cron</code> job. The call interval is determined by a counter initially set to the <code>fudge time2</code> parameter. At each poll interval, <code>minpoll</code> (usually 64 s) is subtracted from the counter. When the counter is equal to or less than zero, the <code>fudge flag1</code> is set, which causes up to three call attempts to be made. The <code>fudge flag1</code> is reset after ten offset samples have been determined in a single call or by a device fault, timeout, or manually using <code>xntpdc</code>. Upon successful completion of a call, the eight samples have been shifted into the clock filter, the local clock updated and the counter reset for the next interval. Setting the <code>fudge time2</code> parameter to zero disables automatic call attempts.

Manual call attempts can be made at any time by setting <code>fudge flag1</code> using <code>xntpdc</code>. For example, the <code>xntpdc</code> command

<pre>
fudge 127.127.18.1 flags 1
</pre>

will ask for a key identifier and password and, if authenticated by the server, will set <code>flag1</code>. There may be a short delay until the expiration of the current poll timeout.

The <code>flag1</code> can be set from a <code>cron</code> job in the following way. Construct a file with contents

<pre>keyid 11
passwd dialup
fudge 127.127.18.1 flags 1
quit
</pre>

Then, run the following program at specified times as required.

`/usr/local/bin/xntpdc <file`

* * *

#### Monitor Data

When enabled by the <code>flag4</code> fudge flag, every received timecode is written as-is to the <code>clockstats</code> file.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>ACTS</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set.

<code>**flag4 0 | 1**</code>

: Enable <code>clockstats</code> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)