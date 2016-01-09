CC = c++
IDIR = ../../include
CFLAGS = -I$(IDIR) -std=c++11 -O2 -I/usr/local/include -L/usr/local/lib -larmadillo

.PHONY: test
test: test.o graph.o
	$(CC) -o $@ $^ $(CFLAGS)

test.o: test.cpp $(IDIR)/graph.h $(IDIR)/io.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: graph
graph: graph.o

graph.o: ../graph.cpp $(IDIR)/graph.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PNOHY: clean
clean:
	rm test.o graph.o
