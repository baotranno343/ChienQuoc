
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：其它征状更新
void into_effect( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) 
{
/*      if( effect1 )    // 简单征状标志１(３２位)
        {
        }       */

/*      if( effect2 )    // 简单征状标志２(３２位)
        {
        }       */

        if( effect3 )    // 简单征状标志３(３２位)
        {
/*              if( effect3 & 0x0000ffff )
                {
                        if( effect3 & 0x000000ff )
                        {
                                if( effect3 & 0x00000001 )
                                if( effect3 & 0x00000002 )
                                if( effect3 & 0x00000004 )
                                if( effect3 & 0x00000008 )
                                if( effect3 & 0x00000010 )
                                if( effect3 & 0x00000020 )
                                if( effect3 & 0x00000040 )
                                if( effect3 & 0x00000080 )
                        }
                        if( effect3 & 0x0000ff00 )
                        {
                                if( effect3 & 0x00000100 )
                                if( effect3 & 0x00000200 )
                                if( effect3 & 0x00000400 )
                                if( effect3 & 0x00000800 )
                                if( effect3 & 0x00001000 )
                                if( effect3 & 0x00002000 )
                                if( effect3 & 0x00004000 )
                                if( effect3 & 0x00008000 )
                        }
                }       */
                if( effect3 & 0xffff0000 )
                {
/*                      if( effect3 & 0x00ff0000 )
                        {
                                if( effect3 & 0x00010000 )
                                if( effect3 & 0x00020000 )
                                if( effect3 & 0x00040000 )
                                if( effect3 & 0x00080000 )
                                if( effect3 & 0x00100000 )
                                if( effect3 & 0x00200000 )
                                if( effect3 & 0x00400000 )
                                if( effect3 & 0x00800000 )
                        }       */
                        if( effect3 & 0xff000000 )
                        {
//                              if( effect3 & 0x01000000 )
//                              if( effect3 & 0x02000000 )
//                              if( effect3 & 0x04000000 )
//                              if( effect3 & 0x08000000 )
//                              if( effect3 & 0x10000000 )
//                              if( effect3 & 0x20000000 )
                                if( effect3 & 0x40000000 ) "/effect/org"->into_effect_3(me);   // ORG
                                if( effect3 & 0x80000000 ) "/effect/city"->into_effect_3(me);   // CITY
                        }
                }
        }

/*      if( effect7 )    // 复杂征状标志(３２位)
        {
        }       */
}
