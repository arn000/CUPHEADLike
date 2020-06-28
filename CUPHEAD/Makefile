CXXFLAGS = -O2 -Wextra -Wall -Ideps\include -std=c++0x
LXXFLAGS = -O2 -Ldeps\lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

output: main.o player.o game_manager.o window.o wall.o npc.o timer.o bullet.o hpbar.o hpbarenemy.o mana.o ultimate.o coin.o text.o
	g++ main.o player.o game_manager.o window.o wall.o npc.o timer.o bullet.o hpbar.o hpbarenemy.o mana.o ultimate.o coin.o text.o $(LXXFLAGS) 
	
main.o: main.cpp 
	g++ -c main.cpp $(CXXFLAGS) 
	
window.o: window.cpp window.h
	g++  -c window.cpp $(CXXFLAGS)

game_manager.o: game_manager.cpp game_manager.h vector2d.h exception.h
	g++  -c game_manager.cpp $(CXXFLAGS)
	
player.o: player.cpp gameobj.h
	g++ -c player.cpp  $(CXXFLAGS) 
	
wall.o: wall.cpp wall.h
	g++ -c wall.cpp  $(CXXFLAGS) 
	
npc.o: npc.cpp npc.h
	g++ -c npc.cpp  $(CXXFLAGS) 

timer.o: timer.cpp timer.h
	g++ -c timer.cpp $(CXXFLAGS) 
	
bullet.o: bullet.cpp bullet.h
	g++ -c bullet.cpp $(CXXFLAGS) 
	
hpbar.o: hpbar.cpp 
	g++ -c hpbar.cpp  $(CXXFLAGS) 
	
hpbarenemy.o: hpbarenemy.cpp hpbarenemy.h
	g++ -c hpbarenemy.cpp  $(CXXFLAGS) 
	
mana.o: mana.cpp mana.h
	g++ -c mana.cpp  $(CXXFLAGS) 	
	
ultimate.o: ultimate.cpp ultimate.h
	g++ -c ultimate.cpp  $(CXXFLAGS) 
	
coin.o: coin.cpp coin.h
	g++ -c coin.cpp  $(CXXFLAGS)
	
text.o: text.cpp text.h
	g++ -c text.cpp  $(CXXFLAGS)
	
clean:
	rm *.o output