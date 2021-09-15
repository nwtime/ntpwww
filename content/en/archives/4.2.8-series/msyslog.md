---
title: "ntpd System Log Messages"
type: archives
---

![gif](/archives/pic/flatheads.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

The log can be shrill at times.

Last update: 10-Mar-2014 05:12 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.8-series/msyslog/#introduction)
*   [Protocol Module](/archives/4.2.8-series/msyslog/#protocol-module)
*   [Clock Discipline Module](/archives/4.2.8-series/msyslog/#clock-discipline-module)
*   [Cryptographic Module](/archives/4.2.8-series/msyslog/#cryptographic-module)

* * *

#### Introduction

You have come here because you found a cryptic message in the system log. This page by no means lists all messages that might be found, since new ones come and old ones go. Generally, however, the most common ones will be found here. They are listed by program module and log severity code in bold: <code>**LOG_ERR**</code>, <code>**LOG_NOTICE**</code> and <code>**LOG_INFO**</code>.

Most of the time <code>**LOG_ERR**</code> messages are fatal, but often <code>ntpd</code> limps onward in the hopes of discovering more errors. The <code>**LOG_NOTICE**</code> messages usually mean the time has changed or some other condition that probably should be noticed. The <code>**LOG_INFO**</code> messages usually say something about the system operations, but do not affect the time.

In the following a <code>?</code> character stands for text in the message. The meaning should be clear from context.

* * *

#### Protocol Module

<code>**LOG_ERR**</code>

<code>**buffer overflow ?**</code>
: Fatal error. An input packet is too long for processing.

<code>**LOG_NOTICE**</code>

<code>**no reply; clock not set**</code>
: In <code>ntpdate</code> mode no servers have been found. The server(s) and/or network may be down. Standard debugging procedures apply.

<code>**LOG_INFO**</code>

<code>**proto_config: illegal item ?, value ?**</code>
: Program error. Bugs can be reported [here](/archives/4.2.8-series/bugs).

<code>**receive: autokey requires two-way communication**</code>
: Configuration error on the <code>broadcastclient</code> command.

<code>**receive: server _server_ maaximum rate exceeded**</code>
: A kiss-o'death packet has been received. The transmit rate is automatically reduced.

<code>**pps sync enabled**</code>
: The PPS signal has been detected and enabled.

<code>**transmit: encryption key ? not found**</code>
: The encryption key is not defined or not trusted.

<code>**precision = ? usec**</code>
: This reports the precision measured for this machine.

<code>**using 10ms tick adjustments**</code>
: Gotcha for some machines with dirty rotten clock hardware.

<code>**no servers reachable**</code>
: The system clock is running on internal batteries. The server(s) and/or network may be down.

* * *

#### Clock Discipline Module

<code>**LOG_ERR**</code>

<code>**time correction of ? seconds exceeds sanity limit (?); set clock manually to the correct UTC time.**</code>
: Fatal error. Better do what it says, then restart the daemon. Be advised NTP and Unix know nothing about local time zones. The clock must be set to Coordinated Universal Time (UTC). Believe it; by international agreement abbreviations are in French and descriptions are in English.

<code>**sigaction() fails to save SIGSYS trap: ?**</code> 
: <code>**sigaction() fails to restore SIGSYS trap: ?**</code>
: Program error. Bugs can be reported [here](/archives/4.2.8-series/bugs).

<code>**LOG_NOTICE**</code>

<code>**frequency error ? exceeds tolerance 500 PPM**</code>
: The hardware clock frequency error exceeds the rate the kernel can correct. This could be a hardware or a kernel problem.

<code>**time slew ? s**</code>
: The time error exceeds the step threshold and is being slewed to the correct time. You may have to wait a very long time.

<code>**time reset ? s**</code>
: The time error exceeds the step threshold and has been reset to the correct time. Computer scientists don't like this, but they can set the <code>ntpd -x</code> option and wait forever.

<code>**kernel time sync disabled ?**</code>
: The kernel reports an error. See the codes in the <code>timex.h</code> file.

<code>**pps sync disabled**</code>
: The PPS signal has died, probably due to a dead radio, broken wire or loose connector.

<code>**LOG_INFO**</code>

<code>**kernel time sync status ?**</code>
: For information only. See the codes in the <code>timex.h</code> file.

* * *

#### Cryptographic Module

<code>**LOG_ERR**</code>

<code>**cert_parse ?**</code>
: <code>**cert_sign ?**</code>
: <code>**crypto_cert ?**</code>
: <code>**crypto_encrypt ?**</code>
: <code>**crypto_gq ?**</code>
: <code>**crypto_iff ?**</code>
: <code>**crypto_key ?**</code>
: <code>**crypto_mv ?**</code>
: <code>**crypto_setup ?**</code>
: <code>**make_keys ?**</code>
: Usually fatal errors. These messages display error codes returned from the OpenSSL library. See the OpenSSL documentation for explanation.

<code>**crypto_setup: certificate ? is trusted, but not self signed.**</code>
: <code>**crypto_setup: certificate ? not for this host**</code>
: <code>**crypto_setup: certificate file ? not found or corrupt**</code>
: <code>**crypto_setup: host key file ? not found or corrupt**</code>
: <code>**crypto_setup: host key is not RSA key type**</code>
: <code>**crypto_setup: random seed file ? not found**</code>
: <code>**crypto_setup: random seed file not specified**</code>
: Fatal errors. These messages show problems during the initialization procedure.

<code>**LOG_INFO**</code>

<code>**cert_parse: expired ?**</code>
: <code>**cert_parse: invalid issuer ?**</code>
: <code>**cert_parse: invalid signature ?**</code>
: <code>**cert_parse: invalid subject ?**</code>
: There is a problem with a certificate. Operation cannot proceed until the problem is fixed. If the certificate is local, it can be regenerated using the <code>ntp-keygen</code> program. If it is held somewhere else, it must be fixed by the holder.

<code>**crypto\_?: defective key**</code>
: <code>**crypto\_?: invalid filestamp**</code>
: <code>**crypto\_?: missing challenge**</code>
: <code>**crypto\_?: scheme unavailable**</code>
: There is a problem with the identity scheme. Operation cannot proceed until the problem is fixed. Usually errors are due to misconfiguration or an orphan association. If the latter, <code>ntpd</code> will usually time out and recover by itself.

<code>**crypto_cert: wrong PEM type ?**</code>
: The certificate does not have MIME type <code>CERTIFICATE</code>. You are probably using the wrong type from OpenSSL or an external certificate authority.

<code>**crypto_ident: no compatible identity scheme found**</code>
: Configuration error. The server and client identity schemes are incompatible.

<code>**crypto_tai: kernel TAI update failed**</code>
: The kernel does not support this function. You may need a new kernel or patch.

<code>**crypto_tai: leapseconds file ? error ?**</code>
: The leapseconds file is corrupt. Obtain the latest file from <code>time.nist.gov</code>.