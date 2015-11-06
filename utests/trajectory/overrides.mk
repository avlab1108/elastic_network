CXXFLAGS += -I../../core/trajectory/excitor
CXXFLAGS += -I../../core/trajectory/relaxer
CXXFLAGS += -I../../core/trajectory/common
CXXFLAGS += -I../../core/network

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp
