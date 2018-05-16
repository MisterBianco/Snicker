BPATH    := build

TARGETS  := $(BPATH)/snicker
OBJECTS  := $(BPATH)/main.o $(BPATH)/interfacehelper.o $(BPATH)/packetsniffer.o $(BPATH)/resources.o

CXXFLAGS := -g -std=c++17 -Wall -Wextra
LDFLAGS  := -ltins -lpthread

all: $(TARGETS)

# Checks and tests
check: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon

check1: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon -f 2

check2: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon -f 2 -c 5

bcheck: $(TARGETS)
	sudo $(BPATH)/snicker wlan1mon

bcheck1: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon -1

bcheck2: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon 5

bcheck3: $(TARGETS)
	sudo $(BPATH)/snicker -i wlan1mon -f 5 5

$(BPATH)/snicker: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BPATH)/%.o: source/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

memtest: $(PROGRAM)
	rm -f valgrind.log
	-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v --log-file=valgrind.log ./$(TARGETS)
	cat valgrind.log

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f $(BPATH)/*.o
