#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

void create()
{
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, i;
	mixed *mixTime;
	remove_call_out("check_time");
	iTime = time();
	mixTime = localtime(iTime);
	if (mixTime[TIME_WDAY] == 1 || mixTime[TIME_WDAY] == 3 || mixTime[TIME_WDAY] == 5 || mixTime[TIME_WDAY] == 0) // Thứ 3, t5, t7 có Boss
	{
		call_out("check_time", 3600 * 24);
		return;
	}
	else
	{
		if (mixTime[TIME_HOUR] != 20)
		{
			call_out("check_time", 3600);
		}
		else
		{
			"tran/phuban/go"->set_open(1);
			CHAT_D->sys_channel(0, HIR "Phó Bản Thế Giới đã bắt đầu. mọi người đến NPC Vạn Thần để tham gia, phó bản sẽ kết thúc sau 3 giờ");
			call_out("check_time2", 10800);
			call_out("check_time", 3600);
		}
	}
}
//  移除武林败类NPC
void check_time2()
{
	object *member, map;
	int i, size;

	"tran/phuban/go"->set_open(0);
	if (get_map_object(2999))
	{
		map = get_map_object(2999);
		member = map->get_all_user(map);
		map->destruct_virtual_map(map, map->get_id());
		for (i = 0, size = sizeof(member); i < size; i++)
		{
			member[i]->add_to_scene(80, 275, 185);
		}
	}
	CHAT_D->sys_channel(0, HIR "Phó Bản đã kết thúc!!!");
}
