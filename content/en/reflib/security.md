---
title: "NTP Security Analysis"
type: archives
toc_hide: true
---

![gif](/documentation/pic/alice44.gif)

from [_Alice's Adventures in Wonderland_](/reflib/pictures/), Lewis Carroll

The Cheshire Cat is our resident cryptographer.

* * *

#### Table of Contents

*  [Abstract](/reflib/security/#abstract)
*  [1. Introduction](/reflib/security/#1-introduction)
*  [1.1 Threats and Countermeasures](/reflib/security/#11-threats-and-countermeasures)
*  [1.2 Protocol Layers](/reflib/security/#12-protocol-layers)
*  [2. On-Wire Protocol Layer](/reflib/security/#2-on-wire-protocol-layer)
*  [3. Message Digest Layer](/reflib/security/#3-message-digest-layer)
*  [4. Autokey Sequence Layer](/reflib/security/#4-autokey-sequence-layer)
*  [4.1. Client/Server Mode](/reflib/security/#41-clientserver-mode)
*  [4.2. Symmetric Modes](/reflib/security/#42-symmetric-modes)
*  [4.3 Broadcast Modes](/reflib/security/#43-broadcast-modes)
*  [5. Autokey Protocol Layer](/reflib/security/#5-autokey-protocol-layer)
*  [5.1. Client/Server and Symmetric Modes](/reflib/security/#51-clientserver-and-symmetric-modes)
*  [5.2. Broadcast Modes](/reflib/security/#52-broadcast-modes)
*  [6. Conclusions](/reflib/security/#6-conclusions)
*  [7. Parting Shots](/reflib/security/#7-parting-shots)
*  [7.1 Cookie Size](/reflib/security/#71-cookie-size)
*  [7.2. Cookie Snatcher Attack](/reflib/security/#72-cookie-snatcher-attack)
*  [7.3. Certificate Validation](/reflib/security/#73-certificate-validation)
*  [7.4. Reference Implementation Improvements](/reflib/security/#74-reference-implementation-improvements)
*  [8. References](/reflib/security/#8-references)
*  [Appendix A. Autokey Extension Fields](/reflib/security/#appendix-a-autokey-extension-fields)

* * *

#### Abstract

Ubiquitous Internet protocols such as the Network Time Protocol (NTP) are routinely subject to hostile attempts to disrupt protocol operations or deny service. This document describes security enhancements to NTP, including the use of symmetric-key and public-key cryptographic means to avoid wiretap and middleman attacks that can disrupt the protocol. However, detailed analysis of the current provisions also exposes subtle vulnerabilities where a determined middleman can masquerade as a legitimate server under certain conditions. This document proposes solutions to these vulnerabilities, as well as minor modifications allowing use of commercial certificates in addition to locally manufactured ones.

* * *

#### 1. Introduction

A ubiquitous time service such as NTP operating over the public Internet can be vulnerable to all kinds of attacks which might attempt to disrupt the protocol or the data it conveys. This document presents an analysis of the NTP security model and considers a wide range of attack scenarios that an intruder might attempt to exploit. While the discussion applies to all servers and clients, it is primarily intended for national laboratories, such as NIST and USNO, providing services to a large client population on local networks connected to the public Internet by routers.

It is essential to consider the use of the term _authentic_ as used in this document. A server that can be proven authentic by one cryptographic means or another can deliver correct time with respect to its synchronization sources and best estimate according to the available mitigation algorithms described elsewhere. However, a server that has been proven authentic can deliver incorrect time if, for instance, its synchronization sources deliver incorrect time. On the other hand, a server that has not been proven authentic may or may not deliver correct time or even deliver bogus time not synchronized to any source. To determine authenticity, all credible security threats must be evaluated. As used in this document, to _defend_ against a particular threat means to detect it and take countermeasures against it.

The software means assumed in this document and used in the reference implementation include the software cryptographic library available from https://www.openssl.org. This library is automatically included in the build process, if available, but the Autokey provisions must be separately enabled in the `configure` command. The library includes several encryption algorithms, hash functions and signature schemes used throughout the industry; however, in conformance with US federal regulations, no data other than signatures and cookies are encrypted.

> Note: If symmetric key cryptography using the MD5 hash algorithm is the only means required, the OpenSSL library is not required. The MD5 hash algorithm is included with the reference implementation base distribution.

The security of the signature algorithm depends in part on the modulus used to compute various functions. The reference implementation currently uses a default modulus of 512, which is generally assumed adequate to resist cryptanalysis in this application. However, the modulus can be changed in a command line option in the range 256 through 2048, although with the larger options the NTP packet size can become unwieldy.

* * *

#### 1.1 Threats and Countermeasures

First, we need to consider what the intruder is trying to do. The NTP security model considers the data in an NTP packet to be public values, so there is no attempt to disguise or encrypt the data itself; only to confirm authenticity of the sources and avoid attacks such as described in this document. The most obvious goal for the intruder is to produce incorrect or inconsistent time values that result in failure of some time-dependent critical service. Another goal is to disrupt the protocol operations, to clog the network, server or client with a high volume of traffic, or force the protocol to consume significant resources, such as expensive cryptographic computations.

Next, we need to consider the types of attack an intruder might attempt. In a _bogus attack_, the intruder attempts to manufacture a packet acceptable to the client or server. In a _wiretap attack_, the intruder copies client and server packets, and in principle can archive them forever. In a _replay attack_ the intruder replays one or more of these packets. A _duplicate_ is a replay of the most recent packet sent, most likely due to a retransmission in the network. An _old duplicate_ is a replay of a packet other than the most recent one sent, most likely due to an intruder. We assume in this case that replayed packets cannot arrive before the original packet. Attacks like these might be possible by a rogue computer on a shared Ethernet.

In addition to these active attacks, there are passive attacks in which packets can be lost due to collisions, queue overflow or bit errors resulting in checksum failure. Due to the nature of the mitigation algorithms defined in the NTPv4 specification, a moderate rate of lost packets does not affect the performance of these algorithms. However, there are some conditions under which a lost packet causes a protocol restart, which can cause delays with these algorithms, as described in this document.

In a _middleman attack_, an intruder can intercept a client or server packet and optionally prevent its onward transmission. The middleman can then fabricate bogus or misleading packets acceptable to the server or client. Alternatively, the middleman can attempt a _cut-and-paste attack_ to substitute old or bogus information in an Autokey extension field. The ultimate attack is a _masquerade attack_, in which the intruder assumes the identity of a legitimate server. Attacks like these might be possible by a compromised router or bogus DNS server.

An intruder can attempt a _delay attack_, in which client or server packets are delayed a constant or variable time, but otherwise are unchanged. If the delays in the two directions between the client and server are substantially the same, the offset error may be insignificant. This is the case with space data links, where the light time varies with spacecraft maneuvers. If the delays in the two directions are significantly different, the offset error is half the difference between the delays in the two directions. Attacks like these might be possible by a compromised router. They can occur independently or in combination with other security vulnerabilities discussed in this document.

One or more intruders can collaborate in a _denial of service_ (DoS) _attack,_ which attempts to deny service by flooding the network, clients or servers with a high level of bogus traffic. From past experience, these attacks on NTP servers have not been effective, since the hardware and software resources required are minimal. However, a DoS attack may be effective if it forces needless and expensive cryptographic calculations. For this purpose, encryption algorithms such as RSA and DSA are considered expensive, but not hash algorithms such as MD5 and SHA. Vulnerabilities due to this cause will be discussed in later sections of this document.

The security measures discussed in this document are not the only defenses available. This document does not consider access controls, which are an integral part of the NTP reference implementation. It does not consider the packet sanity tests which detect and discard packets with invalid format or packet header values. Finally, it does not consider the various mitigation algorithms, in particular the select algorithm which separates the truechimer servers from the falseticker rascals.

* * *

#### 1.2 Protocol Layers

![gif](/documentation/pic/sx1.gif)

**Figure 1. NTP Security Model**

The NTP security model has the hierarchical structure shown in Figure 1. Defense against intruder attack starts at the bottom layer of the hierarchy, the _On-Wire Protocol_ layer. Successful attacks on this layer, if there are any, are defended by the next upward layer, the _Message Digest_ layer, using symmetric key cryptography. Successful attacks on this layer, if there are any, are defended by the _Autokey Sequence_ layer, which uses a hash or pseudo-random sequence technique to bind packets to digital signatures. The Autokey architecture, protocol and algorithms are described in [Network Time Protocol Version 4: Autokey Specification RFC 5906](/reflib/rfc/rfc5906.txt). Defense against a masquerade attack depends on the _Autokey Protocol_ layer, which uses public key cryptography to securely bind the server credentials to digital signatures.

Note that, if a particular threat is successfully defended at one layer, it is assumed defended at higher layers. However, if a particular threat is successfully defended at one layer, it may or may not be defended at lower layers. In general, the layers above the On-Wire Protocol layer are optional. Symmetric key cryptography uses only the bottom two layers; public key cryptography uses all four layers.

* * *

#### 2. On-Wire Protocol Layer

The on-wire protocol is used to transport packets from client to server and from server to client. It is described in detail in the white paper [Analysis and Simulation of the NTP On-Wire Protocols](/reflib/onwire/). The protocols use the transmit timestamp in the NTP packet as a nonce for bogus and duplicate detection and in what is called the _loopback test_. For this purpose a random fuzz is inserted in the non-significant bits of the 64-bit transmit timestamp. It is highly unlikely that an intruder could predict the transmit timestamp in advance. It is not necessary that the transmit timestamp be correct, or monotone-definite increasing; just that each transmit timestamp is different and could not be predicted precisely to within 0.232 ns.

In all protocol modes a duplicate packet is detected if the transmit timestamp matches the transmit timestamp of the previous packet. In this case the duplicate is discarded without further effect on the timestamp calculations. In client/server and symmetric modes, the loopback test compares the transmit timestamp in the client request packet to the origin timestamp in the server reply packet. A discrepancy indicates that the server packet is bogus, an old duplicate, or lost in transit. In symmetric modes, the discrepancy could be due to a protocol restart or packets crossed in flight.

Using the loopback test in client/server and symmetric modes, all the wiretap attacks described in [Section 1](/reflib/security/#1-introduction) are defended. In broadcast modes the on-wire protocol does not detect bogus or old duplicate packets, as the loopback test is not possible. However, these scenarios assume that the packet is not modified during transmission and that the server is authentic and not a middleman attempting to masquerade as a legitimate server. These attacks are discussed in the next section.

> Note: In basic and interleaved symmetric modes, a replay, lost or bogus packet, or protocol restart causes a protocol recovery cycle which delays protocol product delivery one or two rounds. If the intruder maintains an assault rate greater than one packet per round, the delivery rate falls to zero and the synchronization service is effectively disabled. Defense against this type of attack requires additional measures, as described in the next section.

* * *

#### 3. Message Digest Layer

The assumption made so far is that packets cannot be modified in transit. A rogue or compromised router or even a compromised server, could modify any field of a packet except the transmit timestamp field. This can cause the packet to be incorrectly classified or to deliver incorrect time. To defend against this type of attack, the message digest layer uses symmetric key cryptography to compute a message digest.

The message digest is a cryptographic hash computed by an algorithm such as MD5 or SHA. When authentication is specified, the reference implementation appends a message authentication code (MAC) following the NTP packet header and extension fields, if present. The MAC consists of a 32-bit key identifier (key ID) followed by a 128- or 160-bit message digest. The algorithm computes the message digest as the hash of a 128- or 160- bit secret message digest key concatenated with the NTP packet header fields and extension fields, if present, with the exception of the MAC itself. On transmit, the digest is computed and inserted in the MAC. On receive, the digest is computed and compared with the digest in the MAC. The packet is accepted only if the two digests are identical. If a discrepancy is found, the client ignores the packet, but raises an alarm. If this happens at the server, the server returns a special message called a _crypto-NAK_.

![gif](/documentation/pic/sx5.gif)

**Figure 2. Typical Symmetric Key File**

The security of the message digest layer depends on the _message digest key_. In symmetric key cryptography, a set of secret message digest keys is defined in a keys file such as shown in Figure 2. A file such as this is loaded by the reference implementation when the program is started. Each line consists of a key ID used in the packet header, a digest algorithm identifier and the key. In the case of MD5, the key is restricted to a maximum of 16 ASCII printing characters, either a given string, such as `2late4Me` for key ID 10, or a random string. In other digest algorithms the key is a 20-octet random string represented as 40 hex digits.

A tabular definition is not the only method to define message digest keys. In the Autokey sequence layer described in [Section 4](/reflib/security/#4-autokey-sequence-layer), the message digest key is computed by a crafted algorithm involving shared secrets.

On the assumption that the message digest key is shared only between the intended server and client, the message digest layer successfully defends against the threats described in the previous section, as well as a middleman attack or masquerade. It is generally agreed that symmetric key cryptography is extremely reliable and difficult to circumvent. While recent developments suggest it may be possible to synthesize a packet with given MD5 hash, the additional requirement that the packet has a valid NTP format and transmit timestamp makes even MD5 a cryptographically strong algorithm.

However, for a national time server with many thousands of clients, the requirement for shared message digest keys scales awkwardly, at least if each user or user group must have a different message digest key. The key ID space assigned for symmetric key cryptography is limited to 65,534 distinct keys. While a key population of this size is technically possible using the NTPv4 reference implementation, managing such a large population would be awkward at best. Provisions must be made for secure key assignment, distribution and revocation, as well as regular key refreshment.

Possibly, the best application for symmetric key cryptography is for broadcast modes or automatic server discovery schemes such as manycast. In these cases, a small number of keys could serve a proportionately large population.

* * *

#### 4. Autokey Sequence Layer

The Autokey sequence layer is used to authenticate NTP packets using public key cryptography and digital signatures. As public key algorithms have a relatively long and highly variable execution time, they cannot be used for every packet. The Autokey sequence layer uses digitally signed packets only infrequently and binds the remaining packets to them using fast hash and pseudo-random sequence techniques.

> Note: That digital signatures are used only in protocol responses from the server to the client, and then only if the server is synchronized to an authentic source.

The protocol design takes two approaches, one for client/server and symmetric modes; the other for broadcast modes. Both are based on the _autokey_ described in [Appendix A](/reflib/security/#appendix-a-autokey-extension-fields). Autokeys are used when constructing client and server cookies and message digest keys, also described in Appendix A.

* * *

#### 4.1. Client/Server Mode

In client/server mode, the server has a _server cookie_ that is used to generate a _client cookie_ unique to each client separately. The server cookie is a nonce and is refreshed at intervals of about one day. The server computes the client cookie as the MD5 hash of the autokey with client and server IP addresses, a key ID of zero and the server cookie. On request, the server returns the client cookie encrypted using the client public host key provided in the request. In order to avoid counterfeit, the response is signed using the server private sign key. The client decrypts the client cookie and verifies the signature using the server public sign key contained on its certificate. The client cookie is a shared secret retained by the client and regenerated by the server when a client packet arrives. Once the client cookie has been obtained, extension fields are no longer required.

The client generates a nonce to be used as the key ID included in both the client and server packets and is used only once. When sending or receiving an NTP packet, both the client and server calculate the message digest key as described in [Appendix A](/reflib/security/#appendix-a-autokey-extension-fields). Both the client and server verify the message digest as in [Section 3](/reflib/security/#3-message-digest-layer). Without the client cookie, an intruder cannot produce a packet acceptable to either the server or client. In this way, each NTP packet is bound to the client cookie which itself is bound to the server signature.

As long as the client cookie is not compromised, a middleman cannot manufacture bogus packets or modify legitimate packets acceptable to either the server or client. However, a significant _cookie snatcher_ vulnerability exists where a middleman is able to wiretap the client cookie request to learn the client and server IP addresses. The middleman then launches a client cookie request using its own public encryption key. Using the client cookie, the middleman can masquerade as the legitimate server and inject bogus packets acceptable to the client.

> Note: A modification to this design which does not have this hazard is described in [Section 7](/reflib/security/#7-parting-shots).

* * *

#### 4.2. Symmetric Modes

In symmetric modes, each peer operates as a server for the other peer as client; however, each peer has a unique certificate, private/public sign key pair and private/public host key pair. Each peer independently obtains a client cookie as described above. Once the client cookie has been obtained, each peer calculates the shared peer cookie as the exclusive OR of its client cookie and the client cookie obtained from the other peer.

> Note: Close inspection of the symmetric modes protocol reveal that the protocol has the same cookie snatcher vulnerability as in the client/server mode. The middleman sends a cookie request to both peers and forms the exclusive OR of the two client cookies. The middleman can now masquerade as either peer. A modification to this design which does not have this hazard is described in [Section 7](/reflib/security/#7-parting-shots).

* * *

#### 4.3. Broadcast Modes

In broadcast modes the design is more complex, since a two-way exchange is not possible. The Autokey layer defense in broadcast modes uses a variant of the S-KEY scheme to bind a batch of packets to a digitally signed packet. A typical scenario is illustrated in Figure 3.

![gif](/documentation/pic/sx2.gif)

**Figure 3. Autokey Sequence in Broadcast Modes**

Here, <code>_T<sub>i</sub>_</code> represents the transmit timestamp in the NTP header and <code>_T<sub>i</sub>_ < _T_<sub>_i_+1</sub></code>. The broadcast server constructs a key list, where each entry represents the key ID and corresponding message digest key of an autokey with the server source IP address, the broadcast destination IP address, a key ID <code>_x_</code> and a cookie zero. Let <code>_y_ = S(_x_)</code> be the first four octets of the message digest key <code>_x_</code>.

There is a broadcast server serving each subnet, each with an individual key list. If for some reason the system clock is stepped, all key lists are expunged and regenerated. Each broadcast server constructs a key list as follows. Let <code>_C_</code> be a nonce. From Figure 3, <code>S(_C_) = 11, S(11) = S(S(C)) = 1, S(1) = S(S(S(C))) = 5</code> and so on. The final <code>S(3) = 7</code>, along with the number of hashes <code>5</code>, are called the _autokey values_, in this case <code>(7, 5)</code>. These values are transmitted in an Autokey extension field signed by the server private sign key. A key list populated in this way has from one to several hundred entries, depending on the poll interval, and lasts about one hour, after which it is regenerated with a new nonce <code>_C_</code>.

Once the key list has been constructed, the server uses the entries in reverse order. One entry with key ID and message digest key is used for each packet. For instance, the packet sent at <code>_T_<sub>2</sub></code> has key ID 3. The clients verify <code>S(3) = 7</code>. Operations continue in this way until packet <code>_T_<sub>5</sub></code>, after which a new key list is constructed.

Both the client and server compute the message digest key from the autokey formed by the IP addresses and key ID in the packet, and a cookie of zero. In principle, a wiretapper can manufacture a packet with bogus key ID and valid message digest key, but as a practical matter the first four octets of the message digest key will not match any previous key ID, even if the hash calculation is repeated. If for some reason the system clock is stepped, all key lists are expunged and regenerated. In case of a bogus or old duplicate packet, the number of hash repetitions will exceed the maximum number specified by the autokey values. In case a packet is lost, a subsequent packet may cause the client to repeat the hash, but the hash will eventually match the autokey values.

In a _propaganda attack_ the middleman can wiretap a valid NTP packet, substitute bogus header values and recalculate the message digest key. However, the nature of the local network broadcast medium makes middleman attacks very unlikely. However, a middleman attack might be feasible in multicast configurations involving a compromised local network agent.

* * *

#### 5. Autokey Protocol Layer

The Autokey protocol layer is used to retrieve and update cryptographic media such as certificates and identity keys. It is designed to operate without any additional infrastructure, such as TSL <sup>[2](#myfootnote2)</sup>. Provisions are included, but not tested, to utilize industry standard certificate authorities. Once the initial exchanges have been completed, there is no packet header overhead for authentication purposes.

Cryptographic media fall into two categories, private values and public/private key pairs. Private values are nonces with a limited lifetime. They include the autokey values seed and the server cookie. Private values are routinely regenerated and are always obscured by a hash computation.

Public/private key pairs include the host keys, sign keys and identity keys. Host keys are used to encrypt the client cookie, as described in [Section 4](/reflib/security/#4-autokey-sequence-layer). New host keys can be generated at any time without affecting other servers or client. Sign keys are used on certificates to verify signatures on extension fields, as described in [Section 4](/reflib/security/#4-autokey-sequence-layer). If sign keys are changed, all certificates dependent on them must be regenerated. Certificates have a limited lifetime, by default one year, and must be regenerated as required. Identity keys are used to avoid middleman masquerade attacks. Their primary use is to authenticate sign keys when certificates cannot be reliably obtained, as in complex security configurations not discussed in this document. By design, identity keys have a very long lifetime and are used in algorithms that are extremely difficult to cryptanalyze.

> Note: Identity keys are necessary only if an identity scheme is configured. Host keys and the server cookie are not necessary if the protocol changes proposed in [Section 7](/reflib/security/#7-parting-shots) are adopted.

While not strictly necessary in all configurations, the reference implementation requires the servers and clients to load the RSA host key pair, RSA or DSA sign key pair, corresponding RSA or DSA trusted certificate, and optional identity key pair from files when NTP is first started. The client obtains the public component of these keys as the protocol proceeds.

Autokey protocol messages are contained in extension fields, as described in [Appendix A](/reflib/security/#appendix-a-autokey-extension-fields). Each extension field is signed by the server private sign key and verified using the server public sign key included in the server certificate. An Autokey packet includes the NTP header followed by one or more extension fields and then the MAC. The message digest key is determined as in [Section 4](/reflib/security/#4-autokey-sequence-layer) with a cookie value of zero.

> Note: While the extension field signature protects against modification, it does not prevent middleman cut-and-paste attacks where one extension field is exchanged with another. Since the key ID and cookie are exposed. It also does not protect against modification of the packet header fields, so these fields should not be used when extension fields are present. As the Autokey protocol exchanges in the various modes are brief and the on-wire protocol can tolerate moderate packet loss, this has not been a problem.

In order to help defend against replay attacks that might consume resources, the client association includes a timestamp for each cryptographic media type, such as client cookie, autokey values and others defined in the specification. The extension field includes the message type, association ID and signature timestamp. It also includes a filestamp used to verify the cryptographic media. The association ID is a nonce assigned when the client association is mobilized. The timestamp is assigned when the signature is updated, while the filestamp is assigned when the media are updated.

The association timestamp is updated from the packet variables only if:

*   The message type and association ID match the client association values. This prevents middleman substitution with an extension field for another client.
*   The timestamp is strictly later than the media timestamp. This prevents middleman substitution with a replay of an earlier extension field.
*   The filestamp is the same or later than the media filestamp. This is intended to force a remobilization if the media is updated.
*   The extension field signature is valid.

If these criteria are not met, the packet is discarded. If no valid packets are received within a timeout period, the association is remobilized and the media variables are refreshed. If the server clock is set backwards for some reason, its extension fields will be discarded until timeout.

A determined invader might attempt a DoS attack designed to consume server computation resources. For example, an intruder could replay spurious but valid cookie request packets at high rate. The attack could clog the server with expensive host encryption and signature calculations. An effective defense against this and other DoS attacks are the rate management provisions in the reference implementation. These operate to limit the arrival rate from any client to no more than one packet every two seconds. Excess packets are discarded without incurring cryptographic computations.

* * *

#### 5.1. Client/Server and Symmetric Modes

Client/server mode is the most appropriate for a national time server with thousands of clients. In this case the trusted certificate (TC) scheme is used along with an optional identity exchange such as IFF. The protocol messages, collectively called a _dance_, consist of several exchanges, including the association, certificate, cookie and optional identity exchanges. These exchanges are the logical equivalent of the TLS handshake protocol. They must be processed in a defined order, with each exchange required to be complete before the next one. Requests are retransmitted as required until the corresponding response is received or until timeout.

> Note: An optional design would be to use the TLS handshake protocol as described in <sup>[2](#myfootnote2)</sup>; however, the overhead to use this for multiple associations in embedded systems would be considerable. The Autokey dances accomplished the same thing with far fewer required resources.

The client/server dance begins when the client sends an association request including its X.509 distinguished name and available cryptographic options. The stateless server sends an association response including its X.509 distinguished name and available cryptographic options. The client selects among the available options and sends a certificate request specifying the server distinguished name, which is also the certificate subject name. The server sends the certificate signed by the server private sign key for positive identification.

> Note: The association exchange is also used as an access control filter for named secure groups that share a common broadcast media network in server discovery schemes.

In the current protocol client/server dance the client next sends a cookie request message including its client RSA public key. The server responds with the client cookie encrypted with this key and signed with the server private key. The client verifies the signature using the public key in the server certificate and decrypts the client cookie. This exchange is vulnerable to the cookie snatcher attack described in [Section 4](/reflib/security/#4-autokey-sequence-layer). A modification to this design which does not have this hazard is described in [Section 7](/reflib/security/#7-parting-shots).

The optional identity exchange is designed to defend against an attack where the intruder masquerades as the legitimate server and/or the certificate authority (CA). To begin the identity exchange, the client sends a nonce to the server. The server performs a mathematical computation involving the client nonce, a server nonce and a private identity key. The server sends the result to the client, along with a confirming hash, signed by the server private sign key. The client performs a second mathematical computation involving the public identity key to confirm the server has the correct private identity key and correct certificate. Once the identity exchange is complete, there is no need for further extension fields until the server cookie is refreshed or the association is remobilized.

The security analysis in symmetric modes is similar to client/server mode, except that each peer must run the Autokey protocol independently of the other. In practice, when unsynchronized peer A finds synchronized peer B, peer A runs the protocol until receiving the cookie of B; but, while this is going on, peer B responds to requests, but idles until A is able to provide a valid signature. Once this occurs, B can run the protocol until receiving the cookie of A, at which point both A and B have no further need for extension fields. This exchange has the cookie snatcher vulnerability described in [Section 4](/reflib/security/#4-autokey-sequence-layer). A modification to this design which does not have this hazard is described in [Section 7](/reflib/security/#7-parting-shots).

* * *

#### 5.2. Broadcast Modes

The service model in broadcast mode is considerably different than in the other modes. In common configurations there are from one to several broadcast servers and perhaps several hundred broadcast clients sharing a multi-segment Ethernet LAN interconnected by switches. The identity of the broadcast servers is not configured in advance; they are discovered when the first broadcast packet is received by the client.

In the reference implementation, clients select the broadcast servers using a system of configured filters based on access control lists, server stratum and security options. When Autokey is enabled, an additional filter based on the secure group name can be used. A middleman intruder is highly unlikely, as the packets flow from servers directly to clients; however, without additional protection, it is readily possible for a rogue intruder to masquerade as a legitimate server.

With Autokey, each potential server is associated with a distinct public/private sign key pair and certificate. The certificate is ordinarily obtained via an Autokey exchange. However, if obtained by an Autokey exchange, it might be necessary to execute the exchange for every broadcast packet received, only to refuse the actual broadcast packet.

An autokey values response packet is sent when the key list is regenerated. It includes the three media values, the association ID, timestamp and filestamp. This is sufficient to initialize the autokey sequence, so that subsequent packets can be verified. However, the extension field signature cannot be verified until the client obtains the server certificate. This can be done using a two-way exchange at the same time the propagation delay is calibrated.

A complication occurs when a client shows up between autokey values packets. One approach might be to force the client to wait until the next autokey values packet, but that could take up to an hour. The solution is to include an unsigned association message in every packet sent by the server, except the autokey values packet. The association message includes the association ID and the X.509 distinguished name of the server. Upon receipt, the client runs the client/server dance in order to retrieve the server certificate used to validate subsequent autokey values packets.

The security analysis in broadcast mode has two components. The first is to defend the calibration round that validates the server certificate and calculates the roundtrip delay. The second is to validate the autokey values packet with respect to the server certificate. The calibration round has the same vulnerabilities as in [Section 5.1](/reflib/security/#51-clientserver-and-symmetric-modes), including the cookie snatcher attack. While a cookie snatcher attack can compromise the roundtrip delay calculation, it cannot in general compromise the server certificate. Once the calibration round is complete, the client reverts to listen-only mode and behaves as described in [Section 4.3](/reflib/security/#43-broadcast-modes).

* * *

#### 6. Conclusions

The security threats today are far different than those when the Autokey scheme was first designed in 1996. Routers of that day were extraordinarily dumb by today's standards, so the threat of an intelligent middleman was not considered significant. Among the conclusions reached from the discussion in this document are the following. Further discussion of the vulnerabilities found are in [Section 7](/reflib/security/#7-parting-shots). These conclusions are based primarily on an assumed configuration of a national time server with thousands of clients.

*   In client/server and symmetric modes, the on-wire protocol defends against wiretap attacks, including bogus packets, replay packets and lost packets. In symmetric modes the protocol defends against protocol restarts and packets crossed in flight. In broadcast modes it defends against all but bogus packets and old duplicate packets. In all modes it does not defend against middleman attacks or DoS attacks.
*   The rate management provisions in the reference implementation defend against most forms of DoS attacks, including those targeted on expensive cryptographic algorithms. However, as in other ubiquitous, public applications, the servers are vulnerable in distributed DoS warfare.
*   The message digest layer using symmetric key cryptography defends against middleman attacks, including bogus, message modification and masquerade. However, these provisions are not practical when large numbers of clients are involved.
*   The Autokey protocol is vulnerable in client/server and symmetric modes to the cookie snatcher attack described in [Section 4](/reflib/security/#4-autokey-sequence-layer). This vulnerability results from the ability of a middleman to wiretap client requests, obtain the client cookie and masquerade as the legitimate server. One conclusion reached from this study is that a private message digest key cannot be protected if the server is required to be stateless.
*   The Autokey protocol may be vulnerable in broadcast modes to NTP packet header modification by a middleman; however, this vulnerability does not exist when the client and server are on the same network, even if on different segments connected by switches.
*   The NTP packet header is vulnerable to modification when extension fields are used. Extension fields are used only briefly in the Autokey exchanges that initialize the cryptographic media. Prudent design suggests the NTP packet header data should not be used during these exchanges.

* * *

#### 7. Parting Shots

The analysis in this document has exposed a number of deficiencies in the existing specification and reference implementation. This section suggests a number of changes designed to remedy these deficiencies.

* * *

#### 7.1 Cookie Size

In the design described below, the autokey of [Appendix A](/reflib/security/#appendix-a-autokey-extension-fields) is used for all modes. However, the cookie size of 4 octets is way too small. The size should be increased to match the message digest size, 16 octets with MD5 or 20 octets with SHA.

* * *

#### 7.2. Cookie Snatcher Attack

The cookie snatcher attack described in [Section 4](/reflib/security/#4-autokey-sequence-layer) is the most serious vulnerability exploitable by a middleman. The vulnerability exposes the client cookie, and thus the message digest key. The fundamental problem creating this vulnerability is that the server is required to be stateless. The analysis in this document shows that it is not possible to protect the message digest key unless the server includes some form of private state memory for each client.

A defense against the cookie snatcher attack is to adopt a key agreement scheme such as used by the TLS handshake protocol. In this scheme the cookie is not used and the client sets the message digest key as a nonce. The client then encrypts the key using the server public sign key on its certificate and sends the encrypted key to the server in an agreement exchange. The server decrypts the key and saves it for future use. This might be a topic for future standardization.

As mentioned in [Section 4](/reflib/security/#4-autokey-sequence-layer), the cookie snatcher vulnerability exists in symmetric modes. This vulnerability can be mitigated using an agreement exchange as in client/server mode. However, since the peers maintain persistent state in symmetric modes, an alternate approach might be the Station-to-Station (StS) protocol in <sup>[1](#myfootnote1)</sup> or some modification of it, as suggested in Photures, Oackley or ISAKMP using the Diffie-Hellman (D-H) key agreement algorithm. This might be a topic for future standardization.

The following design considerations apply.

*   The server maintains a message digest key list with an entry for each Autokey client. The entry includes the IP source and destination addresses, the message digest key, and a timeout counter. The entry is updated upon arrival of an agreement request. The timeout counter is initialized upon arrival of an NTP packet and then decrements once per second. The initial counter value is determined from the peer poll interval in the most recent NTP packet . The entry is expunged and garbage collected if the counter reaches zero.
*   There is a hazard in this design when a wiretapper hijacks the client addresses and sends an agreement request with a bogus message digest key, encrypted or not. This can result in an authentication failure for a legitimate client message. In this case, the server returns a crypto-NAK. In response, the client sends an agreement request with a new message digest key. If the wiretapper attacks often enough, the client can never send a successful NTP packet.
*   No matter what agreement scheme is devised, the server is vulnerable to a DoS attack which attempts to exhaust the server resources, in particular, the message digest list storage. Such attacks are mitigated by the rate management provisions in the reference implementation. As in other similar protocols, the server is vulnerable to a distributed DoS attack. There may be defenses against such attacks using a cookie as in Photuris.

* * *

#### 7.3. Certificate Validation

The existing Autokey design assumes no external cryptographic support, such as a trusted certificate authority (CA). The CA function is provided by the Autokey trusted host (TH), which acts as a CA. A more traditional design would use a trusted commercial root certificate in all clients and servers, together with a server certificate signed by the CA for each server. The server certificate would be retrieved by the client using an Autokey certificate exchange as in the present design. There is no need to change the Autokey certificate trail validation procedures, as they are consistent with the X.509 specification.

* * *

#### 7.4. Reference Implementation Improvements

Following are suggested changes in the NTP reference implementation.

*   The Autokey interpretation of the certificate trail coincides with the X.509 specification. However, certain minor changes might be required to resolve the use of an X.509 extension field to identify the Autokey trusted host.
*   If a host is configured with no dependent clients, there is no need to load a sign key pair and dependent certificate. In this case the typical client of a national time server would need no special configuration or key generation and the Autokey dance is reduced to only three exchanges: association, certificate and agreement.
*   The agreement exchange should be implemented as described above. If so, there is no need to load a host key pair.
*   The reference implementation loads a self-signed certificate generated for the host. This certificate can be replaced by a commercial CA root certificate without change in the implementation. Provisions should be added to load a host certificate signed by the CA.

* * *

#### 8. References

<a name="myfootnote1">1</a>  Diffie, W., P.C. Van Oorschot, M.J. Wiener. Authentication and authenticated key exchanges. Designs, Codes and Cryptography 2 (1992), 107-125.

<a name="myfootnote2">2</a>  Dierks, T. The Transport Layer Security (TLS) Protocol Version 1.2. Request for Comments [RFC 5246](https://www.rfc-editor.org/rfc/rfc5246.html). Internet Engineering Task Force, August 2008.

* * *

#### Appendix A. Autokey Extension Fields

![gif](/documentation/pic/sx3.gif)

**Figure A1. Autokey**

The autokey function is used to map a packet header to a message digest key of 16 or 20 octets, depending on the hash algorithm. The function is used for all modes, including client/server, symmetric and broadcast modes. As shown in Figure A1, the autokey function includes four arguments, a 4-octet IPv4 or 16-octet IPv6 source address, a 4-octet IPv4 or 16-octet IPv6 destination address, a 4-octet key ID and a 4-octet _cookie_. It is likely in future that the cookie size will be increased to at least the message digest size.

The first three arguments are public values included in the NTP packet header; the last is either a public or a private value. The MD5 or SHA hash of these four fields is the message digest key used for the hash algorithm of the message digest layer.

Extension fields are normally used only in the Autokey dances before the system clock is synchronized. For packets with extension fields, the cookie value is zero and thus a public value. Extension fields are individually protected by digital signatures. Since in principle an intruder could change the packet header and recompute the message digest, packets with extension fields should not be used for timestamp calculations. For packets without extension fields, the cookie is a private value mutually agreed between server and client.

The Autokey protocol uses one or more extension fields inserted between the NTP packet header and the MAC. The general format of the extension field is shown in Figure A2.

![gif](/documentation/pic/sx4.gif)

**Figure A2. Extension Field Format**

The ER, VN and Code fields specify the operation code and modifiers. The Length field specifies the overall extension field length, including the Length field. The Association ID field specifies the association mobilized in the configuration. The Timestamp field specifies the NTP seconds that the signature was computed, while the Filestamp field specifies the NTP seconds that the associated cryptographic media was created. The optional Value and Value Length fields specify a value, such as a certificate, client cookie or autokey values.

A set of timestamp values is maintained by the client for each Autokey message type. The timestamps are in NTP seconds if the server is synchronized to an authentic source; otherwise, the timestamps have value zero. Timestamps are used to detect and discard old, but otherwise valid, extension fields and avoid expensive signature verifications. If the timestamp fields are valid and a Value field is present, the Signature and Signature Length fields specify the signature of the entire extension field.

In general, extension field messages are either requests or responses. In a request message the Code specifies the operation with both the E and R bits dim; a response message has the same Code as the request with the R bit lit and the E bit lit if an error results. The VN is the version number, currently 2. A request is sent at intervals until a corresponding response is received. In some cases an unsolicited response can be sent without a corresponding request. There are several request messages that can be sent in various scenarios; some, but not all, of which are discussed in this document.