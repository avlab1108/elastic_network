BUILD_DIRS = core applications

include mkfiles/defaults.mk

doc:
	doxygen Doxyfile

doc_pdf:
	doxygen Doxyfile
	$(MAKE) -C latex
