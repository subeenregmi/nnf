NAME:=nnf.out
COMPILER:=g++
CURRENTMODEL:=xor

INCLUDEDIR:=./include/
SRCDIR:=./src/
MODELDIR:=./models/
TESTDIR:=./tests/
BUILDDIR:=./build/
OUTDIR:=./build/out/

SRCFILES:=$(wildcard $(SRCDIR)*.cpp)
SRCOBJECTS:=$(patsubst %.cpp, %.o, $(SRCFILES))
DEPFILES:= $(patsubst %.cpp, %.d, $(SRCFILES))
MODELFILES:= $(wildcard $(MODELDIR)$(CURRENTMODEL).cpp)
MODELOBJECTS:=$(patsubst %.cpp, %.o, $(MODELFILES))
MODELNAME:= $(patsubst %.cpp, %.out, $(MODELFILES))
TESTFILES:= $(wildcard $(TESTDIR)*.cpp)
TESTOBJECTS:=$(patsubst %.cpp, %.o, $(SRCFILES))

OPT:=-O0
DEPFLAGS:=-MP -MD 
COMPILERFLAGS:= -Wall -Wextra $(OPT) $(DEPFLAGS)-I$(INCLUDEDIR)

all:
	echo "Nothing..."

model: $(CURRENTMODEL)

$(CURRENTMODEL): $(MODELOBJECTS) $(SRCOBJECTS)
	$(COMPILER) -o $(BUILDDIR)out/$@ $(MODELOBJECTS) $(SRCOBJECTS)

%.o : %.cpp
	$(COMPILER) $(COMPILERFLAGS) -c -o $@ $<

run:
	$(OUTDIR)$(CURRENTMODEL)

clean:
	rm -rf $(SRCOBJECTS) $(DEPFILES) $(TESTOBJECTS) $(MODELOBJECTS) 
