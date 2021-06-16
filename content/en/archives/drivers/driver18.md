---
title: "NIST/USNO/PTB Modem Time Services"
type: archives
---

Author: David L. Mills (mills@udel.edu)  
Last update: 12-Oct-2017 08:13 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver18/#synopsis)
*   [Description](/archives/drivers/driver18/#description)
*   [US Phone Numbers and Formats](/archives/drivers/driver18/#us-phone-numbers-and-formats)
*   [Monitor Data](/archives/drivers/driver18/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver18/#fudge-factors)
*   [Additional Information](/archives/drivers/driver18/#additional-information)

* * *

#### Synopsis

Address: 127.127.18._u_  
Reference ID: <tt>NIST | USNO | PTB | WWVB</tt>  
Driver ID: <tt>ACTS_MODEM</tt>  
Serial Port: <tt>/dev/acts_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>  
Requires: <tt>/usr/include/sys/termios.h</tt> header file with modem control and a dial-out (cua) device.

* * *

#### Description

This driver supports the US (NIST and USNO) and European (PTB (Germany), NPL (UK), etc.) modem time services, as well as Spectracom GPS and WWVB receivers connected via a modem. The driver periodically dials a number from a telephone list, receives the timecode data and calculates the local clock correction. It is designed primarily for backup when neither a radio clock nor connectivity to Internet time servers are available. It can also be configured to operate full period.

For best results the indicated time must be corrected for the modem and telephone circuit propagation delays, which can reach 200 ms or more. For the NIST service, corrections are determined automatically by measuring the roundtrip delay of echoed characters. With this service the absolute accuracy is typically a millisecond or two. Corrections for the other services must be determined by other means. With these services variations from call to call and between messages during a call are typically a few milliseconds, occasionally higher.

This driver requires a 9600-bps modem with a Hayes-compatible command set and control over the modem data terminal ready (DTR) control line. The actual line speed ranges from 1200 bps with USNO to 14,400 bps with NIST. The modem setup string is hard-coded in the driver and may require changes for nonstandard modems or special circumstances.

There are three modes of operation selected by the <tt>mode</tt> keyword in the <tt>server</tt> configuration command. In manual mode (2) the calling program is initiated by setting fudge <tt>flag1</tt>. This can be done manually using <tt>ntpq</tt>, or by a cron job. In auto mode (0) <tt>flag1</tt> is set at each poll event. In backup mode (1) <tt>flag1</tt> is set at each poll event, but only if no other synchronization sources are available.

When <tt>flag1</tt> is set, the calling program dials the first number in the list specified by the <tt>phone</tt> command. If the call fails for any reason, the program dials the second number and so on. The phone number is specified by the Hayes ATDT prefix followed by the number itself, including the prefix and long-distance digits and delay code, if necessary. The <tt>flag1</tt> is reset and the calling program terminated if (a) valid clock update has been determined, (b) no more numbers remain in the list, (c) a device fault or timeout occurs or (d) fudge <tt>flag1</tt> is reset manually using <tt>ntpq</tt>.

The driver automatically recognizes the message format of each modem time service. It selects the parsing algorithm depending on the message length. There is some hazard should the message be corrupted. However, the data format is checked carefully and only if all checks succeed is the message accepted. Corrupted lines are discarded without complaint. Once the service is known, the reference identifier for the driver is set to NIST, USNO, PTB or WWVB as appropriate.

The Spectracom radio can be connected via a modem if the radio is configured to send time codes continuously at 1-s intervals. In principle, fudge <tt>flag2</tt> enables port locking, allowing the modem to be shared when not in use by this driver. At least on Solaris with the current NTP I/O routines, this results in lots of ugly error messages.

The <tt>minpoll</tt> and <tt>maxpoll</tt> keywords of the server configuration command can be used to limit the intervals between calls. The recommended settings are 12 (1.1 hours) for <tt>minpoll</tt> and 17 (36 hours) for <tt>maxpoll</tt>. Ordinarily, the poll interval will start at <tt>minpoll</tt> and ramp up to <tt>maxpoll</tt> in a day or two.

* * *

#### US Phone Numbers and Formats

**Note:** Phone numbers include the entire Hayes modem command, including the <tt>ATDT</tt> and other control codes as may be necessary. For most cases only the <tt>ATDT</tt> may be necessary.

[National Institute of Science and Technology (NIST)](https://www.nist.gov/time-distribution/automated-computer-time-service-acts)

Phone: (303) 494-4774 (Boulder, CO); (808) 335-4721 (Hawaii)

Data Format:

<tt>National Institute of Standards and Technology  
Telephone Time Service, Generator 3B  
Enter question mark "?" for HELP  
MJD YR MO DA H M S ST S UT1 msADV <OTM>  
47999 90-04-18 21:39:15 50 0 +.1 045.0 UTC(NIST) *  
47999 90-04-18 21:39:16 50 0 +.1 045.0 UTC(NIST) #  
...</tt>

<tt>MJD</tt>, <tt>YR</tt>, <tt>ST</tt>, <tt>UT1</tt> and <tt>UTC(NIST)</tt> are not used by this driver. The <tt><OTM></tt> on-time character `*` changes to `#` when the delay correction is valid.

[US Naval Observatory (USNO)](https://www.usno.navy.mil/)

Phone: (202) 762-1594 (Washington, DC); (719) 567-6743 (Colorado Springs, CO)

[Data Format](https://www.usno.navy.mil/USNO/time/telephone-time) (two lines, repeating at one-second intervals)

<tt>jjjjj nnn hhmmss UTC</tt>

* on-time character for previous timecode message  
jjjjj modified Julian day number (not used)  
nnn day of year  
hhmmss second of day

[European Phone Numbers and Formats](/archives/drivers/tf582_4)

[Spectracom GPS and WWVB Receivers](http://www.spectracomcorp.com)

If a modem is connected to a Spectracom receiver, this driver will call it and retrieve the time in one of two formats, 0 and 2. Ordinarily, the receiver requires a <tt>T</tt> in order to return the timecode. As this driver does not send data via the modem, it must either be configured in continuous mode or be polled by another local driver.

* * *

#### Monitor Data

The received timecode is written as-is to the <tt>clockstats</tt> file along with the Hayes connection and hang-up commands and result codes.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Set by the driver to (one of) <tt>NIST</tt>, <tt>USNO</tt>, <tt>PTB</tt> or <tt>WWVB</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Initiate a call if 1. Automatically reset by program.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Enables port locking if 1, disables if 0 (default).</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

</dl>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock) 
