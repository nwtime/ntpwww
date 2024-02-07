---
title: "Undisciplined Local Clock"
type: archives
---

Author: David L. Mills (mills@udel.edu)
: Last update: 9-May-2014 08:34 UTC

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver1/#synopsis)
*   [Description](/documentation/drivers/driver1/#description)
*   [Monitor Data](/documentation/drivers/driver1/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver1/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver1/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.1._u_</code>
: **Reference ID:** `LOCL`
: **Driver ID:** `LOCAL`

* * *

#### Description

> **ノート： このドライバーの使用はお勧めしません。** もっと柔軟な代替方法については、[Orphan Mode](/documentation/4.2.8-series/orphan) をご参照下さい。

このドライバーは、電波時計やモデムなどの外部同期ソースが利用できない隔離されたネットワークでの使用を目的としていました。
このドライバーを指定されたタイム・サーバーがプライマリ・サーバーとして機能し、ネットワーク上の他のクライアントに同期時刻を提供できます。
優れたクロック発振器を備えたマシンを選び、このドライバーで構成します。利用可能な最良の時計を見て、そのマシンの時刻を設定します。
次に、他のすべてのマシンの参照先をこのマシンに向けるか、ブロードキャスト・モードを使用して時間を配信します。


このドライバーの別の用途は、特定のタイム・サーバーで他の全ての通常の同期ソースがなくなったときに最後の手段のクロックとして使用する場合です。 
これは、そのサーバーに周波数安定度が高い恒温槽発信器がある場合に特に役立ちます。
このため、必須ではありませんが通常は他の利用可能な時間ソースよりも大きい階層番号でこのドライバーを構成します。
このドライバーのデフォルトの5は、ネットワーク内の他の適切な同期ソースが利用可能な場合に、このドライバーが同期ソースを引き取ってしまうのを防ぎます。 
偶発的または悪意による時刻公開から、インターネットのインフラストラクチャを保護するために、別の同期ソースが利用可能で動作している場合、このドライバーは無効になります。

* * *

#### Monitor Data

このドライバーは、`clockstats` を出力しません。

* * *

#### Fudge Factors

<code>**time1 _time_**</code>
: 調整時間、単位：秒（小数点以下も可）、デフォルト 0.0秒

<code>**time2 _time_**</code>
: 周波数調整係数、単位：PPM（百万分の１）、デフォルト 0.0

<code>**stratum _number_**</code>
: 階層番号、0 から 15 の整数、デフォルト 5

<code>**refid _string_**</code>
: ドライバーのREFID、ASCIIの1文字から４文字、デフォルト `LOCL`.

<code>**flag1 0 | 1**</code>
: 未使用

<code>**flag2 0 | 1**</code>
: 未使用

<code>**flag3 0 | 1**</code>
: 未使用

<code>**flag4 0 | 1**</code>
: 未使用

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.8-series/refclock)