all:
	g++ *.cpp -o QRex -Wno-write-strings -std=c++0x

clean:
	rm -f QRex

