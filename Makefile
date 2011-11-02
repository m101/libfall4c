all:
	cd src && $(MAKE)

.PHONY: clean mrproper

clean:
	cd src && $(MAKE) clean

mrproper: clean
	cd src && $(MAKE) mrproper
