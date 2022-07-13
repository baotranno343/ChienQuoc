#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <public.h>
#include <cmd.h>

inherit OFFICER;

int iTimes;
int *nPlayer = ({});
int *nDaughter = ({});
// 函数：获取人物造型
//int get_char_picid() { return 7302; }
void do_welcome(string arg);
//是女儿
int is_daughter() { return 1;}
// 函数：构造处理
void create()
{
	object me = this_object();
        set_name("夏妈妈的女儿");
	NPC_EQUIP_D->init_figure( this_object(), RICH_LADY, FEMALE, 20 );
 	set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
        set( "birthday", time() );
        if( !clonep(me) ) return;
        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 10);    // 循环心跳：１秒钟
        me->heart_beat();
        set_heart_beat(1);
}

void do_look( object who ) { __FILE__->do_look_call(who,this_object());}

void do_look_call(object who, object npc)
{
	string id;
	object obj;
	
	if ( stringp(id = npc->get("xiamama")) )	//已经有人领取
		return ;
	if ( stringp(id = who->get_save_2("xiamama")) && objectp(obj=find_char(id))&&obj->is_daughter())	//已经领取
		return ;		
	send_user(who,"%c%c%w%s",':',3 ,npc->get_char_picid(),sprintf("%s:\n    我迷路了，快送我回家，我妈妈会给你意想不到的奖励的哟。\n"ESC"接受。\ntalk %x# welcome.1\n"ESC"抱歉！我太忙了，没时间去。",npc->get_name(),getoid(npc),getoid(npc)));
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_player(),this_object(),arg);}

void do_welcome_call(object who, object npc, string arg)
{
	string id;
	int i = to_int(arg);
	object obj;
	
	if ( i == 1 )
	{
		if ( stringp(id = npc->get("xiamama")) )
		{
			send_user(who,"%c%c%w%s",':',3 ,npc->get_char_picid(),npc->get_name()+":\n    抱歉，我不能跟你走。");
			return ;
		}
		if ( stringp(id = who->get_save_2("xiamama")) && objectp(obj=find_char(id))&&obj->is_daughter())	//已经领取
		{
			send_user(who,"%c%c%w%s",':',3 ,npc->get_char_picid(),npc->get_name()+":\n    抱歉，我不能跟你走。");
			return ;
		}
//		npc->set( "birthday", time() );
		who->set_save_2("xiamama",sprintf("%x#",getoid(npc)));
		npc->set("xiamama",sprintf("%d",who->get_number()));      
		send_user(who,"%c%c%w%s",':',3 ,npc->get_char_picid(),npc->get_name()+":\n    等等我，我跟你去找妈妈。");
	}			
	
}
// 函数：心跳处理
void heart_beat() { }
// 函数：允许走路
int is_moveable() { return 1; }    // 能使用 go 命令
// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１秒处理
{
        object owner;
        int z, x, y, p;
        string id;
        if( stringp(id=me->get("xiamama"))&&objectp( owner = find_player(id) ) )
        {
                if( distance_between(me, owner) > 1 && inside_screen_2(me, owner) )    // 跟随：每秒３步
                {
                        z = get_z(owner);  x = get_x(owner);  y = get_y(owner);
                        if( p = get_valid_path( z, get_x(me), get_y(me), x, y ) )
                                GO_CMD->main_npc( me, sprintf("%d", p) );
                        else    GO_CMD->main_npc( me, sprintf("%d", random(8) + 1) );    // 随机走路
                }
                else    GO_CMD->main_npc( me, sprintf("%d", random(8) + 1) );    // 随机走路
        }
        if ( gone_time(me->get("birthday")) > 3600 )	//60分钟后消失
        {
		me->remove_from_scene();
		destruct(me);        	
        }

}