#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>
#include <city.h>
#include <task.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2523; }
void do_visit(string arg);
void outlet(int sec,object map);

// 函数：构造处理
void create()
{
	object me=this_object();
        set_name("Linh Dược");
        set_2( "talk", ([
                 "visit"         : (: do_visit :),
        ]) );
        setup();
        set( "birthday", time() );
}

// 函数：复位处理
void reset()
{
	__FILE__->reset2(this_object());
}

// 函数：复位处理
void reset2(object me) 
{
        string member ;
        int number,i;
        object owner;
        if( gone_time( me->get("birthday") ) >= 1200 )    // 20 分钟
        {
		for (i=0;i<2;i++)
		{
	        	number = me->get(sprintf("user%d",i));
	                owner = find_any_char(sprintf("%d", number));
	                if (owner) 
			{
			       	owner->delete_save_2("qixi.flag");
//				owner->delete_save_2("qixi.receive");
			        send_user( owner, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_QIXI,9,0,"" );
				send_user( owner, "%c%c%c%w%w%s", 0x51, 1, 2,TID_QIXI,9,"" ); 
				send_user( owner, "%c%c%c%w%s", 0x51, 1, 1,TID_QIXI,"" ); 
				MAILBOX->sys_mail(owner->get_id(),owner->get_number(),HIY"超出时限，七夕天赐奇缘任务失败。你可以放弃任务后，到"HIR"牛郎织女"HIY"处重新开始。");
			}
		}
                me->remove_from_scene();
                destruct( me );
        }
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	int i,id,tId,size;
	object *team;
	string leader;
	id = getoid(me);
	tId = who->get_team_id();
	team = who->get_team();

	if(who->get_save_2("qixi.together") != me->get("bb"))
	{	
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    这是谁家的孩子跑出来乱碰东西啊，还不赶快来领回去！\n"ESC"离开" );
                return;
	}
        if( ( size = sizeof(team) ) > 2 )
        {
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    不要带些不相干的人来！\n"ESC"离开" );
                return;
        }

        if( !tId || ( size = sizeof(team) ) != 2 )
        {
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你的有缘人呢？还是赶快找到有缘人再来我这里吧！\n"ESC"离开" );
                return;
        }

	for (i=0;i<size;i++)		
	{
		if (!inside_screen_2(me, team[i]))
		{
                	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    还是等队员到齐后再说吧！\n"ESC"离开" );	
			return;
		}
	}
        if(  !who->is_leader() )
        {
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + "：\n    你们的队长呢？让队长过来。\n"ESC"离开" );
                return;
        }
        if ( team[0]->get_save_2("qixi.flag") == 9 && team[1]->get_save_2("qixi.flag") == 9 && team[0]->get_gender() != team[1]->get_gender() && team[0]->get_save_2("qixi.together") == team[1]->get_save_2("qixi.together") )
	{
	        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
	        	sprintf("%s：\n    你也想要来偷我的灵药吗？\n"
	                ESC "暂时借用一下\ntalk %x# visit.2\n"
	                ESC "离开", me->get_name(), getoid(me) ) );
	}

}
void do_visit( string arg )
{
        object me = this_object();
        __FILE__ ->do_visit2(me, arg);
}

void do_visit2( object me, string arg )
{
	int flag,i,p,z,x,y,id,size,tId,*nXy, level,count,exit;
       	object who,npc,*team,map,leader,convey;
	string *attr=({"妖","厉害","空手"});
	int *npc_xy=({5032,5029});
	int *player_xy=({2830,3030});
        who = this_player();
	tId = who->get_team_id();
        flag = to_int(arg);

        who->set_time( "talk",  0);
        id = getoid(me);
       
        switch(flag)
        {
        case 2:        	
		team = who->get_team();
		if (!tId) return;
		if (sizeof(team)!=2) return;
	        if (!who->is_leader()) return;
		for (i=0;i<sizeof(team);i++)		
		{
			if (!inside_screen_2(me, team[i])) return;
			if (team[i]->get_save_2("qixi.together") != me->get("bb")) return;
			if (team[i]->get_save_2("qixi.flag") != 9) return;
			if (team[i]->get_level()>=level) level=team[i]->get_level();
		}
		if (team[0]->get_save_2("qixi.together") != team[1]->get_save_2("qixi.together")) return;
		if( ( z = find_map_flag(1000, 2999, 0) ) > 0 )
		{
			p = 891;
			init_virtual_map(z, p);    // 生成虚拟地图
		        map = new( "/inh/std/qixi_map" );
			map->set_client_id(p);
			set_map_object( map, map->set_id(z) );

			for(i=0;i<2;i++)
			{
				npc = new("npc/party/spirit_animal");
				NPC_ENERGY_D->init_npc(npc,level,attr);
//			        NPC_ENERGY_D->init_level( npc, level );    
//				if( !( p = efun::get_xy_point( 891, IS_CHAR_BLOCK ) ) )
//					continue;
//				x = ( p % 1000000 ) / 1000;  y = p % 1000;
//				npc->add_to_scene(z,x,y);
				npc->add_to_scene(z,npc_xy[i]/100,npc_xy[i]%100);
		                npc->set( "task", team[0]->get_save_2("qixi.together") );
				count++;
			}
			map->add("scene_npc_amount",count);
			for (i=0;i<sizeof(team);i++)
			{
	//			if( !( p = efun::get_xy_point( 891, IS_CHAR_BLOCK ) ) )
	//				continue;
	//			x = ( p % 1000000 ) / 1000;  y = p % 1000;
				team[i]->add_to_scene(map->get_id(),player_xy[i]/100,player_xy[i]%100);
				send_user( team[i], "%c%s", ';', HIY"我们的队伍已进入灵药圣地。" );
			}
			map->set_owner(me);
		}
		break;
	}
}


//传出场景
void outlet(int sec,object map)
{
	int i,size,tId;
	object *member,npc;
	string id;
	sec = sec-5;
	
	member = "inh/std/qixi_map"->get_all_user( map );

	if ( sec > 0 )
	{
		for(i=0,size=sizeof(member);i<size;i++)
		{
			tell_user(member[i],"%d秒后，你将被传出活动场景",sec);
		}

		call_out("outlet",5,sec,map);
	}
	else
	{
		npc = map->get_owner();
		for(i=0,size=sizeof(member);i<size;i++)
		{
			member[i]->add_to_scene(get_z(npc),get_x(npc)+random(3),get_y(npc)+random(3));
		}

		npc->remove_from_scene();
		destruct(npc);

	}		
}

//死亡处理
void scum_die(object map,object who)
{
	object owner;
	owner = map->get_owner();
	who->add_to_scene(get_z(owner), get_x(owner)+random(3), get_y(owner)+random(3), 3);
        send_user(who,"%c%s",'!',"你被守护灵兽打败了");
}