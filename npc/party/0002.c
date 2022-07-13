#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;

int iTimes;
// 函数：获取人物造型
int get_char_picid() { return 7301; }
void do_bonus(string arg);
void do_setup(string arg);
int add_times(int i) { return iTimes+=i; }
void generate_daughter(object who);

void init()
{
	iTimes = 0;
}
// 函数：构造处理
void create()
{
        set_name("夏妈妈");
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
                 "setit"	 : (: do_setup :),
        ]) );

        setup();
}

void do_look( object who ) { __FILE__->do_look_call(who,this_object());}

void do_look_call(object who, object npc)
{
	string id;
	object obj;
	
	if ( stringp(id=who->get_save_2("xiamama")) && objectp(obj=find_char(id)) && obj->is_daughter() )
	{
		send_user(who,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s\n    谢谢你把我的女儿带回来，我一定会重重奖励你的。\n"ESC"领取奖励\ntalk %x# bonus.1\n"ESC"离开",npc->get_name(),getoid(npc)));
		return ;
	}
	if( is_gm(who) || is_god(who) ) 
	{
		send_user(who,"%c%c%w%s", ':', 3 ,npc->get_char_picid(),sprintf("%s:\n    你想干什么?\n"ESC"开始新一轮活动\ntalk %x# setit.1\n"ESC"离开",npc->get_name(),getoid(npc),getoid(npc)));
	}

}

void do_bonus(string arg) { __FILE__->do_bonus_call(this_player(),this_object(),arg);}

void do_bonus_call(object who,object npc,string arg)
{
	int i=to_int(arg),r,p;
	string id,file;
	object obj,item;
	if ( i == 1 )
	{
		if ( !stringp(id = who->get_save_2("xiamama")) || !objectp(obj=find_char(id)) || !obj->is_daughter())	//没有领取
			return ;
		if ( !inside_screen_2(obj,who) || !inside_screen_2(npc,who))
			return ;
		iTimes=npc->add_times(1);
		if ( iTimes == 1 )
		{
			file = BOOK_FILE->get_book_file();
		}
		else if ( iTimes == 2 )
		{
			file = "/item/std/0088";
		}
		else if ( iTimes == 3 )
		{
			file = "/item/91/9150";
		}
		else
		{
			obj->remove_from_scene();
			destruct(obj);
			who->delete_save_2("xiamama");
			who->add_cash(100000);
			send_user(who,"%c%s",';',"你得到10万金的奖励");
			CHAT_D->sys_channel(0,who->get_name()+"玩家在“妈妈的嘱托”活动中获得十万金的奖励");
			log_file("mama_bonus.txt",sprintf("%s,%d %s c %d\n",short_time(),who->get_number(),who->get_name(),iTimes));
			return ;	
		}			
		if ( stringp(file) && load_object(file) )
		{
			item = new(file);
			if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
			{
				obj->remove_from_scene();
				destruct(obj);
				who->delete_save_2("xiamama");				
				send_user(who,"%c%s",';',sprintf("你得到 %s 的奖励", item->get_name()));
				CHAT_D->sys_channel(0,who->get_name()+sprintf("玩家在“妈妈的嘱托”活动中获得 %s 的奖励", item->get_name()));
				r =item->move(who, -1);
				item->add_to_user(r);
				log_file("mama_bonus.txt",sprintf("%s,%d %s b %d\n",short_time(),who->get_number(),who->get_name(),iTimes));
			}
			else
			{
				npc->add_times(-1);
	                        destruct(item);	
	                        return ;
			}
		}
	}
}

void do_setup(string arg) { __FILE__->do_setup_call(this_player(),this_object(),arg);}

void do_setup_call(object who, object npc,string arg)
{
	int i,j,size;
	i = to_int(arg);
	if ( is_player(who) )
		return ;
	if ( i == 1 )
	{
		npc->init();
		generate_daughter(who);
	}
}

void generate_daughter(object who)
{
	int p,i,j,x,y,z;
	object npc;
	
	for(j=0;j<100;j++)
	{
		if( p = XY_D->get_seller_point( IS_CHAR_BLOCK ) )
		{
			npc = new("/npc/party/0003");	
			if ( !objectp(npc) )
				continue;
			z=p/1000000;x=p%1000000/1000;y=p%1000000%1000;
			npc->add_to_scene(z, x, y, 3);
			i++;
tell_user(who,"%d %d,%d",z,x,y); 
		}	
		if ( i >= 30 )
			break;		
	}

}