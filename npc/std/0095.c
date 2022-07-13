
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <city.h>
#include <effect.h>

#define CITY_MANAGER_D "/sys/city/manager"
#define CITY_MANAGER_2_D "/sys/city/manager2"
#define CITY_MANAGER_3_D "/sys/city/manager3"
#define CITY_MANAGER_4_D "/sys/city/manager4"
#define CITY_MANAGER_5_D "/sys/city/manager5"

inherit OFFICER;
inherit SAVE_F;
inherit "/inh/npc/manager";
inherit "/inh/npc/manager2";
inherit "/inh/npc/manager3";

// 函数：帮派功能人物
int is_org_officer() { return 1; }

// 函数：取存盘文件名
string get_save_file()
{
        string name = get_org_name();

        if (!name || name == "")
                name = "XXXX";

        switch (get_city_name())
        {
        case "Tề Quốc":
                return sprintf("data/org-1/%s%s", name, SAVE_EXTENSION);
        case "Hàn Quốc":
                return sprintf("data/org-2/%s%s", name, SAVE_EXTENSION);
        case "Triệu Quốc":
                return sprintf("data/org-3/%s%s", name, SAVE_EXTENSION);
        case "Ngụy Quốc":
                return sprintf("data/org-4/%s%s", name, SAVE_EXTENSION);
        case "Tần Quốc":
                return sprintf("data/org-5/%s%s", name, SAVE_EXTENSION);
        case "Sở Quốc":
                return sprintf("data/org-6/%s%s", name, SAVE_EXTENSION);
        case "Yên Quốc":
                return sprintf("data/org-7/%s%s", name, SAVE_EXTENSION);
        default:
                return sprintf("data/org-8/%s%s", name, SAVE_EXTENSION);
        }
}

void do_info(string arg);
void do_appoint(string arg);
void do_demise(string arg);
void do_banish(string arg);
void do_exit(string arg);
void do_savings(string arg);

void do_join(string arg);
void do_apply(string arg);
void do_accept(string arg);
void do_refuse(string arg);

void do_skill(string arg);
void do_research(string arg);

void do_note(string arg);

void do_war(string arg);
void do_org(string arg);

void do_upgrade(string arg);

void do_abandon(string arg);

// 函数：获取人物造型
int get_char_picid() { return 9955; }

// 函数：构造处理
void create()
{
        object me = this_object();
        int time;

        set_name("Tổng Quản");

        set_2("talk", (["info":(
                                   : do_info:),
                           "appoint":(
                                         : do_appoint:),
                            "demise":(
                                         : do_demise:),
                            "banish":(
                                         : do_banish:),
                              "exit":(
                                         : do_exit:),
                           "savings":(
                                         : do_savings:),

                              "join":(
                                         : do_join:),
                             "apply":(
                                         : do_apply:),
                            "accept":(
                                         : do_accept:),
                            "refuse":(
                                         : do_refuse:),

                             "skill":(
                                         : do_skill:),
                          "research":(
                                         : do_research:),

                              "note":(
                                         : do_note:),

                               "war":(
                                         : do_war:),
                               "org":(
                                         : do_org:),
                           "abandon":(
                                         : do_abandon:),
                           "upgrade":(
                                         : do_upgrade:),
        ]));

        setup();

        if (!clonep(me))
                return;
        /*
        time = ( 3600 - time() % 3600 ) / 60;    // 3600, 3600 - time() % 3600
        set_effect( me, EFFECT_ITEM_ORG, range_value(time, 1, MAX_NUMBER) );

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 600);    // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
*/
}

// 函数：心跳处理
void heart_beat() {}

private
static int HeartSec = 0; // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec(int point) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec(int point) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１分处理
{
        ITEM_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); // 征状处理
}

// 函数：增加技能火候
void improve_skill(int skill, int degree)
{

        return USER_SKILL_D->improve_skill_0095(this_object(), skill, degree);
}

void do_look(object who) { CITY_MANAGER_D->do_look(who, this_object()); }

void do_info(string arg) { CITY_MANAGER_D->do_info(this_player(), this_object(), arg); }
void do_appoint(string arg) { CITY_MANAGER_D->do_appoint(this_player(), this_object(), arg); }
void do_demise(string arg) { CITY_MANAGER_D->do_demise(this_player(), this_object(), arg); }
void do_banish(string arg) { CITY_MANAGER_D->do_banish(this_player(), this_object(), arg); }
void do_exit(string arg) { CITY_MANAGER_D->do_exit(this_player(), this_object(), arg); }
void do_savings(string arg) { CITY_MANAGER_D->do_savings(this_player(), this_object(), arg); }

void do_join(string arg) { CITY_MANAGER_2_D->do_join(this_player(), this_object(), arg); }
void do_apply(string arg) { CITY_MANAGER_2_D->do_apply(this_player(), this_object(), arg); }
void do_accept(string arg) { CITY_MANAGER_2_D->do_accept(this_player(), this_object(), arg); }
void do_refuse(string arg) { CITY_MANAGER_2_D->do_refuse(this_player(), this_object(), arg); }

void do_skill(string arg) { CITY_MANAGER_3_D->do_skill(this_player(), this_object(), arg); }
void do_research(string arg) { CITY_MANAGER_3_D->do_research(this_player(), this_object(), arg); }
void do_abandon(string arg) { CITY_MANAGER_3_D->do_abandon(this_player(), this_object(), arg); }

void do_note(string arg) { CITY_MANAGER_4_D->do_note(this_player(), this_object(), arg); }

void do_war(string arg) { CITY_MANAGER_5_D->do_war(this_player(), this_object(), arg); }
void do_org(string arg) { CITY_MANAGER_5_D->do_org(this_player(), this_object(), arg); }

void do_upgrade(string arg) { "/sys/sys/manager"->do_upgrade(this_player(), this_object(), arg); }

void check_skill()
{
        object me = this_object();
        int i, size;
        int *allskill = ({
            104,
            109,
            401,
            404,
            405,
            111,
            121,
            131,
            141,
            151,
            161,
            202,
            402,
            403,
            620,
            630,
            640,
            660,
            650,
        });
        size = sizeof(allskill);
        for (i = 0; i < size; i++)
        {
                if (!me->get_skill(allskill[i]))
                        me->set_skill(allskill[i], 1);
        }
        if (me->get_strong(6) == 0)
                me->set_strong(6);
        // 修改当前研究技能至新的变量存储
        if (me->get_research())
        {
                me->set_researchs(me->get_research(), me->get_research_level());
                me->set_research(0);
                me->set_research_level(0);
        }
}