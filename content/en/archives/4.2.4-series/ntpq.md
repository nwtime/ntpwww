---
title: "ntpq - standard NTP query program"
type: archives
---

![gif](/archives/pic/bustardfly.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

A typical NTP monitoring packet

Last update: 18:45 UTC Thursday, July 28, 2005

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.4-series/ntpq/#synopsis)
*   [Description](/archives/4.2.4-series/ntpq/#description)
*   [Internal Commands](/archives/4.2.4-series/ntpq/#internal-commands)
*   [Control Message Commands](/archives/4.2.4-series/ntpq/#control-message-commands)
*   [Tally Codes](/archives/4.2.4-series/ntpq/#tally-codes)
*   [System Variables](/archives/4.2.4-series/ntpq/#system-variables)
*   [Peer Variables](/archives/4.2.4-series/ntpq/#peer-variables)
*   [Flash Codes](/archives/4.2.4-series/ntpq/#flash-codes)
*   [Bugs](/archives/4.2.4-series/ntpq/#bugs)

* * *

#### Synopsis

<tt>ntpq [-inp] [-c _command_] [_host_] [...]</tt>

* * *

#### Description

The <tt>ntpq</tt> utility program is used to monitor NTP daemon <tt>ntpd</tt> operations and determine performance. It uses the standard NTP mode 6 control message formats defined in Appendix B of the NTPv3 specification RFC1305. The same formats are used in NTPv4, although some of the variables have changed and new ones added. The description on this page is for the NTPv4 variables.

The program can be run either in interactive mode or controlled using command line arguments. Requests to read and write arbitrary variables can be assembled, with raw and pretty-printed output options being available. The <tt>ntpq</tt> can also obtain and print a list of peers in a common format by sending multiple queries to the server.

If one or more request options is included on the command line when <tt>ntpq</tt> is executed, each of the requests will be sent to the NTP servers running on each of the hosts given as command line arguments, or on localhost by default. If no request options are given, <tt>ntpq</tt> will attempt to read commands from the standard input and execute these on the NTP server running on the first host given on the command line, again defaulting to localhost when no other host is specified. <tt>ntpq</tt>will prompt for commands if the standard input is a terminal device.

<tt>ntpq</tt> uses NTP mode 6 packets to communicate with the NTP server, and hence can be used to query any compatible server on the network which permits it. Note that since NTP is a UDP protocol this communication will be somewhat unreliable, especially over large distances in terms of network topology. <tt>ntpq</tt> makes one attempt to retransmit requests, and will time requests out if the remote host is not heard from within a suitable timeout time.

Note that in contexts where a host name is expected, a <tt>-4</tt> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <tt>-6</tt> qualifier forces DNS resolution to the IPv6 namespace.

For examples and usage, see the [NTP Debugging Techniques](/archives/4.2.4-series/debug) page.

Command line options are described following. Specifying a command line option other than <tt>-i</tt> or <tt>-n</tt> will cause the specified query (queries) to be sent to the indicated host(s) immediately. Otherwise, <tt>ntpq</tt> will attempt to read interactive format commands from the standard input.



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

Interactive format commands consist of a keyword followed by zero to four arguments. Only enough characters of the full keyword to uniquely identify the command need be typed. The output of a command is normally sent to the standard output, but optionally the output of individual commands may be sent to a file by appending a <tt>></tt>, followed by a file name, to the command line. A number of interactive format commands are executed entirely within the <tt>ntpq</tt> program itself and do not result in NTP mode 6 requests being sent to a server. These are described following.



<dt><tt>? [_command_keyword_]</tt>  
<tt>helpl [_command_keyword_]</tt></dt>

A <tt>?</tt> by itself will print a list of all the command keywords known to this incarnation of <tt>ntpq</tt>. A <tt>?</tt> followed by a command keyword will print function and usage information about the command. This command is probably a better source of information about <tt>ntpq</tt> than this manual page.

<dt><tt>addvars _variable_name_ [ = _value_] [...]</tt>  
<tt>rmvars _variable_name_ [...]</tt>  
<tt>clearvars</tt></dt>

The data carried by NTP mode 6 messages consists of a list of items of the form <tt>_variable_name_ = _value_</tt>, where the <tt>= _value_</tt> is ignored, and can be omitted, in requests to the server to read variables. <tt>ntpq</tt> maintains an internal list in which data to be included in control messages can be assembled, and sent using the <tt>readlist</tt> and <tt>writelist</tt> commands described below. The <tt>addvars</tt> command allows variables and their optional values to be added to the list. If more than one variable is to be added, the list should be comma-separated and not contain white space. The <tt>rmvars</tt> command can be used to remove individual variables from the list, while the <tt>clearlist</tt> command removes all variables from the list.

<dt><tt>cooked</tt></dt>

Causes output from query commands to be "cooked", so that variables which are recognized by <tt>ntpq</tt> will have their values reformatted for human consumption. Variables which <tt>ntpq</tt> thinks should have a decodable value but didn't are marked with a trailing <tt>?</tt>.

<dt><tt>debug more | less | off</tt></dt>

Turns internal query program debugging on and off.

<dt><tt>delay _milliseconds_</tt></dt>

Specify a time interval to be added to timestamps included in requests which require authentication. This is used to enable (unreliable) server reconfiguration over long delay network paths or between machines whose clocks are unsynchronized. Actually the server does not now require timestamps in authenticated requests, so this command may be obsolete.

<dt><tt>host _hostname_</tt></dt>

Set the host to which future queries will be sent. Hostname may be either a host name or a numeric address.

<dt><tt>hostnames [yes | no]</tt></dt>

If <tt>yes</tt> is specified, host names are printed in information displays. If <tt>no</tt> is specified, numeric addresses are printed instead. The default is <tt>yes</tt>, unless modified using the command line <tt>-n</tt> switch.

<dt><tt>keyid _keyid_</tt></dt>

This command specifies the key number to be used to authenticate configuration requests. This must correspond to a key number the server has been configured to use for this purpose.

<dt><tt>ntpversion 1 | 2 | 3 | 4</tt></dt>

Sets the NTP version number which <tt>ntpq</tt> claims in packets. Defaults to 2, Note that mode 6 control messages (and modes, for that matter) didn't exist in NTP version 1.

<dt><tt>passwd</tt></dt>

This command prompts for a password (which will not be echoed) which will be used to authenticate configuration requests. The password must correspond to the key configured for NTP server for this purpose.

<dt><tt>quit</tt></dt>

Exit <tt>ntpq</tt>.

<dt><tt>raw</tt></dt>

Causes all output from query commands is printed as received from the remote server. The only formating/interpretation done on the data is to transform nonascii data into a printable (but barely understandable) form.

<dt><tt>timeout _millseconds_</tt></dt>

Specify a timeout period for responses to server queries. The default is about 5000 milliseconds. Note that since <tt>ntpq</tt> retries each query once after a timeout, the total waiting time for a timeout will be twice the timeout value set.

* * *

#### Control Message Commands

Each association known to an NTP server has a 16 bit integer association identifier. NTP control messages which carry peer variables must identify the peer the values correspond to by including its association ID. An association ID of 0 is special, and indicates the variables are system variables, whose names are drawn from a separate name space.

Control message commands result in one or more NTP mode 6 messages being sent to the server, and cause the data returned to be printed in some format. Most commands currently implemented send a single message and expect a single response. The current exceptions are the peers command, which will send a preprogrammed series of messages to obtain the data it needs, and the mreadlist and mreadvar commands, which will iterate over a range of associations.

<dt><tt>associations</tt></dt>

Obtains and prints a list of association identifiers and peer statuses for in-spec peers of the server being queried. The list is printed in columns. The first of these is an index numbering the associations from 1 for internal use, the second the actual association identifier returned by the server and the third the status word for the peer. This is followed by a number of columns containing data decoded from the status word. See the peers command for a decode of the <tt>condition</tt> field. Note that the data returned by the <tt>associations</tt> command is cached internally in <tt>ntpq</tt>. The index is then of use when dealing with stupid servers which use association identifiers which are hard for humans to type, in that for any subsequent commands which require an association identifier as an argument, the form &index may be used as an alternative.

<dt><tt>clockvar [_assocID_] [_variable_name_ [ = _value_ [...]] [...]</tt></dt>

<dt><tt>cv [_assocID_] [_variable_name_ [ = _value_ [...] ][...]</tt></dt>

Requests that a list of the server's clock variables be sent. Servers which have a radio clock or other external synchronization will respond positively to this. If the association identifier is omitted or zero the request is for the variables of the <tt>system clock</tt> and will generally get a positive response from all servers with a clock. If the server treats clocks as pseudo-peers, and hence can possibly have more than one clock connected at once, referencing the appropriate peer association ID will show the variables of a particular clock. Omitting the variable list will cause the server to return a default variable display.

<dt><tt>lassociations</tt></dt>

Obtains and prints a list of association identifiers and peer statuses for all associations for which the server is maintaining state. This command differs from the <tt>associations</tt> command only for servers which retain state for out-of-spec client associations (i.e., fuzzballs). Such associations are normally omitted from the display when the <tt>associations</tt> command is used, but are included in the output of <tt>lassociations</tt>.

<dt><tt>lpassociations</tt></dt>

Print data for all associations, including out-of-spec client associations, from the internally cached list of associations. This command differs from <tt>passociations</tt> only when dealing with fuzzballs.

<dt><tt>lpeers</tt></dt>

Like R peers, except a summary of all associations for which the server is maintaining state is printed. This can produce a much longer list of peers from fuzzball servers.

<dt><tt>mreadlist _assocID_ _assocID_</tt>  
<tt>mrl _assocID_ _assocID_</tt></dt>

Like the <tt>readlist</tt> command, except the query is done for each of a range of (nonzero) association IDs. This range is determined from the association list cached by the most recent <tt>associations</tt> command.

<dt><tt>mreadvar _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]</tt>  
<tt>mrv _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]</tt></dt>

Like the <tt>readvar</tt> command, except the query is done for each of a range of (nonzero) association IDs. This range is determined from the association list cached by the most recent <tt>associations</tt> command.

<dt><tt>opeers</tt></dt>

An old form of the <tt>peers</tt> command with the reference ID replaced by the local interface address.

<dt><tt>passociations</tt></dt>

Displays association data concerning in-spec peers from the internally cached list of associations. This command performs identically to the <tt>associations</tt> except that it displays the internally stored data rather than making a new query.

<dt><tt>peers</tt></dt>

Obtains a current list peers of the server, along with a summary of each peer's state. Summary information includes the address of the remote peer, the reference ID (0.0.0.0 if this is unknown), the stratum of the remote peer, the type of the peer (local, unicast, multicast or broadcast), when the last packet was received, the polling interval, in seconds, the reachability register, in octal, and the current estimated delay, offset and dispersion of the peer, all in milliseconds. The character at the left margin of each line shows the synchronization status of the association and is a valuable diagnostic tool. The encoding and meaning of this character, called the tally code, is given later in this page.

<dt><tt>pstatus _assocID_</tt></dt>

Sends a read status request to the server for the given association. The names and values of the peer variables returned will be printed. Note that the status word from the header is displayed preceding the variables, both in hexadecimal and in pidgeon English.

<dt><tt>readlist [ _assocID_ ]</tt>  
<tt>rl [ _assocID_ ]</tt></dt>

Requests that the values of the variables in the internal variable list be returned by the server. If the association ID is omitted or is 0 the variables are assumed to be system variables. Otherwise they are treated as peer variables. If the internal variable list is empty a request is sent without data, which should induce the remote server to return a default display.

<dt><tt>readvar _assocID_ _variable_name_ [ = _value_ ] [ ...]</tt>  
<tt>rv _assocID_ [ _variable_name_ [ = _value_ ] [...]</tt></dt>

Requests that the values of the specified variables be returned by the server by sending a read variables request. If the association ID is omitted or is given as zero the variables are system variables, otherwise they are peer variables and the values returned will be those of the corresponding peer. Omitting the variable list will send a request with no data which should induce the server to return a default display. The encoding and meaning of the variables derived from NTPv3 is given in RFC-1305; the encoding and meaning of the additional NTPv4 variables are given later in this page.

<dt><tt>writevar _assocID_ _variable_name_ [ = _value_ [ ...]</tt></dt>

Like the readvar request, except the specified variables are written instead of read.

<dt><tt>writelist [ _assocID_ ]</tt></dt>

Like the readlist request, except the internal list variables are written instead of read.

* * *

#### Tally Codes

The character in the left margin in the <tt>peers</tt> billboard, called the tally code, shows the fate of each association in the clock selection process. Following is a list of these characters, the pigeon used in the <tt>rv</tt> command, and a short explanation of the condition revealed.

<dt><tt>space reject</tt></dt>

The peer is discarded as unreachable, synchronized to this server (synch loop) or outrageous synchronization distance.

<dt><tt>x  falsetick</tt></dt>

The peer is discarded by the intersection algorithm as a falseticker.

<dt><tt>.  excess</tt></dt>

The peer is discarded as not among the first ten peers sorted by synchronization distance and so is probably a poor candidate for further consideration.

<dt><tt>-  outlyer</tt></dt>

The peer is discarded by the clustering algorithm as an outlyer.

<dt><tt>+  candidat</tt></dt>

The peer is a survivor and a candidate for the combining algorithm.

<dt><tt>#  selected</tt></dt>

The peer is a survivor, but not among the first six peers sorted by synchronization distance. If the association is ephemeral, it may be demobilized to conserve resources.

<dt><tt>*  sys.peer</tt></dt>

The peer has been declared the system peer and lends its variables to the system variables.

<dt><tt>o  pps.peer</tt></dt>

The peer has been declared the system peer and lends its variables to thesystem variables. However, the actual system synchronization is derived from a pulse-per-second (PPS) signal, either indirectly via the PPS reference clock driver or directly via kernel interface.

* * *

#### System Variables

The <tt>status, leap, stratum, precision, rootdelay, rootdispersion, refid, reftime, poll, offset, and frequency</tt> variables are described in RFC-1305 specification. Additional NTPv4 system variables include the following.

<dt><tt>version</tt></dt>

Everything you might need to know about the software version and generation time.

<dt><tt>processor</tt></dt>

The processor and kernel identification string.

<dt><tt>system</tt></dt>

The operating system version and release identifier.

<dt><tt>state</tt></dt>

The state of the clock discipline state machine. The values are described in the architecture briefing on the NTP Project page linked from www.ntp.org.

<dt><tt>peer</tt></dt>

The internal integer used to identify the association currently designated the system peer.

<dt><tt>jitter</tt></dt>

The estimated time error of the system clock measured as an exponential average of RMS time differences.

<dt><tt>stability</tt></dt>

The estimated frequency stability of the system clock measured as an exponential average of RMS frequency differences.

When the NTPv4 daemon is compiled with the OpenSSL software library, additional system variables are displayed, including some or all of the following, depending on the particular dance:

<dt><tt>flags</tt></dt>

The current flags word bits and message digest algorithm identifier (NID) in hex format. The high order 16 bits of the four-byte word contain the NID from the OpenSSL ligrary, while the low-order bits are interpreted as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x01</tt>

&nbsp;&nbsp;&nbsp;&nbsp;autokey enabled

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x02</tt>

&nbsp;&nbsp;&nbsp;&nbsp;NIST leapseconds file loaded

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x10</tt>

&nbsp;&nbsp;&nbsp;&nbsp;PC identity scheme

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x20</tt>

&nbsp;&nbsp;&nbsp;&nbsp;IFF identity scheme

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x40</tt>

&nbsp;&nbsp;&nbsp;&nbsp;GQ identity scheme

<dt><tt>hostname</tt></dt>

The name of the host as returned by the Unix <tt>gethostname()</tt> library function.

<dt><tt>hostkey</tt></dt>

The NTP filestamp of the host key file.

<dt><tt>cert</tt></dt>

A list of certificates held by the host. Each entry includes the subject, issuer, flags and NTP filestamp in order. The bits are interpreted as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x01</tt>

&nbsp;&nbsp;&nbsp;&nbsp;certificate has been signed by the server

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x02</tt>

&nbsp;&nbsp;&nbsp;&nbsp;certificate is trusted

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x04</tt>

&nbsp;&nbsp;&nbsp;&nbsp;certificate is private

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x08</tt>

&nbsp;&nbsp;&nbsp;&nbsp;certificate contains errors and should not be trusted

<dt><tt>leapseconds</tt></dt>

The NTP filestamp of the NIST leapseconds file.

<dt><tt>refresh</tt></dt>

The NTP timestamp when the host public cryptographic values were refreshed and signed.

<dt><tt>signature</tt></dt>

The host digest/signature scheme name from the OpenSSL library.

<dt><tt>tai</tt></dt>

The TAI-UTC offset in seconds obtained from the NIST leapseconds table.

* * *

#### Peer Variables

The <tt>status, srcadr, srcport, dstadr, dstport, leap, stratum, precision, rootdelay, rootdispersion, readh, hmode, pmode, hpoll, ppoll, offset, delay, dspersion, reftime</tt> variables are described in the RFC-1305 specification, as are the timestamps <tt>org, rec and xmt</tt>. Additional NTPv4 system variables include the following.

<dt><tt>flash</tt></dt>

The flash code for the most recent packet received. The encoding and meaning of these codes is given later in this page.

<dt><tt>jitter</tt></dt>

The estimated time error of the peer clock measured as an exponential average of RMS time differences.

<dt><tt>unreach</tt></dt>

The value of the counter which records the number of poll intervals since the last valid packet was received.



When the NTPv4 daemon is compiled with the OpenSSL software library, additional peer variables are displayed, including the following:



<dt><tt>flags</tt></dt>

The current flag bits. This word is the server host status word with additional bits used by the Autokey state machine. See the source code for the bit encoding.

<dt><tt>hostname</tt></dt>

The server host name.

<dt><tt>initkey _key_</tt></dt>

The initial key used by the key list generator in the Autokey protocol.

<dt><tt>initsequence _index_</tt></dt>

The initial index used by the key list generator in the Autokey protocol.

<dt><tt>signature</tt></dt>

The server message digest/signature scheme name from the OpenSSL software library.

<dt><tt>timestamp _time_</tt></dt>

The NTP timestamp when the last Autokey key list was generated and signed.

* * *

#### Flash Codes

The <tt>flash</tt> code is a valuable debugging aid displayed in the peer variables list. It shows the results of the original sanity checks defined in the NTP specification RFC-1305 and additional ones added in NTPv4. There are 12 tests designated <tt>TEST1</tt> through <tt>TEST12</tt>. The tests are performed in a certain order designed to gain maximum diagnostic information while protecting against accidental or malicious errors. The <tt>flash</tt> variable is initialized to zero as each packet is received. If after each set of tests one or more bits are set, the packet is discarded.

Tests <tt>TEST1</tt> through <tt>TEST3</tt> check the packet timestamps from which the offset and delay are calculated. If any bits are set, the packet is discarded; otherwise, the packet header variables are saved. <tt>TEST4</tt> and <tt>TEST5</tt> are associated with access control and cryptographic authentication. If any bits are set, the packet is discarded immediately with nothing changed.

Tests <tt>TEST6</tt> through <tt>TEST8</tt> check the health of the server. If any bits are set, the packet is discarded; otherwise, the offset and delay relative to the server are calculated and saved. <tt>TEST9</tt> checks the health of the association itself. If any bits are set, the packet is discarded; otherwise, the saved variables are passed to the clock filter and mitigation algorithms.

Tests <tt>TEST10</tt> through <tt>TEST12</tt> check the authentication state using Autokey public-key cryptography, as described in the [Authentication Options](/archives/4.2.4-series/authopt) page. If any bits are set and the association has previously been marked reachable, the packet is discarded; otherwise, the originate and receive timestamps are saved, as required by the NTP protocol, and processing continues.

The <tt>flash</tt> bits for each test are defined as follows.

<dt><tt>0x001 TEST1</tt></dt>

Duplicate packet. The packet is at best a casual retransmission and at worst a malicious replay.

<dt><tt>0x002 TEST2</tt></dt>

Bogus packet. The packet is not a reply to a message previously sent. This can happen when the NTP daemon is restarted and before somebody else notices.

<dt><tt>0x004 TEST3</tt></dt>

Unsynchronized. One or more timestamp fields are invalid. This normally happens when the first packet from a peer is received.

<dt><tt>0x008 TEST4</tt></dt>

Access is denied. See the [Access Control Options](/archives/4.2.4-series/accopt) page.

<dt><tt>0x010 TEST5</tt></dt>

Cryptographic authentication fails. See the [Authentication Options](/archives/4.2.4-series/authopt) page.

<dt><tt>0x020TEST6</tt></dt>

The server is unsynchronized. Wind up its clock first.

<dt><tt>0x040 TEST7</tt></dt>

The server stratum is at the maximum than 15. It is probably unsynchronized and its clock needs to be wound up.

<dt><tt>0x080 TEST8</tt></dt>

Either the root delay or dispersion is greater than one second, which is highly unlikely unless the peer is unsynchronized to Mars.

<dt><tt>0x100 TEST9</tt></dt>

Either the peer delay or dispersion is greater than one second, which is highly unlikely unless the peer is on Mars.

<dt><tt>0x200 TEST10</tt></dt>

The autokey protocol has detected an authentication failure. See the [Authentication Options](/archives/4.2.4-series/authopt) page.

<dt><tt>0x400 TEST11</tt></dt>

The autokey protocol has not verified the server or peer is proventic and has valid public key credentials. See the [Authentication Options](/archives/4.2.4-series/authopt) page.

<dt><tt>0x800 TEST12</tt></dt>

A protocol or configuration error has occurred in the public key algorithms or a possible intrusion event has been detected. See the [Authentication Options](/archives/4.2.4-series/authopt) page.

* * *

#### Bugs

The peers command is non-atomic and may occasionally result in spurious error messages about invalid associations occurring and terminating the command. The timeout time is a fixed constant, which means you wait a long time for timeouts since it assumes sort of a worst case. The program should improve the timeout estimate as it sends queries to a particular host, but doesn't.