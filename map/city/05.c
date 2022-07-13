
#include <city.h>
#include <effect.h>

#define SAVE_FILE "data/city/05" SAVE_EXTENSION

inherit "/inh/std/city";

void init_city();
void load_zhou();
// 函数：获取地图标识
int get_map_id() { return 50; }

// 函数：获取城市名称
string get_name() { return "Tần Quốc"; }

// 函数：构造处理
void create()
{
        object me, *char, npc;
        mapping org;
        string *name;
        int x, y, i, size, p;
        int time;

        me = this_object();

        init_city();
        restore_object(SAVE_FILE);

        char = get("manager");
        if (!arrayp(char))
                char = ({});
        else
                char -= ({0});

        time = range_value((3600 - time() % 3600) / 60, 1, MAX_NUMBER); // 3600, 3600 - time() % 3600

        if (mapp(org = get_save_2("org")))
        {
                name = keys(org);
                for (i = 0, size = sizeof(name); i < size; i++)
                        if (sscanf(org[name[i]], "%d,%d", x, y) == 2)
                        {
                                npc = new (MANAGER);
                                npc->set_city_name(get_name());
                                npc->set_org_name(name[i]);
                                npc->restore();
                                npc->set_name(sprintf(" %s Tổng Quản", name[i]));
                                npc->check_skill();
                                char += ({npc});
                                CITY_ZHOU->set_2(sprintf("org.%s", name[i]), npc);

                                set_effect(npc, EFFECT_ITEM_ORG, time);
                        }
                set("manager", char);
        }

        set_effect(me, EFFECT_ITEM_CITY, time);

        set_heart_timer(me, set_heart_timer_2(me, 0));
        set_heart_loop(me, 600); // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：获取合法坐标
int get_xy_point(int flag) { return 050 * 1000000 + efun::get_xy_point(050, flag); }

// 函数：城市初始化
void init_city()
{
        set_level(2);
        set_defence(4000);
        set_armor(25000);
        set_soldier(50000);
        set_training(80);
        set_cash(500000);
        set_money(0);
        set_food(400000);
        set_tax(1000000);
        set_stability(8000);
        // set_disease();
        set_agriculture(30000);
        set_fishculture(3000);
        set_mining(25000);
        set_industry(20000);
        set_commercial(15000);
        set_arts(25000);
        set_education(25000);
        set_religion(18000);

        /*      set_master("");
        set_master_2("");
        set_master_3("");
        set_master_name("－－");
        set_master_name_2("－－");
        set_master_name_3("－－");
*/
        set_buy_tax(1);
        set_sell_tax(1);
        set_buy_tax_2(1);
        set_sell_tax_2(1);
        set_tax_2_cash(40);

        init_friend_dbase();
        init_relation_dbase();
}
void load_zhou()
{
        object *char, npc;
        mapping org;
        string *name;
        int x, y, i, size, p, time;
        restore_object(SAVE_FILE);
        char = get("manager");
        if (!arrayp(char))
                char = ({});
        else
                char -= ({0});
        if (mapp(org = get_save_2("org")))
        {

                name = keys(org);
                for (i = 0, size = sizeof(name); i < size; i++)
                {
                        ///printf(CITY_ZHOU->get_2(sprintf("org.%s", name[i])));
                        //   printf(name[i]);
                        if (!CITY_ZHOU->get_2(sprintf("org.%s", name[i])))
                        {
                                if (sscanf(org[name[i]], "%d,%d", x, y) == 2)
                                {
                                        npc = new (MANAGER);
                                        npc->set_city_name(get_name());
                                        npc->set_org_name(name[i]);

                                        npc->restore();
                                        npc->set_name(sprintf(" %s Tổng Quản", name[i]));
                                        npc->check_skill();
                                        char += ({npc});
                                        CITY_ZHOU->set_2(sprintf("org.%s", name[i]), npc); // 要同 /cmd/user/org 同步

                                        set_effect(npc, EFFECT_ITEM_ORG, time);
                                }
                        }
                }
                set("manager", char);
        }
}
// 函数：取存盘文件名
string get_save_file() { return SAVE_FILE; }
