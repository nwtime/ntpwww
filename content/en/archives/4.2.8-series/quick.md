---
title: "Quick Start"
type: archives
---

![gif](/archives/pic/panda.gif)FAX test image for SATNET (1979).

The baby panda was scanned at University College London and used as a FAX test image for a demonstration of the DARPA Atlantic SATNET Program and the first transatlantic Internet connection in 1978. The computing system used for that demonstration was called the [Fuzzball](/reflib/papers/fuzz.pdf). As it happened, this was also the first Internet multimedia presentation and the first to use a predecessor of NTP in regular operation. The image was widely copied and used for testing purpose throughout much of the 1980s.

Last update: 1-Dec-2012 04:44 UTC

* * *

For the rank amateur the sheer volume of the documentation collection must be intimidating. However, it doesn't take much to fly the <code>ntpd</code> daemon with a simple configuration where a workstation needs to synchronize to some server elsewhere in the Internet. The first thing is to build the distribution for the particular workstation and install in the usual place. The [Building and Installing the Distribution](/archives/4.2.8-series/build/) page describes how to do this.

While it is possible that certain configurations do not need a configuration file, most do. The file, called by default <code>/etc/ntp.conf</code>, need only contain one command specifying a remote server, for instance:

`server foo.bar.com`

Choosing an appropriate remote server is somewhat of a black art, but a suboptimal choice is seldom a problem. The simplest and best is to use the Server Pool Scheme on the [Automatic Server Discovery](/archives/4.2.8-series/discover/) page. There are about two dozen public time servers operated by the [National Institutes of Science and Technology (NIST)](https://tf.nist.gov/tf-cgi/servers.cgi), [US Naval Observatory (USNO)](https://www.usno.navy.mil/USNO/time/ntp/), [Canadian Metrology Centre (CMC)](https://nrc.canada.ca/en/certifications-evaluations-standards/canadas-official-time/network-time-protocol-ntp/) and many others available on the Internet. Lists of public primary and secondary NTP servers are maintained on the [Public NTP Time Servers](https://support.ntp.org/bin/view/Servers/WebHome) page, which is updated frequently. The lists are sorted by country and, in the case of the US, by state. Usually, the best choice is the nearest in geographical terms, but the terms of engagement specified in each list entry should be carefully respected.

During operation <code>ntpd</code> measures and corrects for incidental clock frequency error and occasionally writes the current value to a file specified by the `driftfile /etc/ntp.drift` configuration command. If <code>ntpd</code> is stopped and restarted, it initializes the frequency from this file and avoids the potentially lengthy interval to relearn the correction.

That's all there is to it, unless some problem in network connectivity or local operating system configuration occurs. The most common problem is some firewall between the workstation and server. System administrators should understand NTP uses UDP port 123 as both the source and destination port and that NTP does not involve any operating system interaction other than to set the system clock. While almost all modern Unix systems have included NTP and UDP port 123 defined in the services file, this should be checked if <code>ntpd</code> fails to come up at all.

The best way to confirm NTP is working is using the [<code>ntpq</code>](/archives/4.2.8-series/ntpq/) utility, although the [<code>ntpdc</code>](/archives/4.2.8-series/ntpdc/) utility may be useful in extreme cases. See the documentation pages for further information. Don't forget to check for [system log messages](/archives/4.2.8-series/msyslog/). In the most extreme cases the <code>-d</code> option on the <code>ntpd</code> command line results in a blow-by-blow trace of the daemon operations. While the trace output can be cryptic, to say the least, it gives a general idea of what the program is doing and, in particular, details the arriving and departing packets and any errors found.
