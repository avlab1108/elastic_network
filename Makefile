BUILD_DIRS = core exec utests

include mkfiles/defaults.mk

doc:
	doxygen Doxyfile
