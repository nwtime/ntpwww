---
title: "Rate Management and the Kiss-o'-Death Packet"
type: archives
---

![gif](/archives/pic/boom4.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

Our junior managers and the administrators.

Last update: 	03-May-2009 3:34 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.6-series/rate/#introduction)
*   [Poll Rate Control](/archives/4.2.6-series/rate/#poll-rate-control)
*   [Burst Control](/archives/4.2.6-series/rate/#burst-control)
*   [Average Headway Time](/archives/4.2.6-series/rate/#average-headway-time)
*   [Guard Time](/archives/4.2.6-series/rate/#guard-time)
*   [The Kiss of Death Packet](/archives/4.2.6-series/rate/#the-kiss-of-death-packet)

* * *

#### Introduction

This page describes the various rate management provisions in NTPv4. Details about the configuration commands and options are given on the [Configuration Options](/archives/4.2.6-series/confopt/) page. Details about the cryptographic authentication schemes are given on the [Authentication Options](/archives/4.2.6-series/authopt/) page. Details about the automatic server discovery schemes are described on the [Automatic Server Discovery Schemes](/archives/4.2.6-series/manyopt/) page. Additional information is available in the papers, reports, memoranda and briefings on the [NTP Project](/reflib/ntp/) page.

Some national time metrology laboratories, including NIST and USNO, use the <code>ntpd</code> reference implementation in their very busy public time servers. They operate multiple servers behind load-balancing devices to support aggregate rates up to several thousand packets per second. The servers need to defend themselves against all manner of broken implementations that can clog the server and network infrastructure. On the other hand, friendly <code>ntpd</code> clients need to avoid configurations that can result in unfriendly rates.

There are several features in <code>ntpd</code> designed to defend the servers, clients and network against accidental or intentional flood attack. On the other hand these features are also used to insure <code>ntpd</code> is a good citizen, even if configured in unfriendly ways. The ground rules are:

*   Send at the lowest rate consistent with the expected accuracy expectations.
*   Maintain strict minimum average headway and guard times, even if multiple burst options and/or the Autokey protocol are operating.
*   When the first packet of a burst is sent to a server, do not send further packets until the first packet has been received from the server.
*   Upon receiving a Kiss-o'-Death packet (see below), immediately reduce the sending rate.

Rate management involves four algorithms to manage resources: (1) poll rate control, (2) burst control, (3) average headway time and (4) guard time. These are described in following sections.

* * *

#### Poll Rate Control

Control of the poll interval is an intricate balance between expected acuracy and network load. The poll interval is constrained by the lower limit <code>minpoll</code> and upper limit <code>maxpoll</code> options of the <code>server</code> command and represented by the poll exponent in log<sub>2</sub> s units. The limits default to 6 (64 s) and 10 (1024 s), respectively, which are appropriate for the vast majority of cases. The default limits can be changed with these options to a minimum set by the <code>average</code> option of the <code>discard</code> command (see below) to a maximum of 17 (36 h). Unless the best possible accuracy is required, the well mannered NTP client automatically increases the poll interval to the maximum when possible, whether or not the server is reachable. The current poll interval for each association is displayed by the <code>ntpq</code> program [<code>pe</code>](/archives/4.2.6-series/ntpq/#pe) command. The global poll interval/time constant is displayed as the poll system variable by the rv command. The minimum global poll interval/time constant is displayed as the minpoll system variable by the [<code>rv</code>](/archives/4.2.6-series/ntpq/#pe) command.

As a rule of thumb, the expected errors increase by a factor of two as the poll interval increases by a factor of four. The <code>ntpd</code> poll interval algorithm slowly increases the poll interval when jitter dominates the error budget, but quickly reduces the interval when wander dominates it. The algorithm uses a jiggle counter which operates over the range from <font face="symbol">-</font>30 to +30 and is initialized at 0. If the measured offset is less than four times the measured average jitter, the counter is increased by the pollcurrent exponent; if not, it is decreased by twice the poll exponent. If the counter reaches +30, the poll exponent is incremented by 1; if the counter reaches <font face="symbol">-</font>30, the exponent is decremented by 1. In either case the counter is set to 0.

The poll interval is proportional to the time constant of the feedback loop which disciplines the system clock. The optimum time constant depends on the network time jitter and the clock oscillator frequency wander. Errors due to jitter decrease as the time constant increases, while errors due to wander decrease as the time constant decreases. The two error characteristics intersect at a point called the Allan intercept, which represents the ideal time constant. With a compromise Allan intercept of 2000 s, the optimim poll interval is about 64 s, which corresponds to a poll exponent of 6.

There is normally no need to change the poll limits, as the poll interval is managed automatically as a function of prevailing jitter and wander. The most common exceptions are the following.

*   With fast, lightly loaded LANs and modern processors, the nominal Allan intercept is about 500 s. In these cases the expected errors can be further reduced using a poll exponent of 4 (16 s). In the case of the pulse-per-second (PPS) driver, this is the recommended value.
*   With symmetric modes the most stable behavior results when both peers are configured in symmetric active mode with matching poll intervals of 6 (64 s).
*   The poll interval should not be modified for reference clocks, with the single exception the ACTS telephone modem driver. In this case the recommended minimum and maximum intervals are 12 (1.1 h) and 17 (36 h), respectively.

* * *

#### Burst Control

Occasionally it is necessary to send packets at intervals less than the poll interval. For instance, with the <code>burst</code> and <code>iburst</code> options of the <code>server</code> command, the poll algorithm sends a burst of several packets at 2-s intervals. The <code>ntpd</code> poll algorithm avoids sending needless packets if the server is not responding. The client begins a burst with a single packet. When the first packet is received from the server, the client continues with the remaining packets in the burst. If the first packet is not received within 64 s, it will be sent again for two additional retries before beginning backoff. The result is to minimize network load if the server is not responding.

For the <code>iburst</code> option the number of packets in the burst is six, which is the number normally needed to synchronize the clock; for the <code>burst</code> option, the number of packets in the burst is determined by the difference between the poll interval and the minimum poll interval set by the <code>minpoll</code> option of the [<code>server</code>](/archives/4.2.6-series/confopt/#server) command. For instance, with a poll exponent of 6 (64 s), only a single packet is sent for every poll, while the full number of eight packets is sent at poll intervals of 9 (512 s) or more.

* * *

#### Average Headway Time

There are two features in <code>ntpd</code> to manage the interval between one packet and the next. These features make use of a set of counters: a client output counter for each association and a server input counter for each distinct client address. Each counter increments by a value called the headway when a packet is processed and decrements by one each second. The default minimum average headway in <code>ntpd</code> is 8 s, but this can be changed using the <code>average</code> option of the <code>discard</code> command, but not less than 3 (8 s).

If the <code>iburst</code> or <code>burst</code> options are present, the poll algorithm sends a burst of packets instead of a single packet at each poll opportunity. The NTPv4 specification requires that bursts contain no more than eight packets; so, starting from an output counter value of zero, the maximum counter value or output ceiling can be no more than eight times the minimum poll interval set by the <code>minpoll</code> option of the [<code>server</code>](/archives/4.2.6-series/confopt/#server) command. However, if the burst starts with a counter value other than zero, there is a potential to exceed the ceiling. The poll algorithm avoids this by computing an additional headway time so that the next packet sent will not exceed the ceiling. Additional headway time can result from Autokey protocol operations. Designs such as this are often called leaky buckets. The current headway is displayed as the headway peer variable by the <code>ntpq</code> [<code>rv</code>](/archives/4.2.6-series/ntpq/#pe) command.

The <code>ntpd</code> input packet routine uses a special list of entries, one for each distinct client address found. Each entry includes an IP address, input counter and interval since the last packet arrival. The entries are ordered by interval from the smallest to the largest. As each packet arrives, the IP source address is compared to the IP address in each entry in turn. If a match is found the entry is removed and inserted first on the list. If the IP source address does not match any entry, a new entry is created and inserted first, possibly discarding the last entry on the list if it is full. Observers will note this is the same algorithm used for page replacement in virtual memory systems.

In the virtual memory algorithm the entry of interest is the last, whereas here the entry of interest is the first. The input counter is decreased by the interval since it was last referenced, but not below zero. If the value of the counter plus the headway is greater than the input ceiling set by the <code>average</code> option, the packet is discarded. Otherwise, the counter is increased by the headway and the packet is processed. The result is, if the client maintains a maximum average headway not less than the input ceiling and transmits no more than eight packets in a burst, the input counter will not exceed the ceiling.

* * *

#### Guard Time

A review of past client abuse incidence shows the most frequent scenario is a broken client that attempts to send a number of packets at rates of one per second or more. On one occasion due to a defective client design, over 750,000 clients fell into this mode. There have been occasions where this abuse has persisted for days at a time. These scenarios are the most damaging, as they can threaten not only the victim server but the network infrastructure as well.

In the <code>ntpd</code> design the minimum headway between the last packet received and the current packet is called the guard time. If the headway is less than the guard time, the packet is discarded. The guard time defaults to 2 s, but this can be changed using the <code>minimum</code> option of the <code>discard</code> command.

* * *

#### The Kiss-of-Death Packet

Ordinarily, packets denied service are simply dropped with no further action except incrementing statistics counters. Sometimes a more proactive response is needed to cause the client to slow down. A special packet format has been created for this purpose called the kiss-o'-death (KoD) packet. KoD packets have leap indicator 3, stratum 0 and the reference identifier set to a four-byte ASCII code. At present, only one code <code>RATE</code> is sent by the server if the <code>limited</code> and <code>kod</code> flags are set in the [<code>restrict</code>](/archives/4.2.6-series/accopt/#restrict) command and the rate limit is exceeded.

A client receiving a KoD packet is expected to slow down; however, no explicit mechanism is specified in the protocol to do this. In the current reference implementation, the server sets the packet poll to the greater of (a) minimum average headway and (b) client packet poll. The client sets the peer poll field to the maximum of (a) minimum average headway and (b) server packet poll. For KoD packets (only), the minimum peer poll is clamped not less than the peer poll and the headway temporarily increased.

At present there is only one KoD packet with code <code>RATE.</code> In order to make sure the client notices the KoD, the receive and transmit timestamps are set to the transmit timestamp of the client packet and all other fields left as in the client packet. Thus, even if the client ignores the KoD, it cannot do any useful time computations. KoDs themselves are rate limited in the same way as arriving packets in order to deflect a flood attack.