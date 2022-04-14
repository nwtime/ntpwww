---
title: "Monitoring Options"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/pogo8.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

Pig was hired to watch the logs.

Last update: 10-May-2009 16:19 UTC

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.6-series/monopt/#introduction)
*   [Monitoring Commands](/documentation/4.2.6-series/monopt/#monitoring-commands)
*   [File Set Types](/documentation/4.2.6-series/monopt/#file-set-types)

* * *

#### Introduction

The <code>ntpd</code> includes a comprehensive monitoring facility which collects statistical data of various types and writes the data to files associated with each type at defined events or intervals. The files associated with a particular type are collectively called the generation file set for that type. The files in the file set are the members of that set.

File sets have names specific to the type and generation epoch. The names are constructed from three concatenated elements _<code>prefix</code>_, _<code>filename</code>_ and _<code>suffix</code>_:

<code>**_prefix_**</code>

: The directory path specified in the <code>statsdir</code> command.

<code>**_name_**</code>

: The name specified by the <code>file</code> option of the <code>filegen</code> command.

<code>**_suffix_**</code>

: A string of elements bdginning with . (dot) followed by a number of elements depending on the file set type.

Statistics files can be managed using scripts, examples of which are in the <code>./scripts</code> directory. Using these or similar scripts and Unix <code>cron</code> jobs, the files can be automatically summarized and archived for retrospective analysis.
* * *

#### Monitoring Commands

<code>**filegen _name_ file _filename_ [type _type_] [link | nolink] [enable | disable] _name_**</code>

: Specifies the file set type from the list in the next section.

<code>**file _filename_**</code>

: Specifies the file set name.

<code>**type _typename_**</code>

: Specifies the file set interval. The following intervals are supported with default <code>day</code>:

<code>**none**</code>

: The file set is actually a single plain file.

<code>**pid**</code>

: One file set member is created for every incarnation of <code>ntpd</code>. The file name suffix is the string .<code>n</code>, where <code>n</code> is the process ID of the <code>ntpd</code> server process.

<code>**day**</code>

: One file set member is created per day. A day is defined as the period between 00:00 and 23:59 UTC. The file name suffix is the string <code>.yyyymmdd</code>, where <code>yyyy</code> is the year, <code>mm</code> the month of the year and <code>dd</code> the day of the month. Thus, member created on 10 December 1992 would have suffix <code>.19921210</code>.

<code>**week**</code>

: One file set member is created per week. The week is defined as the day of year modulo 7. The file name suffix is the string <code>.yyyyWww</code>, where <code>yyyy</code> is the year, <code>W</code> stands for itself and <code>ww</code> the week number starting from 0. For example, The member created on 10 January 1992 would have suffix <code>.1992W1</code>.

<code>**month**</code>

: One file set member is created per month. The file name suffix is the string <code>.yyyymm</code>, where <code>yyyy</code> is the year and <code>mm</code> the month of the year starting from 1. For example, The member created on 10 January 1992 would have suffix <code>.199201</code>.

<code>**year**</code>

: One file set member is generated per year. The file name suffix is the string <code>.yyyy</code>, where <code>yyyy</code> is the year. For example, The member created on 1 January 1992 would have suffix <code>.1992</code>.

<code>**age**</code>

: One file set member is generated every 24 hours of <code>ntpd</code> operation. The filename suffix is the string <code>.adddddddd</code>, where <code>a</code> stands for itself and <code>dddddddd</code> is the <code>ntpd</code> running time in seconds at the start of the corresponding 24-hour period.

<code>**link | nolink**</code>

: It is convenient to be able to access the current file set members by file name, but without the suffix. This feature is enabled by <code>link</code> and disabled by <code>nolink</code>. If enabled, which is the default, a hard link from the current file set member to a file without suffix is created. When there is already a file with this name and the number of links to this file is one, it is renamed by appending a dot, the letter <code>C</code>, and the pid of the <code>ntpd</code> server process. When the number of links is greater than one, the file is unlinked. This allows the current file to be accessed by a constant name.

<code>**enable | disable**</code>

: Enable or disable the recording function, with default <code>enable</code>. These options are intended for remote configutation commands.

<code>**statsdir _directory_path_**</code>

: Specify the directory path prefix for statistics file names.

* * *

#### File Set Types

<code>**clockstats**</code>

: Record reference clock statistics. Each update received from a reference clock driver appends one line to the <code>clockstats</code> file set:

`49213 525.624 127.127.4.1 93 226 00:08:29.606 D`

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `127.127.4.1` | IP | reference clock address |
| message | text | log message |

The <code>_message_</code> field includes the last timecode received in decoded ASCII format, where meaningful. In some cases a good deal of additional information is displayed. See information specific to each reference clock for further details.

<code>**cryptostats**</code>

: Record significant events in the Autokey protocol. This option requires the OpenSSL cryptographic software library. Each event appends one line to the <code>cryptostats</code> file set:

<code>49213 525.624 128.4.1.1 _message_</code>

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `128.4.1.1` | IP | source address (`0.0.0.0` for system) |
| message | text | log message |

The <code>_message_</code> field includes the message type and certain ancillary information. See the [Authentication Options](/documentation/4.2.6-series/authopt/) page for further information.

<code>**loopstats**</code>

: Record clock discipline loop statistics. Each system clock update appends one line to the <code>loopstats</code> file set:

`50935 75440.031 0.000006019 13.778 0.000351733 0.013380 6`

| Item | Units | Description |
| ----- | ----- | ----- |
| `50935` | MJD | date |
| `75440.031` | s | time past midnight |
| `0.000006019` | s | clock offset |
| `13.778` | PPM | frequency offset |
| `0.000351733` | s | RMS jitter |
| `0.013380` | PPM | RMS frequency jitter (aka wander) |
| `6` | log<sub>2</sub> s | clock discipline loop time constant |

<code>**peerstats**</code>

: Record peer statistics. Each NTP packet or reference clock update received appends one line to the <code>peerstats</code> file set:

`48773 10847.650 127.127.4.1 9714 -0.001605376 0.000000000 0.001424877 0.000958674`

| Item | Units | Description |
| ----- | ----- | ----- |
| `48773` | MJD | date |
| `10847.650` | s | time past midnight |
| `127.127.4.1` | IP | source address |
| `9714` | hex | status word |
| `-0.001605376` | s | clock offset |
| `0.000000000` | s | roundtrip delay |
| `0.001424877` | s | dispersion |
| `0.000958674` | s | RMS jitter |

The status field is encoded in hex format as described in Appendix B of the NTP specification RFC 1305.

<code>**protostats**</code>

: Record significant peer, system and rptpcp events. Each significant event appends one line to the <code>protostats</code> file set:

<code>49213 525.624 128.4.1.1 963a 8a _message_</code>

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `128.4.1.1` | IP | source address (`0.0.0.0` for system) |
| `963a` | code | status word |
| `8a` | code | event message code |
| message | text | event message |

The event message code and <code>_message_</code> field are described on the [Event Messages and Status Words](/documentation/4.2.6-series/decode/) page.

<code>**rawstats**</code>

: Record timestamp statistics. Each NTP packet received appends one line to the <code>rawstats</code> file set:

`50928 2132.543 128.4.1.1 128.4.1.20 3102453281.584327000 3102453281.58622800031 02453332.540806000 3102453332.541458000`

| Item | Units | Description |
| ----- | ----- | ----- |
| `50928` | MJD | date |
| `2132.543` | s | time past midnight |
| `128.4.1.1` | IP | source address |
| `128.4.1.20` | IP | destination address |
| `3102453281.584327000` | NTP s | origin timestamp |
| `3102453281.58622800031` | NTP s | receive timestamp |
| `02453332.540806000` | NTP s | transmit timestamp |
| `3102453332.541458000` | NTP s | destination timestamp |

<code>**sysstats**</code>

: Record system statistics. Each hour one line is appended to the <code>sysstats</code> file set in the following format:

`50928 2132.543 3600 81965 0 9546 56 512 540 10 4 147 1`

| Item | Units | Description |
| ----- | ----- | ----- |
| `50928` | MJD | date |
| `2132.543` | s | time past midnight |
| `3600` | s | time since reset |
| `81965` | # | packets received |
| `0` | # | packets for this host |
| `9546` | # | current versions |
| `56` | # | old version |
| `512` | # | access denied |
| `540` | # | bad length or format 
| `10` | # | bad authentication |
| `4` | # | declined |
| `147` | # | rate exceeded |
| `1` | # | kiss-o'-death packets sent |

<code>**timingstats**</code>

: (Only available when the daemon is compiled with process time debugging support (<code>-\-enable-debug-timing</code> - costs performance). Record processing time statistics for various selected code paths.

`53876 36.920 10.0.3.5 1 0.000014592 input processing delay`

| Item | Units | Description |
| ----- | ----- | ----- |
| `53876` | MJD | date |
| `36.920` | s | time past midnight |
| `10.0.3.5` | IP | server address |
| `1` | # | event count |
| `0.000014592` | s | total time |
| message | text | code path description (see source) |