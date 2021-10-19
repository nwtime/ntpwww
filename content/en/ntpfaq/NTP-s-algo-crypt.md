---
title: "5.4. Encryption"
type: "archives"
---

This section discusses the use of encryption and related technology for NTP.

Providing or enabling the use of encryption in software is (or at least was) considered harmful by the USA. (However electronic commerce is only possibly with safe data exchange, so use of encryption became a bit more allowed recently.) Therefore NTP version 3 was available as _export version_ without DES encryption as well as a non-export version. As `xntpd` is actually an international product developed and improved allover in the world, NTP version 4 includes no cryptography (from the viewpoint of government regulations) and introduces MD5 keys.

As MD5 is heavily used in digital signatures, MD5 is not considered as cryptography (despite the fact that digital signatures actually _do_ use encryption).

* * *

5.4.1. [What is Encryption used for in NTP?](#what-is-encryption-used-for-in-ntp)  
5.4.2. [How is Authenticity verified?](#how-is-authenticity-verified)  
5.4.3. [Where are authenticated Messages used in NTP?](#where-are-authenticated-messages-used-in-ntp)  
5.4.4. [How is Performance affected by Encryption?](#how-is-performance-affected-by-encryption)

* * *

#### 5.4.1. What is Encryption used for in NTP?

Basically NTP uses encryption only for integrity checking and authentication (which effectively is integrity checking):

* symmetric keys (shared secrets) are used to prove authenticity of data received over the network.
* key pairs are used where establishing shared secrets is difficult. The autokey mechanism uses key pairs.

* * *

#### 5.4.2. How is Authenticity verified?

Cryptographic hash functions like MD5 (and SHA) are believed to have the following properties:

* Large amount of input data produce some small fingerprint (output data).
* Different input creates different output.
* It's not possible to construct some input matching a specific output other than by brute force (trying at least as many combinations of input that correspond to the key space of the output).

The sender computes a _fingerprint_ consisting of public data plus some secret data (the _symmetric key_), and it adds that to the data being transferred. The recipient uses the received data plus the _shared secret_ to compute his own fingerprint in the same way as the sender does. It is believed that providing a correct fingerprint implies that the sender knows the shared secret, and that the data received weren't changed during transmission.

While the above procedure is not considered being data encryption, the following procedure using _key pairs_ is: The sender computes a fingerprint of the public data only, but then encrypts that fingerprint with its part (named _private key_ or _secret key_) of the key pair. Message plus encrypted fingerprint are sent. The recipient decrypts the fingerprint using its part (named _public key_) and compares it tho the fingerprint computed locally from the public data. If both are the same, it is believed that it's only possible to send the correct encrypted fingerpint when knowing the secret key.

The mathematical properties and generation of key pairs are not presented here. Look up literature for RSA if you are interested.

* * *

#### 5.4.3. Where are authenticated Messages used in NTP?

The uses of authenticated messages in NTP are:

* Remote configuration commands.
* Time messages (authentication is optional).

* * *

#### 5.4.4. How is Performance affected by Encryption?

_Strong Cryptography_ is computationally expensive. Furthermore, the time required to complete the computations may depend on the actual values being processed in a non-predictable way.

Therefore NTP tries to avoid cryptography whenever possibly. MD5 is believed to require almost constant CPU cycles, while public key algorithms are known to require significantly more, and a varying number of CPU cycles.

* * *

#### 5.4.1. The Basics of Autokey

Symmetric key encryption requires a secure channel to exchange secret keys. Every communication partner (NTP client) needs such a secret key for authenticating the time messages from a server. Therefore public key cryptography and X.509 version 3 certificates are used for a new authentication schema that is summarized below. See the original documentation and [Q: 6.2.2.6.](/ntpfaq/ntp-s-config-adv/#6226-how-do-i-use-public-key-authentication-autokey) for details.

As public key algorithms are computationally expensive, those algorithms are not used for every packet being exchanged.

* * *

#### 5.4.1.1. Authentic and Proventic

In _NTP Security Model_ the phrases are defined like this:

authentic
: A client is authentic if it can reliably verify the credentials of at least one server and the integrity of its messages.

proventic
: A client is proventic if there exists a path to a trusted server where each node is authentic.

* * *

#### 5.4.1.2. Secure Group and Trusted Host

A _secure group_ defines a subset of the NTP network that uses a common _security model_, _authentication protocol_, and _identity scheme_. Each member of a group has _identity parameters_ and a _group key_ provided by some _trusted agent_.

Each secure group has at least one _trusted host_ that operates as _certificate authority_at the lowest stratum of the group.

A _primary group_ includes at least one trusted primary server (stratum 1).

* * *

#### 5.4.1.3. Identity Schemes

_Identity Schemes_ are methods to prove the identity of a remote system, helping to prevent _man-in-the-middle attacks_. In _NTP Security Algorithms_ and _NTP Security Model_ the following identity schemes are mentioned:

* Private Certificate (PC)
* Trusted Certificate (TC)
* Schnorr Identity Scheme (IFF)
* Guillou-Quisquater Identity Scheme (GQ)
* Mu-Varadharajan Identity Scheme (MV)

The PC scheme is much like private keys, requiring a secret channel to distribute keys. The TC scheme uses a trusted authority (TA) and certificate chains. The IFF scheme uses DSA principles. The GQ scheme is based on RSA principles. The MV scheme is based on DSA principles also, but does not require trusted clients.

All schemes use relatively small keys (few bits), so that those keys must be refreshed regularly. Even though certificates are valid for one year after creation, the keys should be re-created on a shorter interval. Using the NTP timestamp as the certificates' serial number ensures uniqueness. Thus signatures are only generated when the host's time is considered synchronized.

* * *

#### 5.4.1.4. Proventic Trail

According to _NTP Security Protocol_, a _proventic trail_ (certificate trail) is a cryptographically verified sequence of NTP servers ending at a trusted host.

* * *

#### 5.4.1.5. Session Keys

According to _NTP Security Protocol_, _session keys_ are 128 bits (16 octets). Session keys are created as lists of keys, and the last key in the list is digitally signed. See [RFC 2104 HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104) for basics.