CPPCOMPILER=g++
CPPFLAGS=-std=c++11 -pedantic -Wall
OUTPUT_BINARY=ipk-scan
LIBRARIES=utils/arg_parser.cpp utils/error_handler.cpp utils/addres.cpp

all: build

build: main.cpp $(LIBRARIES)
	$(CPPCOMPILER) $(CPPFLAGS) $(LIBRARIES) main.cpp -o $(OUTPUT_BINARY) -lpcap

debug: main.cpp $(LIBRARIES)
	$(CPPCOMPILER) $(CPPFLAGS) -g $(LIBRARIES) main.cpp -o $(OUTPUT_BINARY) -lpcap

run:
	./$(OUTPUT_BINARY)

clean:
	rm $(OUTPUT_BINARY)