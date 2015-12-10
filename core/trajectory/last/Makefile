LIB_TARGETS   = $(TARGET)

TARGET        = $(OBJ_DIR)/trajectory.a

TARGET_SRC_1  = $(wildcard ../common/*.cpp)
TARGET_DEPS_1 = $(patsubst ../common/%.cpp,../common/$(OBJ_DIR)/%.o,$(TARGET_SRC_1))

TARGET_SRC_2  = $(wildcard ../excitor/*.cpp)
TARGET_DEPS_2 = $(patsubst ../excitor/%.cpp,../excitor/$(OBJ_DIR)/%.o,$(TARGET_SRC_2))

TARGET_SRC_3  = $(wildcard ../relaxer/*.cpp)
TARGET_DEPS_3 = $(patsubst ../relaxer/%.cpp,../relaxer/$(OBJ_DIR)/%.o,$(TARGET_SRC_3))

TARGET_DEPS   = $(TARGET_DEPS_1) \
                $(TARGET_DEPS_2) \
                $(TARGET_DEPS_3)

TARGET_CMD    = mkdir -p $(OBJ_DIR) ; $(AR_CMD) || $(DIE)
TARGET_CLEAN  = $(TARGET) $(TARGET_DEPS)

include ../../../mkfiles/defaults.mk
