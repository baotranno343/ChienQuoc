
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <ansi.h>
#include <task.h>
inherit BADMAN;

// 函数：获取人物造型
int get_char_picid() { return 0701; }

// 函数：构造处理
void create()
{
        set_name("守护灵兽");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

        set_max_seek(4);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

int can_fight( object who ) 
{ 
	if(!get_map_object(get_z(who))->is_qixi_map())
	        return 0;
        return 1;
}

// 函数：可以接受战斗
/*int can_be_fighted( object who ) 
{ 
        object owner;

	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) return 1;

        if( get("task") == who->get_save_2("qixi.together") ) return 1;

        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),  get_name() + ":\n    你看不见我……你看不见我……" );
        return 0;
}*/

void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object item, leader,map,*member,npc1;
        string file, owner, id;
        int p, rate, i, size, gold, equip, rate1 ,tId,level,exp;
        int z, x, y;
	string *nTmp;

	tId = me->get("team_id");
	map = get_map_object(get_z(me));
	if ( !map )
		return ;
	map->add("scene_npc_amount",-1);
	//奖励经验
	member = who->get_team();
	member -= ({0});
	exp=2000;
	for(i=0,size=sizeof(member);i<size;i++)
	{
		member[i]->add_exp(exp*(member[i]->get_online_rate()/100));
	}
	if (map->get("scene_npc_amount")==0) 
	{
		for(i=0,size=sizeof(member);i<size;i++)
		{
		        send_user( member[i], "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,1,0,"" );
			send_user( member[i], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,9,"" ); 
			send_user( member[i], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
			member[i]->set_save_2("qixi.flag",10);
			send_user( member[i], "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"七夕任务" ); 
			send_user( member[i], "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,10,"七夕天赐奇缘（2）" ); 
			send_user( member[i], "%c%s", ';', HIY"杀死守护灵兽，采得灵药，赶快回去找王母娘娘吧！" );
		}
		"npc/party/spirit"->outlet(10,map);
	}

}


