CXXFLAGS += -I../../core/trajectory/excitor -I../../core/trajectory/relaxer -I../../core/trajectory/common -I../../core/network -I../../core/utils -I../../core/settings -I../../core/io -I../../core/task_manager -I../common

LDFLAGS  += -fopenmp -L../../core/last/$(OBJ_DIR) -lcore $(YAML_LIB_DIR) $(YAML_LIB) $(ARMADILLO_LIB_DIR) $(ARMADILLO_LIB)
