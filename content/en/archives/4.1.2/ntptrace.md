---
title: "ntptrace - trace a chain of NTP servers back to the primary source"
type: archives
---

![gif](/archives/pic/alice13.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

The rabbit knows the way back.

* * *

#### Table of Contents

* [Synopsis](/archives/4.1.2/ntptrace/#synopsis)
* [Description](/archives/4.1.2/ntptrace/#description)
* [Options](/archives/4.1.2/ntptrace/#options)
* [Bugs](/archives/4.1.2/ntptrace/#bugs)

* * *

#### Synopsis

<tt>ntptrace [ -vdn ] [ -r _retries_ ] [ -t _timeout_ ] [ _server_ ]</tt>

* * *

#### Description

<tt>ntptrace</tt> determines where a given Network Time Protocol (NTP) server gets its time from, and follows the chain of NTP servers back to their master time source. If given no arguments, it starts with <tt>localhost</tt>. Here is an example of the output from <tt>ntptrace</tt>:

<pre>% ntptrace
localhost: stratum 4, offset 0.0019529, synch distance 0.144135
server2ozo.com: stratum 2, offset 0.0124263, synch distance 0.115784
usndh.edu: stratum 1, offset 0.0019298, synch distance 0.011993, refid 'WWVB'
</pre>

On each line, the fields are (left to right): the host name, the host stratum, the time offset between that host and the local host (as measured by <tt>ntptrace</tt>; this is why it is not always zero for "<tt>localhost</tt>"), the host synchronization distance, and (only for stratum-1 servers) the reference clock ID. All times are given in seconds. Note that the stratum is the server hop count to the primary source, while the synchronization distance is the estimated error relative to the primary source. These terms are precisely defined in RFC-1305.

* * *

#### Options

<dt><tt>-d</tt>

Turns on some debugging output.
			
<dt><tt>-n</tt>

Turns off the printing of host names; instead, host IP addresses are given. This may be useful if a nameserver is down.
			
<dt><tt>-r <i>retries</i></tt>

Sets the number of retransmission attempts for each host (default = 5).
			
<dt><tt>-t <i>timeout</i></tt>

Sets the retransmission timeout (in seconds) (default = 2).
			
<dt><tt>-v</tt>

Prints verbose information about the NTP servers.

* * *

#### Bugs

This program makes no attempt to improve accuracy by doing multiple samples.
