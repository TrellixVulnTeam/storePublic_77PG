cmd_/home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio/.install := /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio ./include/uapi/linux/iio events.h types.h; /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio ./include/linux/iio ; /bin/bash scripts/headers_install.sh /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio ./include/generated/uapi/linux/iio ; for F in ; do echo "$(pound)include <asm-generic/$$F>" > /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio/$$F; done; touch /home/nopparat/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/linux/iio/.install
