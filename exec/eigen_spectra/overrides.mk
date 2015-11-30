CXXFLAGS += -I../../core/network -I../../core/utils -I../../core/settings -I../../core/io -fopenmp

LDFLAGS  += -fopenmp -L../../core/last/$(OBJ_DIR) -lcore $(YAML_LIB_DIR) $(YAML_LIB) $(ARMADILLO_LIB_DIR) $(ARMADILLO_LIB)
