---
title: "ntp-genkeys - generate public and private keys"
type: archives
noindex: true
---

![gif](/archives/pic/alice23.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Alice holds the key.

* * *

#### Table of Contents

*   [Synopsis](/archives/4.1.0/genkeys/#synopsis)
*   [Description](/archives/4.1.0/genkeys/#description)
*   [Symmetric Key File Format](/archives/4.1.0/genkeys/#symmetric-key-file-format)
*   [Files](/archives/4.1.0/genkeys/#files)
*   [Bugs](/archives/4.1.0/genkeys/#bugs)

* * *

#### Synopsis

<code>ntp-genkeys</code>

* * *

#### Description

This program generates random keys used by either or both the NTPv3/NTPv4 symmetric key or the NTPv4 public key (Autokey) cryptographic authentication schemes. By default the program generates the <code>ntp.keys</code> file containing 16 random symmetric keys. In addition, if the <code>rsaref20</code> package is configured for the software build, the program generates cryptographic values used by the Autokey scheme. These values are incorporated as a set of three files, <code>ntpkey</code> containing the RSA private key, <code>ntpkey\__host_</code> containing the RSA public key, where <code>_host_</code> is the DNS name of the generating machine, and <code>ntpkey_dh</code> containing the parameters for the Diffie-Hellman key-agreement algorithm. All files and are in printable ASCII format. A timestamp in NTP seconds is appended to each. Since the algorithms are seeded by the system clock, each run of this program produces a different file and file name.

The <code>ntp.keys</code> file contains 16 MD5 keys. Each key consists of 16 characters randomized over the ASCII 95-character printing subset. The file is read by the daemon at the location specified by the <code>keys</code> configuration file command and made visible only to root. An additional key consisting of a easily remembered password should be added by hand for use with the <code>ntpq</code> and <code>ntpdc</code> programs. The file must be distributed by secure means to other servers and clients sharing the same security compartment. While the key identifiers for MD5 and DES keys must be in the range 1-65534, inclusive, the <code>ntp-genkeys</code> program uses only the identifiers from 1 to 16. The key identifier for each association is specified as the key argument in the <code>server</code> or peer configuration file command.

The <code>ntpkey</code> file contains the RSA private key. It is read by the daemon at the location specified by the <code>privatekey</code> argument of the <code>crypto</code> configuration file command and made visible only to root. This file is useful only to the machine that generated it and never shared with any other daemon or application program.

The <code>ntpkey\__host_</code> file contains the RSA public key, where <code>_host_</code> is the DNS name of the host that generated it. The file is read by the daemon at the location specified by the <code>publickey</code> argument to the <code>server</code> or <code>peer</code> configuration file command. This file can be widely distributed and stored without using secure means, since the data are public values.

The <code>ntp_dh</code> file contains two Diffie-Hellman parameters: the prime modulus and the generator. The file is read by the daemon at the location specified by the <code>dhparams</code> argument of the <code>crypto</code> configuration file command. The file can be distributed by insecure means to other servers and clients sharing the same key agreement compartment, since the data are public values.

The file formats begin with two lines, the first containing the generating system DNS name and the second the datestamp. Lines beginning with <code>#</code> are considered comments and ignored by the daemon. In the <code>ntp.keys</code> file, the next 16 lines contain the MD5 keys in order. If necessary, this file can be further customized by an ordinary text editor. The format is described in the following section. In the <code>ntpkey</code> and <code>ntpkey\__host_</code> files, the next line contains the modulus length in bits followed by the key as a PEM encoded string. In the <code>ntpkey_dh</code> file, the next line contains the prime length in bytes followed by the prime as a PEM encoded string, and the next and final line contains the generator length in bytes followed by the generator as a PEM encoded string.

Note: See the file <code>./source/rsaref.h</code> in the <code>rsaref20</code> package for explanation of return values, if necessary.

#### Symmetric Key File Format

In the case of DES, the keys are 56 bits long with, depending on type, a parity check on each byte. In the case of MD5, the keys are 64 bits (8 bytes). <code>ntpd</code> reads its keys from a file specified using the <code>-k</code> command line option or the <code>keys</code> statement in the configuration file. While key number 0 is fixed by the NTP standard (as 56 zero bits) and may not be changed, one or more of the keys numbered 1 through 15 may be arbitrarily set in the keys file.

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

Note that the keys used by the <code>ntpq</code> and <code>ntpdc</code> programs are checked against passwords requested by the programs and entered by hand, so it is generally appropriate to specify these keys in ASCII format.

* * *

#### Files

The RSA Laboratories package <code>rsaref20</code> of cryptographic routines is necessary in order to build and use this program. 

#### Bugs

It can take quite a while to generate the RSA public/private key pair and Diffie-Hellman parameters, from a few seconds on a modern workstation to several minutes on older machines.