
all:
	g++ -shared -fPIC -o libplayer.so Player.cpp;
	g++ -shared -fPIC -o libplayer2.so Player2.cpp;
	g++ main.cpp

clean:
	rm -rf libplayer.so libplayer2.so a.out

.PHONY: all clean run
