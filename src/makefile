CC = c++
IDIR = ../include
BDIR = ../bin
ODIR = ../obj
CFLAGS = -I$(IDIR) -std=c++11 -O2 -I/usr/local/include -L/usr/local/lib -larmadillo

.PHONY: main
main: $(ODIR)/main.o

$(ODIR)/main.o: main.cpp $(IDIR)/graph.h $(IDIR)/io.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: graph
graph: $(ODIR)/graph.o

$(ODIR)/graph.o: graph.cpp $(IDIR)/graph.h
	$(CC) -c -o $@ $< $(CFLAGS)
