CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-address \
    -I/home/ritik/OdbDesign/OdbDesignLib/FileModel/Design/ \
    -I/home/ritik/OdbDesign/Utils \
    -I/home/ritik/OdbDesign/out/build/linux-debug/vcpkg_installed/x64-linux/include/ \
    -I/home/ritik/OdbDesign/OdbDesignLib \
    -I/home/ritik/ODB_Project/include

LDFLAGS = -L/home/ritik/OdbDesign/out/build/linux-debug/OdbDesignLib \
          -L/home/ritik/OdbDesign/out/build/linux-debug/Utils \
          -Wl,-rpath,/home/ritik/OdbDesign/out/build/linux-debug/Utils \
          -lOdbDesign -lUtils

# List of source files
SRC = src/main.cpp src/extractComponentData.cpp \

# Convert .cpp files to .o files (Ensure correct paths)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

TARGET = out

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $(TARGET) ..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@touch $(TARGET) # Update timestamp to avoid unnecessary relinks

# Ensure each .cpp file compiles to the correct .o path
%.o: %.cpp
	@mkdir -p $(dir $@)  # Ensure directories exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

