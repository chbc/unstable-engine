# folders
SRC = RenderEngine
OBJ_DIR = ../obj
LIBRARY_PATHS = ../lib/gcc
BIN_DIR = ../bin/gcc

# engine
ENGINE_DLL = libSRE.dll
ENGINE_LIB = libSRE.a

# application
APP_SRC = SampleApplication
APP_NAME = SampleApplication.exe
APP_INCLUDE_PATHS = -I"./SampleApplication" -I"./RenderEngine" -I"../include"
APP_LINKER_FLAGS = -lSRE
APP_LIBRARY_PATHS = ../lib/gcc

# compilation parameters
CC = g++
INCLUDE_PATHS = -I"./RenderEngine" -I"../include"
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lglew32 -lOpenGL32 -lassimp
DEFINES = -DSRE_DLL_EXPORT
COMPILER_FLAGS = -O3 -Wall # -std=c++17

# code fetch
search_dirs = $(wildcard $1$2) $(foreach d, $(wildcard $1*), $(call search_dirs, $d/, $2))
ALL_SRC := $(call search_dirs, $(SRC)/, *.cpp)
ALL_SRC := $(filter %.cpp, $(ALL_SRC))
ALL_OBJ := $(patsubst $(SRC)/%.cpp, $(OBJ_DIR)/$(SRC)/%.obj, $(ALL_SRC))

all: intermediate app

intermediate: \
	$(ALL_OBJ)
	$(CC) -shared $(ALL_OBJ) -L $(LIBRARY_PATHS) $(LINKER_FLAGS) -Wl,--out-implib,$(LIBRARY_PATHS)/$(ENGINE_LIB) -o $(BIN_DIR)/$(ENGINE_DLL)
	
app:
	$(CC) $(APP_SRC)/main.cpp $(APP_SRC)/application/SampleApplication.cpp $(APP_SRC)/application/events/EventReceiver.cpp $(APP_INCLUDE_PATHS) -L $(APP_LIBRARY_PATHS) $(APP_LINKER_FLAGS) $(COMPILER_FLAGS) -o $(BIN_DIR)/$(APP_NAME)
#	$(CC) $(APP_INCLUDE_PATHS) -L $(APP_LIBRARY_PATHS) $(APP_LINKER_FLAGS) $(COMPILER_FLAGS) $(APP_SRC)/main.cpp $(APP_SRC)/application/SampleApplication.cpp -o $(BIN_DIR)/$(APP_NAME)

$(OBJ_DIR)/$(SRC)/%.obj: $(SRC)/%.cpp
#	@echo "alvo: " $@
#	@echo "diretorio: " $(dir $@)
	mkdir -p $(dir $@)
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c $(DEFINES) $< -o $@
	
run: 
	$(BIN_DIR)/$(APP_NAME)
	
clean:
	rm -rf $(OBJ_DIR) 
	rm $(LIBRARY_PATHS)/$(ENGINE_LIB)
	rm $(BIN_DIR)/$(APP_NAME)

.PHONY: clean
