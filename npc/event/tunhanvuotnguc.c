
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;

// 函数：获取人物造型
int get_char_picid() { return 8000; }

// 函数：构造处理
void create()
{
        set_name(HIY "Bắt Nạt Con Nít");

        set_char_type(FIGHTER_TYPE); // init_level 要用到

        set_head_color(0xd308);

        NPC_ENERGY_D->init_level(this_object(), 80 + random(3)); //
        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action(object who) { return 0; } // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：掉宝奖励
void drop_items(object who) { __FILE__->drop_items_callout(this_object(), who); }

// 函数：掉宝奖励(在线更新)
void drop_items_callout(object me, object who)
{
        object item, leader;
        string file, owner, id;
        int p, rate, i, size, gold, equip, total, total2, tuihang;
        int z, x, y;

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        id = who->get_leader();
        who->add_exp(2000);
        who->add_cash(1500);
        "sys/sys/test_db"->add_yuanbao(who, 2);
        item = new ("item/event/tuihang");
        tuihang = item->move(who, -1);
        if (!tuihang)
        {
                destruct(item);
                return;
        }
        item->add_to_user(tuihang);
        send_user(who, "%c%s", ';', "Bạn nhận được " HIR + item->get_name());
        //	USER_D->user_channel(sprintf(HIC"Vị anh hùng "HIY "%s"  HIC" vừa đánh được "HIY "Tù Nhân Vượt Ngục"HIC" và nhận được lấy được Túi Hàng từ tay chúng", who->get_name() ));
}
