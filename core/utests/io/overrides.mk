CXXFLAGS += -I../../../core/io -I../../../core/network -I../../../core/settings -I../../../core/utils -I../common

LDFLAGS  := -L../../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS) -lboost_unit_test_framework
