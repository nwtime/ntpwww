---
title: "Shared Memory Driver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver28/#synopsis)
*   [Description](/archives/3-5.93e/driver28/#description)
*   [Structure of shared memory-segment](/archives/3-5.93e/driver28/#structure-of-shared-memory-segment)
*   [Operation mode=0](/archives/3-5.93e/driver28/#operation-mode0)
*   [Operation mode=1](/archives/3-5.93e/driver28/#operation-mode1)
*   [Fudge Factors](/archives/3-5.93e/driver28/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver28/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.28._u_</code>
: **Reference ID:** <code>SHM</code>
: **Driver ID:** <code>SHM</code>

* * *

#### Description

This driver receives its reference clock info from a shared memory-segment. The shared memory-segment is created with owner-only access for unit 0 and 1, and world access for unit 2 and 3.

* * *

#### Structure of shared memory-segment

<pre>
struct shmTime {
  int    mode; /* 0 - if valid set
                *       use values, 
                *       clear valid
                * 1 - if valid set 
                *       if count before and after read of 
                *       values is equal,
                *         use values 
                *       clear valid
                */
  int    count;
  time_t clockTimeStampSec;      /* external clock */
  int    clockTimeStampUSec;     /* external clock */
  time_t receiveTimeStampSec;    /* internal clock, when external value was received */
  int    receiveTimeStampUSec;   /* internal clock, when external value was received */
  int    leap;
  int    precision;
  int    nsamples;
  int    valid;
  int    dummy[10]; 
};
</pre>

* * *

#### Operation mode=0

When the poll-method of the driver is called, the valid-flag of the shared memory-segment is checked:

If set, the values in the record (<code>clockTimeStampSec, clockTimeStampUSec, receiveTimeStampSec, receiveTimeStampUSec, leap, precision</code>) are passed to ntp, and the <code>valid-flag</code> is cleared.

If not set, a timeout is reported to ntp, nothing else happened.

* * *

#### Operation mode=1

When the poll-method of the driver is called, the valid-flag of the shared memory-segment is checked:

If set, the count-field of the record is remembered, and the values in the record (<code>clockTimeStampSec, clockTimeStampUSec, receiveTimeStampSec, receiveTimeStampUSec, leap, precision</code>) are read. Then, the remembered count is compared to the count now in the record. If both are equal, the values read from the record are passed to ntp. If they differ, another process has modified the record while it was read out (was not able to produce this case), and failure is reported to ntp. The valid flag is cleared.

If not set, a timeout is reported to ntp, nothing else happened.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>SHM</code>.

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

[Reference Clock Drivers](/archives/3-5.93e/refclock)