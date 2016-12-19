ifneq ($(KERNELRELEASE),)

obj-m := memdev.o

else

KDIR := /home/yh/sharewin/kernel/linux-2.6.35.3
all:
	make -C $(KDIR) -I M=$(PWD) modules
clean:
	rm -f  *.o *.mod.o *.mod.c *.symvers  modul*

endif
