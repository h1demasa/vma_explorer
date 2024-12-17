# KERNEL_SRC ?= $(shell pwd)/../linux-v6.11
KERNEL_SRC ?= /lib/modules/6.11.0-9-generic/build/

obj-m += vm_explorer.o
# vm_ops-objs := src1.o src2.o

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean