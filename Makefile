SUBDIRS=core

.PHONY : compile clean

compile clean:
	@for dir in $(SUBDIRS); do\
		$(MAKE) -C $$dir $@;\
	done
