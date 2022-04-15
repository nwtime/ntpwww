---
title: "ntpq - standard NTP query program"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/bustardfly.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

A typical NTP monitoring packet

* * *

#### Table of Contents

*   [Synopsis](/documentation/4.2.2-series/ntpq/#synopsis)
*   [Description](/documentation/4.2.2-series/ntpq/#description)
*   [Internal Commands](/documentation/4.2.2-series/ntpq/#internal-commands)
*   [Control Message Commands](/documentation/4.2.2-series/ntpq/#control-message-commands)
*   [Tally Codes](/documentation/4.2.2-series/ntpq/#tally-codes)
*   [System Variables](/documentation/4.2.2-series/ntpq/#system-variables)
*   [Peer Variables](/documentation/4.2.2-series/ntpq/#peer-variables)
*   [Flash Codes](/documentation/4.2.2-series/ntpq/#flash-codes)
*   [Bugs](/documentation/4.2.2-series/ntpq/#bugs)

* * *

#### Synopsis

<code>ntpq [-inp] [-c _command_] [_host_] [...]</code>

* * *

#### Description

The <code>ntpq</code> utility program is used to monitor NTP daemon <code>ntpd</code> operations and determine performance. It uses the standard NTP mode 6 control message formats defined in Appendix B of the NTPv3 specification RFC1305. The same formats are used in NTPv4, although some of the variables have changed and new ones added. The description on this page is for the NTPv4 variables.

The program can be run either in interactive mode or controlled using command line arguments. Requests to read and write arbitrary variables can be assembled, with raw and pretty-printed output options being available. The <code>ntpq</code> can also obtain and print a list of peers in a common format by sending multiple queries to the server.

If one or more request options is included on the command line when <code>ntpq</code> is executed, each of the requests will be sent to the NTP servers running on each of the hosts given as command line arguments, or on localhost by default. If no request options are given, <code>ntpq</code> will attempt to read commands from the standard input and execute these on the NTP server running on the first host given on the command line, again defaulting to localhost when no other host is specified. <code>ntpq</code>will prompt for commands if the standard input is a terminal device.

<code>ntpq</code> uses NTP mode 6 packets to communicate with the NTP server, and hence can be used to query any compatible server on the network which permits it. Note that since NTP is a UDP protocol this communication will be somewhat unreliable, especially over large distances in terms of network topology. <code>ntpq</code> makes one attempt to retransmit requests, and will time requests out if the remote host is not heard from within a suitable timeout time.

Note that in contexts where a host name is expected, a <code>-4</code> qualifier preceding the host name forces DNS resolution to the IPv4 namespace, while a <code>-6</code> qualifier forces DNS resolution to the IPv6 namespace.

For examples and usage, see the [NTP Debugging Techniques](/documentation/4.2.2-series/debug/) page.

Command line options are described following. Specifying a command line option other than <code>-i</code> or <code>-n</code> will cause the specified query (queries) to be sent to the indicated host(s) immediately. Otherwise, <code>ntpq</code> will attempt to read interactive format commands from the standard input.

<code>**-4**</code>

: Force DNS resolution of following host names on the command line to the IPv4 namespace.

<code>**-6**</code>

: Force DNS resolution of following host names on the command line to the IPv6 namespace.

<code>**-c**</code>

: The following argument is interpreted as an interactive format command and is added to the list of commands to be executed on the specified host(s). Multiple <code>-c</code> options may be given.

<code>**-d**</code>

: Turn on debugging mode.

<code>**-i**</code>

: Force <code>ntpq</code> to operate in interactive mode. Prompts will be written to the standard output and commands read from the standard input.

<code>**-n**</code>

: Output all host addresses in dotted-quad numeric format rather than converting to the canonical host names.

<code>**-p**</code>

: Print a list of the peers known to the server as well as a summary of their state. This is equivalent to the <code>peers</code> interactive command.

* * *

#### Internal Commands

Interactive format commands consist of a keyword followed by zero to four arguments. Only enough characters of the full keyword to uniquely identify the command need be typed. The output of a command is normally sent to the standard output, but optionally the output of individual commands may be sent to a file by appending a <code>></code>, followed by a file name, to the command line. A number of interactive format commands are executed entirely within the <code>ntpq</code> program itself and do not result in NTP mode 6 requests being sent to a server. These are described following.

<code>**? [_command_keyword_]**</code>  
: <code>**help [_command_keyword_]**</code>

: A <code>?</code> by itself will print a list of all the command keywords known to this incarnation of <code>ntpq</code>. A <code>?</code> followed by a command keyword will print function and usage information about the command. This command is probably a better source of information about <code>ntpq</code> than this manual page.

<code>**addvars _variable_name_ [ = _value_] [...]**</code>  
: <code>**rmvars _variable_name_ [...]**</code>  
: <code>**clearvars**</code>

: The data carried by NTP mode 6 messages consists of a list of items of the form <code>_variable_name_ = _value_</code>, where the <code>= _value_</code> is ignored, and can be omitted, in requests to the server to read variables. <code>ntpq</code> maintains an internal list in which data to be included in control messages can be assembled, and sent using the <code>readlist</code> and <code>writelist</code> commands described below. The <code>addvars</code> command allows variables and their optional values to be added to the list. If more than one variable is to be added, the list should be comma-separated and not contain white space. The <code>rmvars</code> command can be used to remove individual variables from the list, while the <code>clearlist</code> command removes all variables from the list.

<code>**cooked**</code>

: Causes output from query commands to be "cooked", so that variables which are recognized by <code>ntpq</code> will have their values reformatted for human consumption. Variables which <code>ntpq</code> thinks should have a decodable value but didn't are marked with a trailing <code>?</code>.

<code>**debug more | less | off**</code>

: Turns internal query program debugging on and off.

<code>**delay _milliseconds_**</code>

: Specify a time interval to be added to timestamps included in requests which require authentication. This is used to enable (unreliable) server reconfiguration over long delay network paths or between machines whose clocks are unsynchronized. Actually the server does not now require timestamps in authenticated requests, so this command may be obsolete.

<code>**host _hostname_**</code>

: Set the host to which future queries will be sent. Hostname may be either a host name or a numeric address.

<code>**hostnames [yes | no]**</code>

: If <code>yes</code> is specified, host names are printed in information displays. If <code>no</code> is specified, numeric addresses are printed instead. The default is <code>yes</code>, unless modified using the command line <code>-n</code> switch.

<code>**keyid _keyid_**</code>

: This command specifies the key number to be used to authenticate configuration requests. This must correspond to a key number the server has been configured to use for this purpose.

<code>**ntpversion 1 | 2 | 3 | 4**</code>

: Sets the NTP version number which <code>ntpq</code> claims in packets. Defaults to 2, Note that mode 6 control messages (and modes, for that matter) didn't exist in NTP version 1.

<code>**passwd**</code>

: This command prompts for a password (which will not be echoed) which will be used to authenticate configuration requests. The password must correspond to the key configured for NTP server for this purpose.

<code>**quit**</code>

: Exit <code>ntpq</code>.

<code>**raw**</code>

: Causes all output from query commands is printed as received from the remote server. The only formating/interpretation done on the data is to transform nonascii data into a printable (but barely understandable) form.

<code>**timeout _millseconds_**</code>

: Specify a timeout period for responses to server queries. The default is about 5000 milliseconds. Note that since <code>ntpq</code> retries each query once after a timeout, the total waiting time for a timeout will be twice the timeout value set.

* * *

#### Control Message Commands

Each association known to an NTP server has a 16 bit integer association identifier. NTP control messages which carry peer variables must identify the peer the values correspond to by including its association ID. An association ID of 0 is special, and indicates the variables are system variables, whose names are drawn from a separate name space.

Control message commands result in one or more NTP mode 6 messages being sent to the server, and cause the data returned to be printed in some format. Most commands currently implemented send a single message and expect a single response. The current exceptions are the peers command, which will send a preprogrammed series of messages to obtain the data it needs, and the mreadlist and mreadvar commands, which will iterate over a range of associations.

<code>**associations**</code>

: Obtains and prints a list of association identifiers and peer statuses for in-spec peers of the server being queried. The list is printed in columns. The first of these is an index numbering the associations from 1 for internal use, the second the actual association identifier returned by the server and the third the status word for the peer. This is followed by a number of columns containing data decoded from the status word. See the peers command for a decode of the <code>condition</code> field. Note that the data returned by the <code>associations</code> command is cached internally in <code>ntpq</code>. The index is then of use when dealing with stupid servers which use association identifiers which are hard for humans to type, in that for any subsequent commands which require an association identifier as an argument, the form &index may be used as an alternative.

<code>**clockvar [_assocID_] [_variable_name_ [ = _value_ [...]] [...]**</code>
: <code>**cv [_assocID_] [_variable_name_ [ = _value_ [...] ][...]**</code>

: Requests that a list of the server's clock variables be sent. Servers which have a radio clock or other external synchronization will respond positively to this. If the association identifier is omitted or zero the request is for the variables of the <code>system clock</code> and will generally get a positive response from all servers with a clock. If the server treats clocks as pseudo-peers, and hence can possibly have more than one clock connected at once, referencing the appropriate peer association ID will show the variables of a particular clock. Omitting the variable list will cause the server to return a default variable display.

<code>**lassociations**</code>

: Obtains and prints a list of association identifiers and peer statuses for all associations for which the server is maintaining state. This command differs from the <code>associations</code> command only for servers which retain state for out-of-spec client associations (i.e., fuzzballs). Such associations are normally omitted from the display when the <code>associations</code> command is used, but are included in the output of <code>lassociations</code>.

<code>**lpassociations**</code>

: Print data for all associations, including out-of-spec client associations, from the internally cached list of associations. This command differs from <code>passociations</code> only when dealing with fuzzballs.

<code>**lpeers**</code>

: Like R peers, except a summary of all associations for which the server is maintaining state is printed. This can produce a much longer list of peers from fuzzball servers.

<code>**mreadlist _assocID_ _assocID_**</code>  
: <code>**mrl _assocID_ _assocID_**</code>

: Like the <code>readlist</code> command, except the query is done for each of a range of (nonzero) association IDs. This range is determined from the association list cached by the most recent <code>associations</code> command.

<code>**mreadvar _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]**</code>  
: <code>**mrv _assocID_ _assocID_ [ _variable_name_ [ = _value_[ ... ]**</code>

: Like the <code>readvar</code> command, except the query is done for each of a range of (nonzero) association IDs. This range is determined from the association list cached by the most recent <code>associations</code> command.

<code>**opeers**</code>

: An old form of the <code>peers</code> command with the reference ID replaced by the local interface address.

<code>**passociations**</code>

: Displays association data concerning in-spec peers from the internally cached list of associations. This command performs identically to the <code>associations</code> except that it displays the internally stored data rather than making a new query.

<code>**peers**</code>

: Obtains a current list peers of the server, along with a summary of each peer's state. Summary information includes the address of the remote peer, the reference ID (`0.0.0.0` if this is unknown), the stratum of the remote peer, the type of the peer (local, unicast, multicast or broadcast), when the last packet was received, the polling interval, in seconds, the reachability register, in octal, and the current estimated delay, offset and dispersion of the peer, all in milliseconds. The character at the left margin of each line shows the synchronization status of the association and is a valuable diagnostic tool. The encoding and meaning of this character, called the tally code, is given later in this page.

<code>**pstatus _assocID_**</code>

: Sends a read status request to the server for the given association. The names and values of the peer variables returned will be printed. Note that the status word from the header is displayed preceding the variables, both in hexadecimal and in pidgeon English.

<code>**readlist [ _assocID_ ]**</code>  
: <code>**rl [ _assocID_ ]**</code>

: Requests that the values of the variables in the internal variable list be returned by the server. If the association ID is omitted or is 0 the variables are assumed to be system variables. Otherwise they are treated as peer variables. If the internal variable list is empty a request is sent without data, which should induce the remote server to return a default display.

<code>**readvar _assocID_ _variable_name_ [ = _value_ ] [ ...]**</code>  
: <code>**rv _assocID_ [ _variable_name_ [ = _value_ ] [...]**</code>

: Requests that the values of the specified variables be returned by the server by sending a read variables request. If the association ID is omitted or is given as zero the variables are system variables, otherwise they are peer variables and the values returned will be those of the corresponding peer. Omitting the variable list will send a request with no data which should induce the server to return a default display. The encoding and meaning of the variables derived from NTPv3 is given in RFC-1305; the encoding and meaning of the additional NTPv4 variables are given later in this page.

<code>**writevar _assocID_ _variable_name_ [ = _value_ [ ...]**</code>

: Like the <code>readvar</code> request, except the specified variables are written instead of read.

<code>**writelist [ _assocID_ ]**</code>

Like the <code>readlist</code> request, except the internal list variables are written instead of read.

* * *

#### Tally Codes

The character in the left margin in the <code>peers</code> billboard, called the tally code, shows the fate of each association in the clock selection process. Following is a list of these characters, the pigeon used in the <code>rv</code> command, and a short explanation of the condition revealed.

<code>**space reject**</code>

: The peer is discarded as unreachable, synchronized to this server (synch loop) or outrageous synchronization distance.

<code>**x  falsetick**</code>

: The peer is discarded by the intersection algorithm as a falseticker.

<code>**.  excess**</code>

: The peer is discarded as not among the first ten peers sorted by synchronization distance and so is probably a poor candidate for further consideration.

<code>**-  outlyer**</code>

: The peer is discarded by the clustering algorithm as an outlyer.

<code>**+  candidat**</code>

: The peer is a survivor and a candidate for the combining algorithm.

<code>**#  selected**</code>

: The peer is a survivor, but not among the first six peers sorted by synchronization distance. If the association is ephemeral, it may be demobilized to conserve resources.

<code>**\*  sys.peer**</code>

: The peer has been declared the system peer and lends its variables to the system variables.

<code>**o  pps.peer**</code>

: The peer has been declared the system peer and lends its variables to thesystem variables. However, the actual system synchronization is derived from a pulse-per-second (PPS) signal, either indirectly via the PPS reference clock driver or directly via kernel interface.

* * *

#### System Variables

The <code>status, leap, stratum, precision, rootdelay, rootdispersion, refid, reftime, poll, offset</code>, and <code>frequency</code> variables are described in RFC-1305 specification. Additional NTPv4 system variables include the following.

<code>**version**</code>

: Everything you might need to know about the software version and generation time.

<code>**processor**</code>

: The processor and kernel identification string.

<code>**system**</code>

: The operating system version and release identifier.

<code>**state**</code>

: The state of the clock discipline state machine. The values are described in the [architecture briefing](/reflib/brief/clock/clock.pdf).

<code>**peer**</code>

: The internal integer used to identify the association currently designated the system peer.

<code>**jitter**</code>

: The estimated time error of the system clock measured as an exponential average of RMS time differences.

<code>**stability**</code>

: The estimated frequency stability of the system clock measured as an exponential average of RMS frequency differences.

When the NTPv4 daemon is compiled with the OpenSSL software library, additional system variables are displayed, including some or all of the following, depending on the particular dance:

<code>**flags**</code>

The current flags word bits and message digest algorithm identifier (NID) in hex format. The high order 16 bits of the four-byte word contain the NID from the OpenSSL ligrary, while the low-order bits are interpreted as follows:

| Bit | Description |
| ----- | ----- |
| `0x01` | autokey enabled |
| `0x02` | NIST leapseconds file loaded |
| `0x10` | PC identity scheme |
| `0x20` | IFF identity scheme |
| `0x40` | GQ identity scheme |

<code>**hostname**</code>

: The name of the host as returned by the Unix <code>gethostname()</code> library function.

<code>**hostkey**</code>

: The NTP filestamp of the host key file.

<code>**cert**</code>

: A list of certificates held by the host. Each entry includes the subject, issuer, flags and NTP filestamp in order. The bits are interpreted as follows:

| Bit | Description |
| ----- | ----- |
| `0x01` | certificate has been signed by the server |
| `0x02` | certificate is trusted |
| `0x04` | certificate is private |
| `0x08` | certificate contains errors and should not be trusted |

<code>**leapseconds**</code>

: The NTP filestamp of the NIST leapseconds file.

<code>**refresh**</code>

: The NTP timestamp when the host public cryptographic values were refreshed and signed.

<code>**signature**</code>

: The host digest/signature scheme name from the OpenSSL library.

<code>**tai**</code>

: The TAI-UTC offset in seconds obtained from the NIST leapseconds table.

* * *

#### Peer Variables

The <code>status, srcadr, srcport, dstadr, dstport, leap, stratum, precision, rootdelay, rootdispersion, readh, hmode, pmode, hpoll, ppoll, offset, delay, dspersion</code>, and <code>reftime</code> variables are described in the RFC-1305 specification, as are the timestamps <code>org, rec</code> and <code>xmt</code>. Additional NTPv4 system variables include the following.

<code>**flash**</code>

: The flash code for the most recent packet received. The encoding and meaning of these codes is given later in this page.

<code>**jitter**</code>

: The estimated time error of the peer clock measured as an exponential average of RMS time differences.

<code>**unreach**</code>

: The value of the counter which records the number of poll intervals since the last valid packet was received.

When the NTPv4 daemon is compiled with the OpenSSL software library, additional peer variables are displayed, including the following:

<code>**flags**</code>

: The current flag bits. This word is the server host status word with additional bits used by the Autokey state machine. See the source code for the bit encoding.

<code>**hostname**</code>

: The server host name.

<code>**initkey _key_**</code>

: The initial key used by the key list generator in the Autokey protocol.

<code>**initsequence _index_**</code>

: The initial index used by the key list generator in the Autokey protocol.

<code>**signature**</code>

: The server message digest/signature scheme name from the OpenSSL software library.

<code>**timestamp _time_**</code>

: The NTP timestamp when the last Autokey key list was generated and signed.

* * *

#### Flash Codes

The <code>flash</code> code is a valuable debugging aid displayed in the peer variables list. It shows the results of the original sanity checks defined in the NTP specification RFC-1305 and additional ones added in NTPv4. There are 12 tests designated <code>TEST1</code> through <code>TEST12</code>. The tests are performed in a certain order designed to gain maximum diagnostic information while protecting against accidental or malicious errors. The <code>flash</code> variable is initialized to zero as each packet is received. If after each set of tests one or more bits are set, the packet is discarded.

Tests <code>TEST1</code> through <code>TEST3</code> check the packet timestamps from which the offset and delay are calculated. If any bits are set, the packet is discarded; otherwise, the packet header variables are saved. <code>TEST4</code> and <code>TEST5</code> are associated with access control and cryptographic authentication. If any bits are set, the packet is discarded immediately with nothing changed.

Tests <code>TEST6</code> through <code>TEST8</code> check the health of the server. If any bits are set, the packet is discarded; otherwise, the offset and delay relative to the server are calculated and saved. <code>TEST9</code> checks the health of the association itself. If any bits are set, the packet is discarded; otherwise, the saved variables are passed to the clock filter and mitigation algorithms.

Tests <code>TEST10</code> through <code>TEST12</code> check the authentication state using Autokey public-key cryptography, as described in the [Authentication Options](/documentation/4.2.2-series/authopt/) page. If any bits are set and the association has previously been marked reachable, the packet is discarded; otherwise, the originate and receive timestamps are saved, as required by the NTP protocol, and processing continues.

The <code>flash</code> bits for each test are defined as follows.

<code>**0x001 TEST1**</code>

: Duplicate packet. The packet is at best a casual retransmission and at worst a malicious replay.

<code>**0x002 TEST2**</code>

: Bogus packet. The packet is not a reply to a message previously sent. This can happen when the NTP daemon is restarted and before somebody else notices.

<code>**0x004 TEST3**</code>

: Unsynchronized. One or more timestamp fields are invalid. This normally happens when the first packet from a peer is received.

<code>**0x008 TEST4**</code>

: Access is denied. See the [Access Control Options](/documentation/4.2.2-series/accopt/) page.

<code>**0x010 TEST5**</code>

: Cryptographic authentication fails. See the [Authentication Options](/documentation/4.2.2-series/authopt/) page.

<code>**0x020TEST6**</code>

: The server is unsynchronized. Wind up its clock first.

<code>**0x040 TEST7**</code>

: The server stratum is at the maximum than 15. It is probably unsynchronized and its clock needs to be wound up.

<code>**0x080 TEST8**</code>

: Either the root delay or dispersion is greater than one second, which is highly unlikely unless the peer is unsynchronized to Mars.

<code>**0x100 TEST9**</code>

: Either the peer delay or dispersion is greater than one second, which is highly unlikely unless the peer is on Mars.

<code>**0x200 TEST10**</code>

: The autokey protocol has detected an authentication failure. See the [Authentication Options](/documentation/4.2.2-series/authopt/) page.

<code>**0x400 TEST11**</code>

: The autokey protocol has not verified the server or peer is proventic and has valid public key credentials. See the [Authentication Options](/documentation/4.2.2-series/authopt/) page.

<code>**0x800 TEST12**</code>

: A protocol or configuration error has occurred in the public key algorithms or a possible intrusion event has been detected. See the [Authentication Options](/documentation/4.2.2-series/authopt/) page.

* * *

#### Bugs

The peers command is non-atomic and may occasionally result in spurious error messages about invalid associations occurring and terminating the command. The timeout time is a fixed constant, which means you wait a long time for timeouts since it assumes sort of a worst case. The program should improve the timeout estimate as it sends queries to a particular host, but doesn't.