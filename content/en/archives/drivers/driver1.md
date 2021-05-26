---
title: "Undisciplined Local Clock"
type: archives
---

Author: David L. Mills (mills@udel.edu)  
Last update: 9-May-2014 08:34 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver1/#synopsis)
*   [Description](/archives/drivers/driver1/#description)
*   [Monitor Data](/archives/drivers/driver1/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver1/#fudge-factors)
*   [Additional Information](/archives/drivers/driver1/#additional-information)

* * *

#### Synopsis

Address: 127.127.1._u_  
Reference ID: <tt>LOCL</tt>  
Driver ID: <tt>LOCAL</tt>

* * *

#### Description

{{% alert title="Note" color="warning" %}} 
**We recommend against using this driver.** A much more flexible replacement is described on the [Orphan Mode](/archives/4.2.8-series/orphan) page.
{{% /alert %}}

This driver was intended for use in an isolated network where no external source of synchronization such as a radio clock or modem is available. It allows a designated time server to act as a primary server to provide synchronization to other clients on the network. Pick a machine that has a good clock oscillator and configure it with this driver. Set the clock using the best means available, like eyeball-and-wristwatch. Then, point all the other machines at this one or use broadcast mode to distribute time.

Another application for this driver is if a particular server clock is to be used as the clock of last resort when all other normal synchronization sources have gone away. This is especially useful if that server has an ovenized oscillator. For this you would usually, but not necessarily, configure this driver at a stratum greater than any other likely sources of time, such as the default 5 for this driver, to prevent this driver taking over when legitimate sources elsewhere in the network are available. To further protect the Internet infrastructure from accidental or malicious exposure to this driver, the driver is disabled if another source is available and operating.

* * *

#### Monitor Data

No <tt>filegen clockstats</tt> monitor data are produced by this driver.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Specifies the frequency offset calibration factor, in parts per million, with default 0.0.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 5.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>LOCL</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

</dl>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock)
