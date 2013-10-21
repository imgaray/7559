# Makefile

CXXFLAGS = -g

CC = g++

#EN ESTA VARIABLE VAN TODAS LAS DEPENDENCIAS QUE TENGAN UN MAIN Y SE QUIERAN COMPILAR
TARGET = tests

TARGETFLAGS = -g 

archivos = $(wildcard *.cpp)

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = ../common ../logger

SUBSYSTEMS = ../common ../logger

SUBSYS-BIN = $(foreach dir,$(SUBSYSTEMS), $(wildcard $(dir)/*.cpp))

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o $(TARGET))

SUBSYS = $(addprefix SUBSYS, $(SUBSYSTEMS))

CLEANSUB = $(SUBSYSTEMS)

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


all: $(SUBSYSTEMS) $(TARGET)

binaries: $(bin)

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<
	
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

$(SUBSYSTEMS):
	$(MAKE) -C $(SUBSYSTEMS)

$(CLEANSUB):
	$(MAKE) clean -C $(CLEANSUB)

$(TARGET): $(SUBSYSTEMS) binaries
	$(CC) $(I-INCLUDES) $(bin) $(TARGETFLAGS) $(SUBSYS-BIN) -o $(TARGET)

clean: $(CLEANSUB)
	$(LIMPIAR) rm -f $(robjs)

.PHONY: clean all binaries
