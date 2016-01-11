CXXFLAGS += -I../../../core/network -I../../../core/utils -I../common

LDFLAGS  := -L../../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS) -lboost_unit_test_framework
