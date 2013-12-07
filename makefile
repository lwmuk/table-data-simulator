SRC_C = timer.C \
		constant.C \
		integer.C \
		double.C \
		singleselector.C \
		allselector.C \
		other.C \
		tools.C \
		factory.C \
		datatype.C \
		config.C \
		datamanager.C \
		main.C 

OBJ = $(SRC_C:.C=.o)

EXE = simulator
CXXFLAGS = -g

target: $(OBJ)
	@echo -n "Building $(EXE) ... "
	@$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)
	@echo  OK

.C.o:
	@echo -n compiling $< " ... "
	@$(CXX) -o $@ -c $< $(CXXFLAGS)
	@echo  OK

clean:
	@rm -f $(OBJ) $(EXE)
	@echo  "clean finished."
