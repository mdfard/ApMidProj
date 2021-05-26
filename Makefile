CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/maze.o ./obj/main.o ./obj/mazesolution.o ./obj/node.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/maze.o: ./cpp/maze.cpp ./h/maze.h
	$(CXX) $(CXXFLAGS) ./cpp/maze.cpp -o ./obj/maze.o
./obj/mazesolution.o: ./cpp/mazesolution.cpp ./h/mazesolution.h
	$(CXX) $(CXXFLAGS) ./cpp/mazesolution.cpp -o ./obj/mazesolution.o
./obj/node.o: ./cpp/node.cpp ./h/node.h
	$(CXX) $(CXXFLAGS) ./cpp/node.cpp -o ./obj/node.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
