#include <npc.h>
#include <ansi.h>
#include <shouxi.h>

inherit OFFICER;
private
string RealName; // 实名
void do_welcome(string arg);

int get_id_color() { return 0xf0db3e; }
int is_seller() { return 6006; }
int is_self_look() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return get("PicId"); }
void join_elect();
void do_vote(string arg);
void get_hornor(string arg);
void do_exchange(string arg);
void do_fight();
void do_list();
void do_info(string arg);

// 函数：构造处理
void create()
{
        set_name("Đại Đệ Tử cao quí");

        set_2("talk", (["elect":(
                                    : join_elect:),
                              "vote":(
                                         : do_vote:),
                            "hornor":(
                                         : get_hornor:),
                          "exchange":(
                                         : do_exchange:),
                             "fight":(
                                         : do_fight:),
                              "list":(
                                         : do_list:),
                              "info":(
                                         : do_info:),
        ]));

        setup();
}

// 函数：对话处理
void do_look(object who)
{
        SHOUXI->do_look(this_object(), who);
}
// 函数：获取人物名称
string get_real_name() { return RealName; }

// 函数：设置人物名称
string set_real_name(string name)
{
        return RealName = name;
}
// 函数：获取人物名称
string get_short()
{
        if (stringp(get_real_name()))
                return get_real_name() + "||||" + get_name();
        else
                return get_name();
}

void join_elect() { SHOUXI->join_elect(this_object(), this_player()); }
void do_vote(string arg) { SHOUXI->do_vote(this_object(), this_player(), arg); }
void get_hornor(string arg) { SHOUXI->get_hornor(this_object(), this_player(), arg); }
void do_exchange(string arg) { SHOUXI->do_exchange(this_object(), this_player(), arg); }
void do_fight() { SHOUXI->do_fight(this_object(), this_player()); }
void do_list() { SHOUXI->do_list(this_object(), this_player()); }
void do_info(string arg) { SHOUXI->do_info(this_object(), this_player(), arg); }