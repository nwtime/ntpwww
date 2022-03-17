---
title: "NTP Interleaved Modes"
type: archives
noindex: true
---

![gif](/archives/pic/pogo4.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

You need a little magic.

Last update: 03-May-2009 3:37 UTC

* * *

In the protocol described in the NTP specification and implemented today the transmit timestamp is captured before the MD5 digest is computed and the packet is sent, while the receive timestamp is captured after the packet is received. For enhanced accuracy it is desirable to capture the timestamps as close to the wire as possible; i.e., with hardware assist or with a modified driver.

The problem is, while the receive timestamp could in principle be piggybacked in the receive buffer, the transmit timestamp cannot ordinarily be transmitted in the same packet. A solution for this problem is the two-step or interleaved protocol described on this page and included in the current reference implementation. In this experimental variant the transmit timestamp for one packet is actually carried in the immediately following packet. The trick, however, is to implement the interleaved protocol without changing the NTP packet header format, without compromising backwards compatibility and without compromising the error recovery properties.

Currently, the reference implementation uses only software timestamps (softstamps). The receive softstamp is captured at software interrupt time and before the buffer is queued for later processing. The reference implementation captures a softstamp before the message digest routine and another after the send-packet routine. In this design the latter timestamp can be considered most accurate, as it avoids the kernel latencies and queueing mechanisms. The difference, called the interleaved or output delay, varies from 16 ms for a dual-core, 2.8 GHz Pentium 4 running FreeBSD 6.1 to 1100 ms for a Sun Blade 1500 running Solaris 10.

Performacne varies widely between machines and network interface cards on a 100-Mb switched Ethernet where the NTP packet is about 1000 bits or 10 ms. On two identical Pentium 4 machines in symmetric mode, the measured output delay is 16 ms and remaining one-way delay components 45-150 ms. Two LAN segments account for 20 ms, which leaves 25-130 ms for input delay. On two identical UltraSPARC machines running Solaris 10 in symmetric mode, the measured output delay is 160 ms and remaining one-way delay components 195 ms. Two LAN segments account for 20 ms, which leaves 175 ms for input delay.

Performance with the Pentia show a residual jitter of about 20 ms, which is by far the best performance so far. However, much better performance could result if the input delay could be reduced or elminated with driver or hardware timestamps. Should that be done, performance should be in the same order as the PPS and kernel discipline, which is in the order of 2 ms.

Interleaved modes can be used only in NTP symmetric and broadcast modes. It is activated by the <code>xleave</code> option with the <code>peer or</code> <code>broadcast</code> configuration commands. The NTP protocol automatically reconfigures in normal or interleaved mode as required. Ordinary broadcast clients can use the same servers as interleaved broadcast clients at the same time. Further details are in the white paper [NTP Interleaved On-Wire Protocol](/reflib/onwire/) and the briefing [Interleaved Synchronization Protocols for LANs and Space Data Links](/reflib/brief/onwire/onwire.ppt).

* * *

![gif](/archives/pic/pogo1a.gif)
