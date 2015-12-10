COMPILE_TARGETS = $(TARGET_DEPS)

TARGET_SRC_C   = $(wildcard *.cpp)
TARGET_DEPS    = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TARGET_SRC_C))
TARGET_CLEAN   = $(TARGET_DEPS) $(OBJ_DIR)/*.d

include ../../../mkfiles/defaults.mk
