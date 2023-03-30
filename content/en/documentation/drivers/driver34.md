---
title: "Ultralink Clock"
description: "The Ultralink Clock driver supports the Ultralink Model 325 RS-232 powered WWVB receiver."
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver34/#synopsis)
*   [Description](/documentation/drivers/driver34/#description)
*   [Model 325 timecode format](/documentation/drivers/driver34/#model-325-timecode-format)
*   [Model 320 timecode format](/documentation/drivers/driver34/#model-320-timecode-format)
*   [Model 33x timecode format](/documentation/drivers/driver34/#model-33x-timecode-format)
*   [Fudge factors](/documentation/drivers/driver34/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.34._u_</code>

**Reference ID:** `WWVB`

**Driver ID:** `ULINK`

**Serial Port:** <code>/dev/wwvb*u*</code>; 9600 bps, 8-bits, no parity

**Features:** none

* * *

#### Description

This driver supports the Ultralink Model 325 (replacement for Model 320) RS-232 powered WWVB receiver.

[//]: # (PDF specs available on http://www.ulio.com)

This driver also supports the Model 320, 330, 331, and 332 decoders in both polled or continous time code mode. Leap second and quality are supported. Most of this code is originally from `refclock_wwvb.c` with thanks. Any mistakes are mine. Any improvements are welcome.

* * *

#### Model 325 timecode format

<code>\<cr>\<lf>RQ_1C00LYYYY+DDDUTCS_HH:MM:SSL+5</code>

: | Value | Description |
| ----- | ----- |
| `RQ` | Signal readability indicator, ranging from R1 to R5 where R1 is unreadable, R5 is best reception |
| `_` | Space |
| `1` | prev. received data bit, values: 0, 1, M, or ? unknown |
| `C` | Signal reception from `C`olorado or `H`awaii |
| `00` | Hours since last WWVB time and flag code update, values 00 to 99 (hopefully always 00) |
| `L` | HEX A5 if receiver is locked to WWVB, Space if not |
| `YYYY` | Year from 2000 to 2099 |
| `+` | `+` if current year is a leap year, else '' |
| `DDD` | current day in the year from 1 to 365/366 |
| `UTC` | timezone (always UTC) |
| `S` | Daylight savings indicator<br> `S`TD<br> `D`ST<br> `O` transition into DST<br> `I` transition out of DST |
| `HH` | UTC hour 0 to 23 |
| `:` | Time delimiter: `:` if synced, space if not |
| `MM` | Minutes of current hour from 0 to 59 |
| `SS` | Seconds of current minute from 0 to 59 |
| `mm` | 10's milliseconds of the current second from 00 to 99 |
| `L` | Leap second pending at end of month: `I`nsert, `D`elete, or space |
| `+5` | UT1 correction in +/- .1 sec increments |

Note that Model 325 reports a very similar output like Model 33X series. The driver for this clock is similar to Model 33X behavior. On a unmodified new ULM325 clock, the polling flag (`flag1 =1`) needs to be set.

* * *

#### Model 320 timecode format

<code>\<cr>\<lf>SQRYYYYDDD+HH:MM:SS.mmLT\<cr></code>

: | Value | Description |
| ----- | ----- |
| `S` | `S`: sync'd in last hour<br> 0-9: hours x 10 since last update<br> else `?` |
| `Q` | Number of correlating timeframes, from 0 to 5 |
| `R` | `R`: reception in progress<br> `N`: Noisy reception<br> '' standby mode |
| `YYYY` | year from 1990 to 2089 |
| `DDD` | current day from 1 to 366<br> `+` if current year is a leap year |
| `HH` | UTC hour 0 to 23 |
| `MM` | Minutes of current hour from 0 to 59 |
| `SS` | Seconds of current minute from 0 to 59 |
| `mm` | 10's milliseconds of the current second from 00 to 99 |
| `L` | Leap second pending at end of month<br> `I`: insert<br> `D` delete |
| `T` | DST to STD transition indicators |

Note that this driver does not do anything with the `T` flag. The M320 also has a `U` command which returns UT1 correction information. It is not used in this driver.

* * *

#### Model 33x timecode format

`S9+D 00 YYYY+DDDUTCS HH:MM:SSl+5`

: | Value | Description |
| ----- | ----- |
| `S` | sync indicator<br> `S` insync<br> `N` not in sync<br> the sync flag is WWVB decoder<br> sync has nothing to do with time being correct |
| `9+` | signal level 0 thru 9+<br> If over 9, indicated as 9 |
| `D` | data bit (fun to watch but useless), space |
| `00` | hours since last good WWVB frame sync space |
| `YYYY` | current year<br> `+` leap year indicator |
| `DDD` | day of year |
| `UTC` | timezone (always UTC) |
| `S` | daylight savings indicator space |
| `HH` | hours : This is the real in-sync indicator where `:` means insync |
| `MM` | minutes<br> `:` in sync<br> `?` NOT in sync |
| `SS` | seconds |
| `L` | leap second flag |
| `+5` | UT1 correction (sign + digit) |

This driver ignores UT1 correction, DST indicator, Leap year, and signal level.

* * *

#### Fudge factors

flag1 polling enable
: `1`=poll 
: `0`=no poll