---
title: "Historical Notes"
type: archives
---

Last update: 10-Mar-2014 05:07 UTC

* * *

#### Historical Notes on NTP Upgrades

This is an interim report on recent upgrades to the NTPv4 reference implementation code base and documentation. This report documents the upgrade program, which began in June 2007 and continued until March 2008. It is very important to recognize that this historic document describes the upgrade status as of 2008. Additional upgrades have been implemented since then. As of mid 2011, the additional upgrades are documented on the [NTP Version 4 Release Notes](/archives/4.2.8-series/release) page.

The motivation for this project was the overhaul and refinement of the code, some of which dates back twenty years. Some four dozen sets of fingers have introduced sometimes incompatible "improvements" that to some degree enhance or burden the product. There has been a continuing effort over the years to maintain the briar patch and pluck the more flagrant weeds, but it now requires a more systematic and thorough examination of purpose, design and implementation. The project is not complete, but far enough along to present a status report and review of significant changes.

Please note THE CHANGES DO NOT AFFECT THE PROTOCOL SPECIFICATION AND DO NOT AFFECT INTEROPERABILITY WITH PREVIOUS VERSIONS.

* * *

#### 1. Transparent Design

During the project a number of minor inconsistencies in various algorithms were found and resolved. In most cases this did not result in any changes in behavior, just a more simplified, transparent and easier to maintain design. In a few cases behavior has been modified to correct deficiencies and to avoid hostile attacks, as described below.

* * *

#### 2. Documentation

The documentation required a major upgrade. Many pages have been overhauled, some completely rewritten and new ones added. A site map has been added and sorted by page category. A comprehensive command index has been added and sorted by page category. The command index includes a brief gloss for each command. A page has been added to show the various status word and event decodes used for monitoring and event reporting. The decodes show the internal code, ASCII report and short function gloss.

New pages have been added on association management, automatic server discovery and rate management. Much of the overburden on the program manual and configuration pages has been moved to these pages with the intent of the original pages to contain primarily a functional description for the commands and command line options. This is still an ongoing process.

* * *

#### 3. Bulletproofing

In a continuing mission the code flow has been carefully adjusted to decrease vulnerability to configuration errors and possibly hostile attack. The order of restriction processing was adjusted to deflect access denials as early as possible and without consuming useless processor cycles. This is especially important in rate defense, as the MRU list should only be used for clients that could be legitimately served. In addition, the Autokey protocol was adjusted to avoid some potentially nasty disruption attacks.

* * *

#### 4. Rate Management

Strict rate controls have been refined in both outbound and inbound traffic for both minimum headway (guard time) and minimum average headway. This is a major improvement over the original limitreject design of 1992 and upgrade circa 2003. Headway violations result in an optional _kiss-o'-death_ (KoD) packet. To avoid a clogging vulnerability, the KoD packets are themselves rate controlled for each source address separately.

The main feature of the revised design is that it is responsive to the server minimum headway and avoids guessing. This is done by setting the ppoll field in the server packet to the maximum of (a) the ppoll field in the client packet and (b) the server headway. The client sets the ppoll field in the association to the maximum of (a) the ppoll field in the server packet and (b) the minpoll field in the association. If this is a KoD and this value is greater than minpoll, minpoll is set to this value. The result is that the client continues sending, but only at headway at least as large as the server.

The revised design makes possible a decrease in the minimum time constant/poll interval to 3 (8 s), which reduces the risetime to 250 s. This may be useful for rapid convergence when a client is first started, but should not be used for links with moderate to large jitter. This is done using the average option of the discard command, which sets the minimum poll interval and headway from the default 4 (16 s) to a value in the range 3 (8 s) to 6 (64 s). Larger values than 4 might be appropriate for very busy public servers.

Rate management applies also to Autokey messages. This fixes a problem when iburst and autokey are both in play and when for some reason an association with iburst is repeatedly restarted. This may appear spooky to some folks that frequently restart a client for testing. The server remembers. Further information is in the current web documentation.

* * *

#### 5. Frequency File

Initial frequency training has always been a problem, as it can take a very long time to trim the frequency estimate to nominal values. Once this happens and the frequency file is written, subsequent reboots will restore the frequency and frequency training is avoided. The problem is exacerbated using toll modem services such as ACTS which make a call at each poll interval. Until the training is complete the poll interval is held below the desired maximum as toll charges accrue.

