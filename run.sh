g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/cartoons/img_0.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render snow.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/basic/bp_metal_shadow.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/basic/mapdepht_red_basic.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/basic/materials_show.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/basic/normal2rgb_basic.txt


# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_0.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_1.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_2.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_3.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_4.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_5.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_6.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_7.txt
# g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/blinn_phong_base/img_8.txt







# make &&
# ./render samples/scene0.txt &&
# ./render samples/scene1.txt && 
# ./render samples/scene2.txt &&
# ./render samples/scene3.txt &&
# ./render samples/scene4.txt &&
# ./render samples/scene5.txt &&
# make clean

# mkdir -p out
# mkdir -p out_convrt
# rm -f out/*
# rm -f out_convrt/*
# make && 

# # i=-1.0
# i=0
# limit=12
# while [ $i -lt $limit ]
# do
# 	./render $i $i > out/i$i.ppm
# 	convert out/i$i.ppm out_convrt/i$i.jpg
# 	i=$[ $i + 1 ]

# done

# ./render 0 > out/i0.ppm
# convert out/i0.ppm out_convrt/i0.jpg

# ./render 1 > out/i1.ppm
# convert out/i1.ppm out_convrt/i1.jpg

# ./render 2 > out/i2.ppm
# convert out/i2.ppm out_convrt/i2.jpg

# ./render 3 > out/i3.ppm
# convert out/i3.ppm out_convrt/i3.jpg

# ./render 4 > out/i4.ppm
# convert out/i4.ppm out_convrt/i4.jpg

# ./render 5 > out/i5.ppm
# convert out/i5.ppm out_convrt/i5.jpg

# ./render 6 > out/i6.ppm
# convert out/i6.ppm out_convrt/i6.jpg

# ./render 7 > out/i7.ppm
# convert out/i7.ppm out_convrt/i7.jpg

# ./render 8 > out/i8.ppm
# convert out/i8.ppm out_convrt/i8.jpg

# ./render 9 > out/i9.ppm
# convert out/i9.ppm out_convrt/i9.jpg

# ./render 10 > out/i10.ppm
# convert out/i10.ppm out_convrt/i10.jpg

# ./render 11 > out/i11.ppm
# convert out/i11.ppm out_convrt/i11.jpg
# ./render 12 > out/i12.ppm
# convert out/i12.ppm out_convrt/i12.jpg
# ./render 13 > out/i13.ppm
# convert out/i13.ppm out_convrt/i13.jpg
# ./render 14 > out/i14.ppm
# convert out/i14.ppm out_convrt/i14.jpg
# ./render 15 > out/i15.ppm
# convert out/i15.ppm out_convrt/i15.jpg

# rm out/*


# convert -resize 20% -delay 14 -loop 0 out_convrt/i{0..11}.jpg image.gif