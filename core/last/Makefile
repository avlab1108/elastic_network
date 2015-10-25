SLIB_TARGETS 		= $(TARGET)

TARGET				= $(OBJ_DIR)/libnetwork.so

TARGET_DEPS  	= ../network/$(OBJ_DIR)/network.a ../trajectory/excitor/$(OBJ_DIR)/excitor.a
TARGET_CMD  	= $(SLIB_CMD) || $(DIE)
TARGET_CLEAN 	= $(TARGET) $(TARGET_DEPS)

include ../../mkfiles/defaults.mk
