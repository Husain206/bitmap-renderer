CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -g

bmpsrc := bmp.cpp main.cpp -Wall -Wextra -Wpedantic 

main:
	$(CXX) $(CFLAGS) $(bmpsrc) -o bmp

run:
	# change `feh` to your img viewer
	./bmp && feh ./output.bmp

clean:
	rm -rf bmp
	@echo "cleaned"

help:
	@echo "Usage:"
	@echo "  make       - build bmp"
	@echo "  make run   - run ./bmp and display it using an img viewer[note: edit \`run\` to your of choice img veiwer]"
	@echo "  make clean - clean binaries"
