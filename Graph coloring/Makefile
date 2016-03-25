DIR=/usr/local
LIBS= \
   -lgecodeflatzinc  -lgecodedriver \
   -lgecodegist      -lgecodesearch \
   -lgecodeminimodel -lgecodeset    \
   -lgecodefloat     -lgecodeint    \
   -lgecodekernel    -lgecodesupport

coloring: graph_coloring.cpp
	g++ -I$(DIR)/include -c graph_coloring.cpp
	g++ -L$(DIR)/lib -o coloring graph_coloring.o $(LIBS)

clean:
	rm coloring *.o *~
