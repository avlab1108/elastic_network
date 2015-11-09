CXXFLAGS += -I../../core/network -I ../../core/utils

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp
