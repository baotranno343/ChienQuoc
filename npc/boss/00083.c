
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <effect.h>
#include <skill.h>

#define FILE_GUMU "sys/party/gumu"
#define DEBUG(who, arg) ; //tell_user(who,arg);
inherit BADMAN;

//
int is_shiyong()
{
        return 1;
}

// 函数：获取人物造型
int get_char_picid() { return 1261; }
void drop_items(object who);

int set_fight_status(int level)
{
        add_max_hp(get_max_hp() * 100 / 10);
        add_ap(get_ap() * 25 / 10);
}

// 函数：构造处理
void create()
{
        object me = this_object();
        set_name("Thủ Mộ Thạch Dũng");
        set("shiyong", 1);
        set_max_seek(4);
        set("anti_05311", 1); //设置不能被05311迷惑
        set_effect(me, EFFECT_CHAR_BUSY, 15);
        call_out("do_fight", 15);
        setup();
        set_char_type(FIGHTER_TYPE); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action(object who) { return 0; } // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
// void check_legend_task( object who ) { USER_TASK_D->kill_legend_npc( who, this_object() ); }

// 函数：掉宝奖励
//void win_bonus(object me,object who)
//{
//	int i,exp,exp1,exp2,size;
//	int level1,level2;
//	object *team=({});
//	level1=me->get_level();
//	if(who->is_npc()) return;
//	team=who->get_team();
//	if(!team) team+=({who});
//	exp = NPC_ENERGY_D->get_exp_bonus(level1);
//	exp1=exp*3;
//	for(i=0,size=sizeof(team);i<size;i++)
//	{
//		team[i]->add_exp(exp1);
//	}
//}

//15秒后复活，开始战斗
void do_fight()
{
        object me = this_object();
        set_effect(me, EFFECT_CHAR_BUSY, 0);
        me->add_to_scene(get_z(me), get_x(me), get_y(me));
}

void drop_items(object who)
{
        object me = this_object();
        FILE_GUMU->npc_die(who, me);
        __FILE__->drop_items_callout(this_object(), who);
}

// 函数：掉宝奖励(在线更新)
void drop_items_callout(object me, object who)
{
        object item, leader;
        string file, owner, id;
        int p, rate, i, j, size, gold, equip, total, total2;
        int z, x, y;

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);
        id = who->get_leader();
        if (!id)
                owner = who->get_id();
        else
        {
                if (leader = find_player(id))
                {
                        owner = leader->get_id();
                }
                else
                        owner = who->get_id();
        }

        p = random(100);
        size = (p > 2) ? 1 : (p > 0) ? 2
                                     : 2;
        total = 2;
        total2 = 3;

        rate = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;

        for (i = 0; i < size; i++)
        {
                p = random(10000);
                //tell_user(this_player(),"drop_items_callout p=%d",p);
                if (p < 3500 * rate / 100)
                        ;
                else if (p < 4500 * rate / 100) // 金钱  %10
                {
                        if (gold >= total)
                                continue;
                        if (p = get_valid_xy(z, x + random(3), y + random(3), IS_ITEM_BLOCK))
                        {
                                item = new ("/item/std/0001");
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->set_value(500);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                                gold++;
                        }
                }

                else if (p < 4600 * rate / 100) // 欧治宝石 %1
                {
                        switch (random(1))
                        {
                                //case 0 : file = "/item/08/0014";  break;
                        case 0:
                                file = "/item/08/0016";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 5100 * rate / 100) // 藏宝图 %5
                {
                        switch (random(1))
                        {
                        case 0:
                                file = "item/std/8000";
                                break;
                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 5700 * rate / 100) // 紫参丹 %2
                {
                        switch (random(1))
                        {
                        case 0:
                                file = "/item/91/9167";
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
                else if (p < 10000 * rate / 100) // 杂物４//师门物品 %50
                {
                        switch (random(1))
                        {
                        case 0:
                                file = "/item/40/40" + sprintf("%d", 11 + random(72));
                                break;

                        default:
                                break;
                        }
                        if (load_object(file) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                        {
                                item = new (file);
                                TEAM_D->drop_item(item, who);
                                item->set_user_id(owner);
                                item->add_to_scene(z, p / 1000, p % 1000);
                                item->set("winner", who);
                                item->set("time", time());
                        }
                }
        }
}
