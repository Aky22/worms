COMPILER = g++

SOURCES_DIR = src
BUILD_DIR = build

SOURCES = $(SOURCES_DIR)/worms.cpp
COMPILER_FLAGS = -std=c++11 -Wall
EXEC_NAME = $(BUILD_DIR)/worms.exe

CMD_RMDIR = cmd /C rmdir
CMD_MKDIR = cmd /C mkdir
CMD_COPY = cmd /C copy

all: post-build
	echo "Done"
	
clean:
	$(CMD_RMDIR) /S /Q $(BUILD_DIR)
	
pre-build: clean
	$(CMD_MKDIR) $(BUILD_DIR)
	
build: pre-build
	$(COMPILER) -o $(EXEC_NAME) $(SOURCES) $(COMPILER_FLAGS)
	
post-build: build
	$(CMD_COPY) /Y config.txt $(BUILD_DIR)