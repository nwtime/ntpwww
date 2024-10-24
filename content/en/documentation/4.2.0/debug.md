---
title: "NTP Debugging Techniques"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/pogo.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

We make house calls and bring our own bugs.

* * *

### Table of Contents

* [Initial Startup](/documentation/4.2.0/debug/#initial-startup)
* [Verifying Correct Operation](/documentation/4.2.0/debug/#verifying-correct-operation)
* [Large Frequency Errors](/documentation/4.2.0/debug/#large-frequency-errors)
* [Access Controls](/documentation/4.2.0/debug/#access-controls)
* [Large Delay Variations](/documentation/4.2.0/debug/#large-delay-variations)
* [Cryptographic Authentication](/documentation/4.2.0/debug/#cryptographic-authentication)
* [Debugging Checklist](/documentation/4.2.0/debug/#debugging-checklist)

* * *

Once the NTP software distribution has been compiled and installed and the configuration file constructed, the next step is to verify correct operation and fix any bugs that may result. Usually, the command line that starts the daemon is included in the system startup file, so it is executed only at system boot time; however, the daemon can be stopped and restarted from root at any time. Usually, no command-line arguments are required, unless special actions described in the [ntpd - Network Time Protocol (NTP) daemon](/documentation/4.2.0/ntpd/) page are required. Once started, the daemon will begin sending and receiving messages, as specified in the configuration file.

* * *

#### Initial Startup

When started for the first time, the frequency file, usually called <code>ntp.drift</code>, has not yet been created. The daemon switches to a special training routine designed to quickly determine the system clock frequency offset of the particular machine. The routine first measures the current clock offset and sets the clock, then continues for up to twenty minutes before measuring the clock offset, which might involve setting the clock again. The two measurements are used to compute the initial frequency offset and the daemon continues in regular operation, during which the frequency offset is continuously updated. Once each hour the daemon writes the current frequency offset to the <code>ntp.drift</code> file. When restarted after that, the daemon reads the frequency offset from the <code>ntp.drift</code> file and avoids the training routine.

Note that the daemon requires at least four packet exchanges when first started in any case. This is required in order for the mitigation algorithms to insure valid and accurate measurements and defend against network delay spikes and accidental or malicious errors induced by the servers selected in the configuration file. It normally takes less than four minutes to set the clock when first started, but this can be reduced to less than ten seconds with the <code>iburst</code> configuration option.

The best way to verify correct operation is using the [<code>ntpq</code> - standard NTP query program](/documentation/4.2.0/ntpq/) and [<code>ntpdc</code> - special NTP query program](/documentation/4.2.0/ntpdc/) utility programs, either on the server itself or from another machine elsewhere in the network. The <code>ntpq</code> program implements the management functions specified in the NTP specification [RFC-1305, Appendix A](/reflib/rfc/rfc1305/rfc1305c.pdf). The <code>ntpdc</code> program implements additional functions not provided in the standard. Both programs can be used to inspect the state variables defined in the specification and, in the case of <code>ntpdc</code>, additional ones intended for serious debugging. In addition, the <code>ntpdc</code> program can be used to selectively reconfigure and enable or disable some functions while the daemon is running.

In extreme cases with elusive bugs, the daemon can operate in two modes, depending on the presence of the <code>-d</code> command-line debug switch. If not present, the daemon detaches from the controlling terminal and proceeds autonomously. If one or more <code>-d</code> switches are present, the daemon does not detach and generates special output useful for debugging. In general, interpretation of this output requires reference to the sources. However, a single <code>-d</code> does produce only mildly cryptic output and can be very useful in finding problems with configuration and network troubles. With a little experience, the volume of output can be reduced by piping the output to <code>grep</code> and specifying the keyword of the trace you want to see.

Some problems are immediately apparent when the daemon first starts running. The most common of these are the lack of a UDP port for NTP (123) in the Unix <code>/etc/services</code> file (or equivalent in some systems).
> **Note that NTP does not use TCP in any form. Also note that NTP requires 123 for both source and destination ports.** These facts should be pointed out to firewall administrators.

Other problems are apparent in the system log, which ordinarily shows the startup banner, some cryptic initialization data and the computed precision value. Error messages at startup and during regular operation are sent to the system log. In real emergencies the daemon will sent a terminal error message to the system log and then cease operation.

The next most common problem is incorrect DNS names. Check that each DNS name used in the configuration file exists and that the address responds to the Unix <code>ping</code> command. The Unix <code>traceroute</code> or Windows <code>tracert</code> utility can be used to verify a partial or complete path exists. Most problems reported to the [NTP questions mailing list](https://lists.ntp.org/questions/) are not NTP problems, but problems with the network or firewall configuration.

When first started, the daemon polls the servers listed in the configuration file at 64-s intervals. In order to allow a sufficient number of samples for the NTP algorithms to reliably discriminate between truechimer servers and possible falsetickers, at least four valid messages from at least one server or peer listed in the configuration file is required before the daemon can set the clock. However, if the difference between the client time and server time is greater than the panic threshold, which defaults to 1000 s, the daemon sends a message to the system log and shuts down without setting the clock. It is necessary to set the local clock to within the panic threshold first, either manually by eyeball and wristwatch and the Unix <code>date</code> command, or by the <code>ntpdate</code> or <code>ntpd -q</code> commands. The panic threshold can be changed by the <code>tinker panic</code> command discribed on the [Miscellaneous Options](/documentation/4.2.0/miscopt/) page. The panic threshold can be disabled for the first measurement by the <code>-g</code> command line option described on the [<code>ntpd</code> - Network Time Protocol (NTP) daemon](/documentation/4.2.0/ntpd/) page.

If the difference between local time and server time is less than the panic threshold but greater than the step threshold, which defaults to 128 ms, the daemon will perform a step adjustment; otherwise, it will gradually slew the clock to the nominal time. Step adjustments are extremely rare in ordinary operation, usually as the result of reboot or hardware failure. The step threshold can be changed to 300 s using the <code>-x</code> command line option described on the <code>ntpd</code> page. This is usually sufficient to avoid a step after reboot or when the operator has set the system clock to within five minutes by eyeball-and-wristwatch. In extreme cases the step threshold can be changed by the <code>tinker step</code> command discribed on the [Miscellaneous Options](/documentation/4.2.0/miscopt/) page. If set to zero, the clock will never be stepped; however, users should understand the implications for doing this in a distributed data network where all processing must be tightly synchronized. See the [NTP Timescale and Leap Seconds](/reflib/leap/) page for further information. If a step adjustment is made, the clock discipline algorithm will start all over again, requiring another round of at least four messages as before. This is necessary so that all servers and peers operate on the same set of time values.

The clock discipline algorithm is designed to avoid large noise spikes that might occur on a congested network or access line. If an offset sample exceeds the step threshold, it is ignored and a timer started. If a later sample is below the step threshold, the counter is reset and operation continues normally. However, if the counter is greater than the stepout interval, which defaults to 900 s, the next sample will step the time as directed. The stepout threshold can be changed by the <code>tinker stepout</code> command discribed on the Miscellaneous Options page.

If for some reason the hardware clock oscillator frequency error is very large, say over 400 PPM, the time offset when the daemon is started for the first time may increase over time until exceeding the step threshold, which requires a frequency adjustment and another step correction. However, due to provisions that reduce vulnerability to noise spikes, the second correction will not be done until after the stepout threshold. When the frequency error is very large, it may take a number of cycles like this until converging to the nominal frequency correction and writing the <code>ntp.drift</code> file. If the frequency error is over 500 PPM, convergence will never occur and occasional step adjustments will occur indefinitely.

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

The host names or addresses shown in the <code>remote</code> column correspond to the server and peer entries listed in the configuration file; however, the DNS names might not agree if the names listed are not the canonical DNS names. IPv4 addresses are shown in dotted quad notation, while IPv6 addresses are shown alarmingly. The <code>refid</code> column shows the current source of synchronization, while the <code>st</code> column reveals the stratum, <code>t</code> the type (<code>u</code> = unicast, <code>m</code> = multicast, <code>l</code> = local, <code>-</code> = don't know), and <code>poll</code> the poll interval in seconds. The <code>when</code> column shows the time since the peer was last heard in seconds, while the <code>reach</code> column shows the status of the reachability register (see RFC-1305) in octal. The remaining entries show the latest delay, offset and jitter in milliseconds. 
> Note that in NTP Version 4 what used to be the <code>dispersion</code> column has been replaced by the <code>jitter</code> column.

As per the NTP specification RFC-1305, when the <code>stratum</code> is between 0 and 15 for a NTP server, the <code>refid</code> field shows the server DNS name or, if not found, the IP address in dotted-quad. When the <code>stratum</code> is any value for a reference clock, this field shows the identification string assigned to the clock. However, until the client has synchronized to a server, or when the <code>stratum</code> for a NTP server is 0 (appears as 16 in the billboards), the status cannot be determined. As a help in debugging, the <code>refid</code> field is set to a four-character string called the kiss code. The current kiss codes are as follows.

##### Peer Kiss Codes

<code>**ACST**</code>

: The association belongs to a anycast server.

<code>**AUTH**</code>

: Server authentication failed. Please wait while the association is restarted.

<code>**AUTO**</code>

: Autokey sequence failed. Please wait while the association is restarted.

<code>**BCST**</code>

: The association belongs to a broadcast server.

<code>**CRYP**</code>

: Cryptographic authentication or identification failed. The details should be in the system log file or the <code>cryptostats</code> statistics file, if configured. No further messages will be sent to the server.

<code>**DENY**</code>

: Access denied by remote server. No further messages will be sent to the server.

<code>**DROP**</code>

: Lost peer in symmetric mode. Please wait while the association is restarted.

<code>**RSTR**</code>

: Access denied due to local policy. No further messages will be sent to the server.

<code>**INIT**</code>

: The association has not yet synchronized for the first time.

<code>**MCST**</code>

: The association belongs to a manycast server.

<code>**NKEY**</code>

: No key found. Either the key was never installed or is not trusted.

<code>**RATE**</code>

: Rate exceeded. The server has temporarily denied access because the client exceeded the rate threshold.

<code>**RMOT**</code>

: Somebody is tinkering with the association from a remote host running <code>ntpdc</code>. Not to worry unless some rascal has stolen your keys.

<code>**STEP**</code>

: A step change in system time has occurred, but the association has not yet resynchronized.

##### System Kiss Codes

<code>**INIT**</code>

: The system clock has not yet synchronized for the first time.

<code>**STEP**</code>

: A step change in system time has occurred, but the system clock has not yet resynchronized.

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

A detailed explanation of the fields in this billboard are beyond the scope of this discussion; however, most variables defined in the NTP Version 3 specification RFC-1305 are available along with others defined for NTPv4 on the <code>ntpq</code> page. This particular example was chosen to illustrate probably the most complex configuration involving symmetric modes and public-key cryptography. As the result of debugging experience, the names and values of these variables may change from time to time.

A useful indicator of miscellaneous problems is the <code>flash</code> value, which reveals the state of the various sanity tests on incoming packets. There are currently 12 bits, one for each test, numbered from the right, which is for test 1. If the test fails, the corresponding bit is set to one and zero otherwise. If any bit is set following each processing step, the packet is discarded. The meaning of each test is described on the <code>ntpq</code> page.

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
hostname="barnstable.udel.edu", signature=md5WithRSAEncryption,
flags=0x80011, hostkey=3171372095, refresh=3172016539
cert="grundoon.udel.edu grundoon.udel.edu 0x3 3233600829"
cert="whimsy.udel.edu whimsy.udel.edu 0x5 3233682156"
</pre>

An explanation about most of these variables is in the RFC-1305 specification. The most useful ones include <code>clock</code>, which shows when the clock was last adjusted, and <code>reftime</code>, which shows when the server clock of <code>refid</code> was last adjusted. The <code>version</code>, <code>processor</code> and <code>system</code> values are very helpful when included in bug reports. The mean millisecond time offset (<code>phase</code>) and deviation (<code>jitter</code>) monitor the clock quality, while the mean PPM frequency offset (<code>frequency</code>) and deviation (<code>stability</code>) monitor the clock stability and serve as a useful diagnostic tool. It has been the experience of NTP operators over the years that these data represent useful environment and hardware alarms. If the motherboard fan freezes up or some hardware bit sticks, the system clock is usually the first to notice it.

Among the new variables added for NTP Version 4 are the <code>hostname</code>, <code>signature</code>, <code>flags, hostkey, refresh</code> and <code>cert</code>, which are used for the Autokey public-key cryptography described on the [Authentication Options](/documentation/4.2.0/authopt/) page. The numeric values show the filestamps, in NTP seconds, that the associated media files were created. These are useful in diagnosing problems with cryptographic key consistency and ordering principles.

When nothing seems to happen in the <code>pe</code> billboard after some minutes, there may be a network problem. One common network problem is an access controlled router on the path to the selected peer or an access controlled server using methods described on the [Access Control Options](/documentation/4.2.0/accopt/) page. Another common problem is that the server is down or running in unsynchronized mode due to a local problem. Use the <code>ntpq</code> program to spy on the server variables in the same way you can spy on your own.

Normally, the daemon will adjust the local clock in small steps in such a way that system and user programs are unaware of its operation. The adjustment process operates continuously unless the apparent clock error exceeds the step threshold for a period longer than the stepout threshold, which for most Internet paths is a very rare event. If the event is simply an outlyer due to an occasional network delay spike, the correction is simply discarded; however, if the apparent time error persists for longer than the stepout threshold of about 17 minutes, the local clock is stepped or slewed to the new value as directed. This behavior is designed to resist errors due to severely congested network paths, as well as errors due to confused radio clocks upon the epoch of a leap second.

* * *

#### Large Frequency Errors

The frequency tolerance of computer clock oscillators can vary widely, which can put a strain on the daemon's ability to compensate for the intrinsic frequency error. While the daemon can handle frequency errors up to 500 parts-per-million (PPM), or 43 seconds per day, values much above 100 PPM reduce the headroom and increase the time to learn the particular value and record it in the <code>ntp.drift</code> file. In extreme cases before the particular oscillator frequency error has been determined, the residual system time offsets can sweep from one extreme to the other of the 128-ms tracking window only for the behavior to repeat at 900-s intervals until the measurements have converged.

In order to determine if excessive frequency error is a problem, observe the nominal <code>filtoffset</code> values for a number of rounds and divide by the poll interval. If the result is something approaching 500 PPM, there is a good chance that NTP will not work properly until the frequency error is reduced by some means. A common cause is the hardware time-of-year (TOY) clock chip, which must be disabled when NTP disciplines the software clock. For some systems this can be done using the [<code>tickadj</code>](/documentation/4.2.0/tickadj/) utility and the <code>-s</code> command line argument. For other systems this can be done using a command in the system startup file.

If the TOY chip is not the cause, the problem may be that the hardware clock frequency may simply be too slow or two fast. In some systems this might require tweaking a trimmer capacitor on the motherboard. For other systems the clock frequency can be adjusted in increments of 100 PPM using the <code>tickadj</code> utility and the <code>-t</code> command line argument. Note that the <code>tickadj</code> alters certain kernel variables and, while the utility attempts to figure out an acceptable way to do this, there are many cases where <code>tickadj</code> is incompatible with a running kernel.

#### Access Controls

Provisions are included in <code>ntpd</code> for access controls which deflect unwanted traffic from selected hosts or networks. The controls described on the [Access Control Options](/documentation/4.2.0/accopt/) include detailed packet filter operations based on source address and address mask. Normally, filtered packets are dropped without notice other than to increment tally counters. However, the server can be configured to send a "kiss-o'-death" (KOD) packet to the client either when explicitly configured or when cryptographic authentication fails for some reason. The client association is permanently disabled, the access denied bit (TEST4) is set in the flash variable and a message is sent to the system log.

The access control provisions include a limit on the packet rate from a host or network. If an incoming packet exceeds the limit, it is dropped and a KOD sent to the source. If this occurs after the client association has synchronized, the association is not disabled, but a message is sent to the system log. See the [Access Control Options](/documentation/4.2.0/accopt/) page for further information.

#### Large Delay Variations

In some reported scenarios an access line may show low to moderate network delays during some period of the day and moderate to high delays during other periods. Often the delay on one direction of transmission dominates, which can result in large time offset errors, sometimes in the range up to a few seconds. It is not usually convenient to run <code>ntpd</code> throughout the day in such scenarios, since this could result in several time steps, especially if the condition persists for greater than the stepout threshold.

Specific provisions have been built into <code>ntpd</code> to cope with these problems. The scheme is called "huff-'n-puff and is described on the [Miscellaneous Options](/documentation/4.2.0/miscopt/) page. An alternative approach in such scenarios is first to calibrate the local clock frequency error by running <code>ntpd</code> in continuous mode during the quiet interval and let it write the frequency to the <code>ntp.drift</code> file. Then, run <code>ntpd -q</code> from a cron job each day at some time in the quiet interval. In systems with the nanokernel or microkernel performance enhancements, including Solaris, Tru64, Linux and FreeBSD, the kernel continuously disciplines the frequency so that the residual correction produced by <code>ntpd</code> is usually less than a few milliseconds.

#### Cryptographic Authentication

Reliable source authentication requires the use of symmetric key or public key cryptography, as described on the [Authentication Options](/documentation/4.2.0/authopt/) page. In symmetric key cryptography servers and clients share session keys contained in a secret key file In public key cryptography, which requires the OpenSSL software library, the server has a private key, never shared, and a public key with unrestricted distribution. The cryptographic media required are produced by the [<code>ntp-keygen</code>](/documentation/4.2.0/keygen/) program.

Problems with symmetric key authentication are usually due to mismatched keys or improper use of the <code>trustedkey</code> command. A simple way to check for problems is to use the trace facility, which is enabled using the <code>ntpd -d</code> command line. As each packet is received a trace line is displayed which shows the authentication status in the <code>auth</code> field. A status of 1 indicates the packet was successful authenticated; otherwise it has failed.

A common misconception is the implication of the <code>auth</code> bit in the <code>enable</code> and <code>disable</code> commands. **This bit does not affect authentication in any way other than to enable or disable mobilization of a new persistent association in broadcast/multicast client, manycast client or symmetric passive modes.** If enabled, which is the default, these associations require authentication; if not, an association is mobilized even if not authenticated. Users are cautioned that running with authentication disabled is very dangerous, since an intruder can easily strike up an association and inject false time values.

Public key cryptography is supported in NTPv4 using the Autokey protocol, which is described [here](/reflib/brief/atirp2/atirp2.pdf). Development of this protocol is mature and the <code>ntpd</code> implementation is basically complete. Autokey version 2, which is the latest and current version, includes provisions to hike certificate trails, operate as certificate authorities and verify identity using challenge/response identification schemes. Further details of the protocol are on the [Authentication Options](/documentation/4.2.0/authopt/) page. Common problems with configuration and key generation are mismatched key files, broken links and missing or broken random seed file.

As in the symmetric key cryptography case, the trace facility is a good way to verify correct operation. A statistics file <code>cryptostats</code> records protocol transactions and error messages. The daemon requires a random seed file, public/private key file and a valid certificate file; otherwise it exits immediately with a message to the system log. As each file is loaded a trace message appears with its filestamp. There are a number of checks to insure that only consistent data are used and that the certificate is valid. When the protocol is in operation a number of checks are done to verify the server has the expected credentials and its filestamps and timestamps are consistent. Errors found are reported using NTP control and monitoring protocol traps with extended trap codes shown in the Authentication Options page.

To assist debugging every NTP extension field is displayed in the trace along with the Autokey operation code. Every extension field carrying a verified signature is identified and displayed along with filestamp and timestamp where meaningful. In all except broadcast/multicast client mode, correct operation of the protocol is confirmed by the absence of extension fields and an <code>auth</code> value of one. It is normal in broadcast/multicast client mode that the broadcast server use one extension field to show the host name, status word and association ID.

#### Debugging Checklist

If the <code>ntpq</code> or <code>ntpdc</code> programs do not show that messages are being received by the daemon or that received messages do not result in correct synchronization, verify the following:

1.  Verify the <code>/etc/services</code> file host machine is configured to accept UDP packets on the NTP port 123. NTP is specifically designed to use UDP and does not respond to TCP.

2.  Check the system log for <code>ntpd</code> messages about configuration errors, name-lookup failures or initialization problems. Common system log messages are summarized on the [<code>ntpd</code> System Log Messages](/documentation/4.2.0/msyslog/) page. Check to be sure that only one copy of <code>ntpd</code> is running.

3.  Verify using <code>ping</code> or other utility that packets actually do make the round trip between the client and server. Verify using <code>nslookup</code> or other utility that the DNS server names do exist and resolve to valid Internet addresses.

4.  Check that the remote NTP server is up and running. The usual evidence that it is not is a <code>Connection refused</code> message.

5.  Using the <code>ntpdc</code> program, verify that the packets received and packets sent counters are incrementing. If the sent counter does not increment and the configuration file includes configured servers, something may be wrong in the host network or interface configuration. If this counter does increment, but the received counter does not increment, something may be wrong in the network or the server NTP daemon may not be running or the server itself may be down or not responding.

6.  If both the sent and received counters do increment, but the <code>reach</code> values in the <code>pe</code> billboard with <code>ntpq</code> continues to show zero, received packets are probably being discarded for some reason. If this is the case, the cause should be evident from the <code>flash</code> variable as discussed above and on the <code>ntpq</code> page. It could be that the server has disabled access for the client address, in which case the refid field in the <code>ntpq pe</code> billboard will show a kiss code. See earlier on this page for a list of kiss codes and their meaning.

7.  If the <code>reach</code> values in the <code>pe</code> billboard show the servers are alive and responding, note the tattletale symbols at the left margin, which indicate the status of each server resulting from the various grooming and mitigation algorithms. The interpretation of these symbols is discussed on the <code>ntpq</code> page. After a few minutes of operation, one or another of the reachable server candidates should show a \* tattletale symbol. If this doesn't happen, the intersection algorithm, which classifies the servers as truechimers or falsetickers, may be unable to find a majority of truechimers among the server population.

8.  If all else fails, see the FAQ and/or the discussion and briefings at the NTP Project page.