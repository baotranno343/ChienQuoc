
/*
 * 用户断线重连模块
 */

#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

#define LOGIN_LOG "loginfo.txt" // 连线记录日志

// 函数:生成二进制码
void SAVE_BINARY() {}

string get_name() { return "Sợi nối Yêu ma"; }

// 函数:重新进入游戏
void reconnect(object me, object body)
{
        object *inv, mailbox, map, npc, *nPet;
        string id;
        int z, x, y, i, size;

        exec(body, me);
        db_user_clear(me, me->get_id());
        destruct(me);

        me = body;
        me->reconnect();
        USER_D->add_user(me);
        "/sys/sys/id"->add_reconnect_count(1);

        tell_user(me, "Bạn đang %s từ kết nối %s \n", short_time(), get_ip_name(me));

        switch (me->get_attack_mode())
        {
        case 0:
                write_user(me, "Hình thức tấn công: Tự Do");
                break;
                //   case 2 : write_user(me, "Hình thức tấn công: Theo Nhóm" );  break;
        case 3:
                write_user(me, "Hình thức tấn công: Quốc Gia");
                break;
        case 2:
                write_user(me, "Hình thức tấn công: Bang Phái");
                break;
        default:
                write_user(me, "Hình thức tấn công: Hoà Bình");
                break;
        }

        // 身上物品初始化（显示）
        me->set("phpbalance", 0);
        inv = me->get_all_equip();
        me->set_login_flag(2);
        for (i = 0; i < MAX_EQUIP; i++)
                if (objectp(inv[i]))
                        inv[i]->add_to_user(get_d(inv[i]));

        inv = all_inventory(me, 0, 0);
        for (i = 0, size = sizeof(inv); i < size; i++)
                inv[i]->add_to_user(get_d(inv[i]));
        me->disable_logon_cmds();

        // 初始化连线对象数据

        me->init_store_dbase(); // 断线重连，取消摆摊
        me->open_store(0);

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        if (map = get_map_object(z)) // 补 add_to_scene 换场景
                send_user(me, "%c%w%w%w%s", 0x3c, map->get_client_id(), x, y, map->get_name());
        else
                send_user(me, "%c%w%w%w%s", 0x3c, z, x, y, "Bản đồ vô danh");
        me->send_legend();
        me->add_to_scene(z, x, y, get_d(me));
        if (map && map->get_real_z())
                send_user(me, "%c%w", 0x1f, map->get_real_z());
        CONNECT_D->init_user(me);

        inv = me->get_team();
        for (i = 0, size = sizeof(inv); i < size; i++)
                if (inv[i])
                {
                        send_user(me, "%c%c%d%d%c%s", 0x54, inv[i]->is_leader() ? 1 : 2, inv[i]->get_number(), inv[i]->get_armor_code(), inv[i]->get_level(), inv[i]->get_name());
                        //                send_user( me, "%c%c%d%s", 0x54, inv[i]->is_leader() ? 1 : 2, inv[i]->get_number(), inv[i]->get_name() );
                        if (me->get_number() != inv[i]->get_number())
                                send_user(me, "%c%c%d%w%w", 0x54, 10, inv[i]->get_number(), get_x(inv[i]), get_y(inv[i]));
                }
        if (npc = me->get("soldier"))
        {
                send_user(me, "%c%c%d%s", 0x2c, 1, getoid(npc), npc->get_name());
                send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(npc), 1, 2, 3);
                send_user(me, "%c%c%d%c", 0x2c, 3, getoid(npc), npc->get_hp() * 50 / npc->get_max_hp());
                send_user(me, "%c%c%d%c", 0x2c, 4, getoid(npc), npc->get_mp() * 50 / (npc->get_max_mp() + 1));
                send_user(me, "%c%c%d%c", 0x2c, 5, getoid(npc), 2);
                send_user(me, "%c%c%d%c", 0x2c, 6, getoid(npc), npc->get_action());
                send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(npc), get_x(npc), get_y(npc));
                send_user(me, "%c%c%d%d", 0x2c, 8, getoid(npc), npc->get_char_picid());
        }
        if (arrayp(inv = me->get("zombie")) && (size = sizeof(inv)))
        {
                for (i = 0; i < size; i++)
                        if (npc = inv[i])
                        {
                                send_user(me, "%c%c%d%s", 0x2c, 1, getoid(npc), npc->get_name());
                                send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(npc), 1, 2, 3);
                                send_user(me, "%c%c%d%c", 0x2c, 3, getoid(npc), npc->get_hp() * 50 / npc->get_max_hp());
                                send_user(me, "%c%c%d%c", 0x2c, 4, getoid(npc), npc->get_mp() * 50 / (npc->get_max_mp() + 1));
                                send_user(me, "%c%c%d%c", 0x2c, 5, getoid(npc), 2);
                                send_user(me, "%c%c%d%c", 0x2c, 6, getoid(npc), npc->get_action());
                                send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(inv[i]), get_x(inv[i]), get_y(inv[i]));
                                send_user(me, "%c%c%d%d", 0x2c, 8, getoid(inv[i]), inv[i]->get_char_picid());
                        }
        }
        "sys/party/mingren"->check_mingren_upline(me);
        USER_D->gm_channel(sprintf(HIR "%s : %s (%d) do %s nối vào",
                                   get_name(), me->get_name(), me->get_number(), get_ip_name(me)));
        log_file(LOGIN_LOG, sprintf("%s %s %d %s %s - - Kết nối lại nhập\n", me->get_id(), me->get_name(), me->get_number(), get_ip_name(me), short_time()));
        me->send_to_friend(1);
        me->receive_friends();

        mailbox = new (MAILBOX);
        mailbox->set_owner(me->get_id());
        if (mailbox->check_mails())
                send_user(me, "%c", 0x4d);
        destruct(mailbox);

        me->login_timeout(); // 清除限时进程

        send_user(me, "%c%c%d", 0x49, 10, get_heart_timer(me));
        me->set_2("go_count.time2", get_heart_timer(me));

        // 断线重连，准备就绪

        me->set_login_flag(3);
        //      me->set_char_type(PLAYER_TYPE_2);
        me->add_pk(0); // 显示ＰＫ状态
        if (!get_effect(me, EFFECT_CHAR_INVISIBLE))
                set_invisible(me, 0); // 没有隐身时

        if (me->get_quest("escort.flag") == 1               // 运镖任务(物品)
            && stringp(id = me->get_quest("escort.robber")) // 寻找蒙面人
            && objectp(npc = find_char(id)) && npc->is_escort_robber() && present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
        {
                npc->start_fight(me);
                me->set_quest("escort.robber#", npc);
                send_user(me, "%c%s", '!', "Kẻ lạ xuất hiện, hành động bị ảnh hưởng.");
        }

        me->process_input(""); // 重设命令时钟(用于断线僵尸)
        me->set("tasklist", 0);
        CHAR_CHAR_D->send_loop_perform(me, me);   // 显示持续效果
        CHAR_CHAR_D->send_loop_perform_2(me, me); // 显示持续图标

        //宠物显示
        nPet = me->get_all_beast();
        for (i = 0, size = sizeof(nPet); i < size; i++)
                nPet[i]->send_info();
        npc = me->get("showbeast");
        if (npc)
                USER_BEAST_D->show_beast_client(me, npc);
        me->add_title("X");
        me->send_title_list();

        if (me->get_vip())
                "item/sell/0061"->vip_effect(me);
        send_user(me, "%c%c%c", 0xA2, 10, me->get_save_2("online_rank.level")); //修为等级
        WUSHUANG->check_org_title(me);                                          //检查无双称谓
}
