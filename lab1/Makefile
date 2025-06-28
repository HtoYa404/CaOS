CXX = g++

SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = lab1

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

