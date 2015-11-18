CXXFLAGS += -I../../core/io -I../../core/network -I../../core/trajectory/common -I../../core/trajectory/excitor -I../../core/settings -I../../core/utils -I../common

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp -larmadillo -fopenmp
