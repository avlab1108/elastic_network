CXXFLAGS += -I../../core/network -I../../core/utils -I../../core/settings -I../../core/io -I../../core/trajectory/common -fopenmp

LDFLAGS  := -L../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS)
