---
title: "Monitoring Options"
type: archives
---

#### Table of Contents

*   [Monitoring Support](/archives/3-5.93e/monopt/#monitoring-support)
*   [Monitoring Commands](/archives/3-5.93e/monopt/#monitoring-commands)

* * *

#### Monitoring Support

<tt>xntpd</tt> includes a comprehensive monitoring facility suitable for continuous, long term recording of server and client timekeeping performance. See the <tt>statistics</tt> command below for a listing and example of each type of statistics currently supported. Statistic files are managed using file generation sets and scripts in the <tt>./scripts</tt> directory of this distribution. Using these facilities and Unix <tt>cron</tt> jobs, the data can be automatically summarized and archived for retrospective analysis.

* * *

#### Monitoring Commands

<dt><tt>statistics _name_ [...]</tt></dt>

Enables writing of statistics records. Currently, three kinds of _<tt>name</tt>_ statistics are supported.

<dt><tt>loopstats</tt></dt>

Enables recording of loop filter statistics information. Each update of the local clock outputs a line of the following form to the file generation set named <tt>loopstats</tt>:

`48773 10847.650 0.0001307 17.3478 2`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next three fields show time offset in seconds, frequency offset in parts-per-million and time constant of the clock-discipline algorithm at each update of the clock.

<dt><tt>peerstats</tt></dt>

Enables recording of peer statistics information. This includes statistics records of all peers of a NTP server and of special signals, where present and configured. Each valid update appends a line of the following form to the current element of a file generation set named <tt>peerstats</tt>:

`48773 10847.650 127.127.4.1 9714 -0.001605 0.00000 0.00142`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next two fields show the peer address in dotted-quad notation and status, respectively. The status field is encoded in hex in the format described in Appendix A of the NTP specification RFC 1305. The final three fields show the offset, delay, and dispersion, all in seconds.

<dt><tt>clockstats</tt></dt>

Enables recording of clock driver statistics information. Each update received from a clock driver outputs a line of the following form to the file generation set named <tt>clockstats</tt>:

`49213 525.624 127.127.4.1 93 226 00:08:29.606 D`

The first two fields show the date (Modified Julian Day) and time (seconds and fraction past UTC midnight). The next field shows the clock address in dotted-quad notation. The final field shows the last timecode received from the clock in decoded ASCII format, where meaningful. In some clock drivers a good deal of additional information can be gathered and displayed as well. See information specific to each clock for further details.

<dt><tt>statsdir _directory_path_</tt></dt>

Indicates the full path of a directory where statistics files should be created (see below). This keyword allows the (otherwise constant) <tt>filegen</tt> filename prefix to be modified for file generation sets, which is useful for handling statistics logs.

<dt><tt>filegen _name_ [file _filename_] [type _typename_] [ flag _flagval_ ] [link | nolink] [enable | disable]</tt></dt>

Configures setting of generation file set _name_. Generation file sets provide a means for handling files that are continuously growing during the lifetime of a server. Server statistics are a typical example for such files. Generation file sets provide access to a set of files used to store the actual data. At any time at most one element of the set is being written to. The type given specifies when and how data will be directed to a new element of the set. This way, information stored in elements of a file set that are currently unused are available for administrational operations without the risk of disturbing the operation of <tt>xntpd</tt>. (Most important: they can be removed to free space for new data produced.)

Filenames of set members are built from three elements: 

&nbsp;&nbsp;&nbsp;&nbsp;_<tt>prefix</tt>_

&nbsp;&nbsp;&nbsp;&nbsp;This is a constant filename path. It is not subject to modifications via the <tt>filegen</tt> option. It is defined by the server, usually specified as a compile-time constant. It may, however, be configurable for individual file generation sets via other commands. For example, the prefix used with <tt>loopstats</tt> and <tt>peerstats</tt> generation can be configured using the <tt>statsdir</tt> option explained above.

&nbsp;&nbsp;&nbsp;&nbsp;_<tt>filename</tt>_

&nbsp;&nbsp;&nbsp;&nbsp;This string is directly concatenated to the prefix mentioned above (no intervening `/` (slash)). This can be modified using the <tt>file</tt> argument to the <tt>filegen</tt> statement. No <tt>..</tt> elements are allowed in this component to prevent filenames referring to parts outside the filesystem hierarchy denoted by <tt>prefix</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;_<tt>suffix</tt>_

&nbsp;&nbsp;&nbsp;&nbsp;This part reflects individual elements of a file set. The following types are supported: 

&nbsp;&nbsp;&nbsp;&nbsp;<tt>none</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The file set is actually a single plain file.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>pid</tt>

&nbsp;&nbsp;&nbsp;&nbsp;One element of file set is used per incarnation of a <tt>xntpd</tt> server. This type does not perform any changes to file set members during runtime, however it provides an easy way of separating files belonging to different <tt>xntpd</tt> server incarnations. The set member filename is built by appending a <tt>.</tt> (dot) to concatenated _prefix_ and _filename_ strings, and appending the decimal representation of the process ID of the <tt>xntpd</tt> server process.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>day</tt>

&nbsp;&nbsp;&nbsp;&nbsp;One file generation set element is created per day. A day is defined as the period between 00:00 and 24:00 UTC. The file set member suffix consists of a <tt>.</tt> (dot) and a day specification in the form <tt>YYYYMMdd. YYYY</tt> is a 4-digit year number (e.g., 1992). <tt>MM</tt> is a two digit month number. <tt>dd</tt> is a two digit day number. Thus, all information written at 10 December 1992 would end up in a file named <tt>_prefix filename_.19921210</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>week</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Any file set member contains data related to a certain week of a year. The term week is defined by computing day-of-year modulo 7. Elements of such a file generation set are distinguished by appending the following suffix to the file set filename base: A dot, a 4-digit year number, the letter <tt>W</tt>, and a 2-digit week number. For example, information from January, 10th 1992 would end up in a file with suffix <tt>.1992W1</tt>.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>month</tt>

&nbsp;&nbsp;&nbsp;&nbsp;One generation file set element is generated per month. The file name suffix consists of a dot, a 4-digit year number, and a 2-digit month.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>year</tt>

&nbsp;&nbsp;&nbsp;&nbsp;One generation file element is generated per year. The filename suffix consists of a dot and a 4 digit year number.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>age</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This type of file generation sets changes to a new element of the file set every 24 hours of server operation. The filename suffix consists of a dot, the letter <tt>a</tt>, and an 8-digit number. This number is taken to be the number of seconds the server is running at the start of the corresponding 24-hour period.

It is convenient to be able to access the current element of a file generation set by a fixed name. This feature is enabled by specifying <tt>link</tt> and disabled using <tt>nolink</tt>. If <tt>link</tt> is specified, a hard link from the current file set element to a file without suffix is created. When there is already a file with this name and the number of links of this file is one, it is renamed appending a dot, the letter <tt>C</tt>, and the pid of the
<tt>xntpd</tt> server process. When the number of links is greater than one, the file is unlinked. This allows the current file to be accessed by a constant name.