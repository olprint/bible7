#
all:
	mkdir ./bin
	cd fltk && make
	(g++ src/bible7.cpp src/process/process.cpp src/process/process_unix.cpp src/utils.cpp src/bibleselector/VIdObj.cpp src/bibleselector/bibleselector.cpp -Bstatic -Wall -Ifltk -Llib -Ifltk -Llib  -lpng -lfltk -lfltk_images -lfltk_jpeg -lz -lX11 -lXfixes -lXext -ldl -lXrender -lXft -lfontconfig -lpthread -lm -lc -Wl,--as-needed -o ./bin/Bible7) && echo Done 
clean:
	cd fltk && make clean
	if test -d ./fltk; then rm ./fltk -r; fi
	if test -d ./bin; then rm ./bin -r; fi
