---
title: "Rules of Engagement"
type: archives
---

As the load on the hosts supporting NTP primary (stratum 1) time service is heavy and always increasing, clients should avoid using the primary servers whenever possible. In most cases the accuracy of the NTP secondary (stratum 2) servers is only slightly degraded relative to the primary servers and, as a group, the secondary servers may be just as reliable. As a general rule, a secondary server should use a primary server only under the following conditions:

1. The secondary server provides synchronization to a sizable population of other servers and clients on the order of 100 or more.

2. The server operates with at least two and preferably three other secondary servers in a common synchronization subnet designed to provide reliable service, even if some servers or the lines connecting them fail.

3. The administration operating these servers coordinates other servers within the region, in order to reduce the resources required outside that region. Note that at least some interregional resources are required in order to ensure reliable service. 

In order to ensure reliability, clients should operate with several different servers and avoid common points of failure. As a general rule, between three and five servers are sufficient, but they should be selected from different networks. No more than two clients per network should use the same server on another network; however, in order to simplify management of host configuration tables, many hosts on the same network may use the same redundant servers on the same network.

There are many scenarios where the above rules may not apply, especially large campus or corporate networks, clients with intermittent connectivity, and security considerations, which are beyond the scope of this page.

Unix users are strongly encouraged to upgrade to the [latest NTP Version 4 software](/downloads/). Besides providing more accurate, reliable service, the latest version automatically increases the polling intervals for all peer associations without sacrificing performance. This can significantly reduce network loads, as well as the loads on the busy primary servers, some of which have over 700 clients.