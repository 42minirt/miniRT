# 1. Overview
Simple RayTracer with miniLibX

<img src="https://github.com/42minirt/miniRT/assets/51146172/a06f991b-a21f-4f53-bdbd-38833b0580fb" width="800"><br>
(rt_file/test_obj/multi_009.rt)

<br>
<hr>  

# 2. How to use
## 2-1) Clone and compile
```shell
git clone https://github.com/42minirt/miniRT.git
cd miniRT
make
```
<br>

## 2-2) Execute
Some sample setting files in `rt_file/`
```shell
./miniRT <scene_setting_file.rt>
```

<br>
<hr>  

# 3. How to set scene
* The drawing scene is described in a scene setting file; rt file
* Load rt file as a program argument

## 3-1) format
* filename : rt file
* extension : `.rt`
* format
  - `id` and `parameters` on as single line.
  - general
    ```
     < id >         < paramters >
     A:  Ambient    lightning_ratio[0,1]                                                                            RGB[0,255]
     C:  Camera     viewpoint(xyz)         orientation_vec(xyz)[-1,1]   FOV[0,180]
     L:  Light      point(xyz)                                          light_brightness_ratio[0,1]                 RGB[0,255]
     SL: Spotlight  Light_point(xyz)       orientation_vec(xyz)[-1,1]   light_brightness_ratio[0,1]   angle[0-90]   RGB[0,255]
    
     sp: Sphere     center_point(xyz)                                   diameter                                    RGB[0,255]   <options>
     pl: Plane      point(xyz)             orientation_vec(xyz)[-1,1]                                               RGB[0,255]   <options>
     cy: Cylinder   bottom_center(xyz)     orientation_vec(xyz)[-1,1]   diameter    height                          RGB[0,255]   <options>
     co: Corn       bottom_center(xyz)     orientation_vec(xyz)[-1,1]   diameter    height                          RGB[0,255]   <options>
    ```
  - option
    ``` 
    < option id >   < parameters >
    perfect_ref
    checker         RGB
    image           "image_texture_path" "bumpmap_path" 
    ```

  - example
    ```
    A   0.2                                          255, 255, 255
    
    C   -50, 0, 20      0, 0, 1     70
    
    L   -40,50,00                   0.6              10, 0, 255
    
    SL  -40,50,00       0, 0, 1     0.6     60.0     10, 0, 255
  
    sp  0,0,20                     12.6              10, 0, 255
    
    pl  0, 0, -10       0, 1, 0                      0, 0, 225
    
    cy  50, 0, 20       0, 0, 1     14.2    21.42    10, 0, 255  perfect_ref
    
    co  0, 0, 0         0, 0, 1     14.2    21.42    10, 0, 255  checker      0, 0, 0
    
    ```

<br>

## 3-2) coordinate
This program uses a Left-hand coordinate system
```
  +y
  |  +z
  | /
  |/_____ +x
 O
```
<br>

## 3-3) Description Rule
* Each parameter of an id must be written in the order that complies with the format
* Lines starting with `#` are considered comment lines
* If a rt file with an invalid format is loaded, the program will terminate

### i) string, id
* id (`A`, `C`, `L`, `SL`, `sp`, `pl`, `cy`), option specifier (`perfect_ref`, `checker`, `image`) are determined by an exact match
* The number of `A`, `C` must each be 1

### ii) numeric value
* normalized_vec allows `xyz[-1,1]`, but make sure norm(xyz) >= 1
* If each number is out of range, the program will terminate

### iii) delimiter
* Any number of spaces, horizontal tabs can be used between parameters
* If , is not used as an appropriate delimiter, the program will terminate
  - ex) `R,G,B,`, `R,,G,B,` etc...
* If an invalid number such as `++1`, `0..001` is written, the program will terminate

### iv) image
* Image files should be in `P3 PPM` format
* If `image_path` is `""`, it is determined that no image is used
  - For example, `image "texture_path" ""` when only texture_path is loaded, or not loading bumpmap
  - Specify a valid path for either texture or bumpmap
* If the specified `path` is not a valid ppm file, the program will terminate

<br>
<hr>  

# 4. Example

* checkered corn, sphere and plane (rt_file/test_obj/multi_003.rt)  
  <img src="https://github.com/42minirt/miniRT/assets/51146172/072365fd-9cc4-4c5f-9a91-b9a40eb8d181" width="800">  

* image texture and bump mapped sphere (rt_file/simple_test/bump_1.rt)  
  <img src="https://github.com/42minirt/miniRT/assets/51146172/164b71cf-5f16-4b77-a8a3-badbadef250a" width="800">  

* cornel box (rt_file/sample_perfect_ref_cornel_box.rt)  
  <img src="https://github.com/42minirt/miniRT/assets/51146172/f89f5e83-64ea-4ac8-a876-9321f06a66d5" width="800">  

* sphere in the spotlight (rt_file/sample_spot_light.rt)  
  <img src="https://github.com/42minirt/miniRT/assets/51146172/43b57fe1-95ce-4b07-83b7-6f1d2fdb3d61" width="800">  

<br>
<hr>  

# 5. Author
* [ak0327](https://github.com/ak0327)
* [molhot](https://github.com/molhot)

<br>
<hr>  

# 6. Confirmed Environments
* Ubuntu 22.04.2 LTS (ARM64)
* MacOS OS Ventura 13.0 (ARM64)

<br>
<hr>  

# 7. Release
* 2023/Jun/18th

<br>
<hr>  

# 8. References
* [The Textbook of RayTracing @TDU](https://knzw.tech/raytracing/?page_id=1145)
* [C言語でレイトレーシングプログラムを作った](https://jun-networks.hatenablog.com/entry/2021/04/02/043216)
* [床井研究室 バンプマッピング](https://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20050826)
* [Unity Documentation 法線マップ](https://docs.unity3d.com/ja/2021.3/Manual/StandardShaderMaterialParameterNormalMap.html)
* [Ray Tracing in One Weekend](https://raytracing.github.io/)
* Jamis Buck, The Ray Tracer Challenge, Pragmatic Bookshelf
* Fletcher Dunn, Ian Parberry, 実例で学ぶゲーム3D数学（松田 晃一, 訳）, オライリージャパン
* Eric Lengyel, ゲームプログラミングのための3Dグラフィックス数学（狩野 智英, 訳）, ボーンデジタル
* 村岡一信/千葉則茂, CによるCGレイトレーシング, サイエンス社

<br>