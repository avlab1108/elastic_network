CXXFLAGS += -I../../core/io -I../../core/network -I../../core/settings

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lcore -lyaml-cpp
