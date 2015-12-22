CC = c++
IDIR = ../include
BDIR = ../bin
ODIR = ../obj
CFLAGS = -I$(IDIR) -std=c++11 -O2 -I/usr/local/include -L/usr/local/lib -larmadillo

$(ODIR)/main.o: main.cpp $(IDIR)/graph.h $(IDIR)/io.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/graph.o: graph.cpp $(IDIR)/graph.h
	$(CC) -c -o $@ $< $(CFLAGS)
