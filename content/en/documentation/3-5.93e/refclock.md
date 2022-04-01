---
title: "Reference Clock Drivers"
type: archives
noindex: true
---

#### Reference Clock Drivers

Support for most of the commonly available radio and modem clocks is included in the default configuration of the NTP daemon for Unix <code>xntpd</code>. Individual clocks can be activated by configuration file commands, specifically the <code>server</code> and <code>fudge</code> commands described in the [<code>xntpd</code> program manual page](/documentation/3-5.93e/xntpd/). The following discussion presents Information on how to select and configure the device drivers in a running Unix system.

Radio and modem clocks by convention have addresses in the form <code>127.127._t.u_</code>, where <code>_t_</code> is the clock type and <code>_u_</code> is a unit number in the range 0-3 used to distinguish multiple instances of clocks of the same type. Most of these clocks require support in the form of a serial port or special bus peripheral. The particular device is normally specified by adding a soft link <code>/dev/device\__u_</code> to the particular hardware device involved, where <code>_u_</code> correspond to the unit number above.

Following is a list showing the type and title of each driver currently implemented. The compile-time identifier for each is shown in parentheses. Click on a selected type for specific description and configuration documentation, including the clock address, reference ID, driver ID, serial port device name and speed, and features (line disciplines, etc.). For those drivers without specific documentation, please contact the author listed in the [Copyright Notice](/documentation/3-5.93e/copyright/) page.

*   [Type 1](/documentation/3-5.93e/driver1/) Local Clock Driver (<code>LOCAL_CLOCK</code>)
*   [Type 2](/documentation/drivers/driver2/) Trak 8820 GPS Receiver (<code>TRAK</code>
*   [Type 3](/documentation/drivers/driver3/) PSTI/Traconex 1020 WWV/WWVH Receiver (<code>PST</code>)
*   [Type 4](/documentation/3-5.93e/driver4/) Spectracom 8170 and Netclock/2 WWVB Receivers (<code>WWVB</code>)
*   [Type 5](/documentation/3-5.93e/driver5/) TrueTime GPS/GOES/OMEGA Receivers (<code>TRUETIME</code>)
*   [Type 6](/documentation/3-5.93e/driver6/) IRIG Audio Decoder (Sun only) (<code>IRIG</code>)
*   [Type 7](/documentation/3-5.93e/driver7/) Scratchbuilt CHU Receiver (<code>CHU</code>)
*   [Type 8](/documentation/3-5.93e/driver8/) Generic Reference Driver (<code>PARSE</code>)
*   [Type 9](/documentation/3-5.93e/driver9/) Magnavox MX4200 GPS Receiver (<code>MX4200</code>)
*   [Type 10](/documentation/3-5.93e/driver10/) Austron 2200A/2201A GPS Receivers (<code>GPS_AS2201</code>)
*   [Type 11](/documentation/3-5.93e/driver11/) Arbiter 1088A/B GPS Receiver (<code>ARBITER</code>)
*   [Type 12](/documentation/3-5.93e/driver12/) KSI/Odetics TPRO/S IRIG Interface (Sun only) (<code>TPRO</code>)
*   Type 13 Leitch CSD 5300 Master Clock Controller (<code>LEITCH</code>)
*   Type 14 EES M201 MSF Receiver (<code>MSFEES</code>)
*   [Type 15](/documentation/3-5.93e/driver5/) * TrueTime TM-TMD GPS Receiver
*   Type 16 Bancomm GPS/IRIG Receiver (HP only) (<code>BANC</code>)
*   Type 17 Datum Precision Time System (<code>DATUM</code>)
*   [Type 18](/documentation/3-5.93e/driver18/) NIST Modem Time Services (<code>ACTS</code>)
*   [Type 19](/documentation/3-5.93e/driver19/) Heath WWV/WWVH Receiver (<code>WWV_HEATH</code>)
*   [Type 20](/documentation/3-5.93e/driver20/) Generic NMEA GPS Receiver (<code>NMEA</code>)
*   Type 21 TrueTime GPS-VME Interface (HP only) (<code>GPSVME</code>)
*   [Type 22](/documentation/3-5.93e/driver22/) PPS Clock Discipline (<code>ATOM</code>)
*   [Type 23](/documentation/3-5.93e/driver23/) PTB Modem Time Service (<code>PTBACTS</code>) 
*   [Type 24](/documentation/3-5.93e/driver24/) USNO Modem Time Service (<code>USNO</code>)
*   [Type 25](/documentation/3-5.93e/driver5/) * TrueTime generic receivers
*   [Type 26](/documentation/3-5.93e/driver26/) Hewlett Packard 58503A GPS Receiver (<code>HPGPS</code>)
*   [Type 27](/documentation/3-5.93e/driver27/) Arcron MSF Receiver (<code>ARCRON_MSF</code>)
*   [Type 28](/documentation/3-5.93e/driver28/) Shared Memory Driver (<code>SHM</code>)

\* All TrueTime receivers are now supported by one driver, type 5. Types 15 and 25 will be retained only for a limited time and may be reassigned in future.