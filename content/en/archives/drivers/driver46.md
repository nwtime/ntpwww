---
title: "GPSD-NG client driver"
type: archives
---

Last update: 30-Apr-2015 05:53 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver46/#synopsis)
*   [Description](/archives/drivers/driver46/#description)
*   [Naming a Device](/archives/drivers/driver46/#naming-a-device)
*   [The ‘mode’ word](/archives/drivers/driver46/#the-mode-word)
*   [Syslog flood throttle](/archives/drivers/driver46/#syslog-flood-throttle)
*   [PPS secondary clock unit](/archives/drivers/driver46/#pps-secondary-clock-unit)
*   [Clockstats](/archives/drivers/driver46/#clockstats)
*   [Fudge Factors](/archives/drivers/driver46/#fudge-factors)
*   [Additional Information](/archives/drivers/driver46/#additional-information)

* * *

#### Synopsis

Address: `127.127.46._u_`  
Reference ID: <tt>GPSD</tt>  
Driver ID: <tt>GPSD_JSON</tt>  
Serial Port: <tt>/dev/gps_u_</tt> as symlink to the true device (not used directly; see below)  
Features:

* * *

#### Description

This driver is a client driver to the _GPSD_ daemon, which over the time became increasingly popular for UN*Xish platforms. _GPSD_ can manage several devices in parallel, aggregate information, and acts as a data hub for client applications. _GPSD_ can also auto-detect and handle PPS hardware signals on serial ports. Have a look at [the _GPSD_ project page](https://gpsd.gitlab.io/gpsd/index.html).

**It is important to understand that this driver works best using a GPS device with PPS support.**

The GPSD-NG protocol is text based, using JSON notation to transfer records in form of JSON objects. The driver uses a TCP/IP connection to <tt>localhost:gpsd</tt> to connect to the daemon and then requests the GPS device <tt>/dev/gps_u_</tt> to be watched. Different clock units use different devices, and GPSD is able to give only the relevant information to a clock instance.

This driver does not expect _GPSD_ to be running or the clock device to be present _a priori_; it will try to re-establish a lost or hitherto unsuccessful connection and will wait for device to come up in _GPSD._ There is an initial 10 seconds delay between a connection loss or failed attempt and the next reconnect attempt; this makes sure that there is no thrashing on the network layer. If the connection fails again, an exponential back off is used with an upper limit of approximately 10 minutes.

The overall accuracy depends on the receiver used. The driver uses the error estimations (95% probability limits) provided by _GPSD_ to set the clock precision dynamically according to these readings.

The driver needs the VERSION, TPV, PPS, WATCH and TOFF objects of the _GPSD_ protocol. (Others are quietly ignored.) The driver can operate without the TOFF objects, which are available with the _protocol_ version 3.10 and above. (Not to be confused with the _release_ version of _GPSD_!) Running without TOFF objects has a negative impact on the jitter and offset of the serial timing information; if possible, a version of _GPSD_ with support for TOFF objects should be used.

The acronym <u>STI</u> is used here as a synonym for _serial time information_ from the data channel of the receiver, no matter what objects were used to obtain it.

* * *

#### Naming a Device

The _GPSD_ driver uses the same device name as the NMEA driver, namely <tt>/dev/gps_u_</tt>. There is a simple reason for that: While the NMEA driver and the GPSD driver can be active at the same time for different devices, they cannot access the same device at a time. Having the same name helps on that. It also eases migration from using NMEA directly to using GPSD, as no new links etc need to be created.

_GPSD_ is normally started with the device name to access; it can also be instructed by hot-plug scripts to add or remove devices from its device pool. Luckily, the symlinks used by the NMEA driver are happily accepted and used by _GPSD_; this makes it possible to use the symlink names as device identification. This makes the migration from the built-in NMEA driver a bit easier.

{{% alert title="Note" color="warning" %}} 
_GPSD_ (as of version 3.10) cannot use kernel mode PPS on devices that are hot-plugged. This would require to attach the PPS line discipline to the character special file, which is not possible when running with root privileges already dropped. This is not likely to change in the future.
{{% /alert %}}

#### The 'mode' word

A few operation modes can be selected with the mode word.

**The Mode Word**

| Bits | Value | Description |
| ----- | ----- | ----- |
| 0-1 | `0` | STI only operation. This mode is affected by the timing stability of whatever protocol is used between the GPS device and GPSD.  Running on STI only is not recommended in general. Possible use cases include:<br> - The receiver does not provide a PPS signal.<br> - The receiver _does_ provide a PPS signal and the secondary PPS unit is used.<br> - The receiver has a stable serial timing and a proper fudge can be established.<br> - You have other time sources available and want to establish a useful fudge value for <tt>time2</tt>. |
| | `1` | Strict operation. This mode needs a valid PPS and a valid STI to combine the absolute time from the STI with the time stamp from the PPS record. Does not feed clock samples if no valid PPS+STI pair is available. This type of operation results in an ordinary clock with a very low jitter as long as the PPS data is available, but the clock fails once PPS drops out. This mode is a possible choice for receivers that provide a PPS signal most of the time but have an unstable serial timing that cannot be fudge-compensated. |
| | `2` | Automatic mode. Tries to operate in strict mode unless it fails to process valid samples for some time, currently 120s. Then it reverts to STI-only operation until the PPS is stable again for 40s, when strict mode is engaged again. **Important Notice: This is an experimental feature!**  Switching between strict and STI-only mode will cause changes in offset and jitter. Use this mode only if STI-only works fairly well with your setup, or if you expect longer dropouts of the PPS signal and prefer to use STI alone over not getting synchronised at all. |
| | `3` | reserved for future extension, do not use |
| 2-31 | | reserved for future extension, do not use |

* * *

#### Syslog flood throttle

This driver can create a lot of syslog messages when things go wrong, and cluttering the log files is frowned upon. So we attempt to log persistent or recurring errors only once per hour. On the other hand, when tracking a problem the syslog flood throttle can get into the way.

Therefore, fudge _flag3_ can be used to _disable_ the flood throttle at any time; the throttle is engaged by default. Running with the syslog flood throttle disabled for lengthy time is not recommended unless the log files are closely monitored.

* * *

#### PPS secondary clock unit

Units with numbers ≥128 act as secondary clock unit for the primary clock unit (u mod 128). A secondary unit processes only the PPS data from _GPSD_ and needs the corresponding master unit to work<sup>[1](#myfootnote1)</sup>. Use the `noselect` keyword on the primary unit if you are not interested in its data.

The secondary unit employs the usual precautions before feeding clock samples:

*   The system must be already in a synchronised state.
*   The system offset must be less than 400ms absolute.
*   The phase adjustment from the PPS signal must also be less than 400ms absolute.

If fudge flag <tt>flag1</tt> is set for the secondary unit, the unit asserts the PPS flag on the clock as long as PPS data is available. This makes the unit eligible as PPS peer and should only be used if the GPS receiver can be trusted for the quality of its PPS signal<sup>[2](#myfootnote2)</sup>. The PPS flag gets cleared if no PPS records can be aquired for some time. The unit also flushes the sample buffer at this point to avoid the use of stale PPS data.

{{% alert title="Attention" color="warning" %}} 
This unit uses its own PPS fudge value which must be set as fudge <tt>time1</tt>. Only the fudge values <tt>time1</tt> and <tt>flag1</tt> have an impact on secondary units.
{{% /alert %}}

* * *

#### Clockstats

If flag4 is set when the driver is polled, a clockstats record is written for the primary clock unit. (The secondary PPS unit does not provide clock stats on its own.) The first 3 fields are the normal date, time, and IP address common to all clockstats records.

**The Clockstats Line**

| Field | Description |
| ----- | ----- |
| `1` | Date as day number since NTP epoch. |
| `2` | Time as seconds since midnight. |
| `3` | (Pseudo-) IP address of clock unit. |
| `4` | Number of received known JSON records since last poll. The driver knows about TPV, PPS, TOFF, VERSION, and WATCH records; others are silently ignored. |
| `5` | Bad replies since last poll. A record is considered malformed or a bad reply when it is missing vital fields or the fields contain malformed data that cannot be parsed. |
| `6` | Number of sample cycles since last poll that were discarded because there was no GPS fix. This is effectively the number of TPV records with a fix value < 2 or without a time stamp. |
| `7` | Number of serial time information records (TPV or TOFF, depending on the GPSD version) received since last poll. |
| `8` | Number of serial time information records used for clock samples since the last poll. |
| `9` | Number of PPS records received since the last poll. |
| `10` | Number of PPS records used for clock samples on the secondary channel since the last poll. |

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the PPS time offset calibration factor, in seconds and fraction, with default 0.0.

<dt><a name="fudgetime2"><tt>time2 _time_</tt></a></dt>

_[Primary Unit]_ Specifies the TPV/TIME time offset calibration factor, in seconds and fraction, with default 0.0.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>GPSD</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

_[Secondary Unit]_ When set, flags the secondary clock unit as a potential PPS peer as long as good PPS data is available.

<dt><tt>flag2 0 | 1</tt></dt>

_[Primary Unit]_ When set, disables the processing of incoming PPS records. Intended as an aide to test the effects of a PPS dropout when using automatic mode (mode 2).

<dt><tt>flag3 0 | 1</tt></dt>

_[Primary Unit]_ If set, disables the log throttle. Useful when tracking problems in the interaction between _GPSD_ and _NTPD_, since now all error events are logged. Persistent/recurrent errors can easily fill up the log, so this should only be enabled during bug hunts.

<dt><tt>flag4 0 | 1</tt></dt>

_[Primary Unit]_ If set, write a clock stats line on every poll cycle.

</dl>

* * *

#### Additional Information

<a name="myfootnote1">1</a>  Data transmission and decoding is done only once by the primary unit. The decoded data is then processed independently in both clock units. This avoids double transmission over two sockets and decoding the same data twice, but the primary unit is always needed as a downside of this approach.

<a name="myfootnote2">2</a>  The clock driver suppresses the processing PPS records when the TPV/TIME data indicates the receiver has no fix. It can also deal with situations where the PPS signal is not delivered to _GPSD_. But once it is available, it is also processed and used to create samples. If a receiver cannot be trusted for the precision of its PPS signal, it should not be used to create a possible PPS peer: These get extra clout and can effectively become the sole source of input for the control loop. You do not want to use sloppy data for that.

[Reference Clock Drivers](/archives/4.2.8-series/refclock)
