---
title: "6.3. Various Tricks"
description: "This section of the NTP FAQ demonstrates a few configuration tricks."
type: "archives"
---

6.3.1 [Mixing Time Protocols](#631-mixing-time-protocols)   
6.3.2 [Avoiding Time Steps](#632-avoiding-time-steps)    
6.3.3 [Using the Echo Feature in PPS API](#633-using-the-echo-feature-in-pps-api)  

* * *

#### 6.3.1 Mixing Time Protocols

> **Note:** Mixing different time protocols is generally deprecated, because it can invalidate some assumptions necessary for proper operation of any time protocol.

However, sometimes there is a need for NTP to utilize a server that is using a different Time protocol. The short and possibly unpleasant answer is: "Run NTP on that server!".

Alternately, you need a modified configuration to prevent clock adjustments originating from NTP. This example is thanks to Marc Brett:

**Example 6.3a: Using TimeServ and NTP on Windows NT**

In this example, an old Windows NT server is using TimeServ for clock synchronization, and checks the USNO clock via modem. I also want to synchronize some UNIX servers, but NTP via Internet is not possible.

Disable NTP from adjusting the local clock on the Windows NT server using:

<pre>server 127.127.1.0
fudge  127.127.1.0 stratum 4
driftfile %windir%\ntp.drift
disable ntp</pre>

* * *

#### 6.3.2 Avoiding Time Steps

(Answer by Marc Brett) NTP works with up to 1000 seconds of offset, but when the error is "big", where big is defined as 128 ms (!), it will by default step the clock.

It is possible to tell it to always slew the clock though. The solution given refers to the following description: "The clock is ahead by over 20 minutes and it seems to drift forward 6 seconds a week. I would like to bring it back about 30 seconds a week until it's synchronized."

1.  Install `ntpd` with no reference clocks except the local clock (`127.127.0.1`), fudge stratum to 10 or something like that.

2.  Make a fake `ntp.drift` file containing a value which would correct for your drift rate (about `-10.0`), plus a value big enough to bring it back in line within a week: `-(20 * 60) * 1e6 / (86400 * 7) = -1984`.

    Since this number is too large (greater than `500 ppm`), I suspect that you'll have to settle for using `-500` in `ntp.drift`, and allow up to four weeks for your clock to be approximately correct of slightly slow.

    (I believe a negative number in `ntp.drift` will indeed slow the clock down, can anyone verify this?)

3.  At that time you can insert a proper NTP server in your `ntp.conf` file and restart the daemon.

An alternative solution suggests (I assume that there is a chance of simply taking the server offline for 30 minutes sometime during the next few weeks):

1.  Shutdown
2.  Set the BIOS clock
3.  Restart

* * *

#### 6.3.3 Using the Echo Feature in PPS API

This answer provided by [Vladimir Smotlacha](mailto:vs@cesnet.cz) was rephrased by the editor.

The Linux implementation of the PPS API contains the echo feature for the serial ports. The principle is quite simple: an event on the DCD line causes the interrupt routine to generate an event also on the RTS line after getting the event's timestamp. With some external device like a two channel oscilloscope or counter one can measure the difference between the original signal and its echo. About half of the time is the delay between creation of the event and getting its timestamp. That way one can estimate the delay and jitter between real PPS signal and its timestamps.

An utility named `ppsctl` (formerly named `enable_pps`) can be used to activate echo on a port by additionally specifying <code>-e*X*</code>, where <code>_X_</code> is either `a` (assert) or `c` (clear). The utility just sets the flags as described in [RFC 2783](/reflib/rfc/rfc2783.txt). The Linux implementation will always clear the RTS bit in the UART if an event becomes active, and it will clear the bit when the DCD line changes back to the inactive state. Therefore you cannot have an echo for both events.

**Example 6.3b: Measurements and Statistics of PPS Echo Delay**

The following graphs are the result of PPS echo delay measurement during normal operation of an NTP server (about 120 clients). The first PC is a standard Pentium 150MHz (UDMA disk, kernel 2.2.17, NTP 4.0.99k), the second is DELL 1400 (Pentium III 860MHz, SCSI disk, kernel 2.2.18, NTP 4.0.99k36). Source of PPS signal was a Garmin GPS35, and a universal counter SR 620 (Stanford Research Systems) was used for measurements. Root Allan variance of PPS signal derived from GPS is 43 nanoseconds.

| Machine | Mean | Root Allan Variance | Standard Deviation |
| ----- | ----- | ----- | ----- |
| P150 | 11.02 | 0.83 | 0.95 |
| P850 | 8.31 | 0.34 | 0.36 |

![](/ntpfaq/pps-delay.png)

**The graph shows the raw measurements for the delay round-trip time.**

![](/ntpfaq/pps-distrib.png)

**The graph shows the distribution of the delay samples.**

When varying the system load for the P150 with a kernel compilation (varying I/O and CPU load), the delay increased by roughly 15 microseconds. Plain CPU load (simple loop) only adds an extra delay of 7&mu;s, while disk I/O adds up to 30&mu;s. IDE disks without using DMA add up to 100&mu;s of extra delay.