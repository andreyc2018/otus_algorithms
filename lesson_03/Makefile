TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))
CXXFLAGS += -std=c++17 -ggdb -I ../include

all: $(TARGETS)

%: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
