---
title: "ntpdsim - Network Time Protocol (NTP) simulator"
description: "The ntpdsim program is a discrete time simulator of the ntpd  daemon. The simulator includes all the mitigation and discipline algorithms of the actual daemon, as well as the monitoring, statistics recording, trace, and host name resolution features."
type: archives
aliases:
    - /current-stable/ntpdsim/
---
![gif](/documentation/pic/oz2.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

All in a row.

* * *

#### Table of Contents

*   [Synopsis](/documentation/4.2.8-series/ntpdsim/#synopsis)
*   [Description](/documentation/4.2.8-series/ntpdsim/#description)
*   [Command Line Options](/documentation/4.2.8-series/ntpdsim/#command-line-options)
*   [Files](/documentation/4.2.8-series/ntpdsim/#files)

* * *

#### Synopsis

<code>ntpdsim [ -B _bdly_ ] [ -C _snse_ ] [ -O _clk_time_ ] [ -S _sim_time_ ] [ -T _ferr_ ] [ -W _fsne_ ] [ -Y _ndly_ ] [ -X _pdly_ ]</code>

* * *

#### Description

The `ntpdsim` program is an adaptation of the `ntpd` operating system daemon. The program operates as a discrete time simulator using specified systematic and random driving sources. It includes all the mitigation and discipline algorithms of the actual daemon, but with the packet I/O and system clock algorithms driven by simulation. Most functions of the real `ntpd` remain intact, including the monitoring, statistics recording, trace and host name resolution features. Further information on the simulator is on the [NTP Discrete Event Simulator](/reflib/ntpsim/) page.

The simulator is most useful to study NTP behavior in response to time and/or frequency transients under specific conditions of network jitter and oscillator wander. For this purpose the daemon can be driven by pseudorandom jitter and wander sample sequences characteristic of real networks and oscillators. The jitter generator produces samples from a Poisson distribution, while the wander generator produces samples from a Guassian distribution.

The easiest way to use this program is to create a `ntpstats` directory, configuration file `ntp.conf` and frequency file `ntp.drift` and test shell `test.sh` in the base directory. The `ntp.drift` file and `ntpstats` directory can be empty to start. The `test.sh` script can contain something like

<pre>rm ./ntpstats/*
ntpdsim -O 0.1 -C .001 -T 400 -W 1 -c ./ntp.conf,
</pre>

which starts the simulator with a time offset 100 ms, network jitter 1 ms, frequency offset 400 PPM and oscillator wander 1 PPM/s. These parameters represent typical conditions with modern workstations on a Ethernet LAN. The `ntp.conf` file should contain something like:

<pre>disable kernel
server pogo
driftfile ./ntp.drift
statsdir ./ntpstats/
filegen loopstats type day enable
filegen peerstats type day enable
</pre>

* * *

#### Command Line Options

> **NOTE:** The NTP development team is moving to the use of a syntax-directed configuration file design. When complete these options will be replaced by a [new one](/documentation/4.2.8-series/ntpdsim_new/). Most of the `ntpd` command line options apply also to `ntpdsim`. In addition, the following command line options apply to `ntpdsim`.

<code>**-B _bdly_**</code>
: Specify beep delay (3600) s.

<code>**-C _snse_**</code>
: Specify network jitter parameter (0) s.

<code>**-O _clk_time_**</code>
: Specify initial time offset (0) s.

<code>**-S _sim_time_**</code>
: Specify simulation duration (86400) s.

<code>**-T _ferr_**</code>
: Specify initial frequency offset (0) PPM.

<code>**-W _fnse_**</code>
: Specify oscillator wander parameter (0) PPM/s.

<code>**-Y _ndly_**</code>
: Specify network propagation delay (.001) s.

<code>**-Z _pdly_**</code>
: Specify server processing delay (.001) s.

* * *

#### Files

`/etc/ntp.conf` - the default name of the configuration file

`/etc/ntp.drift` - the default name of the drift file

`/etc/ntp.keys` - the default name of the key file