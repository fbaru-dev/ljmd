CXX = icpc
OPTFLAGS = -std=c++11 -O0
#-xCORE-AVX2
DEBUGFLAGS = -g -DWITHCUTOFF
OMPFLAGS = -qopenmp
INCLUDES = 

CXXFLAGS = $(OPTFLAGS) $(DEBUGFLAGS)
MICFLAGS = $(OPTFLAGS) $(DEBUGFLAGS) -mmic

SOURCES = LJSimulation.cpp LJPotential.cpp main.cpp

.SUFFIXES: .o .cpp .omic

##########################################
OBJSC = $(SOURCES:.cpp=.o)
OBJSM = $(SOURCES:.cpp=.omic)
##########################################

EXEC=lennard-cpu.x
EXEM=lennard-mic.x

all: instructions

%.o: %.cpp
	$(info )
	$(info Compiling the object file for CPU: )
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 
	
%.omic: %.cpp
	$(info )
	$(info Compiling the object file for MIC: )
	$(CXX) $(MICFLAGS) $(INCLUDES) -c $< -o $@ 

cpu: $(OBJSC)
	$(info )
	$(info Linking the CPU executable:)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXEC) $(OBJSC)
	
mic: $(OBJSM)
	$(info )
	$(info Linking the CPU executable:)
	$(CXX)  $(MICFLAGS) $(INCLUDES) -o $(EXEM) $(OBJSM)

instructions: 
	$(info )
	$(info To Compile the Application: )
	$(info "make cpu" to compile the application on the host CPU)
	$(info "make mic" to compile the application on the target MIC)
	$(info )

run-cpu: 
	$(info )
	$(info Run the default test case on CPU: )
	./lennard-cpu.x > result-cpu.out &
	
run-mic: 
	$(info )
	$(info Run the default test case on MIC: )
	scp lennard-mic.x $(HOST)-mic0:~/
	ssh $(HOST)-mic0 OMP_NUM_THREADS=1 ./lennard-mic.x > result-mic.out &

clean: 
	rm -f $(OBJSC) $(OBJSM) lennard-cpu.x lennard-mic.x

fclean:
	rm -f *.xyz

