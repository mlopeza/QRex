all:
	g++ *.cpp -o QRex -Wno-write-strings -std=gnu++0x

clean:
	rm -f QRex

