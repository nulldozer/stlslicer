BIN = main
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
CC = g++
LFLAGS = -Wall -W -std=c++11 -lGL -lGLU `wx-config --version=3.0 --libs base,core,gl`
CFLAGS = -Wall -W -std=c++11 -c `wx-config --version=3.0 --cxxflags` 

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $^ $(LFLAGS) 

%.o: %.cpp
	@$(CC) $(CFLAGS) -MD -MP -c -o $@ $<

clean:
	rm $(OBJS) *~ $(BIN)

-include $(SRCS:.cpp=.d)
