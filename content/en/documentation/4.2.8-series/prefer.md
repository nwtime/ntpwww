---
title: "Mitigation Rules and the prefer Keyword"
description: "This page summarizes the criteria for choosing from among the survivors of the clock cluster algorithm a set of contributors to the clock discipline algorithm. The criteria are meticulous, since they have to handle many different scenarios that may be optimized for special circumstances, including support for planetary and deep space missions."
type: archives
aliases:
    - /current-stable/prefer/
---

![gif](/documentation/pic/alice11.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Listen carefully to what I say; it is very complicated.

* * *

#### Table of Contents

*   [Introduction and Overview](/documentation/4.2.8-series/prefer/#introduction-and-overview)
*   [Combine Algorithm](/documentation/4.2.8-series/prefer/#combine-algorithm)
*   [Anti-Clockhop Algorithm](/documentation/4.2.8-series/prefer/#anti-clockhop-algorithm)
*   [Peer Classification](/documentation/4.2.8-series/prefer/#peer-classification)
*   [The <tt>prefer</tt> Peer](/documentation/4.2.8-series/prefer/#the-ttprefertt-peer)
*   [Mitigation Rules](/documentation/4.2.8-series/prefer/#mitigation-rules)
*   [The <tt>minsane</tt> Option](/documentation/4.2.8-series/prefer/#the-ttminsanett-option)

* * *

#### Introduction and Overview

This page summarizes the criteria for choosing from among the survivors of the clock cluster algorithm a set of contributors to the clock discipline algorithm. The criteria are very meticulous, since they have to handle many different scenarios that may be optimized for special circumstances, including some scenarios designed to support planetary and deep space missions. For additional information on statistical principles and performance metrics, see the [Performance Metrics](/documentation/4.2.8-series/stats/) page.

Recall the suite of NTP data acquisition and grooming algorithms. These algorithms proceed in five phases. Phase one discovers the available _sources_ and mobilizes an association for each source found. These sources can result from explicit configuration, broadcast discovery or the pool and manycast autonomous configuration schemes. See the [Automatic Server Discovery Schemes](/documentation/4.2.8-series/discover/) page for further information.

Phase two selects the _candidates_ from among the sources by excluding those sources showing one or more of the errors summarized on the [Clock Select Algorithm](/documentation/4.2.8-series/select/) page and to determine the _truechimers_ from among the candidates, leaving behind the _falsetickers_. A server or peer configured with the <code>true</code> option is declared a truechimer independent of this algorithm. Phase four uses the algorithm described on the [Clock Cluster Algorithm](/documentation/4.2.8-series/cluster/) page to prune the statistical outliers from the truechimers, leaving the _survivor list_ as result.

Phase five uses a set of algorithms and mitigation rules to combined the survivor statistics and discipline the system clock. The mitigation rules select from among the survivors a _system peer_ from which a set of system statistics can be inherited and passed along to dependent clients, if any. The mitigation algorithms and rules are the main topic of this page. The clock offset developed from these algorithms can discipline the system clock, either using the [clock discipline algorithm](/documentation/4.2.8-series/discipline/) or using the kernel to discipline the system clock directly, as described on the [Kernel Model for Precision Timekeeping](/documentation/4.2.8-series/kern/) page.


* * *

#### Combine Algorithm

The clock combine algorithm uses the survivor list to produce a weighted average of both offset and jitter. Absent other considerations discussed later, the _combined offset_ is used to discipline the system clock, while the _combined jitter_ is augmented with other components to produce the system jitter statistic inherited by dependent clients, if any.

The clock combine algorithm uses a weight factor for each survivor equal to the reciprocal of the root distance. This is normalized so that the sum of the reciprocals is equal to unity. This design favors the survivors at the smallest root distance and thus the smallest maximum error.

* * *

#### Anti-Clockhop Algorithm

The anti-clockhop algorithm is intended for cases where multiple servers are available on a fast LAN with modern computers. Typical offset differences between servers in such cases are less than 0.5 ms. However, changes between servers can result in unnecessary system jitter. The object of the anti-clockhop algorithm is to avoid changing the current system peer, unless it becomes stale or has significant offset relative to other candidates on the survivor list.

For the purposes of the following description, call the last selected system peer the _old peer_, and the currently selected source the _candidate peer_. At each update, the candidate peer is selected as the first peer on the survivor list sorted by increasing root distance. The algorithm initializes the _clockhop_ _threshold_ with the value of <code>mindist</code>, by default 1 ms.

The anti-clockhop algorithm is called immediately after the combine algorithm. If there was no old peer or the old and candidate peers are the same, the candidate peer becomes the system peer. If the old peer and the candidate peer are different, the algorithm measures the difference between the offset of the old peer and the candidate peer. If the difference exceeds the clockhop threshold, the candidate peer becomes the system peer and the clockhop threshold is restored to its original value. If the difference is less than the clockhop threshold, the old peer continues as the system peer. However, at each subsequent update, the algorithm reduces the clockhop threshold by half. Should operation continue in this way, the candidate peer will eventually become the system peer.

* * *

#### Peer Classification

The behavior of the various algorithms and mitigation rules involved depends on how the various synchronization sources are classified. This depends on whether the source is local or remote and if local, the type of source. The following classes are defined:

1.  A selectable association configured for a remote server or peer is classified as a _client association_. All other selectable associations are classified as _device driver associations_ of one kind or another. In general, one or more sources of either type will be available in each installation.
2.  If all sources have been lost and one or more hosts on a common DMZ network have specified the orphan stratum in the <code>orphan</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command, each of them can become an _orphan parent_. Dependent orphan children on the same DMZ network will see the orphan parents as if synchronized to a server at the orphan stratum. Note that, as described on the [Orphan Mode](/documentation/4.2.8-series/orphan/) page, all orphan children will select the same orphan parent for synchronization.
3.  When a device driver has been configured for pulse-per-second (PPS) signals and PPS signals are being received, it is designated the _PPS driver._ Note that the [Pulse-per-Second driver (type 22)](/documentation/drivers/driver22/) is often used as a PPS driver, but any driver can be configure as a PPS driver if the hardware facilities are available. The PPS driver provides precision clock discipline only within ±0.4 s, so it is always associated with another source or sources that provide the seconds numbering function.
4.  When the [Undisciplined Local Clock driver (type 1)](/documentation/drivers/driver1/) is configured, it is designated the _local driver_. It can be used either as a backup source (stratum greater than zero) should all sources fail, or as the primary source (stratum zero) whether or not other sources are available if the <code>prefer</code> option is present. The local driver can be used when the kernel time is disciplined by some other means of synchronization, such as the NIST <code>lock clock</code> scheme, or another synchronization protocol such as the [IEEE 1588 Precision Time Protocol (PTP)](/reflib/ptp/) or Digital Time Synchronization Service (DTSS).
5.  When the [Automated Computer Time Service driver (type 18)](/documentation/drivers/driver18/) is configured, it is designated the _modem driver_. It is used either as a backup source, should all other sources fail, or as the primary source if the <code>prefer</code> option is present.

* * *

#### The <tt>prefer</tt> Peer

The mitigation rules are designed to provide an intelligent selection of the system peer from among the selectable sources of different types. When used with the <code>server</code> or <code>peer</code> commands, the <code>prefer</code> option designates one or more sources as preferred over all others. While the rules do not forbid it, it is usually not useful to designate more than one source as preferred; however, if more than one source is so designated, they are used in the order specified in the configuration file. If the first one becomes unselectable, the second one is considered and so forth. This order of priority is also applicable to multiple PPS drivers, multiple modem drivers and even multiple local drivers, although that would not normally be useful.

The cluster algorithm works on the set of truechimers produced by the select algorithm. At each round the algorithm casts off the survivor least likely to influence the choice of system peer. If selectable, the prefer peer is never discarded; on the contrary, its potential removal becomes a termination condition. However, the prefer peer can still be discarded by the select algorithm as a falseticker; otherwise, the prefer peer becomes the system peer.

Ordinarily, the combine algorithm computes a weighted average of the survivor offset and jitter to produce the final values. However, if a prefer peer is among the survivors, the combine algorithm is not used. Instead, the offset and jitter of the prefer peer are used exclusively as the final values. In the common case involving a radio clock and a flock of remote backup servers, and with the radio clock designated a prefer peer, the radio clock disciplines the system clock as long as the radio itself remains operational. However, if the radio fails or becomes a falseticker, the combined backup sources continue to discipline the system clock.

* * *

#### Mitigation Rules

As the select algorithm scans the associations for selectable candidates, the modem driver and local driver are segregated for later, but only if not designated a prefer peer. If so designated, the driver is included among the candidate population. In addition, if orphan parents are found, the parent with the lowest metric is segregated for later; the others are discarded. For this purpose the metric is defined as the four-octet IPv4 address or the first four octets of the hashed IPv6 address. The resulting candidates, including any prefer peers found, are processed by the select algorithm to produce a possibly empty set of truechimers.

As previously noted, the cluster algorithm casts out outliers, leaving the survivor list for later processing. The survivor list is then sorted by increasing root distance and the first entry temporarily designated the system peer. At this point the following contributors to the system clock discipline may be available:
*   (potential) system peer, if there are survivors;
*   orphan parent, if present;
*   local driver, if present;
*   modem driver, if present;
*   prefer peer, if present;
*   PPS driver, if present.

The mitigation algorithm proceeds in three steps in turn.
1.  If there are no survivors, the modem driver becomes the only survivor if there is one. If not, the local driver becomes the only survivor if there is one. If not, the orphan parent becomes the only survivor if there is one. If the number of survivors at this point is less than the <code>minsane</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command, the algorithm is terminated and the system variables remain unchanged. Note that <code>minsane</code> is by default 1, but can be set at any value including 0.
2.  If the prefer peer is among the survivors, it becomes the system peer and its offset and jitter are inherited by the corresponding system variables. Otherwise, the combine algorithm computes these variables from the survivor population.
3.  If there is a PPS driver and the system clock offset at this point is less than 0.4 s, and if there is a prefer peer among the survivors or if the PPS peer is designated as a prefer peer, the PPS driver becomes the system peer and its offset and jitter are inherited by the system variables, thus overriding any variables already computed. Note that a PPS driver is present only if PPS signals are actually being received and enabled by the associated driver.

If none of the above is the case, the data are disregarded and the system variables remain as they are.

* * *

#### The <tt>minsane</tt> Option

The <code>minsane</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command, the <code>prefer</code> option of the <code>server</code> and <code>peer</code> commands and the <code>flag</code> option of the <code>fudge</code> command for a selected driver can be used with the mitigation rules to provide many useful configurations. The <code>minsane</code> option specifies the minimum number of survivors required to synchronize the system clock. The <code>prefer</code> option operates as described in previous sections. The <code>flag</code> option enables the PPS signal for the selected driver.

A common scenario is a GPS driver with a serial timecode and PPS signal. The PPS signal is disabled until the system clock has been set by some means, not necessarily the GPS driver. If the serial timecode is within 0.4 s of the PPS signal, the GPS driver is designated the PPS driver and the PPS signal disciplines the system clock. If the serial timecode becomes unreliable, or if the PPS signal is disconnected, the GPS driver stops updating the system clock and so eventually becomes unreachable and is replaced by other sources.

Whether or not the GPS driver disables the PPS signal when the timecode becomes unreliable is at the discretion of the driver. Ordinarily, the PPS signal is disabled in this case; however, when the GPS receiver has a precision holdover oscillator, the driver may elect to continue PPS discipline . In this case, <code>minsane</code> can be set to zero so the PPS signal continues to discipline the system clock.
