---
title: "Authentication Options"
type: archives
noindex: true
---

#### Table of Contents

*   [Authentication Support](/documentation/3-5.93e/authopt/#authentication-support)
*   [Authentication Commands](/documentation/3-5.93e/authopt/#authentication-commands)
*   [Authentication Key File Format](/documentation/3-5.93e/authopt/#authentication-key-file-format)

* * *

#### Authentication Support

The NTP standard specifies an extension which provides cryptographic authentication of received NTP packets. This is implemented in <code>xntpd</code> using the DES or MD5 algorithms to compute a digital signature, or message digest. The specification allows any one of possibly 4 billion keys, numbered with 32-bit key identifiers, to be used to authenticate an association. The servers involved in an association must agree on the key and key identifier used to authenticate their messages. 

Keys and related information are specified in a key file, which should be exchanged and stored using secure procedures beyond the scope of the protocol. There are three classes of keys involved in the current implementation. One class is used for ordinary NTP associations, another for the [ntpq](/documentation/3-5.93e/ntpq/) utility program and the third for the [xntpdc](/documentation/3-5.93e/xntpdc/) utility program. 

* * *

#### Authentication Commands

<code>**keys _keyfile_**</code>

: Specifies the file name containing the encryption keys and key identifiers used by <code>xntpd</code>, <code>ntpq</code> and <code>xntpdc</code> when operating in authenticated mode. The format of this file is described later in this document. 

<code>**trustedkey [_key_] [...]**</code>

: Specifies the encryption key identifiers which are trusted for the purposes of authenticating peers suitable for synchronization. The authentication procedures require that both the local and remote servers share the same key and key identifier for this purpose, although different keys can be used with different servers. The <code>key</code> arguments are 32-bit unsigned integers. Note that NTP key 0 is fixed and globally known. If meaningful authentication is to be performed the 0 key should not be trusted.  

<code>**requestkey _key_**</code>

: Specifies the key identifier to use with the [<code>xntpdc</code>](/documentation/3-5.93e/xntpdc/) program, which uses a proprietary protocol specific to this implementation of <code>xntpd</code>. This program is useful to diagnose and repair problems that affect <code>xntpd</code> operation. The key argument to this command is a 32-bit unsigned integer. If no <code>requestkey</code> command is included in the configuration file, or if the keys don't match, such requests will be ignored. 

<code>**controlkey _key_**</code>

: Specifies the key identifier to use with the [<code>ntpq</code>](/documentation/3-5.93e/ntpq/) utility, which uses the standard protocol defined in RFC-1305. This program is useful to diagnose and repair problems that affect <code>xntpd</code> operation. The <code>_key_</code> argument to this command is a 32-bit unsigned integer. If no <code>requestkey</code> command is included in the configuration file, or if the keys don't match, such requests will be ignored. 

* * *

#### Authentication Key File Format

In the case of DES, the keys are 56 bits long with, depending on type, a parity check on each byte. In the case of MD5, the keys are 64 bits (8 bytes). <code>xntpd</code> reads its keys from a file specified using the <code>-k</code> command line option or the <code>keys</code> statement in the configuration file. While key number 0 is fixed by the NTP standard (as 56 zero bits) and may not be changed, one or more of the keys numbered 1 through 15 may be arbitrarily set in the keys file.

The key file uses the same comment conventions as the configuration file. Key entries use a fixed format of the form

<code>_keyno type key_</code>

where <code>_keyno_</code> is a positive integer, <code>_type_</code> is a single character which defines the key format, and <code>_key_</code> is the key itself.

The key may be given in one of three different formats, controlled by the <code>_type_</code> character. The three key types, and corresponding formats, are listed following.

<code>**S**</code>

: The key is a 64-bit hexadecimal number in the format specified in the DES specification; that is, the high order seven bits of each octet are used to form the 56-bit key while the low order bit of each octet is given a value such that odd parity is maintained for the octet. Leading zeroes must be specified (i.e., the key must be exactly 16 hex digits long) and odd parity must be maintained. Hence a zero key, in standard format, would be given as <code>0101010101010101</code>.

<code>**N**</code>

: The key is a 64-bit hexadecimal number in the format specified in the NTP standard. This is the same as the DES format, except the bits in each octet have been rotated one bit right so that the parity bit is now the high order bit of the octet. Leading zeroes must be specified and odd parity must be maintained. A zero key in NTP format would be specified as <code>8080808080808080</code>.

<code>**A**</code>

: The key is a 1-to-8 character ASCII string. A key is formed from this by using the low order 7 bits of each ASCII character in the string, with zeroes added on the right when necessary to form a full width 56-bit key, in the same way that encryption keys are formed from Unix passwords.

<code>**M**</code>

: The key is a 1-to-8 character ASCII string, using the MD5 authentication scheme. Note that both the keys and the authentication schemes (DES or MD5) must be identical between a set of peers sharing the same key number.

Note that the keys used by the <code>ntpq</code> and <code>xntpdc</code> programs are checked against passwords requested by the programs and entered by hand, so it is generally appropriate to specify these keys in ASCII format.