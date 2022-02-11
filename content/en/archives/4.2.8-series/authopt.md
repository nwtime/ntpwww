---
title: "Authentication Commands and Options"
type: archives
---

![gif](/archives/pic/alice44.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Our resident cryptographer; now you see him, now you don't.

Last update: 24-Jul-2018 07:27 UTC

* * *

#### Commands and Options

Unless noted otherwise, further information about these commands is on the [Authentication Support](/archives/4.2.8-series/authentic/) page.

<code>**automax [_logsec_]**</code>

: Specifies the interval between regenerations of the session key list used with the Autokey protocol, as a power of 2 in seconds. Note that the size of the key list for each association depends on this interval and the current poll interval. The default interval is 12 (about 1.1 hr). For poll intervals above the specified interval, a session key list with a single entry will be regenerated for every message sent. See the [Autokey Public Key Authentication](/archives/4.2.8-series/autokey/) page for further information.

<code>**controlkey _keyid_**</code>

: Specifies the key ID for the [<code>ntpq</code>](/archives/4.2.8-series/ntpq/) utility, which uses the standard protocol defined in [RFC-1305](/reflib/rfc/rfc1305/rfc1305b.pdf). The <code>_keyid_</code> argument is the key ID for a [trusted key](/archives/4.2.8-series/authopt/), where the value can be in the range 1 to 65535, inclusive.

<code>**crypto [digest _digest_] [host _name_] [ident _name_] [pw _password_] [randfile _file_]**</code>

: This command activates the Autokey public key cryptography and loads the required host keys and certificate. If one or more files are unspecified, the default names are used. Unless the complete path and name of the file are specified, the location of a file is relative to the keys directory specified in the <code>keysdir</code> configuration command with default <code>/usr/local/etc</code>. See the [Autokey Public Key Authentication](/archives/4.2.8-series/autokey/) page for further information. Following are the options.

<code>digest _digest_</code>

: Specify the message digest algorithm, with default MD5. If the OpenSSL library is installed, <code>_digest_</code> can be any message digest algorithm supported by the library. The current selections are: <code>MD2</code>, <code>MD4</code>, <code>MD5,</code> <code>MDC2</code>, <code>RIPEMD160</code>, <code>SHA</code> and <code>SHA1</code>. All participants in an Autokey subnet must use the same algorithm. The Autokey message digest algorithm is separate and distinct from the symmetric key message digest algorithm.
> Note: If compliance with FIPS 140-2 is required, the algorithm must be ether <code>SHA</code> or <code>SHA1</code>.

<code>host _name_</code>

: Specify the cryptographic media names for the host, sign and certificate files. If this option is not specified, the default name is the string returned by the Unix <code>gethostname()</code> routine.

> Note: In the latest Autokey version, this option has no effect other than to change the cryptographic media file names.

<code>ident _group_</code>

: Specify the cryptographic media names for the identity scheme files. If this option is not specified, the default name is the string returned by the Unix <code>gethostname()</code> routine.

> Note: In the latest Autokey version, this option has no effect other than to change the cryptographic media file names.

<code>pw _password_</code>

: Specifies the password to decrypt files previously encrypted by the <code>ntp-keygen</code> program with the <code>-p</code> option. If this option is not specified, the default password is the string returned by the Unix <code>gethostname()</code> routine.

<code>randfile _file_</code>

: Specifies the location of the random seed file used by the OpenSSL library. The defaults are described on the [<code>ntp-keygen</code>](/archives/4.2.8-series/keygen/) page.

<code>**ident _group_**</code>

: Specifies the group name for ephemeral associations mobilized by broadcast and symmetric passive modes. See the [Autokey Public-Key Authentication](/archives/4.2.8-series/autokey/) page for further information.

<code>**keys _path_**</code>

: Specifies the complete directory path for the key file containing the key IDs, key types and keys used by <code>ntpd</code>, <code>ntpq</code> and <code>ntpdc</code> when operating with symmetric key cryptography. The format of the keyfile is described on the [<code>ntp-keygen</code>](/archives/4.2.8-series/keygen/) page. This is the same operation as the <code>-k</code> command line option. Note that the directory path for Autokey cryptographic media is specified by the <code>keysdir</code> command.

<code>**keysdir _path_**</code>

: Specifies the complete directory path for the Autokey cryptographic keys, parameters and certificates. The default is <code>/usr/local/etc/</code>. Note that the path for the symmetric keys file is specified by the <code>keys</code> command.

<code>**requestkey _keyid_**</code>

: Specifies the key ID for the [<code>ntpdc</code>](/archives/4.2.8-series/ntpdc/) utility program, which uses a proprietary protocol specific to this implementation of <code>ntpd</code>. The <code>_keyid_</code> argument is a key ID for a [trusted key](/archives/4.2.8-series/authopt/), in the range 1 to 65535, inclusive.

<code>**revoke [_logsec_]**</code>

: Specifies the interval between re-randomization of certain cryptographic values used by the Autokey scheme, as a power of 2 in seconds, with default 17 (36 hr). See the [Autokey Public-Key Authentication](/archives/4.2.8-series/autokey/) page for further information.

<code>**trustedkey [_keyid_ | (_lowid_ ... _highid_)] [...]**</code>

: Specifies the key ID(s) which are trusted for the purposes of authenticating peers with symmetric key cryptography. Key IDs used to authenticate <code>ntpq</code> and <code>ntpdc</code> operations must be listed here and additionally be enabled with [controlkey](/archives/4.2.8-series/authopt/) and/or [requestkey](/archives/4.2.8-series/authopt/). The authentication procedure for time transfer requires that both the local and remote NTP servers employ the same key ID and secret for this purpose, although different keys IDs may be used with different servers. Ranges of trusted key IDs may be specified: <code>trustedkey (1 ... 19) 1000 (100 ... 199)</code> enables the lowest 120 key IDs which start with the digit 1. The spaces surrounding the ellipsis are required when specifying a range.