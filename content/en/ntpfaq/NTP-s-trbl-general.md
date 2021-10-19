---
title: "8.2. General Issues"
type: "archives"
---

This section discusses problems that are independent of a specific operating system, probably referring to more specific entries.

8.2.1. [Starting, running, querying](#starting-running-querying)  
8.2.1.1. [How can I check that ntpd is up and running?](#how-can-i-check-that-ntpd-is-up-and-running)  
8.2.1.2. [Whenever I execute ntpd the daemon will only run for about 10 to 20 minutes. Do you have any idea why?](#whenever-i-execute-ntpd-the-daemon-will-only-run-for-about-10-to-20-minutes-do-you-have-any-idea-why)  
8.2.2. [Cabling and Interfacing](#cabling-and-interfacing)  
8.2.2.1. [Why does my Serial Interface hang when I connect a PPS Signal to DCD?](#why-does-my-serial-interface-hang-when-i-connect-a-pps-signal-to-dcd)  
8.2.2.2. [Why is the PPS API only detecting one Edge?](#why-is-the-pps-api-only-detecting-one-edge)  
8.2.3. [Exchanging Time](#exchanging-time)  
8.2.3.1. [Is a remote server providing time?](#is-a-remote-server-providing-time)  
8.2.3.2. [My server is up and running, but it is unusable for clients](#my-server-is-up-and-running-but-it-is-unusable-for-clients)  
8.2.3.3. [I waited a long time, still server not working](#i-waited-a-long-time-still-server-not-working)  
8.2.4. [Cryptography](#cryptography)  
8.2.4.1. [No time received when using autokey](#no-time-received-when-using-autokey) 
8.2.5. [Time Errors](#time-errors)  
8.2.5.1. [Why does my server change time references quite frequently?](#why-does-my-server-change-time-references-quite-frequently)  
8.2.5.2. [My server periodically loses synchronization](#my-server-periodically-loses-synchronization)  
8.2.5.3. [Why does my system step 0.6 seconds several times a day?](#why-does-my-system-step-06-seconds-several-times-a-day)  
8.2.6. [Messing with broken Hardware](#messing-with-broken-hardware)  
8.2.6.1. [How do I set the correct value for tick?](#how-do-i-set-the-correct-value-for-tick)  
8.2.7. [Incompatibilities](#incompatibilities)  
8.2.7.1. [How do I set the precision?](#how-do-i-set-the-precision)  
8.2.8. [Other](#other)  
8.2.8.1. [ntpd periodically opens a dial-out connection. Can I avoid that?](#ntp-periodically-opens-a-dial-out-connection-can-i-avoid-that)  
8.2.8.2. [Any more Hints?](#any-more-hints)  
8.2.9.1. [Fatal Errors](#fatal-errors)  
8.2.9.1.1. [ntpq: read: connection refused](#ntpq-read-connection-refused)  
8.2.9.1.2. [127.0.0.1: timed out, nothing received, Request timed out](#127001-timed-out-nothing-received-request-timed-out)  
8.2.9.1.3. [ntpdate: no server suitable for synchronization found](#ntpdate-no-server-suitable-for-synchronization-found)  
8.2.9.2. [Syntax Errors](#syntax-errors)  
8.2.9.2.1. [configure: keyword "precision" unknown, line ignored](#configure-keyword-precision-unknown-line-ignored)  
8.2.9.3. [Warnings](#warnings)  
8.2.9.3.1. [Previous time adjustment didn't complete](#previous-time-adjustment-didnt-complete)  
8.2.9.4. [Spurious and unexpected Messages](#spurious-and-unexpected-messages)  
8.2.9.4.1. [sendto: Overlapped I/O operation is in progress.](#sendto-overlapped-i-o-operation-is-in-progress)

* * *

#### 8.2.1. Starting, running, querying

#### 8.2.1.1. How can I check that ntpd is up and running?

The easiest command to verify that `ntpd` is still running is `ntpq -p`. This command will contact `ntpd` on the local host, and it will list all configured servers together with some health status. If `ntpd` is not running, the typical error message is `ntpq: read: Connection refused`.

If your are logged in to a UNIX machine, you can use `ps` to look for the daemon.

* * *

#### 8.2.1.2. Whenever I execute ntpd the daemon will only run for about 10 to 20 minutes. Do you have any idea why?

`ntpd` expects that the system time has been set closely to the real time, for example by using `ntpdate`. If the [reference time is significantly off](/ntpfaq/ntp-s-algo/#5114-what-happens-if-the-reference-time-changes), `ntpd` waits up to 20 minutes until it sets the time).

However, if the time is off by more than some magic amount of roughly 20 minutes, `ntpd` refuses to set the system time, and it terminates instead. To confirm what is going on, look into syslog or into the logfile you configured!

Either set your system clock with `ntpdate` before starting `ntpd`, or try the `-g` switch for `ntpd`. Or just set the time manually.

* * *

#### 8.2.2. Cabling and Interfacing

#### 8.2.2.1. Why does my Serial Interface hang when I connect a PPS Signal to DCD?

Sometimes drivers misinterpret the meaning of DCD to be a MODEM status. When using the `stty -a` command, the port used should have `clocal` set (preferrably together with `-hupcl`). When using a standard modem cable, make sure that the DCD pin is not connected to some other output of the reference clock as well.

* * *

#### 8.2.2.2. Why is the PPS API only detecting one Edge?

First, the PPS API is not required to provide an implementation that can detect both edges of a pulse. See function `time_pps_getcap()` in the description of the API.

Then the hardware may not be responding fast enough. See also [Q: 6.2.4.6.1.](/ntpfaq/ntp-s-config-adv/#62461-what-is-the-shortest-width-for-a-pulse-connected-to-the-dcd-pin-of-an-rs-232-interface) about timing on a serial port.

Finally, even if the hardware can send an interrupt for the edge being detected first, the CPU may be still busy with handling the interrupt when the hardware detects the other edge. That may either cause the second interrupt to be missed, or the interrupt handler being called for the first interrupt actually sees a hardware state that corresponds to the second interrupt condition, thereby reporting the wrong event, ignoring the edge that originally triggered the interrupt.

* * *

#### 8.2.3. Exchanging Time

#### 8.2.3.1. Is a remote server providing time?

Basically the procedure to check a remote server is identical to debugging a local server, but some commands may be restricted. To check a remote server with `ntpq`, simply add the desired host name or IP address to the command line.

There is another command named `ntptrace` to follow a complete synchronization path from the local or specified server to the reference clock.

**Example 7. Using ntptrace**

This example is taken from David Dalton's _NTP Primer_, another good introduction to NTP (originally written for HP-UX):

<pre>ntptrace cosl4
cosl4: stratum 5, offset 0.022003, synch distance 0.24033
te897-01.cup.hp.com: stratum 4, offset 0.014292, synch distance 0.17822
hpuxps.cup.hp.com: stratum 3, offset 0.006833, synch distance 0.13556
cupertino.cns.hp.com: stratum 2, offset 0.005313, synch distance 0.07320
listo.hp.com: stratum 1, offset 0.010896, synch distance 0.02277, refid 'WWVB'</pre>

The output of the command shows the stratum of the desired server, the estimated offset from the correct time, and an estimation of the random error.

* * *

#### 8.2.3.2. My server is up and running, but it is unusable for clients

Well, this is the answer for the impatient: Probably you have made no mistakes, but you simply have to wait for about five minutes until the server synchronizes to a time reference for the first time. If you changed the `minpoll` parameter, the wait time may change accordingly.

If you are running `xntpd` for the first time, you may even have to wait longer, because `xntpd` resets after a _time step_, thus needing another five minutes. (see also [How will NTP discipline my Clock?](/ntpfaq/ntp-s-algo/#5161-how-will-ntp-discipline-my-clock)).

If the above does not apply, see the next question.

* * *

#### 8.2.3.3. I waited a long time, still server not working

If you have waited for more than 20 minutes since startup of `ntpd`, it's time for monitoring `ntpd`. First you should verify that your daemon is [still running](#8211-how-can-i-check-that-ntpd-is-up-and-running). In any case you should also check your `syslog` for messages from `ntpd`. Messages found there are influenced by the `logconfig` statement in `/etc/ntp.conf` and by your `/etc/syslog.conf`.

If you still have no clue of what's going wrong, you should contact `ntpd` with one of the frontend programs named `ntpq` and `ntpdc`. One of the easiest ways to get a first impression of the daemon's status is:

1.  Run `ntpq -p` on the host where `ntpd` is running, or specify the host name at the end of the command line for a remote host (e.g. <code>ntpq -p _hostname_</code>). This command will show you the number and the status of your configured or otherwise used time references.
2.  Run `ntpq -c as` in a similar way to see what `ntpd` thinks of these time references.

If the above does not explain your problem, use `ntpq -p` to quickly inspect configured time sources, reachability, delay, and dispersion. Basically the reachability should be `377` for full reachability (an octal value). The delay should be positive, but small, depending on your network technology. Dispersion should be below `1000` (1 second) for at least one server. One of the servers should be marked with a `*`.

Here's another example taken from David Dalton's NTP Primer (NTPv3):

<pre>remote  refid   st t when poll reach   delay   offset    disp
=========================================================================
*WWVB_SPEC(1)  .WWVB.  0 l  114   64  377     0.00   37.623   12.77  
 relay.hp.com    listo 2 u  225  512  377     6.93   34.052   10.79  
 cosl4.cup.hp.co listo 2 u  226  512  377     4.18   29.385   13.21  
 paloalto.cns.hp listo 2 u  235  512  377     9.80   33.487   11.61  
 chelmsford.cns. listo 2 u  233  512  377    88.79   30.462    9.66  
 atlanta.cns.hp. listo 2 u  231  512  377    67.44   32.909   12.86  
 colorado.cns.hp listo 2 u  233  512  377    43.70   30.077   18.63  
 boise.cns.hp.co listo 2 u  224  512  377    33.42   31.682    8.54</pre>

* * *

#### 8.2.4. Cryptography

#### 8.2.4.1. No time received when using autokey

The first place to check (as always) is the system log file or (if configured) `ntpd`'s log file. Here's a sample of successful configuration between `ltgpsdemo`, an external timeserver (Meinberg LANTIME) synchronized to GPS and PPS, and `elf`, a client running Linux with no kernel modifications (SUSE Linux 9.2). Right after startup, the client displays a `refid` of `.INIT.` like this:

<pre>ntpq> pe
     remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
 GENERIC(1)      .GPS.            0 l    4   64    1    0.000   -0.719   0.001
 PPS(1)          .PPS.           16 l    -   64    0    0.000    0.000 4000.00
 ltgpsdemo       .INIT.          16 u    3   64    0    0.000    0.000 4000.00
ntpq></pre>

The host key should be displayed with `rl` in `ntpq`:

<pre>ntpq> rl
assID=0 status=c027 sync_alarm, sync_unspec, 2 events, event_clock_excptn,
version="ntpd 4.2.0a@1.1190-r Fri Apr 29 11:06:00 UTC 2005 (1)"?,
processor="i686", system="Linux/2.6.8-24.17-default", leap=11,
stratum=16, precision=-20, rootdelay=0.000, rootdispersion=0.210,
peer=0, refid=INIT,
reftime=00000000.00000000  Thu, Feb  7 2036  7:28:16.000, poll=6,
clock=0xc6ab46c3.01a1016c, state=1, offset=0.000, frequency=100.730,
noise=0.001, jitter=0.001, stability=0.000, hostname="elf",
signature="md5WithRSAEncryption", flags=0x80001, hostkey=3333113513,
cert="elf elf 0x0 3333113513"
ntpq></pre>

The details of the encryption status can be seen in the field `flash` when using the command `rl` on the desired association:

<pre>ntpq> rl &3
assID=41910 status=e000 unreach, conf, auth, no events,
srcadr=ltgpsdemo, srcport=123, dstadr=10.0.0.2, dstport=123, leap=11,
stratum=16, precision=-20, rootdelay=0.000, rootdispersion=0.000,
refid=INIT, reach=000, unreach=1, hmode=3, pmode=0, hpoll=6, ppoll=10,
flash=400 not_proventic, keyid=817784215, ttl=0, offset=0.000,
delay=0.000, dispersion=0.000, jitter=4000.000,
reftime=00000000.00000000  Thu, Feb  7 2036  7:28:16.000,
org=c6ab46b7.85c91d14  Mon, Aug 15 2005 18:52:07.522,
rec=c6ab46b7.85e7210b  Mon, Aug 15 2005 18:52:07.523,
xmt=c6ab46b7.859ae924  Mon, Aug 15 2005 18:52:07.521,
filtdelay=     0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00,
filtoffset=    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00,
filtdisp=   16000.0 16000.0 16000.0 16000.0 16000.0 16000.0 16000.0 16000.0,
hostname="ltgpsdemo", signature="md5WithRSAEncryption", flags=0x80021,
identity="ltgpsdemo"
ntpq></pre>

If everything works fine, the client should have received the server's certificate after a while. Once again, use the command `rl` to check:

<pre>ntpq> rl
(...)
signature="md5WithRSAEncryption", flags=0x80001, hostkey=3333113513,
cert="ltgpsdemo ltgpsdemo 0x3 3333112788",
cert="elf elf 0x1 3333113513"
ntpq></pre>

Again, a little later, the `rl` should display a `flash` value of zero:

<pre>ntpq> rl &3
assID=41910 status=f014 reach, conf, auth, 1 event, event_reach,
srcadr=ltgpsdemo, srcport=123, dstadr=10.0.0.2, dstport=123, leap=00,
stratum=1, precision=-18, rootdelay=0.000, rootdispersion=440.033,
refid=GPS, reach=001, unreach=3, hmode=3, pmode=4, hpoll=6, ppoll=6,
flash=00 ok, keyid=2001415940, ttl=0, offset=-0.417, delay=0.624,
dispersion=7937.503, jitter=0.001,
reftime=c6ab4708.097efe0c  Mon, Aug 15 2005 18:53:28.037,
org=c6ab473a.abebe165  Mon, Aug 15 2005 18:54:18.671,
rec=c6ab473a.ac1ba7fc  Mon, Aug 15 2005 18:54:18.672,
xmt=c6ab473a.a58b60f2  Mon, Aug 15 2005 18:54:18.646,
filtdelay=     0.62    0.00    0.00    0.00    0.00    0.00    0.00    0.00,
filtoffset=   -0.42    0.00    0.00    0.00    0.00    0.00    0.00    0.00,
filtdisp=      0.01 16000.0 16000.0 16000.0 16000.0 16000.0 16000.0 16000.0,
hostname="ltgpsdemo", signature="md5WithRSAEncryption",
valid="3333112795:3364648795", flags=0x80721, identity="ltgpsdemo"
ntpq></pre>

Then `ntpq`'s command `pe` shows the usual `refid`:

<pre>ntpq> pe
     remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
 GENERIC(1)      .GPS.            0 l   38   64    7    0.000   -1.193   0.528
 PPS(1)          .PPS.           16 l    -   64    0    0.000    0.000 4000.00
 ltgpsdemo       .GPS.            1 u   33   64    1    0.624   -0.417   0.001
ntpq></pre>

Eventually the status displays will look like this:

<pre>ntpq> rl
assID=0 status=04b7 leap_none, sync_uhf_clock, 11 events, event_clock_excptn,
version="ntpd 4.2.0a@1.1190-r Fri Apr 29 11:06:00 UTC 2005 (1)"?,
processor="i686", system="Linux/2.6.8-24.17-default", leap=00,
stratum=1, precision=-20, rootdelay=0.000, rootdispersion=3.051,
peer=41908, refid=GPS,
reftime=c6ab5610.098298cc  Mon, Aug 15 2005 19:57:36.037, poll=10,
clock=0xc6ab562d.bc703298, state=4, offset=-0.437, frequency=99.839,
noise=0.147, jitter=0.203, stability=0.173, hostname="elf",
signature="md5WithRSAEncryption", flags=0x80001, hostkey=3333113513,
refresh=3333113784, cert="elf ltgpsdemo 0x3 3333113513",
cert="ltgpsdemo ltgpsdemo 0x3 3333112788",
cert="elf elf 0x3 3333113513"
ntpq> pe
     remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
*GENERIC(1)      .GPS.            0 l   45   64  377    0.000   -0.437   0.203
 PPS(1)          .PPS.           16 l    -   64    0    0.000    0.000 4000.00
+ltgpsdemo       .PPS.            1 u  116  512  377    0.500    0.349   0.106
ntpq> as

ind assID status  conf reach auth condition  last_event cnt
===========================================================
  1 41908  9685   yes   yes  none  sys.peer  clock expt  8
  2 41909  8000   yes   yes  none    reject
  3 41910  f414   yes   yes   ok   candidat   reachable  1
ntpq> rl &3
assID=41910 status=f414 reach, conf, auth, sel_candidat, 1 event, event_reach,
srcadr=ltgpsdemo, srcport=123, dstadr=10.0.0.2, dstport=123, leap=00,
stratum=1, precision=-18, rootdelay=0.000, rootdispersion=2.289,
refid=PPS, reach=377, unreach=0, hmode=3, pmode=4, hpoll=10, ppoll=9,
flash=00 ok, keyid=3240968593, ttl=0, offset=0.349, delay=0.500,
dispersion=9.760, jitter=0.106,
reftime=c6ab55b0.fdf7e803  Mon, Aug 15 2005 19:56:00.992,
org=c6ab55c9.2f12b1b2  Mon, Aug 15 2005 19:56:25.183,
rec=c6ab55c9.2f1d4f9c  Mon, Aug 15 2005 19:56:25.184,
xmt=c6ab55c9.2edd0528  Mon, Aug 15 2005 19:56:25.183,
filtdelay=     0.55    0.62    0.50    0.54    0.54    0.58    0.54    0.56,
filtoffset=    0.11    0.26    0.35    0.36    0.38    0.42    0.43    0.40,
filtdisp=      0.00    3.84    7.71    9.65   11.55   13.46   14.45   15.42,
hostname="ltgpsdemo", signature="md5WithRSAEncryption",
valid="3333112795:3364648795", flags=0x83f21, identity="ltgpsdemo"
ntpq></pre>

* * *

#### 8.2.5. Time Errors

#### 8.2.5.1. Why does my server change time references quite frequently?

Ideally the quality of a time reference is a static feature. In reality however they can be of varying quality over time. In addition you should realize that the observed quality can have the two reasons already mentioned in [My server periodically loses synchronization](#8252-my-server-periodically-loses-synchronization).

In fact this behaviour is so frequent that it has a name of its own: _clock hopping_.

Clock hopping can be avoided by deterministic network delays, but usually you can't do anything about that. The other solution is to select a preferred time source that is used as long as it seems reasonable (even if other sources have better quality). To do this, check the documentation on configuration for the `prefer` keyword.

* * *

#### 8.2.5.2. My server periodically loses synchronization

The typical reason is that system time and the time received from a reference disagree. This can be caused by the local clock that drifts very badly and needs a significant _drift correction_, or by a virtually bad time reference. I say _virtually bad_, because the client (i.e. your server) cannot decide whether random variations in network delay or variations in the time reference itself cause that observation. Not only because of that it is recommended to have several independent time references configured.

In any case you should keep an eye on the [_reachability register_](/ntpfaq/ntp-s-trouble/#814-what-does-257-mean-as-value-for-reach), on [`delay`](/ntpfaq/ntp-s-trouble/#812-how-do-i-use-peerstats-and-loopstats) and on `dispersion` (`jitter`).

* * *

#### 8.2.5.3. Why does  my system step 0.6 seconds several times a day.

`ntpd` has problems controlling the system clock. Most likely the frequency of your timer interrupts is either too fast or too slow. Another possibility is a broken interface between `ntpd` and the operating system. In any case the problem is serious. If you suspect the first problem, you should [adjust the value of `tick`](#8261-how-do-i-set-the-correct-value-for-tick) to compensate the error.

> As adjustments to `tick` are not possible for every operating system, it's deprecated in general. The suggested solution is to use suitable hardware for time servers.

If you are using the [kernel discipline](/ntpfaq/ntp-s-algo#5161-how-will-ntp-discipline-my-clock) and you are suspecting the second problem, try to use `adjtime()` instead.

Usually `ntpd` can compensate small and even not-so-small errors, but in this case the clock is too bad to be adjusted by the NTP algorithm. Any clock error of more than one minute per day is definitely too large to be corrected by NTP.

**Example 8. Entries in logfile from ntpd**

<pre> 9 Jun 21:56:53 ntpd[116]: time reset (step) 0.706052 s
 9 Jun 23:51:04 ntpd[116]: time reset (step) 0.821992 s
10 Jun 01:57:31 ntpd[116]: time reset (step) 0.720290 s
10 Jun 03:47:25 ntpd[116]: time reset (step) 0.855968 s</pre>

This means that in the period from `9 Jun 21:56:53` (excluding) to `10 Jun 03:47:25` (including), that is during 21032 seconds, `ntpd` added 2.398250 seconds (do _not_ include the amount added during the first time step). Thus in each second 114.0286 microseconds should have been added.

You get a more accurate calculation when you do _not_ run `ntpd`. Start the measurement by synchronizing your system to a NTP server using `ntpdate -b -s -p 4 -t 0.1 NTPserver`. Complete the measurement with the same command after a few hours.

In your `/var/log/messages` (`syslog` file) file you will have 2 lines like:

<pre>Jun 9 15:00:47 NTPclient ntpdate[334]: step time server 10.0.0.1 offset 0.009416 sec
Jun 9 21:40:23 NTPclient ntpdate[515]: step time server 10.0.0.1 offset 2.718281 sec</pre>

Use this information to compute the number of microseconds to add to `tick`.

For some operating systems there is a `tickadj` utility that can be used to change the value of `tick`. See [Section 3](/ntpfaq/ntp-s-sw-clocks) and [Q: 8.2.6.1.](#8261-how-do-i-set-the-correct-value-for-tick) for a discussion on how to compute the necessary adjustment.

* * *

#### 8.2.6. Messing with broken Hardware

#### 8.2.6.1. How do I set the correct value for tick?

Here is a procedure taken from an article by Andrew Hood:

1.  Watch the value in `ntp.drift` and when it seems to stabilise continue at the next step.
2.  Run `tickadj` without any options to get the value of tick.
3.  Calculate a new value of `tick` as <code>newtick = oldtick*(1+drift/2<sup>^</sup>20)</code>.
4.  Run `tickadj` with the new value of `tick`.
5.  Restart from the beginning.

**Example 9. Correcting the value of tick**
: Here are the specific commands for Linux.

<pre>cat /etc/ntp.drift
269.799
tickadj
tick = 10000
echo 'scale=7; t=10000*(1+269.799/2^20)+0.5; scale=0; t/1' | bc
10003
tickadj 10003</pre>

The author points out that it can also be done with one single command:

<pre>echo "scale=7; `tickadj`; drift=`cat /etc/ntp.drift`; t=tick*(1+(drift)/2^20)+0.5; scale=0;t/1" | bc</kbd>
10003</pre>

**Example 10. Changing nsec_per_tick**

For the Solaris operating system the variable `nsec_per_tick` is in nanoseconds and can be modified using `adb` (thanks to Thomas Tornblom):

The command `echo 'nsec_per_tick/W 0t10000900' |adb -w -k` makes the clock faster by 90 PPM, i.e. a drift value of 97 can be reduced to 7.

For FreeBSD there are two sysctls that you can use, `machdep.i8254_freq` and `machdep.tsc_freq`. Use the one that is being used on your machine to tell FreeBSD what the frequency of your clock is. (according to [John Hay](mailto:John.Hay@mikom.csir.co.za))

Changing the value of `tick` is considered an obsolete technology by [Professor David L. Mills](mailto:mills@udel.edu), and the `tickadj` utility will probably be missing in future releases of the NTP software. Even now the latest kernel clock model silently resets the values of `tick` to the default value when a PPS signal is detected.

With this new strategy clock errors of up to 500 PPM can be corrected by the kernel clock machinery. Severely broken machines that really needed `tickadj` either should be running no NTP or an older version of the software.

* * *

#### 8.2.7. Incompatibilities

#### 8.2.7.1. How do I set the precision?

New implementations of NTP determine the precision automatically, and do not allow setting it. This is a great benefit as you do not have to determine the value prior to setting it.

The statement above is valid for the system clock and should also be valid for the reference clock drivers.

* * *

#### 8.2.8. Other

#### 8.2.8.1.ntpd periodically opens a dial-out connection. Can I avoid that?

Originally NTP has not been designed with dial-up connections in mind. Therefore it does not care very much about when to send out packets.

If you have defined an external `server` or `peer`, `ntpd` will periodically poll it. The [polling interval](/ntpfaq/ntp-s-algo/#5124-when-are-the-servers-polled) is limited by the [settings `minpoll` and `maxpoll`](/ntpfaq/ntp-s-algo#5151-what-is-the-allowed-range-for-minpoll-and-maxpoll). The virtual stability of the system clock determines whether the polling interval is reduced or increased.

However, increasing the polling interval may be a sub-optimal solution: `ntpd` will take longer for the initial synchronization, and it may become unable to catch up with the clock's drift.

For some operating systems you may be able to select what types of packets are allowed to open a dial-up connection.

The following solution has been donated by [Eric W. Bates](mailto:ericx@vineyard.net). As [chunkeey](mailto:chunkeey@web.de) pointed out, the solution will also work for Linux. The preferred directory for your additions may be `/etc/ppp/ip-up.d` and `/etc/ppp/ip-down.d`: All the scripts found there are executed.

When using `PPP` on `FreeBSD` or `NetBSD` (`Linux` kernel does not properly support `pppd`'s demand dialing; so you will have to solve this another way), I configured my `pppd` options to ignore traffic on the NTP port (snippet):

<pre>### demand dialing options
demand                          # only actually connect ppp on demand
holdoff         10              # after connection drops, wait 10 seconds before dialing again
idle            1500            # drop connection after 25 minutes of no traffic
active-filter   'not port ntp'  # don't regard ntp packets as link activity</pre>

Then in the scripts `ip-up` and `ip-down` I start and stop `xntpd` (respectively):

<pre># Start any IP activity here that should only run while the modem is connected
/usr/sbin/xntpd -p /var/run/xntpd.pid

# During boot, when pppd is first initialized a connection is always
# made (not clear why -- named?), but when xntpd is started at that
# time it does not write the PID file (not clear why -- filesystem not
# writable?); so there is a case where the PID file is not readable.

PIDFILE=/var/run/xntpd.pid
if [ -r $PIDFILE ]; then
    kill -TERM $(cat $PIDFILE)
    rm $PIDFILE
else
    # Get the process ID (do the "grep -v" to exclude this search from the result.
    kill -TERM $(ps ax | grep xntpd | grep -v grep | cut -c 1-5)
fi</pre>

This results in a `ppp0` interface which is configured at boot and dials only when there is demand for IP on its route. Upon dial-up `NTP` is started and the sync traffic does not prevent the dial-up from timing out, allowing the modem to hang up. Upon hang-up, the NTP daemon is stopped.

This has worked nicely for me for some years. I recognize that frequent connect/disconnects tend to mess with `ntpd`'s ability to sync, but my work habits are such that once the PPP is up and live, it tends to stay up for long periods. Good enough for a workstation at home.

* * *

#### 8.2.8.2. Any more Hints?

Try the suggestions in [NTP Debugging Techniques](/archives/4.2.8-series/debug/).

* * *

#### 8.2.9. Messages

This section deals with messages that are not too obvious in their meaning.

#### 8.2.9.1. Fatal Errors

#### 8.2.9.1.1. ntpq: read: connection refused

This message typically indicates that a connection could not be made because the [service is not available](#8211-how-can-i-check-that-ntpd-is-up-and-running).

* * *

#### 8.2.9.1.2. 127.0.0.1: timed out, nothing received, Request timed out

No response was received within the timeout interval. Either the network dropped the request or the answer, or it delayed it considerably, or the server did not respond. One reason for the latter would be a configuration line like this:

<pre>restrict default ignore</pre>

* * *

#### 8.2.9.1.3. ntpdate: no server suitable for synchronization found

If you see that message in your log file, the system time was not set by `ntpdate`. There are several possible reasons:

*   `ntpdate` failed to communicate through UDP port 123. This could be caused by some packet filtering or by firewalls. Unfortunately, using option `-d` to turn on debugging also changes the port `ntpdate` uses.
* If `ntpdate` works with option `-d`, you should try option `-u` to use an unpriviledged port. In any case you should check your packet filtering.

* * *

##### 8.2.9.2. Syntax Errors

#### 8.2.9.9.1. configure: keyword "precision" unknown, line ignored

The [keyword `precision`](#8271-how-do-i-set-the-precision) is no longer known by the configuration parser. Most likely you are using a configuration file intended for an old version of NTP.

* * *

##### 8.2.9.3. Warnings

#### 8.2.9.3.1. Previous time adjustment didn't complete

Using `adjtime()` your system clock can be corrected by [some amount of time](/ntpfaq/ntp-s-algo/#5161-how-will-ntp-discipline-my-clock). Normally `ntpd` will only use small amounts that can be applied within one second. However, if you disallow time steps, the last correction may be not completed yet, and `ntpd` is unable to apply another correction until the last one is finished. This is what the message says.

* * *

#### 8.2.9.4. Spurious and unexpected Messages

#### 8.2.9.4.1. sendto: Overlapped I/O operation is in progress.

The exact cause of this message is not clear, but it seems some non-NTP applications also use port `123`. The strange IP address (`192.0.0.192`) is a strong indication for this.

John Hay contributed the output of `nslookup 192.0.0.192`, namely `192.0.0.0-is-used-for-printservices-discovery----illegally.iana.net`, and [Professor David L. Mills](mailto:mills@udel.edu) stated: "Port 123 was assigned well before 1985 as per documented, but was in use probably from 1982." This means the address is not registered officially, and it should not be used. Also it seems some software for printers or printing is using that address together with NTP's port number.

Despite worrying some system administrator the message indicates no trouble. Specifically no printer is known to need a NTP server to operate, nor do printers and NTP servers harm each other.