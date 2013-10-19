# Makefile

CXXFLAGS = -g

CC = g++

#EN ESTA VARIABLE VAN TODAS LAS DEPENDENCIAS QUE TENGAN UN MAIN Y SE QUIERAN COMPILAR
TARGET = tp1

TARGETFLAGS = -g 

archivos = $(wildcard *.cpp)

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = common logger

SUBSYSTEMS = logger common torre controlador aviones

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o $(TARGET))

SUBSYS = $(addprefix SUBSYS, $(SUBSYSTEMS))

CLEANSUB = $(addprefix CLEANSUB, $(SUBSYSTEMS))

EXBINS = $(wildcard common/*.cpp logger/*.cpp)

SUBSYS-BINS = $(EXBINS:.cpp=.o)

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

%.o: %.cpp %.h
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<
	
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

SUBSYS%: % 
	$(MAKE) -C $<

CLEANSUB%: %
	$(MAKE) clean -C $<

$(TARGET): $(SUBSYS) binaries
	$(CC) $(I-INCLUDES) $(bin) $(SUBSYS-BINS) $(TARGETFLAGS) -o $(TARGET)

clean: $(CLEANSUB)
	$(LIMPIAR) rm -f $(robjs)

doc:
	cd doc/ &&  rm -f *.aux *log && pdflatex tp.tex

clean-doc:
	rm -f *.aux *.log *.toc tp.pdf

.PHONY: clean all binaries doc clean-doc
