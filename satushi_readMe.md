# 実装の流れ
  
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
4   color
が格納されている。  
  
## 2	描画処理
  
### 一　　　入力情報の格納
  
### 二　　　視点ベクトルを決める
後ほど対応を完了させるため、一旦無視  
  
### 三　　　　　描画のための色情報の獲得
  
#### intersectionの情報を格納
この情報を使ってかくobjのcolorの計算を一元化したい<br>

#### calc_ambient_reflection

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
⑤　光源のタイプが点の場合、別処理を加える（並行光源の実装によるもの？  
⑥　nとlをかけた結果が0以下なら以降の処理はしない  
⑦　反射ベクトルを計算(inverse_eye_vecが何を意味するか確認したい)  
⑧　反射ベクトルとinv_eye_vecの計算を行う（v_r）  
⑨　v_rが0より小さいか確認、0以下なら以降の処理を飛ばす  
⑩　色の計算  
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜  
  
#### calc_perfect_reflection

① 完全鏡面反射以外なら無視  
（　②　画像を貼った時の処理） 
  
〜〜　光源の個数分だけ繰り返し処理　〜〜  
③　視線ベクトルの逆ベクトルを計算  
④　視線の逆ベクトルと法線ベクトルの掛け算を行う　結果が0以下なら処理を終了  
⑤　④で計算したものを用い、raytransの計算を行う  （limitはあとで決める）
⑥　色の計算  
〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜  
  
※ 　calc_inflection_refractionは屈折の計算のようなので一旦無視  
  
### 四　　　　　描画
put関数を用いて描画  
  
  
ピクセルの個数文だけ二〜四を繰り返す<br><br>
何やるか決めるんば<br><br>
constructor → mocha takira<br>
ratio_ball ratio_corn → takira<br>
ratio_plane ratio_cylinder → mocha<br>

もちゃ対応
calc_specular_reflection(scene, eye_ray, intp, shape);
perfect_reflect_color = calc_perfect_reflection(scene, eye_ray, out_col, recursion_level, intp, shape);

あきらさん対応
calc_diffuse_reflection(scene, intp, *eye_ray, shape);
