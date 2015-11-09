CXXFLAGS += -I../../core/io -I../../core/network -I../../core/settings -I../../core/utils

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp
