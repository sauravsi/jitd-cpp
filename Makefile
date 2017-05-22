# CC = g++ -w
# INC = include/
# SRC = src/
# BIN = bin/

# WOR = WithoutRead/
# WR = WithRead/

# WORFILES := $(wildcard $(SRC)*.cpp) $(wildcard $(SRC)$(WOR)*.cpp)
# WRFILES := $(wildcard $(SRC)*.cpp) $(wildcard $(SRC)$(WR)*.cpp)

# WOROBJECTS := $(addprefix $(BIN)$(WOR),$(addsuffix .o, $(basename $(notdir $(WORFILES)))))
# WROBJECTS := $(addprefix $(BIN)$(WR),$(addsuffix .o, $(basename $(notdir $(WRFILES)))))

# TARGET1 = jitd_nr

# TARGET2 = jitd_r

# INCLUDES = -I $(INC) -I $(SRC)

# WRINCLUDES = -I $(INC)$(WR)

# WORINCLUDES = -I $(INC)$(WOR)

# all: $(BIN) $(TARGET1) $(TARGET2)

# print:
# 	@echo $(WORFILES)
# 	@echo $(WOROBJECTS)
# 	@echo $(WRFILES)
# 	@echo $(WROBJECTS)
# 	@echo $(WRINCLUDES)
# 	@echo $(WORINCLUDES)

# noread: noread = 
# noread: $(BIN) $(TARGET1)

# read: read =
# read: $(BIN) $(TARGET2)

# #create binary folder
# $(BIN):
# 	@mkdir $@

# #create executable
# $(TARGET1): $(WOROBJECTS) 
# 	$(CC) $^ -o $@

# $(TARGET2): $(WROBJECTS)
# 	$(CC) $^ -o $@

# #create objects
# $(BIN)%main.o: $(SRC)%main.cpp
# 	$(CC) -c $(INCLUDES) $^ -o $@

# $(BIN)$(WR)%.o: $(SRC)%.cpp $(SRC)$(WR)%.cpp $(INC)%.h
# 	$(CC) -c $(WRINCLUDES) $(INCLUDES) $< -o $@

# $(BIN)$(WOR)%.o: $(SRC)%.cpp $(SRC)$(WOR)%.cpp $(INC)%.h
# 	$(CC) -c $(WORINCLUDES) $(INCLUDES) $< -o $@

# #raise warning for missing header
# $(INC)%.h:
# 	@echo "Warning no header for "$*.cpp

# #delete binaries and executable


# clean:
# 	@rm -rf $(BIN) $(TARGET)

all: read noread

read:
	g++ -w -I include/ -I src/ -I include/WithRead/ -I src/WithRead/ src/*.cpp src/WithRead/*.cpp -o jitd_r

noread:
	g++ -w -I include/ -I src/ -I include/WithoutRead/ -I src/WithoutRead/ src/*.cpp src/WithoutRead/*.cpp -o jitd_nr

clean:
	@rm -rf jitd_r jitd_nr
