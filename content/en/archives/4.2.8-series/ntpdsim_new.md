---
title: "ntpdsim - Network Time Protocol (NTP) Simulator"
type: archives
---

![gif](/archives/pic/oz2.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures/)

All in a row.

Last update: 31-Jan-2014 06:54 UTC

* * *

#### Table of Contents

*   [Description](/archives/4.2.8-series/ntpdsim_new/#description)
*   [Configuration](/archives/4.2.8-series/ntpdsim_new/#configuration)
*   [Sample Configuration File](/archives/4.2.8-series/ntpdsim_new/#sample-configuration-file)

* * *

#### Description

The <code>ntpdsim</code> program is used to simulate and study the behavior of an NTP daemon that derives its time from a number of different simulated time sources (servers). Each simulated server can be configured to have a different time offset, frequency offset, propagation delay, processing delay, network jitter and oscillator wander.

The <code>ntpdsim</code> program runs all the same selection, mitigation, and discipline algorithms as the actual <code>ntpd</code> daemon at the client. (It actually uses the same code). However, the input/output routines and servers are simulated. That is, instead of sending the client messages over the network to the actual servers, the client messages are intercepted by the <code>ntpdsim</code> program, which then generates the replies to those messages. The reply messages are carefully "inserted" into the input queue of the client at the right time according to the specified server properties (like propagation delay).

Each simulated server runs according to a specified script that describes the server properties at a particular time. Each script consists of a series of consecutive acts. Each act runs for a particular duration and specifies the frequency offset, propagation delay, processing delay, network jitter and oscillator wander of the server for that duration. Once the duration of an act expires, the simulated server reconfigures itself according to the properties specified in the next act.

* * *

#### Configuration

The <code>ntpdsim</code> program is configured by providing a configuration file at startup. The crux of the simulator configuration is specified using a <code>simulate</code> command, the syntax of which is given below. Note that all time quantities are in seconds and all frequency quantities are in parts per million (PPM):

<code><_simulate_command_> ::= simulate { <_init_statement_list_> <_server_list_> }</code>
: <code><_init_statement_list_> ::= <init_statement_list> <init_statement> ; | <init_statement> ;</code> 
: <code><_init_statement_> ::= beep_delay = \<number> | simulation_duration = \<number></code>
: <code><_server_list_> ::= <_server_list_> \<server> | \<server></code>
: <code><_server_list_> ::= server = \<address> { server_offset = \<number> ; <act_list> }</code>
: <code><_act_list_> ::= <_act_list_> <_act_> | <_act_></code>
: <code><_act_> ::= duration = \<number> { <_act_stmt_list_> }</code>
: <code><_act_stmt_list_> ::= <_act_stmt_list_> <_act_stmt_> ; | <_act_stmt_> ;</code>
: <code><_act_stmt_> ::= freq_offset = \<number> | wander = \<number> | jitter = \<number> | prop_delay = \<number> | proc_delay = \<number></code>

In addition to the <code>simulate</code> command, other standard NTP configuration commands can be specified. These commands have the same meaning as in the <code>ntpd</code> configuration. Note that newlines are **not** significant within the <code>simulate</code> command even though they are used to mark the end of a normal NTP configuration command. While a newline is an "end of command" terminator for other configuration commands, in the <code>simulate</code> stanza <code>;</code> (the semicolon) is the "end of command" terminator.

* * *

#### Sample Configuration File

A sample <code>ntpdsim</code> configuration file is given below. It specifies two simulated servers, each of which has two acts.

<pre>    # Client configuration
    disable kernel
    server pogo
    driftfile ./ntp.drift
    statsdir ./ntpstats/
    filegen loopstats type day enable
    filegen peerstats type day enable

    # Simulation configuration
    simulate {
        simulation_duration = 86400;
        beep_delay = 3600;

        # Server 1
	server = louie.udel.edu {
	    server_offset = 0;
            duration = 50000 {
		freq_offset = 400;
		wander = 1.0;
		jitter = 0.001;
		prop_delay = 0.001;
		proc_delay = 0.001;
	    }
            duration = 6400 {
		freq_offset = 200;
		wander = 1.0;
		jitter = 0.001;
		prop_delay = 0.001;
		proc_delay = 0.001;
	    }
	}

        # Server 2
	server = baldwin.udel.edu {
	    server_offset = 0.02;
	    duration = 10000 {
		freq_offset = 400;
		wander = 1.0;
		jitter = 0.001;
		prop_delay = 0.5;
		proc_delay = 0.001;
	    }
	    duration = 60000 {
		freq_offset = 200;
		wander = 1.0;
		jitter = 0.05;
		prop_delay = 0.005;
		proc_delay = 0.001;
	    }
	}
 }
  </pre>

* * *

[Sachin Kamboj](mailto:skamboj@udel.edu)
