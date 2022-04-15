---
title: "JJY Receivers"
type: archives
---
       
[JAPANESE](/documentation/drivers/driver40-ja/)

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver40/#synopsis)
*   [Description](/documentation/drivers/driver40/#description)
*   [Mode-1](/documentation/drivers/driver40/#mode-1)
*   [Mode-2](/documentation/drivers/driver40/#mode-2)
*   [Mode-3](/documentation/drivers/driver40/#mode-3)
*   [Mode-4](/documentation/drivers/driver40/#mode-4)
*   [Mode-5](/documentation/drivers/driver40/#mode-5)
*   [Mode-6](/documentation/drivers/driver40/#mode-6)
*   [Mode-100](/documentation/drivers/driver40/#mode-100)
*   [Monitor Data](/documentation/drivers/driver40/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver40/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.40._u_</code>
: **Reference ID:** `JJY`
: **Driver ID:** `JJY`
: **Serial Port:** <code>/dev/jjy*u*</code>; See corresponding receiver

* * *

#### Description

This driver supports the following JJY receivers and the GPS clock sold in Japan, and the time service through a telephone line.

| Model | Mode | Language |
| ----- | ----- | ----- |
| [Tristate Ltd.   TS-JJY01, TS-JJY02](http://www.tristate.ne.jp/) | [1](/documentation/drivers/driver40/#mode-1) | Japanese only |
| [C-DEX Co.,Ltd.   JST2000](http://www.c-dex.co.jp/) | [2](/documentation/drivers/driver40/#mode-2) | Japanese only |
| Echo Keisokuki Co.,Ltd.   LT-2000 | [3](/documentation/drivers/driver40/#mode-3) | |
| [CITIZEN T.I.C. CO.,LTD.   JJY-200](https://tic.citizen.co.jp/english/index.html) | [4](/documentation/drivers/driver40/#mode-4) | Japanese only |
| [Tristate Ltd.   TS-GPSclock-01](http://www.tristate.ne.jp/) | [5](/documentation/drivers/driver40/#mode-5) | Japanese only |
| [SEIKO TIME SYSTEMS INC.   TDC-300](https://www.seiko-sts.co.jp/) | [6](/documentation/drivers/driver40/#mode-6) | English and Japanese |
| [Telephone JJY](https://jjy.nict.go.jp/) | [100](/documentation/drivers/driver40/#mode-100) | English and Japanese |

* * *

#### Mode-1

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 1`

`fudge   127.127.40.X   time1 0.NNN   flag1 0|1   flag2 0|1   time2 H`

`time1` may specify a constant to be added to the time offset for the time from the receiver, a fixed-point decimal number in seconds. You may specify the time offset from several tens of ms (0.0NN seconds) to a hundred and several tens of ms (0.1NN seconds) for this clock.

`time2` may specify a grace period in hours after the adjusted reply of the `STUS` command stopped coming.  This hours is effective when both `flag1` and `flag2` are set to 1.

`flag1` has no effect for time synchronization unless `flag2` is set to 1.  When `flag1` is set to 1, status commands are issued before `DATE` and `STIM` commands, and write a response text into the `clockstats` file.

**fudge flag1**

| Value | Description |
| ----- | ----- |
| `0` (Default) | DCST and STUS commands are not issued |
| `1` | DCST and STUS commands are issued |

`flag2` enables the time synchronization only when the reply of the STUS is adjusted. When this functionality is used, `flag1` must also be set to 1.

**fudge flag2**

| Value | Description |
| ----- | ----- |
| `0` (Default) | Always |
| `1` | adjusted only |

**Interface**

RS-232C, 9600 BPS, 8-bits, no parity, 1 stop bit

**Time code format**

| Command | Reply |
| ----- | ----- |
| `dcst{CR}{LF}` | `valid{CR}{LF}` \| <code>invalid{CR}{LF}</code> |
| `stus{CR}{LF}` | `adjusted{CR}{LF}` \| <code>unadjusted{CR}{LF}</code> |
| `time{CR}{LF}` | `HH:MM:SS{CR}{LF}` |
| `date{CR}{LF}` | `YYYY/MM/DD WWW{CR}{LF}` |
| `stim{CR}{LF}` | `HH:MM:SS{CR}{LF}` |

The date and time are requested separately. The time is requested before and after the date request to check uncertainty of the date whether it's before or after midnight.

* * *

#### Mode 2

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 2`

`fudge   127.127.40.X   time1 0.NNN`

**Interface**

RS-232C, 9600 BPS, 8-bits, no parity, 1 stop bit

**Time code format**

|Command | Reply |
| ----- | ----- |
| `{ENQ}1J{ETX}` | `{STX}JYYMMDDWHHMMSSS{ETX}` |

* * *

#### Mode-3

Echo Keisokuki was dissolved. Some business of the company was taken over by FreqTime Co., Ltd. in July, 2015.

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 3`

`fudge   127.127.40.X   time1 0.NNN`

**Interface**

RS-232C, 9600 BPS, 8-bits, no parity, 1 stop bit

**Time code format**

|Command | Reply |
| ----- | ----- |
| `C` | (Mode 2 : Continuous) |
| (Every second before 0.5 second) | `YYMMDDWHHMMSS{ST1}{ST2}{ST3}{ST4}{CR}` |
| `#` | (Mode 1 : Request&Send) |

* * *

#### Mode-4

The JJY-200 became end-of-sales in 2013.

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 4`

`fudge   127.127.40.X   time1 0.NNN`

**Interface**

RS-232C, 4800 BPS, 8-bits, no parity, 1 stop bit

**Time code format**

|Command | Reply |
| ----- | ----- |
| (Every second) | `'XX YY/MM/DD W HH:MM:SS{CR}` |

* * *

#### Mode-5

This driver supports the Tristate TS-GPSclock-01 in command/response mode, though it is a GPS clock, not JJY radio clock. Using the menus and the onboard switches, the TS-GPSclock-01 should be set to command/response mode and JST time zone.

Besides this driver (Type 40), [the generic NMEA GPS driver (Type 20)](/documentation/drivers/driver20/) supports the TS-GPSclock-01 in NMEA mode.

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 5`

`fudge   127.127.40.X   time1 0.NNN   flag1 0|1`

`time1` may specify a constant to be added to the time offset for the time from the receiver, a fixed-point decimal number in seconds.

`flag1` has no effect for time synchronization. When `flag1` is set to 1, the status command is issued before the DATE and TIME commands and a response text is written to a `clockstats` file.

**fudge flag1**

| Value | Description |
| ----- | ----- |
| `0` (Default) | STUS command is not issued |
| `1` | STUS command is issued |

**Interface**

USB (<code>/dev/ttyACM*0*</code>)

**Time code format**

|Command | Reply |
| ----- | ----- |
| `stus{CR}{LF}` | `*R{CR}{LF}\|*G{CR}{LF}\|*U{CR}{LF}\|+U{CR}{LF}` |
| `time{CR}{LF}` | `HH:MM:SS{CR}{LF}` |
| `date{CR}{LF}` | `YYYY/MM/DD{CR}{LF}` |

The date and time are requested separately. The time is requested before and after the date request to check uncertainty of the date whether it's before or after midnight.

* * *

#### Mode-6

The TDC-300 must be set to the type 3 data format using the front panel menu display and the switches.

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode 6`

`fudge   127.127.40.X   time1 0.NNN`

**Interface**

RS-232C, 2400 BPS, 8-bits, no parity, 1 stop bit

**Time code format**

|Command | Reply |
| ----- | ----- |
| | `{STX}YYMMDDWHHMMSS{ETX}` |
(5 to 10 ms before second) | `{STX}{xE5}{ETX}` |

* * *

#### Mode-100

The telephone JJY is the time service through a public telephone line.

The service is provided by the National Institute of Information and Communications Technology in Japan.

> **Attention:** This mode, the telephone JJY, can not be used with `refclock_acts` [(type 18)](/documentation/drivers/driver18/) at the same time. Because the `phone` statement in the ntp configuration file is not involved with the `server` statement, both the `refclock_acts` (type 18) and this `refclock_jjy` (type 40, mode 100 to 180) can not recognize the appropriate `phone` statement among the `phone` statements.

**NTP configuration (ntp.conf)**

`server   127.127.40.X   mode (100, 101 to 180)   minpoll N`

When `mode` 100 is specified, this driver does not issue the loopback command in order to measure the delay, and the delay of the telephone line and the system processing is not adjusted.

When `mode` 101 to 180 is specified, this driver issues the loopback command and measures the delay of the telephone line and the system processing through the Telphone JJY loopback circuit.

The round trip time through the Telphone JJY loopback circuit is measured 5 times, and each delay time is greater than 700 ms, that delay time is ignored during average delay time calculation. Also, if the valid delay time ( <= 700 ms.) is measured more than 3 times, the maximum delay time among the valid delay times is ignored, and if the valid delay time is measured more than 4 times, the minimum delay time among them is ignored, like marking/grading sports judgment.

The adjustment time is calculated by the formula `multiply (the measured round trip time) by ( ( the mode number ) - 100) %`, and the adjustment delay time is added to the syncronizing time.
    
If you choose the automatic delay adjustment, in other words, the `mode` 101 to 180 is specifed, the recommended `mode` number is 145 to 165.

The default polling interval 6 (64 seconds) is too short for this mode. The `minpoll` should be set to greater than or equal to 8 (256 seconds, about 4 minutes).

The interval time is given the value in second power of 2. The `minpoll` value 12 is 4096 seconds interval (about 1 hour), 14 is 16384 seconds interval (about 4.5 hours), 16 is 65536 seconds (about 18 hours), respectively.

`fudge   127.127.40.X   flag1 0|1   flag2 0|1   flag3 0|1   flag4 0|1`

`time1` may specify a constant to be added to the time offset for the time from the receiver, a fixed-point decimal number in seconds.

When `mode` 100 is specified, `time1` may be specified in order to adjust the time offset.

When `mode` 101 to 180 is specified, `time1` should not be specified because this driver adds some percentage of the measured loopback delay, depending on the value of the `mode` number.

`flag1` is the modem dialing type.

**fudge flag1**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | Tone | `ATDWTnn...nn` |
| `1` | Pulse | `ATDWPnn...nn` |

`flag2` is the modem error correction type.

**fudge flag2**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | Normal | `AT\N0` |
| `1` | Auto V42, MNP, Normal | `AT\N3` |

`flag3` is the modem speaker switch.

**fudge flag3**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | Off | `ATM0Ln` |
| `1` | On | `ATM2Ln` |

`flag4` is the modem speaker volume.

**fudge flag4**

| Value | Description | AT Command |
| ----- | ----- | ----- |
| `0` (Default) | Low | `ATMnL1`
| `1` | Middle | `ATMnL2`

**phone 042NNNNNNN**

The phone number is available at https://jjy.nict.go.jp/.

The number of digits of the phone number is checked. If the international access number and the country number are added in order to call from outside of Japan, the number of digits is over the limit.

The first 2 or 3 digits are checked. The emergency service number and the special service number in Japan are not allowed.

When calling from an extension line, the number for an outside line should be prefix `0,` (zero comma). The prefix is also checked, and no other outside access number is allowed.

**Interface**

RS-232C or USB, 2400 BPS, 8-bits, no parity, 1 stop bit

**Modem control commands:**

`ATE0Q0V1, ATMnLn, AT&K4, AT+MS=V22B, AT%C0, AT\Nn, ATH1, ATDWxnn...nn`
`+++, ATH0`

**Time code format**

| Prompt | Command | Reply |
| ----- | ----- | ----- |
| `Name{SP}?{SP}` | `TJJY{CR}` | Welcome messages |
| `>` | `LOOP{CR}` | Switch to the loopback circuit |
| | `(One char.)` | `(One char.)` |
| | `COM{CR}` | Exit from the loopback circuit |
| `>` | `TIME{CR}` | `HHMMSS{CR}HHMMSS{CR}HHMMSS{CR}` 3 times on second |
| `>` | `4DATE{CR}` | `YYYYMMDD{CR}` |
| `>` | `LEAPSEC{CR}` | `{SP}0{CR} \| +1{CR} \| -1{CR}` |
| `>` | `BYE{CR}` | Sayounara messages |

The date and time are requested separately. The time is requested before and after the date request to check uncertainty of the date whether it's before or after midnight.

The leap second is not handled, and only written in the `clockstats` file as information.

The JJY is the radio station which transmits the JST (Japan Standard Time) in long wave radio. The station JJY is operated by the National Institute of Information and Communications Technology. An operating announcement and some information are available from [http://www.nict.go.jp/](http://www.nict.go.jp/) (English and Japanese) and https://jjy.nict.go.jp/ (English and Japanese).

The user is expected to provide a symbolic link to an available serial port device. This is typically performed by a command such as:

`ln -s /dev/ttyS0 /dev/jjy0`

Using an RS-232C to USB converter cable, the clock or a modem can be connected to a USB port instead of a serial port. In this case, the typical symbolic link command is as follows;

`ln -s /dev/ttyUSB0 /dev/jjy0`

Windows NT does not support symbolic links to device files. <code>COM*X*</code> is the unit used by the driver, based on the refclock unit number, where unit 1 corresponds to `COM1` and unit 3 corresponds to `COM3`.

* * *

#### Monitor Data

The driver writes sent and received data to/from the JJY receivers, GPS clock, and the modem into the `clockstats` file.

`statsdir /var/log/ntpd/  
filegen clockstats file clockstats type day enable`

**Mark of the clockstats record**

| Data | Meaning |
| ----- | ----- |
| JJY | Information message (This refclock starts or stops.) |
| `-->` |  Sent data |
| `<--` | Received data |
| `---` | Information message |
| `===` | Information message (Start of each polling, and sync. time.) |
| `-W-` | Warning message |
| `-X-` | Error message |

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `JJY`.

<code>**flag1 0 | 1**</code>

: See corresponding receiver.

<code>**flag2 0 | 1**</code>

: See corresponding receiver.

<code>**flag3 0 | 1**</code>

: See corresponding receiver.

<code>**flag4 0 | 1**</code>

: See corresponding receiver.