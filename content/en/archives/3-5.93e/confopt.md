---
title: "Configuration Options"
type: archives
---

#### Configuration Commands

<dt><tt>peer _address_ [key _key_ ] [version _version_] [prefer] [minpoll _minpoll_] [maxpoll _maxpoll_]</tt></dt>

<dt><tt>server _address_ [key _key_ ] [version _version_] [prefer] [mode _mode_]</tt></dt>

<dt><tt>broadcast _address_ [key _key_ ] [version _version_] [ttl _ttl_]</tt></dt>

These three commands specify the time server name or address _address_ to be used and the mode in which to operate. The _address_ can be either a DNS name or a IP address in dotted-quad notation. The <tt>peer</tt> command specifies that the local server is to operate in symmetric active mode with the remote server. In this mode, the local server can be synchronized to the remote server and, in addition, the remote server can be synchronized by the local server. This is useful in a network of servers where, depending on various failure scenarios, either the local or remote server may be the better source of time.

The <tt>server</tt> command specifies that the local server is to operate in client mode with the specified remote server. In this mode, the local server can be synchronized to the remote server, but the remote server can never be synchronized to the local server.

The <tt>broadcast</tt> command specifies that the local server is to operate in broadcast mode, where the local server sends periodic broadcast messages to a client population at the broadcast/multicast _address_ specified. Ordinarily, this specification applies only to the local server operating as a sender; for operation as a broadcast client, see the <tt>broadcastclient</tt> or <tt>multicastclient</tt> commands below. In this mode, _address_ is usually the broadcast address on (one of) the local network(s) or a multicast address assigned to NTP. The Numbers Czar has assigned the address 224.0.1.1 to NTP; this is presently the only address that should be used. Note that the use of multicast features requires a multicast kernel, which is not yet ubiquitous in vendor products.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>key</tt> _<tt>key</tt>_

&nbsp;&nbsp;&nbsp;&nbsp;All packets sent to the address are to include authentication fields encrypted using the specified key identifier, which is an unsigned 32 bit integer. The default is to not include an encryption field. 

&nbsp;&nbsp;&nbsp;&nbsp;<tt>version _version_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the version number to be used for outgoing NTP packets. Versions 1, 2, and 3 are the choices, with version 3 the default.  

&nbsp;&nbsp;&nbsp;&nbsp;<tt>prefer</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Marks the server as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/3-5.93e/prefer) page for further information. 

&nbsp;&nbsp;&nbsp;&nbsp;<tt>ttl _ttl_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This option is used only with broadcast mode. It specifies the time- to-live ttl to use on multicast packets. Selection of the proper value, which defaults to 127, is something of a black art and must be coordinated with the network administrator(s). 

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minpoll _minpoll_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This option specifies the minimum polling interval for NTP messages, in seconds to the power of two. The allowable range is 4 (16 s to 14 (16384 s) inclusive. The default is 6 (64 s) for all except reference clocks. 

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxpoll _maxpoll_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;This option specifies the maximum polling interval for NTP messages, in seconds to the power of two. The allowable range is 4 (16 s to 14 (16384 s) inclusive. The default is 10 (1024 s) for all except reference clocks. 

<dt><tt>broadcastclient [ _address_ ]</tt></dt>

This command directs the local server to listen for broadcast messages at the broadcast address _address_ of the local network. The default address is the subnet address with the host field bits set to ones. Upon hearing a broadcast message for the first time, the local server measures the nominal network delay using a brief client/server exchange with the remote server, then enters the broadcastclient mode, in which it listens for and synchronizes to succeeding broadcast messages. Note that, in order to avoid accidental or malicious disruption in this mode, both the local and remote servers should operate using authentication and the same trusted key and key identifier.

<dt><tt>multicastclient [ _address_ ] [ ... ]</tt></dt>

This command directs the local server to listen for multicast messages at the group _address_(es) of the global network. The default address is that assigned by the Numbers Czar to NTP (224.0.1.1). This command operates in the same way as the <tt>broadcastclient</tt> command, but uses IP multicasting. Support for this command requires a multicast kernel.

<dt><tt>driftfile _driftfile_</tt></dt>

This command specifies the name of the file used to record the frequency offset of the local clock oscillator. If the file exists, it is read at startup in order to set the initial frequency offset and then updated once per hour with the current frequency offset computed by the daemon. If the file does not exist or this command is not given, the initial frequency offset is assumed zero. In this case, it may take some hours for the frequency to stabilize and the residual timing errors to subside.

The <tt>ntp.drift</tt> file format consists of a single line containing a single floating point number, which records the frequency offset measured in parts-per-million (PPM). That the file is updated once per hour by first writing the current drift value into a temporary file and then renaming this file to replace the old version. This implies that <tt>xntpd</tt> must have write permission for the directory the drift file is located in, and that file system links, symbolic or otherwise, should probably be avoided.

<dt><tt>enable auth | bclient | monitor | pll | pps | stats</tt></dt>
  
<dt><tt>disable auth | bclient | monitor | pll | pps | stats</tt></dt>

Provides a way to enable or disable various server options. Flags not mentioned are unaffected. Note that all of these flags can be controlled remotely using the [<tt>xntpdc</tt>](/archives/3-5.93e/xntpdc) utility program.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>auth</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to synchronize with unconfigured peers only if the peer has been correctly authenticated using a trusted key and key identifier. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>bclient</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to listen for a message from a broadcast or multicast server, as in the <tt>multicastclient</tt> command with default address. The default for this flag is disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>monitor</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the monitoring facility. See the <tt>xntpdc</tt> program and the <tt>monlist</tt> command or further information. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>pll</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the server to adjust its local clock by means of NTP. If disabled, the local clock free-runs at its intrinsic time and frequency offset. This flag is useful in case the local clock is controlled by some other device or protocol and NTP is used only to provide synchronization to other clients. In this case, the local clock driver is used. See the [Reference Clock Drivers](/archives/3-5.93e/refclock) page for further information. The default for this flag is enable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>pps</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the pulse-per-second (PPS) signal when frequency and time is disciplined by the precision time kernel modifications. See the [A Kernel Model for Precision Timekeeping](/archives/3-5.93e/kern) page for further information. The default for this flag is disable.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stats</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Enables the statistics facility. See the [Monitoring Options](/archives/3-5.93e/monopt) page for further information. The default for this flag is enable.

<dt><tt>tick value</tt></dt>

If no value for <tt>tick</tt> can be found from the kernel, use this value. This is the "normalized" value; if your system keeps <tt>tick</tt> in nanoseconds you must divide your value by 1000. The expected range of the value is between 900 and 11,000 (don't use the comma in the config file).

<dt><tt>tickadj value</tt></dt>

If no value for <tt>tickadj</tt> can be found in the kernel, use this value. The value must be "normalized"; if your system keeps <tt>tickadj</tt> in nanoseconds you must divide your value by 1000. The expected range of the value is between 1 and 50.