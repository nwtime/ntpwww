---
title: "6. Configuration"
type: "archives"
---

Configuration is a manual procedure that is necessary to get a running NTP system.

#### 6.1. Can't I become happy with ntpdate alone?

`ntpdate` sets the system clock once and mostly in a brute way. As real clocks drift, you need periodic corrections. Basically can run `ntpdate` in a `cron` job hourly or daily, but your machine won't be an NTP server then.

In contrast, running `xntpd` will learn and remember the clock drift and it will correct it autonomously, even if there is no reachable server. Therefore large clock steps can be avoided while the machine is synchronized to some reference clock. In addition `xntpd` will maintain error estimates and statistics, and finally it can offer NTP service for other machines. Last, but no least, `ntpdate` cannot query a local reference clock.

In addition, there are plans to put the functionality of `ntpdate` into `ntpd`. Let me quote [Professor David L. Mills](mailto:mills@udel.edu):

Our zeal to deprecate `ntpdate` and friends like that is based entirely on our wish to eliminate redundant maintenance. The `ntpdate` program was crafted many years ago as a ripoff of `xntpd` with poorly adapted I/O, outdated algorithms and poor debugging support. If we can satisfy folks that `ntpd` with appropriate command line switch is the answer to their collective prayers, then we will scrap `ntpdate` and friend. It is in principle easy to modify `ntpd` to "quickly" set the clock; however, please do understand our reluctance to do that for the following reasons.

Most folks who use `ntpdate` call it from a `cron` job at intervals of maybe a day. You would be surprised at how many do this at the stroke of midnight. We have observed little fireballs of congestion when that occurs, especially at the NIST and USNO servers which even in the best of times with polite `xntpd/ntpd` suffer an aggregate load of well over 40 packets per second. We really don't want clients to create volleys of congestion by transmitting as fast as the network will allow.

The thrust of recent work on the NTPv4 protocols has not (with emphasis) been to improve accuracy - the nanokernel development is tangential and the only interlocking agenda has been to adapt the PPS interface to a standard acceptable to the kernel-mongers for the Alpha, SPARC and Intel platforms. However, it is indeed fair to characterize the work specific to NTPv4 as concentrating on the error mitigation algorithms to deal with the extraordinary range of network path characteristics encountered today. There also have been many incremental improvements, such as burst mode, that have resulted from various bug reports and suggestions.

An absolutely vital requirement in our view is to protect against accidental or malicious servers that may result in excessive time errors. The only true defense against falsetickers is to have at least three different servers (a Byzantine defense requires at least four) and an effective mitigation algorithm, such as the one now used in NTP and refined over the last eight years. Note that accuracy is not an issue here, only the separation of the truechimers from the falsetickers.

Now, the first measurement when the `ntpd` is first started is almost certainly a terrible one. There are many reasons for this - ARP caching in the routers, flow setup at various points and circuit setup (ISDN). The only real solution for that is to use more than one sample. The measurements made some years ago and revealed in an RFC suggest that a window of eight samples is a good compromise between effectiveness (more samples) and closed-loop transient response (fewer samples).
 
So, I think most folks would agree that some number of different servers is necessary and that some number of samples should be collected before the mitigation algorithms do set the clock. You get to select the former in the configuration file (or use manycast to do that automatically). How many samples to wait before the mitigation algorithms actually set the clock depends on the quality of the estimated accuracy. The parameters selected as the result of experience result in about four samples, depending on the network jitter.

So, let's say that as the result of several years experience and algorithm refinement we agree on four servers and four samples. The question is what is the interval between samples? As delivered from shrinkwrap, the initial interval is 64 s, but does usually increase to 1024 s. That results in about a four minute delay before the clock is set, which might be too long for some, but does protect the musy public servers on the net now. So what's the deal? You can reduce that interval to a few seconds using burst mode. While this does provide more snappy response, it increases the aggregate client insult to the server by a factor of eight and should be used sparingly.

However, this is not the only consideration. When multiple servers are involved, it is not a good idea to poll them at the same time. Therefore, ntpd randomized the initial volley when first coming up. This results in an average delay of about 30 s before anything useful happens. Worse than that, ntpd has to wait until a majority of the configured servers have showed up and with at least four good samples.

