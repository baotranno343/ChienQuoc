
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <map.h>
inherit DBASE_F;
/*
	goto 		前去活动场景
	reset		初始化活动场景或者解禁所有玩家，解除戒严
	invite %d	邀请玩家
	kickout %d	踢出场景
	clean		清除怪物
	recover all	恢复所有玩家
	recover %d	恢复某一玩家
	busy %d		禁锢玩家
	free %d 	解禁玩家
	forbbit all	戒严指令
	forbbit none	解除戒严
*/


// 函数：命令处理
int main( object me, string arg )
{
	string * key, result;
	object * users, player, who;
	int i, size, z, p, x, y, x0, y0, *maps;
	object map;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if( !arg )
        {
                if (get("maps")==0)
                {                	
                	send_user( me, "%c%s", ':', "你想做什么呢？\n"
                        	ESC "生成活动场景\n" + "gmfight reset\n" +
                        	ESC "取消\nCLOSE" );
                	return 1;
		}        
                send_user( me, "%c%s", ':', "你想执行什么操作？\n"
                	ESC "去活动场景1\n" + "gmfight goto 1\n" +
                	ESC "去活动场景2\n" + "gmfight goto 2\n" +
                       	ESC "初始化活动场景\n" + "gmfight reset\n" +
                       	ESC "邀请玩家\n" + "gmfight invite ?\n" +
                       	ESC "请离玩家\n" + "gmfight kickout ?\n" +
                       	ESC "清除怪物\n" + "gmfight clean\n" +
                       	ESC "恢复所有玩家状态\n" + "gmfight recover all\n" +
                       	ESC "恢复某一玩家\n" + "gmfight recover ?\n" +
                       	ESC "禁锢玩家\n" + "gmfight busy ?\n" +
                       	ESC "解禁玩家\n" + "gmfight free ?\n" +
                       	ESC "场景戒严\n" + "gmfight forbbit all\n" +
                       	ESC "戒严取消\n" + "gmfight forbbit none\n" +
                       	ESC "取消\nCLOSE" );		
		return 1;	
        }
        key = explode( arg, " ");
       	size = sizeof(key);
       	maps = get("maps"); 
       	if (size==1)
       	{
       		switch(arg)
       		{
		case "reset":			
			if (maps==0)
			{
				if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) > 0 )
				{
					p = 891;
					init_virtual_map(z, p);    // 生成虚拟地图
					map = new( "/inh/std/fight" );
					map->set_client_id(p);
					set_map_object( map, map->set_id(z) );
					map->set_owner(me);
					map->set_forbbit(0);
					tell_user(me, "虚拟活动场所生成成功！");
					maps = ({ z });
				}
				if( ( z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0) ) > 0 )
				{
					p = 891;
					init_virtual_map(z, p);    // 生成虚拟地图
					map = new( "/inh/std/fight" );
					map->set_client_id(p);
					set_map_object( map, map->set_id(z) );
					map->set_owner(me);
					map->set_forbbit(0);
					tell_user(me, "虚拟活动场所生成成功！");
					maps += ({ z });
				}
				set("maps", maps);
				return 1;
			}
			map = get_map_object(maps[0]);
			if (map)
			{
				"/inh/std/fight"->cleanup_badman(map);
				users = "/inh/std/fight"->get_users(map);
				if (sizeof(users))
				{
					foreach (player in users) if( is_player(player) ) player->delete("no_fight");						
				}
				map->set_forbbit(0);
				tell_user(me, "虚拟活动场所初始化成功！");
			}
			map = get_map_object(maps[1]);
			if (map)
			{
				"/inh/std/fight"->cleanup_badman(map);
				users = "/inh/std/fight"->get_users(map);
				if (sizeof(users))
				{
					foreach (player in users) if( is_player(player) ) player->delete("no_fight");						
				}
				map->set_forbbit(0);
				tell_user(me, "虚拟活动场所初始化成功！");
			}			
			break;
		case "clean":
			if (maps==0)
			{
				notify( "活动地图不存在！" );
				return 1;
			}		
			map = get_map_object(maps[0]);	
			if (map)
			{
				"/inh/std/fight"->cleanup_badman(map);
				tell_user(me, "清除怪物成功");
			}	
			map = get_map_object(maps[1]);	
			if (map)
			{
				"/inh/std/fight"->cleanup_badman(map);
				tell_user(me, "清除怪物成功");
			}									
       		}
       		return 1;
       	}
       	if (size>2)
       	{
       		notify( "命令格式错误！" );
       		return 1;
       	}
	if (maps==0)
	{
		notify( "活动地图不存在！" );
		return 1;
	}
	z = get_z(me);
	if (z!=maps[0] && z!=maps[1]&& key[0]!="goto")		
	{
		notify( "你需要在活动地图才能执行这些指令" );
		return 1;
	}		
	map = get_map_object(z);     
	if (!map)  	
	{
		notify( "当前地图不存在！" );
		return 1;
	}	
       	switch(key[0])
       	{
	case "goto":	
		z = to_int(key[1]);
		z --;
		if (z<0) z = 0;
		if (z>1) z = 1;
		z = maps[z];
		if (z==0)
		{
			notify( "活动地图"+sprintf("%d", z)+"不存在！" );
			return 1;
		}			
		if( p = get_jumpin(z, 1) )
		{
			me->set("no_fight", 1);
			me->add_to_scene(z, p / 1000, p % 1000, 3);			   		 	
		}
		break;       		
       	case "invite":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "请输入邀请目标玩家的ID：\n"
                        	ESC "gmfight invite %s\n");       					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "您无法找到这个人。" );
				return 1;
		        }       
		        if (who->is_npc()&&is_gm(me))	
		        {
		                notify( "您的权限不足于邀请NPC。" );
				return 1;
		        }		        			
       			z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);
       			if( !p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) ) return 1;
       			x = p / 1000;  y = p % 1000;
			who->add_to_scene( z, x, y, 3, 40971, 0, 40971, 0 );
			tell_user(me, "你成功邀请了"+who->get_name());
       		}
       		break;
       	case "kickout":
       		if (key[1]=="?")
       		{       	
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "请输入请离目标玩家的ID：\n"
                        	ESC "gmfight kickout %s\n");          					
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "您无法找到这个人。" );
				return 1;
		        }  
		        MAP_D->add_to_void(who);       		
		        tell_user(me, "你将"+who->get_name()+"请离活动地图。");	
       		}       	
       		break;
       	case "recover":
       		if (key[1]=="?")
       		{       
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "请输入恢复目标玩家的ID：\n"
                        	ESC "gmfight recover %s\n");         						
       		}
       		else
       		if (key[1]=="all")
       		{
			users = "/inh/std/fight"->get_users(map);
			if (sizeof(users))
			{
				foreach (who in users)
				{
				        who->set_hp( who->get_max_hp() );
				        who->set_mp( who->get_max_mp() );
				        who->set_yuan( who->get_max_yuan() );						
				}						
			} 
			tell_user(me, "你恢复所有活动地图的玩家的状态。");      			
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "您无法找到这个人。" );
				return 1;
		        }  
		        who->set_hp( who->get_max_hp() );
		        who->set_mp( who->get_max_mp() );
		        who->set_yuan( who->get_max_yuan() );	
		        tell_user(me, "你将"+who->get_name()+"的状态恢复");		               			
       		}       	
       		break;
       	case "busy":
       		if (key[1]=="?")
       		{       			
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "请输入禁锢目标玩家的ID：\n"
                        	ESC "gmfight busy %s\n");         			
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "您无法找到这个人。" );
				return 1;
		        }  
		        who->set("no_fight", 1);	
		        tell_user(me, "你将"+who->get_name()+"在活动场所的战斗禁锢");	       			
       		}       	
       		break;
       	case "free":
       		if (key[1]=="?")
       		{       		
                	send_user( me, "%c%c%d%s", '?', 1, MAX_NUMBER, "请输入解禁目标玩家的ID：\n"
                        	ESC "gmfight free %s\n");         				
       		}
       		else
       		{
			if( !( who = find_any_char(key[1]) ) )
		        {
		                notify( "您无法找到这个人。" );
				return 1;
		        }  
		        if( is_player(who) ) who->delete("no_fight");	
		        tell_user(me, "你将"+who->get_name()+"在活动场所的战斗解禁");	          			
       		}       	
       		break;
       	case "forbbit":
       		if (key[1]=="all") map->set_forbbit(1);
       		else
       		if (key[1]=="none") map->set_forbbit(0);
       		else
       			notify( "命令格式错误！" );
       		break;
       	}
       	return 1;
}

/*
	goto 		前去活动场景
	reset		初始化活动场景或者解禁所有玩家，解除戒严
	invite %d	邀请玩家
	kickout %d	踢出场景
	clean		清除怪物
	recover all	恢复所有玩家
	recover %d	恢复某一玩家
	busy %d		禁锢玩家
	free %d 	解禁玩家
	forbbit all	戒严指令
	forbbit none	解除戒严
*/	