---
title: "ntpd System Log Messages"
type: archives
---

![gif](/archives/pic/alice47.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

The mushroom knows all the error codes, which is more than most of us do.

Last update:  02:23 UTC Saturday, February 01, 2003

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.0/msyslog/#introduction)
*   [Protocol Module](/archives/4.2.0/msyslog/#protocol-module)
*   [Clock Discipline Module](/archives/4.2.0/msyslog/#clock-discipline-module)
*   [Cryptographic Module](/archives/4.2.0/msyslog/#cryptographic-module)

* * *

#### Introduction

You have come here because you found a cryptic message in the system log. This page by no means lists all messages that might be found, since new ones come and old ones go. Generally, however, the most common ones will be found here. They are listed by program module and log severity code in bold: <tt>**LOG_ERR**</tt>, **<tt>LOG_NOTICE</tt>** and <tt>**LOG_INFO**</tt>.

Most of the time **<tt>LOG_ERR</tt>** messages are fatal, but often <tt>ntpd</tt> limps onward in the hopes of discovering more errors. The <tt>**LOG_NOTICE**</tt> messages usually mean the time has changed or some other condition that probably should be noticed. The <tt>**LOG_INFO**</tt> messages usually say something about the system operations, but do not affect the time.

In the following a `?` character stands for text in the message. The meaning should be clear from context.

* * *

#### Protocol Module

<tt>**LOG_ERR**</tt>

<dt><tt>buffer overflow ?</tt></dt>

Fatal error. An input packet is too long for processing.

<tt>**LOG_NOTICE**</tt>

<dt><tt>no reply; clock not set</tt></dt>

In <tt>ntpdate</tt> mode no servers have been found. The server(s) and/or network may be down. Standard debugging procedures apply.

<tt>**LOG_INFO**</tt>

<dt><tt>proto_config: illegal item ?, value ?</tt></dt>

Program error. Please report to bugs@ntp.org. 

<dt><tt>pps sync enabled</tt></dt>

The PPS signal has been detected and enabled.

<dt><tt>transmit: encryption key ? not found</tt></dt>

The key cache is inconsistent. Please report to bugs@ntp.org. 

<dt><tt>precision = ? usec</tt></dt>

This reports the precision measured for this machine.

<dt><tt>using 10ms tick adjustments</tt></dt>

Gotcha for some machines with dirty rotten clock hardware.

<dt><tt>no servers reachable</tt></dt>

The system clock is running on internal batteries. The server(s) and/or network may be down.

* * *

#### Clock Discipline Module

<tt>**LOG_ERR**</tt>

<dt><tt>time correction of ? seconds exceeds sanity limit (?); set clock manually to the correct UTC time</tt>.</dt>

Fatal error. Better do what it says, then restart the daemon. Be advised NTP and Unix know nothing about local time zones. The clock must be set to Coordinated Universal Time (UTC). Believe it; by international agreement abbreviations are in French and descriptions are in English.

<dt><tt>sigaction() fails to save SIGSYS trap: ? </tt></dt>

<dt><tt>sigaction() fails to restore SIGSYS trap: ?</tt></dt>

Program error. Please report to bugs@ntp.org.

<tt>**LOG_NOTICE**</tt>

<dt><tt>frequency error ? exceeds tolerance 500 PPM</tt></dt>

The hardware clock frequency error exceeds the rate the kernel can correct. This could be a hardware or a kernel problem.

<dt><tt>time slew ? s</tt></dt>

The time error exceeds the step threshold and is being slewed to the correct time. You may have to wait a very long time.

<dt><tt>time reset ? s</tt></dt>

The time error exceeds the step threshold and has been reset to the correct time. Computer scientists don't like this, but they can set the <tt>ntpd -x</tt> option and wait forever.

<dt><tt>kernel time sync disabled ?</tt></dt>

The kernel reports an error. See the codes in the <tt>timex.h</tt> file.

<dt><tt>pps sync disabled</tt></dt>

The PPS signal has died, probably due to a dead radio, broken wire or loose connector.

<tt>**LOG_INFO**</tt>

<dt><tt>kernel time sync status ?</tt></dt>

For information only. See the codes in the <tt>timex.h</tt> file.

* * *

#### Cryptographic Module

<tt>**LOG_ERR**</tt>

<tt>cert_parse ?</tt>

<tt>cert_sign ?</tt>

<tt>crypto_cert ?</tt>

<tt>crypto_encrypt ?</tt>

<tt>crypto_gq ?</tt>

<tt>crypto_iff ?</tt>

<tt>crypto_key ?</tt>

<tt>crypto_mv ?</tt>

<tt>crypto_setup ?</tt>

<tt>make_keys ?</tt>

Usually fatal errors. These messages display error codes returned from the OpenSSL library. See the OpenSSL documentation for explanation.

<tt>crypto_setup: certificate ? is trusted, but not self signed.</tt>

<tt>crypto_setup: certificate ? not for this host</tt>

<tt>crypto_setup: certificate file ? not found or corrupt</tt>

<tt>crypto_setup: host key file ? not found or corrupt</tt>

<tt>crypto_setup: host key is not RSA key type</tt>

<tt>crypto_setup: random seed file ? not found</tt>

<tt>rypto_setup: random seed file not specified</tt>

Fatal errors. These messages show problems during the initialization procedure.

<tt>**LOG_INFO**</tt>

<tt>cert_parse: expired ?</tt>

<tt>cert_parse: invalid issuer ?</tt>

<tt>cert_parse: invalid signature ?</tt>

<tt>cert_parse: invalid subject ?</tt>

There is a problem with a certificate. Operation cannot proceed until the problem is fixed. If the certificate is local, it can be regenerated using the <tt>ntp-keygen</tt> program. If it is held somewhere else, it must be fixed by the holder.

<tt>crypto_?: defective key</tt>

<tt>crypto_?: invalid filestamp</tt>

<tt>crypto_?: missing challenge</tt>

<tt>crypto_?: scheme unavailable</tt>

There is a problem with the identity scheme. Operation cannot proceed until the problem is fixed. Usually errors are due to misconfiguration or an orphan association. If the latter, <tt>ntpd</tt> will usually time out and recover by itself.

<dt><tt>crypto_cert: wrong PEM type ?</tt></dt>

The certificate does not have MIME type <tt>CERTIFICATE</tt>. You are probably using the wrong type from OpenSSL or an external certificate authority.

<dt><tt>crypto_ident: no compatible identity scheme found</tt></dt>

Configuration error. The server and client identity schemes are incompatible.

<dt><tt>crypto_tai: kernel TAI update failed</tt></dt>

The kernel does not support this function. You may need a new kernel or patch.

<dt><tt>crypto_tai: leapseconds file ? error ?</tt></dt>

The leapseconds file is corrupt. Obtain the latest file from <tt>time.nist.gov</tt>.