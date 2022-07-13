#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>
#include <city.h>
inherit OFFICER;
int host_type;
//int *nxy = ({080034,087040,094046,101051,109057,116063,074040,081046,089051,097056,105062,111067,069046,077052,085056,092061,100067,107071,064051,072056,081061,087065,096071,0102075,059055,067060,075066,082070,091076,097079,054059,063066,071071,077075,084080,089085,048066,055071,062076,068081,074086,080091,});
// 函数:获取人物造型
int get_char_picid() { return 9415; }
void do_visit(string arg);
void outlet(int sec,object map);
//int challenge(object player,object master);
// 函数:构造处理
void create()
{
	object me=this_object();
        set_name("Võ Lâm Bại Hoại");
        set_2( "talk", ([
                 "visit"         : (: do_visit :),
        ]) );
        setup();
	host_type = MAIN_D->get_host_type();
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
//	if (MAIN_D->get_host_type()==6012)
//	{
//		send_user(who, "%c%s", '!', "副本系统尚未开放！");
//		return;
//	}	
	if (me->get("overdue"))	return;
	if (!me->get("busy"))
	{
	        if( !tId || ( size = sizeof(team) ) < 1 )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    Lập tổ đội 1 người trở lên mới được khiêu chiến với ta \n"ESC"Rời khỏi" );
	                return;
	        }
	        if(  !who->is_leader() )
	        {
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    Hãy gọi đội trưởng đến đây, ngươi không đủ tư cách !\n"ESC"Rời khỏi" );
	                return;
	        }
		for (i=0;i<size;i++)		
		{
			if (!inside_screen_2(me, team[i]))
			{
	                	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    Hãy gọi tất cả thành viên trong đội tới đây rồi muốn vào thì ta cho vào \n"ESC"Rời khỏi" );				
				return;
			}
		}
		if (who->is_leader() && size>=1)
		{
			for (i=0;i<sizeof(team);i++)
			{
				team[i]->delete("wg_bb");
				team[i]->delete("c_n");
			}
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Võ Lâm Bại Hoại:\n    Các ngươi thích xen vào chuyện người khác thì đừng mong giữ được mạng ！\n"ESC"Bớt nói nhảm đi, ta oánh nè！\ntalk %x# visit.1\n"ESC"Rời khỏi",id));
		}
	}
	else
	{
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    NPC đang cùng chiến đấu với người chơi\n"ESC"Rời khỏi" );
		return;
	}


/*	else if (me->get("busy") != tId)
	{
                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    NPC đang cùng chiến đấu với người chơi\n"ESC"离开" );
		return;
	}
	else if (me->get("busy") == tId)
	{
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("武林败类:\n    尔等不要多管闲事，免得你们小命不保！\n"ESC"废话少说，看打！\ntalk %x# visit.5\n"ESC"离开",id));
	}*/
}

void do_visit( string arg )
{
        object me = this_object();
        __FILE__ ->do_visit2(me, arg);
}

void do_visit2( object me, string arg )
{
	int flag,i,p,z,x,y,id,size,tId,*nXy, level,count,exit,j=0;
       	object who,npc,*team,map,leader,convey;
        who = this_player();
	tId = who->get_team_id();
        flag = to_int(arg);

        who->set_time( "talk",  0);
        id = getoid(me);
//	if (MAIN_D->get_host_type()==6012)
//	{
//		send_user(who, "%c%s", '!', "副本系统尚未开放！");
//		return;
//	}        
        switch(flag)
        {
        case 1:        	
		team = who->get_team();
		for (i=0;i<sizeof(team);i++)
		{
			send_user(team[i],"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Võ Lâm Bại Hoại:\n   Muốn vào không ? \n"ESC"Dùng 5 Ngân Bảo gia tăng 50％ kinh nghiệm\ntalk %x# visit.3\n"ESC"Tiến vào\ntalk %x# visit.4\n",id,id));
		}
//		me->do_visit(2);
        	break;
        case 3:        	
		who->set("wg_bb",1);
		me->do_visit(4);
        	break;
        case 4:        	
		who->set("c_n",1);
		team = who->get_team();
		for (i=0;i<sizeof(team);i++)
			j=j+team[i]->get("c_n");
		if (j<sizeof(team))
//			send_user( who, "%c%s", ';', HIY"请等待其他玩家选择" );
	                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name() + ":\n    Xin đợi người chơi khác lựa chọn\n"ESC"Xác nhận" );
		if (j>=sizeof(team))
		{
			for (i=0;i<sizeof(team);i++)
				team[i]->delete("c_n");
			j=0;
			me->do_visit(2);
		}
        	break;
        case 2:        	
		team = who->get_team();
		if (me->get("overdue"))	return;
		if (!tId) return;
		if (sizeof(team)<1) return;
		if (me->get("busy")) return;
		for (i=0;i<sizeof(team);i++)		
		{
			if (!inside_screen_2(me, team[i]))
			{
				return;
			}
		}
		me->set("busy",tId);
