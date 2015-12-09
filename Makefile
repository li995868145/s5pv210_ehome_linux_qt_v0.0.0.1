
help:
	@echo "step1: make app_install"
	@echo "step2: make pc_install"
	@echo "step3: make image"
	


app_install:
	mkdir -p apps/bin apps/lib/ apps/lib/ts apps/lib/fonts apps/etc apps/reciever apps/trigger apps/modules apps/plugins
	make -C emilib-read-only -f Makefile.arm clean
	make -C emilib-read-only -f Makefile.arm
	make -C emilib-read-only -f Makefile.arm install 
	make -C eh_server clean
	make -C eh_server
	make -C eh_server install
	make -C eh_server/plugins clean
	make -C eh_server/plugins
	make -C eh_server/plugins install
	make -C drivers/beep
	make -C drivers/ds18b20
	make -C drivers/adc
	cp -av libs/lib/*.so* apps/lib/
	cp -av libs/lib/ts/* apps/lib/ts/
	cp -av libs/lib/fonts/* apps/lib/fonts/
	cp -av libs/bin/* apps/bin/
	cp -av libs/etc/* apps/etc/
	cp -av libs/plugins/* apps/plugins/
	mv images/*ko apps/modules
	qmake -makefile -o pc/EHOME/Makefile pc/EHOME/arm.pro -spec $(PWD)/libs/mkspecs/qws/linux-arm-g++
	make -C pc/EHOME/ clean
	make -C pc/EHOME/
	mv pc/EHOME/bdehmanager apps/bin/


pc_install:
	make -C emilib-read-only -f Makefile.pc clean
	make -C emilib-read-only -f Makefile.pc
	make -C emilib-read-only -f Makefile.pc install
	qmake -makefile -o pc/EHOME/Makefile pc/EHOME/pc.pro
	make -C pc/EHOME/ clean
	make -C pc/EHOME/
	mv pc/EHOME/ehmanager images/ehmanager

qemu_test:
	make -C qemu

image:
	rm -f images/app.img
	tools/mkyaffs2image apps images/app.img
	chmod 666 images/app.img
	
root:
	dd if=/dev/zero of=images/ramdisk.img count=8 bs=1024k
	mkfs.ext2 images/ramdisk.img
	mkdir -p /tmp/tmpram
	mount images/ramdisk.img /tmp/tmpram
	cp -a rootfs/* /tmp/tmpram/
	umount /tmp/tmpram
	

clean:
	make -C eh_server clean
	make -C eh_server/plugins clean
	make -C emilib-read-only -f Makefile.arm clean 
	make -C drivers/beep clean
	make -C drivers/ds18b20 clean
	make -C drivers/adc clean
	make -C qemu clean
	make -C pc/EHOME/ clean
	rm -rf apps
	rm -rf images/app.img images/ehmanager
