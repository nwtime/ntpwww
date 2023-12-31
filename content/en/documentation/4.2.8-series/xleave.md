---
title: "NTP Interleaved Modes"
description: "In interleaved mode, the transmit drivestamp for one packet is carried in the immediately following packet. Interleaved mode can be used only in NTP symmetric and broadcast modes. It is activated by the xleave option with the peer or broadcast configuration commands."
type: archives
aliases:
    - /current-stable/xleave/
---

![gif](/documentation/pic/pogo4.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

You need a little magic.

* * *

In the protocol described in the NTP specification and reference implementation up to now, the transmit timestamp, which is captured before the message digest is computed and the packet queued for output, is properly called as a _softstamp_. The receive timestamp, which is captured after the input driver interrupt routine and before the packet is queued for input, is properly called a _drivestamp_. For enhanced accuracy it is desirable to capture the transmit timestamp as close to the wire as possible; for example, after the output driver interrupt routine.

In other words, we would like to replace the transmit softstamp with a drivestamp, but the problem is the transmit drivestamp is available only after the packet has been sent. A solution for this problem is the two-step or interleaved protocol described on this page and included in the current reference implementation. In interleaved modes the transmit drivestamp for one packet is actually carried in the immediately following packet. The trick, however, is to implement the interleaved protocol without changing the NTP packet header format, without compromising backwards compatibility and without compromising the error recovery properties.

The reference implementation captures a softstamp before the message digest routine and a drivestamp after the output interrupt routine. In this design the latter timestamp can be considered most accurate, as it avoids the various queuing and transmission latencies. The difference between the two timestamps, which is called the interleaved or output delay, varies from 16 μs (microseconds) for a dual-core Pentium running FreeBSD 6.1 to 1100 μs (microseconds) for a Sun Blade 1500 running Solaris 10.

Interleaved mode can be used only in NTP symmetric and broadcast modes. It is activated by the <code>xleave</code> option with the <code>peer</code> or <code>broadcast</code> configuration commands. A broadcast server configured for interleaved mode is transparent to ordinary broadcast clients, so both ordinary and interleaved broadcast clients can use the same packets. An interleaved symmetric active peer automatically switches to ordinary symmetric mode if the other peer is not capable of operation in interleaved mode.

As demonstrated in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/), the interleaved modes have the same resistance to lost packets, duplicate packets, packets crossed in flight and protocol restarts as the ordinary modes. An application of the interleaved symmetric mode in space missions is presented in the white paper [Time Synchronization for Space Data Links](/reflib/proximity/).

* * *

![gif](/documentation/pic/pogo1a.gif)
