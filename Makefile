NAME:=nnf.out
COMPILER:=g++
CURRENTMODEL:=xor
CURRENTTEST:=test

INCLUDEDIR:=./include/
SRCDIR:=./src/
MODELDIR:=./models/
TESTDIR:=./tests/
BUILDDIR:=./build/
OUTDIR:=./build/out/

SRCFILES:=$(wildcard $(SRCDIR)*.cpp)
SRCOBJECTS:=$(patsubst %.cpp, %.o, $(SRCFILES))
MODELFILES:= $(wildcard $(MODELDIR)$(CURRENTMODEL).cpp)
MODELOBJECTS:=$(patsubst %.cpp, %.o, $(MODELFILES))
MODELNAME:= $(patsubst %.cpp, %.out, $(MODELFILES))
TESTFILES:= $(wildcard $(TESTDIR)*.cpp)
TESTOBJECTS:=$(patsubst %.cpp, %.o, $(TESTFILES))

DEPFILES:= $(patsubst %.cpp, %.d, $(SRCFILES) $(MODELFILES) $(TESTFILES))

OPT:=-O0
DEPFLAGS:=-MP -MD 
COMPILERFLAGS:= -Wall -Wextra $(OPT) $(DEPFLAGS)-I$(INCLUDEDIR)

all:
	echo $(DEPFILES)

model: $(CURRENTMODEL)

$(CURRENTMODEL): $(MODELOBJECTS) $(SRCOBJECTS)
	$(COMPILER) -o $(BUILDDIR)out/$@ $(MODELOBJECTS) $(SRCOBJECTS)

%.o : %.cpp
	$(COMPILER) $(COMPILERFLAGS) -c -o $@ $<


tests: $(CURRENTTEST)

$(CURRENTTEST) : $(SRCOBJECTS) $(TESTOBJECTS)
	$(COMPILER) -o $(TESTDIR)$@ $(SRCOBJECTS) $(TESTOBJECTS)

clean:
	rm -rf $(DEPFILES) $(SRCOBJECTS) $(MODELOBJECTS) $(TESTOBJECTS)

run: 
	$(OUTDIR)$(CURRENTMODEL)

runtests:
	@$(TESTDIR)$(CURRENTTEST)
