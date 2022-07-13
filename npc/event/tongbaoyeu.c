#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>

inherit BADMAN;

object robber;
int get_id_color() { return 0107215; }
// 函数：获取人物造型
int get_char_picid() { return 9963; }
void do_bonus();
// 函数：构造处理
void create()
{
        set_name("Chiến Quốc Tống Bảo Tiểu Yêu");
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
        ]) );
	set_char_type(FIGHTER_TYPE_2);
	set_level(20);
	set("birthday",time());
        setup();
	set_char_type(FIGHTER_TYPE_2);

}
/*
int can_fight( object who ) 
{ 
	if ( !objectp(this_object()->get_enemy()) )
		return 0;	
	return 1;
}
*/
// 函数：死亡奖励
void win_bonus( object who ) { "sys/party/tongbaoyeu"->win_bonus_callout( this_object(), who ); }


