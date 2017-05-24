CC := g++ -w -std=c++11 
ROOT := ../../
INC := $(ROOT)include/
SRC := $(ROOT)src/
BIN := $(ROOT)bin/
WR := WithRead/
THIS := $(SRC)$(WR)
THIS_H := $(INC)$(WR)


FILES := $(wildcard $(SRC)*.cpp) $(wildcard $(THIS)*.cpp)
OBJECTS := $(FILES:$(SRC)%.cpp=$(BIN)%.o)

TARGET := $(ROOT)jitd_read

INCLUDES := -I $(INC) -I $(SRC) -I $(THIS) -I $(THIS_H)

all: $(BIN) $(BIN)$(WR) $(TARGET)

$(BIN):
	@mkdir $@

$(BIN)$(WR):
	@mkdir $@

print:
	@echo $(FILES)
	@echo $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

$(BIN)%.o: $(SRC)%.cpp $(INC)%.h
	$(CC) -c $(INCLUDES) $< -o $@

$(BIN)$(WR)main.o: $(SRC)$(WR)main.cpp
	$(CC) -c $(INCLUDES) $^ -o $@

$(BIN)$(WR)%.o: $(SRC)$(WR)%.cpp $(INC)$(WR)%.h
	$(CC) -c $(INCLUDES) $< -o $@

%.h:

clean:
	rm -rf $(BIN) $(TARGET)