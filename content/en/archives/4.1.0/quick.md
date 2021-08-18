---
title: "Quick Start"
type: archives
---

![gif](/archives/pic/panda.gif)FAX test image for SATNET (1979).

The baby panda was scanned at University College London and used as a FAX test image for a demonstration of the DARPA Atlantic SATNET Program and the first transatlantic Internet connection in 1978. The computing system used for that demonstration was called the [Fuzzball](/reflib/papers/fuzz.pdf). As it happened, this was also the first Internet multimedia presentation and the first to use a predecessor of NTP in regular operation. The image was widely copied and used for testing purpose throughout much of the 1980s.

* * *

For the rank amateur the sheer volume of the documentation collection must be intimidating. However, it doesn't take much to fly the <tt>ntpd</tt> daemon with a simple configuration where a workstation needs to synchronize to some server elsewhere in the Internet. The first thing that needs to be done is to build the distribution for the particular workstation and install in the usual place. The [Building and Installing the Distribution](/archives/4.1.0/build) page describes how to do this.

While it is possible that certain configurations do not need a configuration file, most do require one. The file, called by default <tt>/etc/ntp.conf</tt>, need only contain one line specifying a remote server, for instance

<tt>server foo.bar.com</tt>

Choosing an appropriate remote server is somewhat of a black art, but a suboptimal choice is seldom a problem. Links to public time servers operated by National Institutes of Science and Technology (NIST), US Naval Observatory (USNO), Canadian Metrology Centre (CMC) and many others are given in the home page of this document collection. The lists are sorted by country and, in the case of the US, by state. Usually, the best choice is the nearest in geographical terms, but the terms of engagement specified in each list entry should be carefully respected.

During operation <tt>ntpd</tt> measures and corrects for incidental clock frequency error and writes the current value to a file called by default <tt>/etc/ntp.drift</tt>. If <tt>ntpd</tt> is stopped and restarted, it initializes the frequency from this file. In this way the potentially lengthy interval to relearn the frequency error is avoided. Thus, for most applications an additional line should be added to the file of the form

`driftfile /etc/ntp.drift`

That's all there is to it, unless some problem in network connectivity or local operating system configuration occurs. The most common problem is some firewall between the workstation and server. System administrators should understand NTP uses UDP port 123 as both the source and destination port and that NTP does not involve any operating system interaction other than to set the system clock. While almost all modern Unix systems have included NTP and UDP port 123 defined in the services file, this should be checked if <tt>ntpd</tt> fails to come up at all.

The best way to confirm NTP is working is using the [<tt>ntpq</tt>](/archives/4.1.0/ntpq) utility, although the [<tt>ntpdc</tt>](/archives/4.1.0/ntpdc) utility may be useful in extreme cases. See the documentation pages for further information. In the most extreme cases the <tt>-d</tt> option on the <tt>ntpd</tt> command line results in a blow-by-blow trace of the daemon operations. While the trace output can be cryptic, to say the least, it gives a general idea of what the program is doing and, in particular, details the arriving and departing packets and detected errors, if present.

Sometimes the <tt>ntpd</tt>. behavior may seem to violate the Principle of Least Astonishment, but there are good reasons for this. See the [Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd) page for revealing insights. See this page and its dependencies for additional configuration and control options. The [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.1.0/notes) page contains an extended discussion of these options.