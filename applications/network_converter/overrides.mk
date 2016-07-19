CXXFLAGS += -I../../core/utils

LDFLAGS  := -L../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS)
