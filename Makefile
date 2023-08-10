NAME:=nnf.out
COMPILER:=g++
CURRENTMODEL:=lineregression
CURRENTTEST:=tests

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
	echo "model - to build the current model, test - to build the current tests" 

model: $(CURRENTMODEL)

$(CURRENTMODEL): $(MODELOBJECTS) $(SRCOBJECTS)
	$(COMPILER) -o $(BUILDDIR)out/$@ $(MODELOBJECTS) $(SRCOBJECTS)

%.o : %.cpp
	$(COMPILER) $(COMPILERFLAGS) -c -o $@ $<

$(CURRENTTEST) : $(SRCOBJECTS) $(TESTOBJECTS)
	$(COMPILER) -o $(TESTDIR)$@ $(SRCOBJECTS) $(TESTOBJECTS)

clean:
	rm -rf $(DEPFILES) $(SRCOBJECTS) $(MODELOBJECTS) $(TESTOBJECTS) models/*.o models/*.d

run: 
	$(OUTDIR)$(CURRENTMODEL)

runtests:
	@$(TESTDIR)$(CURRENTTEST)
