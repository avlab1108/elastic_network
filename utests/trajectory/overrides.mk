CXXFLAGS += -I../../core/trajectory/excitor -I../../core/trajectory/relaxer -I../../core/trajectory/common -I../../core/network -I ../../core/utils -I../common

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp
