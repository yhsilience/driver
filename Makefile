KERNELDIR ?= /home/yh/sharewin/kernel/linux-2.6.35.3
obj-m := hello.o
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -rf .tmp* .*.ko* .*.o.cmd *.ko *.mod.* *.symvers *.symvers *.order
