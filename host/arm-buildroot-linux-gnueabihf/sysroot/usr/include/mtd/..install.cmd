cmd_/home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd/.install := /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd ./include/uapi/mtd inftl-user.h mtd-abi.h mtd-user.h nftl-user.h ubi-user.h; /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd ./include/mtd ; /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd ./include/generated/uapi/mtd ; for F in ; do echo "$(pound)include <asm-generic/$$F>" > /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd/$$F; done; touch /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/mtd/.install
