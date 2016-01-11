CXXFLAGS += -I../../core/trajectory/excitor -I../../core/trajectory/relaxer -I../../core/trajectory/common -I../../core/network -I../../core/utils -I../../core/settings -I../../core/io -I../../core/task_management -I../../core/application

LDFLAGS  := -L../../core/last/$(OBJ_DIR) -lcore $(LDFLAGS)
