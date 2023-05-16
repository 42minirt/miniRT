A   0.2                                        255, 255, 255

C   -50.0, 0, 20    0, 0, 1     70

L   -40,50,00       0.6                         10, 0, 255

sp  0.0, 0.0, 20.6      12.6                    10, 0, 255

pl  0, 0, -10       0, 1, 0                     0, 0, 2255

cy  50, 0, 20.6     0, 0, 1     14.2    21.42   10, 0, 255


co  0, 0, 0         0, 0, 1     14.2    21.42   10, 0, 255

sl   -40,50,00       0.6        60.0            10, 0, 255


 #Ambient   lightning ratio[0,1]                                                            RGB[0,255]
 #Camera    viewpoint(xyz)       normalized orientation vec[-1,1]  FOV[0,180]
 #Light     point(xyz)           light brightness ratio[0,1]                                RGB[0,255]
 #Spotlight Light point(xyz)     light brightness ratio[0,1]       angle[0-90]              RGB[0,255]
 #Sphere    center point(xyz)    diameter    RGB[0,255]
 #Plane     point(xyz)           normalized vec[-1,1]                                       RGB[0,255]
 #Cylinder  center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]
 #Corn      center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]

 bonus options
    perfect_ref
    checker         RGB
    image           "image_texture_path",   "bumpmap_path"
                    ""                  ,   "bumpmap_path"

##################################################################
# Rule

light list : A, L, sl
shape list : sp, pl, cy, co
camera     : C

フォーマットを満たさなければNG
A, Cが2以上あればNG

各数値がout of rangeであればNG
normalized vecの入力は難しく、柔軟性を持たせるためにxyz[-1,1]を内部で正規化するようにしたい


,が合わなければNG
atoi, atof失敗はNG : ++1, 0..001など

数値間のスペースの数は不問、horizontal tabもOK

image_pathが""であればNULL
texture_path & bumpmap_pathいずれも""はNG