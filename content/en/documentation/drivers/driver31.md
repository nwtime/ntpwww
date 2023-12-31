---
title: "Rockwell Jupiter GPS Receiver"
description: "The Rockwell Jupiter GPS Receiver driver supports models of the Rockwell Jupiter GPS receivers that support the Zodiac Binary Protocol."
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver31/#synopsis)
*   [Description](/documentation/drivers/driver31/#description)
*   [Monitor Data](/documentation/drivers/driver31/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver31/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver31/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.31._u_</code>

**Reference ID:** `GPS`

**Driver ID:** `JUPITER`

**Serial Port:** <code>/dev/gps*u*</code>;  9600 baud, 8-bits, no parity.

* * *

#### Description

This driver supports at least some models of the Rockwell Jupiter GPS receivers (Jupiter 11, Jupiter-T); they must at least support the _Zodiac Binary Protocol_.

The driver requires a standard `PPS` interface for the pulse-per-second output from the receiver. The serial data stream alone does not provide precision time stamps, whereas the PPS output is precise down to 40 ns (1 sigma) for the Jupiter 11 and 25 ns (1 sigma) for Jupiter-T according to the documentation. If you do not have the PPS signal available, then you should probably not be using the Jupiter receiver as a time source. This driver requires a `PPS` signal and the time output from Jupiter receivers is not predictable in `NMEA` mode; the reported time can take one second steps.

* * *

#### Monitor Data

The driver always puts a lot of useful information on the `clockstats` file, and when run with debugging can be quite chatty on `stdout`. When first starting to use the driver you should definitely review the information written to the `clockstats` file to verify that the driver is running correctly.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver. Should be left at zero.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `GPS`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Specifies the mobility of the `GPS` receiver: 0 for walking (default), 1 for driving.

<code>**flag3 0 | 1**</code>

: Specifies the `PPS` signal on-time edge: 0 for assert (default), 1 for clear.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

#### Additional Information

The driver was resurrected from a sorry state using the Windows NT port and a Jupiter 11, and has since seen little testing on other platforms. On Windows there exists a barrier, as there is no publicly available `PPSAPI` implementation, at least not to my knowledge. However, there has been one success report using Linux 2.4.20 and PPSkit 2.1.1.

The Jupiter receivers seem to have quite a few names. They are referred to at least as Rockwell receivers, Navman receivers, Zodiac receivers, Conexant receivers and SiRF Technology receivers. Rockwell seems to be the original and most commonly used name and Navman seems to be the current supplier.

##### Configuration

The edge of the `PPS` signal that is on-time can be set with `flag2`. There is currently no way to cause the `PPS` signal to control the kernel `PLL`.

##### Performance

The performance is largely unexplored. I have achieved submillisecond stability using a Jupiter 11, but the poor result is more than likely due to the proprietary `PPSAPI` implementation or Windows itself.

This driver does not handle leap seconds.