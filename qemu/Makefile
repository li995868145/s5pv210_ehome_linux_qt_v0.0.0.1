


qemu:
	echo "qemu test"
	rm -rf rootfs/*
	cp -av ../rootfs/* ./rootfs/
	rm -rf rootfs/home
	cp -av ../apps rootfs/home
	./qemu.sh

qemu_root:
	echo "qemu test"
	rm -rf rootfs/*
	cp -av ../rootfs/* ./rootfs/
	rm -rf rootfs/home
	cp -av ../apps rootfs/home

clean:
	rm -rf rootfs/*
