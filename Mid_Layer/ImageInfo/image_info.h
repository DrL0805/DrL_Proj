#ifndef     IMAGE_INFO_H
#define     IMAGE_INFO_H

// 软件应用版本
//固件版本号说明: 版本号是32位，只使用低24位有用
//bit 16~23: main version,  value: 0x00xxxx~0x09xxxx
//bit 8 ~15: sub version,   value: 0x00xx~0x09xx
//bit 0 ~ 7: debug version, value: 0x00~0x09

#define         PROJECT_VERSION             0x00000006

#endif      // IMAGE_INFO_H
