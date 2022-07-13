/*****************************
/*****************************
	**Tết Âm lịch**
*****************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

int *change54 = ({
	0010,
	0011,
	0050,
	0051,
	0052,
	0053,
	0100,
	0101,
	0102,
	0150,
	0151,
	0152,
	0200,
	0201,
	0202,
	0250,
	0251,
	0252,
	0300,
	0301,
	0302,
	0303,
	0304,
	0350,
	0351,
	0352,
	0400,
	0401,
	0402,
	0450,
	0500,
	0502,
	0550,
	0551,
	0552,
	8010,
	8011,
});
int *nScene = ({1, 80});
int iStart, iFinish, iFinish2, close_val, open_val;

mapping mpOanQuy = ([1:({
						   ({179, 154, 3}),
						   ({146, 102, 3}),
						   ({146, 153, 3}),
						   ({100, 123, 3}),
					   }),
					80:({
						   ({318, 135, 4}),
					   }),

]);

mapping mpThucMa = ([1:({
						   ({178, 154, 3}),
						   ({145, 102, 3}),
						   ({145, 153, 3}),
						   ({94, 123, 3}),
					   }),
					80:({
						   ({314, 138, 4}),
					   }),
]);
object *NianShou, *BaoZhu, *NPCHinhNom;
mapping mpNianshou;

void generate_baozhu();
void destroy_baozhu();
void generate_nianshou();
void destroy_nianshou();
void generate_NPCHinhNom();
void destroy_NPCHinhNom();

// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	iStart = mktime(2021, 2, 6, 0, 0, 0);	  // Ngày 31 tháng 10
	iFinish = mktime(2021, 2, 22, 0, 0, 0);	  // Ngày 2 tháng 11 lúc 23h kết thúc event
	iFinish2 = mktime(2021, 2, 22, 0, 59, 0); // Ngày 2 tháng 11 lúc 23h59 phút kết thúc hình nộm
	NianShou = ({});
	BaoZhu = ({});
	mpNianshou = ([]);
	NPCHinhNom = ({});
	if (time() > iStart)
		generate_NPCHinhNom();
	call_out("check_time", 3);
}

void check_time()
{
	int iHour, p, i;
	mixed *mixTime;
	remove_call_out("check_time");
	iHour = time();

	if (iHour > iFinish2)
	{
		destroy_NPCHinhNom();
		return;
	}
	if (iHour > iFinish)
	{
		destroy_baozhu();
		destroy_nianshou();
		return;
	}
	if (iHour < iStart) //没到时间
	{
		call_out("check_time", iStart - iHour);
		return;
	}

	mixTime = localtime(time());
	iHour = mixTime[TIME_HOUR];
	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // == 0 là giờ lẽ, == 1 là giờ chẵn
	{
		call_out("check_time", i);
		return;
	}
	else
	{
		if (mixTime[TIME_HOUR] == 2 || mixTime[TIME_HOUR] == 4 || mixTime[TIME_HOUR] == 6 || mixTime[TIME_HOUR] == 8 || (mixTime[TIME_HOUR] == 10 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 14 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 16 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 18 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 22 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] > 30))
			call_out("check_time", i + 3600);
		else
		{
			generate_baozhu();	 // Tạo Bùa
			generate_nianshou(); // Tạo tà thú
			call_out("check_time", i + 3600);
		}
	}
}

// Tạo hình nộm
void generate_NPCHinhNom()
{
	int i, size, z, p, x, y, j, count, *nZ, *nXy;
	object *nObj, fw;
	mixed *nPoint;
	nObj = ({});

	nZ = keys(mpOanQuy);
	for (j = 0, count = sizeof(nZ); j < count; j++)
	{
		z = nZ[j];
		nPoint = mpOanQuy[z];
		for (i = 0, size = sizeof(nPoint); i < size; i++)
		{
			fw = new ("npc/party/fuhh");
			if (!objectp(fw))
				continue;
			nXy = nPoint[i];
			fw->add_to_scene(z, nXy[0], nXy[1], nXy[2]);
			NPCHinhNom += ({fw});
		}
	}

	nZ = keys(mpThucMa);
	for (j = 0, count = sizeof(nZ); j < count; j++)
	{
		z = nZ[j];
		nPoint = mpThucMa[z];
		for (i = 0, size = sizeof(nPoint); i < size; i++)
		{
			fw = new ("npc/party/fuww");
			if (!objectp(fw))
				continue;
			nXy = nPoint[i];
			fw->add_to_scene(z, nXy[0], nXy[1], nXy[2]);
			NPCHinhNom += ({fw});
		}
	}
}

// Xóa hình nộm
void destroy_NPCHinhNom()
{
	int i, size;

	for (i = 0, size = sizeof(NPCHinhNom); i < size; i++)
	{
		if (!objectp(NPCHinhNom[i]))
			continue;
		NPCHinhNom[i]->remove_from_scene();
		destruct(NPCHinhNom[i]);
	}
}

//  Bùa Tiên
void generate_baozhu()
{
	int i, size, z, p, x, y, j, count;
	object item;
	for (j = 0, count = sizeof(nScene); j < count; j++)
	{
		z = nScene[j];
		for (i = 0; i < 80; i++)
		{
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			item = new ("/item/event/banhtet");
			item->set_amount(5);
			if (!objectp(item))
				continue;
			item->add_to_scene(z, x, y);
			BaoZhu += ({item});
		}
	}
	call_out("destroy_baozhu", 1800);
	CHAT_D->sys_channel(0, HIC "Ngoài thành nước Chu và Tân thủ thôn đột nhiên xuất hiện rất nhiều Bánh Tết, hãy nhanh chóng thu nhặt chúng về để đổi thưởng ở Thiện Tài Đồng Tử tại nước Chu !!");
	CHAT_D->sys_channel(0, HIC "Ngoài thành nước Chu và Tân thủ thôn đột nhiên xuất hiện rất nhiều Bánh Tết, hãy nhanh chóng thu nhặt chúng về để đổi thưởng ở Thiện Tài Đồng Tử tại nước Chu !!");
}

//  移除Pháo
void destroy_baozhu()
{
	int i, size;
	for (i = 0, size = sizeof(BaoZhu); i < size; i++)
	{
		if (!objectp(BaoZhu[i]))
			continue;
		BaoZhu[i]->remove_from_scene();
		destruct(BaoZhu[i]);
	}
}

//  放入年兽
void generate_nianshou()
{
	int i, size, z, p, x, y, j, count, amount;
	object *nObj, npc;
	nObj = ({});

	for (j = 0, count = sizeof(nScene); j < count; j++)
	{
		z = nScene[j];
		nObj = mpNianshou[z];
		if (!arrayp(nObj))
			nObj = ({});
		nObj -= ({0});
		amount = 30 - sizeof(nObj);
		nObj = ({});
		for (i = 0; i < amount; i++)
		{
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				continue;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			npc = new ("/npc/event/phantacnammoi");
			npc->add_to_scene(z, x, y);
			NianShou += ({npc});
			nObj += ({npc});
		}
		mpNianshou[z] = nObj;
	}
	call_out("destroy_nianshou", 1800);
	CHAT_D->sys_channel(0, HIY "Một đám phản tặc đã lợi dụng lúc bá tánh thiên hạ đang xum vầy bên nhau những ngày Tết, chúng đã trộm đi rất nhiều Hồng bao lì xì và trốn thoát. Nghe nói chúng đang ẩn nấp ở ngoài thành Chu quốc và Tân thủ thôn. Các vị anh hùng hãy nhanh chóng đi truy tìm và tiêu diệt bọn chúng trừ hại cho dân !");
	CHAT_D->sys_channel(0, HIY "Một đám phản tặc đã lợi dụng lúc bá tánh thiên hạ đang xum vầy bên nhau những ngày Tết, chúng đã trộm đi rất nhiều Hồng bao lì xì và trốn thoát. Nghe nói chúng đang ẩn nấp ở ngoài thành Chu quốc và Tân thủ thôn. Các vị anh hùng hãy nhanh chóng đi truy tìm và tiêu diệt bọn chúng trừ hại cho dân !");
}

//  移除年兽
void destroy_nianshou()
{
	int i, size;
	for (i = 0, size = sizeof(NianShou); i < size; i++)
	{
		if (!objectp(NianShou[i]))
			continue;
		NianShou[i]->remove_from_scene();
		destruct(NianShou[i]);
	}
	CHAT_D->sys_channel(0, HIY "Bọn phản tặc đã bị các anh hùng Chiến Quốc đánh đuổi thành công !");
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	object item, leader;
	string file, owner, id;
	int p, i, size, gold;
	int z, x, y;

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	if (!id)
		owner = who->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = who->get_id();
	}
	i = random(10000);
	if (i < 6000) // Thẻ Biến Thân
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new (sprintf("/item/54/%04d", change54[random(sizeof(change54))]));
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	if (i < 100) // Sơ cấp
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/sell/0032");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	if (i < 4000) // 10.000 ngân lượng
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/std/0001");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->set_value(10000);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
			gold++;
		}
	}
	if (i < 2000) //Túi Linh Thạch
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/TuiLinhThach/NgauNhien/2");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	if (i < 10000)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/event/lixi");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
}

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int exp, exp2;
	int i, size;
	string leader;

	if (!objectp(who = me->get_enemy_4()))
		return;
	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

	CHAT_D->sys_channel(0, HIY "Bằng hữu " + who->get_name() + " đã tiêu diệt Phản tặc trừ hại cho dân!");

	drop_items(me, who);

	if ((leader = who->get_leader()) && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
	}
	else
		size = 1;

	exp = 300;

	if (size > 1) // 多人
	{
		for (i = 0; i < size; i++)
			if (team[i])
			{
				exp2 = exp * (10 + size - 1) / 10;
				team[i]->add_exp(exp2);
			}
	}
	else // 单人
	{
		who->add_exp(exp);
	}
}

//设置春节活动的开启和关闭
int set_newyear(int open, int close)
{
	open_val = open;
	close_val = close;
	check_time();
	return 1;
}
