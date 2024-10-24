---
title: "Suggestions for Protocol and Security Enhancements for the Network Time Protocol"
date: 2023-07-22
description: "This memo by David L. Mills suggests protocol and security enhancements for the Network Time Protocol (NTP), along with a replacement for the Autokey security scheme."
type: archives
---

**[David L. Mills](https://www.nwtime.org/bio/david-l-mills/) (author)**

**[Harlan Stenn](https://www.nwtime.org/bio/harlan-stenn/) (editor)**

#### Abstract

This memo suggests protocol and security enhancements for the Network Time Protocol (NTP) described in [RFC 5905](/reflib/rfc/rfc5905.txt), along with a replacement for the Autokey security scheme described in [RFC 5906](/reflib/rfc/rfc5906.txt).

The primary goals in this memo are to improve synchronization accuracy in all protocol modes. Secondary goals include improved resistance to wiretap and middleman attacks that exploit weaknesses in the error detection and recovery procedures. 

The accuracy and security enhancements proposed in this memo are compatible with the current reference implementation and others in the community. They can be implemented either as incremental changes to the reference implementation or as a standalone replacement.

To acknowledge its ancestry, the proposed design is called NTP-Lite. It is resistant to protocol and security attacks and cryptographic key compromise. It involves various hash, encryption, agreement, and signature algorithms protecting the NTP hosts against wiretap and middleman insurrection.

NTP-Lite is based on UDP and a single port 123 shared with NTP. The proposed onwire protocol supports interleave operations with symmetric, client/server and broadcast modes. The design is based on a protocol machine and a set of messages contained in extension fields appended to the NTP packet header.

Fundamental Axioms for NTP-Lite 

*Law 1:* A packet may not injure a player or, through inaction, allow a player to come to harm.
 
*Law 2:* A packet must obey orders given by players, except where such orders would conflict with the First Law.

*Law 3:* A packet must protect its own existence as long as such protection does not conflict with the First or Second Laws. 

-- Apologies to Isaac Asimov

---

#### 1. Introduction

This memo suggests security and accuracy enhancements for the Network Time Protocol (NTP) described in [RFC 5905](/reflib/rfc/rfc5905.txt), [RFC 5906](/reflib/rfc/rfc5906.txt),  and [technical reports](/reflib/reports/) and conference proceedings.

The accuracy enhancements include new features, such as universal interleave support and more effective algorithms for error management. These algorithms are designed to improve performance while preserving compatibility with the reference implementation described in RFC 5905. The security enhancements include new authentication and provenance algorithms consistent with internet public key infrastructure (PKI) principles.

The  NTP architecture can be represented in three parts: the first part is the suite of protocols and algorithms which are the topic of this memo, the second part is the set of algorithms that mitigate the falsetickers and truechimers according to the Byzantine principles of computer science theory, the third part is the clock discipline algorithm used to synchronize the system clock in time and frequency according to the mathematical principals of electrical engineering. This memo documents the first part; the other parts are documented elsewhere.

The Autokey public key security scheme described in RFC 5906 was implemented over twenty years ago and has been obsoleted in recent times. This memo replaces the Autokey protocols and algorithms with new designs based on current practice. 

Due to its ancestry, including Autokey, the new protocol is called NTP-Lite; however, the new protocol is greatly simplified and free from complicated key computations, as well as unnecessary protocol functions.

NTP-Lite has several advantages over previous versions; these include the following:

* precision interleave support has been extended to all protocol modes,

* client/server and symmetric mode packets use the same format and are processed in the same way. Server mode can be selected by a configuration bit,

* security schemes that depend on persistent secret keys have been replaced by schemes that depend on keys that change with every packet,

* error management schemes using the crypto-NAK message have been replaced by schemes using packet counters,

* the proposed enhancements are compatible with previous NTP versions that use either no security or prestored private key security,

* key expiration and replacement can be performed automatically without operator intervention,

* the certificate trail or provenance is automatically verified without the use of certificate caches.

NTP is designed to synchronize all clocks in the network to international standard time and leap second events. The ultimate goal is to provide synchronization accuracy between tasks running on a single machine comparable to these tasks running on different machines. In principal, a harmonious distributed orchestra can be built with each instrument playing on a different machine.

In a typical configuration a reference clock radio or satellite receiver provides standard time and leap second warning to primary servers operating at stratum 1. Secondary servers operate at increasing strata to provide clock offset and roundtrip delay to dependent applications. 

The principal goal in the NTP-Lite design is to maximize synchronization accuracy, rather than incorporate nonessential timescale and protocol options. This memo does not discuss alternative models or compare one model to another. 

The proposed protocol model is derived from the reference implementation. New features such as the NTP Version 5 proposals, can be implemented without major changes to the format and private key layers. Most new features require only minor changes to the onwire protocol and public key layers.

In the NTP-Lite protocol design, each player sends a packet containing perishable timestamps and protocol messages at every poll event. A message authentication code (MAC) message can be appended to every packet; other messages are not ordinarily used once the cryptographic keys have been determined, since they can affect nominal accuracy, but may be useful for additional security and application functions.

This memo discusses engineering issues important to the NTP-Lite security and protocol design. It does not discuss packet formats, other than for illustration. It does not discuss offline cryptographic key or certificate construction. These functions are available in the current NTP distribution.

At several places in this narrative, the current NTP reference implementation is cited as example. The reference implementation has been updated with many improvements and refinements over the years. Lessons learned extend to the latest designs described in this memo.

Section 1 is this introduction, [Section 2](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#2-protocol-basics) describes the basic building blocks used in the design, [Section 3](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#3-operating-principles) develops the protocols and security algorithms at the heart of the design, [Section 4](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#4-layered-model) describes the layered model, including security considerations and handshake protocol operations, and [Section 5](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#5-miscellaneous-provisions) describes a number of optional algorithms that improve performance while resisting the effects of network congestion and external intervention. [Appendix A](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#appendix-a-security-analysis) summarizes security hazards, including wiretap and middleman attacks.

This memo is designed for programmers familiar with operating system and internet principles, but not necessarily familiar with clock synchronization principles. Readers with experience in these areas can skip directly to [Section 4](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#4-layered-model) on the layered model and protocol enhancements.

***

#### 2. Protocol Basics

This section discusses the basic principles of architecture and design used in NTP-Lite. These concepts are at the heart of the design, including handshake and cryptographic algorithms and data structures.

##### 2.1 Message Principals

An NTP-Lite message is a block of 4-octet (32-bit) words contained in an NTP extension field. One or more messages can be piggybacked on an ntp packet header. The protocol operations and message operations are independent of each other.

The maximum total packet size, including the NTP header plus all extension fields must be less than the MTU of 1500 octets. Extra-long certificates in the order of 5000 octets must be used only in certificate authorities external to the NTP network. This avoids fragmentation and its evil consequences.

The first word of a message contains the block length in the high-order 16 bits and the function code in the low-order 16 bits. The format and interpretation of the function code depends on the whims of the designer and is suggested here for illustration only. The function code includes the message type, response bit and, for MAC messages, the message digest key number. The interpretation of these data are topics for raucous arguments. 

NTP-Lite messages are of two types: request and response. The type is the same for both request and matching response messages, except for a response bit, which is set to 0 for a request message and to one for the associated response message. The critical bit defined in the NTS memos is not used in NTP- Lite.

The rules require that the request message type matches the response message type, except for the response bit. If a mismatch is detected, the response message is discarded and a new request message is sent in the next packet.

Associations are identified by explicit internet address or a cookie consisting of a hash of a message digest followed by the internet address in either 64 or 128 bit format.

By rule, packets can contain request messages or response messages, but not both in the same packet. A single response is ordinarily matched with a single previous request. If a request is sent, but a matching response is not received before the next transmit packet, the request is sent again in that packet. If a request is received instead of the expected matching response, a response to that request is sent instead. If a response is received without a previous matching request, the response is discarded.

##### 2.2 Message Exchanges and Dances

A message exchange consists of a request message from one player followed by a response message from the other player. A handshake dance consists of a sequence of exchanges between players.

Agreement exchanges require that the outcome of a handshake dance is independent of which player starts first or whether a message is lost and repeated in the next packet. This is not a trivial constraint, since it depends on the peculiar semantics defined in this memo.

In client/server mode players operate according to a remote procedure call (RPC) paradigm where the server has no persistent state and the client has persistent state. In symmetric mode each player has persistent state coordinated with the other player.

##### 2.3 Cryptographic Considerations

It is prudent to limit the message size for other than certificates to some reasonable value such as 256 octets or 2048 bits. In this memo, n is the modulus used by cryptographic algorithms. This is also the maximum size of the hash or signature  value used to authenticate NTP packets. The value of n must be shared among all participants in the network.

Cryptographic algorithms are a movable feast where each algorithm has a limited shelf life of about ten years before being replaced by the next version de jour. For the purposes of this memo, the following cryptographic algorithms are supported as default:

* cryptographic hash functions MD5 and SHA compress a text string of indefinite length onto a hash value. The 256-bit hash can be truncated to 160 bits without significant loss of security,

* agreement algorithm Diffie-Hellman computes a value used to determine a shared message digest key,

* public key algorithm RSA encrypts and decrypts blocks using public and private keys,

* symmetric key encryption algorithm AES encrypts and decrypts blocks using a secret key in cipher block chaining (CBC) mode,

* secure signatures use hash function MD5 or SHA to construct the hash of the message digest, then encrypts this value using RSA with a private key. The signature is verified using RSA and the public key, then compares this value with the reconstructed hash value.

##### 2.4 Timescales

A timescale is a mapping from causal events to a continuous scale extending from the indefinite past to the indefinite future. There are two standard timescales associated with NTP: International Atomic Time (TAI) is based on earth revolution about the sun; Universal Coordinated Time (UTC) is based on earth rotation about its axis. Both TAI and UTC run in standard seconds (SI), but UTC diverges from TAI due to earth wobble about its axis.

The NTP timescale is a continuous sequence of eras, where each era spans about 136 years. The current era 0 began at the tropical year 1900. NTP time is coincident with UTC time as broadcast by NIST and other national standards laboratories around the globe. As earth rotation is gradually slowing down, a leap second is inserted in UTC at intervals from a few months to several years.

The only arithmetic operation defined on the NTP timescale is twos complement differences. If the difference between two timestamps in the same or adjacent eras is less than 68 years, the difference can be computed using 64-bit twos complement arithmetic. Timestamp differences are then converted to 64-bit floating double for use in the core algorithms.

##### 2.5 Timestamp and Datestamp Formats

The NTP timestamp format consists of a 64-bit unsigned integer with high-order 32 bits for seconds and low-order 32 bits for fractional seconds. This format represents absolute time from 2.4 ns to 136 years and is used primarily in packet data fields.

The NTP datestamp format consists of a 128-bit unsigned integer with high-order 64 bits for seconds and low-order 64 bits for fractional seconds. This format represents absolute time from the Plank interval to when the universe grows cold. This format is used primarily for conversion between calendar time and NTP time. Conversion of NTP time to other formats and local time zones is performed by the computer operating system.

A timestamp has a size not greater than 64 bits. An undefined timestamp has size 0 bits. A timestamp with size 0 appears as either a no key error or a keyless checksum, depending on application.

A timestamp constant is created by calling the operating system to read the system clock in 64-bit timestamp format with unique name beginning in upper case. A timestamp variable has a value assigned by a timestamp constant or another timestamp variable with unique name beginning in lower case.

There are three types of timestamps in order of increasing accuracy: sofstamps, devstamps and hardstamps, which  are captured from the system clock at specified protocol events. A receive sofstamp is captured when a packet is removed from the input queue, while  a transmit sofstamp  is captured when a packet is added to the output queue. For convenience, sofstamp names begin with the letter s, while devstamp names begin with the letter d.

A transmit devstamp is captured at the output device interrupt, while a receive devstamp is captured at the input device interrupt. Hardstamps require special hardware which may  not be widely available, so hardstamps are not used in the proposed design. Devstamps are the preferred type for all protocol operations.

System clock readings must conform to the [Lamport rules](https://en.wikipedia.org/wiki/Lamport_timestamp#Algorithm), which requires that the readings must be piecewise continuous and positive definite.  This implies that the system clock always moves forward, even if by a small amount, but never stands still or runs backwards.

The physical timestamp routine returns the hardware clock time together  with the clock precision in bits. The library timestamp routine returns the physical clock time corrected for leap seconds and with the low-order non-significant bits replaced by a random bit string. Thus, timestamps are never predictable and roundoff errors are minimized.

##### 2.6 Statistical Considerations

Three decades of online experience have demonstrated that network statistics are best modeled as a quasi-random, [long range dependent (lrd)](https://dl.acm.org/doi/abs/10.5555/1345263.1345300), process, rather than the exponential process often used in computer network traffic analysis. The lessons learned suggest that a simple exponential average does not improve accuracy as the averaging interval increases beyond a point called the Allan intercept. This magical value is usually in the range 5 to 15 minutes.

LRD principles are most important to explain the error statistics of the onwire protocol described in this memo. The characteristics of LRD processes suggest an effective strategy used by the huff 'n puff filter described later in this memo. The filter is particularly effective to avoid asymmetric delays common in overloaded computer networks and is compatible with the proposed onwire protocol and reference implementation.

***

#### 3. Operating Principles

This section discusses basic operating principles and infrastructure support for NTP-Lite. An important question is what the protocol is supposed to do. A short answer is to wrangle a herd of computer clocks to within a few microseconds of each other and international standards and at all times, including leap second events. In addition, the impulse response of the clock discipline loop must be chosen so that a string of client/servers does not show excessive ringing or other transient behaviors.

A fundamental principle of NTP-Lite engineering requires the poll protocol to run continuously in all modes. NTP-Lite messages implement the security and management functions, while NTP packet header timestamps are used to discipline the system clock. A naive observer might describe the protocol as a radio signal where the carrier frequency is the packet rate and the modulation is the piggyback message protocol.

A summary of typical protocol actions is as follows:

* The protocol starts out in nonsecure mode with only the loopback tests for protection. This is the default mode in the reference implementation,

* a private key configuration can be created using either a prestored key or a key produced by an agreement algorithm. This mode is similar to the authentication mode in the reference implementation,

* a public key configuration can be created using a handshake dance. This is similar to the autokey scheme described in RFC 5906,

* a proventic configuration can be created using a handshake dance consisting of parameter, agreement, verify, and signature exchanges. This is similar to the signature cache used by the signature exchange of the Autokey scheme.

##### 3.1 Legacy Compatibility

It is important that the algorithms and protocols defined in this memo are compatible with RFC 5905 and [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf). The new model supports that the legacy security provisions, including the keys file, message authentication code (MAC) format and selection of hash algorithm, should also be retained. It is not necessary to preserve the autokey scheme itself, although some elements of the autokey scheme are used in the various NTP-Lite functions.

It is also important to retain the capability to reconfigure the NTP network in response to link or host failures. In certain configurations this might create a vulnerability to hostile attacks. Creative defenses against such attacks are discussed in [Appendix A](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#appendix-a-security-analysis).

##### 3.2 Infrastructure

A fundamental principle in this memo is that only minimal infrastructure  support is necessary. Thus, DNS address resolution and PKI certificate management facilities may not be available. In particular, private/public keys and certificates must be generated and verified by the hosts that use them.

When certificates cannot be authenticated by PKI means, there is a possibility of a middleman attack that injects a certificate on the provenance trail leading to a fake certificate authority. In the original autokey design there are optional means to verify the provenance trail using the identity exchange. This exchange is no longer needed, since the message digest keys and onwire protocol loopback test perform the same function.

##### 3.3 Time and Security Principles

In the NTP engineering design the time and security operations proceed separately and independently for each association. An association has valid time when the dispersion statistic is less than a defined threshold. The security is valid when the message digest is verified. An association is authentic when both the time and security are valid.

##### 3.4 Two-Way Issues

In broadcast mode a two-way path between the broadcast server and client is needed to compute roundtrip delay. However, in some supported configurations a return path is not available so the roundtrip delay cannot be computed and must be estimated. It is not then possible to retrieve any server data other than the broadcast server packet itself.

The reference implementation supports both one-way and two-way paths. Where a two-way path is available, a client/server exchange can be used to compute the roundtrip delay, then continue using only broadcast packets.

##### 3.5 Access Control and Rate Management

The current reference implementation includes access controls based on internet address filtering and rate restrictions. Optional access controls described in this memo can be provided by the message digest keys and certificate subject name verification. There is no need for additional access control functions in the cryptographic algorithms themselves.

Rate management issues are a critical consideration in the reference implementation. The design is discussed and evaluated in scientific papers and books. The design has been implemented for the NIST public time servers and has performed well under punishing conditions.

An implementation of rate restrictions is described in [Appendix A](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#appendix-a-security-analysis). The basic design is intended for a relatively small number of offenders operating at high packet rates. The rate restrictions are less effective in large flooding attacks, such as DDoS and amplification invasions, where multiple offenders use random source addresses at high packet rates. Packets that violate the rate restrictions are discarded with no further action, except an optional kiss o' death (KoD), message which is intended to restrain the source.

Packet headway is defined as the interval between one packet and the next following packet, both using the same source address. As learned from experience, it is vital that all input packets be subject to headway restrictions, including packets from NTP monitoring and control functions, especially TCP applications.

In the reference implementation the minimum headway is two seconds and the minimum average headway is 30 seconds; packets with headway less than this are discarded. 

The primary consumer of CPU resources is packet rate, which can reach thousands of packets per second. The resources required are substantially independent of packet length or number of messages in the packet. For example, NIST servers routinely battle 3000 packets per second. A significant minority of clients routinely violate the headway restrictions, so the restricted packets are summarily discarded.

Output packet rate restrictions are implemented for each association. This is most important for control and monitoring packets, which use a proprietary packet format. The implementation is driven by a state variable, ceiling in each association, which is set at a configured value as each packet begins transmission, then decrements each second. An output packet is quarantined until the ceiling falls to 0.

Rate restrictions apply both to the NTP packet flows, as well as the security function. As this function often involves multiple exchanges, this may result in excessive acquisition times. The means described below provide a way to minimize the number of packets to complete the handshake dance.

##### 3.6 NTP Secure Network Engineering Principles

This section discusses architectural issues in a generalized NTP network consisting of an acyclic, directed graph organized as a tree with nodes descending from the root node. The nodes correspond to the NTP hosts and the edges correspond to the network paths between them. The network paths include one or more physical links interconnected by routers and firewalls.

The number of nodes between a primary reference node and a client node is called the stratum of that client The network topology is established using the [Bellman-Ford algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm), with stratum as the metric. Note that the network topology can change from time to time due to host or network failures.

The NTP network contains one or more trees, where each tree can be assigned to a secure group. Each group host is considered trusted, while hosts outside the group are considered potential traitors. A number of trees can be arranged as a forest, where an edge of one group can terminate on a host of a different group. The groups of the forest usually have different servers as trust anchors. Each trust anchor and its descendants are associated with a provenance trail that binds each host certificate to the trust anchor.

Each host can communicate directly only with its immediate upstream and downstream hosts. A host can operate as a client or server or both at the same time.

***

#### 4. Layered Model

The architecture model proposed in this memo has a 4-layer design. The format and private key layers verify correct packet format and cryptographic protection, as in  the reference implementation. The onwire layer implements the NTP-Lite onwire protocol that calculates the offset and delay statistics for each player. The public key layer verifies and authenticates onwire calculations using a widely available library of cryptographic functions consistent with public key infrastructure (PKI) principles.

##### 4.1 Format Layer

When a NTP packet arrives, the first layer verifies the packet syntax, in particular, the UDP checksum and format of the extension fields in the packet. If no errors are found, the packet is forwarded to the second layer; otherwise, the packet is discarded as if never sent.

The format scan uses three pointers, a fixed header pointer, a fixed packet pointer and a variable field pointer. The header pointer is set at the end of the packet header.  The packet pointer is set at the end of the packet. The field pointer starts at the header pointer, then increases by the size of each field until the field pointer equals the packet pointer.

In legacy format, if the size of the block measured from the field pointer to the packet pointer is greater than the size of a legacy MAC, the scan continues; otherwise, the scan terminates with this block as the legacy MAC. This provides flexibility and legacy compatibility.

It is convenient to rewrite a legacy MAC as a NAC message. This is can be used for transmit and receive MACs, but not for RFC 5906 MACs where the entire first word is the hash key identifier. Rewriting changes the message size from 0 to the value computed above. The first octet of the legacy MAC is copied to the second octet, and the first octet set as the message type.

##### 4.2 Private Key Layer

The second layer determines whether a packet transmitted by one player is received intact and without errors by another player. Since a valid packet can be modified, duplicated or discarded by a nasty middleman, it is assumed that valid packets are identified by internet address.

Each player generates a message authentication code MAC consisting of the hash of a digest key and the NTP packet header. If the receive mac does not match the transmit mac, the receive packet is discarded. 

The digest key depends on a key number configured in each association and used in the MAC message. The key number is used as follows:

* if the key number is empty or unavailable, private key cryptography is not supported,

* if the key number is in the range 1 to 255, the digest key is the key file entry with that number,

* if the key member is zero, the digest key for a set of trusted players is determined by one of the schemes described below. In these schemes, the packet header hash is extended to include the internet addresses in the packet. This design provides packet authentication as well as  player identification.

The digest key can be determined in one of two schemes called, respectably, static and dynamic. In the static scheme the digest key is a secret shared among a set of trusted players and opaque to other players. In the dynamic scheme the digest key is the loopback nonce included in every packet. The loopback nonce is an unpredictable random variable different for each packet.

These schemes raise an interesting question: is the security protection provided by a shared secret key more or less than a public key which is changed at every packet?

An error is exposed when a received MAC message does not match the corresponding transmit MAC message, in which case the received packet is discarded.

Prestored keys for all associations are stored in a keys file indexed by key number in the range 1-255. A digest key can be selected by key number or a special digest key included in each association as key number 0.

###### 4.2.1 Additional Comments

The OpenSSL library includes just about every hash algorithm likely to be imagined. While historically ambiguous, the International Trade in Arms Regulations (ITAR) prohibits export of the OpenSSL library, so only the exportable MD5 hash algorithm is included in the reference distribution. Alternatively, the OpenSSL library can be imported from foreign or domestic sources, although the resulting product may not be exported from the US.

A collision event occurs when the hash of a bogus packet matches the hash of a legitimate packet. In principle, this can be done by tinkering with the bogus packet contents, but success requires the tinkered packet to satisfy the format and protocol rules.

For the best accuracy, the length of all NTP packets should be nearly the same. Also, the network delay on the client path and server path should be nearly the same. For example, on a 100 Mb/s link, each bit consumes 10 ns, so the delay of a 32-octet message is about 2.6 microseconds, while the delay of a 256-octet packet is about 20.5 microseconds. For a network path where client packets go by satellite and server packets go by landline, the delay difference is some 270 ms.

###### 4.2.2 Agreement Algorithms

This section proposes an agreement algorithm that player Alice can use to send a secret value s to player Bob. The agreement algorithm uses message exchanges as described in this memo; it constructs a secret encryption key using the Diffie-Hellman algorithm. The encryption key is different for each use and does not reveal private values or encryption keys that might be used in a spoof attack.

Players Alice and Bob create random private and public dh keys which  are used only once. The public dh key for Alice is computed as the primitive generator g raised to the power eA modulo a large prime p. The public dh key for Bob is computed in the same way. The values of g and p must be shared by all players.

The agreement exchange is initiated by either Alice or Bob. For instance, Alice sends her dh public key to Bob. Bob sends his dh public key to Alice. Both Alice and Bob compute the agreement result as the dh public key of their twin raised to the power of their own private dh key.

For illustration, assume that Alice intends to send a private value s to Bob. Bob creates his dh private key and dh public key, and sends his dh public key in a request message to Alice. She creates her dh private key and dh public key, then uses the Diffie-Hellman algorithm to construct the encryption key. She then encrypts s using the encryption key.

Alice sends a response message containing two parts: the first part is the encrypted value of s; the second part is the dh public key for Alice. Bob first generates the shared encryption key using the Diffie-Hellman algorithm, then decrypts s using the shared encryption key.

##### 4.3 Onwire Protocol Layer

The third layer describes the onwire protocol used to exchange packets between players and develop statistics such as offset, delay, and skew. The protocol is compatible with the reference implementation using no security or private key security, but not using public key security.

The onwire protocol is designed for two players that send packets to each other at nominal poll intervals. The design uses a packet format with three timestamps and a transmission medium such as the internet, railroad trains, camel caravans, or pony express.

The protocol is self-synchronized and needs no preliminary setup. Retransmissions of old packets are not used; a packet captures only the latest timestamps.

In client/server mode multiple clients synchronize to a single server using a digest key as described above. The server responds immediately using either the same or different digest key.

In symmetric mode two players use the same prestored digest key or a digest key generated as described above. Symmetric players synchronize to other symmetric players or to each other, depending on assigned stratum. Alternatively, two players can synchronize to each other using back-to-back client/server mode.

##### 4.4 Protocol Overview 

The historic onwire protocol includes two variants: basic and interleave, and three modes: symmetric, client/server, and broadcast. These are selected by configuration or online negotiation. The NTP-Lite onwire protocol proposed in this memo combines the variant and mode in a unified design.

The onwire packet format is defined in NTP Version 4 Specification RFC 5905. This format provides three 64-bit packet timestamps, s1, s2, s3. Onwire packets are processed by a single routine, as described below in this memo. The devil is in the details.

###### 4.4.1 Protocol Overview

Each player has persistent timestamp variables t1, t2, t3, t4, and a shared packet with variables s1, s2, s3.

The transmit sofstamp primitive sends a packet and returns the time when the packet joins the output queue. The transmit devstamp primitive returns the time at the output device interrupt, while  the receive devstamp primitive returns the time at the input device interrupt.

The goal of the onwire protocol is to compute state variables offset, delay, and skew for each player in both symmetric and client/server modes. 

###### 4.4.2 Basic Operations

The onwire protocol generates a round for each player. In legacy mode, a round produces timestamps t1, t2, t3, t4 for each player; in NTP-Lite mode a round produces only t1 and t2 for each player, so two rounds are required to produce timestamps t1 and t2 from the first round and t3 equals t1 and t4 equals t2 from the second round.
	
The A round consists of a packet from player A at t1  to player B at t2 followed by a packet from player B at t3 to player A at t4. The B round consists of a packet from player B at t1 to player A at t2 followed by a packet from player A at t1 to player B at t2. Note that the second packet of the A round is coincident with the first packet of the B round.

A status packet is recognized when all packet variables are 0. This packet is used for player initialization and error recovery.

Player A begins with a script setting packet timestamps s1 equal s3, then the player sends the packet with s3 equals transmit sofstamp. At the end of transmission t1 equals transmit devstamp.  Player B receives this packet and sets s2 equals receive devstamp.

At the next poll opportunity, player B sends a packet using the same script as player A, but with players A and B interchanged. Player A receives this packet and sets t2 equals s2, t3 equals s3, and t4 equals receive devstamp. At the end of both rounds, each player has timestamps t1, t2, t3, t4 to compute offset, delay, and skew, as described later.

A player compares s3 with t3. If equal, player A has timestamps t1, t2, t3, t4 to compute offset, delay, and skew.

A packet with format or MAC errors is immediately discarded. If the packet timestamps are all 0, this is an information packet and may contain error information. If s3 does not equal t3, the timestamps are ignored; otherwise, the  packet is processed in the same way as player A.

Client/server mode is like symmetric mode, but the server keeps no persistent state and sends the reply packet immediately after the client packet has been received. The server nonce is generally ignored. The choice of client/server or symmetric mode is determined by a server configuration bit.

Transmit sofstamps s1 and s3 are created just before a packet is queued for transmission. Receive devstamp t2 is created at the input device interrupt. Sofstamps s1 and s3 are replaced by devstamps t1 and t3 as the protocol proceeds.

In legacy format the loopback nonce is determined by the transmit sofstamp; however, this might not be considered sufficiently random as a nonce. In such cases, the loopback nonce can be provided by a random number generator.

In each player round s1 and s3 use transmit sofstamps, while t2 and t4 use receive devstamps. The transmit sofstamps are replaced by transmit devstamps as the protocol proceeds.

Note that each player can produce measurement data independent of the other player. If two players are synchronized to each other, the players will loop forever with increasing stratum, unless one of the players is synchronized to a third player.

The results includes offset = ((t2 - s1) + (t4 - s3))/2, delay = (t4 - s1) - (s3 - t2), and a new statistic skew = (t2 - s1) - (t4 - s3). If the huff 'n puff filter is available, it is inserted at this point.

###### 4.4.4 Additional Remarks

If the hash or signature size is too large, it can compromise timing accuracy; if too small, it can compromise security. The choice of hash size depends on the hash algorithm. For instance, a common choice is a 160-bit or 20-octet hash size using the SHA160 algorithm, as in the current reference implementation. The reference implementation's hash or signature algorithm can be specified for each key in the keys file. In principle, the algorithm can be specified for the association as well, providing an independent choice of hash or signature algorithm.

###### 4.4.5 Error Processing

A longstanding tool used in legacy error recovery has been the crypto-NAK message, but this message can be hijacked by a determined intruder and used to disrupt the protocol. In this memo, a special packet counter is used by each player for error recovery. The counter is incremented for each packet sent and is set to 0 for each valid packet received. Invalid packets with security or protocol errors are discarded without affecting state variables.

If a packet counter exceeds a defined threshold, the player is restarted, which clears all state variables including the digest key. Since the restarted player can produce only nonsecure packets, the other player will eventually restart in the same way.

Additional discussion on error management strategies is in [Appendix A](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#appendix-a-security-analysis).

###### 4.4.6 Broadcast Mode

In broadcast mode accuracy can be improved using interleave protocol principles. The broadcast server has state variable dev, while the broadcast client has state variables xmt and dst.

The broadcast server packet includes a MAC containing the packet signature using the server private key. The MAC is verified by the client using the public key on the server certificate. This design protects against packet modification but not duplication or kidnap. 

The server sends packets at nominal poll intervals. Each packet includes torg = transmit devstamp dev from the previous round and transmit sofstamp txmt from the current round. After the packet has been sent, dev = transmit devstamp.

A client receives the server packet and computes torg - xmt. If this value is less than a defined threshold, the packet offset = torg - xmt; otherwise, the packet is either an old duplicate or the first packet received after one or more lost packets.

The delay is either estimated or computed in a previous client/server exchange. This design supports both legacy and interleave broadcast modes using the same packet stream.

##### 4.5 Public Key Layer

The fourth layer functions in a manner similar to the NTS handshake protocol but is greatly simplified in NTP-Lite.

###### 4.5.1 Security Model

A provenance function is used to verify the certificate trail. Public/private keys and certificates are generated individually by each player.

The goal of the security scheme is to authenticate each client relative to an upstream server using cryptographic hash functions and public certificates. In the preferred implementation, the security scheme evolves as follows.

In the basis step, the certificate authority host is designated proventic by some means external to the network. In the inductive step, each association requests its server to sign and return the client certificate. If the server is designated proventic and the signature is verified, the client is designated proventic; otherwise, the request is ignored and can be sent again in a following packet.

By induction, eventually all certificates will be signed and designated proventic. A host is considered authentic when the MAC messages  have been confirmed and the certificate has been signed by the next ascending host on the trail to the certificate authority. Note that this model does not construct the provenance trail in each client host. In former designs, this was achieved using a persistent certificate cache which had to be updated on a regular basis.

Both the former Autokey and proposed security models are potentially vulnerable to a middleman that masquerades as a certificate authority. A dependent client may believe the signature of its certificate is valid. The original defense against this vulnerability was the Schnorr (IFF) identity scheme described in RFC 5906. The provenance scheme proposed in this memo replaces the identity scheme while performing the same function. 

###### 4.5.2 Handshake Dance

An important feature of the design is that a layer must be verified before the next higher layer is processed. This simplifies error detection and recovery when the message digest key is unavailable or applications do not require security provisions.

The handshake dance produces the message digest key used in subsequent packets. It consists of an ordered sequence of exchanges beginning with the agreement exchange followed by the  parameter exchange, verify exchange, and signature exchange, in that order.

The agreement exchange calculates the shared message digest key used by subsequent NTP packets. The parameter exchange sends the certificate and default cryptographic parameters of each player to the other player. The verify exchange confirms that the key computed by one player matches the key computed by the other player, but without revealing the key itself. In the signature exchange the server signs the client certificate, which is then verified by the client.

The agreement packets are normally transmitted without cryptographic protection, so the preferred protection is the loopback test and packet syntax check. Once the dance has completed for the first time, the verify and signature exchanges are sent occasionally as a sanity check.

In the signature exchange the client certificate is signed by the server using its private key and verified by the client using the server public key. In order to validate the certificate lifetimes, the signature exchange is delayed until the system clock has been synchronized. The message digest key remains until replacement, in which case the handshake dance restarts from the beginning.

The certificate authority host is designated either by a self-signed certificate or by an identifier in the X509v3 extension field. New certificates replace old ones with the same subject and issuer names. Note that the certificate authority host can be either the root server host in the network or an external certificate authority host connected by an appropriate communication means.

By default, the subject name on the host certificate is the string returned by the Unix `gethostbyname` library routine. The subject name on the certificate authority is interpreted as the group name associated with the particular trail and is useful in the identity exchange or equivalent scheme.

The provenance trail is constructed for each association separately. At each step the issuer name on the client certificate is replaced by the subject name on the server certificate. Note that each step involves a single signature, not the entire provenance trail. Once the trail has been verified, it is not necessary to do it again, unless a certificate is revoked or reaches advanced age. Note that each association might have a certificate with different issuer and subject names.

As part of the initialization process, a self-signed host certificate is generated for each association. If the host certificate has not been signed by the server for each association, the host certificate is provided to each association server for signature.

Once the provenance trail signatures have been verified, the client certificate is considered authentic. If a certificate has been changed on the provenance trail, the scheme to update the trail could be tedious. Note that there are no provisions in the security scheme to revoke a certificate, so this must be done by external means.

###### 4.5.3 Handshake Operations

In the following, the server certificate and private key belong to the server, while the client certificate and public key belong to each client association separately. The sequence of exchanges in the handshake dance can best be managed by appropriate state tables and transition rules. These dances are similar, but not identical to the ones used in the RFC 5906 Autokey implementation.

An optional feature is to verify the subject name on the received certificate. The name is valid if it matches an entry on a private list of host names in the NTP network. The list must be constructed in advance. Note that the signature algorithm is defined on each certificate. Otherwise, the signature algorithm defaults as in the parameter exchange.

A complication is how to validate the lifetime of the certificates along the provenance trail to the certificate authority. There are two axioms: a valid timestamp must lie within the lifetime specified by the not before and not after fields of the host certificate. The lifetime of a subject certificate intersected with the lifetime of its issuer must not be empty.

The proposed solution is to wait until the clock has been synchronized, then run the signature exchange to update the lifetimes. A violation results in a  protocol error. A new certificate might require a new generation of its issuer. The implications may be tedious.

The original Autokey protocol was based on the assumption that the cryptographic algorithms were very slow and vulnerable to a flooding attack. In fact, the Diffie-Hellman agreement took over 10 seconds on a Sun IPC.

As current machines and algorithms are much faster, public key cryptography is an appropriate means to protect broadcast packets. The broadcast server packet contains the transmit devstamp of the previous round and the transmit sofstamp of the current round. The MAC message contains the signature of the packet using the broadcast server private key; the broadcast client verifies the MAC using the public key of the server certificate. This is not a trivial requirement; the provenance trail must be constructed separately.

***

#### 5. Miscellaneous Provisions

The following sections describe several improved protocol and security algorithms useful in protocol designs. Many of these algorithms are optional and can be reordered in various ways.

##### 5.1 The Huff 'n Puff Filter

Measurements of offset and delay can be severely affected under conditions of extreme network congestion and asymmetric network delays. This section considers ways and means to reduce errors due to these causes using probabilistic analysis and measurement techniques.

The huff 'n puff filter (HPF) is an improved version of a design used in the reference implementation for several years. It is most effective on DSL tail circuits when traffic is concentrated in one direction or the other during busy daytime hours and largely quiescent during nighttime hours.

The HPF is positioned just after the relative offset, roundtrip delay, and sample skew have been measured, as explained in [section 4.3](/reflib/enhancements/suggestions-protocol-and-security-enhancements-ntp/#43-onwire-protocol-layer) of this memo. The skew represents the difference between the outbound and inbound delays. If the absolute value of the skew is less than a defined skew threshold, the measurements are passed directly to the mitigation algorithm; otherwise, the measurements are passed to the congestion management algorithm.

The default for the latter algorithm is to discard the measurements, so the clock discipline maintains its current heading. A design for the congestion management algorithm is a topic for further study, but it is not discussed in this memo.

The congestion threshold can be set during quiet nighttime hours and automatically kicks in during busy daytime hours. This avoids frequency surges that can cause significant time errors.

If the inbound or outbound delays are less than the offset, or if the skew exceeds the roundtrip delay, the system clock will be set backwards, which violates the Lamport rules, so the sample is discarded. This consideration is most important in high precision networks using client/server mode.

An interesting approach is to use artificial intelligence (AI) to learn the relevant statistics and evolve countermeasures that avoid daytime congestion for optimum performance under specific and local conditions.  

##### 5.2 Leap Second Processing

This section describes how a leap second event is implemented by the onwire protocol and distributed to the general population. 

The NTP-Lite protocol provides precision global time relative to international standard time for all players in the worldwide internet. This means that a contract designed to begin at global midnight in Singapore will be executed at the same global time in Moscow. This also means that a leap second event is implemented at the same global time in all supercomputers, laptops, and wristwatches everywhere, before and after the leap. This is also necessary to preserve the transient response to a leap event along a string of servers and clients.

As a practical matter, NTP primary servers determine the UTC time and leap day indicator from national radio and satellite broadcasts. Primary servers set the leap day indicator from the attached radio or satellite receiver. The leap day indicator is propagated to all dependent hosts by the onwire protocol. If multiple associations are on the same host, the host leap day indicator is set by the mitigation algorithms.

By [international consensus](https://www.cl.cam.ac.uk/~mgk25/time/metrologia-leapsecond.pdf) the global timescale is retarded by one second following the last second of the leap day, effectively repeating the last second of the day. However, the Lamport rules require that the global timescale be piecewise continuous and positive definite. These rules are implemented by a kernel state machine described in [RFC 1589](/reflib/rfc/rfc1589.txt). The local clock reading increases by the execution time of the clock reading routine.

A deeper understanding of the leap event can be displayed on a graph showing global time on the x axis and local time on the y axis. There are two 45 degree lines, an upper global timeline and a lower leap timeline. At every point on the x axis a vertical line intersects the two timelines as it moves from past to future. At this point the two timelines are separated by one second in both the x and y directions. The trick is to devise a transition function from the global to the leap timelines beginning at the leap time.

The consensus model requires a negative one second step connecting the timelines at the leap event. But this violates the Lamport rules. The negative step can be replaced by a horizontal line beginning at the leap time on the global timeline and extending to the leap timeline one second later. This is the classic algorithm implemented in the reference implementation for the last 35 years.

###### 5.2.1 Virtual Timescales

Purists insist that an optional virtual timescale is available to smooth the clock readings at and near the leap event. However, the current design is necessary for precise timekeeping to the microsecond level. 

The need for a virtual timescale is problematic at best, since the current design effectively disguises the leap event, while satisfying the Lamport rules. Applications such as stock trading and air traffic control need an accurate clock infrastructure as required by government regulations.

In the grand scheme of things, civil time is affected by seasonal jumps of one hour and occasional jumps of one day or more. A virtual timescale can be implemented using a library routine without affecting the protocol operations.

A well-known problem in older radio timecode receivers is the delay following the leap event for the radio to synchronize to the new timescale, which can take a few minutes. The kernel clock discipline freezes the indicated time offset following the leap event until a programmed delay called the stepout interval of 600 s. However, the stepout interval is short circuited when the offset drops below the step threshold of 128 ms.

The virtual timescale should never be used for transmitted packets; to do so can cause clockhopping and  invites network chaos.

***

#### 6. References

1. Mills, David L. [Network Time Synchronization: the Network Time Protocol on Earth and in Space](/reflib/book/), Second Edition. CRC Press 2011, 466 pp.

2. Mills, D., J. Martin (Ed.), et al. [Network Time Protocol Version 4: protocol and algorithm specification. Request for comments RFC 5905](/reflib/rfc/rfc5905.txt), Internet Engineering Task Force, June, 2010.

3. Mills, D., B. Haberman (Ed.). [Network Time Protocol Version 4: Autokey Specification. Request for Comments RFC 5906](/reflib/rfc/rfc5906.txt), Internet Engineering Task Force, June, 2010.

4. Mills, D., D. Plonka and J. Montgomery. [Simple Network Time Protocol (SNTP) Version 4 for IPv4, IPv6 and OSI. Network Working Group Report RFC 4330](/reflib/rfc/rfc4330.txt), University of Delaware, December 2005, 27 pp.

5. Mills, D.L. [Network Time Protocol (Version 3) Specification, Implementation and Analysis. Network Working Group Report RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf), University of Delaware, March 1992, 113 pp.

6. [White papers](/reflib/papers/) on the design and implementation of NTP servers and clients.

7. Mills, D.L. [A kernel model for precision timekeeping. Network Working Group Report RFC 1589](/reflib/rfc/rfc1589.txt), University of Delaware, March 1994. 31 pp. ASCII.

8. RA Nelson, et al. [The Leap Second: its History and Possible Future](https://www.cl.cam.ac.uk/~mgk25/time/metrologia-leapsecond.pdf) (2001), Metrologia 38 509

9. Lamport, L. [Time, Clocks and the Ordering of Events in a Distributed System](https://amturing.acm.org/p558-lamport.pdf), Communications of the ACM, Volume 21 Number 7 (July 1978), 558-565.

10. Cristian, F. [Probabilistic clock synchronization](https://web.eecs.umich.edu/~manosk/assets/papers/Cristian.pdf), Distributed Computing 3, 146-158 (1989).

11. Rezaul, Karim Mohammed and Grout, Vic. [An Overview of Long-Range Dependent Network Traffic Engineering and Analysis: Characteristics, Simulation, Modelling and Control](https://dl.acm.org/doi/10.5555/1345263.1345300), ValueTools '07: Proceedings of the 2nd international conference on Performance evaluation methodologies and tools, October 2007, Article No.: 29, pp 1-10 

***

#### Appendix A. Security Analysis

The following sections of this appendix analyze security issues in the NTP-Lite onwire protocol described in this memo. The goal of this analysis is to explore specific security hazards and devise generic mechanisms to avoid them.

##### A.1 Secure Key Generation

There are two kinds of keys used in this memo. Temporary keys are generated and used only once. Persistent keys are generated before first use and last potentially forever.

Persistent keys must be rolled over from time to time in order to frustrate urban dogfights. A rollover can be triggered by a packet counter or operator command.

A generic timestamp has size 64 bits, where the high-order significant bits are derived from the system clock and the low-order non-significant bits are replaced by a random bit string. This improves randomness and minimizes roundoff errors.

##### A.2 Security Provisions

The security provisions in the NTP-Lite onwire protocol proposed in this memo depend on three security principles:

* all packets are protected by private key cryptography and hash or signature algorithms,

* missing and duplicate packets are detected using nonces and loopback tests without needing insecure sequence numbers or timestamp comparisons,

* packet counters reveal errors resulting from obsolete keys, protocol errors. or external tinkering without using  insecure crypto-Nak messages.

Cryptographic algorithms depend on random keys that are not disclosed and are extremely difficult to simulate.  The primary use of these algorithms is to verify that packet contents have not been modified in transit. A secondary use is to generate nonces used in loopback tests.

Cryptographic keys have size between 64 and 256 bits, which is consistent with current industry practice. A 64 bit random key can be generated as a transmit timestamp, while a larger random key can require a random number generator.

##### A.3 Packet Counters

The packet counters protect the onwire protocol against invalid or fabricated packets or security compromise of one or both players. Each player increments its packet counter for every transmit packet and sets the counter to zero upon receipt of a valid packet. If the counter overflows a defined threshold, the player restarts the protocol by clearing all state variables and keys, then continues as required by the protocol rules.

The players exchange packets continuously regardless of packet errors lost or duplicate packets. Each packet updates the packet timestamps according to the onwire protocol rules. Operation continues as long as the loopback test is satisfied. The restart rules require that each player passes the loopback test, then players continue as described previously.

The counter overflow strategy can be compared with the previous strategy using the crypto-NAK message from a trusted or untrusted agent. This strategy is deprecated in this memo due to its vulnerability to external intruders.

###### A.3.1 Internet Spy Hazards

The internet spy dictionary defines wiretap and middleman spy tools. A wiretapper can copy packets for further use, but cannot modify them or divert their destinations. The wiretap tool is most effective on shared networks such as ethernet segments.

A middleman can use the wiretap tool and in addition divert selected packets to a covert facility. There, a spook can tinker with the packet contents, then forward the packet to the same or some other destination. In fact, the federal government [CALEA regulations](https://www.fcc.gov/calea) require common carriers to provide similar facilities to support law enforcement activities. The middleman tool is most useful on routers and firewalls.

A middleman can insert or remove protocol messages in a secure or nonsecure packet, especially agreement request or response messages. The intent is to disrupt the agreement exchange or create misleading data.

These vulnerabilities are mitigated by  two provisions.

* agreement packets are discarded if the packet is not authenticated by other means,

*  non-authenticated packets must pass loopback and packet counter tests.

##### A.4 Protocol Restart

When an NTP-Lite protocol restarts or begins life, it runs the onwire protocol in nonsecure mode to exchange packets and synchronize state variables. As defined in this memo, the message digest key is compromised or unavailable and leaves the loopback test as the primary deterrent against unwelcome dogcatchers.

A typical restart sequence begins when the state variables and keys for each player are  undefined or zero. Each player runs the transmit and receive routines as described in the main body of this memo.

The loopback test confirms that the player is synchronized. The next step is to run the agreement algorithm to generate the digest keys.  The onwire protocol continues as described previously. This may or may not result in a violation of the protocol rules. Other versions of this attack and defense are also credible.

An intruder can snatch a packet and replay it after a programed delay. If the delay is less than the poll interval, the delayed packet simply refreshes the state variables, then flees down a rabbit hole. In any case, a replayed packet that survives these tests is usually discarded by the mitigation algorithms.

A directed attack on the protocol itself might allow a genie conjuring the hash key to invent fake handshake exchanges in any order and at any time. The handshake dance resists these intrusions using a combination of the key and onwire protocol rules.

For instance, NTP clients generate requests, never responses; NTP servers generate responses, never requests. Symmetric players generate either requests or responses according to the protocol rules.

A sneaky genie can seize a secure packet and amputate the MAC message, leaving a nonsecure packet behind. An immature implementation might allow a nonsecure packet to alter its receive or transmit timestamps. 

The protocol rules provide correct recovery in case of public key changes or server secret key updates. While this design invites a terrorist to disrupt the protocol by injecting a bogus agreement exchange, the insult is caught in the verify exchange. The result might or might not be considered a vulnerability, but in any case it represents a potential denial of service opportunity.

##### A.5 Handshake Dance Protection

The handshake packets are protected by the first three protocol layers and must have length less than the MTU. The packet syntax and semantics must be consistent with the exchange type; in particular, the response operation code must agree with the request operation code, except for the response bit. 

While it is cryptographically hard to masquerade as a valid client or server, a clever middleman can simply change a packet to intentionally cause an error. Done often enough, the result represents a denial of service opportunity.

The handshake dance is protected by the onwire protocol rules and cryptographic defenses. The parameter request includes the subject name on the client certificate; the parameter response includes the subject name on the server certificate. These names can be verified by the client or server association.

Attacks on certificates or public keys are detected in the verify and signature exchanges. In particular, a successful verify exchange is strong evidence that the working key for each player is identical and not visible to snoopers.

The most likely result of a compromised agreement exchange is a handshake restart, rather than a false agreement. If the adventure is not scrubbed by the loopback test, this can cause an external entrapment or internal surprise ambush.

A significant disruption is likely when a new public/private key and certificate are generated in the middle of the provenance trail. This requires recomputing the new certificate signature in the immediate upstream hosts and the immediate downstream hosts.

In broadcast mode, the most popular attack is to repeat old valid messages. Ordinarily, these are suppressed by the interleave broadcast protocol described above; however, protocol restarts and lost packets might result in disordered messages. The enlightened response is to run a timeout upon receiving a valid message and terminate it upon receiving a message with a later timestamp. Note that a terrorist cannot construct a valid message, as it cannot construct a valid signature.

##### A.6 Distributed Denial of Service (DDoS) Attacks

Of the threat scenarios, a distributed denial of service DDoS attack is potentially the most disruptive. A DDoS attack can be created by one or more fraudsters using fake packet source addresses randomly distributed over a wide range. A fundamental principle of defense strategy is that the CPU cycles to identify and discard a fake packet must be much less than the CPU cycles necessary to process it.

The reference implementation includes an effective defense against DDoS attacks using a most recently used MRU list. Each entry on the list includes the packet source address and process time of arrival. The process time is implemented by a counter which increments once per second, independently of the system clock.

When a packet arrives, the MRU list is searched for an entry matching the packet source address. If found, the packet headway is computed as the current process time minus the entry process time. If the headway is less than two seconds, the packet is discarded; otherwise, the entry process time is set to the current process time and the packet is queued for the onwire protocol.

If the new entry source address does not match an entry already on the MRU list, the new entry is inserted before the first entry and initialized with the source address and current process time. If the new arrival causes a MRU list overflow, the last entry on the list is amputated.

This design has worked well in the reference implementation operating in the NIST time servers over the last several years; however, this design does not work well when the spam of fake addresses found well exceeds the size of the MRU list. In an extreme DDoS attack, fake packet source addresses are randomly distributed over a relatively wide range. Samples are drawn from an approximately uniform distribution that maximizes the entropy and simulates white noise.

The mission then is to extract valid sources, if any, from the interfering population. This may be extremely difficult using the assumed probabilistic model in this memo. In the most extreme case the MRU list may converge to a state where all entries have occurred only for the first time. In the reference implementation, the result is a call on the onwire protocol for every packet arrival and produces no useful result. This condition can be avoided if the protocol is modified to suppress the first occurrence, but this may create new hazards yet to be explored.

In the reference implementation, the MRU list has 700 entries, so at 3000 packets per second, the MRU list will overflow in a few seconds. The processing rate is the total number of entries on the MRU list divided by the total elapsed process time. The processing rate can be used in a scheme to discard arriving packets as the rate increases above a threshold. Note that a DDoS attack cannot be differentiated from an overflow of legitimate traffic. There might be other schemes using the processing rate or list overflow as well.

##### A.7 Amplification Attacks

In the NTP-Lite protocol described in this memo, an amplification hazard is when a small request packet results in a large response packet. This can be avoided by including a dummy placeholder in the request packet, so that the response has the same length as the request. This is considered a waste of network resources and is unnecessary in the protocol described in this memo.

In NTP-Lite there are no instances of significant differences between the lengths of request and response packets, except for the agreement exchange in client/server mode, as described previously. This is not considered an amplification attack, since a flood of bogus agreement packets is detected by rate management and the flood packets are discarded before responses are generated.

##### A.8 Data Minimization

A hazard has been identified when a wiretapper can learn something about client location using packet header values. A partial solution in client/server mode is to replace the client transmit sofstamp xmt with a 64-bit random nonce. The server packet will have org = xmt and pass the loopback test, then the transmit devstamp dev replaces org. This solution is not applicable to symmetric mode.

##### A.9 Broadcast Hazards

The NTP reference implementation includes a number of broadcast modes, including IPv4/IPv6 broadcast, multicast, and manycast modes. These modes pose a significant hazard when a terrorist attempts to clog the broadcast client with a stream of broadcast server messages with fake internet addresses at extreme rate. These hazards can be deflected by the packet signature and by access controls and rate management.

Manycast mode might be useful to the pool community; however, this poses a unique hazard. The manycast client begins by broadcasting a client request packet. One or more manycast servers reply with a unicast server response packet. The client selects the server based on server parameters, such as stratum. The client and selected server proceed as in ordinary client/server mode.

The multicast model presents unique challenges for security schemes. Apparently, each potential server must run a separate handshake dance. The client must save server data for later review and selection. 

The handshake dance is protected by the onwire protocol. Ongoing traffic is protected by the working key as usual; however, a middleman can overload the manycast servers with a flood of manycast client packets. Potential pool clients can use this mode, but are advised to use carefully tailored access controls.

There are additional scenarios where an attacker can overload the servers or clients with multiple passive associations. These include a flood of fake broadcast server or symmetric active probes using bogus source IP addresses. These packets might result in a broadcast client or symmetric passive peer to allocate and initialize a flood of passive associations. The result can be depletion of processor and memory resources.