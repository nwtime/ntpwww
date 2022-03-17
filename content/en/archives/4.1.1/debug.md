---
title: "NTP Debugging Techniques"
type: archives
noindex: true
---

![gif](/archives/pic/pogo.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

We make house calls and bring our own bugs.

* * *

### Table of Contents

* [Initial Startup](/archives/4.1.1/debug/#initial-startup)
* [Verifying Correct Operation](/archives/4.1.1/debug/#verifying-correct-operation)
* [Special Problems](/archives/4.1.1/debug/#special-problems)
* [Debugging Checklist](/archives/4.1.1/debug/#debugging-checklist)

* * *

Once the NTP software distribution has been compiled and installed and the configuration file constructed, the next step is to verify correct operation and fix any bugs that may result. Usually, the command line that starts the daemon is included in the system startup file, so it is executed only at system boot time; however, the daemon can be stopped and restarted from root at any time. Usually, no command-line arguments are required, unless special actions described in the [ntpd - Network Time Protocol (NTP) daemon](/archives/4.1.1/ntpd/) page are required. Once started, the daemon will begin sending and receiving messages, as specified in the configuration file.

* * *

#### Initial Startup

The best way to verify correct operation is using the [<code>ntpq</code> - standard NTP query program](/archives/4.1.1/ntpq/) and [<code>ntpdc</code> - special NTP query program](/archives/4.1.1/ntpdc/) utility programs, either on the server itself or from another machine elsewhere in the network. The <code>ntpq</code> program implements the management functions specified in the NTP specification [RFC-1305, Appendix A](/reflib/rfc/rfc1305/rfc1305c.pdf). The <code>ntpdc</code> program implements additional functions not provided in the standard. Both programs can be used to inspect the state variables defined in the specification and, in the case of <code>ntpdc</code>, additional ones intended for serious debugging. In addition, the <code>ntpdc</code> program can be used to selectively reconfigure and enable or disable some functions while the daemon is running.

In extreme cases with elusive bugs, the daemon can operate in two modes, depending on the presence of the <code>-d</code> command-line debug switch. If not present, the daemon detaches from the controlling terminal and proceeds autonomously. If one or more <code>-d</code> switches are present, the daemon does not detach and generates special output useful for debugging. In general, interpretation of this output requires reference to the sources. However, a single <code>-d</code> does produce only mildly cryptic output and can be very useful in finding problems with configuration and network troubles. With a little experience, the volume of output can be reduced by piping the output to <code>grep</code> and specifying the keyword of the trace you want to see.

Some problems are immediately apparent when the daemon first starts running. The most common of these are the lack of a UDP port for NTP (123) in the Unix <code>/etc/services</code> file (or equivalent in some systems). Note that NTP does not use TCP in any form. Other problems are apparent in the system log file. The log file should show the startup banner, some cryptic initialization data and the computed precision value. The next most common problem is incorrect DNS names. Check that each DNS name used in the configuration file exists and that the address responds to the Unix <code>ping</code> command.

When first started, the daemon normally polls the servers listed in the configuration file at 64-s intervals. In order to allow a sufficient number of samples for the NTP algorithms to reliably discriminate between truechimer servers and possible falsetickers, at least four valid messages from at least one server or peer listed in the configuration file is required before the daemon can set the clock. However, if the difference between the client time and server time is greater than the panic threshold, which defaults to 1000 s, the daemon sends a message to the system log and shuts down without setting the clock. It is necessary to set the local clock to within the panic threshold first, either manually by eyeball and wristwatch and the Unix <code>date</code> command, or by the <code>ntpdate</code> or <code>ntpd -q</code> commands. The panic threshold can be changed by the <code>tinker panic</code> command discribed on the [Miscellaneous Options](/archives/4.1.1/miscopt/) page. The panic threshold can be disabled entirely by the <code>-g</code> command line option described on the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/archives/4.1.1/ntpd/) page.

If the difference between local time and server time is less than the panic threshold but greater than the step threshold, which defaults to 125 ms, the daemon will perform a step adjustment; otherwise, it will gradually slew the clock to the nominal time. The step threshold can be changed by the <code>tinker step</code> command described on the [Miscellaneous Options](/archives/4.1.1/miscopt/) page. The step threshold can be disabled entirely by the <code>-x</code> command line option described on the [ntpd - Network Time Protocol (NTP) daemon](/archives/4.1.1/ntpd/) page. In this case the clock will never be stepped; however, users should understand the implications for doing this in a distributed data network where all processing must be tightly synchronized.  See the [NTP Timescale and Leap Seconds](/reflib/leap/) page for further information. If a step adjustment is made, the clock discipline algorithm will start all over again, requiring another round of at least four messages as before. This is necessary so that all servers and peers operate on the same set of time values.

The clock discipline algorithm is designed to avoid large noise spikes that might occur on a congested network or access line. If an offset sample exceeds the step threshold, it is ignored and a timer started. If a later sample is below the step threshold, the counter is reset. However, if the counter is greater than the stepout interval, which defaults to 900 s, the next sample will step the time as directed. The stepout threshold can be changed by the <code>tinker stepout</code> command discribed on the [Miscellaneous Options](/archives/4.1.1/miscopt/) page.

If, as discussed later on this page, for some reason the hardware clock oscillator frequency error is very large, the time errors upon first startup of the daemon may increase over time until exceeding the step threshold, which requires another step correction. However, due to provisions that reduce vulnerability to noise spikes, the second correction will not be done until after the stepout threshold. When the frequency error is very large, it may take a number of cycles like this until converging on the nominal frequency correction. After this, the correction is written to the  <code>ntp.drift</code> file, which is read upon subsequent restarts, so the herky-jerky cycles should not recur.

* * *

#### Verifying Correct Operation

After starting the daemon, run the <code>ntpq</code> program using the <code>-n</code> switch, which will avoid possible distractions due to name resolution problems. Use the <code>pe</code> command to display a billboard showing the status of configured peers and possibly other clients poking the daemon. After operating for a few minutes, the display should be something like:

<pre>ntpq> pe
     remote      refid       st t when poll reach delay offset jitter
=====================================================================
-isipc6.cairn.ne .GPS1.        1 u  18  64  377  65.592 -5.891  0.044
+saicpc-isiepc2. pogo.udel.edu 2 u 241 128  370  10.477 -0.117  0.067
+uclpc.cairn.net pogo.udel.edu 2 u  37  64  177 212.111 -0.551  0.187
*pogo.udel.edu   .GPS1.        1 u  95 128  377   0.607  0.123  0.027
</pre>

The host names or addresses shown in the <code>remote</code> column correspond to the server and peer entries listed in the configuration file; however, the DNS names might not agree if the names listed are not the canonical DNS names. IPv4 addresses are shown in dotted quad notation, while IPv6 addresses are shown alarmingly. The <code>refid</code> column shows the current source of synchronization, while the <code>st</code> column reveals the stratum, <code>t</code> the type (<code>u</code> = unicast, <code>m</code> = multicast, <code>l</code> = local, <code>-</code> = don't know), and <code>poll</code> the poll interval in seconds. The <code>when</code> column shows the time since the peer was last heard in seconds, while the <code>reach</code> column shows the status of the reachability register (see RFC-1305) in octal. The remaining entries show the latest delay, offset and jitter in milliseconds. Note that in NTP Version 4 what used to be the <code>dispersion</code> column has been replaced by the <code>jitter</code> column.

The tattletale symbol at the left margin displays the synchronization status of each peer. The currently selected peer is marked `*`, while additional peers designated acceptable for synchronization are marked `+`. Peers marked `*` and `+` are included in the weighted average computation to set the local clock; the data produced by peers marked with other symbols are discarded. See the <code>ntpq</code> page for the meaning of these symbols.

Additional details for each peer separately can be determined by the following procedure. First, use the <code>as</code> command to display an index of association identifiers, such as

<pre>ntpq> as
ind assID status  conf reach auth condition  last_event cnt
===========================================================
  1 50252  f314   yes   yes   ok    outlyer   reachable  1
  2 50253  f414   yes   yes   ok   candidat   reachable  1
  3 50254  f414   yes   yes   ok   candidat   reachable  1
  4 50255  f614   yes   yes   ok   sys.peer   reachable  1
</pre>

Each line in this billboard is associated with the corresponding line in the <code>pe</code> billboard above. The <code>assID</code> shows the unique identifier for each mobilized association, while the <code>status</code> column shows the peer status word in hex, as defined in the NTP specification. Next, use the <code>rv</code> command and the respective <code>assID</code> identifier to display a detailed synopsis for the selected peer, such as

<pre>ntpq> rv 50253
status=f414 reach, conf, auth, sel_candidat, 1 event, event_reach,
srcadr=saicpc-isiepc2.cairn.net, srcport=123, dstadr=140.173.1.46,
dstport=123, keyid=3816249004, stratum=2, precision=-27,
rootdelay=10.925, rootdispersion=12.848, refid=pogo.udel.edu,
reftime=bd11b225.133e1437  Sat, Jul  8 2000 13:59:01.075, delay=10.550,
offset=-1.357, jitter=0.074, dispersion=1.444, reach=377, valid=7,
hmode=1, pmode=1, hpoll=6, ppoll=7, leap=00, flash=00 ok,
org=bd11b23c.01385836  Sat, Jul  8 2000 13:59:24.004,
rec=bd11b23c.02dc8fb8  Sat, Jul  8 2000 13:59:24.011,
xmt=bd11b21a.ac34c1a8  Sat, Jul  8 2000 13:58:50.672,
filtdelay=   10.45  10.50  10.63  10.40  10.48  10.43  10.49  11.26,
filtoffset=  -1.18  -1.26  -1.26  -1.35  -1.35  -1.42  -1.54  -1.81,
filtdisp=     0.51   1.47   2.46   3.45   4.40   5.34   6.33   7.28,
hostname="miro.time.saic.com", signature=md5WithRSAEncryption, flags=0x83f01, initsequence=61, initkey=0x287b649c,
timestamp=3172053041
</pre>

A detailed explanation of the fields in this billboard are beyond the scope of this discussion; however, most variables defined in the NTP Version 3 specification RFC-1305 are available along with others defined for NTP Version 4. This particular example was chosen to illustrate probably the most complex configuration involving symmetric modes and public-key cryptography. As the result of debugging experience, the names and values of these variables may change from time to time. An explanation of the current set is on the <code>ntpq</code> page.

A useful indicator of miscellaneous problems is the <code>flash</code> value, which reveals the state of the various sanity tests on incoming packets. There are currently eleven bits, one for each test, numbered from the right, which is for test 1. If the test fails, the corresponding bit is set to one and zero otherwise. If any bit is set following each processing step, the packet is discarded. The meaning of each test is described on the <code>ntpq</code> page.

The three lines identified as <code>filtdelay</code>, <code>filtoffset</code> and <code>filtdisp</code> reveal the roundtrip delay, clock offset and dispersion for each of the last eight measurement rounds, all in milliseconds. Note that the dispersion, which is an estimate of the error, increases as the age of the sample increases. From these data, it is usually possible to determine the incidence of severe packet loss, network congestion, and unstable local clock oscillators. There are no hard and fast rules here, since every case is unique; however, if one or more of the rounds show large values or change radically from one round to another, the network is probably congested or lossy.

Once the daemon has set the local clock, it will continuously track the discrepancy between local time and NTP time and adjust the local clock accordingly. There are two components of this adjustment, time and frequency. These adjustments are automatically determined by the clock discipline algorithm, which functions as a hybrid phase/frequency feedback loop. The behavior of this algorithm is carefully controlled to minimize residual errors due to network jitter and frequency variations of the local clock hardware oscillator that normally occur in practice. However, when started for the first time, the algorithm may take some time to converge on the intrinsic frequency error of the host machine.

The state of the local clock itself can be determined using the <code>rv</code> command (without the argument), such as

<pre>ntpq> rv
status=0644 leap_none, sync_ntp, 4 events, event_peer/strat_chg,
version="ntpd 4.0.99j4-r Fri Jul  7 23:38:17 GMT 2000 (1)",
processor="i386", system="FreeBSD3.4-RELEASE", leap=00, stratum=2,
precision=-27, rootdelay=0.552, rootdispersion=12.532, peer=50255,
refid=pogo.udel.edu,
reftime=bd11b220.ac89f40a  Sat, Jul  8 2000 13:58:56.673, poll=6,
clock=bd11b225.ee201472  Sat, Jul  8 2000 13:59:01.930, state=4,
phase=0.179, frequency=44.298, jitter=0.022, stability=0.001,
hostname="barnstable.udel.edu", publickey=3171372095, params=3171372095,
refresh=3172016539
</pre>

An explanation about most of these variables is in the RFC-1305 specification. The most useful ones include <code>clock</code>, which shows when the clock was last adjusted, and <code>reftime</code>, which shows when the server clock of <code>refid</code> was last adjusted. The <code>version</code>, <code>processor</code> and <code>system</code> values are very helpful when included in bug reports. The mean millisecond time offset (<code>phase</code>) and deviation (<code>jitter</code>) monitor the clock quality, while the mean PPM frequency offset (<code>frequency</code>) and deviation (<code>stability</code>) monitor the clock stability and serve as a useful diagnostic tool. It has been the experience of NTP operators over the years that these data represent useful environment and hardware alarms. If the motherboard fan freezes up or some hardware bit sticks, the system clock is usually the first to notice it.

Among the new variables added for NTP Version 4 are the <code>hostname</code>, <code>publickey</code>, <code>params</code>, and <code>refresh</code>, which are used for the Autokey public-key cryptography described on the [Authentication Options](/archives/4.1.1/authopt/) page. The values show the filestamps, in NTP seconds, that the associated values were created. These are useful in diagnosing problems with cryptographic key consistency and ordering principles.

When nothing seems to happen in the <code>pe</code> billboard after some minutes, there may be a network problem. One common network problem is an access controlled router on the path to the selected peer or an access controlled server using methods described on the [Access Control Options](/archives/4.1.1/accopt/) page. Another common problem is that the server is down or running in unsynchronized mode due to a local problem. Use the <code>ntpq</code> program to spy on the server variables in the same way you can spy on your own.

Normally, the daemon will adjust the local clock in small steps in such a way that system and user programs are unaware of its operation. The adjustment process operates continuously unless the apparent clock error exceeds the step threshold for a period longer than the stepout threshold, which for most Internet paths is a very rare event. If the event is simply an outlyer due to an occasional network delay spike, the correction is simply discarded; however, if the apparent time error persists for longer than the stepout threshold of about 17 minutes, the local clock is stepped or slewed to the new value as directed. This behavior is designed to resist errors due to severely congested network paths, as well as errors due to confused radio clocks upon the epoch of a leap second.

* * *

#### Special Problems

The frequency tolerance of computer clock oscillators can vary widely, which can put a strain on the daemon's ability to compensate for the intrinsic frequency error. While the daemon can handle frequency errors up to 500 parts-per-million (PPM), or 43 seconds per day, values much above 100 PPM reduce the headroom and increase the time to learn the particular value and record it in the <code>ntp.drift</code> file. In extreme cases before the particular oscillator frequency error has been determined, the residual system time offsets can sweep from one extreme to the other of the 128-ms tracking window only for the behavior to repeat at 900-s intervals until the measurements have converged.

In order to determine if excessive frequency error is a problem, observe the nominal <code>filtoffset</code> values for a number of rounds and divide by the poll interval. If the result is something approaching 500 PPM, there is a good chance that NTP will not work properly until the frequency error is reduced by some means. A common cause is the hardware time-of-year (TOY) clock chip, which must be disabled when NTP disciplines the software clock. For some systems this can be done using the [<code>tickadj</code>](/archives/4.1.1/tickadj/) utility and the <code>-s</code> command line argument. For other systems this can be done using a command in the system startup file.

If the TOY chip is not the cause, the problem may be that the hardware clock frequency may simply be too slow or two fast. In some systems this might require tweaking a trimmer capacitor on the motherboard. For other systems the clock frequency can be adjusted in increments of 100 PPM using the <code>tickadj</code> utility and the <code>-t</code> command line argument. Note that the <code>tickadj</code> alters certain kernel variables and, while the utility attempts to figure out an acceptable way to do this, there are many cases where <code>tickadj</code> is incompatible with a running kernel.

Provisions are included in <code>ntpd</code> for access controls which deflect unwanted traffic from selected hosts or networks. The controls described on the [Access Control Options](/archives/4.1.1/accopt/) include detailed packet filter operations based on source address and address mask. Normally, filtered packets are dropped without notice other than to increment tally counters. However, the server can configure to generate what is called a kiss-of-death (KOD) packet and send to the client. In case of outright access denied, the KOD is the response to the first client packet. In this case the client association is permanently disabled and the access denied bit (test 4) is set in the flash peer variable mentioned above and a message is sent to the system log.

The access control provisions include a limit on the packet rate from a host or network. If an incoming packet exceeds the limit, it is dropped and a KOD sent to the source. If this occurs after the client association has synchronized, the association is not disabled, but a message is sent to the system log. See the [Access Control Options](/archives/4.1.1/accopt/) page for further information.

In some reported scenarios an access line may show low to moderate network delays during some period of the day and moderate to high delays during other periods. Often the delay on one direction of transmission dominates, which can result in large time offset errors, sometimes in the range up to a few seconds. It is not usually convenient to run <code>ntpd</code> throughout the day in such scenarios, since this could result in several time steps, especially if the condition persists for greater than the stepout threshold.

The recommended approach in such scenarios is first to calibrate the local clock frequency error by running <code>ntpd</code> in continuous mode during the quiet interval and let it write the frequency to the <code>ntp.drift</code> file. Then, run <code>ntpd -q</code> from a cron job each day at some time in the quiet interval. In systems with the nanokernel or microkernel performance enhancements, including Solaris, Tru64, Linux and FreeBSD, the kernel continuously disciplines the frequency so that the residual correction produced by <code>ntpd</code> is usually less than a few milliseconds.

#### Debugging Checklist

If the <code>ntpq</code> or <code>ntpdc</code> programs do not show that messages are being received by the daemon or that received messages do not result in correct synchronization, verify the following:

1.  Verify the <code>/etc/services</code> file host machine is configured to accept UDP packets on the NTP port 123. NTP is specifically designed to use UDP and does not respond to TCP.
2.  Check the system log for <code>ntpd</code> messages about configuration errors, name-lookup failures or initialization problems.
3.  Verify using <code>ping</code> or other utility that packets actually do make the round trip between the client and server. Verify using <code>nslookup</code> or other utility that the DNS server names do exist and resolve to valid Internet addresses.
4.  Using the <code>ntpdc</code> program, verify that the packets received and packets sent counters are incrementing. If the sent counter does not increment and the configuration file includes configured servers, something may be wrong in the host network or interface configuration. If this counter does increment, but the received counter does not increment, something may be wrong in the network or the server NTP daemon may not be running or the server itself may be down or not responding.
5.  If both the sent and received counters do increment, but the <code>reach</code> values in the <code>pe</code> billboard with <code>ntpq</code> continues to show zero, received packets are probably being discarded for some reason. If this is the case, the cause should be evident from the <code>flash</code> variable as discussed above and on the <code>ntpq</code> page.
6.  If the <code>reach</code> values in the <code>pe</code> billboard show the servers are alive and responding, note the tattletale symbols at the left margin, which indicate the status of each server resulting from the various grooming and mitigation algorithms. The interpretation of these symbols is discussed on the <code>ntpq</code> page. After a few minutes of operation, one or another of the reachable server candidates should show a \* tattletale symbol. If this doesn't happen, the intersection algorithm, which classifies the servers as truechimers or falsetickers, may be unable to find a majority of truechimers among the server population.
7.  If all else fails, see the FAQ and/or the discussion and briefings at [Network Time Synchronization Project](/reflib/ntp/).