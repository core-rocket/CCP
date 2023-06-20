## CAN_Simulatorの仕様

1行ごとに以下のように時間とシム値が書かれた2つのcsvを読み込み，`CCP_A_accel_mss`の3番目の値`data_fp16_2`と`CCP_A_pressure_altitude_m`として時間通りにCANに送信する．csvは加速度と気圧高度で独立している．

```
時間[ms],機軸方向の加速度[m/s^2]
```

```
時間[ms],気圧高度[m]
```

csvをPCで読み込んでマイコンにデータを送る方法は任せるが，一般人のPCで実行しやすくメンテしやすい方法で実装してほしい．

マイコンのコードは↓のようなイメージ
```
float accel_mss = 9.8;
float altitude_m = 12.3;
CCP.fp16_to_device(CCP_A_accel_mss, 0,0,accel_mss);
CCP.float_to_device(CCP_A_pressure_altitude_m, accel_mss);
```