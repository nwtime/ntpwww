---
title: "Shared Memory Driver"
type: archives
---

Last update: 8-Aug-2014 19:17 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver28/#synopsis)
*   [Description](/archives/drivers/driver28/#description)
*   [Structure of shared memory-segment](/archives/drivers/driver28/#structure-of-shared-memory-segment)
*   [Operation mode=0](/archives/drivers/driver28/#operation-mode0)
*   [Operation mode=1](/archives/drivers/driver28/#operation-mode1)
*   [Mode-independent post-processing](/archives/drivers/driver28/#mode-independent-post-processing)
*   [GPSD](/archives/drivers/driver28/#gpsd)
*   [Clockstats](/archives/drivers/driver28/#clockstats)
*   [The 'mode' word](/archives/drivers/driver28/#the-mode-word)
*   [Fudge Factors](/archives/drivers/driver28/#fudge-factors)
*   [Public vs. Private SHM segments](/archives/drivers/driver28/#public-vs-private-shm-segments)
*   [Additional Information](/archives/drivers/driver28/#additional-information)

* * *

#### Synopsis

Address: 127.127.28._u_  
Reference ID: <tt>SHM</tt>  
Driver ID: <tt>SHM</tt>

* * *

#### Description

This driver receives its reference clock info from a shared memory-segment. The shared memory-segment is created with owner-only access by default, unless otherwise requested by the mode word for units ≥2. Units 0 and 1 are always created with owner-only access for backward compatibility.

* * *

#### Structure of shared memory-segment

<pre>struct shmTime {
        int    mode; /* 0 - if valid is set:
                      *       use values,
                      *       clear valid
                      * 1 - if valid is set:
                      *       if count before and after read of data is equal:
                      *         use values
                      *       clear valid
                      */
        volatile int    count;
        time_t          clockTimeStampSec;
        int             clockTimeStampUSec;
        time_t          receiveTimeStampSec;
        int             receiveTimeStampUSec;
        int             leap;
        int             precision;
        int             nsamples;
        volatile int    valid;
        unsigned        clockTimeStampNSec;     /* Unsigned ns timestamps */
        unsigned        receiveTimeStampNSec;   /* Unsigned ns timestamps */
        int             dummy[8];
};</pre>

* * *

#### Operation mode=0

Each second, the value of `valid` of the shared memory-segment is checked:

If set, the values in the record (clockTimeStampSec, clockTimeStampUSec, receiveTimeStampSec, receiveTimeStampUSec, leap, precision) are passed to _NTPD_, and `valid` is cleared and `count` is bumped.

If not set, `count` is bumped.

* * *

#### Operation mode=1

Each second, `valid` in the shared memory-segment is checked:

If set, the `count` field of the record is remembered, and the values in the record (clockTimeStampSec, clockTimeStampUSec, receiveTimeStampSec, receiveTimeStampUSec, leap, precision) are read. Then, the remembered `count` is compared to current value of `count` now in the record. If both are equal, the values read from the record are passed to _NTPD_. If they differ, another process has modified the record while it was read out (was not able to produce this case), and failure is reported to _NTPD_. The `valid` flag is cleared and `count` is bumped.

If not set, `count` is bumped

* * *

#### Mode-independent post-processing

After the time stamps have been successfully plucked from the SHM segment, some sanity checks take place:

*   The receive time stamp of the SHM data must be in the last 5 seconds before the time the data is processed. This helps in weeding out stale data.
*   If the absolute difference between remote and local clock exceeds the limit (either _time2_ or the default of 4hrs), then the sample is discarded. This check is disabled when _flag1_ is set to 1.

* * *

#### GPSD

[_GPSD_](http://gpsd.berlios.de/) knows how to talk to many GPS devices. It can work with _NTPD_ through the SHM driver.

The _GPSD_ man page suggests setting minpoll and maxpoll to 4. That was an attempt to reduce jitter. The SHM driver was fixed (ntp-4.2.5p138) to collect data each second rather than once per polling interval so that suggestion is no longer reasonable.

{{% alert title="Note" color="warning" %}} 
The _GPSD_ client driver (type 46) uses the _GPSD_ client protocol to connect and talk to _GPSD_, but using the SHM driver is the ancient way to have _GPSD_ talk to _NTPD_. There are some tricky points when using the SHM interface to interface with _GPSD_, because _GPSD_ will use two SHM clocks, one for the serial data stream and one for the PPS information when available. Receivers with a loose/sloppy timing between PPS and serial data can easily cause trouble here because _NTPD_ has no way to join the two data streams and correlate the serial data with the PPS events.
{{% /alert %}}

* * *

#### Clockstats

If flag4 is set when the driver is polled, a clockstats record is written. The first 3 fields are the normal date, time, and IP address common to all clockstats records.

The 4th field is the number of second ticks since the last poll. The 5th field is the number of good data samples found. The last 64 will be used by _NTPD_. The 6th field is the number of sample that didn't have valid data ready. The 7th field is the number of bad samples. The 8th field is the number of times the mode 1 info was update while _NTPD_ was trying to grab a sample.

Here is a sample showing the GPS reception fading out:

<pre>54364 84927.157 127.127.28.0  66  65   1   0   0
54364 84990.161 127.127.28.0  63  63   0   0   0
54364 85053.160 127.127.28.0  63  63   0   0   0
54364 85116.159 127.127.28.0  63  62   1   0   0
54364 85180.158 127.127.28.0  64  63   1   0   0
54364 85246.161 127.127.28.0  66  66   0   0   0
54364 85312.157 127.127.28.0  66  50  16   0   0
54364 85375.160 127.127.28.0  63  41  22   0   0
54364 85439.155 127.127.28.0  64  64   0   0   0
54364 85505.158 127.127.28.0  66  36  30   0   0
54364 85569.157 127.127.28.0  64   0  64   0   0
54364 85635.157 127.127.28.0  66   0  66   0   0
54364 85700.160 127.127.28.0  65   0  65   0   0
</pre>

* * *

#### The 'mode' word

Some aspects of the driver behavior can be adjusted by setting bits of the 'mode' word in the server configuration line:  
  <tt>server 127.127.28.</tt>_x_ <tt>mode</tt> _Y_

**mode word bits and bit groups**

| Bit |Dec | Hex | Meaning |
| ----- | ----- | ----- | ----- |
| 0 | 1 | 1 | The SHM segment is private (mode 0600). This is the fixed default for clock units 0 and 1; clock units >1 are mode 0666 unless this bit is set for the specific unit. |
| 1-31 | - | - | reserved: do not use |

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Maximum allowed difference between remote and local clock, in seconds. Values <1.0 or >86400.0 are ignored, and the default value of 4hrs (14400s) is used instead. See also flag 1.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>SHM</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Skip the difference limit check if set. Useful for systems where the RTC backup cannot keep the time over long periods without power and the SHM clock must be able to force long-distance initial jumps. Check the difference limit if cleared (default).</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>If flag4 is set, clockstats records will be written when the driver is polled.</dd>

</dl>

* * *

#### Public vs. Private SHM segments

The driver attempts to create a shared memory segment with an identifier depending on the unit number. This identifier (which can be a numeric value or a string) clearly depends on the method used, which in turn depends on the host operating system:

*   <tt>Windows</tt> uses a file mapping to the page file with the name `Global\NTP_u_` for public accessible mappings, where `_u_` is the clock unit. Private / non-public mappings are created as `Local\NTP_u_`.

    Public access assigns a NULL DACL to the memory mapping, while private access just uses the default DACL of the process creating the mapping.

*   <tt>SYSV IPC</tt> creates a shared memory segment with a key value of <tt>0x4E545030</tt> + `_u_`, where `_u_` is again the clock unit. (This value could be hex-decoded as `NTP0`, `NTP1`,..., with funny characters for units > 9.)

    Public access means a permission set of 0666, while private access creates the mapping with a permission set of 0600.

There's no support for POSIX shared memory yet.

NTPD is started as root on most POSIX-like operating systems and uses the setuid/setgid system API to run under reduced rights once the initial setup of the process is done. One consequence out of this is that the allocation of SHM segments must be done early during the clock setup. The actual polling of the clock is done as the run-time user; deferring the creation of the SHM segment to this point will create a SHM segment owned by the runtime-user account. The internal structure of _NTPD_ does not permit the use of a fudge flag if this is to be avoided; this is the reason why a mode bit is used for the configuration of a public segment.

When running under Windows, the chosen user account must be able to create a SHM segment in the global object name space for SHM clocks with public access. Otherwise the session isolation used by Windows kernels after WinXP will get into the way if the client program does not run in the same session.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock)

