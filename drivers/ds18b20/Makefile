SRC_PATH=../../kernel_header

all:
	make -C $(SRC_PATH) M=`pwd` modules 
	cp ds18b20_drv.ko ../../images
clean:
	rm -rf modules.order *.o *.ko *.mod.* Module* .*cmd .tmp*

obj-m	+= ds18b20_drv.o
