BPATH    := build

TARGETS  := $(BPATH)/snicker
OBJECTS  := $(BPATH)/main.o \
			$(BPATH)/interfacehelper.o \
			$(BPATH)/packetsniffer.o \
			$(BPATH)/resources.o \
			$(BPATH)/clients.o \
			$(BPATH)/hotspots.o

CXXFLAGS := -g -std=c++11 -Wall -Wextra
LDFLAGS  := -ltins -lpthread -lgcov

all: $(TARGETS)

$(BPATH)/snicker: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BPATH)/%.o: source/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Checks and tests
check: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon

read: $(TARGETS)
		sudo $(BPATH)/snicker -o test.pcap

memtest: $(PROGRAM)
	-rm -f valgrind.log
	-sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v --log-file=valgrind.log ./$(TARGETS) -i wlan1mon
	-cat valgrind.log

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f $(BPATH)/*.o
