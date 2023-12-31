---
title: "Performance Metrics"
description: "This page describes several statistics provided in the NTP specification and reference implementation and how they determine the accuracy and error measured during routine and exceptional operation."
type: archives
aliases:
    - /current-stable/stats/
---

#### Table of Contents

*   [Introduction](/documentation/4.2.8-series/stats/#introduction)
*   [Statistics Summary](/documentation/4.2.8-series/stats/#statistics-summary)
*   [Quality of Service](/documentation/4.2.8-series/stats/#quality-of-service)

* * *

#### Introduction

This page describes several statistics provided in the NTP specification and reference implementation and how they determine the accuracy and error measured during routine and exceptional operation. These statistics provide the following information.

*   Nominal estimate of the server clock time relative to the client clock time. This is called _clock offset_ symbolized by the Greek letter <code>θ</code>.
*   Roundtrip system and network delay measured by the on-wire protocol. This is call _roundtrip delay_ symbolized by the Greek letter <code>δ</code>.
*   Potential clock offset error due to the maximum uncorrected system clock frequency error. This is called _dispersion_ symbolized by the Greek letter <code>ε</code>.
*   Expected error, consisting of the root mean square (RMS) nominal clock offset sample differencess in a sliding window of several samples. This is called _jitter_ symbolized by the Greek letter <code>φ</code>.

Figure 1 shows how the various measured statistics are collected and compiled to calibrate NTP performance.

![gif](/documentation/pic/stats.gif)

**Figure 1: Statistics Budget**

The data represented in boxes labeled Server are contained in fields in packet received from the server. The data represented in boxes labeled Peer are computed by the on-wire protocol, as described below. The algorithms of the box labeled Selection and Combining Algorithms process the peer data to select a system peer. The System box represents summary data inherited from the system peer. These data are available to application programs and dependent downstream clients.

* * *

#### Statistics Summary

Each NTP synchronization source is characterized by the offset <code>θ</code> and delay <code>δ</code> samples measured by the on-wire protocol, as described on the [How NTP Works](/documentation/4.2.8-series/warp/) page. In addition, the dispersion <code>ε</code> sample is initialized with the sum of the source precision <code>ρ<sub>R</sub></code> and the client precision <code>ρ</code> (not shown) as each source packet is received. The dispersion increases at a rate of 15 μs/s after that. For this purpose, the precision is equal to the latency to read the system clock. The offset, delay and dispersion are called the sample statistics.

> **NOTE:** In very fast networks where the client clock frequency is not within 1 PPM or so of the server clock frequency, the roundtrip delay may have small negative values. This is usually a temporary condition when the client is first started. When using the roundtrip delay in calculations, negative values are assumed zero.

In a window of eight (offset, delay, dispersion) samples, the algorithm described on the [Clock Filter Algorithm](/documentation/4.2.8-series/filter/) page selects the sample with minimum delay, which generally represents the most accurate offset statistic. The selected offset sample determines the _peer offset_ and _peer delay_ statistics. The _peer dispersion_ is a weighted average of the dispersion samples in the window. These quantities are recalculated as each update is received from the source. Between updates, both the sample dispersion and peer dispersion continue to grow at the same rate, 15 μs/s. Finally, the _peer jitter_ <code>φ</code> is determined as the RMS differences between the offset samples in the window relative to the selected offset sample. The peer statistics are recorded by the <code>peerstats</code> option of the [<code>filegen</code>](/documentation/4.2.8-series/monopt/#monitoring-commands-and-options) command. Peer variables are displayed by the <code>rv</code> command of the [<code>ntpq</code>](/documentation/4.2.8-series/ntpq/#peer-variables) program.

The clock filter algorithm continues to process updates in this way until the source is no longer reachable. Reachability is determined by an eight-bit shift register, which is shifted left by one bit as each poll packet is sent, with 0 replacing the vacated rightmost bit. Each time a valid update is received, the rightmost bit is set to 1. The source is considered reachable if any bit is set to 1 in the register; otherwise, it is considered unreachable. When a source becomes unreachable, a dummy sample with "infinite" dispersion is inserted in the filter window at each poll, thus displacing old samples. This causes the peer dispersion to increase eventually to infinity.

The composition of the source population and the system peer selection is redetermined as each update from each source is received. The system peer and system variables are determined as described on the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.8-series/prefer/) page. The system variables `Θ, Δ, Ε` and `Φ` are updated from the system peer variables of the same name and the system stratum set one greater than the system peer stratum. The system statistics are recorded by the <code>loopstats</code> option of the [<code>filegen</code>](/documentation/4.2.8-series/monopt/#monitoring-commands-and-options) command. System variables are displayed by the <code>rv</code> command of the [<code>ntpq</code>](/documentation/4.2.8-series/ntpq/#system-variables) program.

Although it might seem counterintuitive, a cardinal rule in the selection process is, once a sample has been selected by the clock filter algorithm, older samples are no longer selectable. This applies also to the clock select algorithm. Once the peer variables for a source have been selected, older variables of the same or other sources are no longer selectable. The reason for these rules is to limit the time delay in the clock discipline algorithm. This is necessary to preserve the optimum impulse response and thus the risetime and overshoot.

This means that not every sample can be used to update the peer variables, and up to seven samples can be ignored between selected samples. This fact has been carefully considered in the discipline algorithm design with due consideration for feedback loop delay and minimum sampling rate. In engineering terms, even if only one sample in eight survives, the resulting sample rate is twice the Nyquist rate at any time constant and poll interval.

* * *

#### Quality of Service

This section discusses how an NTP client determines the system performance using a peer population including reference clocks and remote servers. This is determined for each peer from two statistics, _peer jitter_ and _root distance._ Peer jitter is determined from various jitter components as described above. It represents the expected error in determining the clock offset estimate. Root distance represents the maximum error of the estimate due to all causes.

The root distance statistic is computed as one-half the _root delay_ of the primary source of time; i.e., the reference clock, plus the _root dispersion_ of that source. The root variables are included in the NTP packet header received from each source. At each update the root delay is recomputed as the sum of the root delay in the packet plus the peer delay, while the root dispersion is recomputed as the sum of the root dispersion in the packet plus the peer dispersion.

> **NOTE:**
In order to avoid timing loops, the root distance is adjusted to the maximum of the above computation and a _minimum threshold._ The minimum threshold defaults to 1 ms, but can be changed according to client preference using the <code>mindist</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command.

A source is considered selectable only if its root distance is less than the _select threshold_, by default 1.5 s, but can be changed according to client preference using the <code>maxdist</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command. When an upstream server loses all sources, its root distance apparent to dependent clients continues to increase. The clients are not aware of this condition and continue to accept synchronization as long as the root distance is less than the select threshold.

The root distance statistic is used by the select, cluster and mitigation algorithms. In this respect, it is sometimes called the _synchronization distance_ often shortened simply to _distance_. The root distance is also used in the following ways.

*   Root distance defines the maximum error of the clock offset estimate due to all causes as long as the source remains reachable.
*   Root distance defines the upper and lower limits of the correctness interval. This interval represents the maximum clock offset for each of possibly several sources. The clock select algorithm computes the intersection of the correctness intervals to determine the truechimers from the selectable source population.
*   Root distance is used by the clock cluster algorithm as a weight factor when pruning outliers from the truechimer population.
*   The (normalized) reciprocal of the root distance is used as a weight factor by the combine algorithm when computing the system clock offset and system jitter.
*   Root distance is used by the mitigation algorithm to select the system peer from among the cluster algorithm survivors.

The root distance thus functions as a metric in the selection and weighting of the various available sources. The strategy is to select the system peer as the source with the minimum root distance and thus the minimum maximum error. The reference implementation uses the [Bellman-Ford algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm), where the goal is to minimize the root distance. The algorithm selects the _system peer_, from which the system root delay and system root dispersion are inherited.

The algorithms described on the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.8-series/prefer/) page deliver several important statistics. The _system offset_ and _system jitter_ are weighted averages computed by the clock combine algorithm. System offset is best interpreted as the maximum-likelihood estimate of the system clock offset, while system jitter, also called estimated error, is best interpreted as the expected error of this estimate. _System delay_ is the root delay inherited from the system peer, while _system dispersion_ is the root dispersion plus contributions due to jitter and the absolute value of the system offset.

The maximum system error, or _system distance_, is computed as one-half the system delay plus the system dispersion. In order to simplify discussion, certain minor contributions to the maximum error statistic are ignored. If the precision time kernel support is available, both the estimated error and maximum error are reported to user programs via the <code>ntp_adjtime()</code> kernel system call. See the [Kernel Model for Precision Timekeeping](/documentation/4.2.8-series/kern/) page for further information.
