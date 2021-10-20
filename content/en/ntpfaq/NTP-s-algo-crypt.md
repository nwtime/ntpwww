---
title: "5.4. Encryption"
type: "archives"
---

This section discusses the use of encryption and related technology for NTP.

Providing or enabling the use of encryption in software was considered harmful by the USA. However electronic commerce is only possibly with safe data exchange, so use of encryption has become a bit more allowed. NTP version 4 includes no cryptography, from the viewpoint of government regulations, and introduces MD5 keys.

As MD5 is heavily used in digital signatures, MD5 is not considered as cryptography, despite the fact that digital signatures actually _do_ use encryption.

* * *

5.4.1 [What is Encryption used for in NTP?](#541-what-is-encryption-used-for-in-ntp)  
5.4.1.1 [How is Authenticity verified?](#5411-how-is-authenticity-verified)  
5.4.1.2 [Where are authenticated Messages used in NTP?](#5412-where-are-authenticated-messages-used-in-ntp)  
5.4.1.3 [How is Performance affected by Encryption?](#5413-how-is-performance-affected-by-encryption)  
5.4.2 [The Basics of Autokey](#542-the-basics-of-autokey)  
5.4.2.1 [Authentic and Proventic](#5421-authentic-and-proventic)  
5.4.2.2 [Secure Group and Trusted Host](#5422-secure-group-and-trusted-host)  
5.4.2.3 [Identity Schemes](#5423-identity-schemes)  
5.4.2.4 [Proventic Trail](#5424-proventic-trail)  
5.2.4.5 [Session Keys](#5425-session-keys)

* * *

#### 5.4.1 What is Encryption used for in NTP?

Basically NTP uses encryption only for integrity checking and authentication:

* Symmetric keys (shared secrets) are used to prove authenticity of data received over the network.
* Key pairs are used where establishing shared secrets is difficult. The autokey mechanism uses key pairs.

* * *

#### 5.4.1.1 How is Authenticity verified?

Cryptographic hash functions like MD5 have the following properties:

* A large amount of input data produces a small fingerprint (output data).
* Different input creates different output.
* It's not possible to construct some input matching a specific output other than by brute force, or trying at least as many combinations of input that correspond to the key space of the output.

The sender computes a _fingerprint_ consisting of public data plus some secret data (the _symmetric key_), and adds it to the data being transferred. The recipient uses the received data plus the _shared secret_ to compute its own fingerprint in the same way as the sender. Providing a correct fingerprint implies that the sender knows the shared secret, and that the data received wan't changed during transmission.

While the above procedure is not considered to be data encryption, the following procedure using _key pairs_ is: the sender computes a fingerprint of the public data only, but then encrypts that fingerprint with its secret _private key_ of the key pair. Message plus encrypted fingerprint are sent. The recipient decrypts the fingerprint using its _public key_ and compares it the fingerprint computed locally from the public data. If both are the same, it is believed that it's only possible to send the correct encrypted fingerpint when knowing the secret key.

Refer to [this article](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) for an overview of the mathematical properties and generation of key pairs.

* * *

#### 5.4.1.2 Where are authenticated Messages used in NTP?

The uses of authenticated messages in NTP are:

* Remote configuration commands.
* Time messages (authentication is optional).

* * *

#### 5.4.1.3 How is Performance affected by Encryption?

Strong cryptography is computationally expensive. Furthermore, the time required to complete the computations may depend on the actual values being processed in a non-predictable way.

NTP tries to avoid cryptography whenever possibe. MD5 is believed to require almost constant CPU cycles, while public key algorithms are known to require significantly more, and a varying number of CPU cycles.

* * *

#### 5.4.2 The Basics of Autokey

Symmetric key encryption requires a secure channel to exchange secret keys. Every NTP client needs a secret key for authenticating the time messages from a server. Public key cryptography and X.509 version 3 certificates are used for the [Autokey](/reflib/rfc/rfc5906.txt) authentication schema that is summarized below. See [Q: 6.2.2.6](/ntpfaq/ntp-s-config-adv/#6226-how-do-i-use-public-key-authentication-autokey) for configuration details.

As public key algorithms are computationally expensive, those algorithms are not used for every packet being exchanged.

* * *

#### 5.4.2.1 Authentic and Proventic

In [NTP Security Model](/reflib/brief/autokey/autokey.pdf) the phrases are defined like this:

authentic
: A client is authentic if it can reliably verify the credentials of at least one server and the integrity of its messages.

proventic
: A client is proventic if there exists a path to a trusted server where each node is authentic.

* * *

#### 5.4.2.2 Secure Group and Trusted Host

A _secure group_ defines a subset of the NTP network that uses a common _security model_, _authentication protocol_, and _identity scheme_. Each member of a group has _identity parameters_ and a _group key_ provided by some _trusted agent_.

Each secure group has at least one _trusted host_ that operates as _certificate authority_ at the lowest stratum of the group.

A _primary group_ includes at least one trusted primary server (stratum 1).

* * *

#### 5.4.2.3 Identity Schemes

_Identity Schemes_ are methods to prove the identity of a remote system, helping to prevent _man-in-the-middle attacks_. In [NTP Security Algorithms](/reflib/brief/secalgor/secalgor.pdf) and [NTP Security Model](/reflib/brief/autokey/autokey.pdf) the following identity schemes are mentioned:

* **Private Certificate (PC):** much like private keys, requiring a secret channel to distribute keys.
* **Trusted Certificate (TC):** uses a trusted authority (TA) and certificate chains.
* **Schnorr Identity Scheme (IFF):** uses DSA principles.
* **Guillou-Quisquater Identity Scheme (GQ):** based on RSA principles.
* **Mu-Varadharajan Identity Scheme (MV):** based on DSA principles, but does not require trusted clients.

All schemes use relatively small keys (few bits), so those keys must be refreshed regularly. Even though certificates are valid for one year after creation, the keys should be re-created on a shorter interval. Using the NTP timestamp as the certificate's serial number ensures uniqueness. Thus signatures are only generated when the host's time is considered synchronized.

* * *

#### 5.4.2.4 Proventic Trail

According to [NTP Security Protocol](/reflib/brief/secproto/secproto.pdf), a _proventic trail_ (certificate trail) is a cryptographically verified sequence of NTP servers ending at a trusted host.

* * *

#### 5.4.2.5 Session Keys

According to [NTP Security Protocol](/reflib/brief/secproto/secproto.pdf), _session keys_ are 128 bits (16 octets). Session keys are created as lists of keys, and the last key in the list is digitally signed. See [RFC 2104 HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104) for basics.