all:
	g++ *.cpp -o QRex -Wno-write-strings

clean:
	rm -f QRex

