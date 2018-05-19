BPATH    := ../../build

TARGETS  := $(BPATH)/test
OBJECTS  := $(BPATH)/interfacehelper_tests.o $(BPATH)/interfacehelper.o $(BPATH)/packetsniffer.o $(BPATH)/resources.o

CXXFLAGS := -g -std=c++11 -Wall -Wextra
LDFLAGS  := -ltins -lpthread -lgtest

all: $(TARGETS)

$(BPATH)/test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BPATH)/interfacehelper_tests.o: interfacehelper_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BPATH)/%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

check: $(TARGETS)
	$(TARGETS)

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f $(BPATH)/snicker
	-rm -f $(BPATH)/*.o
