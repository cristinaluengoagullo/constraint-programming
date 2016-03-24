DIR=/usr/local
LIBS= \
   -lgecodeflatzinc  -lgecodedriver \
   -lgecodegist      -lgecodesearch \
   -lgecodeminimodel -lgecodeset    \
   -lgecodefloat     -lgecodeint    \
   -lgecodekernel    -lgecodesupport

queens1: queens1.cpp
	g++ -I$(DIR)/include -c queens1.cpp
	g++ -L$(DIR)/lib -o queens1 queens1.o $(LIBS)

queens2: queens2.cpp
	g++ -I$(DIR)/include -c queens2.cpp
	g++ -L$(DIR)/lib -o queens2 queens2.o $(LIBS)

clean:
	rm queens1 queens2 *.o *~
