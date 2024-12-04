##
# GraphicsApplicationProgrammming
#
# @file
# @version 0.1

# Compiler settings
BUILD_DIR = build
CMAKE_DBG_FLAGS = -DCMAKE_BUILD_TYPE=Debug
EXE = app

# Default target
.PHONY: all
all: build

.PHONY: builddbg
builddbg: configure_dbg build

.PHONY: configure_dbg
configure:
	@cmake -s .-B $(BUILD_DIR) $(CMAKE_DBG_FLAGS)

# Create the build directory and configure the project with CMake
.PHONY: configure
configure:
	@cmake -S . -B $(BUILD_DIR) $(CMAKE_FLAGS)

# Build the project using the previously configured build directory
.PHONY: build
build: configure
	@cmake --build $(BUILD_DIR)

# Clean up the build directory
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: dbg
dbg:
	gdb ./${BUILD_DIR}/app

.PHONY: run
run:
	./${BUILD_DIR}/app


# end
