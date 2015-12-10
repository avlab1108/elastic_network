AR_CMD 		= $(RM) $@ ; $(AR) $(ARFLAGS) $@ $^

SLIB_CMD 	= mkdir -p $(OBJ_DIR); $(CPLUSPLUS_SLIB) $(CXX_SPECIFIC_FLAGS) -fPIC -o $@ $(SLIB_ALL) $^ $(SLIB_NONE) $(EXTRA_SLIB_CMD_ARGS)

EXEC_CMD 	= $(CXX) $(CXX_SPECIFIC_FLAGS) -o $@ $(filter-out %.h, $^) $(LDFLAGS)

DIE 			= ( $(RM) $@; exit 1 )
