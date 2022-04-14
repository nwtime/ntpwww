---
title: "Monitoring Options"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Monitoring Support](/documentation/3-5.93e/monopt/#monitoring-support)
*   [Monitoring Commands](/documentation/3-5.93e/monopt/#monitoring-commands)

* * *

#### Monitoring Support

<code>xntpd</code> includes a comprehensive monitoring facility suitable for continuous, long term recording of server and client timekeeping performance. See the <code>statistics</code> command below for a listing and example of each type of statistics currently supported. Statistic files are managed using file generation sets and scripts in the <code>./scripts</code> directory of this distribution. Using these facilities and Unix <code>cron</code> jobs, the data can be automatically summarized and archived for retrospective analysis.

* * *

#### Monitoring Commands

<code>**statistics _name_ [...]**</code>

: Enables writing of statistics records. Currently, three kinds of <code>_name_</code> statistics are supported.

<code>loopstats</code>

: Enables recording of loop filter statistics information. Each update of the local clock outputs a line of the following form to the file generation set named <code>loopstats</code>:

`48773 10847.650 0.0001307 17.3478 2`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next three fields show time offset in seconds, frequency offset in parts-per-million and time constant of the clock-discipline algorithm at each update of the clock.

<code>peerstats</code>

: Enables recording of peer statistics information. This includes statistics records of all peers of a NTP server and of special signals, where present and configured. Each valid update appends a line of the following form to the current element of a file generation set named <code>peerstats</code>:

`48773 10847.650 127.127.4.1 9714 -0.001605 0.00000 0.00142`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next two fields show the peer address in dotted-quad notation and status, respectively. The status field is encoded in hex in the format described in Appendix A of the NTP specification RFC 1305. The final three fields show the offset, delay, and dispersion, all in seconds.

<code>clockstats</code>

: Enables recording of clock driver statistics information. Each update received from a clock driver outputs a line of the following form to the file generation set named <code>clockstats</code>:

`49213 525.624 127.127.4.1 93 226 00:08:29.606 D`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next field shows the clock address in dotted-quad notation. The final field shows the last timecode received from the clock in decoded ASCII format, where meaningful. In some clock drivers a good deal of additional information can be gathered and displayed as well. See information specific to each clock for further details.

<code>**statsdir _directory_path_**</code>

: Indicates the full path of a directory where statistics files should be created (see below). This keyword allows the (otherwise constant) <code>filegen</code> filename prefix to be modified for file generation sets, which is useful for handling statistics logs.

<code>**filegen _name_ [file _filename_] [type _typename_] [ flag _flagval_ ] [link | nolink] [enable | disable]**</code>

: Configures setting of generation file set <code>_name_</code>. Generation file sets provide a means for handling files that are continuously growing during the lifetime of a server. Server statistics are a typical example for such files. Generation file sets provide access to a set of files used to store the actual data. At any time at most one element of the set is being written to. The type given specifies when and how data will be directed to a new element of the set. This way, information stored in elements of a file set that are currently unused are available for administrational operations without the risk of disturbing the operation of <code>xntpd</code>. (Most important: they can be removed to free space for new data produced.)

Filenames of set members are built from three elements: 

<code>_prefix_</code>

: This is a constant filename path. It is not subject to modifications via the <code>filegen</code> option. It is defined by the server, usually specified as a compile-time constant. It may, however, be configurable for individual file generation sets via other commands. For example, the prefix used with <code>loopstats</code> and <code>peerstats</code> generation can be configured using the <code>statsdir</code> option explained above.

<code>_filename_</code>

This string is directly concatenated to the prefix mentioned above (no intervening `/` (slash)). This can be modified using the <code>file</code> argument to the <code>filegen</code> statement. No <code>..</code> elements are allowed in this component to prevent filenames referring to parts outside the filesystem hierarchy denoted by <code>prefix</code>.

<code>_suffix_</code>

This part reflects individual elements of a file set. The following types are supported: 

<code>none</code>

: The file set is actually a single plain file.

<code>pid</code>

: One element of file set is used per incarnation of a <code>xntpd</code> server. This type does not perform any changes to file set members during runtime, however it provides an easy way of separating files belonging to different <code>xntpd</code> server incarnations. The set member filename is built by appending a <code>.</code> (dot) to concatenated <code>_prefix_</code> and <code>_filename_</code> strings, and appending the decimal representation of the process ID of the <code>xntpd</code> server process.

<code>day</code>

: One file generation set element is created per day. A day is defined as the period between 00:00 and 24:00 UTC. The file set member suffix consists of a <code>.</code> (dot) and a day specification in the form <code>YYYYMMdd</code>. <code>YYYY</code> is a 4-digit year number (e.g., 1992). <code>MM</code> is a two-digit month number. <code>dd</code> is a two-digit day number. Thus, all information written at 10 December 1992 would end up in a file named <code>_prefix filename_.19921210</code>.

<code>week</code>

: Any file set member contains data related to a certain week of a year. The term week is defined by computing day-of-year modulo 7. Elements of such a file generation set are distinguished by appending the following suffix to the file set filename base: A dot, a 4-digit year number, the letter <code>W</code>, and a 2-digit week number. For example, information from January, 10th 1992 would end up in a file with suffix <code>.1992W1</code>.

<code>month</code>

: One generation file set element is generated per month. The file name suffix consists of a dot, a 4-digit year number, and a 2-digit month.

<code>year</code>

: One generation file element is generated per year. The filename suffix consists of a dot and a 4-digit year number.

<code>age</code>

: This type of file generation sets changes to a new element of the file set every 24 hours of server operation. The filename suffix consists of a dot, the letter <code>a</code>, and an 8-digit number. This number is taken to be the number of seconds the server is running at the start of the corresponding 24-hour period.

It is convenient to be able to access the current element of a file generation set by a fixed name. This feature is enabled by specifying <code>link</code> and disabled using <code>nolink</code>. If <code>link</code> is specified, a hard link from the current file set element to a file without suffix is created. When there is already a file with this name and the number of links of this file is one, it is renamed appending a dot, the letter <code>C</code>, and the pid of the <code>xntpd</code> server process. When the number of links is greater than one, the file is unlinked. This allows the current file to be accessed by a constant name.