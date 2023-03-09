---
title: "6.2. Advanced Configuration"
description: "This section of the NTP FAQ discusses advanced configuration options that are probably not needed for the average user. If you want to provide time service to a larger community, consider some of these topics."
type: "archives"
---

This section discusses advanced configuration options that are probably not needed for the average user. If you want to provide time service to a larger community, consider some of these topics.

6.2.1 [Server Selection](#621-server-selection)  
6.2.1.1 [What is the rule of thumb for number of servers to synchronize to?](#6211-what-is-the-rule-of-thumb-for-number-of-servers-to-synchronize-to)  
6.2.1.2 [Should the servers be a mix of primary and secondary servers?](#6212-should-the-servers-be-a-mix-of-primary-and-secondary-servers)  
6.2.1.3 [How should I provide NTP services for a huge network?](#6213-how-should-i-provide-ntp-services-for-a-huge-network)  
6.2.2 [Authentication](#622-authentication)  
6.2.2.1 [Why Authentication?](#6221-why-authentication)  
6.2.2.2 [How is Authentication applied?](#6222-how-is-authentication-applied)  
6.2.2.3 [How do I create a key?](#6223-how-do-i-create-a-key)  
6.2.2.4 [How does Authentication work?](#6224-how-does-authentication-work)  
6.2.2.5 [Can I add Authentication without restarting ntpd?](#6225-can-i-add-authentication-without-restarting-ntpd)  
6.2.2.6 [How do I use Public-Key Authentication (autokey)?](#6226-how-do-i-use-public-key-authentication-autokey)  
6.2.3 [Broadcasting, Multicasting, and Manycasting](#623-broadcasting-multicasting-and-manycasting)   
6.2.3.1 [How do I configure a Broadcast Server?](#6231-how-do-i-configure-a-broadcast-server)  
6.2.3.2 [How do I configure a Broadcast Client?](#6232-how-do-i-configure-a-broadcast-client)  
6.2.3.3 [Why doesn't Broadcasting work with LCL?](#6233-why-doesnt-broadcasting-work-with-lcl)   
6.2.3.4 [How do I configure Multicast Servers and Clients?](#6234-how-do-i-configure-multicast-servers-and-clients)    
6.2.3.5 [What is Manycasting?](#6235-what-is-manycasting)  
6.2.4. [PPS Synchronization](#624-pps-synchronization)    
6.2.4.1 [Which components are required to use PPS synchronization?](#6241-which-components-are-required-to-use-pps-synchronization)  
6.2.4.2 [What changes are required in ntp.conf?](#6242-what-changes-are-required-in-ntpconf)  
6.2.4.3 [How do I verify that everything is working?](#6243-how-do-i-verify-that-everything-is-working)  
6.2.4.4 [Special Drivers](#6244-special-drivers)  
6.2.4.4.1 [What is a PPS peer?](#62441-what-is-a-pps-peer)  
6.2.4.4.2 [How do I use PPS with the Motorola Oncore driver?](#62442-how-do-i-use-pps-with-the-motorola-oncore-driver)  
6.2.4.4.3 [How do I use PPS with the NMEA driver?](#62443-how-do-i-use-pps-with-the-nmea-driver)  
6.2.4.5 [What is the PPS API?](#6245-what-is-the-pps-api)  
6.2.4.6 [What is the shortest Width for a Pulse connected to the DCD Pin of an RS-232 Interface?](#6246-what-is-the-shortest-width-for-a-pulse-connected-to-the-dcd-pin-of-an-rs-232-interface)  
6.2.5 [Automatic Configuration](#625-automatic-configuration)  
6.2.5.1 [How can I define the address of an NTP server in a BOOTP reply?](#6251-how-can-i-define-the-address-of-an-ntp-server-in-a-bootp-reply)  
6.2.5.2 [How do I use information about NTP servers given in a BOOTP reply?](#6252-how-do-i-use-information-about-ntp-servers-given-in-a-bootp-reply)  
6.2.6 [Offering Time Service](#626-offering-time-service)  
6.2.6.1 [Is there any way to configure ntpd to attach to a specific Interface?](#6261-is-there-any-way-to-configure-ntpd-to-attach-to-a-specific-interface)  
6.2.6.2 [Should Access be restricted?](#6262-should-access-be-restricted)  
6.2.6.3 [What should be done before announcing public NTP service?](#6263-what-should-be-done-before-announcing-public-ntp-service)

* * *

#### 6.2.1. Server Selection

#### 6.2.1.1. What is the rule of thumb for number of servers to synchronize to?

It is entirely up to you and your tolerance for outages. Obviously you have some tolerance, or you would be buying GPS receivers and installing your own stratum-1 servers. But three is a good place to start, and you can progress to three-groups-of-three if you feel the need. Remember that network outages are at least as likely as timeserver outages. If you only have one network path to the outside world, adding a more timeservers doesn't really improve reliability as your ISP is the single-point-of-failure.

* * *

#### 6.2.1.2. Should the servers be a mix of primary and secondary servers?

Probably not. The secondaries are good enough for almost everybody. If you care about the small differences in accuracy/precision between the primaries and the secondaries (and you must be close enough, topology-wise, to even _see_ the difference) then you should buy some GPS receivers.

* * *

#### 6.2.1.3. How should I provide NTP services for a huge network?

For a huge network you should provide enough redundancy while avoiding a single point of failure. The following discussion will be based on Figure 6.2a, a configuration that is frequently recommended. I'm not saying it's the only possible configuration, but let's just have a closer look.

**Figure 6.2a: Configuration for a huge Network**

<pre> 1a  1b     1c  1d     1e  1f      outside
. \ / ...... \ / ...... \ / ..............
   2a ---p--- 2b ---p--- 2c        inside
  /|\        /|\        /|\
 / | \      / | \      / | \
3a 3b 3c   3e 3f 3g   3h 3i 3j

Key: 1 = stratum-1, 2 = stratum-2, 3 = stratum-3, p = peer</pre>

The example configuration uses six stratum-1 servers (`1a` ... `1f`) to synchronize three stratum-2 servers (`2a` ... `2c`). All servers at stratum two are peers to each other. Each of these stratum-2 servers serve three stratum-3 servers. Clients will be using the servers at stratum three.

Having [more than one reference server configured](/ntpfaq/ntp-s-algo-real/#532-why-should-i-have-more-than-one-clock) increases reliability and stability of the client. That is why there are two servers for each of the stratum-2 servers. Distributing time horizontally (peering) reduces the amount of traffic to the stratum-1 servers while giving additional redundancy for the stratum-2 servers. The extra layer of stratum-2 servers helps to distribute the load created by lower levels (stratum-3).

If you have a reference clock, you would probably arrange peering with one or more stratum-1 servers. For most networks you can probably leave out the third layer (stratum-3) completely.

There's an additional comment by David Dalton:

But my advice is this: if your stratum-N peers all use the same ISP to get to the outside world, then peers are mostly pointless. Your single-point-of-failure is the network path, not the stratum-1 machines themselves. Building huge redundancy into your hierarchy can get very expensive very quickly. Think hard about how much redundancy you really need.

And another comment from [Mark Martinec](mailto:mark.martinec@ijs.si):

I don't find the Figure 6.2a a good idea. It has a big problem in that stratum-3 servers in the picture all have a single point of failure in their single reference stratum-2 NTP server, not to mention it throws away all the fancy NTP algorithms.

As a fix (and to make it cleaner/leaner), one could strike out the stratum-3 layer completely from the picture and say that each of the company clients will use _all three_ peered company stratum-2 servers as their reference.

If one really needs more fanout (doubtful), one can put back the stratum-3 layer, but with each stratum-3 server referenced to _each_ of the company stratum-2 servers.

* * *

#### 6.2.2. Authentication

#### 6.2.2.1. Why Authentication?

Most users of NTP do not need authentication as the protocol contains several filters against bad time. However, there is still authentication, and its use seems to become more common. Some reasons might be:

*   You only want to use time from trusted sources.
*   An attacker may broadcast wrong time stamps.
*   An attacker may disguise as another time server.

* * *

#### 6.2.2.2. How is Authentication applied?

NTP uses keys to implement authentication. These keys are used when exchanging data between two machines. As shown in [Q: 6.1.4.3](/ntpfaq/ntp-s-config/#6143-how-do-i-configure-remote-administration) and [Q: 6.1.4.4](/ntpfaq/ntp-s-config/#6144-how-do-i-use-authentication-keys), one of the uses has to do with remote administration. When configuring a `server` or `peer`, an authentication key can be specified:

<pre>peer 128.100.49.105 key 22
peer 128.8.10.1     key 4
peer 192.35.82.50   key 6

# path for key file
keys /usr/local/etc/ntp.keys

trustedkey 4 6 14 15 22 # define trusted keys
requestkey 15    # key (7) for accessing server variables
controlkey 15    # key (6) for accessing server variables</pre>

The keyword `key` specifies the key to be used when talking to the specified server.

* * *

#### 6.2.2.3. How do I create a key?

`ntp-keygen` is used to create keys. Refer to its [documentation](/documentation/4.2.8-series/keygen/) for a complete description and command line options.

[Q: 6.1.4.3](/ntpfaq/ntp-s-config/#6143-how-do-i-configure-remote-administration) provides a remote configuration example.

* * *

#### 6.2.2.4. How does Authentication work?

Basically authentication is a digital signature, and no data encryption (if there is any difference at all). The usual data packet plus the key is used to build a non-reversible magic number that is appended to the packet. The receiver (having the same key) does the same computation and compares the result. If the results match, authentication suceeded.

* * *

#### 6.2.2.5. Can I add Authentication without restarting ntpd?

Yes and No. You can dynamically add servers that use authentication keys, and you can trust or un-trust any key using `ntpdc`. You can also re-read the keyfile using the `readkeys` command. Unfortunately you need to configure basic authentication before using any of these commands.

* * *

#### 6.2.2.6. How do I use Public-Key Authentication (autokey)?

Refer to the examples in [Autokey Public-Key-Authentication](/documentation/4.2.8-series/autokey/) and [Q: 6.1.4.6](/ntpfaq/ntp-s-config/#6146-how-do-i-use-autokey). 

The following example includes [advice](https://support.ntp.org/Support/ConfiguringAutokeyDev) from [Professor David L. Mills](mailto:mills@udel.edu):

> Ensure you have a working NTP configuration before configuring Autokey!

**Configure NTP Servers**

1. Generate a trusted certificate for each group member using `ntp-keygen -T` as described in [Configuration - Authentication Schemes](/documentation/4.2.8-series/autokey/#configuration---authentication-schemes). 

2. Make the group keys with the `-I` option on a trusted host or trusted agent.

3. Make the client keys from the group keys and distribute to the clients. Use an arbitrary file name, preferably the name of the group.

**Configure NTP Clients**

1. Create a directory for the client's NTP keys (e.g. `/etc/ntp`). That directory should only be readable by root.

2. In each client's `/etc/ntp.conf` file, append `autokey` to the `server` entry. Then append the `ident` option to the client's `server` entry with the same name as the installed client keys.

3. For broadcast clients, use the `ident` option in the `crypto` command instead. 

* * *

#### 6.2.3. Broadcasting, Multicasting, and Manycasting

With broadcasting and multicasting several clients can be addressed with a single packet transmitted by the server.

* * *

#### 6.2.3.1. How do I configure a Broadcast Server?

A line like `broadcast 128.4.2.255` enables periodic sending of broadcast packets containing the current time as long as the server's clock is synchronized. The period may be influenced by the `minpoll` option. Packet forwarding can be limited by specifying the `ttl` option. Make sure you are using the correct broadcast address for your subnet.

* * *

#### 6.2.3.2 How do I configure a Broadcast Client?

Using the line `broadcastclient` will enable listening to broadcasts. As anybody can send out any broadcasts, use of authentication is strongly advised. In NTPv4 the client will actively query a broadcasting server to calibrate the delay. More details can be found in [Association Management](/documentation/4.2.8-series/assoc/#broadcastmulticast-modes).

* * *

#### 6.2.3.3 Why doesn't Broadcasting work with LCL?

Before continuing, make sure you read and understood [Q: 7.1.1](/ntpfaq/ntp-s-refclk/#711-what-is-lcl-the-local-clock) and [Q: 6.1.3.1.](/ntpfaq/ntp-s-config/#6131-can-i-use-my-system-clock-as-reference-clock). As you shouldn't broadcast bad time, a `prefer` keyword is required when using `LCL`.

* * *

#### 6.2.3.4 How do I configure Multicast Servers and Clients?

Multicasting is configured just like broadcasting, but instead of using a broadcast address, a _multicast group address_ (class D) is used.

* * *

#### 6.2.3.5 What is Manycasting?

This is an explanation by [Professor David L. Mills](mailto:mills@udel.edu): "Manycast only works in multicast mode. It uses an expanding-ring search by adjusting the TTL field. This doesn't make sense in broadcast mode, since broadcast packets do not span subnets. It might in fact be useful to implement manycast in broadcast mode without the search, but that is rather far down the to-do list." (...) "Only the `*` and `+` tattletales indicate a candidate survivor. Note that one of your servers is in process of going away, another coming onboard. This is a normal situation when first coming up and when the signatures are refreshed once per day. I assume you are using autokey; if not, no promises at all."

So basically it's a mechanism to automatically configure servers on a nearby network. Compared to broadcasting and multicasting, manycasting uses the normal `server` keyword, but with a multicast group address (class D) on the client. Manycast servers use the keyword `manycastserver`. As for broadcasts and multicasts, manycast associations on the client may come and go over time.

* * *

#### 6.2.4. PPS Synchronization

[PPS (Pulse-per-Second)](/documentation/4.2.8-series/pps/) synchronization is an option that is neither necessary nor available for all operating systems. Still it brings many benefits if used, so it's discussed here.

Network connections can suffer from random delays. Even for local reference clocks the exact point in time to which some time message belongs is difficult to determine. Delays imposed by the operating system are another issue to deal with.

Some means to improve the situation were thought of:

*   The operating system could be modified to capture the time of some external event more precisely. Among such events could be characters received at a serial port or some [signal edge](https://en.wikipedia.org/wiki/Signal_edge) detected on a digital input.
*   If such external events arrive periodically with high precision, the time stamps could be used to determine the frequency error of the associated computer clock.
*   If the external event arrived exactly at the time when a new second starts, the time stamps could be used to correct the offset of the associated computer clock.

Basically, this is what the PPS discussion is about.

* * *

#### 6.2.4.1 Which components are required to use PPS synchronization?

The following items are needed in order to use PPS synchronization:

*   You need a high precision signal that can be connected to the computer running NTP. Usual sources of PPS signals are quality reference clocks that feature such an output.
*   Your operating system must support processing of PPS signals. Most operating systems that come with source code (such as Linux and FreeBSD) already support PPS processing or can be modified to do so.
    
	Most operating systems supporting PPS have a programming interface to read timestamps and also implement the NTP kernel clock model with special PPS processing options. See also [Q: 5.2.3.3](/ntpfaq/ntp-s-algo-kernel/#5233-what-does-hardpps-do).
*   The NTP software must be configured to recognize and use PPS processing. Usually the software's autoconfigure process will detect the presence of PPS processing capabilities.
*   Finally you should edit `ntp.conf` to work with PPS.

* * *

#### 6.2.4.2 What changes are required in ntp.conf?

Unfortunately PPS processing is a [little messy](/ntpfaq/ntp-s-config-adv/#6245-what-is-the-pps-api). Example 6.2a demonstrates the entries in `/etc/ntp.conf` which work with PPSkit-1.0.0 on my Linux PC.

**Example 6.2a: Using a PPS Signal**

<pre>
server 127.127.8.1 mode 135 prefer	# Meinberg GPS167 with PPS
fudge 127.127.8.1 time1 0.0042		# relative to PPS for my hardware

server 127.127.22.1 			# PPS
fudge 127.127.22.1 flag3 1		# enable PPS API</pre>

When starting, the following things happen:

1.  The clock `GENERIC(1)` becomes reachable while PPS is used to update the kernel variables described in [Q: 6.2.4.3](/ntpfaq/ntp-s-config-adv/#6243-how-do-i-verify-that-everything-is-working).
2.  The configured clock is selected as synchronization source, and `status` changes to `0x2143` after a while. At that time `PPS(1)` also becomes reachable. During that time `status` changes to `0x2107`, and `offset` shows current offsets from PPS.
3.  Eventually `PPS(1)` becomes PPS peer.

* * *

#### 6.2.4.3 How do I verify that everything is working?

The pleasant part of this answer is that there are tools included in the standard NTP software that makes this an easy task. The less pleasant part is that there is no single way to enable PPS detection for each operating system. However the [PPS API](/ntpfaq/ntp-s-config-adv/#6245-what-is-the-pps-api) may change things in a positive way.

Let's start with the easier part using standard tools:

1.  There are two means to look at the NTP kernel clock: `ntptime` and `ntpdc -c kerninfo`. As `ntptime` is a little more verbose, let's consider it.

    <pre>windl@elf:~ >ntptime
    ntp_gettime() returns code 0 (OK)
      time bd6b9cf2.9c3c6c60  Thu, Sep 14 2000 20:52:34.610, (.610297702),
      maximum error 3480 us, estimated error 0 us.
    ntp_adjtime() returns code 0 (OK)
      modes 0x0 (),
      offset 1.658 us, frequency 17.346 ppm, interval 128 s,
      maximum error 3480 us, estimated error 0 us,
      status 0x2107 (PLL,PPSFREQ,PPSTIME,PPSSIGNAL,NANO),
      time constant 6, precision 3.530 us, tolerance 496 ppm,
      pps frequency 17.346 ppm, stability 0.016 ppm, jitter 1.378 us,
      intervals 57, jitter exceeded 29, stability exceeded 0, errors 0.</pre>

    The above command has been run on Linux version 2.2.16 with PPSkit-1.0.0. That combination features PPS processing and a kernel clock using nanoseconds.

    The first thing you should look at is the `status1` (`0x2107` in our case). The magic words in parentheses explain the meaning of the individual bits. The important bit for now is `PPSSIGNAL`. That bit is set directly by the operating system and says a PPS signal has been detected.

2.  Now that pulses are detected, let's see whether they are good ones. For that purpose we read some additional numbers about the kernel clock's calibration process:

    *   `intervals 57` says that there were 57 calibration intervals. When PPS pulses are arriving, this number should increase. Each frequency adjustment requires a good calibration interval. The length of the current calibration interval can be found as `interval 128 s` (128 seconds is the default maximum length). Remaining numbers count abnormal conditions as explained below.

    *   `jitter exceeded 29` means that there were 29 pulses that arrived at a time when they were not considered good; however, completely bad pulses are not counted here. This can mean that the pulses were out of range, or that the system clock was read badly when the pulses arrived. The algorithm dynamically adjusts the threshold for jitter. Occasional jitter is allowed and should not worry you. If significant jitter is detected, the flag `PPSJITTER` is set.

    *   `stability exceeded 0` is the number of calibration intervals that would result in a correction larger than considered valid, where the default limit is quite high.

        Validity is a bit fuzzy, but it means that the frequency change would be more than the tolerance. You can find the tolerance coded into your operating system from `tolerance 496 ppm`, but it's not guaranteed that the value is specific to your hardware.

        Stability should not be exceeded during normal operating conditions. Upon detection of that error the flag `PPSWANDER` is set.

    *   `errors 0` indicates the number of calibration intervals where pulses were missing or completely out of bounds. In these cases the flag `PPSERROR` is set. During normal operation that number should not increase.

    Those numbers are only reset when the machine is booted.

3.  If you did not find an error, your PPS configuration should work! You can inspect some additional performance indicators:

    *   `stability 0.016 ppm` is an averaged value for the last frequency corrections made (instability). Basically a small value indicates that both your operating system's clock and your external PPS signal are stable. Remember that [temperature changes affect the average PC](/ntpfaq/ntp-s-algo/#5131-how-accurate-will-my-clock-be). The sample above was taken after running the system for about one hour; you should expect a value below `0.1 ppm` for a stable system.

    *   `jitter 1.378 us` is also an averaged value. It indicates how much the individual pulses vary from second to second, as measured by the operating system's clock. This value will vary due to system load and interrupt latency. A few microseconds are probably fine, but a few milliseconds definitely are not!

This completes the basic checks for PPS configuration. In the case above the NTP daemon is also working and using the data provided from the operating system kernel. I'll complete the description of the remaining output:

*   `pps frequency 17.346 ppm` indicates the current correction value for the clock frequency derived from the PPS signal. Positive values indicate the clock is too slow compared to the PPS. If flag `PPSFREQ` is set, that frequency correction is used for correcting the kernel clock. The NTP daemon will set this flag if the PPS parameters seem valid.

*   `offset 1.658 us` shows the last measured offset correction for the system clock. If flag `PPSTIME` is set, that offset is derived from the offset of the PPS pulse every second, and otherwise it's updated through `ntp_adjtime()` from the application. A positive value for `offset` means that the system clock is behind the reference time.

    PPS pulses add further corrections while the kernel clock tries to consume this offset by correcting the time accordingly. Formerly the offset was updated every 16 seconds by the kernel, but recently it's updated every second.

* * *

#### 6.2.4.4 Special Drivers

#### 6.2.4.4.1. What is a PPS peer?

Even when the kernel clock uses PPS signals to calibrate, the NTP daemon will still use the usual offsets of some reference clock. As it is desirable to use the offsets of the PPS pulses, there is a pseudo clock driver to do that. That driver needs to know the interface specific to the platform to get the time stamps of the PPS pulses.

That driver is called [PPS](/documentation/drivers/driver22/) and can be configured just as any other reference clock. The difference is that PPS can only be used in combination with another preferred time reference. As soon as the preferred time reference is used for synchronization, the `PPS` driver becomes reachable, and it will eventually be used as [primary synchronization source](/ntpfaq/ntp-s-algo-real/#532-why-should-i-have-more-than-one-clock). A PPS peer will be handled specially so that other time offsets are not considered. The command `ntpq -c peer -c as -c rl` will print something like:

<pre>remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
+GENERIC(1)      .GPS.            0 l   48   64  377    0.000    0.025   0.001
oPPS(1)          .PPS.            0 l   17   64  377    0.000    0.027   0.000

ind assID status  conf reach auth condition  last_event cnt
===========================================================
  1 57300  9434   yes   yes  none  candidat   reachable  3
  2 57301  9714   yes   yes  none  pps.peer   reachable  1

status=2194 leap_none, sync_atomic/PPS, 9 events, event_peer/strat_chg,
version="ntpd 4.0.99k Sun Sep 10 19:22:28 MEST 2000 (5)",
processor="i586", system="Linux2.2.16-NANO", leap=00, stratum=1,
precision=-16, rootdelay=0.000, rootdispersion=1.831, peer=57301,
refid=PPS, reftime=bd6b94f2.272b8844  Thu, Sep 14 2000 20:18:26.153,
poll=6, clock=bd6b952d.da89dadf  Thu, Sep 14 2000 20:19:25.853, state=4,
phase=0.005, frequency=16.984, jitter=0.000, stability=0.043</pre>

* * *

#### 6.2.4.4.2 How do I use PPS with the Motorola Oncore driver?

Considering the configuration below, John Hay wrote:

(...)The Oncore driver directly manages the PPS stuff, so you only need the first line (`server 127.127.30.0 prefer`) in the config file. The rest is not needed to have a functional Oncore refclock.

<pre>server 127.127.30.0 prefer
fudge 127.127.30.0 stratum 0

server 127.127.22.1                     # PPS
fudge 127.127.22.1 flag3 1              # enable PPS module
</pre>

> **Note:** As documented in [PPS Clock Discipline](/documentation/drivers/driver8/#fudge-factors), `flag2` controls the edge of the PPS signal being used, obsoleting the `pps` keyword.

Maybe it should also be noted here that a _site survey_ can take significant time to finish. [Terje Mathisen](mailto:Terje.Mathisen@hda.hydro.com) says: "My survey (under Linux) took about 36 hours, I also gave up a couple of times before allowing it to run to completion."

* * *

#### 6.2.4.4.3 How do I use PPS with the NMEA driver?

An [NMEA driver](/documentation/drivers/driver20/) is included in NTPv4. That means that for PPS processing we don't need the `PPS` driver or `pps` command in `ntp.conf`.

Here is sample `ntp.conf`:

<pre>server 127.127.20.0     # NMEA driver
fudge  flag3 1          # enable kernel PPS discipline</pre>

* * *

#### 6.2.4.5 What is the PPS API?

As seen above, the programming interface specific to the operating system and platform is a messy thing. Therefore some people decided to make a common programming interface named PPS API. In March 2000 that draft was accepted as an [RFC 2783](/reflib/rfc/rfc2783.txt). The functions of the API include:

*   Routines to enable capturing of external events on a specified device (if supported).
*   Routines to query the last captured time stamps and associated event counters.
*   Routines to change operating parameters like compensating for processing delays and selecting polarity of the PPS signal.
*   Routines to control automatic processing of detected events by a _kernel consumer_ in the kernel of the operating system.

[RFC 2783](/reflib/rfc/rfc2783.txt) indicates that: "Several available implementations of this API are [listed](/ppsapi/ppsimplist/). Note that not all of these implementations correspond to the current version of the specification".

* * *

#### 6.2.4.6 What is the shortest Width for a Pulse connected to the DCD Pin of an RS-232 Interface?

That depends. The higher the quality your serial port is, the longer pulses will be needed. This is because of the ESD protection of the chip.

26 usec should be about the bit time for a 38400 serial line, so you could connect it to the RxD line instead and see if you receive characters that way when the port is set for 38400 or faster.

Another thing to try is to configure the serial port for 115200. Some chips base their deglitching on the baud rate, often requiring a full symbol before they react.

* * *

#### 6.2.5 Automatic Configuration

If many systems have to be configured in a similar way, there is a desire to automate the process. We try to give some useful hints here.

* * *

#### 6.2.5.1 How can I define the address of an NTP server in a BOOTP reply?

The BOOTP protocol is defined in [RFC 1048](https://www.rfc-editor.org/rfc/rfc1048) (obsoleted by [RFC 2132](https://www.rfc-editor.org/rfc/rfc2132)). Marc Brett contributed:

Time ([RFC 868](https://www.rfc-editor.org/rfc/rfc868)) servers may be specified in the _Vendor Extensions field_, Code `4`.

NTP servers may be specified in the _Application and Service Parameters_, Code `42`.

In some popular `bootpd`, time servers are specified with `ts=`, but NTP servers are specified with `nt=`. The latter allows a list of Internet addresses to be specified.

* * *

#### 6.2.5.2 How do I use information about NTP servers given in a BOOTP reply?

If you are using Microsoft Windows, check whether your DHCP client software or NTP software supports this feature. If not, you are probably out of luck.

If you are using a UNIX system, you may be able to install the needed code.Exactly what is needed depends on the operating system, but if you are comfortable editing scripts, it shouldn't be too hard.

In general, UNIX systems implement BOOTP DHCP via a client daemon which handles the interaction with the DHCP server. Often, the daemon itself does not set up the network interface's address or do any other work based on the DHCP reply. Instead, it stores the information and activates an initialization script to use that information to adjust the computer's configuration.

Your first job is to identify the correct script. Start by tracking down the script that brings up the interface during normal startup. That script will have code which activates the DHCP client, and thus must also arrange to activate the script that implements the configuration provided by DHCP.

* * *

#### 6.2.6. Offering Time Service

This section presents some guidelines for offering time service to others.

* * *

#### 6.2.6.1. Is there any way to configure ntpd to attach to a specific Interface?

By default, `ntpd` listens on all virtual IP addresses. Use `-L` to configure `ntpd` to not listen on virtual IPs.

* * *

#### 6.2.6.2. Should Access be restricted?

If you don't want to have clients, don't offer the service. But as you want to offer NTP service to others, you should not be afraid of clients. Let me quote from an article in news://comp.protocols.time.ntp written by David Dalton about the subject whether queries with `ntpq` and `ntpdc` should be allowed:

I am somewhat new to the security concerns of public timeservers. Only in the past few weeks did I upgrade my public timeserver to stratum-1 with a Trimble Palisade GPS receiver. It doesn't have a lot of security right now, but the `ntpdc` reconfiguration functions are restricted. I'm soliciting advice about how to protect myself, although I don't depend on that public timeserver in any way.

I agree with you that there is no substitute for long-term data for evaluating the stability of a timeserver and the network between yourself and the timeserver.

But the query tools allow one to make evaluations without spending a lot of time, because the timeservers themselves have already collected the long-term data. I always want to run `ntpq -p` or `ntpdc -p` on a remote timeserver before committing to it. Very handy.

Even long-term statistics (gathered by your own client) won't tell you anything about how well the remote server is configured. How many reference clocks does it have? Which reference clocks? How many stratum-1 servers does it have in case the clock(s) fail(s)? Which one of these candidates would you prefer?

<pre>EXAMPLE ONE (BAD)
 -----------------
 [444] ntpq -p fubar.net
  <samp class="COMPUTEROUTPUT">remote      refid      st t when poll reach   delay   offset    disp
 =========================================================================
 *WWVB_SPEC       .WWVB.      0 l   18   16  377     0.00    0.301    1.69
  LOCAL(1)        LOCAL(1)    0 l    1   16  377     0.00    0.000   10.01
 
 EXAMPLE TWO (NOT BAD)
 ---------------------
 [170] ntpq  -p fubar2.net</kbd>
  <samp class="COMPUTEROUTPUT">remote      refid      st t when poll reach   delay   offset    disp
 =========================================================================
 *WWVB_SPEC(      .WWVB.      0 l   30   16  377     0.00    0.140    2.01
  LOCAL(1)        LOCAL(1)   10 l   13   16  377     0.00    0.000   10.01
 +hpxxxxxxxx      .GPS.       1 u   11   16  376     0.99   -0.708    0.35
 +hpxxxxxxxx      .GPS.       1 u   49   64  377     4.97   -2.680    0.81
  hpxxxxxxxx      xxxxxxxx    3 u  206 1024  377     4.70   -3.010    9.69
  hpxxxxxxxx      xxxxxxxx    3 u   29 1024  377     2.88   -4.287    0.17
 
 EXAMPLE THREE (OUTSTANDING)
 ---------------------------
 [169] ntpq  -p ntp2.usno.navy.mil</kbd>
  <samp class="COMPUTEROUTPUT">remote      refid      st t when poll reach   delay   offset    disp
 =========================================================================
 +GPS_VME(0)     .USNO.       0 l   15   16  377     0.00   -0.007    0.02
 *GPS_VME(1)     .USNO.       0 l   14   16  377     0.00    0.003    0.02
 +GPS_VME(2)     .USNO.       0 l   13   16  377     0.00    0.028    0.02
 +tick.usno      .USNO.       1 u   45   64  376     1.65    0.032    0.64
 -tock.usno      .USNO.       1 u   16   64  377     1.48   -0.072    0.47
 x204.34.19      .USNO.       1 u   24   64  377   226.88    3.924    1.77
 x204.34.19      .USNO.       1 u 1014 1024  376   249.76   10.737   26.49
  navobs1.g      0.0.0.0     16 -    - 1024    0     0.00    0.000 16000.0</pre>

That article continues:

You and I might agree that a handheld consumer-grade GPS receiver putting out NMEA data to a small workstation with 500 milliseconds dispersion is a poor excuse for a stratum-1 public timeserver, but that doesn't stop somebody from offering such a server for public use. No sanity checking or evaluation is done on the machines listed at UDelaware (AFAIK).

Here is what my handheld GPS receiver (400 dollars) looked like:

<pre>[179] ntpq  -p gpstime.net
  <samp class="COMPUTEROUTPUT">remote      refid      st t when poll reach   delay   offset    disp
 =========================================================================
 *GPS_NMEA        .GPS.       0 l    1   64  377     0.00  -226.243  420.08</samp></pre>
 
Here is a stratum-2 timeserver that has a good pedigree (HP-UX) and is synching to a stratum-1 timeserver that has an HP GPS clock, but the stratum-2 machine is having problems because the network is _very_ congested and it has no backup sources:
 
 <pre>  remote            refid      st t when poll reach  delay   offset disp
 ==========================================================================
  big_srv         17.8.5.7      2 u    3  512   17   312.87 -249.15 1960.85</pre>
 
Here are some results from well configured public timeservers that I have surveyed at various times. It is interesting to work your way through the stratum-1 list at UDelaware and see a lot of timeservers this way.

 <pre>[165] ntpq  -p ntp-cup.external.hp.com
  <samp class="COMPUTEROUTPUT">remote      refid      st t when poll reach   delay   offset    disp
 =========================================================================
 *REFCLK(29,1)    .GPS.       0 l   21   32  377     0.00    0.014    0.02
 +bigben.cac.wash .USNO.      1 u  115  128  377    38.48   -0.292    0.46
 +clepsydra.dec.c .GPS.       1 u    2  128  377     6.94    0.044    0.21
 -clock.isc.org   .GOES.      1 u  381 1024  377     6.29   -3.159    0.11
  hpsdlo.sdd.hp.c bigben.ash  2 u   25   32  125    53.68   -9.817    3.69
 -tick.ucla.edu   .USNO.      1 u   70  128  377    19.18   -0.894    0.38
 -usno.pa-x.dec.c .USNO.      1 u   39  128  377     7.05   -0.434    0.26</pre>

So there are valid arguments for allowing some standard queries from prospective or active NTP clients. On the other hand there are also arguments for restricting access:

*   [Configuration changes](/ntpfaq/ntp-s-config/#6144-how-do-i-use-authentication-keys) should be restricted to machines within the own administrative domain at least.
*   You might consider the possibility that a security hole is found in some software which could be exploited to do bad things to your server. Therefore you could restrict or enable certain ranges of IP addresses.

* * *

#### 6.2.6.3. What should be done before announcing public NTP service?

As with any service offered in the Internet, there is a potential to do something stupid. You are strongly advised to do some [monitoring](/ntpfaq/ntp-s-trouble/#81-monitoring) of your server before going public.

Once you are satisfied with the performance data, you should also consider the following questions:

*   Does the server have an offset and stability better or equal to other servers at the same stratum?
*   Does the server have redundant or highly available time sources (reference clocks or peers)?
*   Did you arrange peering with at least one other server at the same or at an even better stratum?
*   Do you want to serve possibly hundreds of unknown clients?
*   Does the Internet connection satisfy the demands for NTP service (good network response times and very few dropped packets)?
*   Is the server machine highly available? Does it start up automatically after a failure? Is there a contact person in case of problems?
*   Are there plans to continue the service for at least six months?

If you answered any of these questions with "No", reconsider the decision to offer public time service.