The problem was solved by changing the clock state machine so that, if no frequency file is available, an initial training interval of 300 s occurs, after which the frequency is directly calculated and the discipline then turned over to the feedback loop. The choice of 300 s is based on the assumption that time can be estimated within 1 ms and the resulting frequency estimate within nominal 1 PPM.

Note that once the initial time offset is either stepped or slewed, no further time offsets are amortized during the training period. If the frequency error is large, the time offset at the end of the period can be moderately large, which then must be amortized by the feedback loop. While this may take up to an hour and result in a minor frequency tweak, the behavior is very much better than without the initial training. The remedy would require intricate and fragile code revisions.

In the original design the frequency file was written at one-hour intervals. This apparently makes embedded systems folks nervous, since this can tire the flash NVRAM after several years. The interval between writes now depends on the ambient clock stability and normally maxes out at something over one day unless the frequency takes an unusual twitch.

* * *

#### 6. Leapseconds

The leapsecond processing has been overhauled once again. The problem is to avoid fake leap warnings displayed by an errant server and to insure correct response in case of large time changes which might validate or invalidate arming for a subsequent leap. No leap information is used unless the client is synchronized to a proventic source. The values obtained from an Autokey server or peer are updated if newer than the current values. Server leap warning bits are disregarded if these values are available. If not, and if either a majority of the servers show leap warning bits or if one or more of the survivors are a reference clock with leap warning bit, the leap is armed. If armed by server leap warning bits and these provisions no longer prevail, the leap is disarmed. The NTPv4 protocol specifically does not speak to this issue.

The leap armed condition is displayed in the host status word. Transitions between warnings and no warnings are reported to the protostats file, system log and traps.

* * *

#### 7. Orphan Mode and Local Clock Driver

The orphan mode code has been overhauled to correct some minor bugs and to clarify operation under normal and recovery conditions. The requirement that all subnet hosts have orphan configuration has been removed. The only requirement is that the orphan clients on the DMZ network sharing the root server(s) be so configured The scheme now works if the root servers are configured with each other, either in symmetric or broadcast modes. Orphan mode is not considered in the NTPv4 protocol specification.

The local clock driver can be very dangerous when used as a fallback when connectivity to Internet time servers is interrupted. Orphan mode was designed to reduce the need for the local clock driver, as it is active only if no server is available. The local clock driver has been modified to have the same characteristics, regardless of stratum. Only if the host running the local clock driver loses all servers, regardless of stratum, is the driver activated. Thus, it is possible, but not recommended, to run the driver at any stratum, including zero.

* * *

#### 8. Poll Rate Control

One of the most persistent problems is when after long operation and then a failure and then subsequently recovery, a client can take a long time to refresh the clock filter and resynchronize. Once the client has backed off the poll interval after a lengthy outage, it sends polls at that interval until receiving a response. At that time it temporarily retries at the minimum poll interval to fill up the clock filter. If iburst is configured, this will happen after 10 seconds or so and the client then resumes its poll interval required by the discipline time constant. This avoids needless network traffic while the poll interval increases gradually to the maximum. Further information is in the current web documentation.

The same thing happens on initial startup or when an association is restarted. The intent is to avoid a blast of <tt>iburst</tt> packets unless the server actually responds to the first one and to retry only while responding to the rate controls.

In order to speed response to initial startup when a reference clock is available, the clock is set on the first message received from the driver. This exposed an interesting bug, now fixed, with the ACTS modem driver, which began prematurely to ramp up the poll interval.

* * *

#### 9. Autokey

The management of host and group names with respect to Autokey configuration and key generation has been removed and simplified. On host certificates, the subject and issuer fields carry the group name, while other certificates carry the host name, which can be an arbitrary string having nothing to do with the DNS name. This opens up a possible future plan to use the Autokey name rather than the IP address when constructing the session key. It also allows a client to easily switch from one group to another without regenerating the certificate. Further information is in the current web documentation and in the latest Autokey ID.

Various protocol refinements have been done in the Autokey state machine. A bug was found in symmetric modes where the peer cookies were not EXORed. A bug was found in processing the certificate cache when a participant was a client of two or more server in the same group which themselves had certificate trails to different trusted hosts.

The protocol machine is now restarted every several days in order to update certificates and leapseconds values when they are changed.

