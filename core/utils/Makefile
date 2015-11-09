COMPILE_TARGETS = $(TARGET_DEPS)
LIB_TARGETS 		= $(TARGET)

TARGET					= $(OBJ_DIR)/utils.a

TARGET_SRC_C		= $(wildcard *.cpp)
TARGET_DEPS  		= $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TARGET_SRC_C))
TARGET_CMD  		= $(AR_CMD) || $(DIE)
TARGET_CLEAN 		= $(TARGET) $(TARGET_DEPS) $(OBJ_DIR)/*.d

include ../../mkfiles/defaults.mk
