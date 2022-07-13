/*******************************
	**门派偷袭战**
*******************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <chia_kenh.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

void generate_scum();
void destroy_scum();

int *nScene = ({289, 273, 80, 324, 269, 54, 165});
string *schoolname = ({
	"Đào Hoa Nguyên",
	"Thục Sơn",
	"Cấm Vệ Quân",
	"Đường Môn",
	"Mao Sơn",
	"Côn Luân",
	"Vân Mộng Cốc",
});
object *Scum;
mapping mpNianshou;
// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	//	restore();
	Scum = ({});
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, rate, level, z, p, x, y;
	int i, *nScene, size;
	mixed *mixTime;
	remove_call_out("check_time");
	iTime = time();

	mixTime = localtime(iTime);
	i = 60 * (60 - mixTime[TIME_MIN]);

	if (mixTime[TIME_HOUR] != 10 && mixTime[TIME_HOUR] != 20)
	{
		call_out("check_time", i);
		return;
	}

	if ((mixTime[TIME_HOUR] == 10 && mixTime[TIME_MIN] < 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] < 30))
	{
		call_out("check_time", 1800 - i);
	}
	else
	{
		"cmd/base/time"->set_tapkich(1);

		generate_scum();
		call_out("check_time", i + 3600);
		call_out("destroy_scum", 3600 - (60 * mixTime[TIME_MIN]));
		log_file("party_event.dat", sprintf("%d ：%d: Tập Kích Môn Phái mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
	}

	// if (mixTime[TIME_HOUR] % 2 == 1) // == 0 là giờ lẽ, == 1 là giờ chẵn
	// {
	// 	call_out("check_time", i);
	// 	return;
	// }
	// else
	// {
	// 	if ((mixTime[TIME_HOUR] == 2) || (mixTime[TIME_HOUR] == 4) || (mixTime[TIME_HOUR] == 6) || (mixTime[TIME_HOUR] == 8) || (mixTime[TIME_HOUR] == 10 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] > 30) //Nếu giờ hiện tại là: 1 , 3, 5, 7h thì Kết thúc hàm -> ko có Phi Tặc
	// 		|| (mixTime[TIME_HOUR] == 14) || (mixTime[TIME_HOUR] == 16) || (mixTime[TIME_HOUR] == 18)																																		 // Nếu ko có dòng > 30 thì 9h59 vẫn sẽ có phỉ còn nếu có thì khi bật GSE lên 9h30 sẽ ko có phỉ
	// 		|| (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 22 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] > 30))
	// 		call_out("check_time", i + 3600);
	// 	else
	// 	{
	// 		generate_scum();				  // Nếu giờ hiện tại là: 9,11,13,15,17,19,21,23h thì gọi Phi Tặc ra
	// 		call_out("check_time", i + 3600); //( nhưng nếu cùng giờ đó mà số phút lớn hơn 30 - Chỉ tính cái này khi vừa bật GSE -> thì Phi Tặc sẽ đợi sang giờ kế tiếp mới xuất hiện )
	// 	}
	// }
}
//  放入武林败类NPC

void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;

	j = random(7);
	z = nScene[j];
	for (i = 0; i < 15; i++)
	{
		if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
			continue;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		npc = new ("/npc/party/scum2");
		npc->add_to_scene(z, x, y);
		Scum += ({npc});
	}

	CHAT_D->sys_channel(0, sprintf(HIR "Võ Lâm Bại Hoại tập kích " HIY "%s" HIR " ,anh hùng tứ phương hãy ra tay trợ giúp " HIY "%s đệ tử" HIR " tiêu diệt đám bại hoại này.", schoolname[j], schoolname[j]));
	CHAT_D->sys_channel(0, sprintf(HIR "Võ Lâm Bại Hoại tập kích " HIY "%s" HIR " ,anh hùng tứ phương hãy ra tay trợ giúp " HIY "%s đệ tử" HIR " tiêu diệt đám bại hoại này.", schoolname[j], schoolname[j]));
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" + sprintf(HIG "Võ Lâm Bại Hoại tập kích " HIY "%s" HIR " ,anh hùng tứ phương hãy ra tay trợ giúp " HIY "%s đệ tử" HIR " tiêu diệt đám bại hoại này.", schoolname[j], schoolname[j]));

	//	CHAT_D->sys_channel(0,sprintf(HIR "Võ Lâm Bại Hoại tập kích "HIY"%s"HIR " ,anh hùng tứ phương hãy ra tay trợ giúp "HIY "%s đệ tử"HIR " tiêu diệt đám bại hoại này.",schoolname[j],schoolname[j]));
}

//  移除武林败类NPC
void destroy_scum()
{
	int i, size;
	for (i = 0, size = sizeof(Scum); i < size; i++)
	{
		if (!objectp(Scum[i]))
			continue;
		// if (!Scum[i]->get("busy"))
		// {
		Scum[i]->remove_from_scene();
		destruct(Scum[i]);
		//}
		// else
		// 	Scum[i]->set("overdue", 1);
	}

	"cmd/base/time"->set_tapkich(0);
	Scum -= ({0});
	CHAT_D->sys_channel(0, sprintf(HIR "Võ Lâm Bại Hoại tập kích " HIG "Đã rời đi cảm ơn các ân nhân đã giúp đỡ bổn môn phái"));
}
