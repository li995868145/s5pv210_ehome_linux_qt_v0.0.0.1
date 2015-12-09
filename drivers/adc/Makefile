SRC_PATH=../../kernel_header/

all:
	make -C $(SRC_PATH) M=`pwd` modules 
	cp adc_drv.ko ../../images
clean:
	rm -rf modules.order *.o *.ko *.mod.* Module*  .tmp* .*cmd

obj-m	+= adc_drv.o
