CC = g++ -w
INC = include/
SRC = src/
BIN = bin/

FILES := $(wildcard $(SRC)*.cpp)
OBJECTS := $(addprefix $(BIN),$(addsuffix .o, $(basename $(notdir $(FILES)))))

TARGET = jitd

INCLUDES = -I $(INC) -I $(SRC)

all: $(BIN) $(TARGET)

#create binary folder
$(BIN):
	@mkdir $@

#create executable
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

#create objects
$(BIN)main.o: $(SRC)main.cpp
	$(CC) -c $(INCLUDES) $^ -o $@

$(BIN)%.o: $(SRC)%.cpp $(INC)%.h
	$(CC) -c $(INCLUDES) $< -o $@

#raise warning for missing header
$(INC)%.h:
	@echo "Warning no header for "$*.cpp

#delete binaries and executable
clean:
	@rm -rf $(BIN) $(TARGET)