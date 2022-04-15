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

* [Initial Startup](/documentation/4.2.6-series/debug/#initial-startup)
* [Verifying Correct Operation](/documentation/4.2.6-series/debug/#verifying-correct-operation)
* [Large Frequency Errors](/documentation/4.2.6-series/debug/#large-frequency-errors)
* [Access Controls](/documentation/4.2.6-series/debug/#access-controls)
* [Large Delay Variations](/documentation/4.2.6-series/debug/#large-delay-variations)
* [Cryptographic Authentication](/documentation/4.2.6-series/debug/#cryptographic-authentication)
* [Debugging Checklist](/documentation/4.2.6-series/debug/#debugging-checklist)

* * *

#### Initial Startup

This page discusses <code>ntpd</code> program monitoring and debugging techniques using the [<code>ntpq</code> - standard NTP query program](/documentation/4.2.6-series/ntpq/), either on the local server or from a remote machine. In special circumstances the [<code>ntpdc</code> - special NTP query program](/documentation/4.2.6-series/ntpdc/), can be useful, but its use is not covered here. The <code>ntpq</code> program implements the management functions specified in the NTP specification [RFC-1305, Appendix A](/reflib/rfc/rfc1305/rfc1305c.pdf). It is used to read and write the variables defined in the NTP Version 4 specification now navigating the standards process. In addition, the program can be used to send remote configuration commands to the server.

The <code>ntpd</code> daemon can operate in two modes, depending on the presence of the <code>-d</code> command-line option. Without the option the daemon detaches from the controlling terminal and proceeds autonomously. With one or more <code>-d</code> options the daemon does not detach and generates special trace output useful for debugging. In general, interpretation of this output requires reference to the sources. However, a single <code>-d</code> does produce only mildly cryptic output and can be very useful in finding problems with configuration and network troubles.

Some problems are immediately apparent when the daemon first starts running. The most common of these are the lack of a UDP port for NTP (123) in the Unix <code>/etc/services</code> file (or equivalent in some systems). **Note that NTP does not use TCP in any form. Also note that NTP requires port 123 for both source and destination ports.** These facts should be pointed out to firewall administrators.

Other problems are apparent in the system log, which ordinarily shows the startup banner, some cryptic initialization data and the computed precision value. Event messages at startup and during regular operation are sent to the optional <code>protostats</code> monitor file, as described on the [Event Messages and Status Words](/documentation/4.2.6-series/decode/) page. These and other error messages are sent to the system log, as described on the [<code>ntpd</code> System Log Messages](/documentation/4.2.6-series/msyslog/) page. In real emergencies the daemon will sent a terminal error message to the system log and then cease operation.

The next most common problem is incorrect DNS names. Check that each DNS name used in the configuration file exists and that the address responds to the Unix <code>ping</code> command. The Unix <code>traceroute</code> or Windows <code>tracert</code> utility can be used to verify a partial or complete path exists. Most problems reported to the NTP newsgroup are not NTP problems, but problems with the network or firewall configuration.

* * *

#### Verifying Correct Operation

Unless using the <code>iburst</code> option, the client normally takes a few minutes to synchronize to a server. If the client time at startup happens to be more than 1000 s distant from NTP time, the daemon exits with a message to the system log directing the operator to manually set the time within 1000 s and restart. If the time is less than 1000 s but more than 128 s distant, a step correction occurs and the daemon restarts automatically.

When started for the first time and a frequency file is not present, the daemon enters a special mode in order to calibrate the frequency. This takes 900 s during which the time is not disciplined. When calibration is complete, the daemon creates the frequency file and enters normal mode to amortize whatever residual offset remains.

The <code>ntpq</code> commands <code>pe</code>, <code>as</code> and <code>rv</code> are normally sufficient to verify correct operation and assess nominal performance. The [<code>pe</code>](/documentation/4.2.6-series/ntpq/#pe) command displays a list showing the DNS name or IP address for each association along with selected status and statistics variables. The first character in each line is the tally code, which shows which associations are candidates to set the system clock and of these which one is the system peer. The encoding is shown in the <code>select</code> field of the [peer status word](/documentation/4.2.6-series/decode/#peer-status-word).

The [<code>as</code>](/documentation/4.2.6-series/ntpq/#as) command displays a list of associations and association identifiers. Note the <code>condition</code> column, which reflects the tally code. The [<code>rv</code>](/documentation/4.2.6-series/ntpq/#pe) command displays the [system variables](/documentation/4.2.6-series/ntpq/#system-variables) billboard, including the [system status word](/documentation/4.2.6-series/decode/#system-status-word). The [<code>rv _assocID_</code>](/documentation/4.2.6-series/ntpq/#rv) command, where <code>_assocID_</code> is the association ID, displays the [peer variables](/documentation/4.2.6-series/ntpq/#peer-variables) billboard, including the [peer status word](/documentation/4.2.6-series/decode/#peer-status-word). Note that, except for explicit calendar dates, times are in milliseconds and frequencies are in parts-per-million (PPM).

A detailed explanation of the system, peer and clock variables in the billboards is beyond the scope of this page; however, a comprehensive explanation for each one is in the NTPv4 protocol specification. The following observations will be useful in debugging and monitoring.

1.  The server has successfully synchronized to its sources if the <code>leap</code> peer variable has value other than 3 (11b) The client has successfully synchronized to the server when the <code>leap</code> system variable has value other than 3.
2.  The <code>reach</code> peer variable is an 8-bit shift register displayed in octal format. When a valid packet is received, the rightmost bit is lit. When a packet is sent, the register is shifted left one bit with 0 replacing the rightmost bit. If the <code>reach</code> value is nonzero, the server is reachable; otherwise, it is unreachable. Note that, even if all servers become unreachable, the system continues to show valid time to dependent applications.
3.  A useful indicator of miscellaneous problems is the <code>flash</code> peer variable, which shows the result of 13 sanity tests. It contains the [flash status word](/documentation/4.2.6-series/decode/#flash-status-word) bits, commonly called flashers, which displays the current errors for the association. These bits should all be zero for a valid server.
4.  The three peer variables <code>filtdelay</code>, <code>filtoffset</code> and <code>filtdisp</code> show the delay, offset and jitter statistics for each of the last eight measurement rounds. These statistics and their trends are valuable performance indicators for the server, client and the network. For instance, large fluctuations in delay and jitter suggest network congestion. Missing clock filter stages suggest packet losses in the network.
5.  The synchronization distance, defined as one-half the delay plus the dispersion, represents the maximum error statistic. The jitter represents the expected error statistic. The maximum error and expected error calculated from the peer variables represents the quality metric for the server. The maximum error and expected error calculated from the system variables represents the quality metric for the client. If the root synchronization distance for any server exceeds 1.5 s, called the select threshold, the server is considered invalid.

* * *

#### Large Frequency Errors

The frequency tolerance of computer clock oscillators varies widely, sometimes above 500 PPM. While the daemon can handle frequency errors up to 500 PPM, or 43 seconds per day, values much above 100 PPM reduce the headroom, especially at the lowest poll intervals. To determine the particular oscillator frequency, start <code>ntpd</code> using the <code>noselect</code> option with the <code>server</code> configuration command.

Record the time of day and offset displayed by the <code>ntpq</code> [<code>pe</code>](/documentation/4.2.6-series/ntpq/#pe) command. Wait for an hour or so and record the time of day and offset. Calculate the frequency as the offset difference divided by the time difference. If the frequency is much above 100 PPM, the [tickadj](/documentation/4.2.6-series/tickadj/) program might be useful to adjust the kernel clock frequency below that value. For systems that do not support this program, this might be one using a command in the system startup file.

* * *

#### Access Controls

Provisions are included in <code>ntpd</code> for access controls which deflect unwanted traffic from selected hosts or networks. The controls described on the [Access Control Options](/documentation/4.2.6-series/accopt/) include detailed packet filter operations based on source address and address mask. Normally, filtered packets are dropped without notice other than to increment tally counters. However, the server can be configured to send a "kiss-o'-death" (KOD) packet to the client either when explicitly configured or when cryptographic authentication fails for some reason. The client association is permanently disabled, the access denied bit (TEST4) is set in the flash variable and a message is sent to the system log.

The access control provisions include a limit on the packet rate from a host or network. If an incoming packet exceeds the limit, it is dropped and a KOD sent to the source. If this occurs after the client association has synchronized, the association is not disabled, but a message is sent to the system log. See the [Access Control Options](/documentation/4.2.6-series/accopt/) page for further information.

* * *

#### Large Delay Variations

In some reported scenarios an access line may show low to moderate network delays during some period of the day and moderate to high delays during other periods. Often the delay on one direction of transmission dominates, which can result in large time offset errors, sometimes in the range up to a few seconds. It is not usually convenient to run <code>ntpd</code> throughout the day in such scenarios, since this could result in several time steps, especially if the condition persists for greater than the stepout threshold.

Specific provisions have been built into <code>ntpd</code> to cope with these problems. The scheme is called "huff-'n-puff and is described on the [Miscellaneous Options](/documentation/4.2.6-series/miscopt/) page. An alternative approach in such scenarios is first to calibrate the local clock frequency error by running <code>ntpd</code> in continuous mode during the quiet interval and let it write the frequency to the <code>ntp.drift</code> file. Then, run <code>ntpd -q</code> from a cron job each day at some time in the quiet interval. In systems with the nanokernel or microkernel performance enhancements, including Solaris, Tru64, Linux and FreeBSD, the kernel continuously disciplines the frequency so that the residual correction produced by <code>ntpd</code> is usually less than a few milliseconds.

* * *

#### Cryptographic Authentication

Reliable source authentication requires the use of symmetric key or public key cryptography, as described on the [Authentication Options](/documentation/4.2.6-series/authopt/) page. In symmetric key cryptography servers and clients share session keys contained in a secret key file In public key cryptography, which requires the OpenSSL software library, the server has a private key, never shared, and a public key with unrestricted distribution. The cryptographic media required are produced by the [<code>ntp-keygen</code>](/documentation/4.2.6-series/keygen/) program.

Problems with symmetric key authentication are usually due to mismatched keys or improper use of the <code>trustedkey</code> command. A simple way to check for problems is to use the trace facility, which is enabled using the <code>ntpd -d</code> command line. As each packet is received a trace line is displayed which shows the authentication status in the <code>auth</code> field. A status of 1 indicates the packet was successful authenticated; otherwise it has failed.

A common misconception is the implication of the <code>auth</code> bit in the <code>enable</code> and <code>disable</code> commands. **This bit does not affect authentication in any way other than to enable or disable mobilization of a new persistent association in broadcast/multicast client, manycast client or symmetric passive modes.** If enabled, which is the default, these associations require authentication; if not, an association is mobilized even if not authenticated. Users are cautioned that running with authentication disabled is very dangerous, since an intruder can easily strike up an association and inject false time values.

Public key cryptography is supported in NTPv4 using the [Autokey protocol](/reflib/brief/atirp2/atirp2.pdf). Development of this protocol is mature and the <code>ntpd</code> implementation is basically complete. Autokey version 2, which is the latest and current version, includes provisions to hike certificate trails, operate as certificate authorities and verify identity using challenge/response identification schemes. Further details of the protocol are on the [Authentication Options](/documentation/4.2.6-series/authopt/) page. Common problems with configuration and key generation are mismatched key files, broken links and missing or broken random seed file.

As in the symmetric key cryptography case, the trace facility is a good way to verify correct operation. A statistics file <code>cryptostats</code> records protocol transactions and error messages. The daemon requires a random seed file, public/private key file and a valid certificate file; otherwise it exits immediately with a message to the system log. As each file is loaded a trace message appears with its filestamp. There are a number of checks to insure that only consistent data are used and that the certificate is valid. When the protocol is in operation a number of checks are done to verify the server has the expected credentials and its filestamps and timestamps are consistent. Errors found are reported using NTP control and monitoring protocol traps with extended trap codes shown in the Authentication Options page.

To assist debugging every NTP extension field is displayed in the trace along with the Autokey operation code. Every extension field carrying a verified signature is identified and displayed along with filestamp and timestamp where meaningful. In all except broadcast/multicast client mode, correct operation of the protocol is confirmed by the absence of extension fields and an <code>auth</code> value of one. It is normal in broadcast/multicast client mode that the broadcast server use one extension field to show the host name, status word and association ID.

* * *

#### Debugging Checklist

If the <code>ntpq</code> or <code>ntpdc</code> programs do not show that messages are being received by the daemon or that received messages do not result in correct synchronization, verify the following:

1.  Verify the <code>/etc/services</code> file host machine is configured to accept UDP packets on the NTP port 123. NTP is specifically designed to use UDP and does not respond to TCP.
2.  Check the system log for <code>ntpd</code> messages about configuration errors, name-lookup failures or initialization problems. Common system log messages are summarized on the [<code>ntpd</code> System Log Messages](/documentation/4.2.6-series/msyslog/) page. Check to be sure that only one copy of <code>ntpd</code> is running.
3.  Verify using <code>ping</code> or other utility that packets actually do make the round trip between the client and server. Verify using <code>nslookup</code> or other utility that the DNS server names do exist and resolve to valid Internet addresses.
4.  Check that the remote NTP server is up and running. The usual evidence that it is not is a <code>Connection refused</code> message.
5.  Using the <code>ntpdc</code> program, verify that the packets received and packets sent counters are incrementing. If the sent counter does not increment and the configuration file includes configured servers, something may be wrong in the host network or interface configuration. If this counter does increment, but the received counter does not increment, something may be wrong in the network or the server NTP daemon may not be running or the server itself may be down or not responding.
6.  If both the sent and received counters do increment, but the <code>reach</code> values in the <code>pe</code> billboard with <code>ntpq</code> continues to show zero, received packets are probably being discarded for some reason. If this is the case, the cause should be evident from the <code>flash</code> variable as discussed above and on the <code>ntpq</code> page. It could be that the server has disabled access for the client address, in which case the <code>refid</code> field in the <code>ntpq pe</code> billboard will show a kiss code. See earlier on this page for a list of kiss codes and their meaning.
7.  If the <code>reach</code> values in the <code>pe</code> billboard show the servers are alive and responding, note the tattletale symbols at the left margin, which indicate the status of each server resulting from the various grooming and mitigation algorithms. The interpretation of these symbols is discussed on the <code>ntpq</code> page. After a few minutes of operation, one or another of the reachable server candidates should show a <code>*</code> tattletale symbol. If this doesn't happen, the intersection algorithm, which classifies the servers as truechimers or falsetickers, may be unable to find a majority of truechimers among the server population.
8.  If all else fails, see the FAQ and/or the discussion and briefings at the NTP Project page.