CC = c++
IDIR = ../include
BDIR = ../bin
ODIR = ../obj
CFLAGS = -I$(IDIR) -std=c++11 -O2 -I/usr/local/include -L/usr/local/lib -larmadillo

.PHONY: all
all: $(ODIR)/main.o $(ODIR)/graph.o $(ODIR)/io.o
	$(CC) -o $(BDIR)/main $^ $(CFLAGS)

.PHONY: main
main: $(ODIR)/main.o

$(ODIR)/main.o: main.cpp $(IDIR)/graph.h $(IDIR)/io.h $(IDIR)/resources.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: graph
graph: $(ODIR)/graph.o

$(ODIR)/graph.o: graph.cpp $(IDIR)/graph.h $(IDIR)/resources.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: io
io: $(ODIR)/io.o

$(ODIR)/io.o: io.cpp $(IDIR)/io.h $(IDIR)/resources.h
	$(CC) -c -o $@ $< $(CFLAGS)
