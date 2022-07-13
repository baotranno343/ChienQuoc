/*******************************
	**古墓探险**
*******************************/

#include <time.h>
#include <ansi.h>
#include <chia_kenh.h>
inherit DBASE_F;
inherit SAVE_F;

#define FILE_NPC "npc/party/0041"
#define PLAYER_EXIT "sys/party/gumu"
#define FILE_SAVE "data/party" SAVE_EXTENSION
#define DEBUG(arg)      \
	if (find_char("9")) \
		tell_user(find_char("9"), arg);

int gumu = 0;
int gumu_party = 1;
// 函数：生成二进制码
void SAVE_BINARY() {}

//活动开启状态保存
string get_save_file()
{
	return FILE_SAVE;
}
void create()
{
	// if (MAIN_D->get_kenh() != KENH_EVENT)
	// {
	// 	return;
	// }
	restore();
	gumu = 0;
	call_out("check_time", 3);
}

void check_time()
{
	int iTime, i;
	mixed *mixTime;

	remove_call_out("check_time");
	iTime = get_party_time();
	if (!gumu_party)
		return;
	mixTime = localtime(iTime);
	if (mixTime[TIME_HOUR] > 22)
	{
		call_out("check_time", 3600 * 24 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
		return;
	}
	if (mixTime[TIME_HOUR] < 20)
	{
		call_out("check_time", 20 * 3600 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
		return;
	}
	if (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] < 30)
	{
		call_out("check_time1", 60 * (30 - mixTime[TIME_MIN]));
		return;
	}
	else
	{
		call_out("check_time1", 1);
		log_file("party_event.dat", sprintf("%d ：%d: Cổ Mộ mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
	}
}

void check_time1()
{

	int i;
	mixed *mixTime;
	mixTime = localtime(get_party_time());
	if (gumu_party)
	{
		for (i = 0; i < 3; i++)
			CHAT_D->sys_channel(0, HIR "Thám hiểm Cổ Mộ chính thức bắt đầu, mọi người hãy nhanh đến Chu(276,163) báo danh！");
	}
	gumu = 1;
	"cmd/base/time"->set_gumu(1);
	//"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" HIG "Thám hiểm Cổ Mộ chính thức bắt đầu, mọi người hãy nhanh đến Chu(276,163) báo danh！");

	call_out("check_time2", 22 * 3600 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
}

void check_time2()
{
	int i;
	mixed *mixTime;
	mixTime = localtime(get_party_time());
	remove_call_out("check_time2");
	if (gumu_party)
	{
		for (i = 0; i < 3; i++)
			CHAT_D->sys_channel(0, HIR "Thám hiểm Cổ Mộ chính thức kết thúc, mọi người hãy lại đến Chu(276,163) báo danh vào tối mai！");
	}
	gumu = 0;
	"cmd/base/time"->set_gumu(0);
	call_out("player_exit", 24 * 3600 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
	call_out("check_time", 24 * 3600 - mixTime[TIME_HOUR] * 3600 - mixTime[TIME_MIN] * 60);
}

int get_gumu_open()
{
	return gumu;
}

void set_gumu_party_open(int party, int test)
{
	if (party == 0)
	{
		if (test)
		{
			USER_D->gm_channel(HIY "测试活动关闭");
			gumu = 0;
		}
		USER_D->gm_channel(HIY "ＧＭ正常关闭活动");
	}
	else
	{
		if (test)
		{
			USER_D->gm_channel(HIY "测试活动开启");
			gumu = 1;
		}
		USER_D->gm_channel(HIY "ＧＭ正常开启活动");
	}
	gumu_party = party;
	__FILE__->check_time();
	save();
}

int get_gumu_party_open()
{
	return gumu_party;
}

string get_party_statue()
{
	if (get_gumu_party_open() && get_gumu_open())
		return "古墓探险活动处于开始状态";
	else if (get_gumu_party_open())
		return "古墓探险活动处于正常开启状态";
	return "古墓探险活动处于关闭状态";
}

//void add_npc(int z,int x,int y)
//{
//	object npc,map;
//	npc=new(FILE_NPC);
//	if(!npc) return;
//	if(!z&&!x&&!y) return;
//	if(!objectp(map=get_map_object(z))) return;
//	npc->add_to_scene(z,x,y,4,9413);
//	map->set("npc",npc);
//}
//
//void delete_npc(int z)
//{
//	object map,npc;
//	if(!z) return;
//	if(!objectp(map=get_map_object(z))) return;
//	npc=map->get("npc");
//	npc->remove_from_scene();
//	destruct(npc);
//	map->delete("npc");
//
//}

void player_exit()
{
	PLAYER_EXIT->player_exit();
}