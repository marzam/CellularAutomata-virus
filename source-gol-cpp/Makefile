################################################################################
#
#
#  Universidade Federal Rural do Rio de Janeiro
#  por: Marcelo Zamith - zamith.marcelo@gmail.com
#
#
################################################################################
VERSION     = -D_VERSION=\"0.01\"
APPLICATION = -D_APPLICATION=\"$(EXEFILE)\"
CPUCC       = g++
CPPFLAGS    = -g
DEFS        = -DALIGN=64
INCLUDES    = -I. -I/usr/include/python3.7m/
LIBDIR      = -L/usr/lib
LIBS        =  -lm
LINK        =  $(LIBDIR) $(LIBS)
COMPILE     = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)

all:  python2cpp CellularAutomata
	$(COMPILE) -lboost_python3  -shared -fPIC -o  ../pylibca.so  obj/python2cpp.o obj/CellularAutomata.o

CellularAutomata:
	$(COMPILE) -fPIC -c CellularAutomata.cpp -o obj/CellularAutomata.o

python2cpp:
	$(COMPILE) -fPIC -c python2cpp.cpp -o obj/python2cpp.o

clean:
	rm obj/*.o; rm  ../pylibca.so
