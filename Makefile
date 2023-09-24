CC=g++
CPPFLAGS=-O2 -I./ -std=c++11 -march=native -Wno-deprecated-declarations -Wno-unused-result
LDFLAGS=
LDLIBS=-lstdc++ -lsecp256k1 -lpthread -lssl -lcrypto

SOURCES= \
	base58.cpp \
	db.cpp \
	key.cpp \
	logger.cpp \
	main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=keybrute

all: clean $(SOURCES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o
