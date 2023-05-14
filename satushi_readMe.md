#実装の流れ

## 1	情報の整理

objlist lightlist を包括するのが　scenes
objlistには
１　数字
２　union型（これによって4つの形を使い分ける
３　colorの情報
が格納されている。

lightlist内の各lightには
１　point（電気の場所
２　輝度
３　色
が格納されている。

〜〜〜〜〜〜〜〜〜〜〜〜〜

## 2	描画処理

### 壱　　　入力情報の格納


### 弐　　　視点ベクトルを決める
後ほど対応を完了させるため、一旦無視

### 參　　　　　描画のための色情報の獲得

#### calc_diffuse_reflection
① 完全鏡面反射なら無視
（　②　画像を貼った時の処理）

〜〜　光源の個数分だけ繰り返し処理　〜〜
③　nとlの計算（内積）
④　光源と物体の間に他の物体がないか確認、もしあれば色の計算をしない
⑤　diffusereflectionによる色の計算
⑥　reflectionによる色の計算
⑦　checkerreflectionによる色の計算
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

#### calc_specular_reflection
① 完全鏡面反射なら無視
（　②　画像を貼った時の処理）

〜〜　光源の個数分だけ繰り返し処理　〜〜
③　nとlの計算（内積）
④　光源と物体の間に他の物体がないか確認、もしあれば色の計算をしない
⑤　diffusereflectionによる色の計算
⑥　reflectionによる色の計算
⑦　checkerreflectionによる色の計算
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