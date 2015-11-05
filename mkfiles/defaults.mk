no_target ::
	@echo "Please specify a target to build, such as:"
	@echo "$(TARGET_LIST)"
	@exit 1

%.mk         :: ;

OBJ_DIR = obj

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

include $(SELF_DIR)/default_defs.mk
include $(SELF_DIR)/default_commands.mk
include $(SELF_DIR)/default_rules.mk

TARGET_LIST 			= all compile lib slib exec clean

ALL_TARGETS 			= $(TARGET)
CLEAN_TARGETS 		= $(TARGET_CLEAN)
ALL_DEP_TARGETS 	= $(TARGET_DEPS)

default_target : $(ALL_TARGETS)

all : compile lib slib exec

lib : compile

slib : lib

clean ::
ifneq "$(strip $(BUILD_DIRS))" ""
	@for sub in $(strip $(BUILD_DIRS)) ; do  \
		if [ ! -d "$$sub" ] ; then  \
			continue;               \
		elif [ ! \( -f "$$sub/Makefile"  -o -f "$$sub/makefile" \) ] ; then \
			continue; \
		fi ;                        \
		CCPWD=`pwd` ;               \
		cd $$sub ;                  \
		$(MAKE) -w $@ ;      \
		cd $$CCPWD ;                \
	done
endif
ifneq "$(strip $(CLEAN_TARGETS))" ""
	$(RM) -r $(CLEAN_TARGETS) $(ALL_TARGETS)
endif

compile :
ifneq "$(strip $(BUILD_DIRS))" ""
	@for sub in $(strip $(BUILD_DIRS)) ; do  \
		if [ ! -d "$$sub" ] ; then  \
	    continue;               \
	  elif [ ! \( -f "$$sub/Makefile"  -o -f "$$sub/makefile" \) ] ; then \
	    continue; \
	  fi ;                        \
	  CCPWD=`pwd` ;               \
	  cd $$sub ;                  \
		$(MAKE) -w $@ ;      \
	  cd $$CCPWD ;                \
	done
endif
ifneq "$(strip $(COMPILE_TARGETS))" ""
	$(MAKE) $(COMPILE_TARGETS)
endif

lib :
ifneq "$(strip $(BUILD_DIRS))" ""
	@for sub in $(strip $(BUILD_DIRS)) ; do  \
   	if [ ! -d "$$sub" ] ; then  \
    	continue;               \
   	elif [ ! \( -f "$$sub/Makefile"  -o -f "$$sub/makefile" \) ] ; then \
     	continue; \
   	fi ;                        \
   	CCPWD=`pwd` ;               \
   	cd $$sub ;                  \
   	$(MAKE) -w $@ ;      \
   	cd $$CCPWD ;                \
 	done
endif
ifneq "$(strip $(LIB_TARGETS))" ""
	$(MAKE) $(LIB_TARGETS)
endif

slib :
ifneq "$(strip $(BUILD_DIRS))" ""
	@for sub in $(strip $(BUILD_DIRS)) ; do  \
   	if [ ! -d "$$sub" ] ; then  \
    	continue;               \
   	elif [ ! \( -f "$$sub/Makefile"  -o -f "$$sub/makefile" \) ] ; then \
     	continue; \
   	fi ;                        \
   	CCPWD=`pwd` ;               \
   	cd $$sub ;                  \
   	$(MAKE) -w $@ ;      \
   	cd $$CCPWD ;                \
 	done
endif
ifneq "$(strip $(SLIB_TARGETS))" ""
	$(MAKE) $(SLIB_TARGETS)
endif

exec :
ifneq "$(strip $(BUILD_DIRS))" ""
	@for sub in $(strip $(BUILD_DIRS)) ; do  \
		if [ ! -d "$$sub" ] ; then  \
			continue;               \
		elif [ ! \( -f "$$sub/Makefile"  -o -f "$$sub/makefile" \) ] ; then \
			continue; \
		fi ;                        \
		CCPWD=`pwd` ;               \
		cd $$sub ;                  \
		$(MAKE) -w $@ ;      \
		cd $$CCPWD ;                \
	done
endif
ifneq "$(strip $(EXEC_TARGETS))" ""
	$(MAKE) $(EXEC_TARGETS)
endif

.PHONY: $(TARGET_LIST) $(CLEAN_TARGET_LIST)

ifdef TARGET
$(TARGET) : $(TARGET_DEPS)
	$(TARGET_CMD)
endif

-include $(OBJ_DIR)/*.d
