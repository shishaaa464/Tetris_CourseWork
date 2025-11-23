CXX = g++
CXXFLAGS = -Wall -std=c++17
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cpp Game.cpp Tetromino.cpp Field.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = tetris

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
