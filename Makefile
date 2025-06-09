CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

SOURCES = main.cpp
HEADERS = MyContainer.hpp AscendingOrder.hpp DescendingOrder.hpp SideCrossOrder.hpp ReverseOrder.hpp Order.hpp MiddleOutOrder.hpp
MAIN_TARGET = main
TEST_TARGET = test

.PHONY: all clean Main test valgrind

all: Main

Main: $(MAIN_TARGET)

$(MAIN_TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) $(SOURCES)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) test.cpp

valgrind: $(MAIN_TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(MAIN_TARGET)

clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) *.o *.gch *~