You can see from the above why we believe `ntpdate` is such a poor network citizen and at least some idea of its vulnerabilities. You can also see where the compromises are and possibly how changing some of the parameters might benefit your cause. We could disable the initial randomization, increase the quality tolerance so fewer samples will set the clock, go into burst mode initially and once the clock is set back off to normal mode, etc., etc. Right now, parameter selection is a black art; I would suspect making them configurable will result in some very bad choices and may result in serious server insult. Once upon a time (with NTPv1) a bug resulted in some servers volleying continuously as fast as the net would allow. The bug was discovered only after the network monitoring center reported that NTP was the single largest source of traffic in the Internet.

The issues of whether and how to step the clock have been debated more or less continuously for the twenty years of NTP evolution. One clique believes the clock should never be set backward under any circumstances. Their punishment is to suffer up to some hours while the clock torques to acceptable offset at half a millisecond per second, which is the maximum rate most kernels can tolerate and the limiting assumption which is at the very heart of the formal correctness principles supported by the design. During the torque interval network clocks cannot be assumed synchronized, so network makes, archiving, etc., can fail, even if local applications may survive. The `-g` option was designed to behave this way, but its use is not recommended.

A complicating fact is that, once an error greater than 125 ms is discovered, the question is whether to believe it. Our experience with radio clocks is that it may take several minutes or more to obtain initial synchronization. This and the fact that very noisy paths to some remote spots on the globe can result in huge spikes from time to time suggest that the clock should not be stepped until a consistent offset has been observed for a sanity interval, currently 15 minutes. Considerable experience suggests this is a good compromise time, but your agenda might be better served using some other value. What should it be?

In the vast majority of cases, once the clock is reliably set and the frequency stabilizes, the clock does not need to be stepped again, even after reboot and sometimes even when the power is cycled. The current NTP behavior is to step the clock if necessary when ntpd is started and the clock has never been set, then to obey the -g option after that. This was done as the result of suggestions made some time back.

Obviously, keeping most folks happy with any one set of rules may not be acceptable by other folks. The intent feverishly pursued is to avoid configured little nits in favor of an adaptive approach where the daemon figures things out on its own and without configured appeasement. It may be possible to satisfy more that some folks crave by continued enhancement and re-engineering of intricate behavior, but the above ground rules must be respected.

(...)

To avoid a biased impression, lets quote [Per Hedeland](mailto:per@erix.ericsson.se) as well:

99.9999% of NTP users don't care one iota whether `ntpdate` does such a lousy job that the clock ends up just within 50 ms of the correct time instead of 5 or 0.005. On the other hand they care a lot if the boot has to be delayed - for how long? 5 x 64 seconds? - just to allow `ntpd` to get a good enough fix that it is prepared to step the clock. And they care a lot, though they may not know it, if various applications (which may be many more than "some database servers") run into problems because the clock is stepped after they've started instead of before.

* * *

#### 6.1. Basic Configuration

This section discusses basic configuration issues for `xntpd`, hopefully covering what 90% of the users need.

#### 6.1.1. Recommended Minimum

