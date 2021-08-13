---
title: "Authentication Commands and Options"
type: archives
---

![gif](/archives/pic/alice44.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

Our resident cryptographer; now you see him, now you don't.

Last update: 24-Jul-2018 07:27 UTC

* * *

#### Commands and Options

Unless noted otherwise, further information about these commands is on the [Authentication Support](/archives/4.2.8-series/authentic) page.

<dt id="automax"><tt>automax [_logsec_]</tt></dt>

Specifies the interval between regenerations of the session key list used with the Autokey protocol, as a power of 2 in seconds. Note that the size of the key list for each association depends on this interval and the current poll interval. The default interval is 12 (about 1.1 hr). For poll intervals above the specified interval, a session key list with a single entry will be regenerated for every message sent. See the [Autokey Public Key Authentication](/archives/4.2.8-series/autokey) page for further information.

<dt id="controlkey"><tt>controlkey _keyid_</tt></dt>

Specifies the key ID for the [<tt>ntpq</tt>](/archives/4.2.8-series/ntpq) utility, which uses the standard protocol defined in RFC-1305. The <tt>_keyid_</tt> argument is the key ID for a [trusted key](/archives/4.2.8-series/authopt/#trustedkey), where the value can be in the range 1 to 65535, inclusive.

<dt id="crypto"><tt>crypto [digest _digest_] [host _name_] [ident _name_] [pw _password_] [randfile _file_]</tt></dt>

This command activates the Autokey public key cryptography and loads the required host keys and certificate. If one or more files are unspecified, the default names are used. Unless the complete path and name of the file are specified, the location of a file is relative to the keys directory specified in the <tt>keysdir</tt> configuration command with default <tt>/usr/local/etc</tt>. See the [Autokey Public Key Authentication](/archives/4.2.8-series/autokey) page for further information. Following are the options.

<dt><tt>digest</tt> _digest_</dt>

Specify the message digest algorithm, with default MD5. If the OpenSSL library is installed, <tt>_digest_</tt> can be any message digest algorithm supported by the library. The current selections are: <tt>MD2</tt>, <tt>MD4</tt>, <tt>MD5,</tt> <tt>MDC2</tt>, <tt>RIPEMD160</tt>, <tt>SHA</tt> and <tt>SHA1</tt>. All participants in an Autokey subnet must use the same algorithm. The Autokey message digest algorithm is separate and distinct from the symmetric key message digest algorithm. Note: If compliance with FIPS 140-2 is required, the algorithm must be ether <tt>SHA</tt> or <tt>SHA1</tt>.

<dt><tt>host _name_</tt></dt>

Specify the cryptographic media names for the host, sign and certificate files. If this option is not specified, the default name is the string returned by the Unix <tt>gethostname()</tt> routine.

<span class="style1">Note: In the latest Autokey version, this option has no effect other than to change the cryptographic media file names.</span>

<dt><tt>ident _group_</tt></dt>

Specify the cryptographic media names for the identity scheme files. If this option is not specified, the default name is the string returned by the Unix <tt>gethostname()</tt> routine.

<span class="style1">Note: In the latest Autokey version, this option has no effect other than to change the cryptographic media file names.</span>

<dt><tt>pw _password_</tt></dt>

Specifies the password to decrypt files previously encrypted by the <tt>ntp-keygen</tt> program with the <tt>-p</tt> option. If this option is not specified, the default password is the string returned by the Unix <tt>gethostname()</tt> routine.

<dt><tt>randfile _file_</tt></dt>

Specifies the location of the random seed file used by the OpenSSL library. The defaults are described on the [<tt>ntp-keygen</tt> page](/archives/4.2.8-series/keygen).

<dt id="ident"><tt>ident _group_</tt></dt>

Specifies the group name for ephemeral associations mobilized by broadcast and symmetric passive modes. See the [Autokey Public-Key Authentication](/archives/4.2.8-series/autokey) page for further information.

<dt id="keys"><tt>keys _path_</tt></dt>

Specifies the complete directory path for the key file containing the key IDs, key types and keys used by <tt>ntpd</tt>, <tt>ntpq</tt> and <tt>ntpdc</tt> when operating with symmetric key cryptography. The format of the keyfile is described on the [<tt>ntp-keygen</tt> page](/archives/4.2.8-series/keygen). This is the same operation as the <tt>-k</tt> command line option. Note that the directory path for Autokey cryptographic media is specified by the <tt>keysdir</tt> command.

<dt id="keysdir"><tt>keysdir _path_</tt></dt>

Specifies the complete directory path for the Autokey cryptographic keys, parameters and certificates. The default is <tt>/usr/local/etc/</tt>. Note that the path for the symmetric keys file is specified by the <tt>keys</tt> command.

<dt id="requestkey"><tt>requestkey _keyid_</tt></dt>

Specifies the key ID for the [<tt>ntpdc</tt>](/archives/4.2.8-series/ntpdc) utility program, which uses a proprietary protocol specific to this implementation of <tt>ntpd</tt>. The <tt>_keyid_</tt> argument is a key ID for a [trusted key](/archives/4.2.8-series/authopt/#trustedkey), in the range 1 to 65535, inclusive.

<dt id="revoke"><tt>revoke [_logsec_]</tt></dt>

Specifies the interval between re-randomization of certain cryptographic values used by the Autokey scheme, as a power of 2 in seconds, with default 17 (36 hr). See the [Autokey Public-Key Authentication](/archives/4.2.8-series/autokey) page for further information.

<dt id="trustedkey"><tt>trustedkey [_keyid_ | (_lowid_ ... _highid_)] [...]</tt></dt>

Specifies the key ID(s) which are trusted for the purposes of authenticating peers with symmetric key cryptography. Key IDs used to authenticate <tt>ntpq</tt> and <tt>ntpdc</tt> operations must be listed here and additionally be enabled with [controlkey](/archives/4.2.8-series/authopt/#controlkey) and/or [requestkey](/archives/4.2.8-series/authopt/#requestkey). The authentication procedure for time transfer requires that both the local and remote NTP servers employ the same key ID and secret for this purpose, although different keys IDs may be used with different servers. Ranges of trusted key IDs may be specified: <tt>trustedkey (1 ... 19) 1000 (100 ... 199)</tt> enables the lowest 120 key IDs which start with the digit 1. The spaces surrounding the ellipsis are required when specifying a range.