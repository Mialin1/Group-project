flag = -pedantic-errors -std=c++11

Objects = interface.cpp IO.cpp main.cpp map.cpp player.cpp update.cpp

game: $(Objects)
	g++ $(flag)