---
title: "Mitigation Rules and the prefer Keyword"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/alice11.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Listen carefully to what I say; it is very complicated.

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.6-series/prefer/#introduction)
*   [Peer Classification](/documentation/4.2.6-series/prefer/#peer-classification)
*   [The <tt>prefer</tt> Peer](/documentation/4.2.6-series/prefer/#the-ttprefertt-peer)
*   [Mitigation Rules](/documentation/4.2.6-series/prefer/#mitigation-rules)
*   [The <tt>minsane</tt> Option](/documentation/4.2.6-series/prefer/#the-ttminsanett-option)

* * *

#### Introduction

This page summarizes the criteria for choosing from among a number of potential sources suitable contributors to the clock discipline algorithm. The criteria are very meticulous, since they have to handle many different scenarios that may be optimized for peculiar circumstances, including some scenarios designed to support planetary and deep space missions.

Recall the suite of NTP data acquisition and grooming algorithms as these algorithms proceed in five phases. Phase one discovers the available sources and mobilizes an association for each candidate found. These candidates can result from explicit configuration, broadcast discovery or the pool and manycast autonomous configuration schemes. Phase two grooms the selectable candidates excluding those sources showing one or more of the following errors:

1.  A stratum error occurs if (1) the source had never been synchronized or (2) the stratum of the source is below the <code>floor</code> option or not below the <code>ceiling</code> option specified by the <code>tos</code> command. The default value for these options are 0 and 16, respectively.
2.  A distance error occurs for a remote source if the root distance is not below the distance threshold <code>maxdist</code> option of the <code>tos</code> command. The default value for this option is 1.5 s for networks including only the Earth, but this should be increased to 2.5 s for networks including the Moon.
3.  A loop error occurs if the source is synchronized to the client of if the source is synchronized to the same source as the client.
4.  An unreachable error occurs if the source is unreachable or if the <code>server</code> or <code>peer</code> command for the source includes the <code>noselect</code> option.

Phase three uses an intersection algorithm to select the truechimers from among the candidates, leaving behind the falsetickers. A server or peer configured with the <code>true</code> option is ipso facto a truechimer independent of this algorithm. Phase four uses a clustering algorithm to cast off statistical outliers from the truechimers until a set of survivors not less than the number specified as the <code>minclock</code> option of the <code>tos</code> command, with default 3. Phase five uses a set of mitigation rules to select from among the survivors a system peer from which a set of system statistics can be inherited and passed along to a dependent client population. The clock offset developed from these algorithms can discipline the system clock either using the <code>ntpd</code> clock discipline algorithm or enable the kernel to discipline the system clock directly, as described on the [A Kernel Model for Precision Timekeeping](/documentation/4.2.6-series/kern/) page. Phase five is the topic of this page.

* * *

#### Peer Classification

The behavior of the various algorithms and mitigation rules involved depends on how the various synchronization sources are classified. This depends on whether the source is local or remote and if local the type of source. The following classes are defined:

1.  An association configured for a remote server or peer is classified simply as a _server_. All other associations are classified as a _device driver_ of one kind or another. In general, one or more sources of either or both types will be configured in each installation.
2.  If all sources have been lost and the orphan stratum has been specified by the <code>orphan</code> option of the <code>tos</code> command, a pseudo-source called the _orphan parent_ is created with offset and jitter both zero. Dependent orphan children will see the orphan parent as if synchronized to a server at the orphan stratum.If the only survivor is the orphan parent, it becomes the system peer and its clock offset and jitter are inherited by the corresponding system variables. Note that by design all the orphan children having the same set of orphan parents will select the same parent.
3.  When a device driver has been configured for pulse-per-second (PPS) signals and PPS signals are being received, it is designated the _PPS driver._ Note that the Pulse-per-Second driver (type 22) is often used as a PPS driver, but any driver can be operated as a PPS driver as well. The PPS driver provides precision clock discipline only within +-0.5 s, so is always associated with another source or sources that provide the seconds numbering function.
4.  When the Undisciplined Local Clock driver (type 1) is configured, it is designated the _local driver_. This driver is used either as a backup source (stratum greater than zero) should all sources fail, or as the primary source (stratum zero) in cases where the kernel time is disciplined by some other means of synchronization, such as the NIST <code>lockclock</code> scheme, or another synchronization protocol such as the Digital Time Synchronization Service (DTSS).
5.  When the Automated Computer Time Service driver (type 18) is configured, it is designated the _modem driver_. This is used either as a backup source, should all other sources fail, or as the (only) primary source.

* * *

#### The <tt>prefer</tt> Peer

The mitigation rules are designed to provide an intelligent selection of the system peer from among the survivors of different types. When used with the <code>server</code> or <code>peer</code> commands, the <code>prefer</code> option designates one or more survivors as preferred over all others. While the rules do not forbid it, it is usually not useful to designate more than one source as preferred; however, if more than one source is so designated, they are used in the order specified in the configuration file; that is, if the first one becomes unselectable, the second one is considered and so forth. This order of priority is also applicable to multiple PPS drivers, multiple modem drivers and even multiple local drivers, although that would not normally be useful.

The clustering algorithm works on the set of truechimers produced by the intersection algorithms. Ordinarily, any one of them can in principle provide correct time; however, due to various latency variations, not all can provide the most accurate and stable time. The clustering algorithm, processes the truechimers in one or more rounds to cast off a statistical outlier until no more than the <code>minclock</code> option of the <code>tos</code> command are left. The default for this option is 3.

In the prefer scheme the clustering algorithm is modified so that the prefer peer is never discarded; on the contrary, its potential removal becomes a rounds-termination condition. However, the prefer peer can still be discarded by the intersection algorithm as a falseticker. To avoid this, it is usually wise to increase the <code>mindist</code> option of the <code>tos</code> command from the default .005 s to something like .05 s.

Ordinarily, the combining algorithm computes a weighted average of the survivor offsets to produce the final synchronization source. However, if a prefer peer is among the survivors, the combining algorithm is not used. Instead, the offset of the prefer peer is used exclusively as the final synchronization source. In the common case involving a radio clock and a flock of remote backup servers, and with the radio clock designated a prefer peer, the result is that the radio clock normally disciplines the system clock as long as the radio itself remains operational. However, if the radio fails or becomes a falseticker, the averaged backup sources continue to discipline the system clock.

* * *

#### Mitigation Rules

As the selection algorithm scans the associations for selectable candidates, the modem driver and local driver are segregated for later, but only if not designated a prefer peer. If so designated, a driver is included among the candidate population. In addition, if orphan parents are found the parent with the lowest metric is segregated for later; the others are discarded. For this purpose the metric is defined as the four-octet IPv4 address or the first four octets of the hashed IPv6 address. The resulting candidates, including any prefer peers found, are processed by the intersection to produce a possibly empty set of truechimers. The clustering algorithm ranks the truechimers first by stratum then by synchronization distance and designates the survivor with the lowest distance as the potential system peer.

If one or more truechimers support a pulse-per-second (PPS) signal and the PPS signal is operating correctly, it is designated a PPS driver. If more than one PPS diver are found, only the first one is used. The PPS driver is not included in the combining algorithm and is mitigated separately.

At this point we have the following contributors to the system clock discipline:

*   (potential) system peer, if there are survivors;
*   orphan parent, if present;
*   local driver and zero offset, if present;
*   modem driver and modem offset, if present;
*   prefer peer and offset, if present;
*   PPS driver and offset, if present.

The mitigation algorithm proceeds in three steps in turn.

1.  If there are no survivors, the modem driver becomes the only survivor if there is one. If not, the local driver becomes the only survivor if there is one. If not, the orphan parent becomes the only survivor if there is one. If the number of survivors at this point is less than the <code>minsane</code> option of the <code>tos</code> command, the algorithm is terminated and the system variables remain unchanged. Note that <code>minsane</code> is by default 1, but can be set at any value including 0.
2.  If the prefer peer is among the survivors, it becomes the system peer and its clock offset and jitter are inherited by the corresponding system variables. Otherwise, the combining algorithm computes these variables from the survivor population.
3.  If there is a PPS driver and the system clock offset at this point is less than 0.4 s, and if there is a prefer peer among the survivors or if the PPS peer is designated as a prefer peer, the PPS driver becomes the system peer and its offset and jitter are inherited by the system variables, thus overriding any variables already computed. Note that a PPS driver is present only if PPS signals are actually being received and enabled by the associated driver.

If none of the above is the case, the data are disregarded and the system variables remain as they are.

* * *

#### The <tt>minsane</tt> Option

The <code>minsane</code> option of the <code>tos</code> command, the <code>prefer</code> option of the <code>server</code> and <code>peer</code> commands and the <code>flag</code> options of the <code>fudge</code> command for the PPS driver can be used with the mitigation rules to provide many useful configurations. The <code>minsane</code> option specifies the minimum number of survivors required to synchronized the system clock. The <code>prefer</code> option designates the prefer peer. The driver-dependent <code>flag</code> options enable the PPS driver for various conditions.

A common scenario is a GPS driver with a serial timecode and PPS signal. The PPS signal is disabled until the system clock has been set by some means, not necessarily the GPS driver. If the serial timecode is within 0.4 s of the PPS signal, the GPS driver is designated the PPS driver and the PPS signal disciplines the system clock. If no GPS satellites are in view, or if the PPS signal is disconnected, the GPS driver stops updating the system clock and so eventually becomes unreachable and replaced by other sources..

Whether or not the GPS driver disables the PPS signal when unreachable is at the discretion of the driver. Ordinarily, the PPS signal would be disabled in this case; however, When the GPS receiver has a precision holdover oscillator, the driver may elect to continue PPS operation. In this case the PPS signal continues to discipline the system clock.
