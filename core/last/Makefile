SLIB_TARGETS 		= $(TARGET)

TARGET				= $(OBJ_DIR)/libnetwork.so

TARGET_DEPS  	= ../network/$(OBJ_DIR)/network.a ../trajectory/last/$(OBJ_DIR)/trajectory.a
TARGET_CMD  	= $(SLIB_CMD) || $(DIE)
TARGET_CLEAN 	= $(TARGET) $(TARGET_DEPS)

include ../../mkfiles/defaults.mk
