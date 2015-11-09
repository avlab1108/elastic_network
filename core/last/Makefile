SLIB_TARGETS 		= $(TARGET)

TARGET				= $(OBJ_DIR)/libcore.so

TARGET_DEPS  	= ../utils/$(OBJ_DIR)/utils.a ../io/$(OBJ_DIR)/io.a ../network/$(OBJ_DIR)/network.a ../settings/$(OBJ_DIR)/settings.a ../trajectory/last/$(OBJ_DIR)/trajectory.a
TARGET_CMD  	= $(SLIB_CMD) || $(DIE)
TARGET_CLEAN 	= $(TARGET) $(TARGET_DEPS)

include ../../mkfiles/defaults.mk
