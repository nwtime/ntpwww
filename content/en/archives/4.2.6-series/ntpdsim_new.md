---
title: "ntpdsim - Network Time Protocol (NTP) Simulator"
type: archives
---

![gif](/archives/pic/oz2.gif)[from _The Wizard of Oz_, L. Frank Baum](/reflib/pictures)

All in a row.

Last update: 15:56 UTC Sunday, March 02, 2008

* * *

#### Table of Contents

*   [Description](/archives/4.2.6-series/ntpdsim_new/#description)
*   [Configuration](/archives/4.2.6-series/ntpdsim_new/#configuration)
*   [Sample Configuration File](/archives/4.2.6-series/ntpdsim_new/#sample-configuration-file)

* * *

#### Description

The ntpdsim program is used to simulate and study the behavior of an NTP daemon that derives its time from a number of different simulated time sources (servers). Each simulated server can be configured to have a different time offset, frequency offset, propagation delay, processing delay, network jitter and oscillator wander.

The ntpdsim program runs all the same selection, mitigation, and discipline algorithms as the actual ntpd daemon at the client. (It actually uses the same code). However, the input/output routines and servers are simulated. That is, instead of sending the client messages over the network to the actual servers, the client messages are intercepted by the ntpdsim program, which then generates the replies to those messages. The reply messages are carefully "inserted" into the input queue of the client at the right time according to the specified server properties (like propagation delay).

Each simulated server runs according to a specified script that describes the server properties at a particular time. Each script consists of a series of consecutive acts. Each act runs for a particular duration and specifies the frequency offset, propagation delay, processing delay, network jitter and oscillator wander of the server for that duration. Once the duration of an act expires, the simulated server reconfigures itself according to the properties specified in the next act.

* * *

#### Configuration

The ntpdsim program is configured by providing a configuration file at startup. The crux of the simulator configuration is specified using a <tt>simulate</tt> command, the syntax of which is given below. Note that all time quantities are in seconds and all frequency quantities are in parts per million (PPM):


`<_simulate_command_> ::= <tt>simulate</tt> { <_init_statement_list_> <_server_list_> }`  

`<_init_statement_list_> ::= <init_statement_list> <init_statement> | <init_statement>`  

`<_init_statement_> ::= <tt>beep_delay</tt> = <number> | <tt>simulation_duration</tt> = <number>`  

`<_server_list_> ::= <_server_list_> <server> | <server>`  

`<_server_list_> ::= <tt>server</tt> = <address> { <tt>server_offset</tt> = <number> <act_list> }`  

`<_act_list_> ::= <_act_list_> <_act_> | <_act_>`  

`<_act_> ::= <tt>duration</tt> = <number> { <_act_stmt_list_> }`  

`<_act_stmt_list_> ::= <_act_stmt_list_> <_act_stmt_> | <_act_stmt_>`  

`<_act_stmt_> ::= <tt>freq_offset</tt> = <number> | <tt>wander</tt> = <number> | <tt>jitter</tt> = <number> | <tt>prop_delay</tt> = <number> | <tt>proc_delay</tt> = <number>`


In addition to the simulate command, other standard NTP configuration commands can be specified. These commands have the same meaning as in the ntpd configuration. Note that newlines are **not** significant within the simulate command even though they are used to mark the end of a normal NTP configuration command.

* * *

#### Sample Configuration File

A sample ntpdsim configuration file is given below. It specifies two simulated servers, each of which has two acts.

<pre>    # Client configuration 
    disable kernel
    server pogo
    driftfile ./ntp.drift
    statsdir ./ntpstats/
    filegen loopstats type day enable
    filegen peerstats type day enable

    # Simulation configuration
    simulate {
        simulation_duration = 86400
        beep_delay = 3600

        # Server 1
	server = louie.udel.edu {
	    server_offset = 0 
            duration = 50000 {
		freq_offset = 400
		wander = 1.0
		jitter = 0.001
		prop_delay = 0.001
		proc_delay = 0.001
	    }
            duration = 6400 {
		freq_offset = 200
		wander = 1.0
		jitter = 0.001
		prop_delay = 0.001
		proc_delay = 0.001
	    }
	}

        # Server 2
	server = baldwin.udel.edu {
	    server_offset = 0.02
	    duration = 10000 {
		freq_offset = 400
		wander = 1.0
		jitter = 0.001
		prop_delay = 0.5
		proc_delay = 0.001
	    }
	    duration = 60000 {
		freq_offset = 200
		wander = 1.0
		jitter = 0.05
		prop_delay = 0.005
		proc_delay = 0.001
	    }
	}
    }
  </pre>

* * *

[Sachin Kamboj](mailto:skamboj@udel.edu)
