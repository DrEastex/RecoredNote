#0. Prepare:
0. Linux Kernel
1. binutils source
2. gcc source
3. glibc source

#1. Depends:
flex bison texinfo libgmpv4-dev libgmp-dev libmpfr-dev libmpc-dev

#2. Get Envs:
There Is A Tool To Get Target Env In Gcc Called 'config.guess'
Run This Tool Can Get Target Machine Name

#3. Get Header Files:
`
make mrproper
make ARCH=arm headers_check
make ARCH=arm INSTALL_HDR_PATH=$TARGET_DIR headers_install -j6
`
After, $TARGET_DIR Will Has Dirc 'include'

#4. Compile binutils:
Goes Into binutils Dirc
./configure \
--prefix=$BUILD_DIRC --target=$TARGET_MACHINE

make
make install


#5. Compile gcc 1st Time:
Goes Into Gcc Dirc
./configure --prefix=$TARGET_DIRC \
--build=$HOST_MACHINE --host=$HOST_MACHINE --target=$TARGET_MACHINE \
--with-native-system-header-dir=$KERNEL_HEADER_DIRC \
--without-headers \
--disable-threads \
--enable-languages=c --disable-shared

make all-gcc all-target-libgcc
make install-gcc install-target-libgcc 

#6. Compile glibc:
Goes Into Glibc Dirc
mkdir build
cd build
../configure --prefix=/home/shengxiao/Work/rpi/build/ \
--host=armv7l-unknown-linux-gnueabihf --build=i686-pc-linux-gnu --target=armv7l-unknown-linux-gnueabihf \
--with-binutils=/home/shengxiao/Work/rpi/build/bin --with-headers=/home/shengxiao/Work/rpi/build/include --enable-add-ons --enable-shared

make
make install


#7. Compile gcc 2nd Time(Final):
../configure --prefix=/home/shengxiao/Work/rpi/build/ \
--build=i686-pc-linux-gnu --target=armv7l-unknown-linux-gnueabihf --host=i686-pc-linux-gnu \
--with-native-system-header-dir=/home/shengxiao/Work/rpi/build/include \
--enable-shared

make
make install

