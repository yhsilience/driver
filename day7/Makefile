ifneq ($(KERNELRELEASE),)

obj-m := char_dev.o

else

KDIR :=/home/yh/sharewin/kernel/linux-2.6.35.3
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf  *.o *.mod.o *.mod.c *.symvers  modul* .*.cmd .tmp_*

endif
