---
title: "Arcron MSF Receiver"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver27/#synopsis)
*   [Description](/documentation/3-5.93e/driver27/#description)
*   [Monitor Data](/documentation/3-5.93e/driver27/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver27/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver27/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.27._u_</code>
: **Reference ID:** <code>MSF</code>
: **Driver ID:** <code>ARCRON_MSF</code>
: **Serial Port:** <code>/dev/arc\__u_</code>; 300 baud, 8-bits, 2-stop, no parity
: **Features:** <code>tty_clk</code>

* * *

#### Description

This driver supports the Arcron MSF receiver, and would probably also support the DCF77 variant of the same clock. The clock reports its ID as <code>MSFa</code> to indicate MSF as a source and the use of the ARCRON driver.

This documentation describes version V1.1 (1997/06/23) of the source and has been tested (amongst others) against xntpd3-5.90 on Solaris-1 (SunOS 4.1.3_U1 on an SS1 serving as a router and firewall) and against xntpd3-5.90 on Solaris-2.5 (on a SS1+ and TurboSPARC 170MHz). This code will probably work, and show increased stability, reduced jitter and more efficiency (fewer context switches) with the <code>tty_clk</code> discipline/STREAMS module installed, but this has not been tested. For a to-do list see the comments at the start of the code. 

This code has been significantly slimmed down since the V1.0 version, roughly halving the memory footprint of its code and data.

This driver is designed to allow the unit to run from batteries as designed, for something approaching the 2.5 years expected in the usual stand-alone mode, but no battery-life measurements have been taken.

Much of this code is originally from the other refclock driver files with thanks. The code was originally made to work with the clock by Derek Mulcahy, with modifications by [Damon Hart-Davis](mailto:d@hd.org). Thanks also to [Lyndon David](mailto:lyndond@sentinet.co.uk) for some of the specifications of the clock. 

There is support for a Tcl/Tk monitor written by Derek Mulcahy that examines the output stats; see the [ARC Rugby MSF Receiver](https://www.exnet.com/NTP/ARC/ARC.html) page for more details and the code. 

Look at the notes at the start of the code for further information; some of the more important details follow.

The driver interrogates the clock at each poll (ie every 64s by default) for a timestamp. The clock responds at the start of the next second (with the start bit of the first byte being on-time). The time is in 'local' format, including the daylight savings adjustment when it is in effect. The driver code converts the time back to UTC. 

The clock claims to be accurate to within about 20ms of the MSF-broadcast time, and given the low data transmission speed from clock to host, and the fact that the clock is not in continuous sync with MSF, it seems sensible to set the precision of this clock to -5 or -4, -4 being used in this code, which builds in a reported dispersion of over 63ms (ie says "This clock is not very good."). You can improve the reported precision to -4 (and thus reduce the base dispersion to about 31ms) by setting the <code>fudge flag3</code> to <code>1</code>.

Even a busy and slow IP link can yield lower dispersions than this from polls of primary time servers on the Internet, which reinforces the idea that this clock should be used as a backup in case of problems with such an IP link, or in the unfortunate event of failure of more accurate sources such as GPS. 

By default this clock reports itself to be at stratum 2 rather than the usual stratum 0 for a refclock, because it is not really suited to be used as other than a backup source. The stratum reported can be changed with the <code>stratum</code> directive to be whatever you like. After careful monitoring of your clock, and appropriate choice of the <code>time1</code> fudge factor to remove systematic errors in the clock's reported time, you might fudge the clock to stratum 1 to allow a stratum-2 secondary server to sync to it.

The driver code arranges to resync the clock to MSF at intervals of a little less than an hour (deliberately avoiding the same time each hour to avoid any systematic problems with the signal or host). Whilst resyncing, the driver supplements the normal polls for time from the clock with polls for the reception signal quality reported by the clock. If the signal quality is too low (0--2 out of a range of 0--5), we chose not to trust the clock until the next resync (which we bring forward by about half an hour). If we don't catch the resync, and so don't know the signal quality, we do trust the clock (because this would generally be when the signal is very good and a resync happens quickly), but we still bring the next resync forward and reduce the reported precision (and thus increase reported dispersion). 

If we force resyncs to MSF too often we will needlessly exhaust the batteries the unit runs from. During clock resync this driver tries to take enough time samples to avoid <code>xntpd</code> losing sync in case this clock is the current peer. By default the clock would only resync to MSF about once per day, which would almost certainly not be acceptable for NTP purposes.

The driver does not force an immediate resync of the clock to MSF when it starts up to avoid excessive battery drain in case <code>xntpd</code> is going to be repeatedly restarted for any reason, and also to allow enough samples of the clock to be taken for <code>xntpd</code> to sync immediately to this clock (and not remain unsynchronised or to sync briefly to another configured peer, only to hop back in a few poll times, causing unnecessary disturbance). This behaviour should not cause problems because the driver will not accept the timestamps from the clock if the status flag delivered with the time code indicates that the last resync attempt was unsuccessful, so the initial timestamps will be close to reality, even if with up to a day's clock drift in the worst case (the clock by default resyncs to MSF once per day).

The clock has a peculiar RS232 arrangement where the transmit lines are powered from the receive lines, presumably to minimise battery drain. This arrangement has two consequences:

*   Your RS232 interface must drive both +ve and -ve
*   You must (in theory) wait for an echo and a further 10ms between characters

This driver, running on standard Sun ahardware, seems to work fine; note the use of the <code>send_slow()</code> routine to queue up command characters to be sent once every two seconds.

Three commands are sent to the clock by this driver. Each command consists of a single letter (of which only the bottom four bits are significant), followed by a CR (ASCII 13). Each character sent to the clock should be followed by a delay to allow the unit to echo the character, and then by a further 10ms. Following the echo of the command string, there may be a response (ie in the case of the <code>g</code> and <code>o</code> commands below), which in the case of the <code>o</code> command may be delayed by up to 1 second so as the start bit of the first byte of the response can arrive on time. The commands and their responses are:

<code>**g CR**</code>

: Request for signal quality. Answer only valid during (late part of) resync to MSF signal. The response consists of two characters as follows:

| First Bit Number | Description | Second Bit Number | Description |
| ----- | ----- | ----- | ----- |
| 7 | parity | 7 | parity |
| 6 | always 0 | 6 | always 0 |
| 5 | always 1 | 5 | always 1 |
| 4 | always 1 | 4 | always 1 |
| 3 | always 0 | 3 | always 0 |
| 2 | always 0 | 2--0 | reception signal quality in the range 0--5 (very poor to very good); if in the range 0--2 no successful reception is to be expected. The reported value drops to zero when not resyncing, ie when first returned byte is not `3`. |
| 1 | always 1 | | |
| 0 | 0 if no reception attempt at the moment; 1 if reception attempt (ie resync) in progress | | |

<code>**h CR**</code>
: Request to resync to MSF. Can take up from about 30s to 360s. Drains batteries so should not be used excessively. After this the clock time and date should be correct and the phase within 20ms of time as transmitted from Rugby MSF (remember to allow for propagation time). By default the clock resyncs once per day shortly after 2am (presumably to catch transitions to/from daylight saving time quickly). With this driver code we resync at least once per hour to minimise clock wander. 

<code>**o CR**</code>
: Request timestamp. Start bit of first byte of response is on-time, so may be delayed up to 1 second.  Note that when the BST mode is in effect the time is GMT/UTC +0100, ie an hour ahead of UTC to reflect local time in the UK. The response data is as follows: 

  1.  hours tens (hours range from 00 to 23)
  2.  hours units
  3.  minutes tens (minutes range from 00 to 59)
  4.  minutes units
  5.  seconds tens (seconds presumed to range from 00 to 60 to allow for leap second)
  6.  seconds units
  7.  day of week 1 (Monday) to 7 (Sunday)
  8.  day of month tens (day ranges from 01 to 31)
  9.  day of month units
  10.  month tens (months range from 01 to 12)
  11.  month units
  12.  year tens (years range from 00 to 99)
  13.  year units

  14. BST/UTC status 
 
| Bit Number | Description |
| ----- | ----- | 
| 7 | parity |
| 6 | always 0 |
| 5 | always 1 |
| 4 | always 1 |
| 3 | always 0 |
| 2 | 1 if UTC is in effect (reverse of bit 1) |
| 1 | 1 if BST is in effect (reverse of bit 2) |
| 0 | 1 if BST/UTC change pending |

  15. clock status

| Bit Number | Description |
| ----- | ----- |
| 7 | parity |
| 6 | always 0 |
| 5 | always 1 |
| 4 | always 1 |
| 3 | `1` if low battery is detected |
| 2 | `1` if last resync failed (though officially undefined for the MSF clock) |
| 1 | `1` if at least one reception attempt since 0230 for the MSF clock was successful (0300 for the DCF77 clock)  |
| 0 | `1` if the clock has valid time---reset to zero when clock is reset (eg at power-up), and set to 1 after first successful resync attempt. |

The driver only accepts time from the clock if the bottom three bits of the status byte are <code>011</code>. The leap-year logic for computing day-in-year is only valid until 2099, and the clock will ignore stamps from the clock that claim BST is in effect in the first hour of each year. If the UK parliament decides to move us to +0100/+0200 time as opposed to the current +0000/+0100 time, it is not clear what effect that will have on the time broadcast by MSF, and therefore on this driver's usefulness. 

A typical <code>ntp.conf</code> configuration file for this driver might be:

<pre># hostname(n) means we expect (n) to be the stratum at which hostname runs.

#------------------------------------------------------------------------------
# SYNCHRONISATION PARTNERS
# ========================

# Our betters...
server 127.127.27.0 # ARCRON MSF radio clock
# Fudge stratum and other features as required.
# ADJUST time1 VALUE FOR YOUR HOST, CLOCK AND LOCATION!
fudge 127.127.27.0 stratum 1 time1 0.016 flag3 1 flags 4 1

peer 11.22.33.9 # tick(1--2).
peer 11.22.33.4 # tock(3), boot/NFS server.

# This shouldn't get swept away unless left untouched for a long time.
driftfile /var/tmp/ntp.drift

#------------------------------------------------------------------------------
# RESTRICTIONS
# ============

# By default, don't trust and don't allow modifications.  Ignore in fact.
restrict default ignore notrust nomodify

# Allow others in our subnet to check us out...
restrict 11.22.33.0 mask 255.255.255.0 nomodify notrust

# Trust our peers for time.  Don't trust others in case they are insane.
restrict 127.127.27.0 nomodify
restrict 11.22.33.4 nomodify
restrict 11.22.33.9 nomodify

# Allow anything from the local host.
restrict 127.0.0.1</pre>

There are a few <code>#define</code>s in the code that you might wish to play with:

<code>**ARCRON_KEEN**</code>

: With this defined, the code is relatively trusting of the clock, and assumes that you will have the clock as one of a few time sources, so will bend over backwards to use the time from the clock when available and avoid <code>xntpd</code> dropping sync from the clock where possible. You may wish to undefine this, especially if you have better sources of time or your reception is ropey. However, there are many checks built in even with this flag defined.

<code>**ARCRON_OWN_FILTER**</code>

: When defined, the code uses its own median-filter code rather than that available in <code>ntp_refclock.c</code> since the latter seems to have a minor bug, at least in version 3-5.90. If this bug goes away this flag should be turned off to avoid duplication of code. (The bug, if that's what it is, causes the last raw offset to be used rather than the median offset.)

Without this defined (and without <code>ARCRON_MULTIPLE_SAMPLES</code> below) a typical set of offsets reported and used to drive the clock-filter algorithm is (oldest last):

`filtoffset=  -4.32  -34.82   -0.78    0.89    2.76    4.58   -3.92   -2.17`

Look at that spike!

With this defined a typical set of offsets is:

`filtoffset=  -7.06   -7.06   -2.91   -2.91   -2.91   -1.27   -9.54   -6.70`

with the repeated values being some evidence of outlyers being discarded.

<code>**ARCRON_MULTIPLE_SAMPLES**</code>

: When is defined, we regard each character in the returned timecode as at a known delay from the start of the second, and use the smallest (most negative) offset implied by any such character, ie with the smallest kernel-induced display, and use that. This helps to reduce jitter and spikes.

<code>**ARCRON_LEAPSECOND_KEEN**</code>

: When is defined, we try to do a resync to MSF as soon as possible in the first hour of the morning of the first day of the first and seventh months, ie just after a leap-second insertion or deletion would happen if it is going to. This should help compensate for the fact that this clock does not continuously sample MSF, which compounds the fact that MSF itself gives no warning of an impending leap-second event. This code did not seem functional at the leap-second insertion of 30th June 1997 so is by default disabled.

<code>**PRECISION**</code>

: Currently set to <code>-4</code>, but you may wish to set it to <code>-5</code> if you are more conservative, or to <code>-6</code> if you have particularly good experience with the clock and you live on the edge. Note that the <code>flag3</code> fudge value will improve the reported dispersion one notch if clock signal quality is known good. So maybe just leave this alone.

<code>**NSAMPLES**</code>

: Should be at least 3 to help smooth out sampling jitters. Can be more, but if made too long can make <code>xntpd</code> overshoot on clock corrections and can hold onto bad samples longer than you would like. With this set to 4 and <code>NKEEP</code> set to 3 this allows the occasional bad sample (in my experience less than 1 value in 10) to be dropped. (Note that there seems to be some sort of 'beat' effect in the offset with a periodicity of about 7 samples as of this writing (1997/05/11) still under investigation; a filter of approximately this length should be able to almost completely suppress this effect.) Note that if the fudge-factor <code>flag3</code> is set to 1, a larger <code>NSAMPLES</code> is used. 

* * *

#### Monitor Data

Each timecode is written to the <code>clockstats</code> file with a signal quality value appended (`0`-`5` as reported by the clock, or `6` for unknown).

Each resync and result (plus gaining or losing MSF sync) is logged to the system log at level <code>LOG_NOTICE</code>; note that each resync drains the unit's batteries, so the syslog entry seems justified.

Syslog entries are of the form:

<pre>May 10 10:15:24 oolong xntpd[615]: ARCRON: unit 0: sending resync command
May 10 10:17:32 oolong xntpd[615]: ARCRON: sync finished, signal quality 5: OK, will use clock
May 10 11:13:01 oolong xntpd[615]: ARCRON: unit 0: sending resync command
May 10 11:14:06 oolong xntpd[615]: ARCRON: sync finished, signal quality -1: UNKNOWN, will use clock anyway
May 10 11:41:49 oolong xntpd[615]: ARCRON: unit 0: sending resync command
May 10 11:43:57 oolong xntpd[615]: ARCRON: sync finished, signal quality 5: OK, will use clock
May 10 12:39:26 oolong xntpd[615]: ARCRON: unit 0: sending resync command
May 10 12:41:34 oolong xntpd[615]: ARCRON: sync finished, signal quality 3: OK, will use clock</pre>

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0. On a Sun SparcStation 1 running SunOS 4.1.3_U1, with the receiver in London, a value of 0.020 (20ms) seems to be appropriate.

<code>**time2 _time_**</code>

: Not currently used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0. It is suggested that the clock be fudged to stratum 1 so that it is used as a backup time source rather than a primary when more accurate sources are available.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>MSFa</code>. 

<code>**flag1 0 | 1**</code>

: (Modes 1-3) Not currently used by this driver. 

<code>**flag2 0 | 1**</code>

: Not currently used by this driver. 

<code>**flag3 0 | 1**</code>

: If set to 1, better precision is reported (and thus lower dispersion) while clock's received signal quality is known to be good.

<code>**flag4 0 | 1**</code>

: If set to 1, a longer-than-normal (8-stage rather than 4-stage) median filter is used, to provide some extra smoothing of clock output and reduction in jitter, at the cost of extra clock overshoot. Probably not advisable unless the server using this clock has other sources it can use to help mitigate the overshoot. 

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)  

[ARC Rugby MSF Receiver](https://www.exnet.com/NTP/ARC/ARC.html) page