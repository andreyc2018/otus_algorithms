TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))
CXXFLAGS += -std=c++14 -ggdb

all: $(TARGETS)

%: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
