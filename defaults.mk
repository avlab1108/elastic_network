GCC=gcc
AR=ar rcs

CXXFLAGS:=-std=c++11 $(CXXFLAGS)
IFLAGS+=
LFLAGS:=-lstdc++ -lm $(LFLAGS)

OBJ_DIR=obj

TARGET_RES=$(OBJ_DIR)/$(TARGET_NAME)

.PHONY: compile clean

compile: $(TARGET_RES)

$(TARGET_RES) : $(OBJS)
	$(TARGET_CMD) $@ $^

$(OBJS) : $(SOURCES)

clean :
	rm -rf $(TARGET_RES) $(OBJS)

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	$(GCC) $(CXXFLAGS) $(IFLAGS) $(LFLAGS) -c -o $@ $<
