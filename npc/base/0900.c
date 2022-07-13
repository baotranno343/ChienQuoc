
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>
#include <chia_kenh.h>
inherit OFFICER;

void do_goto(string arg);
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5205; }

// 函数：构造处理
void create()
{
        set_name("Cự Thú Đảo Xa Phu");
        set_city_name("Chu Quốc");

        set_2("talk", (["welcome":(
                                      : do_welcome:),
        ]));
        setup();
}

// 函数：对话处理
void do_look(object who)
{
        object me = this_object();
        send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n Nghe nói ở Bờ Đông Hải xa xôi, có một ngư dân ra biển đánh cá, phát hiện ra một lục địa thần kỳ, có nhiều bí mật ít người biết đến! Ngươi muốn đến đó thám hiểm không?\n" ESC "Đến thám hiểm Cự Thú Đảo\ntalk %x# welcome.23\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
}

void do_welcome(string arg)
{
        object me = this_object();
        __FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
        int flag, p;
        object who, item;
        string result;

        who = this_player();
        flag = to_int(arg);
        if (MAIN_D->get_kenh() != KENH_CUTHUDAO && KENH_CUTHUDAO != 0)
        {
                send_user(who, "%c%s", '!', "Nếu muốn vào cự thú đảo, hãy quay về Kênh Cự Thú Đảo hoặc Kênh Event");
                return;
        }
        if (!who->get("checkpointsuccess"))
        {
                "/cmd/user/checkpoint"->main(who);
                return;
        }
        who->set_time("talk", 0);
        switch (flag)
        {
        case 23:
                p = 166148;
                send_user(who, "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");
                who->set_2("travel.z", 549);
                who->set_2("travel.p", p);
                who->set_2("travel.money", 0);
                set_effect(who, EFFECT_TRAVEL, 3);
                who->delete ("checkpointsuccess");
                break;
        }
}
