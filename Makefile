CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
<<<<<<< HEAD
OBJECTS = ./obj/maze.o ./obj/main.o ./obj/node.o ./obj/mazeSolution.o
=======
OBJECTS = ./obj/maze.o ./obj/main.o
GTEST = /usr/local/lib/libgtest.a
>>>>>>> 648936280b775f7a91819e1aec49f654439e39a8
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/maze.o: ./cpp/maze.cpp ./h/maze.h
	$(CXX) $(CXXFLAGS) ./cpp/maze.cpp -o ./obj/maze.o
<<<<<<< HEAD
./obj/node.o: ./cpp/node.cpp ./h/node.h
	$(CXX) $(CXXFLAGS) ./cpp/node.cpp -o ./obj/node.o
./obj/mazeSolution.o: ./cpp/mazeSolution.cpp ./h/mazeSolution.h
	$(CXX) $(CXXFLAGS) ./cpp/mazeSolution.cpp -o ./obj/mazeSolution.o
=======
# ./obj/node.o: ./cpp/node.cpp ./h/node.h
# 	$(CXX) $(CXXFLAGS) ./cpp/node.cpp -o ./obj/node.o
>>>>>>> 648936280b775f7a91819e1aec49f654439e39a8
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
