
#include <npc.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：初始化衣服
void init_figure( object me, int type, int gender, int age )
{
        int *table1, *table2, color1, color2;

        if( gender == MALE )    // 男性
        {
                me->set_gender( MALE );
                switch( type )
                {
                case KING :             // 王爷
                        me->set("figure", "王爷");
                        me->set_armor_code( M_GUANPAO );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_YELLOW | H_YELLOW_H );
                                me->set_armor_color_2( H_YELLOW | H_YELLOW_H );
                                break;
                       case 1 : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                break;
                       case 2 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                break;
                        }
                        me->set_head_code( M_ZIJINGUAN );
                        switch( random(3) )
                        {
                      default : me->set_head_color( H_MAROON | H_MAROON_H );  break;
                       case 1 : me->set_head_color( H_YELLOW | H_YELLOW_H );  break;
                       case 2 : me->set_head_color( H_RED | H_RED_H );  break;
                        }
                        break;
                case MINISTER :         // 大臣
                        me->set("figure", "大臣");
                        me->set_armor_code( M_GUANPAO );
                        me->set_head_code( M_DAOGUAN );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                       case 3 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                        }
                        break;
                case CAPTOR :           // 捕头
                        me->set("figure", "捕头");
                        me->set_armor_code( M_PIJIA );
                        me->set_head_code( M_WUSHENGMAO );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLACK | H_BLACK_H );
                                me->set_armor_color_2( H_BLACK | H_BLACK_H );
                                me->set_head_color( H_BLACK | H_BLACK_H );
                                break;
                        }
                        break;
              case CAPTOR_2 :           // 衙役
                        me->set("figure", "衙役");
                        me->set_armor_code( M_JINZHUANG );
                        me->set_head_code( M_WUSHENGMAO );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                       case 1 : me->set_armor_color_1( GRAY | GRAY_H );
                                me->set_armor_color_2( GRAY | GRAY_H );
                                me->set_head_color( GRAY | GRAY_H );
                                break;
                        }
                        break;

                case MARSHAL :          // 将帅
                        me->set("figure", "将帅");
                        me->set_armor_code( M_ZHANJIA );
                        me->set_head_code( M_ZHANKUI );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( H_YELLOW | H_YELLOW_H );
                                me->set_armor_color_2( H_YELLOW | H_YELLOW_H );
                                me->set_head_color( H_YELLOW | H_YELLOW_H );
                                break;
                       case 1 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                        }
                        break;
                case GENERAL :          // 军官
                        me->set("figure", "军官");
                        me->set_armor_code( M_KAIJIA );
                        me->set_head_code( M_YINGKUI );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                        }
                        break;
                case SOLDIER :          // 士兵
                        me->set("figure", "士兵");
                        me->set_armor_code( M_RUANJIA );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( H_OLIVE | H_OLIVE_H );
                                me->set_armor_color_2( H_OLIVE | H_OLIVE_H );
                                break;
                       case 1 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                break;
                        }
                        me->set_head_code( M_YINGKUI );
                        switch( random(2) )
                        {
                      default : me->set_head_color( H_RED | H_RED_H );  break;
                       case 1 : me->set_head_color( H_CYAN | H_CYAN_H );  break;
                        }
                        break;

                case RICH_MAN :         // 富人、富商
                        me->set("figure", "富人");
                        me->set_armor_code( M_CHANGPAO );
                        me->set_head_code( M_PINGMAO );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 2 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                       case 3 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case RICH_YOUNG :       // 富家公子
                        me->set("figure", "富家公子");
                        me->set_armor_code( M_CHANGPAO );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 2 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                       case 3 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        me->set_head_code( M_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_head_color( H_YELLOW | H_YELLOW_H );  break;
                       case 1 : me->set_head_color( H_RED | H_RED_H );  break;
                       case 2 : me->set_head_color( H_MAROON | H_MAROON_H );  break;
                        }
                        break;
                case RICH_BOY :         // 富家男孩
                        me->set("figure", "富家男孩");
                        me->set_armor_code( M_DUANGUA );
                        me->set_head_code( M_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_PINK | H_PINK_H );
                                me->set_armor_color_2( H_PINK | H_PINK_H );
                                me->set_head_color( H_PINK | H_PINK_H );
                                break;
                       case 2 : me->set_armor_color_1( H_GREEN | H_GREEN_H );
                                me->set_armor_color_2( H_GREEN | H_GREEN_H );
                                me->set_head_color( H_GREEN | H_GREEN_H );
                                break;
                        }
                        break;

                case SELLER :           // 老板
                        me->set("figure", "老板");
                        me->set_armor_code( M_BUYI );
                        me->set_head_code( M_ZHANMAO );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 3 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;
                case SCHOLAR :          // 书生
                        me->set("figure", "书生");
                        me->set_armor_code( M_CHANGPAO );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( WHITE | WHITE_H );
                                me->set_armor_color_2( WHITE | WHITE_H );
                                break;
                       case 1 : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                break;
                        }
                        me->set_head_code( M_BANGDAI );
                        switch( random(2) )
                        {
                      default : me->set_head_color( WHITE | WHITE_H );  break;
                       case 1 : me->set_head_color( H_BLUE | H_BLUE_H );  break;
                        }
                        break;
                case BOY :              // 穷家男孩
                        me->set("figure", "穷家男孩");
                        me->set_armor_code( M_DUANGUA );
                        me->set_head_code( M_BANGDAI );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 3 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;

                case PALADIN :          // 游侠
                        me->set("figure", "游侠");
                        me->set_armor_code( M_JINZHUANG );
                        me->set_head_code( M_WUSHENGMAO );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 3 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                        }
                        break;
                case GUARD :            // 守卫
                        me->set("figure", "守卫");
                        me->set_armor_code( M_JINZHUANG );
                        me->set_head_code( M_BANGDAI );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 3 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;
                case WARRIOR :          // 打手
                        me->set("figure", "打手");
                        me->set_armor_code( M_BUYI );
                        me->set_head_code( M_BANGDAI );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 3 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;

                case WOODMAN :          // 猎户
                        me->set("figure", "猎户");
                        switch( random(2) )
                        {
                      default : me->set_armor_code( M_BUYI );  break;
                       case 1 : me->set_armor_code( M_JINZHUANG );  break;
                        }
                        me->set_head_code( M_BANGDAI );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 3 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;
                case WAITER :           // 店小二
                        me->set("figure", "店小二");
                        me->set_armor_code( M_BUYI );
                        me->set_head_code( M_ZHANMAO );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case ROGUE :            // 流氓、无赖
                        me->set("figure", "流氓");
                        me->set_armor_code( M_BUYI );
                        me->set_head_code( M_BANGDAI );
                        switch( random(2) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;

                case FARMER :           // 农民
                        me->set("figure", "农民");
                        me->set_armor_code( M_DUANGUA );
                        me->set_head_code( M_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_GRAY | H_GRAY_H );
                                me->set_armor_color_2( H_GRAY | H_GRAY_H );
                                me->set_head_color( H_GRAY | H_GRAY_H );
                                break;
                       case 1 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                       case 2 : me->set_armor_color_1( M_OLIVE | M_OLIVE_H );
                                me->set_armor_color_2( M_OLIVE | M_OLIVE_H );
                                me->set_head_color( M_OLIVE | M_OLIVE_H );
                                break;
                        }
                        break;

                case ZOMBIE :           // 僵尸
                        me->set("figure", "僵尸");
                        me->set_armor_code( M_GUANPAO );
                        me->set_head_code( M_DAOGUAN );
                        switch( random(4) )
                        {
                      default : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_CYAN | H_CYAN_H );
                                me->set_armor_color_2( H_CYAN | H_CYAN_H );
                                me->set_head_color( H_CYAN | H_CYAN_H );
                                break;
                       case 3 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                        }
                        break;
                }
        }
        else    // 女性
        {
                me->set_gender( FEMALE );
                switch( type )
                {
                case RICH_WOMAN :       // 贵妇
                        me->set("figure", "贵妇");
                        me->set_armor_code( F_RUQUN );
                        me->set_head_code( F_PINGMAO );
                        switch( random(5) )
                        {
                      default : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_PINK | H_PINK_H );
                                me->set_armor_color_2( H_PINK | H_PINK_H );
                                me->set_head_color( H_PINK | H_PINK_H );
                                break;
                       case 3 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 4 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case RICH_LADY :        // 富家小姐
                        me->set("figure", "富家小姐");
                        me->set_armor_code( F_RUQUN );
                        me->set_head_code( F_BANGDAI );
                        switch( random(5) )
                        {
                      default : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_PINK | H_PINK_H );
                                me->set_armor_color_2( H_PINK | H_PINK_H );
                                me->set_head_color( H_PINK | H_PINK_H );
                                break;
                       case 3 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 4 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case RICH_GIRL :        // 富家女孩
                        me->set("figure", "富家女孩");
                        me->set_armor_code( F_DUANSHAN );
                        me->set_head_code( F_BANGDAI );
                        switch( random(5) )
                        {
                      default : me->set_armor_color_1( H_MAROON | H_MAROON_H );
                                me->set_armor_color_2( H_MAROON | H_MAROON_H );
                                me->set_head_color( H_MAROON | H_MAROON_H );
                                break;
                       case 1 : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 2 : me->set_armor_color_1( H_PINK | H_PINK_H );
                                me->set_armor_color_2( H_PINK | H_PINK_H );
                                me->set_head_color( H_PINK | H_PINK_H );
                                break;
                       case 3 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 4 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case SERVANT_GIRL :     // 丫鬟
                        me->set("figure", "丫鬟");
                        me->set_armor_code( F_BEIZI );
                        me->set_head_code( F_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_PINK | H_PINK_H );
                                me->set_armor_color_2( H_PINK | H_PINK_H );
                                me->set_head_color( H_PINK | H_PINK_H );
                                break;
                       case 1 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;

                case FARM_WOMAN :       // 村妇
                        me->set("figure", "村妇");
                        me->set_armor_code( F_BUYI );
                        me->set_head_code( F_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case FARM_LADY :        // 村姑
                        me->set("figure", "村姑");
                        me->set_armor_code( F_BEIZI );
                        me->set_head_code( F_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                case GIRL :             // 穷家女孩
                        me->set("figure", "穷家女孩");
                        me->set_armor_code( F_DUANSHAN );
                        me->set_head_code( F_BANGDAI );
                        switch( random(3) )
                        {
                      default : me->set_armor_color_1( H_RED | H_RED_H );
                                me->set_armor_color_2( H_RED | H_RED_H );
                                me->set_head_color( H_RED | H_RED_H );
                                break;
                       case 1 : me->set_armor_color_1( H_LIME | H_LIME_H );
                                me->set_armor_color_2( H_LIME | H_LIME_H );
                                me->set_head_color( H_LIME | H_LIME_H );
                                break;
                       case 2 : me->set_armor_color_1( H_BLUE | H_BLUE_H );
                                me->set_armor_color_2( H_BLUE | H_BLUE_H );
                                me->set_head_color( H_BLUE | H_BLUE_H );
                                break;
                        }
                        break;
                }
        }
}

// -------------------------------------------------------------

// 函数：设置装备对象
int use_equip( object me, object equip )    // 只有装备，没有卸除
{
        int point;

        if( !equip || !equip->get_equip_type() ) return 0;

        switch( equip->get_equip_type() )
        {
      case ARMOR_TYPE : me->set_armor_code( equip->get_armor_code() );
                        me->set_armor_color_1( equip->get_armor_color_1() );
                        me->set_armor_color_2( equip->get_armor_color_2() );
//                        if (MAIN_D->get_host_type()!=1000)
			if (0)
                        	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%c%d%d", 0x23, getoid(me), 
                                	me->get_armor_code(), me->get_armor_color_1(), me->get_armor_color_2() );  

			else
							send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%d", 0x23, getoid(me), 
                                	me->get_armor_code(), me->get_armor_color_1() );  
								
                        break;
       case HEAD_TYPE : me->set_head_code( equip->get_head_code() );
                        me->set_head_color( equip->get_head_color() );
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%d", 0x7e, getoid(me), me->get_head_code(), me->get_head_color() );
                        break;
     case WEAPON_TYPE : me->set_weapon_code( equip->get_weapon_type() );
                        me->set_weapon_color( equip->get_weapon_level() );
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%w%w", 0x7c, getoid(me), me->get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2() );
                        break;
              default : break;
        }

        if( point = equip->get( "hp" ) )  me->add( "hp",  point);    // 只是累加属性
        if( point = equip->get( "mp" ) )  me->add( "mp",  point);
        if( point = equip->get( "hp%" ) ) me->add( "hp%", point);
        if( point = equip->get( "mp%" ) ) me->add( "mp%", point);
        if( point = equip->get( "hp*" ) ) me->add( "hp*", point);
        if( point = equip->get( "mp*" ) ) me->add( "mp*", point);
        if( point = equip->get( "ap" ) )  me->add( "ap",  point);
        if( point = equip->get( "ap%" ) ) me->add( "ap%", point);
        if( point = equip->get( "dp" ) )  me->add( "dp",  point);
        if( point = equip->get( "cp" ) )  me->add( "cp",  point);
        if( point = equip->get( "cp%" ) ) me->add( "cp%", point);
        if( point = equip->get( "pp" ) )  me->add( "pp",  point);
        if( point = equip->get( "sp" ) )  me->add( "sp",  point);
        if( point = equip->get(  "!%") )  me->add(  "!%", point);
        if( point = equip->get( "c!%") )  me->add( "c!%", point);
        if( point = equip->get( "t!%") )  me->add( "t!%", point);
        if( point = equip->get(  "?%") )  me->add(  "?%", point);
        if( point = equip->get( "c?%") )  me->add( "c?%", point);
        if( point = equip->get( "-*" ) )  me->add( "-*",  point);
        if( point = equip->get("-c*" ) )  me->add("-c*",  point);
        if( point = equip->get( "-*%" ) ) me->add( "-*%", point);
        if( point = equip->get("-c*%" ) ) me->add("-c*%", point);
        if( point = equip->get(  "@%" ) ) me->add(  "@%", point);
        if( point = equip->get( "X@%" ) ) me->add( "X@%", point);
        if( point = equip->get( "-@%" ) ) me->add( "-@%", point);
        if( point = equip->get(  "/%" ) ) me->add(  "/%", point);
        if( point = equip->get( "??%" ) ) me->add( "??%", point);
        if( point = equip->get(  "#%" ) ) me->add(  "#%", point);

        return 1;
}
