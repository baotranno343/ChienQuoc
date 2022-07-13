
#include <npc.h>
#include <cmd.h>
#include <equip.h>

inherit NPC;

// 函数：构造处理
void create()
{
        object me = this_object();
        int *color = ({H_WHITE, M_WHITE, WHITE, H_GRAY, M_GRAY, GRAY, H_BLACK, M_BLACK, BLACK, H_RED, M_RED, D_RED, H_MAROON, M_MAROON, MAROON, H_LIME, M_LIME, LIME, H_GREEN, M_GREEN, GREEN, H_BLUE, M_BLUE, BLUE, H_NAVY, M_NAVY, NAVY, H_YELLOW, M_YELLOW, YELLOW, H_OLIVE, M_OLIVE, OLIVE, H_FUCHSIA, M_FUCHSIA, FUCHSIA, H_PURPLE, M_PURPLE, PURPLE, H_CYAN, M_CYAN, CYAN, H_TEAL, M_TEAL, TEAL, H_ORANGE, M_ORANGE, ORANGE, H_BROWN, M_BROWN, BROWN, H_PINK, M_PINK, PINK, H_RADIANCE, M_RADIANCE, RADIANCE});
        int *color_h = ({H_WHITE_H, M_WHITE_H, WHITE_H, H_GRAY_H, M_GRAY_H, GRAY_H, H_BLACK_H, M_BLACK_H, BLACK_H, H_RED_H, M_RED_H, D_RED_H, H_MAROON_H, M_MAROON_H, MAROON_H, H_LIME_H, M_LIME_H, LIME_H, H_GREEN_H, M_GREEN_H, GREEN_H, H_BLUE_H, M_BLUE_H, BLUE_H, H_NAVY_H, M_NAVY_H, NAVY_H, H_YELLOW_H, M_YELLOW_H, YELLOW_H, H_OLIVE_H, M_OLIVE_H, OLIVE_H, H_FUCHSIA_H, M_FUCHSIA_H, FUCHSIA_H, H_PURPLE_H, M_PURPLE_H, PURPLE_H, H_CYAN_H, M_CYAN_H, CYAN_H, H_TEAL_H, M_TEAL_H, TEAL_H, H_ORANGE_H, M_ORANGE_H, ORANGE_H, H_BROWN_H, M_BROWN_H, BROWN_H, H_PINK_H, M_PINK_H, PINK_H, H_RADIANCE_H, M_RADIANCE_H, RADIANCE_H});
        int sizeof_color = sizeof(color);
        int sizeof_color_h = sizeof(color_h);

        set_name("Quá lộ đích");
        set_level(5);

        if (random(2))
        {
                set_gender(1);

                switch (random(9))
                {
                default:
                        set_armor_code(M_DUANGUA);
                        break;
                case 1:
                        set_armor_code(M_BUYI);
                        break;
                case 2:
                        set_armor_code(M_JINZHUANG);
                        break;
                case 3:
                        set_armor_code(M_CHANGPAO);
                        break;
                case 4:
                        set_armor_code(M_GUANPAO);
                        break;
                case 5:
                        set_armor_code(M_PIJIA);
                        break;
                case 6:
                        set_armor_code(M_RUANJIA);
                        break;
                case 7:
                        set_armor_code(M_KAIJIA);
                        break;
                case 8:
                        set_armor_code(M_ZHANJIA);
                        break;
                }
                set_armor_color_1(color_h[random(sizeof_color_h)] | color[random(sizeof_color)]);
                set_armor_color_2(color_h[random(sizeof_color_h)] | color[random(sizeof_color)]);

                switch (random(9))
                {
                default:
                        set_head_code(M_BANGDAI);
                        break;
                case 1:
                        set_head_code(M_PINGMAO);
                        break;
                case 2:
                        set_head_code(M_WUSHENGMAO);
                        break;
                case 3:
                        set_head_code(M_DAOGUAN);
                        break;
                case 4:
                        set_head_code(M_ZHANMAO);
                        break;
                case 5:
                        set_head_code(M_PIMAO);
                        break;
                case 6:
                        set_head_code(M_ZIJINGUAN);
                        break;
                case 7:
                        set_head_code(M_YINGKUI);
                        break;
                case 8:
                        set_head_code(M_ZHANKUI);
                        break;
                }
                set_head_color(color[random(sizeof_color)] | (color[random(sizeof_color)] << 8));
        }
        else
        {
                set_gender(2);

                switch (random(9))
                {
                default:
                        set_armor_code(F_DUANSHAN);
                        break;
                case 1:
                        set_armor_code(F_BUYI);
                        break;
                case 2:
                        set_armor_code(F_JINZHUANG);
                        break;
                case 3:
                        set_armor_code(F_BEIZI);
                        break;
                case 4:
                        set_armor_code(F_RUQUN);
                        break;
                case 5:
                        set_armor_code(F_PIJIA);
                        break;
                case 6:
                        set_armor_code(F_RUANJIA);
                        break;
                case 7:
                        set_armor_code(F_KAIJIA);
                        break;
                case 8:
                        set_armor_code(F_ZHANJIA);
                        break;
                }
                set_armor_color_1(color_h[random(sizeof_color_h)] | color[random(sizeof_color)]);
                set_armor_color_2(color_h[random(sizeof_color_h)] | color[random(sizeof_color)]);

                switch (random(9))
                {
                default:
                        set_head_code(F_BANGDAI);
                        break;
                case 1:
                        set_head_code(F_PINGMAO);
                        break;
                case 2:
                        set_head_code(F_WUSHENGMAO);
                        break;
                case 3:
                        set_head_code(F_DAOGUAN);
                        break;
                case 4:
                        set_head_code(F_SHAMAO);
                        break;
                case 5:
                        set_head_code(F_PIMAO);
                        break;
                case 6:
                        set_head_code(F_ZIJINGUAN);
                        break;
                case 7:
                        set_head_code(F_YINGKUI);
                        break;
                case 8:
                        set_head_code(F_ZHANKUI);
                        break;
                }
                set_head_color(color[random(sizeof_color)] | (color[random(sizeof_color)] << 8));
        }

        switch (random(5))
        {
        default:
                set_weapon_code(UNARMED);
                break;
        case 1:
                set_weapon_code(BLADE);
                break;
        case 2:
                set_weapon_code(SWORD);
                break;
        case 3:
                set_weapon_code(SPEAR);
                break;
        case 4:
                set_weapon_code(STICK);
                break;
        }

        setup();

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 10);                                      // 循环心跳：１秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１秒处理
{
        GO_CMD->main_npc(me, sprintf("%d", random(8) + 1));
}
