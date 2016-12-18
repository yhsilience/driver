KERNELDIR ?= /home/yh/sharewin/kernel/linux-2.6.35.3
obj-m += proc_rw.o
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -rf .tmp* .*.o.cmd  *.mod.* *.symvers *.symvers *.order .*.ko.cmd
