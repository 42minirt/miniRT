# rt file format

```
A   0.2                                        255, 255, 255

C   -50.0, 0, 20    0, 0, 1     70

L   -40,50,00       0.6                         10, 0, 255

sp  0.0, 0.0, 20.6      12.6                    10, 0, 255

pl  0, 0, -10       0, 1, 0                     0, 0, 2255

cy  50, 0, 20.6     0, 0, 1     14.2    21.42   10, 0, 255


co  0, 0, 0         0, 0, 1     14.2    21.42   10, 0, 255

sl   -40,50,00       0.6        60.0            10, 0, 255
```

```
 #Ambient    lightning_ratio[0,1]                                                               RGB[0,255]
 #Camera     viewpoint(xyz)         normalized_orientation_vec[-1,1]   FOV[0,180]
 #Light      point(xyz)             light_brightness_ratio[0,1]                                 RGB[0,255]
 #Spotlight  Light_point(xyz)       light_brightness_ratio[0,1]        angle[0-90]              RGB[0,255]
 #Sphere     center_point(xyz)                                         diameter                 RGB[0,255]  <bonus_options>
 #Plane      point(xyz)             normalized_vec[-1,1]                                        RGB[0,255]  <bonus_options>
 #Cylinder   center(xyz)            normalized_vec[-1,1]               diameter    height       RGB[0,255]  <bonus_options>
 #Corn       center(xyz)            normalized_vec[-1,1]               diameter    height       RGB[0,255]  <bonus_options>

 bonus options
    perfect_ref
    checker         RGB
    image           "image_texture_path",   "bumpmap_path"
                    ""                  ,   "bumpmap_path"
```
<br>
<hr>

# figure
## coordinate
Left hand
```
+y
|  +z
| /
|/_____ +x
```
<hr>


# Description Rule
* 記載順はformatに準拠
* formatを満たさなければNG

## string, id
* id(`A`, `C`, `L`, `sp`, `pl`, `cy`, `sl`), bonus指定子(`perfect_ref`, `checker`, `image`) は完全一致を判定
* `A`は2以上あればNG    // todo
* `C`は1個でなければNG  // todo

## numeric value
* 各数値がout of rangeであればNG
* `normalized_vec`は`xyz[-1,1]`を許容し、内部で正規化している

## delimiter
* `,` が適切なデリミタとして使用されていなければNG `R,G,B,` `R,,G,B` など
* `atoi`, `atof`失敗はNG : `++1`,  `0..001`など
* パラメータ間は任意数の`space`, `horizontal tab`が使用可能

## bonus(image)
* `image_path`が`""`であれば画像の使用なしと判定
* `texture_path`のみ, `bumpmap`を読み込まないときは、 `image "texture_path", ""` とする
* `texture_path` & `bumpmap_path`いずれも`""`はNG   `image "",""`
* 指定された`path`が有効な`ppm file`でなければNG