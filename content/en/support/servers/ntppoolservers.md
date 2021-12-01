---
title: "NTP Pool Time Servers"
type: archives
---

[pool.ntp.org](https://www.pool.ntp.org/) uses DNS round robin to make a random selection from a pool of time servers who have [volunteered](https://www.pool.ntp.org/join.html) to be in the pool. This is usually good enough for end-users. The minimal `ntpd` configuration file (e.g. `/etc/ntpd.conf`) for using [pool.ntp.org](https://www.pool.ntp.org/) is:

<pre>
driftfile /var/lib/ntp/ntp.drift
server 0.pool.ntp.org
server 1.pool.ntp.org
server 2.pool.ntp.org
server 3.pool.ntp.org
</pre>

> ALERT! Any questions about the pool.ntp.org server pool should be directed either to the [pool mailing list](https://www.pool.ntp.org/mailinglists.html) or to the [comp.protocols.time.ntp Google group](https://groups.google.com/g/comp.protocols.time.ntp).

Time server operators are encouraged to visit the [NTP Pool website](https://www.pool.ntp.org/join.html) to find out how they can join the NTP pool.

The NTP Pool DNS system automatically picks time servers which are geographically close for you, but if you want to choose explicitly, there are sub-zones of pool.ntp.org. The "continent" ones are: 

| Area | HostName |
| ----- | ----- |
| Worldwide | [pool.ntp.org](https://www.pool.ntp.org/zone/@) |
| Asia | [asia.pool.ntp.org](https://www.pool.ntp.org/zone/asia) |
| Europe | [europe.pool.ntp.org](https://www.pool.ntp.org/zone/europe) |
| North America | [north-america.pool.ntp.org](https://www.pool.ntp.org/zone/north-america) |
| Oceania | [oceania.pool.ntp.org](https://www.pool.ntp.org/zone/oceania) |
| South America | [south-america.pool.ntp.org](https://www.pool.ntp.org/zone/south-america) |

 There are also sub-zones for many countries. Click on your continent to see which country-zones are available there.

When using the by-country zones, be careful: some of them currently contain only one or two servers, so you are probably better off using either the zone of a nearby country, or using the continent or global zone (This is sometimes also valid if you live in a big country). In general though, just use the "global" zone as in the suggested configuration near the top of the page and let the system sort it out for you. 