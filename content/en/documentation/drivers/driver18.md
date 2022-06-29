---
title: "NIST/USNO/PTB Modem Time Services"
description: "The NIST/USNO/PTB Modem Time Services driver supports the US (NIST and USNO), Germany (PTB), and UK (NPL) modem time services, as well as Spectracom GPS and WWVB receivers connected via a modem."
type: archives
---

Author: [David L. Mills](mailto:mills@udel.edu)

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver18/#synopsis)
*   [Description](/documentation/drivers/driver18/#description)
*   [US Phone Numbers and Formats](/documentation/drivers/driver18/#us-phone-numbers-and-formats)
*   [Monitor Data](/documentation/drivers/driver18/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver18/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver18/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.18._u_</code>
: **Reference ID:** `NIST | USNO | PTB | WWVB`
: **Driver ID:** `ACTS_MODEM`
: **Serial Port:** <code>/dev/acts*u*</code>; 9600 baud, 8-bits, no parity
: **Features:** `tty_clk`
: **Requires:** `/usr/include/sys/termios.h` header file with modem control and a dial-out (cua) device.

* * *

#### Description

This driver supports the US (NIST and USNO) and European (PTB (Germany), NPL (UK), etc.) modem time services, as well as Spectracom GPS and WWVB receivers connected via a modem. The driver periodically dials a number from a telephone list, receives the timecode data and calculates the local clock correction. It is designed primarily for backup when neither a radio clock nor connectivity to Internet time servers are available. It can also be configured to operate full period.

For best results the indicated time must be corrected for the modem and telephone circuit propagation delays, which can reach 200 ms or more. For the NIST service, corrections are determined automatically by measuring the roundtrip delay of echoed characters. With this service the absolute accuracy is typically a millisecond or two. Corrections for the other services must be determined by other means. With these services variations from call to call and between messages during a call are typically a few milliseconds, occasionally higher.

This driver requires a 9600-bps modem with a Hayes-compatible command set and control over the modem data terminal ready (DTR) control line. The actual line speed ranges from 1200 bps with USNO to 14,400 bps with NIST. The modem setup string is hard-coded in the driver and may require changes for nonstandard modems or special circumstances.

There are three modes of operation selected by the `mode` keyword in the `server` configuration command. In manual mode (2) the calling program is initiated by setting fudge `flag1`. This can be done manually using `ntpq`, or by a `cron` job. In auto mode (0) `flag1` is set at each poll event. In backup mode (1) `flag1` is set at each poll event, but only if no other synchronization sources are available.

When `flag1` is set, the calling program dials the first number in the list specified by the `phone` command. If the call fails for any reason, the program dials the second number and so on. The phone number is specified by the Hayes ATDT prefix followed by the number itself, including the prefix and long-distance digits and delay code, if necessary. The `flag1` is reset and the calling program terminated if (a) valid clock update has been determined, (b) no more numbers remain in the list, (c) a device fault or timeout occurs or (d) fudge `flag1` is reset manually using `ntpq`.

The driver automatically recognizes the message format of each modem time service. It selects the parsing algorithm depending on the message length. There is some hazard should the message be corrupted. However, the data format is checked carefully and only if all checks succeed is the message accepted. Corrupted lines are discarded without complaint. Once the service is known, the reference identifier for the driver is set to NIST, USNO, PTB or WWVB as appropriate.

The Spectracom radio can be connected via a modem if the radio is configured to send time codes continuously at 1-s intervals. In principle, fudge `flag2` enables port locking, allowing the modem to be shared when not in use by this driver. At least on Solaris with the current NTP I/O routines, this results in lots of ugly error messages.

The `minpoll` and `maxpoll` keywords of the server configuration command can be used to limit the intervals between calls. The recommended settings are 12 (1.1 hours) for `minpoll` and 17 (36 hours) for `maxpoll`. Ordinarily, the poll interval will start at `minpoll` and ramp up to `maxpoll` in a day or two.

* * *

#### US Phone Numbers and Formats

> **Note:** Phone numbers include the entire Hayes modem command, including the `ATDT` and other control codes as may be necessary. For most cases only the `ATDT` may be necessary.

[National Institute of Science and Technology (NIST)](https://www.nist.gov/pml/time-and-frequency-division/time-distribution/automated-computer-time-service-acts)

Phone: (303) 494-4774 (Boulder, CO); (808) 335-4721 (Hawaii)

Data Format:

<code>National Institute of Standards and Technology

Telephone Time Service, Generator 3B

Enter question mark "?" for HELP

MJD YR MO DA H M S ST S UT1 msADV \<OTM>

47999 90-04-18 21:39:15 50 0 +.1 045.0 UTC(NIST) *

47999 90-04-18 21:39:16 50 0 +.1 045.0 UTC(NIST) #

...</code>

`MJD, YR, ST, UT1` and `UTC(NIST)` are not used by this driver. The <code>\<OTM></code> on-time character `*` changes to `#` when the delay correction is valid.

[US Naval Observatory (USNO)](https://www.cnmoc.usff.navy.mil/usno/)

Phone: (202) 762-1594 (Washington, DC); (719) 567-6743 (Colorado Springs, CO)

Data Format (two lines, repeating at one-second intervals)

`jjjjj nnn hhmmss UTC`

`*` on-time character for previous timecode message

`jjjjj` modified Julian day number (not used)

`nnn` day of year

`hhmmss` second of day

[European Phone Numbers and Formats](/documentation/drivers/tf582_4/)

[Spectracom GPS and WWVB Receivers](https://www.orolia.com/)

If a modem is connected to a Spectracom receiver, this driver will call it and retrieve the time in one of two formats, 0 and 2. Ordinarily, the receiver requires a `T` in order to return the timecode. As this driver does not send data via the modem, it must either be configured in continuous mode or be polled by another local driver.

* * *

#### Monitor Data

The received timecode is written as-is to the `clockstats` file along with the Hayes connection and hang-up commands and result codes.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Set by the driver to (one of) `NIST, USNO, PTB`, or `WWVB`.

<code>**flag1 0 | 1**</code>

: Initiate a call if 1. Automatically reset by program.

<code>**flag2 0 | 1**</code>

: Enables port locking if 1, disables if 0 (default).

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.8-series/refclock/)