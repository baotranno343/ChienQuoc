
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <map.h>
inherit DBASE_F;

inherit SAVE_F;

int * place = ({ 80, 20, 10, 70, 60, 50, 40, 30, 139, 271 });

void create() 
{
	restore();
}

// 函数：取存盘文件名
string get_save_file() { return "data/city/findgm"SAVE_EXTENSION; }

// 函数：命令处理
int main( object me, string arg )
{
	int i, size, p, x, y, z, type;
	object * npcs, npc, who, map;
	string arg2;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if( !arg )
        {
              	send_user( me, "%c%s", ':', "你想做什么呢？\n"
              		ESC "设置奖品种类\n" + "findgm setbonus\n" +
              		ESC "设置GM出现的地图\n" + "findgm setmap\n" +
              		ESC "开始寻找ＧＭ的活动\n" + "findgm start\n" +
              		ESC "结束寻找ＧＭ的活动\n" + "findgm end\n" +
              		ESC "显示剩余ＧＭ的位置\n" + "findgm list\n" +
              		ESC "取消\nCLOSE" );
              	return 1;        	
	}
	who = this_object();
	switch(arg)	
	{
	case "start":
		npcs = get("npcs");		
		if (npcs!=0 && sizeof(npcs)!=0)
		{
			notify( "上次寻找gm的活动尚未结束！" );
			return 1;
		}		
		who->add_save("gm_time", 1);
		who->save();
		npcs = ({ });
		npc = new ("/npc/party/gm2");
		size = sizeof(place);
		z = who->get_save("map");
		if (z==0) z = 80;		
		if ( (p = get_xy_point(z, IS_CHAR_BLOCK))|| (p = get_jumpin(z, -1)) )
		{
			x = p / 1000;  y = p % 1000;
	                if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
	                {
	                        npc->add_to_scene( z, p / 1000, p % 1000, get_d(me), 40991, 40992, 40991, 40992 );
	                        npcs += ({ npc });
	                }
	                map = get_map_object(z);
	                arg2 = map->get_name();			
		}
		else		
		{
			notify( "地图设置不对" );
			return 1;
		}
		for (i=0;i<9;i++)
		{
			npc = new ("/npc/party/gm");
			size = sizeof(place);

			if ( (p = get_xy_point(z, IS_CHAR_BLOCK))|| (p = get_jumpin(z, -1)) )
			{
				x = p / 1000;  y = p % 1000;
		                if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
		                {
		                        npc->add_to_scene( z, p / 1000, p % 1000, get_d(me), 40991, 40992, 40991, 40992 );
		                        npcs += ({ npc });
		                }			
			}
				
		}
		set("npcs", npcs);
		notify( "寻找gm的活动成功地在"+arg2+"开始了" );
		return 1;
		break;
	case "end":	
		npcs = get("npcs");
		if (npcs==0) return 1;
		npcs -= ({ 0 });	
		size = sizeof(npcs);
		set("npcs", npcs);
		if (size==0) return 1;
		for (i=0;i<size;i++)
		{
			npcs[i]->remove_from_scene();
			destruct(npcs[i]);        
		}
		set("npcs", 0);
		notify( "寻找gm的活动成功地结束了" );	
		return 1;	
		break;;
	case "list":
		npcs = get("npcs");
		if (npcs==0) return 1;
		npcs -= ({ 0 });	
		size = sizeof(npcs);
		set("npcs", npcs);
		if (size==0) return 1;	
		for (i=0;i<size;i++)
		{
			send_user( me, "%c%s", '>', sprintf("%s(%x#)的坐标是%d %d,%d", npcs[i]->get_name(), getoid(npcs[i]), get_z(npcs[i]), get_x(npcs[i]), get_y(npcs[i])));     
		}	
		return 1;
		break;
	case "setbonus":
              	send_user( me, "%c%s", ':', "请选择除了两万元以外的奖品：\n"
              		ESC "战国令\n" + "findgm setbonus 1\n" +
              		ESC "战国号角\n" + "findgm setbonus 2\n" +
              		ESC "血石\n" + "findgm setbonus 3\n" +
              		ESC "法石\n" + "findgm setbonus 4\n" +
              		ESC "兔子变身卡\n" + "findgm setbonus 5\n" +
              		ESC "气脉丹\n" + "findgm setbonus 6\n" +
              		ESC "逍遥散\n" + "findgm setbonus 7\n" +
              		ESC "紫心丹\n" + "findgm setbonus 8\n" +
              		ESC "取消\nCLOSE" );
		return 1;
		break;
	case "setmap":
              	send_user( me, "%c%s", ':', "请选择活动地图：\n"
              		ESC "周国\n" + "findgm setmap 80\n" +
              		ESC "韩国\n" + "findgm setmap 20\n" +
              		ESC "齐国\n" + "findgm setmap 10\n" +
              		ESC "燕国\n" + "findgm setmap 70\n" +
              		ESC "楚国\n" + "findgm setmap 60\n" +
              		ESC "秦国\n" + "findgm setmap 50\n" +
              		ESC "魏国\n" + "findgm setmap 40\n" +
              		ESC "赵国\n" + "findgm setmap 30\n" +
              		ESC "襄陵\n" + "findgm setmap 21\n" +
              		ESC "涿鹿\n" + "findgm setmap 271\n" +
              		ESC "取消\nCLOSE" );
		return 1;
		break;	
	}	  				
	sscanf(arg, "%s %d", arg2, type);
	switch(arg2)
	{
	case "setbonus":
		who->set_save("bonus", type);
		who->save();	
		notify( "设置了活动的奖励" );	
		break;
	case "setmap":
		p = get_jumpin(type, 10);
		if (p==0)
		{
			notify( "不是刷怪地图，不宜作为活动地图。" );	
			return 1;
		}
		who->set_save("map", type);
		who->save();	
		notify( "设置了活动地图" );	
		break;		
	}	             	
	return 1;
}
	