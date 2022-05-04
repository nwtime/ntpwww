---
title: "Event Messages and Status Words"
type: archives
---

![gif](/documentation/pic/alice47.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Caterpillar knows all the error codes, which is more than most of us do.

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.8-series/decode/#introduction)
*   [System Status Word](/documentation/4.2.8-series/decode/#system-status-word)
*   [Peer Status Word](/documentation/4.2.8-series/decode/#peer-status-word)
*   [Clock Status Word](/documentation/4.2.8-series/decode/#clock-status-word)
*   [Flash Status Word](/documentation/4.2.8-series/decode/#flash-status-word)
*   [Kiss Codes](/documentation/4.2.8-series/decode/#kiss-codes)
*   [Crypto Messages](/documentation/4.2.8-series/decode/#crypto-messages)

* * *

#### Introduction

This page lists the status words, event messages and error codes used for <code>ntpd</code> reporting and monitoring. Status words are used to display the current status of the running program. There is one system status word and a peer status word for each association. There is a clock status word for each association that supports a reference clock. There is a flash code for each association which shows errors found in the last packet received (pkt) and during protocol processing (peer). These are commonly viewed using the [<code>ntpq</code>](/documentation/4.2.8-series/ntpq/) program.

Significant changes in program state are reported as events. There is one set of system events and a set of peer events for each association. In addition, there is a set of clock events for each association that supports a reference clock. Events are normally reported to the <code>protostats</code> monitoring file and optionally to the system log. In addition, if the trap facility is configured, events can be reported to a remote program that can page an administrator.

This page also includes a description of the error messages produced by the Autokey protocol. These messages are normally sent to the <code>cryptostats</code> monitoring file.

In the following tables the Code is the status or event code assigned and the Message is a short string used for display and event reporting. The Description contains a longer explanation of the status or event. Some messages include additional information useful for error diagnosis and performance assessment.

* * *

#### System Status Word

The system status word consists of four fields LI (0-1), Source (2-7), Count (8-11) and Event (12-15). It is reported in the first line of the <code>rv</code> display produced by the <code>ntpq</code> program.

The **Leap Field** displays the system leap indicator bits coded as follows:

| Code | Message | Description |
| ---- | ------ | ----- |
| 0 | leap_none | normal synchronized state |
| 1 | leap_add_sec | insert second after 23:59:59 of the current day |
| 2 | leap_del_sec | delete second 23:59:59 of the current day |
| 3 | leap_alarm | never synchronized |

The **Source Field** displays the current synchronization source coded as follows:

| Code | Message | Description |
| ---- | ------ | ----- |
| 0 | sync_unspec | not yet synchronized |
| 1 | sync_pps | pulse-per-second signal (Cs, Ru, GPS, etc.) |
| 2 | sync_lf_radio | VLF/LF radio (WWVB, DCF77, etc.) |
| 3 | sync_hf_radio | MF/HF radio (WWV, etc.) |
| 4 | sync_uhf_radio | VHF/UHF radio/satellite (GPS, Galileo, etc.) |
| 5 | sync_local | local timecode (IRIG, LOCAL driver, etc.) |
| 6 | sync_ntp | NTP |
| 7 | sync_other | other (IEEE 1588, openntp, crony, etc.) |
| 8 | sync_wristwatch | eyeball and wristwatch |
| 9 | sync_telephone | telephone modem (ACTS, PTB, etc.) |

The **Count Field** displays the number of events since the last time the code changed. Upon reaching 15, subsequent events with the same code are ignored.

The **Event Field** displays the most recent event message coded as follows:

| Code | Message | Description |
| ---- | ------ | ----- |
| 00 | unspecified | unspecified |
| 01 | freq_not_set | frequency file not available |
| 02 | freq_set | frequency set from frequency file |
| 03 | spike_detect | spike detected |
| 04 | freq_mode | initial frequency training mode |
| 05 | clock_sync | clock synchronized |
| 06 | restart | program restart |
| 07 | panic_stop | clock error more than 600 s |
| 08 | no_system_peer | no system peer |
| 09 | leap_armed | leap second armed from file or Autokey |
| 0a | leap_disarmed | leap second disarmed |
| 0b | leap_event | leap event |
| 0c | clock_step | clock stepped |
| 0d | kern | kernel information message |
| 0e | TAI... | leapsecond values update from file |
| 0f | stale leapsecond values | new NIST leapseconds file needed |

* * *

#### Peer Status Word

The peer status word consists of four fields: Status (0-4), Select (5-7), Count (8-11) and Code (12-15). It is reported in the first line of the <code>rv _associd_</code> display produced by the <code>ntpq</code> program.

The **Status Field** displays the peer status code bits in hexadecimal; each bit is an independent flag. **Note this field is 5 bits wide, and combines with the 3-bit-wide Select Field to create the first full byte of the peer status word.** The meaning of each bit in the Status Field is listed in the following table:

| Code | Message | Description |
| ---- | ------ | ----- |
| 08 | bcst | broadcast association |
| 10 | reach | host reachable |
| 20 | auth | authentication ok |
| 40 | authenb | authentication enabled |
| 80 | config | persistent association |

The **Select Field** displays the current selection status. The T Field gives the corresponding tally codes used in the <code>ntpq peers</code> display. The values are coded as follows:

| Code | Message | T | Description |
| ---- | ------ | ----- | ----- |
| 0 | sel_reject | | discarded as not valid (TEST10-TEST13) |
| 1 | sel_falsetick | x | discarded by intersection algorithm |
| 2 | sel_excess | . | discarded by table overflow (not used) |
| 3 | sel_outlier | - | discarded by the cluster algorithm |
| 4 | sel_candidate | + | included by the combine algorithm |
| 5 | sel_backup | # | backup (more than <code>tos maxclock</code> sources) |
| 6 | sel_sys.peer | * | system peer |
| 7 | sel_pps.peer | o | PPS peer (when the prefer peer is valid) |

The **Count Field** displays the number of events since the last time the code changed. Upon reaching 15, subsequent events with the same code are ignored.

The **Event Field** displays the most recent event message coded as follows:

| Code | Message | Description |
| ---- | ------ | ----- |
| 01 | mobilize | association mobilized |
| 02 | demobilize | association demobilized |
| 03 | unreachable | server unreachable |
| 04 | reachable | server reachable |
| 05 | restart | association restart |
| 06 | no_reply | no server found (<code>ntpdate</code> mode) |
| 07 | rate_exceeded | rate exceeded (kiss code <code>RATE</code>) |
| 08 | access_denied | access denied (kiss code <code>DENY</code>) |
| 09 | leap_armed | leap armed from server LI code |
| 0a | sys_peer | become system peer |
| 0b | clock_event | see clock status word |
| 0c | bad_auth | authentication failure |
| 0d | popcorn | popcorn spike suppressor |
| 0e | interleave_mode | entering interleave mode |
| 0f | interleave_error | interleave error (recovered) |

* * *

#### Clock Status Word

The clock status word consists of four fields: Unused (0-7), Count (8-11) and Code (12-15). It is reported in the first line of the <code>clockvar _associd_</code> display produced by the <code>ntpq</code> program.

The Count Field displays the number of events since the last <code>lockvar</code> command, while the **Event Field** displays the most recent event message coded as follows:

| Code | Message | Description |
| ---- | ------ | ----- |
| 00 | clk_unspe | nominal |
| 01 | clk_noreply | no reply to poll |
| 02 | clk_badformat | bad timecode format |
| 03 | clk_fault | hardware or software fault |
| 04 | clk_bad_signal | signal loss |
| 05 | clk_bad_date | bad date format |
| 06 | clk_bad_time | bad time format |

When the clock driver sets the code to a new value, a <code>clock_alarm</code> (11) peer event is reported.

* * *

#### Flash Status Word

The flash status word is displayed by the <code>ntpq</code> program <code>rv</code> command. It consists of a number of bits coded in hexadecimal as follows:

| Code | Tag | Message | Description |
| ---- | ------ | ----- | ----- |
| 0001 | TEST1 | pkt_dup | duplicate packet |
| 0002 | TEST2 | pkt_bogus | bogus packet |
| 0004 | TEST3 | pkt_unsync | server not synchronized |
| 0008 | TEST4 | pkt_denied | access denied |
| 0010 | TEST5 | pkt_auth | authentication failure |
| 0020 | TEST6 | pkt_stratum | invalid leap or stratum |
| 0040 | TEST7 | pkt_header | header distance exceeded |
| 0080 | TEST8 | pkt_autokey | Autokey sequence error |
| 0100 | TEST9 | pkt_crypto | Autokey protocol error |
| 0200 | TEST10 | peer_stratum | invalid header or stratum |
| 0400 | TEST11 | peer_dist | distance threshold exceeded |
| 0800 | TEST12 | peer_loop | synchronization loop |
| 1000 | TEST13 | peer_unreach | unreachable or nonselect |

* * *

#### Kiss Codes

Kiss codes are used in kiss-o'-death (KoD) packets, billboard displays and log messages. They consist of a string of four zero-padded ASCII charactes. In practice they are informal and tend to change with time and implementation. Some of these codes can appear in the reference identifier field in <code>ntpq</code> billboards. Following is the current list:

| Code | Description |
| ---- | ----- |
| ACST | manycast server |
| AUTH  | authentication error |
| AUTO  | Autokey sequence error |
| BCST  | broadcast server |
| CRYPT  | Autokey protocol error |
| DENY  | access denied by server |
| INIT  | association initialized |
| MCST  | multicast server |
| RATE  | rate exceeded |
| TIME  | association timeout |
| STEP  | step time change |

* * *

#### Crypto Messages

These messages are sent to the <code>cryptostats</code> file when an error is detected in the Autokey protocol.

| Code | Message | Description |
| ---- | ------ | ----- |
| 01 | bad_format | bad extension field format or length |
| 02 | bad_timestamp | bad timestamp |
| 03 | bad_filestamp | bad filestamp |
| 04 | bad_public_key | bad or missing public key |
| 05 | bad_digest | unsupported digest type |
| 06 | bad_identity | unsupported identity type |
| 07 | bad_siglength | bad signature length |
| 08 | bad signature | extension field signature not verified |
| 09 | cert_not_verified | certificate signature not verified |
| 0a | cert_expired | host certificate expired |
| 0b | bad_cookie | bad or missing cookie |
| 0c | bad_leapseconds | bad or missing leapseconds values |
| 0d | cert_missing | bad or missing certificate |
| 0e | bad_group_key | bad or missing group key |
| 0f | proto_error | protocol error |