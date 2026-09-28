CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
TARGET = decoder
TEST_TARGET = run_tests

all: $(TARGET)

$(TARGET): decoder.cpp instruction.hpp
	$(CXX) $(CXXFLAGS) decoder.cpp -o $(TARGET)

test: test_decoder.cpp instruction.hpp
	$(CXX) $(CXXFLAGS) test_decoder.cpp -lgtest -lgtest_main -pthread -o $(TEST_TARGET)

test_lit: $(TARGET)
	lit -v lit_tests/

clean:
	rm -f $(TARGET) $(TEST_TARGET)