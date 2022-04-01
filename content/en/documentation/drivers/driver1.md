---
title: "Undisciplined Local Clock"
type: archives
---

Author: David L. Mills (mills@udel.edu)
: Last update: 9-May-2014 08:34 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver1/#synopsis)
*   [Description](/archives/drivers/driver1/#description)
*   [Monitor Data](/archives/drivers/driver1/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver1/#fudge-factors)
*   [Additional Information](/archives/drivers/driver1/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.1._u_</code>
: **Reference ID:** `LOCL`
: **Driver ID:** `LOCAL`

* * *

#### Description

> **NOTE: We recommend against using this driver.** A much more flexible replacement is described on the [Orphan Mode](/archives/4.2.8-series/orphan/) page.


This driver was intended for use in an isolated network where no external source of synchronization such as a radio clock or modem is available. It allows a designated time server to act as a primary server to provide synchronization to other clients on the network. Pick a machine that has a good clock oscillator and configure it with this driver. Set the clock using the best means available, like eyeball-and-wristwatch. Then, point all the other machines at this one or use broadcast mode to distribute time.

Another application for this driver is if a particular server clock is to be used as the clock of last resort when all other normal synchronization sources have gone away. This is especially useful if that server has an ovenized oscillator. For this you would usually, but not necessarily, configure this driver at a stratum greater than any other likely sources of time, such as the default 5 for this driver, to prevent this driver taking over when legitimate sources elsewhere in the network are available. To further protect the Internet infrastructure from accidental or malicious exposure to this driver, the driver is disabled if another source is available and operating.

* * *

#### Monitor Data

No `filegen clockstats` monitor data are produced by this driver.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Specifies the frequency offset calibration factor, in parts per million, with default 0.0.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 5.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `LOCL`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock/)