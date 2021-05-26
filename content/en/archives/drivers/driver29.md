
---
title: "Trimble Palisade and Thunderbolt Receivers"
type: archives
---

Last update: 13-Sep-2019 08:07 UTC

* * *

![gif](/archives/pic/driver29.gif)

![jpg](/archives/pic/thunderbolt.jpg)

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver29/#synopsis)
*   [Description](/archives/drivers/driver29/#description)
*   [Operating System Compatibility](/archives/drivers/driver29/#operating-system-compatibility)
*   [GPS Receiver](/archives/drivers/driver29/#gps-receiver)
*   [GPS Installation](/archives/drivers/driver29/#gps-installation)
*   [O/S Serial Port Configuration](/archives/drivers/driver29/#os-serial-port-configuration)
*   [NTP Configuration](/archives/drivers/driver29/#ntp-configuration)
*   [Time Transfer and Polling](/archives/drivers/driver29/#time-transfer-and-polling)
*   [Run NTP in Debugging Mode](/archives/drivers/driver29/#run-ntp-in-debugging-mode)
*   [Event Logging](/archives/drivers/driver29/#event-logging)
*   [Fudge Factors](/archives/drivers/driver29/#fudge-factors)
*   [Mode Parameter](/archives/drivers/driver29/#mode-parameter)
*   [DEFINEs](/archives/drivers/driver29/#defines)
*   [Data Format](/archives/drivers/driver29/#data-format)
*   [Pinouts](/archives/drivers/driver29/#pinouts)
*   [Notes on the Thunderbolt Receiver’s Firmware](/archives/drivers/driver29/#notes-on-the-thunderbolt-receivers-firmware)

* * *

#### Synopsis

Address: **127.127.29._u_**

Reference ID: **GPS**

Driver ID: **GPS_PALISADE**

Serial Port: **`/dev/palisade_u_`**

Serial I/O: **9600 baud, 8-bits, 1-stop, odd parity**

Serial I/O (Thunderbolt): **9600 baud, 8-bits, 1-stop, no parity**

Serial I/O (Copernicus II): **38400 baud, 8-bits, 1-stop, no parity**

* * *

#### Description

The **refclock_palisade** driver supports [Trimble](https://timing.trimble.com/) Navigation's Palisade Smart Antenna GPS receiver.  

[//]: # (24/5/2021 DL: they seem to be out of the GPS business in favor of GNSS?)
[//]: # (Additional software and information about the Palisade GPS is available from: http://www.trimble.com/oem/ntp.)
[//]: # (Latest NTP driver source, executables and documentation is maintained at: ftp://ftp.trimble.com/pub/ntp].)

This documentation describes version 7.12 of the GPS Firmware and version 2.46 (July 15, 1999) and later, of the driver source.

This documentation describes version 1 of the Thunderbolt Receiver Firmware, no tests have been made on further firmwares, please read [Notes on the Thunderbolt Receiver's Firmware](/archives/drivers/driver29/#notes-on-the-thunderbolt-receivers-firmware) for more information.

This driver also supports the following receivers:

* Endrun Technologies Praecis NTP server with GPS
 
* Trimble Acutime Gold smart antenna
 
* Trimble Resolution family
 
* Trimble ACE III
 
* Trimble Copernicus II

* * *

#### Operating System Compatibility

The Palisade driver has been tested on the following software and hardware platforms:  

| Platform | Operating System | NTP Sources | Accuracy |
| ----- | ----- | ----- | ----- |
| i386 (PC) | Linux | NTP Distribution | 10 us |
| i386 (PC) | Windows NT | | 1 ms |
| SUN | Solaris 2.x | NTP Distribution | 50 us |
| Hewlett-Packard | HPUX 9, 10, 11 | | 50 us |
| Various | FreeBSD | NTP Distribution | 20 us |

{{% alert title="Attention" color="warning" %}} 
Other receiver types have not being tested on the previous software and hardware platforms.
{{% /alert %}}

* * *

#### GPS Receiver

The Palisade GPS receiver is an 8-channel smart antenna, housing the GPS receiver, antenna and interface in a single unit, and is designed for rooftop deployment in static timing applications.

Palisade generates a PPS synchronized to UTC within +/- 100 ns.  The Palisade's external event input with 40 nanosecond resolution is utilized by the Palisade NTP driver for asynchronous precision time transfer.

No user initialization of the receiver is required. This driver is compatible with the following versions of Palisade:  

| Version | Event Input | Trimble Part Number |
| ----- | ----- | ----- |
| 7.02 | No | 26664-00 |
| 7.02E | Yes | 26664-10 |
| 7.12 | Yes | 38158-00 |


{{% alert title="Note" color="warning" %}} 
When using Palisade 26664-00, you must set fudge flag2 to 1 in **ntp.conf**. See [configuration](/archives/drivers/driver29/#ntp-configuration).
{{% /alert %}}

* * *

#### GPS Installation

A location with unobstructed view of the horizon is recommended. Palisade is designed to be securely mounted atop standard 3/4 inch threaded pipe.

The 12 conductor (dia. 10 mm)  power and I/O cable must be routed from the rooftop site to the NTP server and properly strain relieved.

**GPS Connection**

The Palisade is equipped with dual (A & B) RS-422 serial interfaces and a differential TTL PPS output. An RS-232 / RS-422 Interface Module is supplied with the Palisade NTP Synchronization Kit. Palisade port A must be connected to the NTP host server. Maximum antenna cable length is 500 meters. See the [pinouts](/archives/drivers/driver29/#pinouts) table for detailed connection Information.

Palisade's port B provides a TSIP (Trimble Standard Interface Protocol) interface for diagnostics, configuration, and monitoring. Port B and the PPS output are not currently used by the Palisade NTP reference clock driver.  

* * *

#### O/S Serial Port Configuration

The driver attempts to open the device `/dev/palisade_u_` where `_u_` is the NTP refclock unit number as defined by the LSB of the refclock address.  Valid refclock unit numbers are 0 - 3.

The user is expected to provide a symbolic link to an available serial port device.  This is typically performed by a command such as:

`> ln -s /dev/ttyS0 /dev/palisade0`

Windows NT does not support symbolic links to device files. COM**x**: is used by the driver, based on the refclock unit number, where unit 1 corresponds to COM**1**: and unit 3 corresponds to COM3.

* * *

#### NTP Configuration

**Palisade NTP configuration file <tt>ntp.conf</tt> with event polling:**  
<pre><tt>#-----------------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 # Trimble Palisade GPS Refclock Unit #0</tt>  
<tt>peer terrapin.csc.ncsu.edu # internet server</tt>  
<tt># Drift file for expedient re-synchronization after downtime or reboot.</tt>  
<tt>driftfile /etc/ntp.drift</tt>  
<tt>#----------------------------------------------------------------------</tt></pre>

Configuration without event polling:  
<pre><tt>#------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 # Trimble Palisade GPS (Stratum 1).</tt>  
<tt># Set packet delay</tt>  
<tt>[fudge 127.127.29.0 time1 0.020](#time1)</tt>  
<tt># and set flag2 to turn off event polling.</tt>  
<tt>[fudge 127.127.29.0 flag2 1](#flag2)</tt>  
<tt>#-------------------------------------------------------</tt></pre>  

**Thunderbolt NTP Configuration file**

Configuration without event polling:  
<pre><tt>#---------------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 mode 2 # Trimble Thunderbolt GPS (Stratum 1).</tt>  
<tt># Set packet delay</tt>  
<tt>[fudge 127.127.29.0 time1 0.020](#time1)</tt>  
<tt># and set flag2 to turn off event polling.</tt>  
<tt>[fudge 127.127.29.0 flag2 1](#flag2)</tt>  
<tt>#----------------------------------------------------------------</tt></pre>  

**Resolution NTP Configuration file**

Configuration without event polling:  
<pre><tt>#-----------------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 mode 5 # Trimble Resolution GPS (Stratum 1).</tt>  
<tt># Set packet delay</tt>  
<tt>[fudge 127.127.29.0 time1 0.410](#time1)</tt>  
<tt># and set flag2 to turn off event polling.</tt>  
<tt>[fudge 127.127.29.0 flag2 1](#flag2)</tt>  
<tt>#------------------------------------------------------------------</tt></pre>  

**ACE III NTP Configuration file**

Configuration with event polling:  
<pre><tt>#-------------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 mode 6 # Trimble ACE III GPS (Stratum 1).</tt>  
<tt># Set packet delay</tt>  
<tt>[fudge 127.127.29.0 time1 0.720](#time1)</tt>  
<tt>#-------------------------------------------------------------</tt></pre>  

**Copernicus II NTP Configuration file**

Configuration without event polling:  
<pre><tt>#-----------------------------------------------------------------</tt>  
<tt># The Primary reference</tt>  
<tt>server 127.127.29.0 mode 7 # Trimble Copernicus II GPS (Stratum 1).</tt>  
<tt># Set packet delay</tt>  
<tt>[fudge 127.127.29.0 time1 0.240](#time1)</tt>  
<tt># and set flag2 to turn off event polling.</tt>  
<tt>[fudge 127.127.29.0 flag2 1](#flag2)</tt>  
<tt>#-------------------------------------------------------------------</tt></pre>  

Currently the Thunderbolt mode doesn't support event polling, the reasons are explained in the [Notes on the Thunderbolt Receiver's Firmware](/archives/drivers/driver29/#notes-on-the-thunderbolt-receivers-firmware) section. The Resolution and Copernicus II modes require event polling to be disabled whereas the ACE III requires polling to be enabled.

* * *

#### Time Transfer and Polling

Time transfer to the NTP host is performed via the Palisade's comprehensive time packet output. The time packets are output once per second, and whenever an event timestamp is requested.

The driver requests an event time stamp at the end of each polling interval, by pulsing the RTS (request to send) line on the serial port. The Palisade GPS responds with a time stamped event packet.

Time stamps are reported by the Palisade with respect to UTC time. The GPS receiver must download UTC offset information from GPS satellites. After an initial UTC download, the receiver will always start with correct UTC offset information.  

* * *

#### Run NTP in Debugging Mode

The following procedure is recommended for installing and testing a Palisade NTP driver:

1.  Perform initial checkout procedures. Place the GPS receiver outdoors; with clear view of the sky. Allow the receiver to obtain an UTC almanac.
2.  Verify presence of timing packets by observing the 1 Hz (PPS) led on the interface module. It should flash once per second.
3.  Connect Palisade's port A to the NTP host.
4.  Configure NTP and the serial I/O port on the host system.
5.  Initially use <tt>fudge flag2</tt> in **[ntp.conf](#ntp-configuration),** to disable event polling.
6.  Run NTP in debug mode (-d -d), to observe Palisade_receive events.
7.  The driver reports the [tracking status of the receiver](#data-format). Make sure it is tracking several satellites.
8.  Remove fudge flag2 and restart **ntpd** in debug mode to observe palisade_receive events.
9.  If event polling fails, verify the [connections](#pinouts) and that the host hardware supports RTS control.

* * *

#### Event Logging

System and Event log entries are generated by NTP to report significant system events. Administrators should monitor the system log to observe NTP error messages. Log entries generated by the Palisade NTP reference clock driver will be of the form:

<pre> > Nov 14 16:16:21 terrapin ntpd[1127]: Palisade #0: _message_</pre>

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the time offset calibration factor, in seconds and fraction, with default 0.0. If event capture is not used, time1 should be set to 20 milliseconds to correct serial line and operating system delays incurred in capturing time stamps from the synchronous packets.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, **GPS**.

<dt><tt>flag2 0 | 1</tt></dt>

When set to 1, driver does not use hardware event capture. The synchronous packet output by the receiver at the beginning of each second is time stamped by the driver. If triggering the event pulse fails, the driver falls back to this mode automatically.

* * *

## Mode Parameter

<dt><tt>mode _number_</tt></dt>

The mode parameter to the server command specifies the specific hardware this driver is for. The default is 0 for a normal Trimble Palisade. The other options are:

**1** for an **Endrun Praecis** in Trimble emulation mode
 
**2** for the **Trimble Thunderbolt** GPS Disciplined Clock Receiver
 
**3** for the **Acutime Gold** smart antenna
 
**5** for **Trimble Resolution** devices
 
**6** for the **Trimble ACE III** board
 
**7** for the **Trimble Copernicus II** device

* * *

#### DEFINEs

The following constants are defined in the driver source code. These defines may be modified to improve performance or adapt to new operating systems.  

| Label | Definition | Default Value |
| ----- | ----- | ----- |
| DEVICE | The serial port device to be used by the driver | `/dev/palisade_u_` |
| PRECISION | Accuracy of time transfer | 1 microsecond |
| SPEED232 | Host RS-232 baud rate | B9600 |
| SPEED232COP | Host RS-232 baud rate (Copernicus II mode) | B38400 |
| TRMB_MINPOLL | Minimum polling interval | 5 (32 seconds) |
| TRMB_MAXPOLL | Maximum interval between polls | 7 (128 seconds) |

* * *

#### Data Format

Palisade port A can output two synchronous time packets. The NTP driver can use either packet for synchronization. Packets are formatted as follows:

**Packet 8F-AD (Primary NTP Packet)**

| Byte | Item | Type | Meaning
| ----- | ----- | ----- | ----- |
| 0 | Sub-Packet ID | BYTE | Subcode 0xAD |
| 1 - 2 | Event Count | INTEGER | External event count recorded (0 = PPS) |
| 3 - 10 | Fractional Second | DOUBLE | Time elapsed in current second (s) |
| 11 | Hour | BYTE | Hour (0 - 23) |
| 12 | Minute | BYTE | Minute (0 - 59) |
| 13 | Second | BYTE | Second (0 - 59; 60 = leap) |
| 14 | Day | BYTE | Date (1 - 31) |
| 15 | Month | BYTE | Month (1 - 12) |
| 16 - 17 | Year | INTEGER | Year (4 digit) |
| 18 | Receiver Status | BYTE | Tracking Status |
| 19 | UTC Flags | BYTE | Leap Second Flags |
| 20 | Reserved | BYTE | Contains 0xFF |
| 21 | Reserved | BYTE | Contains 0xFF |

**Leap Second Flag Definition**

**Bit 0:**  (1) UTC Time is available  
**Bits 1 - 3:** Undefined  
**Bit 4:**  (1) Leap Scheduled: Leap second pending asserted by GPS control segment.  
**Bit 5:**  (1) Leap Pending: set 24 hours before, until beginning of leap second.  
**Bit 6:**  (1) GPS Leap Warning: 6 hours before until 6 hours after leap event  
**Bit 7:**  (1) Leap In Progress. Only set during the leap second.
 
**Tracking Status Flag Definitions**

| Code | Meaning | Accuracy | Receiver Mode |
| ----- | ----- | ----- | ----- |
| 0 | Receiver is Navigating | +/- 1 us | Self Survey |
| 1 | Static 1 Sat. Timing Mode | +/- 1 us | 1-D Timing |
| 2 | Approximate Time | 20 - 50 ms | Acquisition |
| 3 | Startup | N/A | Initialization |
| 4 | Startup | N/A | Initialization |
| 5 | Dilution of Position too High | 5 ppm | Self Survey |
| 6 | Static 1 Sat. Timing: Sat. not usable | 5 ppm | 1-D Timing |
| 7 | No Satellites Usable | N/A | Self Survey |
| 8 | Only 1 Satellite Usable | 20 - 50 ms | Self Survey |
| 9 | Only 2 Satellite Usable | 20 - 50 ms | Self Survey | 
| 10 | Only 3 Satellites Usable | 20 - 50 ms | Self Survey |
| 11 | Invalid Solution | N/A | Error |
| 12 | Differential Corrections | N/A | N/A |
| 13 | Overdetermined Fixes | +/- 100 ns | Timing Steady State |

**Packet 8F-0B (Comprehensive Timing Packet)**

| Byte    | Item                  | Type    | Meaning      |
| ----- | ----- | ----- | -----|
| 0       | Sub-Packet ID         | BYTE    | Subcode 0x0B |
| 1 - 2   | Event Count           | INTEGER | External event count recorded (0 = PPS) |
| 3 - 10  | UTC / GPS TOW         | DOUBLE  | UTC / GPS time of week (seconds) |
| 11      | Date                  | BYTE    | Day of Month |
| 12      | Month                 | BYTE    | Month of Event |
| 13 - 14 | Year                  | INT     | Year of event |
| 15      | Receiver Mode         | BYTE    | Receiver operating dimensions: <br> 0: Horizontal (2D) <br> 1: Full Position (3D) <br> 2: Single Satellite (0D) <br> 3: Automatic (2D / 3D) <br> 4: DGPS reference <br>  5: Clock hold (2D) <br>  6: Over determined Clock |
| 15 - 17 | UTC Offset            | INTEGER | UTC Offset value (seconds) |
| 18 - 25 | Oscillator Bias       | DOUBLE  | Oscillator BIAS (meters) |
| 26 - 33 | Oscillator Drift Rate | DOUBLE  | Oscillator Drift (meters / second) |
| 34 - 37 | Bias Uncertainty      | SINGLE  | Oscillator bias uncertainty (meters) |
| 38 - 41 | Drift Uncertainty     | SINGLE  | Oscillator bias rate uncertainty (m / sec) |
| 42 - 49 | Latitude              | DOUBLE  | Latitude in radians |
| 50 - 57 | Longitude             | DOUBLE  | Longitude in radians |
| 58 - 65 | Altitude              | DOUBLE  | Altitude above mean sea level, in meters |
| 66 - 73 | Satellite ID          | BYTE    | SV Id No. of tracked satellites |


**Thunderbolt Timing packets Data Format**

Thunderbolt can output 2 synchronous packets.

**Primary Timing Packet - 0x8FAB**

| Byte  | Bit   | Item  | Type  | Value | Description |
| ----- | ----- | ----- | ----- | ----- | ----- |
| 0     |       | Subcode | UINT8 |     | 0xAB  |
| 1-4   |       | Time of Week | UINT32 | | GPS seconds of week |
| 5-6   |       | Week Number | UINT16  | | GPS Week Number |
| 7-8   |       | UTC Offset | SINT16   | | UTC Offset (seconds) |
| 9     | 0 <br> 1 <br> 2 <br> 3 <br> 4 | Timing Flag | Bit field | 0 or 1 <br> 0 or 1 <br> 0 or 1 <br> 0 or 1 <br> 0 or 1 <br> | GPS Time or UTC Time<br> GPS PPS or UTC PPS<br> time is set or time is not set<br> have UTC info or no UTC info<br> Time from GPS or time from user<br> | 
| 10    | | Seconds | UINT8 | 0-59 | (60 for UTC leap second event) |
| 11    | | Minutes | UINT8 | 0-59 | Minutes of Hour |
| 12    | | Hours | UINT8 | 0-23 | Hour of Day |
| 13    | | Day of Month | UINT8 | 1-31 | Day of Month |
| 14    | | Month | UINT8 | 1-12 | Month of Year |
| 15-16 | | Year | UINT16 | | Four digits of Year (e.g. 1998) |


**Supplemental Timing Packet - 0x8FAC**

| Byte  | Bit   | Item  | Type  | Value | Description |
| ----- | ----- | ----- | ----- | ----- | ----- |
| 0     |       | Subcode | UINT8 |     | 0xAC |
| 1     |       | Receiver Mode | UINT8 | 0 <br> 1 <br> 2 <br> 3 <br> 4 <br> 5 <br> 6 | Automatic (2D/3D)<br> Single Satellite (Time)<br> Horizontal (2D)<br> Full Position (3D)<br> DGPS Reference<br> Clock Hold (2D)<br> Overdetermined Clock<br> |
| 2    |       | Disciplining Mode | UINT8 | 0 <br> 1 <br> 2 <br> 3 <br> 4 <br> 5 <br> 6 | Normal <br> Power-Up<br> Auto Holdover<br> Manual Holdover<br> Recovery<br> Not Used</br> Disciplining disabled<br> |
| 3    |       | Self-Survey Progress | UINT 8 | 0-100% | |
| 4-7    |       | Holdover Duration |  UINT 32 | | seconds |
| 8-9 | 0 <br> 1 <br> 2 <br> 3 <br> 4 | Critical Alarms | UINT16 | Bit field | ROM checksum error<br> RAM check has failed<br> Power supply failure<br> FPGA check has failed<br> Oscillator control voltage at rail<br> |
| 10-11 | 0 <br> 1 <br> 2 <br> 3 <br> 4 <br> 5 <br> 6 | Minor Alarms | UINT16 | Bit field | Normal<br> Power-Up<br> Auto Holdover<br> Manual Holdover<br> Recovery<br> Not Used<br> Disciplining disabled<br> |
| 12   |       | GPS Decoding Status | UINT8 | 0<br> 1<br> 3<br> 8<br> 9<br> 0x0A<br> 0x0B<br> 0x0C<br> 0x10<br> | Doing fixes<br> Don't have GPS time<br> PDOP is too high<br> No usable sats<br> Only 1 usable sat<br> Only 2 usable sats<br> Only 3 usable sats<br> The chosen sat is unusable<br> TRAIM rejected the fix<br> |
| 13   |       | Disciplining Activity | UINT8 | 0 <br> 1 <br> 2 <br> 3 <br> 4 <br> 5 <br> 6 <br> 7 <br> 8 | Phase locking<br> Oscillator warming up<br> Frequency locking<br> Placing PPS<br> Initializing loop filter<br> Compensating OCXO<br> Inactive<br> Not used<br> Recovery mode<br> |
| 14   |       | Spare Status 1 | UINT8 | 0 | |
| 15   |       | Spare Status 2 | UINT8 | 0 | |
| 16-19 |      | PPS Offset | Single | | Estimate of UTC/GPS offset (ns) |
| 20-23 |      | 10 MHz Offset | Single | | Estimate of UTC/GPS offset (ns) |
| 24-27 |      | DAC Value | UINT32 | | Offset binary (0x00 - 0xFFFFF) |
| 28-31 |      | DAC Voltage | Single | | Volts |
| 32-35 |      | Temperature | Single | | degrees C |
| 36-43 |      | Latitude | Double | | radians |
| 44-51 |      | Longitude | Double | | radians |
| 52-59 |      | Altitude | Double | | Meters |
| 60-67 |      | Spare | | | For Future Expansion |

* * *

#### Pinouts

The following connections are required when connecting Palisade with a host:  

| Description | Host DB-9 | Host DB-25 | Palisade RS-232 | Palisade RS-422| Palisade Pin|
| ----- | ----- | ----- | ----- | ----- | ----- |
| **Port A** | | | | | |
| Receive Data | 2 | 3 | Green | Green / Blue | 8 (T-) & 10 (T+) |
| Request to Send | 7 | 4 | Gray | Gray / White | 6 (R-) & 7 (R+) |
| Signal Ground | 5 | 7 | Black | Black | 9 (GND) |
| **Port B** | | | | | |
| Receive Data | 2 | 3 | Brown | Brown / Yellow | 4 (T-) & 5 (T+) |
| Transmit Data | 3 | 2 | Violet | Orange/ Violet | 2 (R-) & 3 (R+) |
| Signal Ground | 5 | 7 | Black | Black | 9 (GND) |

{{% alert title="Note" color="warning" %}} 
Driving the RS-422 inputs on the Palisade single-ended, using the Green and Gray connections only, does not work on all serial ports. Use of the Palisade NTP Synchronization Interface Module is recommended.
{{% /alert %}}

**The 12 pin connector pinout definition:**  

Face the round 12 pin connector at the end of the cable, with the notch turned upwards.  

Pin 1 is to the left of the notch. Pins 2 - 8 wrap around the bottom, counterclockwise to pin 9 on the right of the notch. Pin 10 is just below the notch. Pins 10 (top), 11 (bottom left) and 12 (bottom right) form a triangle in the center of the connector.

**Pinouts for the Palisade NTP host adapter (Trimble PN 37070) DB-25 M connector are as follows:**

| DB-25M | Conductor | Palisade | Description |
| ----- | ----- | ----- | ----- |
| 1 | Red | 1 | Power |
| 7 | Black | 9 | Ground |
| 9 | Black/White | 12 | PPS - |
| 10 | Green | 8 | Transmit Port A (T-) |
| 11 | Brown | 4 | Transmit Port B (T-) |
| 12 | Gray | 7 | Receive Port A (R+) |
| 13 | Orange | 3 | Receive Port B (R+) |
| 21 | Orange/White | 11 | PPS + |
| 22 | Blue | 10 | Transmit Port A (T+) |
| 23 | Yellow | 5 | Transmit Port B (T+) |
| 24 | White | 6 | Receive Port A (R-) |
| 25 | Violet | 2 | Receive Port B (R-) |

* * *

#### Notes on the Thunderbolt Receiver's Firmware

The support for Thunderbolt Receiver in the palisade driver doesn't support (for now) event-polling, the reason is that the Thunderbolt receiver the patch is written for doesn't support time-on-request, so you just have to sit there and wait for the time to arrive with the PPS. We tried to contact Trimble because there's presumably a firmware update that support it, but we didn't have much luck. Here is a [link explaining the situation](https://lists.ntp.org/pipermail/hackers/2006-April/002218.html).

* * *

Questions or Comments:  

[Sven Dietrich](mailto:sven_dietrich@trimble.com)  
[Trimble Navigation Ltd.](http://www.trimble.com/)

[Fernando P. Hauscarriaga](mailto:fernandoph@iar.unlp.edu.ar)