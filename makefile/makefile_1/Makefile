SUBDIRS = programa1 programa2 programa3

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

run: 
# 	programa1/programa1
	@echo "Executando programa1..."
	@./programa1/programa1