* * *

#### 10. Report, Log and Event Codes

The status, selection, source, event and log decodes have been adjusted for consistency. Some of the decodes were missing, some with errors and a few new ones added. Old versions of ntpq continue to work without change, but display a new code as space. Except for the new codes, this behavior is consistent with RFC 1305 and proposed for the NTPv4 protocol specification.

The ntpq as command has been changed to fix some very old bugs. The display is now consistent with the system and peer billboards. The authentication state is correctly displayed for broadcast server associations.

The event reporting has been cleaned up for more straightforward interpretation by a remote agent. All significant state transitions are reported, including clock state machine changes, mobilization, /demobilization, system and peer restart, system peer change, panic stop and so forth.

A new protostats monitoring file facility has been added. It works just like the other monitor files. All events are recorded to this file as reported and optionally to the system log. Many reports that sometimes clog up the system log are more usefully directed to this file. The reports also trigger a trap packet that can be sent via an agent to page an administrator.

When the current mode-6 monitoring protocol was designed circa 1988 the considered intent was that monitoring functions rely only on the NTP packet itself and the system, peer and clock status words provided in the mode-6 packet. While the strongly felt advice at that time was to avoid reformatting the plain ASCII text sent by the server, at various times folks have cheated and reformatted the text. In some places this is good, like displaying the filter shift register; in some places this is bad, like reformatting the timestamps. There is nothing much that can be done about this now without angry mobs rioting when forced to upgrade to a new ntpq. I will not rule this out in future.

A more serious comment has to do with using other than the NTP packet, status words and events for monitoring purposes. Emphasis added: monitors should not parse such things as the flash codes, clock state or anything else not called out in the NTPv4 specification. The clock state machine is defined in the specification, but no specific numbers are assigned to the states.

When the numbers were changed to align for reporting purposes, some scripts no longer worked. The scripts should be changed to use only the leap and select fields of the system status word. If the leap field is other than 0, the client has synchronized at least once; if the select field is other than 0, the client is currently synchronized to the source indicated in the decode.

* * *

#### 11. Two-step and timestamp capture

A number of interesting ideas were found in the IEEE 1588 Precision Time Protocol specification. One of them was the two-step protocol in which the transmit timestamp is sent in a following message. However, the PTP design operates only in a master-slave configuration and is not directly usable in NTP. The protocol was adapted to the NTP symmetric design, which requires four state variables rather than two. It is described on [Timestamp Capture Principles](/reflib/stamp). This might be an interesting project for future research.

A detailed study of the timestamp capture opportunities for both hardware and software timestamping revealed that the most accurate and interoperable design involves the transmit timestamp at the beginning of the packet and then receive timestamp at the end. This makes it possible to accurately measure the offset and delay even if the ends of the synchronization path operate at different rates. It is described on the Timestamp Capture Principles page.

* * *

#### 12. Windows client bug

The Windows XP and Vista clients send the NTP request in symmetric active mode rather than client mode. An unsuspecting server could mobilize a symmetric passive association, which is a serious security vulnerability. The NTPv4 servers, including those at NIST and USNO, discard symmetric active requests unless cryptographically authenticated, so Windows clients do not work. The Microsoft KB 875424 discusses the preferred workaround; however, an optional workaround is now available so that, if the request is not authenticated, the server responds with symmetric passive mode, but without mobilize an association. The workaround is enabled with the WINTIME build option.

The spec assumes that either peer in symmetric modes can synchronize the other should a peer lose all sources. The workaround violates that assumption and some legitimate configuration might be badly misused. It should be used only with this understanding.

* * *

#### 13. Autonomous configuration

The autonomous configuration (pool and manycast) code was refined to more reliably prune excess servers. If a truechimer is discarded by the clustering algorithm and the total number of survivors is greater than the maxclock option of the tos command, it is considered excess and shows a "#" tally code. If the association is ephemeral and survives the clustering algorithm, the watchdog counter is reset. If the watchdog timer expires and the total number of associations is greater than the maxclock option of the tos command, it is demobilized. This behavior is not considered in the NTPv4 protocol specification.

* * *

#### 14. Code ornamentation

When auditing the code and figuring out its historic origin and evolution, additional commentary has been added so future generations can figure it out, too.

David L. Mills  
17 March 2008 
