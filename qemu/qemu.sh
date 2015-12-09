
NFSROOT=$PWD/rootfs

qemu-system-arm -M smdkc210 -kernel kernel/zImage  -net nic -net tap,ifname=tap0,script=no,downscript=no -serial stdio -append "root=/dev/nfs nfsroot=192.168.183.3:$NFSROOT ip=192.168.183.4:192.168.183.3:192.168.183.1:255.255.255.0  console=ttySAC0,115200n8 rw "  -device exynos4210-ehci-usb -usb
#qemu-system-arm -M vexpress-a9 -kernel kernel/zImage  -net nic -net tap,ifname=tap0,script=no,downscript=no  -serial stdio -append "ip=192.168.183.4:192.168.3.3:192.168.183.1:255.255.255.0 console=ttyAMA0 rw mtdparts='NAND simulator partition':256k(ARMboot)ro,-(root) root=/dev/ram0" -initrd rootfs.img -mtdblock mtdblock.img
#qemu-system-arm -M vexpress-a9 -kernel kernel/zImage  -net nic -net tap,ifname=tap0,script=no,downscript=no  -serial stdio -append "ip=192.168.183.4:192.168.3.3:192.168.183.1:255.255.255.0 console=ttyAMA0 rw root=/dev/ram0" -initrd rootfs.img 
