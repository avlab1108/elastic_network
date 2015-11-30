CXXFLAGS += -I../../core/network -I../../core/utils -I../common

LDFLAGS  := -L../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS)
