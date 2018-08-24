
SRC = ./RenderEngine/engine
OBJ = ../obj
BIN = ../bin/vc
LIB = ../lib/vc

FLAGS = -O3 -Wall

all: intermediate
	
intermediate: \
	$(OBJ)/utils/FileUtils.obj \
	$(OBJ)/utils/Log.obj
	ar -rcs $(LIB)/SRE_d.lib $(OBJ)/*.obj
	
	
$(OBJ)/%.obj: $(SRC)/%.cpp
	g++ -c $< $(FLAGS) -o $@
	

clean:
	rm $(OBJ)/*.obj
