# Makefile

CXXFLAGS = -g

CC = g++

#EN ESTA VARIABLE VAN TODAS LAS DEPENDENCIAS QUE TENGAN UN MAIN Y SE QUIERAN COMPILAR
TARGET = consumerAviones dispatcherAviones

TARGETFLAGS = -g 

archivos = $(filter-out $(addsuffix .cpp, $(TARGET)), $(wildcard *.cpp))

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = ../common ../logger

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = ../common/*.o ../logger/Logger.o $(archivos:.cpp=.o)

robjs = $(wildcard *.o $(TARGET))

#######################################
#verbose = si

#occ := $(CC)
#ocxx := $(CXX)
#orm := $(RM)
#old := $(LD)
#ifdef verbose
#RM := $(RM) -v
#else
#CC =  @echo "  Compilando  $@"; $(occ)
#CXX = @echo "  CXX $@"; $(ocxx)
#RM =  @echo "  CLEAN"; $(orm)
#LD =  @echo "  LD  $@"; $(old)
#endif

#COMP_DEPEND = @echo "Compilar dependencias externas..."
#LIMPIAR = @echo "Limpiando..."

#########################################


all: consumerAviones dispatcherAviones

binaries: $(bin)

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<
	
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

consumerAviones: consumerAviones.cpp binaries
	$(CC) $(I-INCLUDES) $(bin) $(TARGETFLAGS) consumerAviones.cpp -o consumerAviones


dispatcherAviones: dispatcherAviones.cpp binaries
	$(CC) $(I-INCLUDES) $(bin) $(TARGETFLAGS) dispatcherAviones.cpp -o dispatcherAviones

clean:
	$(LIMPIAR) rm -f $(robjs)

.PHONY: clean all binaries
