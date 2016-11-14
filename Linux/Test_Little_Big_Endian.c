#include <stdio.h>
 
/*
 * 一个测试机器大小端的函数：
 *
 *    一般机器中 long 为 4 byte (32 bit)，所以可以测试某 long 类型的地址和数据分配情况。
 * 比如 0x12345678，0x78 是低字节数据，0x12 是高字节数据，若 0x78 存在于低地址处，则当
 * 前机器为小端，否则，当前机器为大端。
 * 
 *    返回值：0：小端，1：大端
 *
 */
 
int isBigEndian (void) {
    long digit = 0x12345678;  // 0x12 是高字节数据，0x78 是低字节数据
 
    if ( *(char *)&digit == 0x78 ) {
        return 0;
    } else if ( *(char *)&digit == 0x12 ) {
        return 1;
    }
}
 
int main () {
    printf ( isBigEndian () ? "BigEndian!\n" : "SmallEndian!\n" );
    return 0;
}
