---
title: "PPS Clock Discipline"
type: archives
---

Author: David L. Mills (mills@udel.edu)
: Last change: 31-Mar-2014 07:46 UTC

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver22/#synopsis)
*   [Description](/documentation/drivers/driver22/#description)
*   [Fudge Factors](/documentation/drivers/driver22/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver22/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.22._u_</code>
: **Reference ID:** `PPS`
: **Driver ID:** `PPS`
: **Serial or Parallel Port:** <code>/dev/pps*u*</code>
: **Requires:** PPSAPI signal interface for PPS signal processing.

> **ノート：**　このドライバーは、同じ名前の古いドライバーを置き換えた後継です。 古いドライバーは、いくつかのやや古風なインターフェース・デバイスで動作していて複雑な構成が必要であり、また、文書化が不十分でした。
このドライバーを動作させるためには、１秒パルス信号API (PPSAPI)<sup>[1](#myfootnote1)</sup> が必要です。 `pps` 構成コマンドは、このドライバーによって廃止されていることにも注意してください。


#### Description

このドライバーは、セシウム時計、電波時計、または、関連デバイスによって生成される1秒ごとのパルス信号（PPS）のインターフェースを提供します。 使い方の例としては、GPS受信機によって生成されたシリアル・タイムコードを時刻精度を向上させるために使用できます。 混雑した広域ネットワークにあるプライマリ・サーバーに同期しているときに、セカンダリ・サーバーがローカル・クライアントに時間を再配布する前に、 ジッター（時刻情報のゆらぎ）の累積を排除して時間を再設定できます。 このドライバーは、広範な信号の健全性チェックと信号の整備アルゴリズムを持っています。
レンジ・ゲートと周波数弁別器は、雑音や１秒パルスでない誤った信号を排除します。 多段メディアン・フィルターは、ハードウェア割り込みとオペレーティング・システムの遅延によるジッターを排除します。  トリム平均アルゴリズムは、最適な時刻抽出を決定します。 一般的なワーク・ステーションと処理負荷では、偶発的なジッターを数マイクロ秒程度に減らすことができます。

このドライバーは、PPSソースに関連する時間と頻度を制御できますが、秒数を数えることはできません。 この目的のために、補助の時刻ソースが必要で、通常、電波時計を参照します。 あるいは、別のNTPサーバーを使用することもできます。
この目的のために、補助の時刻ソースを優先ピアとして指定する必要があります。 詳しくは、[Mitigation Rules and the `prefer` Keyword](/documentation/4.2.8-series/prefer) で説明されています。

ドライバーには、IETF標準に提案されているPPSAPIインターフェイス<sup>[1](#myfootnote1)</sup>が必要です。 インターフェースは、`timepps.h` ヘッダー・ファイルと関連するカーネル・サポートで構成されています。 
このインターフェースのサポートは、現在のバージョンのSolaris、FreeBSD、Linux、および、商用バージョンのTru64（Alpha）とSunOSに含まれています。 詳細については、[Pulse-per-second (PPS) Signal Interfacing](/documentation/4.2.8-series/pps) を参照して下さい。 

PPS信号は、ハードウェアとオペレーティング・システムに応じて、シリアルポートまたはパラレルポートに接続できます。 シリアルポートは、PPS信号専用、または、別のデバイスと共有のいずれもできます。
ただし、専用の場合は、ノイズや予期しない信号により ntpd が終了する可能性があるので、他の信号線を接続しないで下さい。

電波時計は、通常、シリアルポートに接続され、PPS信号はレベル・コンバータを介して同じコネクタのデータ・キャリア検出（DCD）ピン（DB-9のピン1、DB-25のピン8）に接続されます。 パラレルポートとドライバーが利用可能な一部のシステムでは、PPS信号は、コネクタのACKピン（DB25のピン10）に直接接続できます。 PS信号が専用ポートに接続されているか、別のデバイスと共有されているポートに接続されているかに関係なく、
ドライバーはデバイス `/dev/pps%d` を開きます。`%d` はユニット番号です。 他のドライバーと同様に、シンボリック・リンクを使用して論理名を実際の物理デバイスにリダイレクトできます。

このドライバーは、他のドライバーと同じように動作し、 ntpデーモンに組み込まれている緩和アルゴリズムとPLL/FLLクロック規制を使用します。 カーネルPLL/FLLサポートが利用可能な場合は、代わりにカーネルPLL/FLLクロック規制を使用できます。
デフォルトの動作では、カーネルPPSクロック規制が利用できる場合でも使用されません。 このドライバーは、ドライバーのメディアン・フィルター・アルゴリズムを使用してジッターを低減するための信号処理を組み込んでいます。
その結果、設定ファイルで `minpoll` に 4（16秒）を設定したパフォーマンスは、一般にカーネルPPSよりも優れています。 ただし、必要に応じて、設定ファイルの `fudge flag3` を使用してカーネルPPS規制を有効にすることができます。

このドライバーは、次の二つの条件のいずれかに当てはまる場合のみ有効になります。<br>
（a）緩和アルゴリズムの結果、このドライバー以外の優先ピアが残っているか、<br>
（b）緩和アルゴリズムの結果、残っているピアがなく、`tos` コマンドの `minsane` オプションが 0<br>
優先ピアは、使用可能な場合に秒数を確実に数えることができる別の時刻ソースを指定します。 ただし、使用可能な時刻ソースがない場合、システム・クロックはPPSドライバーによって無期限に規制され続けます。

後者の振る舞いが最も役立つシナリオは、惑星の衛星群で、 例えば、火星の近くでは、火星の衛星群と地球との接近は、火星日ごとに1回か2回だけです。 これらの衛星群は、セシウム発振器の精度で超安定な発振器に基づく正確なタイミング基準を持っています。 PPS信号は超安定な発振器から得られ、まれに地球から、または、NTPを介して別の衛星群から規制することができます。 
上記のシナリオでは、PPS信号はNTPによる更新の間に宇宙船の時計を規制します。

同様のシナリオでは、PPS信号を使用して、モデムによる通信で時刻の更新する間のクロックを規制できます。 これにより、インターネットを全く必要とせずに正確な時刻同期が提供されます。

* * *

#### Fudge Factors

<code>**time1 _time_**</code>
: PPS信号の調整時間、単位：秒（小数点以下も可）、デフォルト 0.0秒

<code>**time2 _time_**</code>
: 未使用

<code>**stratum _number_**</code>
: 階層番号、0 から 15 の整数、デフォルト 0

<code>**refid _string_**</code>
: ドライバーのREFID、ASCIIの1文字から４文字、デフォルト `PPS`.

<code>**flag1 0 | 1**</code>
: 未使用

<code>**flag2 0 | 1**</code>
: 0（デフォルト）： PPS信号の立ち上がりが正秒　／　1： PPS信号の立ち下がりが正秒 Windows では未使用。`serialpps.sys` シリアルポート・ドライバーがインストールされている場合は、常にPPS信号の立ち上がりが正秒

<code>**flag3 0 | 1**</code>
: 0（デフォルト）： <tt>ntpd</tt> clock discipline　／　1： kernel discipline Windows では未使用。`serialpps.sys` シリアルポート・ドライバーがインストールされている場合で、kernel discipline が利用可能ならば kernel discipline

<code>**flag4 0 | 1**</code>
: 0（デフォルト）： １秒ごとのタイムスタンプは記録しない　／　1： １秒ごとのタイムスタンプは記録する  アラン偏差プロットの作成に役立ちます。

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.8-series/refclock)

<a name="myfootnote1">1</a>  Mogul, J., D. Mills, J. Brittenson, J. Stone and U. Windl. Pulse-per-second API for Unix-like operating systems, version 1. Request for Comments [RFC 2783](/reflib/rfc/rfc2783.txt), Internet Engineering Task Force, March 2000, 31 pp.