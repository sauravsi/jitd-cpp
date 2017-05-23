CC := g++ -w
INC := include/
SRC := src/
BIN := bin/

TARGET1 := jitd_read
TARGET2 := jitd_noread

WOR := WithoutRead/
WR := WithRead/

all: read noread

read: $(TARGET1)

noread: $(TARGET2)

$(TARGET1): $(WOROBJECTS) 
	@cd $(SRC)$(WR) && $(MAKE)

$(TARGET2): $(WROBJECTS)
	@cd $(SRC)$(WOR) && $(MAKE)

clean:
	@cd $(SRC)$(WR) && $(MAKE) clean 
	@cd $(SRC)$(WOR) && $(MAKE) clean