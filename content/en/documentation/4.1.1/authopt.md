---
title: "Authentication Options"
type: archives
noindex: true
---

![gif](/archives/pic/alice44.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Our resident cryptographer; now you see him, now you don't.

* * *

#### Table of Contents

*   [Authentication Support](/archives/4.1.1/authopt/#authentication-support)
*   [Symmetric Key Scheme](/archives/4.1.1/authopt/#symmetric-key-scheme)
*   [Public Key Scheme](/archives/4.1.1/authopt/#public-key-scheme)
*   [Leapseconds Table](/archives/4.1.1/authopt/#leapseconds-table)
*   [Key Management](/archives/4.1.1/authopt/#key-management)
*   [Authentication Commands](/archives/4.1.1/authopt/#authentication-commands)
*   [Files](/archives/4.1.1/authopt/#files)
*   [Bugs](/archives/4.1.1/authopt/#bugs)

* * *

#### Authentication Support

Authentication support allows the NTP client to verify that the server is in fact known and trusted and not an intruder intending accidentally or on purpose to masquerade as that server. The NTPv3 specification RFC-1305 defines an scheme which provides cryptographic authentication of received NTP packets. Originally, this was done using the Data Encryption Standard (DES) algorithm operating in Cipher Block Chaining (CBC) mode, commonly called
DES-CBC. Subsequently, this was augmented by the RSA Message Digest 5 (MD5) algorithm using a private key, commonly called keyed-MD5. Either algorithm computes a message digest, or one-way hash, which can be used to verify the server has the correct private key and key identifier.

NTPv4 retains the NTPv3 schemes, properly described as symmetric-key cryptography and, in addition, provides a new Autokey scheme based on public-key cryptography. Public-key cryptography is generally considered more secure than symmetric-key cryptography, since the security is based on a private value which is generated by each server and never revealed. With Autokey all key distribution and management functions involve only public values, which considerably simplifies key distribution and storage.

Authentication is configured separately for each association using the <code>key</code> or <code>autokey</code> subcommands on the <code>peer</code>, <code>server</code>, <code>broadcast</code> and <code>manycastclient</code> commands as described in the [Configuration Options](/archives/4.1.1/config/) page. The authentication
options described below specify the suite of keys, select the key for each configured association and manage the configuration operations.

The <code>auth</code> flag controls whether new associations or remote configuration commands require cryptographic authentication. This flag can be set or reset by the <code>enable</code> and <code>disable</code> configuration commands and also by remote configuration commands sent by a <code>ntpdc</code> program running in another machine. If this flag is enabled, which is the default case, new broadcast client and symmetric passive associations and remote configuration commands must be cryptographically authenticated using either symmetric-key or public-key schemes. If this flag is disabled, these operations are effective even if not cryptographic authenticated. It should be understood that operating in the latter mode invites a significant vulnerability where a rogue hacker can seriously disrupt client timekeeping.

In networks with firewalls and large numbers of broadcast clients it may be acceptable to disable authentication, since that avoids key distribution and simplifies network maintenance. However, when the configuration file contains host names, or when a server or client is configured remotely, host names are resolved using the DNS and a separate name resolution process. In order to protect against bogus name server messages, name resolution messages are authenticated using an internally generated key which is normally invisible to the user. However, if cryptographic support is disabled, the name resolution process will fail. This can be avoided either by specifying IP addresses instead of host names, which is generally inadvisable, or by enabling the flag for
name resolution and disabled it once the name resolution process is complete.

An attractive alternative where multicast support is available is manycast mode, in which clients periodically troll for servers. Cryptographic authentication in this mode uses public-key schemes as described below. The principle advantage of this manycast mode is that potential servers need not be configured in advance, since the client finds them during regular operation, and the configuration files for all clients can be identical.

In addition to the default symmetric-key cryptographic support, support for public-key cryptography is available if the requisite <code>rsaref20</code> software distribution has been installed before building the distribution. Public-key cryptography provides secure authentication of servers without compromising accuracy and stability. The security model and protocol schemes for both symmetric-key and public-key cryptography are described below.

* * *

#### Symmetric Key Scheme

The original RFC-1305 specification allows any one of possibly 65,534 keys, each distinguished by a 32-bit key identifier, to authenticate an association. The servers and clients involved must agree on the key and key identifier to authenticate NTP packets. Keys and related information are specified in a key file, usually called <code>ntp.keys</code>, which must be distributed and stored using secure means beyond the scope of the NTP protocol itself. Besides the keys used for ordinary NTP associations, additional keys can be used as passwords for the [ntpq](/archives/4.1.1/ntpq/) and [ntpdc](/archives/4.1.1/ntpdc/) utility programs. 

When <code>ntpd</code> is first started, it reads the key file specified in the <code>keys</code> configuration command and installs the keys in the key cache. However, individual keys must be activated with the <code>trustedkey</code> command before use. This allows, for instance, the installation of possibly several batches of keys and then activating or deactivating each batch remotely using <code>ntpdc</code>. This also provides a revocation capability that can be used if a key becomes compromised. The <code>requestkey</code> command selects the key used as the password for the <code>ntpdc</code> utility, while the <code>controlkey</code> command selects the key used as the password for the <code>ntpq</code> utility.

* * *

#### Public Key Scheme

The original NTPv3 authentication scheme described in RFC-1305 continues to be supported; however, in NTPv4 an additional authentication scheme called Autokey is available. It uses MD5 message digest, RSA public-key signature and Diffie-Hellman key agreement algorithms available from several sources, but not included in the NTPv4 software distribution. In order to be effective, the <code>rsaref20</code> package must be installed as described in the <code>README.rsa</code> file. Once installed, the configure and build process automatically detects it and compiles the routines required. The Autokey scheme has several modes of operation corresponding to the various NTP modes supported. RSA signatures with timestamps are used in all modes to verify the source of cryptographic values. All modes use a special cookie which can be computed independently by the client and server. In symmetric modes the cookie is constructed using the Diffie-Hellman key agreement algorithm. In other modes the cookie is constructed from the IP addresses and a private value known only to the server. All modes use in addition a variant of the S-KEY scheme, in which a pseudo-random key list is generated and used in reverse order. These schemes are described along with an executive summary, current status, briefing slides and reading list, on the [Autonomous Authentication](/reflib/autokey/) page. 

The cryptographic values used by the Autokey scheme are incorporated as a set of files generated by the [<code>ntp-genkeys</code>](/archives/4.1.1/genkeys/) program, including the symmetric private keys, public/private key pair, and the agreement parameters. See the <code>ntp-genkeys</code> page for a description of the formats of these files. They contain cryptographic values generated by the algorithms of the <code>rsaref20</code> package and are in printable ASCII format. All file names include the timestamp, in NTP seconds, following the default names given below. Since the file data are derived from random values seeded by the system clock and the file name includes the timestamp, every generation produces a different file and different file name.

The <code>ntp.keys</code> file contains the DES/MD5 private keys. It must be distributed by secure means to other servers and clients sharing the same security compartment and made visible only to root. While this file is not used with the Autokey scheme, it is needed to authenticate some remote configuration commands used by the [<code>ntpq</code>](/archives/4.1.1/ntpq/) and [<code>ntpdc</code>](/archives/4.1.1/ntpdc/) utilities. The <code>ntpkey</code> file contains the RSA private key. It is useful only to the machine that generated it and never shared with any other daemon or application program, so must be made visible only to root.

The <code>ntp_dh</code> file contains the agreement parameters, which are used only in symmetric (active and passive) modes. It is necessary that both peers beginning a symmetric-mode association share the same parameters, but it does not matter which <code>ntp_dh</code> file generates them. If one of the peers contains the parameters, the other peer obtains them using the Autokey protocol. If both peers contain the parameters, the most recent copy is used by both peers. If a peer does not have the parameters, they will be requested by all associations, either configured or not; but, none of the associations can proceed until one of them has received the parameters. Once loaded, the parameters can be provided on request to other clients and servers. The <code>ntp_dh</code> file can also be distributed using insecure means, since the data are public values.

The <code>ntpkey\__host_</code> file contains the RSA public key, where <code>_host_</code> is the name of the host. Each host must have its own <code>ntpkey\__host_</code> file, which is normally provided to other hosts using the Autokey protocol Each <code>server</code> or <code>peer</code> association requires the public key associated with the particular server or peer to be loaded either directly from a local file or indirectly from the server using the Autokey protocol. These files can be widely distributed and stored using insecure means, since the data are public values.

The optional <code>ntpkey_certif\__host_</code> file contains the PKI certificate for the host. This provides a binding between the host hame and RSA public key. In the current implementation the certificate is obtained by a client, if present, but the contents are ignored.

Due to the widespread use of interface-specific naming, the host names used in configured and mobilized associations are determined by the Unix <code>gethostname()</code> library routine. Both the <code>ntp-genkeys</code> program and the Autokey protocol derive the name of the public key file using the name returned by this routine. While every server and client is required to load their own public and private keys, the public keys for each client or peer association can be obtained from the server or peer using the Autokey protocol. Note however, that at the current stage of development the authenticity of the server or peer and the cryptographic binding of the server name, address and public key is not yet established by a certificate authority or web of trust.

* * *

#### Leapseconds Table

The NIST provides [tables](https://www.nist.gov/pml/time-and-frequency-division/time-realization/leap-seconds) showing the epoch for all historic occasions of leap second insertion since 1972. The leapsecond table shows each epoch of insertion along with the offset of International Atomic Time (TAI) with respect to Coordinated Universtal Time (UTC), as disseminated by NTP.

While not strictly a security function, the Autokey protocol provides means to securely retrieve the leapsecond table from a server or peer. Servers load the leapsecond table directly from the file specified in the <code>crypto</code> command, while clients can obtain the table indirectly from the servers using the Autokey protocol. Once loaded, the table can be provided on request to other clients and servers.

* * *

#### Key Management

All key files are installed by default in <code>/usr/local/etc</code>, which is normally in a shared filesystem in NFS-mounted networks and avoids installing them in each machine separately. The default can be overridden by the <code>keysdir</code> configuration command. However, this is not a good place to install the private key file, since each machine needs its own file. A suitable place to install it is in <code>/etc</code>, which is normally not in a shared filesystem.

The recommended practice is to keep the timestamp extensions when installing a file and to install a link from the default name (without the timestamp extension) to the actual file. This allows new file generations to be activated simply by changing the link. However, <code>ntpd</code> parses the link name when present to extract the extension value and sends it along with the public key and host name when requested. This allows clients to verify that the file and generation time are always current. However, the actual location of each file can be overridden by the <code>crypto</code> configuration command.

All cryptographic keys and related parameters should be regenerated on a periodic and automatic basis, like once per month. The <code>ntp-genkeys</code> program uses the same timestamp extension for all files generated at one time, so each generation is distinct and can be readily recognized in monitoring data. While a public/private key pair must be generated by every server and client, the public keys and agreement parameters do not need to be explicitly copied to all machines in the same security compartment, since they can be obtained automatically using the Autokey protocol. However, it is necessary that all primary servers have the same agreement parameter file. The recommended way to do this is for one of the primary servers to generate that file and then copy it to the other primary servers in the same compartment using the Unix <code>rdist</code> command. Future versions of the Autokey protocol are to contain provisions for an agreement protocol to do this automatically.

Servers and clients can make a new generation in the following way. All machines have loaded the old generation at startup and are operating normally. At designated intervals, each machine generates a new public/private key pair and makes links from the default file names to the new file names. The <code>ntpd</code> is then restarted and loads the new generation, with result clients no longer can authenticate correctly. The Autokey protocol is designed so that after a few minutes the clients time out and restart the protocol from the beginning, with result the new generation is loaded and operation continues as before. A similar procedure can be used for the agreement parameter file, but in this case precautions must be take to be sure that all machines with this file have the same copy.

* * *

#### Authentication Commands

<code>**autokey [_logsec_]**</code>

: Specifies the interval between regenerations of the session key list used with the Autokey protocol. Note that the size of the key list for each association depends on this interval and the current poll interval. The default interval is 12 (4096 s or about 1.1 hours). For poll intervals above the specified interval, a session key list with a single entry will be regenerated for every message sent.

<code>**controlkey _key_**</code>

: Specifies the key identifier to use with the [<code>ntpq</code>](/archives/4.1.1/ntpq/) utility, which uses the standard protocol defined in RFC-1305. The <code>_key_</code> argument is the key identifier for a trusted key, where the value can be in the range 1 to 65534, inclusive.

<code>**[flags _flags_] [privatekey _file_] [publickey _file_] [dhparms _file_] [leap _file_]**</code>

: This command requires the NTP daemon build process be configured with the RSA library. This command activates public-key cryptography and loads the required RSA private and public key files and the optional Diffie-Hellman agreement parameter file, if present. If one or more files are left unspecified, the default names are used as described below. Following are the subcommands:

<code>privatekey _file_</code> 

: Specifies the location of the RSA private key file, which otherwise defaults to <code>/usr/local/etc/ntpkey</code>.

<code>publickey _file_</code> 

: Specifies the location of the RSA public key file, which otherwise defaults to <code>/usr/local/etc/ntpkey_host_</code>, where host is the name of the generating machine. 

<code>dhparms _file_</code>

: Specifies the location of the Diffie-Hellman parameters file, which otherwise defaults to <code>/usr/local/etc/ntpkey_dh</code>. 

<code>leap _file_</code> 

: Specifies the location of the leapsecond table file, which otherwise defaults to <code>/usr/local/etc/ntpkey_leap</code>.

<code>**keys _keyfile_**</code>

: Specifies the location of the DES/MD5 private key file containing the keys and key identifiers used by <code>ntpd</code>, <code>ntpq</code> and <code>ntpdc</code> when operating with symmetric-key mode. 

<code>**keysdir _path_**</code>

: This command requires the NTP daemon build process be configured with the RSA library. It specifies the default directory path for the private key file, agreement parameters file and one or more public key files. The default when this command does not appear in the configuration file is <code>/usr/local/etc/</code>. 

<code>**requestkey _key_**</code>

: Specifies the key identifier to use with the [<code>ntpdc</code>](/archives/4.1.1/ntpdc/) program, which uses a proprietary protocol specific to this implementation of <code>ntpd</code>. The <code>_key_</code> argument is a key identifier for the trusted key, where the value can be in the range 1 to 65534, inclusive.

<code>**revoke [_logsec_]**</code>

: Specifies the interval between re-randomization of certain cryptographic values used by the Autokey scheme, as a power of 2 in seconds. These values need to be updated frequently in order to deflect brute-force attacks on the algorithms of the scheme; however, updating some values is a relatively expensive operation. The default interval is 16 (65,536 s or about 18 hours). For poll intervals above the specified interval, the values will be updated for every message sent. 

<code>**trustedkey [_key_] [...]**</code>

: Specifies the key identifiers which are trusted for the purposes of authenticating peers with symmetric-key cryptography, as well as keys used by the <code>ntpq</code> and <code>ntpdc</code> programs. The authentication procedures require that both the local and remote servers share the same key and key identifier for this purpose, although different keys can be used with different servers. The <code>key</code> arguments are 32-bit unsigned integers with values from 1 to 65,534. 

* * *

#### Files

<code>ntp.keys</code> - private MD5 keys 

<code>ntpkey</code> - RSA private key 

<code>ntpkey\__host_</code> - RSA public key 

<code>ntp_dh</code> - Diffie-Hellman agreement parameters 

* * *

#### Bugs

The <code>ntpkey_<i>host</i></code> files are really digital certificates. These should be obtained via secure directory services when they become universally available.