//		for (i=0;i<sizeof(team);i++)
//		{
//			send_user(team[i],"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("武林败类:\n    请选择进入方式\n"ESC"支付5元宝进入（打怪经验将额外获得50％的经验加成）\nbuyitem 99 1 1\n"ESC"直接进入"));
//		}
		for (i=0;i<sizeof(team);i++)
		{
			if (team[i]->get("wg_bb")) "cmd/base/buyitem"->main(team[i],"99 1 1");
			level=level+team[i]->get_level();
		}
		level=level/sizeof(team);
//		if (!who->get_2("scum.z"))
		{
			if( ( z = find_map_flag(1000, 2999, 0) ) > 0 )
			{
//				p = 885;
				p = 151;
				init_virtual_map(z, p);    // 生成虚拟地图
//			        map = new( NEWBIE );
			        map = new( "/inh/std/scum_map" );
				map->set_client_id(p);
				set_map_object( map, map->set_id(z) );
//				for(i=0;i<sizeof(nxy);i++)
				for(i=0;i<100;i++)
				{
					npc = new("npc/party/scum_fight3");
					npc->set("team_id",tId);
					npc->set_level(level);
				
				        NPC_ENERGY_D->init_level( npc, level );    
					if( !( p = efun::get_xy_point( 151, IS_CHAR_BLOCK ) ) )
						continue;
					x = ( p % 1000000 ) / 1000;  y = p % 1000;
					npc->add_to_scene(z,x,y);
					//npc->add_to_scene(z,nxy[i]/1000,nxy[i]%1000);
					count++;
				}
				convey = new("npc/party/scum_convey");
				convey->add_to_scene(z,108,58);
				map->add("scene_npc_amount",count);
				map->set("copy_npc_amount",500);
				map->set("copy_level",level);
		
			}		
			for (i=0;i<sizeof(team);i++)
			{
//				team[i]->set_2("scum.z", z);
//				team[i]->set_2("scum.map", map);
//				team[i]->set_2("scum.npc_z",get_z(me));
//				team[i]->set_2("scum.npc_x",get_x(me));
//				team[i]->set_2("scum.npc_y",get_y(me));
//				team[i]->set_2("scum.npc_id",me->get_char_id());
//				team[i]->set_2("scum.team_id",team[i]->get_team_id());
				if( !( p = efun::get_xy_point( 151, IS_CHAR_BLOCK ) ) )
					continue;
				x = ( p % 1000000 ) / 1000;  y = p % 1000;
        			//exit=nxy[random(sizeof(nxy))];
//        			team[i]->add_to_scene(map->get_id(),exit/1000,exit%1000);
        			team[i]->add_to_scene(map->get_id(),x,y);
//				send_user( team[i], "%c%s", ';', HIY"我们的队伍已进入战斗场景。" );
			}
			map->set_owner(me);
//			me->set("mymap",map);
		}
		break;
//	case 5:
////		if (!tId) return;
////		if (sizeof(team)<3) return;
////		if (me->get("busy") != tId) return;
//		map = me->get("mymap");
//		if (!map) return;
//     		exit=nxy[random(sizeof(nxy))];
//		who->add_to_scene(who->get_2("scum.z"), exit/1000,exit%1000);
//		break;
	}
}


//传出场景
void outlet(int sec,object map)
{
	int i,size,tId;
	object *member,npc;
	string id;
	sec = sec-5;
	if (!map) return;
	member = "inh/std/scum_map"->get_all_user( map );

	if ( sec > 0 )
	{
		for(i=0,size=sizeof(member);i<size;i++)
		{
			tell_user(member[i],"Sau %d giây，tự động rời khỏi",sec);
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
        send_user(who,"%c%s",'!',"Ngươi bị Võ Lâm Bại Hoại đánh trọng thương");
}