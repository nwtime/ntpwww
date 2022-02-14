---
title: "NTP Pool Time Servers"
type: archives
---

The [NTP Pool Project](https://www.ntppool.org/) uses DNS round robin to make a random selection from a pool of time servers who have [volunteered](https://www.ntppool.org/en/join.html) to be in the pool. This is usually good enough for end-users. The minimal `ntpd` configuration file (e.g. `/etc/ntpd.conf`) for using [NTP Pool Project](https://www.ntppool.org/) is:

<pre>
driftfile /var/lib/ntp/ntp.drift
server 0.pool.ntp.org
server 1.pool.ntp.org
server 2.pool.ntp.org
server 3.pool.ntp.org
</pre>

> Questions about the NTP Pool Project server pool should be directed to the [NTP Pool Project mailing lists](https://www.ntppool.org/en/mailinglists.html).

Time server operators are encouraged to [join the NTP Pool Project](https://www.ntppool.org/en/join.html).

The NTP Pool Project's DNS system automatically selects geographically close time servers, but if you want to choose explicitly, sub-zones are available. The "continent" ones are: 

| Area | HostName |
| ----- | ----- |
| Worldwide | [pool.ntp.org](https://www.ntppool.org/zone/@/) |
| Asia | [asia.pool.ntp.org](https://www.ntppool.org/zone/asia/) |
| Europe | [europe.pool.ntp.org](https://www.ntppool.org/zone/europe/) |
| North America | [north-america.pool.ntp.org](https://www.ntppool.org/zone/north-america/) |
| Oceania | [oceania.pool.ntp.org](https://www.ntppool.org/zone/oceania/) |
| South America | [south-america.pool.ntp.org](https://www.ntppool.org/zone/south-america/) |

 There are also sub-zones for many countries. Click a continent to see its country zones.

When using the by-country zones, be careful: some of them currently contain only one or two servers, so you are probably better off using either the zone of a nearby country, or using the continent or global zone (This is sometimes also valid if you live in a big country). In general, just use the "global" zone in the above suggested configuration and let the system sort it out for you.