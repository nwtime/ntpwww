---
title: "ntpq - standard NTP query program"
type: archives
noindex: true
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/ntpq/#synopsis)
*   [Description](/archives/3-5.93e/ntpq/#description)
*   [Internal Commands](/archives/3-5.93e/ntpq/#internal-commands)
*   [Control Message Commands](/archives/3-5.93e/ntpq/#control-message-commands)
*   [Bugs](/archives/3-5.93e/ntpq/#bugs)

* * *

#### Synopsis

<code>ntpq [-inp] [-c _command_] [_host_] [...]</code>

* * *

#### Description

<code>ntpq</code> is used to query NTP servers which implement the recommended NTP mode 6 control message format about current state and to request changes in that state. The program may be run either in interactive mode or controlled using command line arguments. Requests to read and write arbitrary variables can be assembled, with raw and pretty-printed output options being available. <code>ntpq</code> can also obtain and print a list of peers in a common format by sending multiple queries to the server. 

If one or more request options is included on the command line when <code>ntpq</code> is executed, each of the requests will be sent to the NTP servers running on each of the hosts given as command line arguments, or on localhost by default. If no request options are given, <code>ntpq</code> will attempt to read commands from the standard input and execute these on the NTP server running on the first host given on the command line, again defaulting to localhost when no other host is specified. <code>ntpq</code> will prompt for commands if the standard input is a terminal device.

<code>ntpq</code> uses NTP mode 6 packets to communicate with the NTP server, and hence can be used to query any compatible server on the network which permits it. Note that since NTP is a UDP protocol this communication will be somewhat unreliable, especially over large distances in terms of network topology. <code>ntpq</code> makes one attempt to retransmit requests, and will time requests out if the remote host is not heard from within a suitable timeout time.

Command line options are described following. Specifying a command line option other than <code>-i</code> or <code>-n</code> will cause the specified query (queries) to be sent to the indicated host(s) immediately. Otherwise, <code>ntpq</code> will attempt to read interactive format commands from the standard input.

<code>**-c**</code>

: The following argument is interpreted as an interactive format command and is added to the list of commands to be executed on the specified host(s). Multiple <code>-c</code> options may be given.

<code>**-i**</code>

: Force <code>ntpq</code> to operate in interactive mode. Prompts will be written to the standard output and commands read from the standard input.

<code>**-n**</code>

: Output all host addresses in dotted-quad numeric format rather than converting to the canonical host names.

<code>**-p**</code>

: Print a list of the peers known to the server as well as a summary of their state. This is equivalent to the <code>peers</code> interactive command.

* * *

#### Internal Commands

Interactive format commands consist of a keyword followed by zero to four arguments. Only enough characters of the full keyword to uniquely identify the command need be typed. The output of a command is normally sent to the standard output, but optionally the output of individual commands may be sent to a file by appending a `<`, followed by a file name, to the command line. A number of interactive format commands are executed entirely within the <code>ntpq</code> program itself and do not result in NTP mode 6 requests being sent to a server. These are described following.

<code>**? [_command_keyword_]**</code>  
: <code>**help [_command_keyword_]**</code>

: A `?` by itself will print a list of all the command keywords known to this incarnation of <code>ntpq</code>. A `?` followed by a command keyword will print function and usage information about the command. This command is probably a better source of information about <code>ntpq</code> than this manual page.

<code>**addvars _variable_name_ [ = _value_] [...]**</code>  
: <code>**rmvars _variable_name_ [...]**</code>  
: <code>**clearvars**</code>

: The data carried by NTP mode 6 messages consists of a list of items of the form <code>_variable_name_ = _value_</code>, where the <code>= _value_</code> is ignored, and can be omitted, in requests to the server to read variables. <code>ntpq</code> maintains an internal list in which data to be included in control messages can be assembled, and sent using the <code>readlist</code> and <code>writelist</code> commands described below. The <code>addvars</code> command allows variables and their optional values to be added to the list. If more than one variable is to be added, the list should be comma-separated and not contain white space. The <code>rmvars</code> command can be used to remove individual variables from the list, while the <code>clearlist</code> command removes all variables from the list.

<code>**authenticate yes | no**</code>

: Normally <code>ntpq</code> does not authenticate requests unless they are write requests. The command <code>authenticate yes</code> causes <code>ntpq</code> to send authentication with all requests it makes. Authenticated requests causes some servers to handle requests slightly differently, and can occasionally melt the CPU in fuzzballs if you turn authentication on before doing a <code>peer</code> display. 

<code>**cooked**</code>

: Causes output from query commands to be "cooked". Variables which are recognized by the server will have their values reformatted for human consumption. Variables which <code>ntpq</code> thinks should have a decodable value but didn't are marked with a trailing `?`.

<code>**debug more | less | off**</code>

: Turns internal query program debugging on and off.

<code>**delay _milliseconds_**</code>

: Specify a time interval to be added to timestamps included in requests which require authentication. This is used to enable (unreliable) server reconfiguration over long delay network paths or between machines whose clocks are unsynchronized. Actually the server does not now require timestamps in authenticated requests, so this command may be obsolete.

<code>**host _hostname_**</code>

: Set the host to which future queries will be sent. Hostname may be either a host name or a numeric address.

<code>**hostnames [yes | no]**</code>

: If <code>yes</code> is specified, host names are printed in information displays. If <code>no</code> is specified, numeric addresses are printed instead. The default is <code>yes</code>, unless modified using the command line <code>-n</code> switch.

<code>**keyid _keyid_**</code>

: This command allows the specification of a key number to be used to authenticate configuration requests. This must correspond to a key number the server has been configured to use for this purpose.

<code>**ntpversion 1 | 2 | 3**</code>

: Sets the NTP version number which <code>ntpq</code> claims in packets. Defaults to 3. Note that mode 6 control messages (and modes, for that matter) didn't exist in NTP version 1. There appear to be no servers left which demand version 1.

<code>**quit**</code>

: Exit <code>ntpq</code>.

<code>**passwd**</code>

: This command prompts you to type in a password (which will not be echoed) which will be used to authenticate configuration requests. The password must correspond to the key configured for use by the NTP server for this purpose if such requests are to be successful.

<code>**raw**</code>

: Causes all output from query commands is printed as received from the remote server. The only formating/interpretation done on the data is to transform nonascii data into a printable (but barely understandable) form.

<code>**timeout _milliseconds_**</code>

: Specify a timeout period for responses to server queries. The default is about 5000 milliseconds. Note that since <code>ntpq</code> retries each query once after a timeout, the total waiting time for a timeout will be twice the timeout value set.

* * *

#### Control Message Commands

Each peer known to an NTP server has a 16 bit integer association identifier assigned to it. NTP control messages which carry peer variables must identify the peer the values correspond to by including its association ID. An association ID of 0 is special, and indicates the variables are system variables, whose names are drawn from a separate name space. 

Control message commands result in one or more NTP mode 6 messages being sent to the server, and cause the data returned to be printed in some format. Most commands currently implemented send a single message and expect a single response. The current exceptions are the peers command, which will send a preprogrammed series of messages to obtain the data it needs, and the mreadlist and mreadvar commands, which will iterate over a range of associations.

<code>**associations**</code>

: Obtains and prints a list of association identifiers and peer statuses for in-spec peers of the server being queried. The list is printed in columns. The first of these is an index numbering the associations from 1 for internal use, the second the actual association identifier returned by the server and the third the status word for the peer. This is followed by a number of columns containing data decoded from the status word. Note that the data returned by the <code>associations</code> command is cached internally in <code>ntpq</code>. The index is then of use when dealing with stupid servers which use association identifiers which are hard for humans to type, in that for any subsequent commands which require an association identifier as an argument, the form and index may be used as an alternative.

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

: Prints association data concerning in-spec peers from the internally cached list of associations. This command performs identically to the <code>associations</code> except that it displays the internally stored data rather than making a new query.

<code>**peers**</code>

: Obtains a list of in-spec peers of the server, along with a summary of each peer's state. Summary information includes the address of the remote peer, the reference ID (`0.0.0.0` if the refID is unknown), the stratum of the remote peer, the type of the peer (local, unicast, multicast or broadcast), when the last packet was received, the polling interval, in seconds, the reachability register, in octal, and the current estimated delay, offset and dispersion of the peer, all in seconds.

The character in the left margin indicates the fate of this peer in the clock selection process. The codes mean: <code>space</code> discarded due to high stratum and/or failed sanity checks; `x` designated falsticker by the intersection algorithm; `.` culled from the end of the candidate list; `-` discarded by the clustering algorithm; `+` included in the final selection set; `#` selected for synchronization but distance exceeds maximum; `*` selected for synchronization; and `o` selected for synchronization, PPS signal in use. 

Note that since the peers command depends on the ability to parse the values in the responses it gets it may fail to work from time to time with servers which poorly control the data formats.

The contents of the host field may be one of four forms. It may be a host name, an IP address, a reference clock implementation name with its parameter or `REFCLK(<implementation number>, <parameter>)`. On <code>hostnames no</code> only IP addresses will be displayed. 

<code>**pstatus _assocID_**</code>

: Sends a read status request to the server for the given association. The names and values of the peer variables returned will be printed. Note that the status word from the header is displayed preceding the variables, both in hexadecimal and in pidgeon English.

<code>**readlist [ _assocID_ ]**</code>  
: <code>**rl [ _assocID_ ]**</code>

: Requests that the values of the variables in the internal variable list be returned by the server. If the association ID is omitted or is 0 the variables are assumed to be system variables. Otherwise they are treated as peer variables. If the internal variable list is empty a request is sent without data, which should induce the remote server to return a default display.

<code>**readvar _assocID_ _variable_name_ [ = _value_ ] [ ...]**</code>  
: <code>**rv _assocID_ [ _variable_name_ [ = _value_ ] [...]**</code>

: Requests that the values of the specified variables be returned by the server by sending a read variables request. If the association ID is omitted or is given as zero the variables are system variables, otherwise they are peer variables and the values returned will be those of the corresponding peer. Omitting the variable list will send a request with no data which should induce the server to return a default display. 

<code>**writevar _assocID_ _variable_name_ [ = _value_ [ ...]**</code>

: Like the <code>readvar</code> request, except the specified variables are written instead of read.

<code>**writelist [ _assocID_ ]**</code>

: Like the <code>readlist</code> request, except the internal list variables are written instead of read.

* * *

#### Bugs

The <code>peers</code> command is non-atomic and may occasionally result in spurious error messages about invalid associations occurring and terminating the command. The timeout time is a fixed constant, which means you wait a long time for timeouts since it assumes sort of a worst case. The program should improve the timeout estimate as it sends queries to a particular host, but doesn't.