6.1.1.1. [What is the minimum configuration?](#what-is-the-minimum-configuration)  
6.1.1.2. [Is the minimum configuration a typical one?](#is-the-minimum-configuration-a-typical-one)  
6.1.1.3. [What is the correct Pseudo IP Address for my reference clock?](#what-is-the-correct-pseudo-ip-address-for-my-reference-clock)  
6.1.1.4. [What is that drift-file?](#what-is-that-drift-file)  
6.1.1.5. [Should I use IP addresses or host names?](#should-i-use-ip-addresses-or-host-names)

* * *

#### 6.1.1.1. What is the minimum configuration?

The minimum configuration for `xntpd` only needs one reference clock. Reference clocks use _pseudo IP addresses_ in `xntpd`. Thus your configuration file could look like this:

<pre>server 127.127.8.0 mode 5	# GENERIC DCF77 AM</pre>

> **Note:** Some reference clock drivers require special device files to be created. These files are used to talk to the reference clock. See the [corresponding documentation of the driver](/archives/4.2.8-series/refclock/#list-of-reference-clock-drivers).

In reality one would add several other configuration items, like a drift-file, additional servers, remote monitoring and configuration, logging, access restrictions, etc.

* * *

#### 6.1.1.2. Is the minimum configuration a typical one?

Besides being functional, configurations for the real life look differently from the one shown in question [Q: 6.1.1.1.](#6111-what-is-the-minimum-configuration). Most NTP servers have no reference clocks, but use lower [stratum](/ntpfaq/ntp-s-algo/#5141-what-is-the-stratum) servers as time references. Public time servers can be found [here](https://support.ntp.org/bin/view/Servers/WebHome). [Courtesy](#6141-what-is-the-preferred-etiquette-when-synchronizing-to-a-public-server) suggests to inform the maintainers of the time server that you are using their service. As an advantage, they might inform you if their service is going to be down. There is almost no difference in the configuration:

<pre>server 132.199.176.10	# some NTP server's IP address
# You might add the EMail address of the contact person</pre>

[Configuring multiple servers](/ntpfaq/ntp-s-algo-real/#532-why-should-i-have-more-than-one-clock) improves the quality of the time. That is because of NTP being able to select the best time sources from a set of available ones.

* * *

#### 6.1.1.3. What is the correct Pseudo IP Address for my reference clock?

The various drivers for reference clocks are selected using IPv4 adresses. (NTP for IP version 6 has not yet been defined.) Such an IP address consists of four bytes that are separated by a dot. The individual bytes are: <code>127.127._Clock Type.Unit Number_</code>.

The supported clock types are listed [here](/archives/4.2.8-series/refclock/#list-of-reference-clock-drivers). Usually it does not make sense, but if you want to connect more than one clock of a type, you can do so by using different unit numbers. The driver maps these unit numbers to one or more device files. The exact name of the device file can be found in the description of the individual reference clock's driver.

* * *

#### 6.1.1.4. What is that drift-file?

When running, `xntpd` learns about the drift of the system clock relative to the reference clock. To make `xntpd` remember the drift, you must add the following item to your configuration file (it will be updated every hour):

<pre>driftfile /etc/ntp.drift        # remember the drift of the local clock</pre>

When using a drift-file, `xntpd` will use the last written value as initial frequency correction after restart. That way the best correction is set up much faster (Without a drift-file the initial frequency correction is always zero).

[Mark Martinec](mailto:mark.martinec@ijs.si) contributed:

On a Cisco router running IOS one can save the current frequency offset estimate to a nonvolatile memory with a command `write memory` (or a newer `copy running-config startup-config`), to make sure router starts up with a good frequency estimate after a reset. Do that manually after a day or two of a stable router operation with its NTP synchronized, and perhaps a few more times per year during seasons changes if router is operating in non-air-conditioned environment. This operation saves the current frequency estimate as a configuration line <code>ntp clock-period _xxxx_</code>.

* * *

#### 6.1.1.5. Should I use IP addresses or host names?

During startup `xntpd` resolves symbolic addresses to numeric addresses using the resolver service. However there are some differences worth considering:

*   If a symbolic name has assigned multiple IP addresses, you may wish to explicitly select one.
*   Using numeric addresses does not require a correct configuration of a resolver, and it may avoid making a connection to the Internet.
*   Many service providers use _aliases_ or _logical host names_ when providing services. When using names like `ntp-1-a` for an NTP server, the service provider may map the logical name to a different machine, possibly without informing any clients. So if you use host names in your configuration file, all you have to do is to restart or [reconfigure](#6134-how-do-i-use-authentication-keys) your `ntpd`.

* * *

#### 6.1.2. Running an isolated Network

If you are not permanently connected to the Internet, you may need a different configuration. This is discussed here.

#### 6.1.2.1. Can I use my system clock as reference clock?

In short: You can, but you should not. See also [What is LCL, the Local Clock?](/ntpfaq/ntp-s-refclk/#711-what-is-lcl-the-local-clock).

> **Warning**: Using the free-running system clock means that your NTP server announces that time as reference time to any client, no matter how wrong it is. Especially when connected to the Internet this can cause severe confusion.

A [survey](/reflib/reports/ntp-survey99-minar.pdf) discovered that about 95% of bad stratum-1 servers had configured `LCL`, the local clock, as time reference. So please don't make the same mistake after having read this!

Care has to be taken if you intend NTP to propagate manual changes of the local system time. `xntpd` (NTP v3) uses an artificial time scale that will not (immediately) follow such changes. See also [Q: 5.1.1.4.](/ntpfaq/ntp-s-algo/#5114-what-happens-if-the-reference-time-changes).

* * *

#### 6.1.2.2. Can I avoid manual time adjustments in a network without reference clock?

If you have a MODEM and you can afford the telephone costs, you can use the following configuration to call NIST (thanks to [William R. Pennock](mailto:bill.pennock@transquest.com)):

<pre># NIST Automated Computer Time Service. This driver calls a special
# telephone number in Boulder, CO, to fetch the time directly from the
# NIST cesium farm. The details of the complicated calling program are
# in html/refclock.htm. The Practical Peripherals 9600SA modem
# does not work correctly with the ACTS echo-delay scheme for
# automatically calculating the propagation delay, so the fudge flag2 is
# set to disable the feature. Instead, we add a fudge time1 of 65.0 ms
# so that the driver time agrees with th e1-pps signal to within 1 ms.
# The phone command specifies three alternate telephone numbers,   
# including AT modem command prefix, which will be tried one after the
# other at each measurement attempt. In this case, a cron job is used to
# set fudge flag1, causing a measurement attempt, every six hours.
server 127.127.18.1
fudge 127.127.18.1 time1 0.0650 flag2 1
phone atdt813034944774 atdt813034944785 atdt813034944774</pre>

* * *

### 6.1.3. Recommended Goodies

The topics discussed here are not strictly needed for a working configuration, but they are quite nice to have.

6.1.3.1. [How can I configure the amount of logging information?](#how-can-i-configure-the-amount-of-logging-information)  
6.1.3.2. [How can I speed up initial Synchronization?](#how-can-i-speed-up-initial-synchronization)  
6.1.3.3. [How do I configure remote administration?](#how-do-i-configure-remote-administration)  
6.1.3.4. [How do I use authentication keys?](#how-do-i-use-authentication-keys)  
6.1.3.5. [What are all the different Keys used for?](#what-are-all-the-different-keys-used-for)  
6.1.3.6. [How do I use the new autokey feature?](#how-do-i-use-the-new-autokey-feature)  

* * *

#### 6.1.3.1. How can I configure the amount of logging information?

When starting to run `xntpd` you should have a more verbose logging than set up by default. Before you go into the details, you might start with the following line:

<pre>logconfig =syncevents +peerevents +sysevents +allclock</pre>

When absolutely clueless of what's going on, you might enable full logging (Make sure your `/etc/syslog.conf` captures all these messages):

<pre>logconfig =all</pre>

* * *

#### 6.1.3.2. How can I speed up initial Synchronization?

[Several packet exchanges are needed](/ntpfaq/ntp-s-algo/#5121-how-is-time-synchronized) before time can be corrected. Therefore the obvious trick is to speed up packet exchanges. See [Q: 5.1.2.4.](/ntpfaq/ntp-s-algo/#5124-when-are-the-servers-polled) for a general discussion of the polling algorithm. The `iburst` keyword can be used to quickly set up the registers of the receive filter when they are empty. Typically this is true for a restart, or when the connection to a server was down for a longer period. When used, the data should be available within 30 seconds.

If the local clock does not have a good estimate for the current time, using option `-g` on the command line may also speed up the time until `ntpd` sets the clock for the first time. Furthermore that option will also allow suspiciously huge initial correction.

These modifications are actually intended as a replacement for `ntpdate` in NTPv4. A script named `ntp-wait` will wait until `ntpd` has set the time of the local host for the first time.

* * *

#### 6.1.3.3. How do I configure remote administration?

One of the nice features of NTP is the ability of remote monitoring and configuration. You can add or remove reference clocks at runtime without having to restart `xntpd`. Normally this doesn't work until you specify authentication information (you don't want anyone to remove your reference clocks, I guess). Authentication in NTP works with keys. First you'll have to specify the numbers (key ID) of the keys to be used:

<pre>### Authentication section ###
keys /etc/ntp.keys
trustedkey 1 2 15
requestkey 15
controlkey 15</pre>

This tells `xntpd` to trust keys `1` and `2` when receiving time information. Key `15` is trusted for queries and configuration changes (`requestkey` is used by `xntpdc` while `controlkey` is used by `ntpq`).

> **Note:** Even though `controlkey` and `requestkey` are explicitly specified, you still must add the keys to `trustedkey`.

To specify the keys for `xntpd` you'll have to create the file `/etc/ntp.keys`. As `xntpd` runs as priviledged process, only the priviledged user (root) needs access to this file.

> **Note:** Password are stored unencrypted in the keyfile. Therefore no other user should have read or write access to that file (or write access to any containing directory).

Here's an example for the contents of a keyfile; the first column specifies the key number (range 1 to 65535), the second column the key type `S` (DES key in DES format), `N` (DES key in NTP format), `A` (DES key as ASCII string), `M` (MD5 key as ASCII string), and the third column is the key itself. In _NTP Security Model_ key IDs are described as 32-bit values.

<pre>1   S    68767ce625aef123
2   S    df2ab658da62237a
15  A    I_see!
498 M    NTPv4.98</pre>

Depending on the type of key (DES or MD5) you want to use, you'll have to use the command `keytype` in `xntpdc` to specify the type your key has. Normally you are asked for the key's number and the password when `xntpdc` uses a command to change the configuration. Your input will be remembered inside `xntpdc`, so that you only have to enter it once per session.

The example above uses DES keys. DES stands for Data Encryption Standard and is considered as munition in the USA, and therefore may not be exported. Probably as this 56-bit encryption is rather ridiculous to the rest of the world, DES keys are no longer supported in NTPv4. You would change all the letters in the second column to `M`. `M` stands for MD5 (Message Digest #5), a strong one-way hash function described in [RFC 1321 - The MD5 Message-Digest Algorithm](/reflib/rfc/rfc1321.txt).

* * *

#### 6.1.3.4. How do I use authentication keys?

The popular implementation of NTP we are talking about has a powerful feature named _dynamic reconfiguration_. This means you can change the configuration of your servers using the protocol itself. As this works over the network, there's no need to log in or to walk around. Even more, it works the same on all operating systems.

As not everybody should be allowed to change the configuration of an NTP server, configuration items are protected by an authentication algorithm. You have to prove that you are allowed to access configuration items by entering some magic key (password). `xntpdc` automatically asks for a key number and a password when it is required. Once entered, the key and password is remembered:

<pre>xntpdc> keytype des
xntpdc> unconfig 127.127.8.0
Keyid: 15
DES Password:</pre>

While possible, specifying the password on `xntpdc`'s command line like <code>xntpdc -c "keyid _1_" -c "passwd _pw_" -c "_other_command"_</code> is not recommended.

* * *

#### 6.1.3.5. What are all the different Keys used for?

In addition to the example given in [Q: 6.1.3.3.](#6133-how-do-i-configure-remote-administration), [Professor David L. Mills](mailto:mills@udel.edu) states:

Control keys are for the ntpq program and request keys are for the ntpdc program. The key file(s) define the cryptographic keys, but these must be activated individually using the trustedkey command. That last is so a single key file can be shared among a bunch of servers, but only certain ones used between pairwise symmetric mode servers. You are invited to cut this paragraph and paste it on the refrigerator door if it eases confusion.

* * *

#### 6.1.3.6. How do I use the new autokey feature?

NTP version 4 has a new way of managing authentication keys, commonly referred to as autokey mechanism. The following procedure had been given by [Professor David L. Mills](mailto:mills@udel.edu):

1.  A broadcast server needs to have a line like `broadcast 128.4.2.255 autokey`.
2.  The clients simply have `broadcastclient`.

Replace `broadcast` with `multicast` and follow `autokey` with `ttl 5` or something like that. As for the crypto questions, refer to [Autonomous Authentication](/reflib/autokey) and 
[Q: 6.2.2.6.](/ntpfaq/ntp-s-config-adv/#6226-how-do-i-use-public-key-authentication-autokey).

* * *

#### 6.1.4. Miscellaneous Hints

#### 6.1.4.1. What is the preferred etiquette when synchronizing to a public server?

If the [listing](https://support.ntp.org/bin/view/Servers/WebHome) says to notify before before using a server, then you should send email and wait until you get an affirmative reply before using that server.

Some public timeservers are listed as "open access" with no notice required (especially the secondaries). Very public-spirited. I have one of these (stratum-2 right now) at ntp-cup.external.hp.com.

You should probably have no more than three of your timeservers using any individual public timeserver. Let all of your internal clients be served by those three (or three-groups-of-three).

The most popular time servers are highly overloaded, recommending that you should avoid them if possible. The official etiquette is described in [Rules of Engagement](https://support.ntp.org/bin/view/Servers/RulesOfEngagement).

* * *

#### 6.1.4.2. How and where can I find public Time Servers?

Additionally, NIST (the United States National Instute of Standards and Technology) has a [list of public time servers](https://tf.nist.gov/tf-cgi/servers.cgi). Their policy statement implies that their Internet time servers are open access to everyone.