CXXFLAGS += -I../../core/network -I../../core/utils -I../../core/settings -I../../core/io -I../../core/task_management -I../../core/application -I../../core/trajectory/common

LDFLAGS  := -L../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS)
