# CAN
CAN通信はController Area Networkの略で、もとは自動車内の通信用です。差動伝送のペアの信号線にノードを接続する多対多の通信規格です。送信時はデータの種類を示してデータを垂れ流して受信時は欲しいデータを受け取るだけで、全てをコントロールするマスターはありません。通信相手を指定するのではなく通信内容を指定するのがCANの特徴です。差動伝送であるため電気的なノイズに強く、CRCによる誤り検出も備えていて信頼性の高い規格です。

ハイブリッドロケットの電装においても、機能ごとに基板を分割しCANで通信することで以下のようなメリットがあります。~~ただし、かなり費用がかさみます。~~
- 信頼性が上がる
    - ソフトウェアが単純になる
    - 冗長性を確保しやすい
    - 故障が波及しづらい
    - 基板間の通信をSPI・I2Cよりも信頼性の高いCANのみにできる
- 開発が楽になる
    - 開発を細かく分担できる (COREはインカレであるためより重要)
    - 流れるデータをデバッグしやすい
    - 互換性のある過去のプロジェクトの基板を用いてデバッグができる
	- 使う部品が変わっても通信規格を軸にして技術継承が可能である

# CCP (CORE CAN Protocol)
標準フォーマットのCANでは、11bitのIDをつけて最大8byteのデータをやりとりできます。どのIDにどんなデータをどんな形式で流すかを定義したものがCORE CAN Protocolです。IDの割り当ては`CANID.xlsx`で管理しています。CCPではIDが1byteに収まるように0x00～0xFFを使用します．
<table>
	<tr>
		<td>CANID</td>
		<td colspan="4">データフレーム(MSB<- ->LSB)</td>
		<td>用途</td>
	</tr>
	<tr>
		<td>0x00~</td>
		<td>秒(uint16_t)</td>
		<td colspan="3">文字列(6文字)</td>
		<td></td>
	</tr>
	<tr>
		<td>0x40~</td>
		<td colspan="2">ミリ秒(unsigned long)</td>
		<td colspan="2">uint32_t</td>
		<td>有効数字が7桁では足りないもの。GPSなどで使用。</td>
	</tr>
	<tr>
		<td>0x80~</td>
		<td colspan="2">ミリ秒(unsigned long)</td>
		<td colspan="2">float</td>
		<td>基本はこれ。有効数字は10進数で7桁程度。</td>
	</tr>
	<tr>
		<td>0xC0~</td>
		<td>秒(uint16_t)</td>
		<td>fp16</td>
		<td>fp16</td>
		<td>fp16</td>
		<td>高速で記録する必要があるもの。FP16は10進数で有効数字3桁程度。</td>
	</tr>
</table>

## CCP.hの実装
### CCP.hとCCP_device.hの違い
CCPクラスとは別に実際に使うデバイスのクラスを用意し、これらを多重継承してCCP_deviceクラスを作成して使用します。

CCP_device.hにはデバイスの初期化に必要な`begin()`、11bitのIDの8byteのデータを送信する`write_device()`と受信する`read_device()`を実装します。これがプレゼンテーション層より下位の層にあたります。

CCPはプレゼンテーション層に相当し、8byteのビット列ではなく様々な種類のデータの送受信を可能にしています。これにより、上位のアプリケーション層はプロジェクトごとに簡単に開発できます。

### 共用体を使ったデータ管理
8byteのビット列を様々なフォーマットで扱うため、`msg_union`という共用体を用いてデータを管理しています。それぞれのフォーマットは構造体として定義しています。

### 送信
データを送信するときは、メンバ変数に直接アクセスするのではなく`型名_to_device(id,data)`のようなセッターを用います。これにより内部で`write_device()`が呼び出されてビット列として送信されます。文字列や半精度浮動小数点数など、共用体内の変数に代入する以外の処理も必要な場合があるためセッターを用意しました。
### 受信
データを受信するときも、メンバ変数に直接アクセスするのではなく`型名()`というようなゲッターを用います。`read_device()`をプログラムから呼び出して共用体`msg_union`のデータを更新したあと、`型名()`で値を読み出します。共用体から変数を取り出すと記述が煩雑になるためゲッターを用意しました。ただし、データの種類を示すIDについてはメンバ変数に直接アクセスする仕様です。

### 浮動小数点の処理
単精度浮動小数点数(float)に加えて、半精度浮動小数点数(fp16)としてデータを送受信する機能を実装しています。プログラムからはfloatとして扱えるように、ビット演算でfloatとfp16を相互に変換する関数を実装して内部で使用しています。

## CCPの使用例
### インクルード
```cpp
#include <CCP_MCP2515.h>
```
### 初期化
```cpp
#define CAN0_INT    2
#define CAN0_CS     3
CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);
void setup()
{
	CCP.begin();
}
```
### 送信
```cpp
CCP.fp16_to_device(CCP_A_accel_mss, 0.1, -0.1, 9.8);
```
### 受信
```cpp
CCP.read_device();
switch (CCP.id) {
	case CCP_opener_control:
		if (CCP.str_match("CHECK", 5)) goCHECK();
		if (CCP.str_match("READY", 5)) goREADY();
		break;
	case CCP_open_time_command_s:
		open_threshold_time_ms = CCP.data_float() * 1000;
		delay(200);
		CCP.float_to_device(CCP_open_time_response_s, (float)open_threshold_time_ms / 1000.0);
		break;
	default:
		break;
}
```

## 依存関係
### MCP2515
* [MCP_CAN_lib](https://github.com/coryjfowler/MCP_CAN_lib)
### W25Q512
* [W25Q512](https://github.com/771-8bit/W25Q512)
* [Arduino-Queue.h](https://github.com/sdesalas/Arduino-Queue.h)
