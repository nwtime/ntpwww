---
title: "ntptrace - trace a chain of NTP servers back to the primary source"
description: "ntptrace is a perl script that uses the ntpq utility to follow the chain of NTP servers from a given host back to the primary time source."
type: archives
---

![gif](/documentation/pic/alice13.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

The rabbit knows the way back.

* * *

#### Table of Contents

* [Synopsis](/documentation/4.2.8-series/ntptrace/#synopsis)
* [Description](/documentation/4.2.8-series/ntptrace/#description)
* [Options](/documentation/4.2.8-series/ntptrace/#options)
* [Bugs](/documentation/4.2.8-series/ntptrace/#bugs)

* * *

#### Synopsis

<code>ntptrace [ -n ] [ -m _maxhosts_ ] [ _server_ ]</code>

* * *

#### Description

<code>ntptrace</code> is a <code>perl</code> script that uses the <code>ntpq</code> utility program to follow the chain of NTP servers from a given host back to the primary time source. For <code>ntptrace</code> to work properly, each of these servers must implement the NTP Control and Monitoring Protocol specified in [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) and enable NTP Mode 6 packets.

If given no arguments, <code>ntptrace</code> starts with <code>localhost</code>. Here is an example of the output from <code>ntptrace</code>:

<pre>% ntptrace
localhost: stratum 4, offset 0.0019529, synch distance 0.144135
server2ozo.com: stratum 2, offset 0.0124263, synch distance 0.115784
usndh.edu: stratum 1, offset 0.0019298, synch distance 0.011993, refid 'WWVB'
</pre>

On each line, the fields are (left to right): the host name, the host stratum, the time offset between that host and the local host (as measured by <code>ntptrace</code>; this is why it is not always zero for <code>localhost</code>), the host synchronization distance, and (only for stratum-1 servers) the reference clock ID. All times are given in seconds. Note that the stratum is the server hop count to the primary source, while the synchronization distance is the estimated error relative to the primary source. These terms are precisely defined in [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf).

* * *

#### Options

<code>**-m _max_hosts_**</code>

: Sets the upper limit of the number of hosts to check (default: unlimited).

<code>**-n**</code>

: Turns off the printing of host names; instead, host IP addresses are given. This may be useful if a nameserver is down.

* * *

#### Bugs

This program makes no attempt to improve accuracy by doing multiple samples.