BUILD_DIRS = core applications

include mkfiles/defaults.mk

doc:
	doxygen Doxyfile
