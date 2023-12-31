---
title: "ntptrace - trace a chain of NTP servers back to the primary source"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/alice13.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

The rabbit knows the way back.

* * *

#### Table of Contents

* [Synopsis](/documentation/4.2.2-series/ntptrace/#synopsis)
* [Description](/documentation/4.2.2-series/ntptrace/#description)
* [Options](/documentation/4.2.2-series/ntptrace/#options)
* [Bugs](/documentation/4.2.2-series/ntptrace/#bugs)

* * *

#### Synopsis

<code>ntptrace [ -vdn ] [ -r _retries_ ] [ -t _timeout_ ] [ _server_ ]</code>

* * *

#### Description

<code>ntptrace</code> determines where a given Network Time Protocol (NTP) server gets its time from, and follows the chain of NTP servers back to their master time source. If given no arguments, it starts with <code>localhost</code>. Here is an example of the output from <code>ntptrace</code>:

<pre>% ntptrace
localhost: stratum 4, offset 0.0019529, synch distance 0.144135
server2ozo.com: stratum 2, offset 0.0124263, synch distance 0.115784
usndh.edu: stratum 1, offset 0.0019298, synch distance 0.011993, refid 'WWVB'
</pre>

On each line, the fields are (left to right): the host name, the host stratum, the time offset between that host and the local host (as measured by <code>ntptrace</code>; this is why it is not always zero for <code>localhost</code>), the host synchronization distance, and (only for stratum-1 servers) the reference clock ID. All times are given in seconds. Note that the stratum is the server hop count to the primary source, while the synchronization distance is the estimated error relative to the primary source. These terms are precisely defined in RFC-1305.

* * *

#### Options

<code>**-d**</code>

: Turns on some debugging output.
			
<code>**-n**</code>

: Turns off the printing of host names; instead, host IP addresses are given. This may be useful if a nameserver is down.
			
<code>**-r _retries_**</code>

: Sets the number of retransmission attempts for each host (default = 5).
			
<code>**-t _timeout_**</code>

: Sets the retransmission timeout (in seconds) (default = 2).
			
<code>**-v**</code>

: Prints verbose information about the NTP servers.

* * *

#### Bugs

This program makes no attempt to improve accuracy by doing multiple samples.