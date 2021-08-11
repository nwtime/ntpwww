---
title: "Autokey Public-Key Authentication"
type: archives
---


Last update: 3-Oct-2011 21:51 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.8-series/autokey/#introduction)
*   [Autokey Subnets](/archives/4.2.8-series/autokey#autokey-subnets)
*   [Subnet Group Names](/archives/4.2.8-series/autokey/#subnet-group-names)
*   [Secure Groups](/archives/4.2.8-series/autokey/#secure-groups)
*   [Configuration - Authentication Schemes](/archives/4.2.8-series/autokey/#configuration---authentication-schemes)
*   [Configuration - Identity Schemes](/archives/4.2.8-series/autokey/#configuration---identity-schemes)
*   [Identity Schemes and Cryptotypes](/archives/4.2.8-series/autokey/#identity-schemes-and-cryptotypes)
*   [Files](/archives/4.2.8-series/autokey/#files)

* * *

#### Introduction

This distribution includes support for the Autokey public key algorithms and protocol specified in RFC-5906 "Network Time Protocol Version 4: Autokey Specification". This support is available only if the OpenSSL library has been installed and the <tt>--enable-autokey</tt> option is specified when the distribution is built.

Public key cryptography is generally considered more secure than symmetric key cryptography. Symmetric key cryptography is based on a shared secret key which must be distributed by secure means to all participants. Public key cryptography is based on a private secret key known only to the originator and a public key known to all participants. A recipient can verify the originator has the correct private key using the public key and any of several digital signature algorithms.

The Autokey Version 2 protocol described on the [Autokey Protocol](/reflib/proto) page verifies packet integrity using message digest algorithms, such as MD5 or SHA, and verifies the source using digital signature schemes, such as RSA or DSA. As used in Autokey, message digests are exceptionally difficult to cryptanalyze, as the keys are used only once.

Optional identity schemes described on the [Autokey Identity Schemes](/reflib/ident) page are based on cryptographic challenge/response exchanges. Optional identity schemes provide strong security against masquerade and most forms of clogging attacks. These schemes are exceptionally difficult to cryptanalyze, as the challenge/response exchange data are used only once. They are described along with an executive summary, current status, briefing slides and reading list on the [Autonomous Authentication](/reflib/autokey) page.

Autokey authenticates individual packets using cookies bound to the IP source and destination addresses. The cookies must have the same IP addresses at both the server and client. For this reason operation with network address translation schemes is not possible. This reflects the intended robust security model where government and corporate NTP servers and clients are operated outside firewall perimeters.

Autokey is designed to authenticate servers to clients, not the other way around as in SSH. An Autokey server can support an authentication scheme such as the Trusted Certificate (TC) scheme described in RFC 5906, while a client is free to choose between the various options. It is important to understand that these provisions are optional and that selection of which option is at the discretion of the client. If the client does not require authentication, it is free to ignore it, even if some other client of the same server elects to participate in either symmetric key or public key cryptography.

Autokey uses industry standard X.509 public certificates, which can be produced by commercial services, utility programs in the OpenSSL software library, and the [<tt>ntp-keygen</tt>](/archives/4.2.8-series/keygen) utility program in the NTP software distribution. A certificate includes the subject name of the client, the issuer name of the server, the public key of the client and the time period over which the public and private keys are valid. All Autokey hosts have a self-signed certificate with the Autokey name as both the subject and issuer. During the protocol, additional certificates are produced with the Autokey host name as subject and the host that signs the certificate as issuer.

There are two timeouts associated with the Autokey scheme. The _key list timeout_ is set by the <tt>automax</tt> command, which specifies the interval between generating new key lists by the client or server. The default timeout of about 1.1 hr is appropriate for the majority of configurations and ordinarily should not be changed. The _revoke timeout_ is set by the <tt>revoke</tt> command, which specifies the interval between generating new server private values. It is intended to reduce the vulnerability to cryptanalysis; however, new values require the server to encrypt each client cookie separately. The default timeout of about 36 hr is appropriate for most servers, but might be too short for national time servers.

#### Autokey Subnets

An Autokey subnet consists of a collection of hosts configured as an acyclic, directed tree with roots one or more trusted hosts (THs) operating at the lowest stratum of the subnet. Note that the requirement that the NTP subnet be acyclic means that, if two hosts are configured with each other in symmetric modes, each must be a TH. The THs are synchronized directly or indirectly to national time services via trusted means, such as radio, satellite or telephone modem, or one or more trusted agents (TAs) of a parent subnet. NTP subnets can be nested, with the THs of a child subnet configured for one or more TAs of a parent subnet. The TAs can serve one or more child subnets, each with its own security policy and set of THs.

A certificate trail is a sequence of certificates, each signed by a host one step closer to the THs and terminating at the self-signed certificate of a TH. The requirement that the subnet be acyclic means certificate trails can never loop. NTP servers operate as certificate authorities (CAs) to sign certificates provided by their clients. The CAs include the TAs of the parent subnet and those subnet servers with dependent clients.

In order for the signature to succeed, the client certificate valid period must begin within the valid period of the server certificate. If the server period begins later than the client period, the client certificate has expired; if the client period begins later than the server period, the server certificate has expired.

The Autokey protocol runs for each association separately, During the protocol, the client recursively obtains the certificates on the trail to a TH, saving each in a cache ordered from most recent to oldest. If an expired certificate is found, it is invalidated and marked for later replacement. As the client certificate itself is not involved in the certificate trail, it can only be declared valid or expired when the server signs it.

The certificates derived from each association are combined in the cache with duplicates suppressed. If it happens that two different associations contribute certificates to the cache, a certificate on the trail from one association could expire before any on another trail. In this case the remaining trails will survive until the expired certificate is replaced. Once saved in the cache, a certificate remains valid until it expires or is replaced by a new one.

It is important to note that the certificate trail is validated only at startup when an association is mobilized. Once validated in this way, the server remains valid until it is demobilized, even if certificates on the trail to the THs expire. While the certificate trail authenticates each host on the trail to the THs, it does not validate the time values themselves. Ultimately, this is determined by the NTP on-wire protocol.

![gif](/archives/pic/flt8.gif)

**Figure 1: Example Configuration**

Figure 1 shows an example configuration with three NTP subnets, Alice, Helen and Carol. Alice and Helen are parent groups for Carol with TA C belonging to Alice and TA S belonging to Helen. Hosts A and B are THs of Alice, host R is the TH of Helen and host X is the TH of Carol. Assume that all associations are client/server, child subnet TH X has two mobilized associations, one to Alice TA host C and the other to Carol TA host S. While not shown in the figure, Alice hosts A and B could configure symmetric mode associations between them for redundancy and backup.

Note that host D certificate trail is D→C→A or D→C→B, depending on the particular order the trails are built. Host Y certificate trail is only Y→X, since X is a TH. Host X has two certificate trails X→C→A or X→C→B, and X→S→R.

#### Subnet Group Names

In some configurations where more than one subnet shares an Ethernet or when multiple subnets exist in a manycast or pool configuration, it is useful to isolate one subnet from another. In Autokey this can be done using group names. An Autokey host name is specified by the <tt>-s</tt><tt> _host_@_group_</tt> option of the <tt>ntp-keygen</tt> program, where _<tt>host</tt>_ is the host name and _<tt>group</tt>_ is the group name. If _<tt>host</tt>_ is omitted, the name defaults to the string returned by the Unix <tt>gethostname()</tt> routine, ordinarily the DNS name of the host. Thus, for host <tt>beauregard.udel.edu</tt> the option <tt>-s @red</tt> specifies the Autokey host name <tt>beauegard.udel.edu@red</tt>.

A subnet host with a given group name will discard ASSOC packets from all subnets with a different group name. This effectively disables the Autokey protocol without additional packet overhead. For instance, one or more manycast or pool servers will not respond to ASSOC packets from subnets with difference group names. Groups sharing an Ethernet will be filtered in the same way.

However, as shown in Figure 1, there are configurations where a TH of one group needs to listen to a TA of a different group. This is accomplished using the <tt>ident _group_</tt> option of the <tt>crypto</tt> command and/or the <tt>ident _group_</tt> option of the <tt>server</tt> command. The former case applies to all hosts sharing a common broadcast, manycast or symmetric passive modes, while the latter case applies to each individual client/server or symmetric active mode association. In either case the host listens to the specified group name in addition to the group name specified in the <tt>-s</tt> option of the <tt>ntp-keygen</tt> program.

#### Secure Groups

NTP security groups are an extension of the NTP subnets described in the previous section. They include in addition to certificate trails one or another identity schemes described on the [Autokey Identity Schemes](/reflib/ident) page. NTP secure groups are used to define cryptographic compartments and security hierarchies. The identity scheme insures that the server is authentic and not victim of masquerade by an intruder acting as a middleman.

An NTP secure group is an NTP subnet configured as an acyclic tree rooted on the THs. The THs are at the lowest stratum of the secure group. They run an identity exchange with the TAs of parent subnets All group hosts construct an unbroken certificate trail from each host, possibly via intermediate hosts, and ending at a TH of that group. The TH verifies authenticity with the TA of the parent subnet using an identity exchange.

![gif](/archives/pic/flt9.gif)

**Figure 2: Identify Scheme**

The identity exchange is run between a TA acting as a server and a TH acting as a client. As shown in Figure 2, the identity exchange involves a challenge-response protocol where a client generates a nonce and sends it to the server. The server performs a mathematical operation involving a second nonce and the secret group key, and sends the result along with a hash to the client. The client performs a another mathematical operation and verifies the result with the hash.

Since each exchange involves two nonces, even after repeated observations of many exchanges, an intruder cannot learn the secret group key. It is this quality that allows the secret group key to persist long after the longest period of certificate validity. In the Schnorr (Identify Friend or Foe - IFF) scheme, the secret group key is not divulged to the clients, so they cannot conspire to prove identity to other hosts.

As described on the [Autokey Identity Schemes](/reflib/ident) page, there are five identity schemes, three of which - IFF, GQ and MV - require identity files specific to each scheme. There are two types of files for each scheme, an encrypted server keys file and a nonencrypted client keys file, also called the parameters file, which usually contains a subset of the keys file.

Figure 2 shows how keys and parameters are distributed to servers and clients. A TA constructs the encrypted keys file and the nonencrypted parameters file. Hosts with no dependent clients can retrieve client parameter files from an archive or web page. The <tt>ntp-keygen</tt> program can export parameter files using the <tt>-e</tt> option. By convention, the file name is the name of the secure group and must match the <tt>ident</tt> option of the <tt>crypto</tt> command or the <tt>ident</tt> option of the <tt>server</tt> command.

When more than one TH Is involved in the secure group, it is convenient for the TAs and THs to use the same encrypted key files. To do this, one of the parent TAs includes the <tt>-i _group_</tt> option on the <tt>ntp-keygen</tt> command line, where _<tt>group</tt>_ is the name of the child secure group. The <tt>ntp-keygen</tt> program can export server keys files using the <tt>-q</tt> option and a chosen remote password. The files are installed on the TAs and then renamed using the name given as the first line in the file, but without the filestamp. The secure group name must match the <tt>ident</tt> option for all TAs.

In the latest Autokey version, the host name and group name are independent of each other and the <tt>host</tt> option of the <tt>crypto</tt> command is deprecated. When compatibility with older versions is required, specify the same name for both the <tt>-s</tt> and <tt>-i</tt> options.

In special circumstances the Autokey message digest algorithm can be changed using the <tt>digest</tt> option of the <tt>crypto</tt> command. The digest algorithm is separate and distinct from the symmetric key message digest algorithm. If compliance with FIPS 140-2 is required, the algorithm must be ether <tt>SHA</tt> or <tt>SHA1</tt>. The Autokey message digest algorithm must be the same for all participants in the NTP subnet.

Returning to the example of Figure 1, Alice, Helen and Carol run run the Trusted Certificate (TC) scheme, internally, as the environment is secure and without threat from external attack, in particular a middleman masquerade. However, TH X of Carol is vulnerable to masquerade on the links between X and C and between X and S. Therefore, both parent subnet TAs C and S run an identity exchange with child subnet TH X. Both have the same encrypted keys file and X the common parameters file.

#### Configuration - Authentication Schemes

Autokey has an intimidating number of options, most of which are not necessary in typical scenarios. However, the Trusted Certificate (TC) scheme is recommended for national NTP time services, such as those operated by NIST and USNO. Configuration for TC is very simple.

Referring to Figure 1, for each TH, A, B, R and X, as root:

`# cd /usr/local/etc`  
`# ntp-keygen -T`

and for the other hosts the same commands without the <tt>-T</tt> option. This generates an RSA private/public host key file and a self-signed certificate file for the RSA digital signature algorithm with the MD5 message digest algorithm. For the THs a trusted certificate is generated; for the others a nontreusted certificate is generated. Include in the <tt>ntp.conf</tt> configuration file for all hosts other than the primary servers, A, B and R, something like

`# server _host_ autokey`  
`# crypto`  
`# driftfile /etc/ntp.drift`

where _<tt>host</tt>_ is the selected server name as shown in the figure. Servers A, B and R are configured for local reference clocks or trusted remoter servers as required.

In the above configuration examples, the default host name is the string returned by the Unix <tt>gethostname()</tt> routine, ordinarily the DNS name of the host. This name is used as the subject and issuer names on the certificate, as well as the default password for the encrypted keys file. The host name can be changed using the <tt>-s</tt> option of the <tt>ntp-keygen</tt> program. The default password can be changed using the <tt>-p</tt> option of the <tt>ntp-keygen</tt> program and the <tt>pw</tt> option of the <tt>crypto</tt> configuration command.

Group names can be added to this configuration by including the <tt>-s _host_@_group_</tt> option with the <tt>ntp-keygen</tt> program. For the purpose of illustration, the <tt>_host_</tt> string is empty, signifying the default host name. For example, @<tt>yellow</tt> can be used for the Alice group, @<tt>orange</tt> for the Helen group and @<tt>blue</tt> for the Carol group. In addition, for TH X the <tt>ident yellow</tt> option should be added to the <tt>server</tt> command for the Alice group and the <tt>ident orange</tt> option should be added to the <tt>server</tt> command for the Helen group.

#### Configuration - Identity Schemes

The example in this section uses the IFF identity scheme, but others, including GQ and MV, can be used as well. It's best to start with a functioning TC configuration and add commands as necessary. We start with the subnets of Figure 1 configured as in the previous section. Recall that the parent subnet TA for Alice is C and for Helen is S. Each of the TAs generates an encrypted server keys file and nonencrypted client parameters file for the IFF identity scheme using the <tt>-I</tt> option of the <tt>ntp-keygen</tt> program. Note the TAs are not necessarily trusted hosts, so may not need the <tt>-T</tt> option.

The nonencrypted client parameters can be exported using the command

`ntp-keygen -e > file`

where the <tt>-e</tt> option redirects the client parameters to _<tt>file</tt>_ via the standard output stream for a mail application or stored locally for later distribution to one or more THs. In a similar fashion the encrypted keys file can be exported using the command

`ntp-keygen -q passw2 > file`

where _<tt>passwd2</tt>_ is the read password for another TA. We won't need this file here.

While the file names used for the exported files are arbitrary, it is common practice to use the name given as the first line in the file with the filestamp suppressed. Thus, the nonencryted parameters file from each TA is copied to X with this name.

To complete the configuration, the TH includes the client parameters file name in the <tt>ident</tt> option of the <tt>server</tt> command for the TA association:

`server 1.2.3.4 ident group`

where _<tt>group</tt>_ is the file name given above.

#### Identity Schemes and Cryptotypes

A specific combination of authentication and identity schemes is called a _cryptotype_, which applies to clients and servers separately. A group can be configured using more than one cryptotype combination, although not all combinations are interoperable. Note however that some cryptotype combinations may successfully intemperate with each other, but may not represent good security practice. The server and client cryptotypes are defined by the following codes.

<dt>NONE</dt>

A client or server is type NONE if authentication is not available or not configured. Packets exchanged between client and server have no MAC.

<dt>AUTH</dt>

A client or server is type AUTH if the <tt>key</tt> option is specified with the <tt>server</tt> configuration command and the client and server keys are compatible. Packets exchanged between clients and servers have a MAC.

<dt>PC</dt>

A client or server is type PC if the <tt>autokey</tt> option is specified with the <tt>server</tt> configuration command and compatible host key and private certificate files are present. Packets exchanged between clients and servers have a MAC.

<dt>TC</dt>

A client or server is type TC if the <tt>autokey</tt> option is specified with the <tt>server</tt> configuration command and compatible host key and public certificate files are present. Packets exchanged between clients and servers have a MAC.

<dt>IDENT</dt>

A client or server is type IDENT if the <tt>autokey</tt> option is specified with the <tt>server</tt> configuration command and compatible host key, public certificate and identity scheme files are present. Packets exchanged between clients and servers have a MAC.

The compatible cryptotypes for clients and servers are listed in the following table.

| Client |      |       | Server |      |       |
| ----- | ----- | ----- | ----- | ----- | ----- |
|       | NONE  | AUTH  | PC    | TC    | IDENT |
| NONE | yes | yes* | yes* | yes* | yes* |
| AUTH | no | yes | no | no | no |
| PC | no | no | yes | no | no |
| TC | no | no | no | yes | yes |
| IDENT | no | no | no | no | yes |

\* These combinations are not valid if the restriction list includes the <tt>notrust</tt> option.

#### Error Codes

Errors can occur due to mismatched configurations, unexpected protocol restarts, expired certificates and unfriendly people. In most cases the protocol state machine recovers automatically by retransmission, timeout and restart, where necessary. Some errors are due to mismatched keys, digest schemes or identity schemes and must be corrected by installing the correct media and/or correcting the configuration file. One of the most common errors is expired certificates, which must be regenerated and signed at least once per year using the [<tt>ntp-keygen</tt>](/archives/4.2.8-series/keygen) program.

The following error codes are reported via the NTP control and monitoring protocol trap mechanism and to the <tt>cryptostats</tt> monitoring file if configured.

<dt>101 bad field format or length</dt>

The packet has invalid version, length or format.

<dt>102 bad timestamp</dt>

The packet timestamp is the same or older than the most recent received. This could be due to a replay or a server clock time step.

<dt>103 bad filestamp</dt>

The packet filestamp is the same or older than the most recent received. This could be due to a replay or a key file generation error.

<dt>104 bad or missing public key</dt>

The public key is missing, has incorrect format or is an unsupported type.

<dt>105 unsupported digest type</dt>

The server requires an unsupported digest/signature scheme.

<dt>106 unsupported identity type</dt>

The client or server has requested an identity scheme the other does not support.

<dt>107 bad signature length</dt>

The signature length does not match the current public key.

<dt>108 signature not verified</dt>

The message fails the signature check. It could be bogus or signed by a different private key.

<dt>109 certificate not verified</dt>

The certificate is invalid or signed with the wrong key.

<dt>110 host certificate expired</dt>

The old server certificate has expired.

<dt>111 bad or missing cookie</dt>

The cookie is missing, corrupted or bogus.

<dt>112 bad or missing leapseconds table</dt>

The leapseconds table is missing, corrupted or bogus.

<dt>113 bad or missing certificate</dt>

The certificate is missing, corrupted or bogus.

<dt>114 bad or missing group key</dt>

The identity key is missing, corrupt or bogus.

<dt>115 protocol error</dt>

The protocol state machine has wedged due to unexpected restart.

#### Files

See the [<tt>ntp-keygen</tt>](/archives/4.2.8-series/keygen) page. Note that provisions to load leap second values from the NIST files have been removed. These provisions are now available whether or not the OpenSSL library is available. However, the functions that can download these values from servers remains available.