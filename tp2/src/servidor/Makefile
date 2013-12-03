# Makefile

CXXFLAGS = -g

CC = g++

#EN ESTA VARIABLE VAN TODAS LAS DEPENDENCIAS QUE TENGAN UN MAIN Y SE QUIERAN COMPILAR
TARGET = mainReceptor procServidor

TARGETFLAGS = -g 

archivos = $(filter-out $(addsuffix .cpp, $(TARGET)), $(wildcard *.cpp))

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = ../common ../logger

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = ../common/*.o ../logger/Logger.o $(archivos:.cpp=.o)

robjs = $(wildcard *.o $(TARGET))

TARGET-FILES = $(addsuffix .cpp, $(TARGET))
TARGET-BIN = $(TARGET-FILES:.cpp=.o)

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


all: $(TARGET)

binaries: $(bin)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

mainReceptor: mainReceptor.o binaries
	$(CC) $(I-INCLUDES) $(bin) $(TARGETFLAGS) mainReceptor.o -o appReceptor
	
procServidor: procServidor.o binaries
	$(CC) $(I-INCLUDES) $(bin) $(TARGETFLAGS) procServidor.o -o appServidor

clean:
	$(LIMPIAR) rm -f $(robjs)

.PHONY: clean all binaries
