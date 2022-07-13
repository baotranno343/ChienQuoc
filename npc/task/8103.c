
#include <npc.h>
#include <ansi.h>
#include <equip.h>

inherit NPC;

// 函数：劫镖强盗
int is_escort_robber() { return 1; }

// 函数：劫镖强盗(quest)
int is_escort_robber_2() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ăn Mày");
        set_char_picid(451); // 蒙面人
        set_char_type(FIGHTER_TYPE);

        setup();

        set("birthday", time());
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：获取当前ＨＰ
int get_hp() { return get_max_hp(); } // 无法杀死

// 函数：设置当前ＨＰ
int set_hp(int point) { return get_max_hp(); }

// 函数：增添当前ＨＰ
int add_hp(int point) { return get_max_hp(); }

// 函数：获取气血比例
int get_hp_cent() { return 50; }

// 函数：复位处理
void reset()
{
        object owner, item;

        if (gone_time(get("birthday")) >= 600) // 10 分钟
        {
                if (objectp(owner = find_player(sprintf("%d", get("task")))) && objectp(item = present("Vật Phẩm Quý Bấu", owner, 1, MAX_CARRY)))
                        item->set_heart_3min(); // 下个３分钟

                remove_from_scene();
                destruct(this_object());
        }
}

// 函数：可以接受战斗
/*      int can_be_fighted( object who ) 
{ 
        object owner;
        int id;

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;

        id = who->get_number();
        if( get("task") == id || get("task2") == id ) return 1;

        send_user( who, "%c%s", '!', get_name() + "不想同你打架。" );
        return 0;
}       */

// --------------------------------------------------------------- 远程调用 ----

// 函数：接受金钱
int accept_money(object who, int gold) { return __FILE__->accept_money_callout(this_object(), who, gold); }

// 函数：接受金钱(在线更新)
int accept_money_callout(object me, object who, int gold)
{
        object item;
        string file;
        int z, x, y, p;

        if (who->is_user() && me->get("task") == who->get_number())
        {
                if (!me->get("gold"))
                        me->set("gold", random(30) + 1);

                if (me->get("gold") == gold) // 数量正确
                {
                        if (random(1000) < 5 && load_object(file = BOOK_FILE->get_book_file())) // 1% // 进阶秘籍
                        {
                                item = new (file);
                                if (p = item->move(who, -1))
                                {
                                        item->add_to_user(p);
                                        write_user(who, ECHO "%sCho bạn%s。", me->get_name(), item->get_name());
                                        send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n    %s có vẻ là một bộ xương kỳ lạ, phải là một vật liệu tốt để luyện võ, cuốn sách cũ này là vô dụng, xin vui lòng gửi cho bạn.", me->get_name(), NPC_RANK_D->get_respect_2(who)));
                                }
                                else
                                        destruct(item);
                        }
                }
                else // 数量错误
                {
                        if ((z = get_z(who)) && (p = get_xy_point(z, IS_CHAR_BLOCK)))
                        {
                                who->add_to_scene(z, p / 1000, p % 1000, get_d(who));
                                write_user(who, ECHO "%s tức giận, đá bạn ra ngoài.", me->get_name());
                        }
                }

                call_out("destruct_npc_callout", 3, me, who); // 清除蒙面人

                return 1;
        }
        return 0;
}

// 函数：删除自己(在线更新)
void destruct_npc_callout(object me, object who)
{
        if (!me)
                return;
        me->win_bonus(who); // 清除蒙面人
        me->remove_from_scene();
        destruct(me);
}

// 函数：可以接受战斗
int can_be_fighted(object who) { return __FILE__->can_be_fighted_callout(this_object(), who); }

// 函数：可以接受战斗(在线更新)
int can_be_fighted_callout(object me, object who)
{
        int i;
        if (who->is_user() && me->get("task") == who->get_number())
        {
                if (!me->get("gold"))
                        me->set("gold", random(30) + 1);
                send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s：\n   HMM … Cái này … Người tốt bụng này, xin hãy thương xót tôi, xin hãy cho tôi %d king. Nếu không tôi sẽ chết và không để anh đi.\n" ESC "Bố thí %d 'Ngân Lượng\ngive %x# 0#0 0#0 0#0 0#0 0#0 0#0 $%d\n" ESC "Hủy Bỏ", me->get_name(), i = me->get("gold"), i, getoid(me), i));
        }
        return 0;
}

// 函数：攻击处理(心跳之中调用)
void heart_beat_attack() {} // 禁止战斗

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who) // 玩家死亡调用
{
        object owner, item;

        if (objectp(owner = find_player(sprintf("%d", me->get("task")))) && objectp(item = present("Vật Phẩm Quý Bấu", owner, 1, MAX_CARRY)))
                item->set_heart_3min(); // 下个３分钟
}
