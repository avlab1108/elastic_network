IFLAGS=-I../../network

TARGET_NAME=relaxer.a
TARGET_CMD=$(AR)

SOURCES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

include ../../../defaults.mk
