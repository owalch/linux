ifneq ($(KERNELRELEASE),)
obj-m 		:= MemDriver.o

else
KDIR		:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	@rm -f *.mod.o *.mod.c *.o > /dev/null	
clean:
	@echo cleaning $(PWD)..
	@rm -f *.o core* *.ko *.cmd *. .*.ko .*.cmd *.mod.c > /dev/null
	@rm -fr .tmp_versions > /dev/null	
	@rm -f *.symvers *.order
endif
