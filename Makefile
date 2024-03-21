BIN     		:= bin
SRC     		:= src
BUILD				:= build
INCLUDE 		:= include
LIB     		:= lib
LIBRARIES   :=

EXECUTABLE  := run
PARAMS    	:= -ts 5 -fd modulo -hash close -bs 3 -fe redispersion
PARAMSOPEN  := -ts 5 -fd suma -hash open

SOURCES := $(wildcard $(SRC)/*.cc)
OBJS	:= $(patsubst $(SRC)/%.cc,$(BUILD)/%.o,$(SOURCES))

.PHONY: all project run clean

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJS)
	@echo "🚧 Building..."
	$(CXX) -o $@ $(CXXFLAGS) -L $(LIB) $(OBJS)

$(BUILD)/%.o: $(SRC)/%.cc
	@echo "🚧 Building..."
	$(CXX) -c -o $@ $(CXXFLAGS) $<

project:
	clear
	@echo "📁 Creating Project Structure..."
	mkdir -p bin build include src

run:
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE) $(PARAMS)

open:
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE) $(PARAMSOPEN)

clean:
	@echo "🧹 Clearing..."
	rm -f $(BIN)/* $(BUILD)/*