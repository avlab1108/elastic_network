LIB_TARGETS 		= $(TARGET)

TARGET				= $(OBJ_DIR)/trajectory.a

TARGET_DEPS  	= ../result_observer/$(OBJ_DIR)/*.o \
								../excitor/$(OBJ_DIR)/*.o \
								../relaxer/$(OBJ_DIR)/*.o

TARGET_CMD  	= mkdir -p $(OBJ_DIR) ; $(AR_CMD) || $(DIE)
TARGET_CLEAN 	= $(TARGET) $(TARGET_DEPS)

include ../../../mkfiles/defaults.mk
