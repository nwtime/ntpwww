---
title: "Monitoring Options"
type: archives
---

![gif](/archives/pic/pogo8.gif)[](http://www.eecis.udel.edu/~mills/pictures.html) from _Pogo_, Walt Kelly

Pig was hired to watch the logs.

Last update: 10-May-2009 16:19 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.6-series/monopt/#introduction)
*   [Monitoring Commands](/archives/4.2.6-series/monopt/#monitoring-commands)
*   [File Set Types](/archives/4.2.6-series/monopt/#file-set-types)

* * *

#### Introduction

The <tt>ntpd</tt> includes a comprehensive monitoring facility which collects statistical data of various types and writes the data to files associated with each type at defined events or intervals. The files associated with a particular type are collectively called the generation file set for that type. The files in the file set are the members of that set.

File sets have names specific to the type and generation epoch. The names are constructed from three concatenated elements _<tt>prefix</tt>_, _<tt>filename</tt>_ and _<tt>suffix</tt>_:

<dt>_<tt>prefix</tt>_</dt>

The directory path specified in the <tt>statsdir</tt> command.

<dt>_<tt>name</tt>_</dt>

The name specified by the <tt>file</tt> option of the <tt>filegen</tt> command.

<dt>_<tt>suffix</tt>_</dt>

A string of elements bdginning with . (dot) followed by a number of elements depending on the file set type.

Statistics files can be managed using scripts, examples of which are in the <tt>./scripts</tt> directory. Using these or similar scripts and Unix <tt>cron</tt> jobs, the files can be automatically summarized and archived for retrospective analysis.
* * *

#### Monitoring Commands

<dt id="filegen"><tt>filegen _name_ file _filename_ [type _type_] [link | nolink] [enable | disable]</tt></dt>

<dt>_<tt>name</tt>_</dt>

Specifies the file set type from the list in the next section.

<dt><tt>file _filename_</tt></dt>

Specfies the file set name.

<dt><tt>type _typename_</tt></dt>

Specifies the file set interval. The following intervals are supported with default <tt>day</tt>:

<dt><tt>none</tt></dt>

The file set is actually a single plain file.

<dt><tt>pid</tt></dt>

One file set member is created for every incarnation of <tt>ntpd</tt>. The file name suffix is the string .<tt>n</tt>, where <tt>n</tt> is the process ID of the <tt>ntpd</tt> server process.

<dt><tt>day</tt></dt>

One file set member is created per day. A day is defined as the period between 00:00 and 23:59 UTC. The file name suffix is the string .<tt>yyyymmdd</tt>, where <tt>yyyy</tt> is the year, <tt>mm</tt> the month of the year and <tt>dd</tt> the day of the month. Thus, member created on 10 December 1992 would have suffix <tt>.19921210</tt>.

<dt><tt>week</tt></dt>

One file set member is created per week. The week is defined as the day of year modulo 7. The file name suffix is the string .<tt>yyyyWww</tt>, where <tt>yyyy</tt> is the year, <tt>W</tt> stands for itself and <tt>ww</tt> the week number starting from 0. For example, The member created on 10 January 1992 would have suffix <tt>.1992W1</tt>.

<dt><tt>month</tt></dt>

One file set member is created per month. The file name suffix is the string .<tt>yyyymm</tt>, where <tt>yyyy</tt> is the year and <tt>mm</tt> the month of the year starting from 1. For example, The member created on 10 January 1992 would have suffix <tt>.199201</tt>.

<dt><tt>year</tt></dt>

One file set member is generated per year. The file name suffix is the string .<tt>yyyy</tt>, where <tt>yyyy</tt> is the year. For example, The member created on 1 January 1992 would have suffix <tt>.1992</tt>.

<dt><tt>age</tt></dt>

One file set member is generated every 24 hours of <tt>ntpd</tt> operation. The filename suffix is the string <tt>.adddddddd</tt>, where <tt>a</tt> stands for itself and <tt>dddddddd</tt> is the <tt>ntpd</tt> running time in seconds at the start of the corresponding 24-hour period.

<dt><tt>link | nolink</tt></dt>

It is convenient to be able to access the current file set members by file name, but without the suffix. This feature is enabled by <tt>link</tt> and disabled by <tt>nolink</tt>. If enabled, which is the default, a hard link from the current file set member to a file without suffix is created. When there is already a file with this name and the number of links to this file is one, it is renamed by appending a dot, the letter <tt>C</tt>, and the pid of the <tt>ntpd</tt> server process. When the number of links is greater than one, the file is unlinked. This allows the current file to be accessed by a constant name.

<dt><tt>enable | disable</tt></dt>

Enable or disable the recording function, with default <tt>enable</tt>. These options are intended for remote configutation commands.

<dt><tt>statsdir _directory_path_</tt></dt>

Specify the directory path prefix for statistics file names.

* * *

#### File Set Types

<dt><tt>clockstats</tt></dt>

Record reference clock statistics. Each update received from a reference clock driver appends one line to the <tt>clockstats</tt> file set:

<tt>49213 525.624 127.127.4.1 93 226 00:08:29.606 D</tt>

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `127.127.4.1` | IP | reference clock address |
| message | text | log message |

The <tt>_message_</tt> field includes the last timecode received in decoded ASCII format, where meaningful. In some cases a good deal of additional information is displayed. See information specific to each reference clock for further details.

<dt><tt>cryptostats</tt></dt>

Record significant events in the Autokey protocol. This option requires the OpenSSL cryptographic software library. Each event appends one line to the <tt>cryptostats</tt> file set:

<tt>49213 525.624 128.4.1.1 _message_</tt>

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `128.4.1.1` | IP | source address (`0.0.0.0` for system) |
| message | text | log message |

The <tt>_message_</tt> field includes the message type and certain ancillary information. See the [Authentication Options](/archives/4.2.6-series/authopt) page for further information.

<dt><tt>loopstats</tt></dt>

Record clock discipline loop statistics. Each system clock update appends one line to the <tt>loopstats</tt> file set:

<tt>50935 75440.031 0.000006019 13.778 0.000351733 0.013380 6</tt>

| Item | Units | Description |
| ----- | ----- | ----- |
| `50935` | MJD | date |
| `75440.031` | s | time past midnight |
| `0.000006019` | s | clock offset |
| `13.778` | PPM | frequency offset |
| `0.000351733` | s | RMS jitter |
| `0.013380` | PPM | RMS frequency jitter (aka wander) |
| `6` | log<sub>2</sub> s | clock discipline loop time constant |

<dt><tt>peerstats</tt></dt>

Record peer statistics. Each NTP packet or reference clock update received appends one line to the <tt>peerstats</tt> file set:

<tt>48773 10847.650 127.127.4.1 9714 -0.001605376 0.000000000 0.001424877 0.000958674</tt>

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

<dt><tt>protostats</tt></dt>

Record significant peer, system and rptpcp events. Each significant event appends one line to the <tt>protostats</tt> file set:

<tt>49213 525.624 128.4.1.1 963a 8a _message_</tt>

| Item | Units | Description |
| ----- | ----- | ----- |
| `49213` | MJD | date |
| `525.624` | s | time past midnight |
| `128.4.1.1` | IP | source address (`0.0.0.0` for system) |
| `963a` | code | status word |
| `8a` | code | event message code |
| message | text | event message |

The event message code and <tt>_message_</tt> field are described on the [Event Messages and Status Words](/archives/4.2.6-series/decode) page.

<dt><tt>rawstats</tt></dt>

Record timestamp statistics. Each NTP packet received appends one line to the <tt>rawstats</tt> file set:

<tt>50928 2132.543 128.4.1.1 128.4.1.20 3102453281.584327000 3102453281.58622800031 02453332.540806000 3102453332.541458000</tt>

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

<dt><tt>sysstats</tt></dt>

Record system statistics. Each hour one line is appended to the <tt>sysstats</tt> file set in the following format:

<tt>50928 2132.543 3600 81965 0 9546 56 512 540 10 4 147 1</tt>

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

<dt><tt>timingstats</tt></dt>

(Only available when the daemon is compiled with process time debugging support (--enable-debug-timing - costs performance). Record processing time statistics for various selected code paths.

<tt>53876 36.920 10.0.3.5 1 0.000014592 input processing delay</tt>

| Item | Units | Description |
| ----- | ----- | ----- |
| `53876` | MJD | date |
| `36.920` | s | time past midnight |
| `10.0.3.5` | IP | server address |
| `1` | # | event count |
| `0.000014592` | s | total time |
| message | text | code path description (see source) |