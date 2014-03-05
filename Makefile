.DEFAULT_GOAL = all
.PHONY: all clean

OBJ_DIR := objs
SRC_DIR := srcs
LIB_DIR := libs
MKPATH := mkdir -p $(OBJ_DIR)

CXX := g++
CXXFLAGS := -std=c++0x -O3 -Wall -D_WEBSOCKETPP_CPP11_STL_ #-g -gdwarf-2 
LDFLAGS := -lm  -Wl,-rpath="$(LIB_DIR)"
INCL := -I./incl -I./libs
LIBS := -L$(LIB_DIR) -lpthread -ljson -lboost_system

TARGET := ShootBurger
AUTOMATA := Uninitialized Connected InRoom Playing Trash
JSON := JsonSerializer HelloRequest HelloResponse Ready StartGame Shot Score Target Interval EndGame InitGame JsonProvider Disconect
SERVER := Server WebSocketConnector Dispatcher Worker Client
ROOMS := GameRoom PlayerData ABallProvider BallProvider Game Engine GameData ScoreData TargetData BallData EndGameData Ball Room
APP := main Lobby


SRCS :=  $(SERVER:=.cpp) $(JSON:=.cpp) $(AUTOMATA:=.cpp) $(ROOMS:=.cpp) $(APP:=.cpp)
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS)) 

all: $(TARGET)	

$(TARGET): $(OBJECTS)
	@echo "Building $(TARGET)"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Building $@"
	@$(MKPATH)
	@$(CXX) $(CXXFLAGS) $(CFLAGS) $(INCL) -c $< -o $@

clean:
	@echo "Cleaning"
	@rm -f $(TARGET)
	@rm -rf $(OBJ_DIR)
