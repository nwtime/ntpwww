---
title: "Authentication Options"
type: archives
---

#### Table of Contents

*   [Authentication Support](/archives/3-5.93e/authopt/#authentication-support)
*   [Authentication Commands](/archives/3-5.93e/authopt/#authentication-commands)
*   [Authentication Key File Format](/archives/3-5.93e/authopt/#authentication-key-file-format)

* * *

#### Authentication Support

The NTP standard specifies an extension which provides cryptographic authentication of received NTP packets. This is implemented in <tt>xntpd</tt> using the DES or MD5 algorithms to compute a digital signature, or message digest. The specification allows any one of possibly 4 billion keys, numbered with 32-bit key identifiers, to be used to authenticate an association. The servers involved in an association must agree on the key and key identifier used to authenticate their messages. 

Keys and related information are specified in a key file, which should be exchanged and stored using secure procedures beyond the scope of the protocol. There are three classes of keys involved in the current implementation. One class is used for ordinary NTP associations, another for the [ntpq](/archives/3-5.93e/ntpq) utility program and the third for the [xntpdc](/archives/3-5.93e/xntpdc) utility program. 

* * *

#### Authentication Commands

<dt id="keys"><tt>keys _keyfile_</tt></dt>

Specifies the file name containing the encryption keys and key identifiers used by <tt>xntpd</tt>, <tt>ntpq</tt> and <tt>xntpdc</tt> when operating in authenticated mode. The format of this file is described later in this document. 

<dt id="trustedkey"><tt>trustedkey [_key_] [...]</tt></dt>

Specifies the encryption key identifiers which are trusted for the purposes of authenticating peers suitable for synchronization. The authentication procedures require that both the local and remote servers share the same key and key identifier for this purpose, although different keys can be used with different servers. The <tt>key</tt> arguments are 32-bit unsigned integers. Note that NTP key 0 is fixed and globally known. If meaningful authentication is to be performed the 0 key should not be trusted.  

<dt id="requestkey"><tt>requestkey _key_</tt></dt>

Specifies the key identifier to use with the [<tt>xntpdc</tt>](/archives/3-5.93e/xntpdc) program, which uses a proprietary protocol specific to this implementation of <tt>xntpd</tt>. This program is useful to diagnose and repair problems that affect <tt>xntpd</tt> operation. The key argument to this command is a 32-bit unsigned integer. If no <tt>requestkey</tt> command is included in the configuration file, or if the keys don't match, such requests will be ignored. 

<dt id="controlkey"><tt>controlkey _key_</tt></dt>

Specifies the key identifier to use with the [<tt>ntpq</tt>](/archives/3-5.93e/ntpq) utility, which uses the standard protocol defined in RFC-1305. This program is useful to diagnose and repair problems that affect <tt>xntpd</tt> operation. The <tt>_key_</tt> argument to this command is a 32-bit unsigned integer. If no <tt>requestkey</tt> command is included in the configuration file, or if the keys don't match, such requests will be ignored. 

* * *

#### Authentication Key File Format

In the case of DES, the keys are 56 bits long with, depending on type, a parity check on each byte. In the case of MD5, the keys are 64 bits (8 bytes). <tt>xntpd</tt> reads its keys from a file specified using the <tt>-k</tt> command line option or the <tt>keys</tt> statement in the configuration file. While key number 0 is fixed by the NTP standard (as 56 zero bits) and may not be changed, one or more of the keys numbered 1 through 15 may be arbitrarily set in the keys file.

The key file uses the same comment conventions as the configuration file. Key entries use a fixed format of the form

<tt>_keyno type key_</tt>

where <tt>_keyno_</tt> is a positive integer, <tt>_type_</tt> is a single character which defines the key format, and <tt>_key_</tt> is the key itself.

The key may be given in one of three different formats, controlled by the <tt>_type_</tt> character. The three key types, and corresponding formats, are listed following.

<dt><tt>S</tt></dt>

The key is a 64-bit hexadecimal number in the format specified in the DES specification; that is, the high order seven bits of each octet are used to form the 56-bit key while the low order bit of each octet is given a value such that odd parity is maintained for the octet. Leading zeroes must be specified (i.e., the key must be exactly 16 hex digits long) and odd parity must be maintained. Hence a zero key, in standard format, would be given as <tt>0101010101010101</tt>.

<dt><tt>N</tt></dt>

The key is a 64-bit hexadecimal number in the format specified in the NTP standard. This is the same as the DES format, except the bits in each octet have been rotated one bit right so that the parity bit is now the high order bit of the octet. Leading zeroes must be specified and odd parity must be maintained. A zero key in NTP format would be specified as <tt>8080808080808080</tt>.

<dt><tt>A</tt></dt>

The key is a 1-to-8 character ASCII string. A key is formed from this by using the low order 7 bits of each ASCII character in the string, with zeroes added on the right when necessary to form a full width 56-bit key, in the same way that encryption keys are formed from Unix passwords.

<dt><tt>M</tt></dt>

The key is a 1-to-8 character ASCII string, using the MD5 authentication scheme. Note that both the keys and the authentication schemes (DES or MD5) must be identical between a set of peers sharing the same key number.

Note that the keys used by the <tt>ntpq</tt> and <tt>xntpdc</tt> programs are checked against passwords requested by the programs and entered by hand, so it is generally appropriate to specify these keys in ASCII format.