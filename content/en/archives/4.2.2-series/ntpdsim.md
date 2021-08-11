---
title: "ntpdsim - Network Time Protocol (NTP) simulator"
type: archives
---
![gif](/archives/pic/oz2.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures)

All in a row.

Last update: 20:07 UTC Friday, June 16, 2006

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.2-series/ntpdsim/#synopsis)
*   [Description](/archives/4.2.2-series/ntpdsim/#description)
*   [Command Line Options](/archives/4.2.2-series/ntpdsim/#command-line-options)
*   [Files](/archives/4.2.2-series/ntpdsim/#files)

* * *

#### Synopsis

<tt>ntpdsim [ -B _bdly_ ] [ -C _snse_ ] [ -O _clk_time_ ] [ -S _sim_time_ ] [ -T _ferr_ ] [ -W _fsne_ ] [ -Y</tt> _<tt>ndly</tt>_ <tt>] [ -X</tt> _<tt>pdly</tt>_ <tt>]</tt>

* * *

#### Description

The <tt>ntpdsim</tt> program is an adaptation of the <tt>ntpd</tt> operating system daemon. The program operates as a discrete time simulator using specified systematic and random driving sources. It includes all the mitigation and discipline algorithms of the actual daemon, but with the packet I/O and system clock algorithms driven by simulation. Most functions of the real <tt>ntpd</tt> remain intact, including the monitoring, statistics recording, trace and host name resolution features. Further information on the simulator is on the [NTP Discrete Event Simulator](http://www.eecis.udel.edu/%7emills/ntpsim.html) page.

The simulator is most useful to study NTP behavior in response to time and/or frequency transients under specific conditions of network jitter and oscillator wander. For this purpose the daemon can be driven by pseudorandom jitter and wander sample sequences characteristic of real networks and oscillators. The jitter generator produces samples from a Poisson distribution, while the wander generator produces samples from a Guassian distribution.

The easiest way to use this program is to create a <tt>ntpstats</tt> directory, configuration file <tt>ntp.conf</tt> and frequency file <tt>ntp.drift</tt> and test shell <tt>test.sh</tt> in the base directory. The <tt>ntp.drift</tt> file and <tt>ntpstats</tt> directory can be empty to start. The <tt>test.sh</tt> script can contain something like

<pre>rm ./ntpstats/*
ntpdsim -O 0.1 -C .001 -T 400 -W 1 -c ./ntp.conf,
</pre>

which starts the simulator with a time offset 100 ms, network jitter 1 ms, frequency offset 400 PPM and oscillator wander 1 PPM/s. These parameters represent typical conditions with modern workstations on a Ethernet LAN. The ntp.conf file should contain something like

<pre>disable kernel
server pogo
driftfile ./ntp.drift
statsdir ./ntpstats/
filegen loopstats type day enable
filegen peerstats type day enable
</pre>

* * *

#### Command Line Options

{{% alert title="Note" color="warning" %}}
The NTP development team is moving to the use of a syntax-directed configuration file design. When complete these options will be replaced by a [new one](/archives/4.2.2-series/ntpdsim_new). Most of the <tt>ntpd</tt> command line options apply also to <tt>ntpdsim</tt>. In addition, the following command line options apply to <tt>ntpdsim.</tt></dt>
{{% /alert %}}

<dt><tt>-B _bdly_</tt></dt>

Specify beep delay (3600) s.

<dt><tt>-C _snse_</tt></dt>

Specify network jitter parameter (0) s.

<dt><tt>-O _clk_time_</tt></dt>

Specify initial time offset (0) s.

<dt><tt>-S _sim_time_</tt></dt>

Specify simulation duration (86400) s.

<dt><tt>-T _ferr_</tt></dt>

Specify initial frequency offset (0) PPM.

<dt><tt>-W _fnse_</tt></dt>

Specify oscillator wander parameter (0) PPM/s.

<dt><tt>-Y _ndly_</tt></dt>

Specify network propagation delay (.001) s.

<dt><tt>-Z _pdly_</tt></dt>

Specify server processing delay (.001) s.

* * *

#### Files

<tt>/etc/ntp.conf</tt> - the default name of the configuration file  
<tt>/etc/ntp.drift</tt> - the default name of the drift file  
<tt>/etc/ntp.keys</tt> - the default name of the key file