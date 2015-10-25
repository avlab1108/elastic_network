CXXFLAGS += -I../../core/trajectory/excitor
CXXFLAGS += -I../../core/network

LDFLAGS += -L../../core/last/$(OBJ_DIR) -lnetwork
