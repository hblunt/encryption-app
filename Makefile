CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJ = main.o UIHandler.o Encryptor.o Decryptor.o Grid.o
TARGET = encryption_app.exe

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $(OBJ)

main.o: main.cpp UIHandler.hpp
    $(CXX) $(CXXFLAGS) -c main.cpp

UIHandler.o: UIHandler.cpp UIHandler.hpp Encryptor.hpp Decryptor.hpp
    $(CXX) $(CXXFLAGS) -c UIHandler.cpp

Encryptor.o: Encryptor.cpp Encryptor.hpp Grid.hpp
    $(CXX) $(CXXFLAGS) -c Encryptor.cpp

Decryptor.o: Decryptor.cpp Decryptor.hpp Grid.hpp
    $(CXX) $(CXXFLAGS) -c Decryptor.cpp

Grid.o: Grid.cpp Grid.hpp
    $(CXX) $(CXXFLAGS) -c Grid.cpp

clean:
	rm -f $(OBJ) $(TARGET)
