---
title: "Orphan Mode"
description: "Orphan mode provides a single simulated UTC source with multiple servers and provides seamless switching as local reference clocks or Internet time servers fail and recover."
type: archives
aliases:
    - /current-stable/orphan/
---

Sometimes an NTP subnet becomes isolated from all UTC sources such as local reference clocks or Internet time servers. In such cases it may be necessary that the subnet servers and clients remain synchronized to a common timescale, not necessarily the UTC timescale. Previously, this function was provided by the local clock driver to simulate a UTC source. A server with this driver could be used to synchronize other hosts in the subnet directly or indirectly.

There are many disadvantages using the local clock driver, primarily that the subnet is vulnerable to single-point failures and multiple-server redundancy is not possible. Orphan mode is intended to replace the local clock driver. It provides a single simulated UTC source with multiple servers and provides seamless switching as servers fail and recover.

A common configuration for private networks includes one or more core servers operating at the lowest stratum. Good practice is to configure each of these servers as backup for the others using symmetric or broadcast modes. As long as at least one core server can reach a UTC source, the entire subnet can synchronize to it.

If no UTC sources are available to any core server, one of them can provide a simulated UTC source for all other hosts in the subnet. However, only one core server can simulate the UTC source and all direct dependents, called orphan children, must select the same server, called the orphan parent.

Hosts sharing the same common subnet, including potential orphan parents and potential orphan children, can be enabled for orphan mode using the <code>orphan _stratum_</code> option of the [<code>tos command</code>](/documentation/4.2.8-series/miscopt/), where <code>_stratum_</code> is some stratum less than 16 and greater than any anticipated stratum that might occur with configured Internet time servers. However, sufficient headroom should remain so every subnet host dependent on the orphan children has stratum less than 16. Where no associations for other servers or reference clocks are configured, the orphan stratum can be set to 1. These are the same considerations that guide the local clock driver stratum selection.

In order to avoid premature enabling of orphan mode, a holdoff delay occurs when the daemon is first started and when all sources have been lost after that. The delay is intended to allow time for other sources to become reachable and selectable. Only when the delay has expired with no sources will orphan mode be enabled. By default the delay is 300 s (five minutes), but this can be changed using the <code>orphanwait</code> option of the [<code>tos</code>](/documentation/4.2.8-series/miscopt/) command.

A orphan parent with no sources shows reference ID <font face="Courier New, Courier, Monaco, monospace">LOOP</font> if operating at stratum 1 and `127.0.0.1` (IPv4 loopback address) otherwise. While ordinary NTP clients use a selection metric based on delay and dispersion, orphan children use a metric computed from the IP address of each core server. Each orphan child chooses the orphan parent as the core server with the smallest metric.

For orphan mode to work well, each core server with available sources should operate at the same stratum. All core servers and orphan children should include the same `tos` command in the configuration file. Each orphan child should include in the configuration file all root servers.

![gif](/documentation/pic/peer.gif)

**Figure 1: Orphan Peer Configuration**

For example, consider the peer network configuration in Figure 1, where two or more campus primary or secondary (stratum 2) servers are configured with reference clocks or public Internet primary servers and with each other using symmetric modes. With this configuration a server that loses all sources continues to discipline the system clock using the other servers as backup. Only the core servers and orphan children need to be enabled for orphan mode.

![gif](/documentation/pic/broad.gif)

**Figure 2: Orphan Broadcast Configuration**

For broadcast networks each core server is configured in both broadcast server and broadcast client modes as shown in Figure 2. Orphan children operate as broadcast clients of all core servers. As in peer networks, the core servers back up each other and only they and the orphan children need to be enabled for orphan mode.

In normal operation subnet hosts operate below stratum 5, so the subnet is automatically configured as described in the NTP specification. If all UTC sources are lost, all core servers become orphans and the orphan children will select the same core server to become the orphan parent.