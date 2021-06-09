---
title: "ntpq - standard NTP query program"
type: archives
---

![gif](/archives/pic/bustardfly.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

A typical NTP monitoring packet

* * *

#### Table of Contents

*   [Synopsis](/archives/4.1.1/ntpq/#synopsis)
*   [Description](/archives/4.1.1/ntpq/#description)
*   [Internal Commands](/archives/4.1.1/ntpq/#internal-commands)
*   [Control Message Commands](/archives/4.1.1/ntpq/#control-message-commands)
*   [Bugs](/archives/4.1.1/ntpq/#bugs)

* * *

#### Synopsis

<tt>ntpq [-inp] [-c _command_] [_host_] [...]</tt>

* * *

#### Description

The <tt>ntpq</tt> utility program is used to query NTP servers which implement the recommended NTP mode 6 control message format about current state and to request changes in that state. The program may be run either in interactive mode or controlled using command line arguments. Requests to read and write arbitrary variables can be assembled, with raw and pretty-printed output options being available. <tt>ntpq</tt> can also obtain and print a list of peers in a common format by sending multiple queries to the server. 

If one or more request options is included on the command line when <tt>ntpq</tt> is executed, each of the requests will be sent to the NTP servers running on each of the hosts given as command line arguments, or on localhost by default. If no request options are given, <tt>ntpq</tt> will attempt to read commands from the standard input and execute these on the NTP server running on the first host given on the command line, again defaulting to localhost when no other host is specified. <tt>ntpq</tt> will prompt for commands if the standard input is a terminal device.

<tt>ntpq</tt> uses NTP mode 6 packets to communicate with the NTP server, and hence can be used to query any compatible server on the network which permits it. Note that since NTP is a UDP protocol this communication will be somewhat unreliable, especially over large distances in terms of network topology. <tt>ntpq</tt> makes one attempt to retransmit requests, and will time requests out if the remote host is not heard from within a suitable timeout time.

For examples and usage, see the [NTP Debugging Techniques](/archives/4.1.1/debug) page.

Command line options are described following. Specifying a command line option other than <tt>-i</tt> or <tt>-n</tt> will cause the specified query (queries) to be sent to the indicated host(s) immediately. Otherwise, <tt>ntpq</tt> will attempt to read interactive format commands from the standard input.

<dt><tt>-c</tt></dt>

The following argument is interpreted as an interactive format command and is added to the list of commands to be executed on the specified host(s). Multiple <tt>-c</tt> options may be given.

<dt><tt>-i</tt></dt>

Force <tt>ntpq</tt> to operate in interactive mode. Prompts will be written to the standard output and commands read from the standard input.

<dt><tt>-n</tt></dt>

Output all host addresses in dotted-quad numeric format rather than converting to the canonical host names.

<dt><tt>-p</tt></dt>

Print a list of the peers known to the server as well as a summary of their state. This is equivalent to the <tt>peers</tt> interactive command.

* * *

#### Internal Commands

Interactive format commands consist of a keyword followed by zero to four arguments. Only enough characters of the full keyword to uniquely identify the command need be typed. The output of a command is normally sent to the standard output, but optionally the output of individual commands may be sent to a file by appending a `<`, followed by a file name, to the command line. A number of interactive format commands are executed entirely within the <tt>ntpq</tt> program itself and do not result in NTP mode 6 requests being sent to a server. These are described following.

<dt><tt>? [_command_keyword_]</tt>  
<tt>help [_command_keyword_]</tt></dt>

A <tt>?</tt> by itself will print a list of all the command keywords known to this incarnation of <tt>ntpq</tt>. A <tt>?</tt> followed by a command keyword will print function and usage information about the command. This command is probably a better source of information about <tt>ntpq</tt> than this manual page.

<dt><tt>addvars _variable_name_ [ = _value_] [...]</tt>  
<tt>rmvars _variable_name_ [...]</tt>  
<tt>clearvars</tt></dt>

The data carried by NTP mode 6 messages consists of a list of items of the form <tt>_variable_name_ = _value_</tt>, where the <tt>= _value_</tt> is ignored, and can be omitted, in requests to the server to read variables. <tt>ntpq</tt> maintains an internal list in which data to be included in control messages can be assembled, and sent using the <tt>readlist</tt> and <tt>writelist</tt> commands described below. The <tt>addvars</tt> command allows variables and their optional values to be added to the list. If more than one variable is to be added, the list should be comma-separated and not contain white space. The <tt>rmvars</tt> command can be used to remove individual variables from the list, while the <tt>clearlist</tt> command removes all variables from the list.

<dt><tt>authenticate yes | no</tt></dt>

Normally <tt>ntpq</tt> does not authenticate requests unless they are write requests. The command <tt>authenticate yes</tt> causes <tt>ntpq</tt> to send authentication with all requests it makes. Authenticated requests causes some servers to handle requests slightly differently, and can occasionally melt the CPU in fuzzballs if you turn authentication on before doing a <tt>peer</tt> display. 

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

This command allows the specification of a key number to be used to authenticate configuration requests. This must correspond to a key number the server has been configured to use for this purpose.

<dt><tt>ntpversion 1 | 2 | 3 | 4</tt></dt>

Sets the NTP version number which <tt>ntpq</tt> claims in packets. Defaults to 3. Note that mode 6 control messages (and modes, for that matter) didn't exist in NTP version 1. There appear to be no servers left which demand version 1.

<dt><tt>quit</tt></dt>

Exit <tt>ntpq</tt>.

<dt><tt>passwd</tt></dt>

This command prompts you to type in a password (which will not be echoed) which will be used to authenticate configuration requests. The password must correspond to the key configured for use by the NTP server for this purpose if such requests are to be successful.

<dt><tt>raw</tt></dt>

Causes all output from query commands is printed as received from the remote server. The only formating/interpretation done on the data is to transform nonascii data into a printable (but barely understandable) form.

<dt><tt>timeout _millseconds_</tt></dt>

Specify a timeout period for responses to server queries. The default is about 5000 milliseconds. Note that since <tt>ntpq</tt> retries each query once after a timeout, the total waiting time for a timeout will be twice the timeout value set.

* * *

#### Control Message Commands

Each peer known to an NTP server has a 16 bit integer association identifier assigned to it. NTP control messages which carry peer variables must identify the peer the values correspond to by including its association ID. An association ID of 0 is special, and indicates the variables are system variables, whose names are drawn from a separate name space. 

Control message commands result in one or more NTP mode 6 messages being sent to the server, and cause the data returned to be printed in some format. Most commands currently implemented send a single message and expect a single response. The current exceptions are the peers command, which will send a preprogrammed series of messages to obtain the data it needs, and the mreadlist and mreadvar commands, which will iterate over a range of associations.

<dt><tt>associations</tt></dt>

Obtains and prints a list of association identifiers and peer statuses for in-spec peers of the server being queried. The list is printed in columns. The first of these is an index numbering the associations from 1 for internal use, the second the actual association identifier returned by the server and the third the status word for the peer. This is followed by a number of columns containing data decoded from the status word. See the peers command for a decode of the <tt>condition</tt> field. Note that the data returned by the <tt>associations</tt> command is cached internally in <tt>ntpq</tt>. The index is then of use when dealing with stupid servers which use association identifiers which are hard for humans to type, in that for any subsequent commands which require an association identifier as an argument, the form and index may be used as an alternative.

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

Obtains a current list peers of the server, along with a summary of each peer's state. Summary information includes the address of the remote peer, the reference ID (0.0.0.0 if this is unknown), the stratum of the remote peer, the type of the peer (local, unicast, multicast or broadcast), when the last packet was received, the polling interval, in seconds, the reachability register, in octal, and the current estimated delay, offset and dispersion of the peer, all in milliseconds. 

The character in the left margin indicates the fate of this peer in the clock selection process. Following is a list of these characters, the pigeon used in the <tt>rv</tt> command, and a short explanation of the condition revealed.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>space reject</tt></dt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is discarded as unreachable, synchronized to this server (synch loop) or outrageous synchronization distance.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>x  falsetick</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is discarded by the intersection algorithm as a falseticker.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>.  excess</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is discarded as not among the first ten peers sorted by synchronization distance and so is probably a poor candidate for further consideration.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>-  outlyer</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is discarded by the clustering algorithm as an outlyer.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>+  candidat</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is a survivor and a candidate for the combining algorithm.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>#  selected</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer is a survivor, but not among the first six peers sorted by synchronization distance. If the association is ephemeral, it may be demobilized to conserve resources.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>*  sys.peer</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer has been declared the system peer and lends its variables to the system variables.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>o  pps.peer</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The peer has been declared the system peer and lends its variables to thesystem variables. However, the actual system synchronization is derived from a pulse-per-second (PPS) signal, either indirectly via the PPS reference clock driver or directly via kernel interface.

The <tt>flash</tt> variable is a valuable debugging aid. It displays the results of the original sanity checks defined in the NTP specification RFC-1305 and additional ones added in NTP Version 4. There are eleven tests called <tt>TEST1</tt> through <tt>TEST11</tt>. The tests are performed in a certain order designed to gain maximum diagnostic information while protecting against accidental or malicious errors. The <tt>flash</tt> variable is first initialized to zero. If after each set of tests one or more bits are set, the packet is discarded.

Tests <tt>TEST4</tt> and <tt>TEST5</tt> check the access permissions and cryptographic message digest. If any bits are set after that, the packet is discarded. Tests <tt>TEST10</tt> and <tt>TEST11</tt> check the authentication state using Autokey public-key cryptography, as described in the [Authentication Options](/archives/4.1.1/authopt) page. If any bits are set and the association has previously been marked reachable, the packet is discarded; otherwise, the originate and receive timestamps are saved, as required by the NTP protocol, and processing continues.

Tests <tt>TEST1</tt> through <tt>TEST3</tt> check the packet timestamps from which the offset and delay are calculated. If any bits are set, the packet is discarded; otherwise, the packet header variables are saved. Tests <tt>TEST6</tt> through <tt>TEST8</tt> check the health of the server. If any bits are set, the packet is discarded; otherwise, the offset and delay relative to the server are calculated and saved. Test <tt>TEST9</tt> checks the health of the association itself. If any bits are set, the packet is discarded; otherwise, the saved variables are passed to the clock filter and mitigation algorithms.

The <tt>flash</tt> bits for each test read in increasing order from the least significant bit are defined as follows.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST1</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Duplicate packet. The packet is at best a casual retransmission and at worst a malicious replay.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST2</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Bogus packet. The packet is not a reply to a message previously sent. This can happen when the NTP daemon is restarted and before somebody else notices.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST3</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Unsynchronized. One or more timestamp fields are invalid. This normally happens when the first packet from a peer is received.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST4</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Access is denied. See the [Access Control Options](/archives/4.1.1/accopt) page.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST5</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Cryptographic authentication fails. See the [Authentication Options](/archives/4.1.1/authopt) page.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST6</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The server is unsynchronized. Wind up its clock first.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST7</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The server stratum is at the maximum than 15. It is probably unsynchronized and its clock needs to be wound up.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST8</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Either the root delay or dispersion is greater than one second, which is highly unlikely unless the peer is synchronized to Mars.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST9</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Either the peer delay or dispersion is greater than one second, which is higly unlikely unless the peer is on Mars.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST10</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The autokey protocol has detected an authentication failure. See the [Authentication Options](/archives/4.1.1/authopt) page.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>TEST11</tt>

&nbsp;&nbsp;&nbsp;&nbsp;The autokey protocol has not verified the server or peer is authentic and has valid public key credentials. See the [Authentication Options](/archives/4.1.1/authopt) page.

Additional system variables used by the NTP Version 4 Autokey support include the following:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>certificate _filestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the certificate file was created.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>hostname _host_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the name of the host as returned by the Unix <tt>gethostname()</tt> library function.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>flags _hex_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the current flag bits, where the <tt>_hex_</tt> bits are interpreted as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x01</tt>

&nbsp;&nbsp;&nbsp;&nbsp;autokey enabled

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x02</tt>

&nbsp;&nbsp;&nbsp;&nbsp;RSA public/private key files present

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x04</tt>

&nbsp;&nbsp;&nbsp;&nbsp;PKI certificate file present

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x08</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Diffie-Hellman parameters file present

&nbsp;&nbsp;&nbsp;&nbsp;<tt>0x10</tt>

&nbsp;&nbsp;&nbsp;&nbsp;NIST leapseconds table file present

&nbsp;&nbsp;&nbsp;&nbsp;<tt>leapseconds _filestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the NIST leapseconds table file was created.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>params _filestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the Diffie-Hellman agreement parameter file was created.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>publickey _filestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the RSA public/private key files were created.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>refresh _timestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the public cryptographic values were refreshed and signed.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>tai _offset_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the TAI-UTC offset in seconds obtained from the NIST leapseconds table.

Additional peer variables used by the NTP Version 4 Autokey support include the following:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>certificate _filestamp_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the certificate file was created.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>flags _hex_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the current flag bits, where the _hex_ bits are interpreted as in the system variable of the same name. The bits are set in the first autokey message received from the server and then reset as the associated data are obtained from the server and stored.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>hcookie _hex_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the host cookie used in the key agreement algorithm.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>initkey _key_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the initial key used by the key list generator in the autokey protocol.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>initsequence _index_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the initial index used by the key list generator in the autokey protocol.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>pcookie _hex_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the peer cookie used in the key agreement algorithm.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>timestamp _time_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Shows the NTP seconds when the last autokey key list was generated and signed.

<dt><tt>pstatus _assocID_</tt></dt>

Sends a read status request to the server for the given association. The names and values of the peer variables returned will be printed. Note that the status word from the header is displayed preceding the variables, both in hexadecimal and in pidgeon English.

<dt><tt>readlist [ _assocID_ ]</tt>  
<tt>rl [ _assocID_ ]</tt></dt>

Requests that the values of the variables in the internal variable list be returned by the server. If the association ID is omitted or is 0 the variables are assumed to be system variables. Otherwise they are treated as peer variables. If the internal variable list is empty a request is sent without data, which should induce the remote server to return a default display.

<dt><tt>readvar _assocID_ _variable_name_ [ = _value_ ] [ ...]</tt>  
<tt>rv _assocID_ [ _variable_name_ [ = _value_ ] [...]</tt></dt>

Requests that the values of the specified variables be returned by the server by sending a read variables request. If the association ID is omitted or is given as zero the variables are system variables, otherwise they are peer variables and the values returned will be those of the corresponding peer. Omitting the variable list will send a request with no data which should induce the server to return a default display. 

<dt><tt>writevar _assocID_ _variable_name_ [ = _value_ [ ...]</tt></dt>

Like the readvar request, except the specified variables are written instead of read.

<dt><tt>writelist [ _assocID_ ]</tt></dt>

Like the readlist request, except the internal list variables are written instead of read.

* * *

#### Bugs

The peers command is non-atomic and may occasionally result in spurious error messages about invalid associations occurring and terminating the command. The timeout time is a fixed constant, which means you wait a long time for timeouts since it assumes sort of a worst case. The program should improve the timeout estimate as it sends queries to a particular host, but doesn't.