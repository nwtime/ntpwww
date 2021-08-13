---
title: "ntpq - standard NTP query program"
type: archives
---

![gif](/archives/pic/bustardfly.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

A typical NTP monitoring packet

Last update: 04-Nov-2009 0:12 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.6-series/ntpq/#synopsis)
*   [Description](/archives/4.2.6-series/ntpq/#description)
*   [Internal Commands](/archives/4.2.6-series/ntpq/#internal-commands)
*   [Control Message Commands](/archives/4.2.6-series/ntpq/#control-message-commands)
*   [Status Words and Kiss Codes](/archives/4.2.6-series/ntpq/#status-words-and-kiss-codes)
*   [System Variables](/archives/4.2.6-series/ntpq/#system-variables)
*   [Peer Variables](/archives/4.2.6-series/ntpq/#peer-variables)
*   [Clock Variables](/archives/4.2.6-series/ntpq/#clock-variables)

* * *

#### Synopsis

<tt>ntpq [-46dinp] [-c _command_] [_host_] [...]</tt>

* * *

#### Description

The <tt>ntpq</tt> utility program is used to monitor NTP daemon <tt>ntpd</tt> operations and determine performance. It uses the standard NTP mode 6 control message formats defined in Appendix B of the NTPv3 specification RFC1305. The same formats are used in NTPv4, although some of the variable names have changed and new ones added. The description on this page is for the NTPv4 variables.

The program can be run either in interactive mode or controlled using command line arguments. Requests to read and write arbitrary variables can be assembled, with raw and pretty-printed output options being available. The <tt>ntpq</tt> can also obtain and print a list of peers in a common format by sending multiple queries to the server.

If one or more request options is included on the command line when <tt>ntpq</tt> is executed, each of the requests will be sent to the NTP servers running on each of the hosts given as command line arguments, or on localhost by default. If no request options are given, <tt>ntpq</tt> will attempt to read commands from the standard input and execute these on the NTP server running on the first host given on the command line, again defaulting to localhost when no other host is specified. <tt>ntpq</tt> will prompt for commands if the standard input is a terminal device.

<tt>ntpq</tt> uses NTP mode 6 packets to communicate with the NTP server, and hence can be used to query any compatible server on the network which permits it. Note that since NTP is a UDP protocol this communication will be somewhat unreliable, especially over large distances in terms of network topology. <tt>ntpq</tt> makes one attempt to retransmit requests, and will time requests out if the remote host is not heard from within a suitable timeout time.

Note that in contexts where a host name is expected, a <tt>-4</tt> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <tt>-6</tt> qualifier forces DNS resolution to the IPv6 namespace.

For examples and usage, see the [NTP Debugging Techniques](/archives/4.2.6-series/debug) page.

Command line options are described following. Specifying a command line option other than <tt>-i</tt> or <tt>-n</tt> will cause the specified query (queries) to be sent to the indicated host(s) immediately. Otherwise, <tt>ntpq</tt> will attempt to read interactive format commands from the standard input.

<dl>

<dt><tt>-4</tt></dt>

Force DNS resolution of following host names on the command line to the IPv4 namespace.

<dt><tt>-6</tt></dt>

Force DNS resolution of following host names on the command line to the IPv6 namespace.

<dt><tt>-c</tt></dt>

The following argument is interpreted as an interactive format command and is added to the list of commands to be executed on the specified host(s). Multiple <tt>-c</tt> options may be given.

<dt><tt>-d</tt></dt>

Turn on debugging mode.

<dt><tt>-i</tt></dt>

Force <tt>ntpq</tt> to operate in interactive mode. Prompts will be written to the standard output and commands read from the standard input.

<dt><tt>-n</tt></dt>

Output all host addresses in dotted-quad numeric format rather than converting to the canonical host names.

<dt><tt>-p</tt></dt>

Print a list of the peers known to the server as well as a summary of their state. This is equivalent to the <tt>peers</tt> interactive command.

* * *

#### Internal Commands

Interactive format commands consist of a keyword followed by zero to four arguments. Only enough characters of the full keyword to uniquely identify the command need be typed. The output of a command is normally sent to the standard output, but optionally the output of individual commands may be sent to a file by appending a <tt>></tt>, followed by a file name, to the command line. A number of interactive format commands are executed entirely within the <tt>ntpq</tt> program itself and do not result in NTP mode-6 requests being sent to a server. These are described following.

<dl>

<dt><tt>? [_command_keyword_]</tt>  
<tt>help [_command_keyword_]</tt></dt>

A <tt>?</tt> by itself will print a list of all the command keywords known to <tt>ntpq</tt>. A <tt>?</tt> followed by a command keyword will print function and usage information about the command.

<dt><tt>addvars _name_ [ = _value_] [...]</tt>  
<tt>rmvars _name_ [...]</tt>  
<tt>clearvars</tt></dt>

The arguments to this command consist of a list of items of the form <tt>_name_ = _value_</tt>, where the <tt>= _value_</tt> is ignored, and can be omitted in read requests. <tt>ntpq</tt> maintains an internal list in which data to be included in control messages can be assembled, and sent using the <tt>readlist</tt> and <tt>writelist</tt> commands described below. The <tt>addvars</tt> command allows variables and optional values to be added to the list. If more than one variable is to be added, the list should be comma-separated and not contain white space. The <tt>rmvars</tt> command can be used to remove individual variables from the list, while the <tt>clearlist</tt> command removes all variables from the list.

<dt><tt>cooked</tt></dt>

Display server messages in prettyprint format.

<dt><tt>debug more | less | off</tt></dt>

Turns internal query program debugging on and off.

<dt><tt>delay _milliseconds_</tt></dt>

Specify a time interval to be added to timestamps included in requests which require authentication. This is used to enable (unreliable) server reconfiguration over long delay network paths or between machines whose clocks are unsynchronized. Actually the server does not now require timestamps in authenticated requests, so this command may be obsolete.

<dt><tt>host _name_</tt></dt>

Set the host to which future queries will be sent. The name may be either a DNS name or a numeric address.

<dt><tt>hostnames [yes | no]</tt></dt>

If <tt>yes</tt> is specified, host names are printed in information displays. If <tt>no</tt> is specified, numeric addresses are printed instead. The default is <tt>yes</tt>, unless modified using the command line <tt>-n</tt> switch.

<dt><tt>keyid _keyid_</tt></dt>

This command specifies the key number to be used to authenticate configuration requests. This must correspond to a key number the server has been configured to use for this purpose.

<dt><tt>ntpversion 1 | 2 | 3 | 4</tt></dt>

Sets the NTP version number which <tt>ntpq</tt> claims in packets. Defaults to 2, Note that mode-6 control messages (and modes, for that matter) didn't exist in NTP version 1.

<dt><tt>passwd</tt></dt>

This command prompts for a password to authenticate configuration requests. The password must correspond to the key configured for NTP server for this purpose.

<dt><tt>quit</tt></dt>

Exit <tt>ntpq</tt>.

<dt><tt>raw</tt></dt>

Display server messages as received and without reformatting.

<dt><tt>timeout _milliseconds_</tt></dt>

Specify a timeout period for responses to server queries. The default is about 5000 milliseconds. Note that since <tt>ntpq</tt> retries each query once after a timeout, the total waiting time for a timeout will be twice the timeout value set.

* * *

#### Control Message Commands

Association IDs are used to identify system, peer and clock variables. System variables are assigned an association ID of zero and system name space, while each association is assigned a nonzero association ID and peer namespace. Most control commands send a single mode-6 message to the server and expect a single response message. The exceptions are the <tt>peers</tt> command, which sends a series of messages, and the <tt>mreadlist</tt> and <tt>mreadvar</tt> commands, which iterate over a range of associations.

<dt id="as"><tt>associations</tt></dt>

Display a list of mobilized associations in the form

<tt>ind assid status conf reach auth condition last_event cnt</tt>

| Variable | Description |
| ----- | ----- |
| `ind` | index on this list |
| `assid` | association ID |
| `status` | [peer status word](/archives/4.2.6-series/decode/#peer-status-word) |
| `conf` | `yes`: persistent<br> `no`: ephemeral |
| `reach` | `yes`: reachable<br> `no`: unreachable |
| `auth` | `ok`, `yes`, `bad` and `none` |
| `condition` | selection status (see the `select` field of the peer status word) |
| `last_event` | event report (see the `event` field of the peer status word) |
| `cnt` | event count (see the `count` field of the peer status word) |

<dt><tt>clockvar _assocID_ [_name_ [ = _value_ [...]] [...]</tt>  
<tt>cv _assocID_ [_name_ [ = _value_ [...] ][...]</tt></dt>

Display a list of [clock variables](/archives/4.2.6-series/ntpq#clock-variables) for those associations supporting a reference clock.

<dt><tt>:config [...]</tt></dt>

Send the remainder of the command line, including whitespace, to the server as a run-time configuration command in the same format as the configuration file. This command is experimental until further notice and clarification. Authentication is of course required.

<dt><tt>config-from-file _filename_</tt></dt>

Send each line of _filename_ to the server as run-time configuration commands in the same format as the configuration file. This command is experimental until further notice and clarification. Authentication is of course required.

<dt><tt>keyid</tt></dt>

Specify the key ID to use for write requests.

<dt><tt>lassociations</tt></dt>

Perform the same function as the associations command, except display mobilized and unmobilized associations.

<dt><tt>mreadvar _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]</tt>  
<tt>mrv _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]</tt></dt>

Perform the same function as the <tt>readvar</tt> command, except for a range of association IDs. This range is determined from the association list cached by the most recent <tt>associations</tt> command.

<dt><tt>passociations</tt></dt>

Perform the same function as the <tt>associations command</tt>, except that it uses previously stored data rather than making a new query.

<dt><tt>passwd</tt></dt>

Specify the password to use for write requests.

<dt id="pe"><tt>peers</tt></dt>

Display a list of peers in the form

<tt>[tally]remote refid st t when pool reach delay offset jitter</tt>

| Variable | Description |
| ----- | ----- |
| `[tally]` | single-character code indicating current value of the `select` field of the [peer status word](/archives/4.2.6-series/decode/#peer-status-word) |
| `remote` | host name (or IP number) of peer |
| `refid` | association ID or kiss code |
| `st` | stratum |
| `t` | `u`: unicast <br> `b`: broadcast <br> `l`: local |
| `when` | sec/min/hr since last received packet |
| `poll` | poll interval (log<sub>2</sub> s) |
| `reach` | reach shift register (octal) |
| `delay` | roundtrip delay |
| `offset` | offset |
| `jitter` | jitter |

<dt id="rv"><tt>readvar _assocID_ _name_ [ = _value_ ] [,...]</tt>  
<tt>rv _assocID_ [ _name_ ] [,...]</tt></dt>

Display the specified variables. If <tt>_assocID_</tt> is zero, the variables are from the [system variables](/archives/4.2.6-series/ntpq#system-variables) name space, otherwise they are from the [peer variables](/archives/4.2.6-series/ntpq#peer-variables) name space. The <tt>_assocID_</tt> is required, as the same name can occur in both spaces. If no <tt>_name_</tt> is included, all operative variables in the name space are displayed. In this case only, if the <tt>_assocID_</tt> is omitted, it is assumed zero. Multiple names are specified with comma separators and without whitespace. Note that time values are represented in milliseconds and frequency values in parts-per-million (PPM). Some NTP timestamps are represented in the format YYYYMMDDTTTT, where YYYY is the year, MM the month of year, DD the day of month and TTTT the time of day.

<dt id="saveconfig"><tt>saveconfig _filename_</tt></dt>

Write the current configuration, including any runtime modifications given with <tt>:config</tt> or <tt>config-from-file</tt>, to the ntpd host's file _filename_. This command will be rejected by the server unless [saveconfigdir](/archives/4.2.6-series/miscopt#saveconfigdir) appears in the <tt>ntpd</tt> configuration file. _filename_ can use strftime() format specifiers to substitute the current date and time, for example, <tt>saveconfig ntp-%Y%m%d-%H%M%S.conf</tt>. The filename used is stored in system variable <tt>savedconfig</tt>. Authentication is required.

<dt><tt>writevar _assocID_ _name_ = _value_ [,...]</tt></dt>

Write the specified variables. If the <tt>_assocID_</tt> is zero, the variables are from the [system variables](/archives/4.2.6-series/ntpq#system-variables) name space, otherwise they are from the [peer variables](/archives/4.2.6-series/ntpq#peer-variables) name space. The <tt>_assocID_</tt> is required, as the same name can occur in both spaces.

* * *

#### Status Words and Kiss Codes

The current state of the operating program is shown in a set of status words maintained by the system and each association separately. These words are displayed in the <tt>rv</tt> and <tt>as</tt> commands both in hexadecimal and decoded short tip strings. The codes, tips and short explanations are on the [Event Messages and Status Words](/archives/4.2.6-series/decode) page. The page also includes a list of system and peer messages, the code for the latest of which is included in the status word.

Information resulting from protocol machine state transitions is displayed using an informal set of ASCII strings called [kiss codes](/archives/4.2.6-series/decode/#kiss-codes). The original purpose was for kiss-o'-death (KoD) packets sent by the server to advise the client of an unusual condition. They are now displayed, when appropriate, in the reference identifier field in various billboards.

* * *

#### System Variables

The following system variables appear in the <tt>rv</tt> billboard. Not all variables are displayed in some configurations.

| Variable | Description |
| ----- | ----- |
| `status` | [system status word](/archives/4.2.6-series/decode/#system-status-word) |
| `version` | NTP software version and build time |
| `processor` | hardware platform and version |
| `system` | operating system and version |
| `leap` | leap warning indicator (0-3) |
| `stratum` | stratum (1-15) |
| `precision` | precision (log<sub>2</sub> s) |
| `rootdelay` | total roundtrip delay to the primary reference clock |
| `rootdisp` | total dispersion to the primary reference clock |
| `peer` | system peer association ID |
| `tc` | time constant and poll exponent (log<sub>2</sub> s) (3-17) |
| `mintc` | minimum time constant (log<sub>2</sub> s) (3-10) |
| `clock` | date and time of day |
| `refid` | reference ID or [kiss code](/archives/4.2.6-series/decode/#kiss-codes) |
| `reftime` | reference time |
| `offset` | combined time offset |
| `sys_jitter` | combined system jitter |
| `frequency` | clock frequency offset (PPM) |
| `clk_wander` | clock frequency wander (PPM) |
| `clk_jitter` | clock jitter |
| `tai` | TAI-UTC offset (s) |
| `leapsec` | NTP seconds when the next leap second is/was inserted |
| `expire` | NTP seconds when the NIST leapseconds file expires |

The jitter and wander statistics are exponentially-weighted RMS averages. The system jitter is defined in the NTPv4 specification; the clock jitter statistic is computed by the clock discipline module.

When the NTPv4 daemon is compiled with the OpenSSL software library, additional system variables are displayed, including some or all of the following, depending on the particular Autokey dance:

| Variable | Description |
| ----- | ----- |
| `host` | Autokey host name |
| `group` | Autokey group name |
| `flags` | host flags (see Autokey specification) |
| `digest` | OpenSSL message digest algorithm |
| `signature` | OpenSSL digest/signature scheme |
| `update` | NTP seconds at last signature update |
| `cert` | certificate subject, issuer and certificate flags |
| `until` | NTP seconds when the certificate expires |

* * *

#### Peer Variables

The following system variables appear in the <tt>rv</tt> billboard for each association. Not all variables are displayed in some configurations.

| Variable | Description |
| ----- | ----- |
| `associd` | association ID |
| `status` | [peer status word](/archives/4.2.6-series/decode/#peer-status-word) |
| `srcadr`<br>  `srcport` | source (remote) IP address and port |
| `dstadr`<br> `dstport` | destination (local) IP address and port |
| `leap` | leap indicator (0-3) |
| `stratum` | stratum (0-15) |
| `precision` | precision (log<sub>2</sub> s) |
| `rootdelay` | total roundtrip delay to the primary reference clock |
| `rootdisp` | total root dispersion to the primary reference clock |
| `refid` | reference ID or [kiss code](/archives/4.2.6-series/decode/#kiss-codes) |
| `reftime` | reference time |
| `reach` | reach register (octal) |
| `unreach` | unreach counter |
| `hmode` | host mode (1-6) |
| `pmode` | peer mode (1-5) |
| `hpoll` | host poll exponent (log<sub>2</sub> s) (3-17) |
| `ppoll` | peer poll exponent (log<sub>2</sub> s) (3-17) |
| `headway` | headway (see [Rate Management and the Kiss-o'-Death Packet)](/archives/4.2.6-series/rate) |
| `flash` | [flash status word](/archives/4.2.6-series/decode/#flash-status-word) |
| `offset` | filter offset |
| `delay` | filter delay |
| `dispersion` | filter dispersion |
| `jitter` | filter jitter |
| `bias` | unicast/broadcast bias |
| `xleave` | interleave delay (see [NTP Interleaved Modes](/archives/4.2.6-series/xleave)) |

The bias variable is calculated when the first broadcast packet is received after the calibration volley. It represents the offset of the broadcast subgraph relative to the unicast subgraph. The xleave variable appears only in the interleaved symmetric and interleaved modes. It represents the internal queuing, buffering and transmission delays for the preceding packet.

When the NTPv4 daemon is compiled with the OpenSSL software library, additional peer variables are displayed, including the following:

| Variable | Description |
| ----- | ----- |
| `flags` | peer flags (see Autokey specification) |
| `host` | Autokey server name |
| `signature` | OpenSSL digest/signature scheme |
| `initsequence` | initial key ID |
| `initkey` | initial key index |
| `timestamp` | Autokey signature timestamp |

* * *

#### Clock Variables

The following clock variables appear in the <tt>cv</tt> billboard for each association with a reference clock. Not all variables are displayed in some configurations.

| Variable | Description |
| ----- | ----- |
| `associd` | association ID |
| `status` | [clock status word](/archives/4.2.6-series/decode/#clock-status-word) |
| `device` | device description |
| `timecode` | ASCII time code string (specific to device) |
| `poll` | poll messages sent |
| `noreply` | no reply |
| `badformat` | bad format |
| `baddata` | bad date or time |
| `fudgetime1` | fudge time 1 |
| `fudgetime2` | fudge time 2 |
| `stratum` | driver stratum |
| `refid` | driver reference ID |
| `flags` | driver flags |