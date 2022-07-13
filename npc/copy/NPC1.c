#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;
int host_type;
void reset();
// 函数：获取人物造型
int get_char_picid() { return 9115; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Khiêu Chiến Danh Tướng");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "accept":(
								   : do_accept:),
					   "query":(
								   : do_query:),
	]));
	setup();
	host_type = MAIN_D->get_host_type();
}

void do_look(object who)
{
	int id;
	object me = this_object();

	id = getoid(me);
	if (MAIN_D->get_host_type() == 6012)
	{
		send_user(who, "%c%s", '!', "Bản sao chưa được mở ra");
		return;
	}
	send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Khiêu Chiến Danh Tướng：\n Hãy chuẩn bị sẵn sàng, ta sẽ đưa ngươi đến ải tiếp theo!!\n" ESC "Tiến vào Phó bản\ntalk %x# welcome.3\n" ESC "Rời khỏi", id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, i, id, tId, *nXy, level, iTime, iDay, size, tid, x, y, z, p;
	string legend, result;
	object who, item, map, *team;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	who = this_player();
	flag = to_int(arg);
	level = who->get_level();
	who->set_time("talk", 0);
	id = getoid(me);
	if (MAIN_D->get_host_type() == 6012)
	{
		send_user(who, "%c%s", '!', "Bản sao chưa được mở ra");
		return;
	}
	switch (flag)
	{
	case 1:
		if (level > 0)
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Khiêu Chiến Danh Tướng：\n  Update.............!!!", id, id, ));
		break;
	case 2:
		if (level > 0)
			send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Khiêu Chiến Danh Tướng：\n Update............. !!!\n ", id, ));
		break;
	case 3:
	{
		team = who->get_team();
		size = sizeof(team);
		/*
		if ( !item )
		{
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Khiêu Chiến Danh Tướng：\n Bạn không có chìa khóa ải 1 à ????  "));
			return ;	
		} 
		 */

		if (!who->is_leader())
		{
			result = sprintf(me->get_name() + ":\n Hãy gọi đội trưởng tới gặp ta !\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}

		if (size < 1)
		{
			result = sprintf(me->get_name() + ":\n  Phải có đội nhóm mới có thể tiến vào!\n");
			result += sprintf(ESC "Rời khỏi");
			send_user(who, "%c%c%w%s", ':', 1, me->get_char_picid(), result);
			return;
		}

		for (i = 0; i < size; i++)
		{
			if (!objectp(team[i]))
				continue;
			if (!inside_screen_2(me, team[i]))
			{
				result = sprintf(me->get_name() + ":\n Hãy gọi tất cả thành viên trong nhóm đến gặp ta !\n");
				result += sprintf(ESC "Rời khỏi");
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
				return;
			}
			/*	if(team[i]->get_level()<60)
		     	      	{
		     	      		result=sprintf(me->get_name()+":\n  Thành viên trong nhóm ngươi "HIR "%s "NOR "cấp bậc chưa đủ 60 cấp trở lên !\n",team[i]->get_name() );
		     	      		result+=sprintf(ESC "Rời khỏi");
		     	      		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
		     	      		return;
		     	      	}
						if (team[i]->get_save_2("ptt.day")==iDay)
		                 {
			           result = me->get_name()+"：\n  Bạn đã tham gia phó bản hôm nay rồi!\n";
			           send_user( who, "%c%c%w%s", ':', 3, 5201, result );
			                return;
		                  }*/
		}
		tid = who->get("team_id");
		{
			map = TEAM_D->get_copy_scene(tId, COPY_BARRACK3);
			//		 USER_D->user_channel(sprintf("Bằng hữu "HIY" %s "NOR " cùng đồng đội tiến vào ải  "HIY" 1 "NOR" phá thiên trận.", who->get_name() ));
			if (!map) //创建副本
			{
				map = "sys/copy/barrack2"->new_copy(me, who, me->get("tang"));
			}
			if (!map)
				return;
			for (i = 0; i < sizeof(team); i++)
			{
				nXy = map->get("entrance");
				//        		who->add_to_scene(map->get_id(),nXy[0],nXy[1]);
				//team[i]->add_save("ptt.day",1);
				// send_user(team[i], "%c%c%w%s", 0x5a, 0, 3, "Truyền tống……");
				// team[i]->set_2("travel.z", map->get_id());
				// team[i]->set_2("travel.p", nXy[0] + nXy[1]);
				// //team[i]->set_save_2("ptt.day", iDay);
				// set_effect(team[i], EFFECT_CHAR_NO_MOVE, 3);
				// set_effect(team[i], EFFECT_TRAVEL, 3);
				if (!(p = efun::get_xy_point(map->get_id(), IS_CHAR_BLOCK)))
					continue;
				x = (p % 1000000) / 1000;
				y = p % 1000;
				team[i]->add_to_scene(map->get_id(), x, y);
			}
			// for (i = 0; i < sizeof(team); i++)
			// {
			// 	if (!(p = efun::get_xy_point(896, IS_CHAR_BLOCK)))
			// 		continue;
			// 	x = (p % 1000000) / 1000;
			// 	y = p % 1000;
			// 	team[i]->add_to_scene(z, x, y);

			// 	team[i]->set_save_2("ptt.day", iDay);
			// }
			me->remove_from_scene();
			destruct(me);
			break;
		}

		//	 send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Khiêu Chiến Danh Tướng：\n Update............. !!!\n ",id,));
	}
	}
}
