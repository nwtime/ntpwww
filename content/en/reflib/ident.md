---
title: "Autokey Identity Schemes"
type: archives
toc_hide: true
---

![gif](/archives/pic/alautun4a.gif)

[Maya glyph _alautun_](/reflib/maya/)

#### Table of Contents

*  [Briefing Slides](/reflib/ident/#briefing-slides)
*  [Related Pages](/reflib/ident/#related-pages)
*  [Introduction](/reflib/ident/#introduction)
*  [Private Certificate (PC) Cryptosystem](/reflib/ident/#private-certificate-pc-cryptosystem)
*  [Schnorr (IFF) Cryptosystem](/reflib/ident/#schnorr-iff-cryptosystem)
*  [Guillou-Quisquater (GQ) Cryptosystem](/reflib/ident/#guillou-quisquater-gq-cryptosystem)
*  [Mu-Varadharajan (MV) Cryptosystem](/reflib/ident/#mu-varadharajan-mv-cryptosystem)
*  [Selected Publications](/reflib/ident/#selected-publications)

* * *

#### Briefing Slides

*   NTP Security Model [PDF](/reflib/brief/autokey/autokey.pdf)
*   NTP Security Algorithms [PDF](/reflib/brief/secalgor/secalgor.pdf)
*   NTP Security Protocol [PDF](/reflib/brief/secproto/secproto.pdf)

* * *

#### Related Pages

*   [Autonomous Configuration](/reflib/autocfg/)
*   [Autonomous Authentication](/reflib/autokey/)
*   [Autokey Protocol](/reflib/proto/)
*   [Autokey Identity Schemes](/reflib/ident/)

* * *

#### Introduction

While the identity scheme described in [RFC 2875](/reflib/rfc/rfc2875.txt) is based on a ubiquitous Diffie-Hellman infrastructure, it is expensive to generate and use when compared to others described here. There are five schemes now implemented in Autokey to prove identity: (1) trusted certificates (TC), (2) private certificates (PC), (3) a modified Schnorr algorithm (IFF aka Identify Friendly or Foe), (4) a modified Guillou-Quisquater algorithm (GQ), and (5) a modified Mu-Varadharajan algorithm (MV). The TC scheme, which involves a certificate trail to a trusted host, is discussed on the [Autokey Protocol](/reflib/proto/) page. Each of the others involves generating parameters specific to the scheme, together with public and private values used by the scheme.

In order to simplify implementation, each scheme uses existing structures in the OpenSSL library, including those for RSA and DSA cryptography. As these structures are sometimes used in ways far different than their original purpose, they are called cuckoo structures in the descriptions that follow.

![gif](/archives/pic/xchange.gif)

In the challenge-response schemes client Alice asks server Bob to prove identity relative to a secret group key _b_ provided by a trusted authority (TA). As shown in the figure above, client Alice rolls random _nonce1_ and sends to server Bob. Bob rolls random _nonce2_, performs some mathematical function and returns the response along with the hash of some private value to Alice. Alice performs another mathematical function and verifies the result matches the hash in Bob's message.

Each of the five schemes is intended for specific use. There are three kinds of keys, trusted agent, server and client. Servers can be clients of other servers, but clients cannot be servers for dependent clients. In general, the goals of the schemes are that clients cannot masquerade as servers and servers cannot masquerade as trusted agents (TAs), but they differ somewhat on how to achieve these goals. To the extent that identity can be verified without revealing the group key, the schemes are properly described as zero-knowledge proofs.

The four identity schemes described here have different design goals and are intended for specific application. The PC scheme is intended for one-way broadcast configurations where clients cannot run a duplex protocol. It is essentially a symmetric key cryptosystem where the certificate itself is the key.

The IFF scheme is intended for servers operated by national laboratories. The servers share a private group key and provide the public client parameters on request. The clients cannot masquerade as servers.

The GQ scheme is intended for exceptionally hostile scenarios where it is necessary to change the client key at relatively frequent intervals. As in the IFF scheme the servers share a private group key and provide the public client parameters on request. In this scheme clients requre a public key to complete the exchange. This is conveyed in the server certificate in an extension field. The certificate can be changed while retaining the same group key.

The MV scheme is intended for the most challenging scenarios where it is necessary to protect against both server and client masquerade. The private values used by the TA to generate the cryptosystem are not available to the servers and the private values used by the servers to encrypt data are not available to the clients. Thus, a client cannot masquerade as a server and a server cannot masquerade as a TA. However, a client can verify a server has the correct group key even though neither the client nor server know the group key, nor can either manufacture a client key acceptable to any other client. A further feature of this scheme is that the TA can collaborate with the servers to revoke client keys.

* * *

#### Private Certificate (PC) Cryptosystem

![gif](/archives/pic/pc.gif)

The PC scheme shown above uses a private certificate as the group key. A certificate is designated private by a X509 Version 3 extension field when generated by the `ntp-keygen` program in the NTP software distribution. In the Autokey context it functions as a symmetric key. The private certificate is generated by a TA and distributed to all group members by secure means and is never revealed outside the group. A client is marked trusted in the (optional) Parameter Exchange and authentic when the first signature is verified. This scheme is cryptographically strong as long as the private certificate is protected; however, it can be very awkward to refresh the keys or certificate, since new values must be securely distributed to a possibly large population and activated simultaneously.

* * *

#### Schnorr (IFF) Cryptosystem

The Schnorr (IFF) identity scheme can be used when certificates are generated by utilities other than the `ntp-keygen` program in the NTP software distribution. Certificates can be generated by the OpenSSL library or an external public certificate authority, but conveying an arbitrary public value in a certificate extension field might not be possible. The TA generates the IFF parameters, private key and public key, then sends these values to the servers and the parameters and public key to the clients. Without the private key a client cannot masquerade as a legitimate server.

The DSA parameters are generated by routines in the OpenSSL library. The IFF values hide in a DSA cuckoo structure which uses the same parameters. The values are used by an identity scheme based on DSA cryptography and described in <sup>[4](#myfootnote4)</sup> and <sup>[5](#myfootnote5)</sup> p. 285. The <code>_p_</code> is a 512-bit prime, <code>_g_</code> a generator of the multiplicative group <code>_Z<sub>p</sub>_\*</code> and <code>_q_</code> a 160-bit prime that divides <code>_p_ - 1</code> and is a <code>_q_</code>th root of <code>1 mod _p_</code>; that is, <code>_g<sup>q</sup>_ = 1 mod _p_</code>. The TA rolls a private random group key <code>_b_ (0 < _b_ < _q_)</code> and computes the public key <code>_v_ = _g<sup>b</sup>_</code>, then distributes private <code>(_p_, _q_, _g_, _b_)</code> to the servers using secure means and public <code>(_p_, _q_, _g, v_)</code> to the clients not necessarily using secure means.

![gif](/archives/pic/iff.gif)

The TA generates a DSA parameter structure for use as IFF parameters. The IFF parameters are identical to the DSA parameters, so the OpenSSL library DSA parameter generation routine can be used directly. The DSA parameter structure is written to a file as an encrypted DSA key encoded in PEM. Unused structure members are set to one.

| IFF | DSA | Item | Include |
| ----- | ----- | ----- | ----- |
| <code>_p_</code> | `p` | modulus | all |
| <code>_q_</code> | `q` | modulus | all |
| <code>_g_</code> | `g` | generator | all |
| <code>_b_</code> | `priv_key` | group key | server |
| <code>_v_</code> | `pub_key` | client key | client |

Alice challenges Bob to confirm identity using the following protocol exchange.

1.  Alice rolls random <code>_r_ (0 < _r_ < _q_)</code> and sends to Bob.
2.  Bob rolls random <code>_k_ (0 < _k_ < _q_)</code>, computes <code>_y_ = _k_ + _b r_ mod _q_</code> and <code>_x_ = _g__<sup>k</sup>_ mod _p_</code>, then sends <code>(_y_, hash(_x_))</code> to Alice.
3.  Alice computes <code>_z_ = _g<sup>y</sup>_ _v<sup>r</sup>_ mod _p_</code> and verifies <code>hash(_z_)</code> equals <code>hash(_x_)</code>.

* * *

#### Guillou-Quisquater (GQ) Cryptosystem

The Guillou-Quisquater (GQ) identity scheme is useful when certificates are generated by the `ntp-keygen` program in the NTP software distribution. The TA generates the GQ parameters, private key and public key, then sends these values to the servers and the parameters to the clients. The public key is inserted in an X.509 extension field when the certificate is generated. Without the private key a client cannot masquerade as a legitimate server.

The RSA parameters are generated by routines in the OpenSSL libbrary. The GQ values hide in a RSA cuckoo structure which uses the same parameters. The values are used in an identity scheme based on RSA cryptography and described in <sup>[1](#myfootnote1)</sup> and <sup>[5](#myfootnote5)</sup> p. 300 (with errors). The 512-bit public modulus <code>_n_ = _p_ _q_</code>, where <code>_p_</code> and <code>_q_</code> are secret large primes. The TA rolls random group key <code>_b_ (0 < _b_ < _n_)</code> and sends <code>(_n_, _b_)</code> to the servers using secure means. The private key and public key are constructed later.

![gif](/archives/pic/gq.gif)

The TA generates a RSA parameter structure for use as GQ parameters. The RSA parameter structure is written to a file as an encrypted RSA key encoded in PEM. Unused structure members are set to one.

When generating new certificates, the server rolls new random private key <code>_u_ (0 < _u_ < _n_)</code> and public key its inverse <code>_u_<sup>-1</sup></code> obscured by the group key <code>_v_ = _u_<sup>-1</sup> _<sup>b</sup>_</code>. These values replace the private and public keys normally generated by the RSA scheme. In addition, the public key <code>_v_</code> is conveyed in a X.509 certificate extension.

| GQ | RSA | Item | Include |
| ----- | ----- | ----- | ----- |
| <code>_n_</code> | `n` | modulus | all |
| <code>_b_<code> | `e` | group key | all |
| <code>_u_</code> | `p` | server key | server |
| <code>_v_</code> | `q` | client key | client |

Alice challenges Bob to confirm identity using the following exchange.

1.  Alice rolls random <code>_r_ (0 < _r_ < _n_)</code> and sends to Bob.
2.  Bob rolls random <code>_k_ (1 < _k_ < _n_)</code> and computes <code>_y_ = _k_ _u<sup>r</sup>_ mod _n_</code> and <code>_x_ = _k<sup>b</sup>_ mod _n_</code>, then sends <code>(_y_, hash(_x_))</code> to Alice.
3.  Alice computes <code>_z_ = _v<sup>r</sup> y<sup>b</sup>_ mod _n_</code> and verifies <code>hash(_z_)</code> equals <code>hash(_x_)</code>.

* * *

#### Mu-Varadharajan (MV) Cryptosystem

The Mu-Varadharajan (MV) scheme was originally intended to encrypt broadcast transmissiions to receivers which do not transmit. There is one encryption key for the broadcaster and a separate decryption key for each receiver. It operates something like a pay-per-view satellite broadcasting system where the session key is encrypted by the broadcaster and the decryption keys are held in a tamperproof set-top box. We don't use it this way, but read on.

In the MV scheme the TA constructs an intricate cryptosystem involving a number of activation keys known only to the TA. The TA decides which keys to activate and provides to the servers an encryption key <code>_E_</code> and server decryption keys <code>_gbar_</code> and <code>_ghat_</code> which depend on the activated keys. The servers have no additional information and, in particular, cannot masquerade as a TA. In addition, the TA provides for each activation key <code>_j_</code> individual client decryption keys <code>_xbar_</code> and <code>_xhat_</code>, which do not need to be changed if the TA enables or disables an activation key. The clients have no further information and, in particular, cannot masquerade as a server or TA.

Clients are assigned one of the activation keys and are provided with the corresponding client key. There can be any number of clients sharing the same activation key according to policy. While the machinery to enable and disable ativation keys is included in the current implementation, specific means and interfaces to do this are not yet available, so only one client key is provided.

The scheme is designed so that clients can construct the inverse of <code>_E_</code> from the server <code>_gbar_</code> and <code>_ghat_</code> and client <code>_xbar_</code> and <code>_xhat_</code>. In the scheme both <code>_E_</code> and its inverse are exponentiated by a server nonce, so the product is always one and the secrecy depends on the descrete log problem.

The MV values hide in a DSA cuckoo structure which uses the same parameters, but generated in a different way. The values are used in an encryption scheme similar to El Gamal cryptography and use a polynomial formed from the expansion of product terms <code>(_x_ - _x<sub>j</sub>_)</code>, as described in <sup>[3](#myfootnote3)</sup>. The paper has significant errors and serious omissions.

![gif](/archives/pic/mv.gif)

The TA generates the modulus, encryption key and server decryption keys as an encrypted DSA key encoded in PEM. Unused structure members are set to one.

| MV | DSA | Item | Include |
| ----- | ----- | ----- | ----- |
| <code>_p_</code> | `p` | modulus | all |
| <code>_q_</code> | `q` | modulus | server |
| <code>_E_</code> | `g` | private encrypt key | server |
| <code>_gbar_</code> | `priv_key` | server decrypt key | server |
| <code>_ghat_</code> | `pub_key` | server decrypt key | server |

The TA generates the modulus and client decryption keys as a nonencrypted DSA key encoded in PEM. It is used only by designated recipient(s) who pay a suitably outrageous fee for its use. Unused structure members are set to one.

| MV | DSA | Item | Include |
| ----- | ----- | ----- | ----- |
| <code>_p_</code> | `p` | modulus | all |
| <code>_xbar_</code> | `priv_key` | client decrypt key | client |
| <code>_xhat_</code> | `pub_key` | client decrypt key | client |

The devil is in the details. Let <code>_q_</code> be the product of <code>_n_</code> distinct primes <code>_s1_<sub>_j</sub>_ (_j_ = 1..._n_)</code>, where each <code>_s1_<sub>_j</sub>_</code>, also called an activation key, has <code>_m_</code> significant bits. Let prime <code>_p_ = 2*q* + 1</code>, so that <code>_q_</code> and each <code>_s1_<sub>_j</sub>_</code> divide <code>_p_ - 1</code> and <code>_p_</code> has <code>_M_ = _nm_ + 1</code> significant bits. Let <code>_g_</code> be a generator of the multiplicative group <code>_Z<sub>p</sub>_*</code>; that is, <code>gcd(_g_, _p_ - 1) = 1</code> and <code>_g<sup>q</sup>_ = 1 mod _p_</code>. We do modular arithmetic over <code>_Z<sub>q</sub>_</code> and then project into <code>_Z<sub>p</sub>_*</code> as powers of <code>_g_</code>. Sometimes we have to compute an inverse <code>_b_<sup>-1</sup></code> of random <code>_b_</code> in <code>_Z<sub>q</sub>_</code>, but for that purpose we require <code>gcd(_b_, _q_) = 1</code>. We expect <code>_M_</code> to be in the 500-bit range and <code>_n_</code> relatively small, like 30. The TA uses a nasty probabilistic algorithm to generate the cryptosystem. In the following let the number of bits in the modulus <code>_m_ = 512</code>.

1.  The object is to generate a multiplicative group <code>_Z<sub>p</sub>_*</code> modulo, a prime <code>_p_</code> and a subset <code>_Z<sub>q</sub>_ mod _q_</code>, where <code>_q_</code> is the product of <code>_n_</code> distinct <code>_m_</code>-bit primes <code>_s1_<sub>_j</sub>_ (_j_ = 1..._n_)</code> and <code>_q_</code> divides <code>_p_ - 1</code>. As a practical matter, it is tough to find more than 31 distinct primes for <code>_mn_ = 512</code> or 61 primes for <code>_mn_ = 1024</code>. The latter can take several hundred iterations and several minutes on a Sun Blade 1000.
2.  Compute the modulus <code>_q_</code> as the product of the primes. Compute the modulus <code>_p_</code> as <code>2*q* + 1</code> and test <code>_p_</code> for primality. If <code>_p_</code> is composite, replace one of the primes with a new distinct prime and try again. Note that <code>_q_</code> will hardly be a secret since we have to reveal <code>_p_</code> to servers and clients. However, factoring <code>_q_</code> to find the primes should be adequately hard, as this is the same problem considered hard in RSA. Question: is it as hard to find <code>_n_</code> small prime factors totalling <code>_n_</code> bits as it is to find two large prime factors totalling <code>_n_</code> bits? Remember, the bad guy doesn't know <code>_n_</code>.
3.  Associate with each <code>_s1_<sub>_j</sub>_</code> an element <code>_s<sub>j</sub>_</code> such that <code>_s<sub>j</sub>_ _s1_<sub>_j</sub>_ = _s1_<sub>_j</sub>_ mod _q_</code>. One way to find an <code>_s<sub>j</sub>_</code> is to compute the quotient <code>(_q_ + _s1_<sub>_j</sub>_) / _s1_<sub>_j_</sub> mod _p_</code>. The student should prove the remainder is always zero.
4.  Compute the generator <code>_g_</code> of <code>_Z<sub>p</sub>_</code> using a random roll such that <code>gcd(_g_, _p_ - 1) = 1</code> and <code>_g<sup>q</sup>_ = 1</code>. If not, roll again.

The cryptosystem parameters <code>_n_, _p_, _q_, _g_, _s1_<sub>_j</sub>_, _s_<sub>_j</sub>_ (_j_ = 1..._n_)</code> have been determined. The TA sets up a specific instance of the scheme as follows.

1.  Roll random roots <code>_x<sub>j</sub>_ mod _q_ (_j_ = 1..._n_)</code> for a polynomial of order <code>_n_</code>. While it may not be strictly necessary, Make sure each root has no factors in common with <code>_q_</code>.
2.  Generate polynomial coefficients <code>_a<sub>i</sub>_ (_i_ = 0..._n_)</code> from the expansion of root products <code>(_x_ - _x<sub>i</sub>_) mod _q_</code> in powers of <code>_x_</code> using a fast method contributed by Charlie Boncelet.
3.  Generate <code>_g<sub>i</sub>_ = _g<sup>ai</sup>_ mod _p_</code> for all <code>_i_</code> and the generator <code>_g_</code>. Verify <code>prod(_g<sub>i</sub><sup>ai</sup> <sup>xji</sup>_) = 1</code> for all <code>_i_, _j_</code>. Note the <code>_a<sub>i</sub> x<sub>j</sub><sup>i</sup>_</code> exponent is computed <code>mod _q_</code>, but the <code>_g<sub>i</sub>_</code> is computed <code>mod _p_</code>. Also note the expression given in the paper cited is incorrect.
4.  Make master encryption key <code>_A_ = Prod(_g<sub>i</sub><sup>xj</sup>_) (_i_ = 0..._n_, _j_ = 1..._n_ - 1)</code>. Keep it around for awhile, since it is expensive to compute.
5.  Roll private random group key <code>_b_ mod _q_ (0 < _b_ < _q_)</code>, where <code>gcd(_b_, _q_) = 1</code> to guarantee the inverse exists, then compute <code>_b_<sup>-1</sup> mod _q_</code>. If <code>_b_</code> is changed, all keys must be recomputed.
6.  Make private client keys <code>_xbar<sub>j</sub>_ = _b_<sup>-1</sup> Sum(_x<sub>i</sub><sup>n</sup>_ mod _q)_ (_i_ = 1...n, _i_ != _j_)</code> and <code>_xhat<sub>j</sub>_ = _s<sub>j</sub>x<sub>j</sub><sup>n</sup>_</code> for all <code>_j_</code>. Note that the keys for the <code>_j_</code>th client involve only <code>_s<sub>j</sub>_</code> and that <code>_s1_<sub>_j</sub>_</code> remain secret. The TA sends <code>(_p_, _xbar<sub>j</sub>_, _xhat<sub>j</sub>_)</code> to the <code>_j_</code>th client(s) using nonsecure means.
7.  The activation key is initially <code>_q_</code> by construction. The TA revokes client <code>_j_</code> by dividing <code>_q_</code> by <code>_s1_<sub>_j</sub>_</code>. The quotient becomes the activation key <code>_s_</code>. Note we always have to revoke one key; otherwise, the plaintext and cryptotext would be identical. The TA computes private server encryption key <code>_E_ = _A<sup>s</sup>_</code> and server decryption keys <code>_gbar_ = _gbar<sup>s</sup>_</code> and <code>_ghat_ = _ghat<sup>sb</sup>_ mod _p_</code> and sends <code>(_p_, _E_, _gbar_, _ghat_)</code> to the servers using secure means. These values must be recomputed if an activation key is changed.

Alice challenges Bob to confirm identity using the following exchange.

1.  Alice rolls random <code>_r_ (0 < _r_ < _q_)</code> and sends to Bob.
2.  Bob rolls random <code>_k_ (0 < _k_ < _q_)</code>, computes <code>_y_ = _rE<sup>k</sup>_, _ybar_ = _gbar<sup>k</sup>_</code> and <code>_yhat_ = _ghat<sup>k</sup>_</code>, then returns <code>(_y_, _ybar_, _yhat_)</code> to Alice.
3.  Alice computes the session decryption key <code>(_E<sup>k</sup>_)<sup>-1</sup> = _ybar<sup>xhatj</sup>_ _yhat<sup>xbarj</sup>_</code>, then verifies that <code>_y_ = _r_</code>.

* * *

#### Selected Publications

<a name="myfootnote1">1</a>  Guillou, L.C., and J.-J. Quisquatar. A "paradoxical" identity-based signature scheme resulting from zero-knowledge. _Proc. CRYPTO 88 Advanced in Cryptology_, Springer-Verlag, 1990, 216-231.

<a name="myfootnote2">2</a>  Mills, D.L. The Autokey security architecture, protocol and algorithms. Electrical and Computer Engineering Technical Report 06-1-1, University of Delaware, January 2006, 59 pp, [PDF](/reflib/reports/stime1/stime.pdf).

<a name="myfootnote3">3</a>  Mu, Y., and V. Varadharajan. Robust and secure broadcasting. _Proc. INDOCRYPT 2001, LNCS 2247_, Springer Verlag, 2001, 223-231.

<a name="myfootnote4">4</a>  Schnorr, C.P. Efficient signature generation for smart cards. _J. Cryptology 4, 3_ (1991), 161-174.

<a name="myfootnote5">5</a>  Stinson, D.R. _Cryptography - Theory and Practice_. CRC Press, Boca Raton, FA, 1995, ISBN 0-8493-8521-0.