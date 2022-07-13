
#include <ansi.h>
#include <task.h>
#include <npc.h>
#include <item.h>
#include <cmd.h>
#include <time.h>
#include <equip.h>
// 函数:生成二进制码
void SAVE_BINARY() {}

// Lưu Lãng Thương Nhân的坐标
int SellerLocate = 0;

string *mastername = ({
	"Chu Vương",
	"Tề Vương",
	"Sở Vương",
	"Tần Vương",
	"Yên Vương",
	"Triệu Vương",
	"Ngụy Vương",
	"Hàn Vương",
	"Thục Sơn Chân Nhân",
	"Quỷ Cốc Tử",
	"Quảng Thành Tử",
	"Mao Chân Nhân",
	"Đường Lão Gia",
	"Đại Tướng Quân",
	"Vô Danh Lão Nhân",
});
string *locatename = ({
	"Chu Quốc",
	"Tề Quốc",
	"Sở Quốc",
	"Tần Quốc",
	"Yên Quốc",
	"Triệu Quốc",
	"Ngụy Quốc",
	"Hàn Quốc",
	"Thục Sơn",
	"Vân Mộng Cốc",
	"Côn Luân",
	"Mao Sơn",
	"Đường Môn",
	"Cấm Vệ Quân",
	"Đào Hoa Nguyên",
});
string *giftname = ({
	"0104",
	"0109",
	"0111",
	"0121",
	"0131",
	"0141",
	"0151",
	"0161",
	"0202",
	"0401",
	"0402",
	"0403",
	"0211",
	"0212",
	"0316",
	"0317",
	"0319",
	"0221",
	"0231",
	"0222",
	"0325",
	"0329",
	"0241",
	"0251",
	"0242",
	"0348",
	"0349",
	"0261",
	"0363",
	"0364",
	"0365",
	"0368",
	"0271",
	"0413",
	"0414",
	"0417",
	"0418",
	"0421",
	"0422",
	"0423",
	"0424",
	"0425",
	"0281",
	"0501",
	"0511",
	"0531",
	"0591",
});
string *cityname = ({
	"Tề Quốc",
	"Sở Quốc",
	"Tần Quốc",
	"Yên Quốc",
	"Triệu Quốc",
	"Ngụy Quốc",
	"Hàn Quốc",
});
string *schoolname = ({
	"Đào Hoa Nguyên",
	"Thục Sơn",
	"Cấm Vệ Quân",
	"Đường Môn",
	"Mao Sơn",
	"Côn Luân",
	"Vân Mộng Cốc",
});
mapping mpSkill = (["Đào Hoa Nguyên":({
										 0211,
										 0212,
										 0316,
										 0317,
										 0319,
									 }),
						  "Thục Sơn":({
										 0221,
										 0231,
										 0222,
										 0325,
										 0329,
									 }),
					   "Cấm Vệ Quân":({
										 0241,
										 0251,
										 0242,
										 0348,
										 0349,
									 }),
						 "Đường Môn":({
										 0261,
										 0363,
										 0364,
										 0365,
										 0368,
									 }),
						   "Mao Sơn":({
										 0271,
										 0413,
										 0414,
										 0417,
										 0418,
									 }),
						  "Côn Luân":({
										 0421,
										 0422,
										 0423,
										 0424,
										 0425,
									 }),
					  "Vân Mộng Cốc":({
										 0281,
										 0501,
										 0511,
										 0531,
										 0591,
									 }),
]);
mapping FamilyBook =
	(["Đào Hoa Nguyên":({
						   "0211",
						   "0212",
						   "0316",
						   "0317",
						   "0319",
					   }),
			"Thục Sơn":({
						   "0221",
						   "0231",
						   "0222",
						   "0325",
						   "0329",
					   }),
		 "Cấm Vệ Quân":({
						   "0241",
						   "0251",
						   "0242",
						   "0348",
						   "0349",
					   }),
		   "Đường Môn":({
						   "0261",
						   "0363",
						   "0364",
						   "0365",
						   "0368",
					   }),
			 "Mao Sơn":({
						   "0271",
						   "0413",
						   "0414",
						   "0417",
						   "0418",
					   }),
			"Côn Luân":({
						   "0421",
						   "0422",
						   "0423",
						   "0424",
						   "0425",
					   }),
		"Vân Mộng Cốc":({
						   "0281",
						   "0501",
						   "0511",
						   "0531",
						   "0591",
					   }),
]);
string *TaskName = ({"Bắt yêu quái", "Rèn luyện", "Du lịch", "Thu mua", "Thu thập", "Thăm viếng", "Tìm tung tích", "Hiệp trợ trị an", "Tuần sơn", "Môn phái tỷ thý"}); //,"Trù tập","Truy sát phản đồ","Truy bắt Thích khách"});
void check_random_bonus(object player);
int do_look2(object player, object master);
void task_bonus(object player, object master);
int get_city_number(string city);
void task_finish9(object player, object master);
void give_five_bonus(object who);
void clear_task(object player, int iCancel);
void send_task_desc(object who, int iClear);
void clear_task_desc(object who, int type);
void send_task_list(object who, int type);
void extra_skill_bonus(object who);
void init_npc(object npc);
void check_date(object player)
{
	mixed *mixTime;
	mixTime = localtime(time());
	if (mixTime[TIME_YDAY] != player->get_save_2("mastertask.day"))
	{
		player->set_save_2("mastertask.day", mixTime[TIME_YDAY]);
		player->set_save_2("mastertask.count", 0);
		player->set_save_2("mastertask.fivebonus", 0);
	}
}
void do_look(object player, object master)
{
	string name1, name2, result = "", cTmp;
	int id, status, time, level, date, exp, pot, order1, order2;
	object npc;

	name1 = player->get_fam_name();
	name2 = master->get_fam_name();

	// Thăm viếng
	if (__FILE__->do_look2(player, master) == 1)
		return;
	if (name1 == "" || name1 != name2 || player->get_fam_master() != master->get_name())
	{
		TASK_APPRENTICE_D->do_look(player, master);
		return;
	}
	id = getoid(master);
	order1 = player->get_fam_order();
	order2 = master->get_fam_order();

	if (player->get_save_2("master_hide"))
	{
		result = sprintf(" %s :\n Võ thuật của bổn môn tinh thâm, có sự biến hoá thần kỳ, công lực đoạt thiên tạo điạ. Tiểu đồ ngươi bình thường cần phải nỗ lực nghiên cứu tìm hiểu mới được. Không biết hôm nay ngươi tới tìm vi sư có chuyện gì?\n" ESC "Học tập kỹ năng\ntalk %x# skills\n", master->get_name(), id);
		if (order1 == order2 && order2 != 1)
			result += sprintf(ESC "Khiêu chiến\ntalk %x# apprentice.1\n", id);
		result += sprintf(ESC "Còn chỗ nào có thể mua được vũ khí của bổn môn phái?\ntalk %x# apprentice.11\n", getoid(master));
		result += sprintf(ESC "Mua trang bị của bổn môn phái\nlist %x#\n", getoid(master));
		//增加强化技能学习选项.
		if (!player->get_save("kjh_enhance_sk"))
		{
			if (player->get_level() >= 60 && (present("Thiên Ân Lệnh", player, 1, MAX_CARRY * 4)))
			{
				result += sprintf(ESC "申请学习强化门派技能\ntalk %x# apprentice.15\n", getoid(master));
			}
		}
		result += ESC "Quay về hướng của sư phụ mời nhấn\nCLOSE";
		send_user(player, "%c%s", ':', result);
		return;
	}

	if ((status = player->get_save_2("mastertask.type")) > 0)
	{
		if (status > sizeof(TaskName))
			return;
		if (status == 4 || status == 5 || status == 6 || status == 8 || status == 11 || status == 12)
			result = sprintf(" %s :\n Võ thuật của bổn môn tinh thâm, có sự biến hoá thần kỳ, công lực đoạt thiên tạo điạ. Tiểu đồ ngươi bình thường cần phải nỗ lực nghiên cứu tìm hiểu mới được. Không biết hôm nay ngươi tới tìm vi sư có chuyện gì?\n" ESC "Học tập kỹ năng\ntalk %x# skills\n", master->get_name(), id);
		else
			result = sprintf(" %s :\n Võ thuật của bổn môn tinh thâm, có sự biến hoá thần kỳ, công lực đoạt thiên tạo điạ. Tiểu đồ ngươi bình thường cần phải nỗ lực nghiên cứu tìm hiểu mới được. Không biết hôm nay ngươi tới tìm vi sư có chuyện gì?\n" ESC "Học tập kỹ năng\ntalk %x# skills\n" ESC "%s\ntalk %x# task_info\n", master->get_name(), id, TaskName[status - 1], id);
		if (order1 == order2 && order2 != 1)
			result += sprintf(ESC "Khiêu chiến\ntalk %x# apprentice.1\n", id);
		result += sprintf(ESC "Còn chỗ nào có thể mua được vũ khí của bổn môn phái?\ntalk %x# apprentice.11\n", getoid(master));
		if (order2 == 4)
			result += sprintf(ESC "Mua trang bị của bổn môn phái\nlist %x#\n", getoid(master));
		//增加强化技能学习选项.
		if (!player->get_save("kjh_enhance_sk"))
		{
			if (player->get_level() >= 60 && (present("Thiên Ân Lệnh", player, 1, MAX_CARRY * 4)))
			{
				result += sprintf(ESC "申请学习强化门派技能\ntalk %x# apprentice.15\n", getoid(master));
			}
		}
		result += ESC "Quay về hướng của sư phụ mời nhấn\nCLOSE";
		send_user(player, "%c%s", ':', result);
		return;
	}

	check_date(player);
	result = sprintf(" Võ thuật của bổn môn tinh thâm, có sự biến hoá thần kỳ, công lực đoạt thiên tạo điạ. Tiểu đồ ngươi bình thường cần phải nỗ lực nghiên cứu tìm hiểu mới được. Không biết hôm nay ngươi tới tìm vi sư có chuyện gì?\n" ESC "Học tập kỹ năng\ntalk %x# skills\n" ESC "Nhận nhiệm vụ\ntalk %x# quest\n", id, id);
	if (order1 == order2 && order2 != 1)
		result += sprintf(ESC "Khiêu chiến\ntalk %x# apprentice.1\n", id);
	result += sprintf(ESC "Còn chỗ nào có thể mua được vũ khí của bổn môn phái?\ntalk %x# apprentice.11\n", getoid(master));
	result += sprintf(ESC "Mua trang bị sơ cấp của bổn môn\nlist %x#\n", getoid(master));
	//增加强化技能学习选项.
	if (!player->get_save("kjh_enhance_sk"))
	{
		if (player->get_level() >= 60 && (present("Thiên Ân Lệnh", player, 1, MAX_CARRY * 4)))
		{
			result += sprintf(ESC "申请学习强化门派技能\ntalk %x# apprentice.15\n", getoid(master));
		}
	}
	result += ESC "Quay về hướng của sư phụ mời nhấn\nCLOSE";
	send_user(player, "%c%s", ':', result);
}

//检查、开放玩家学习强化技能.
void check_enhance_sk(object player, object master)
{
	string name1, name2;
	object item;

	name1 = player->get_fam_name();
	name2 = master->get_fam_name();

	if (player->get_save("kjh_enhance_sk"))
	{
		send_user(player, "%c%s", ':', "你不是已经可以学习强化门派技能了吗!!\n" + ESC + "Rời khỏi\nCLOSE");
		return;
	}

	if (!(item = present("Thiên Ân Lệnh", player, 1, MAX_CARRY * 4)) || player->get_level() < 60 || (name1 == "" || name1 != name2 || player->get_fam_master() != master->get_name()))
	{
		send_user(player, "%c%s", ':', "学习本门派的强化技能必须满足以下条件:\n1. 自身门派必须与所学技能门派对应一致；\n2. 玩家当前等级必须≥60；\n3. 玩家必须有强化门派技能学习信物——天恩令!\n你当前不满足以上条件，申请未通过!\n" + ESC + "Rời khỏi\nCLOSE");
		return;
	}
	else if (item->remove_from_user())
	{
		destruct(item);
		player->set_save("kjh_enhance_sk", 1);
		send_user(player, "%c%s", ':', "你已经可以学习本门派的强化技能了!你可以直接关闭当前对话框，重新点击Học kĩ năng就可以了!\n" + ESC "Rời khỏi\nCLOSE");
		send_user(player, "%c%s", '!', "你申请学习强化门派技能的请求已经通过");
	}
}

void do_quest(object player, object master)
{
	int date, type, level, size, p, x, y, z;
	string npc, cQue, *cTmp;
	object target, item;
	string *Masters;

	if (player->get_save_2("master_hide"))
		return;
	if (player->get_save_2("mastertask.type"))
		return;
	if (gone_time(player->get_save_2("master.questtime")) < 180)
	{
		send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), master->get_name() + ":\n    Đều do Vi sư không tính ra năng lực của ngươi, ngươi hãy cho ta chút thời gian suy nghĩ để ta giao một Nhiệm vụ thích hợp cho ngươi !");
		return;
	}
	player->set_save_2("master.questtime", time());

	type = "sys/task/quest1"->get_random_task(player);
	if (is_god(player))
	{
		if (player->get("lb"))
			type = player->get("lb");
	}
	player->set("master.type", type);

	switch (type)
	{
	case 1:
		level = player->get_level();
		cTmp = "/sys/task/quest1"->get_random_quest2(level);
		player->set("master.targetname", cTmp);
		cQue = sprintf("%s:\nHiện này thiên hạ đại loạn, yêu ma quỷ quái hoành hành bốn bể.  Nghe nói ở %s , ngươi hãy thay ta đi bắt một con về đây !\n", master->get_name(), cTmp[1]);
		break;
	case 2:
		level = player->get_level();
		if (level < 20)
			x = NPC_ENERGY_D->get_exp_bonus(level) * 10;
		else if (level < 30)
			x = NPC_ENERGY_D->get_exp_bonus(level) * 15;
		else
			x = NPC_ENERGY_D->get_exp_bonus(level) * 20;
		player->set("master.exp", x);
		cQue = sprintf("%s:\nNgười học nghệ thuật chỉ cần chuyên tâm luyện tập, kỹ thuật ngày càng tinh xảo. Cứ tiếp tục kiên trì, sẽ lãnh hội được hết tinh hoa võ thuật của bổn môn, sư phụ muốn ngươi nâng cao %d kinh nghiệm chiến đấu .Muốn đạt đến đỉnh cao tinh hoa của võ học, điều quan trọng nhất là phải thể hiện ra năng lực, mà năng lực thi có được từ sự khổ luyện mà ra. Sư phụ muốn ta ra ngoài rèn luyện, để có thể nâng cao võ công của mình.\n", master->get_name(), x);
		break;
	case 3:
		level = player->get_level();
		if (level < 20)
			x = 10;
		else if (level < 30)
			x = 15;
		else
			x = 20;
		player->set("master.pot", x);
		cQue = sprintf("%s:\nĐồ nhi, nếu muốn đạt đến đỉnh cao trong võ học, ngươi phải biết khổ luyện cho nhiều.Vi sư hy vọng ngươi ra ngoài vừa đi vừa khổ luyện.\n", master->get_name());
		break;
	case 4:
		player->delete ("master.targetname");
		cQue = sprintf("%s:\n%s do ngày thường không lưu ý kĩ, có một số vật phẩm dự trữ trong bổ môn rõ ràng là không đủ, nếu như không giải quyết kịp thời, sẽ mang lại rất nhiều phiền phức. Nhưng lúc này lại thiếu người, ngươi hãy đến hỏi thử xem\n", master->get_name(), "/sys/task/quest1"->get_manager_name(player->get_fam_name()));
		break;
	case 5:
		player->delete_save_2("mastertask.targetname");
		cQue = sprintf("%s:\nTheo bẩm báo của %s gần đây, một số vật phẩm mà bổn môn cần dùng đã được chuyển đến, ngươi hãy qua đó hỏi thăm tình hình cụ thể, xem có thể giúp đỡ được gì không\n", master->get_name(), "/sys/task/quest1"->get_manager_name(player->get_fam_name()));
		break;
	case 6:
		size = sizeof(locatename);
		p = random(size);
		if (locatename[p] == master->get_fam_name())
			p--;
		if (p < 0)
			p = 0;
		npc = mastername[p];
		player->set("master.targetname", npc);
		Masters = locatename - ({master->get_fam_name()});
		player->set("master.targetcity", locatename[p]);
		cQue = sprintf("%s:\nSư phụ bế quan tu hành đã mấy hôm rồi, cũng không biết tình hình mấy người bạn già của sư phụ như thế nào. Trước đây họ thường đến thăm viếng sư phụ, nếu lâu quá sư phụ không đi thăm hỏi lại họ thì cũng có phần thất lễ. Do đó, ngươi hãy thay mặt ta đi thăm hỏi %s %s.\n", master->get_name(), locatename[p], npc);
		break;
	case 7:
		cQue = sprintf("%s:\nGần đây sư phụ muốn thử luyện chế một loại đơn dược, nhưng luyện chế loại đơn dược này cần phải có linh dược làm dược dẫn, Nghe nói chỉ có Vân Du Thương Nhân mới có loại linh dược này. Ngươi hãy thử đi tìm Vân Du Thương Nhân, nếu như tìm được ông ta thì xin ông ta loại linh dược này\n", master->get_name());
		break;
	case 8:
		size = sizeof(cityname);
		npc = cityname[random(size)];
		player->set("master.targetname", npc);
		cQue = sprintf("%s:\nỞ %s Gần đây Quản Ngục Quan %s có gửi thư đến, nói tình hình trị an trong nước ngày càng nghiêm trọng, khẩn cầu mấy đệ tử giỏi của bổn môn phái đến giúp đỡ giữ trị an. Ngươi hãy đến đó trợ giúp việc giải quyết vấn đề rối loạn trị an ở đó\n", master->get_name(), npc, npc);
		break;
	case 9:
		z = get_z(master);
		if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
			return 0;
		x = (p % 1000000) / 1000;
		y = p % 1000;
		player->set("mastertask.targetxy", x * 1000 + y);
		x = x + random(60) - 30;
		y = y + random(60) - 30;
		if (x < 1)
			x = 1;
		if (y < 1)
			y = 1;
		player->set("mastertask.targetxy1", x * 1000 + y);
		cQue = sprintf("%s:\nCó đệ tự bẩm báo với sư phụ, gần đây trong sư môn (%d,%d) xuất hiện nhân vật khả nghi, Ngươi hãy đi điều tra, và ta phát hiện ra một lũ cẩu tặc, ta phải dạy cho chúng một bài học, nếu không thì uy tín của bổn môn để ở đâu ?\n", master->get_name(), x, y);
		break;
	case 10:
	default:
		Masters = schoolname - ({player->get_fam_name()});
		size = sizeof(Masters);
		npc = Masters[random(size)];
		player->set("master.targetname", npc);
		cQue = sprintf("%s:\n%s môn phái đã sai người đến đây phát thư mời đệ tử của bổn môn ra tỷ thí võ công, tự bổ sung vào những điểm khiếm khuyết của võ học, sư phụ lệnh cho ngươi đi, ngươi không thể bỏ lỡ cơ hội lần này, thời gian có hạn, ngươi phải lập tức đi ngay.\n", master->get_name(), npc);
		break;
		/*	case 11:	
		cQue = sprintf("%s:\nBổn môn %s dạo này như bị tâm thần, chắc bởi vì tài chính có vấn đề, ngươi hãy đi hỏi thử xem !\n", master->get_name(), "/sys/task/quest1"->get_manager_name(player->get_fam_name()) ) ;
		break;
	case 12:
		size = sizeof(cityname);
		npc = cityname[random(size)];
		player->set("master.targetname",npc);
		cQue =sprintf("%s:\nVừa lấy được %s lá thư cầu cứu khẩn cấp, ngươi hãy đi tìm %s Tổng Quản Vương Phủ và lập tức giải quyết khó khăn.\n", master->get_name(), npc, npc ) ;
		break;
	case 13:
	default:
		size = sizeof(cityname);
		npc = cityname[random(size)];
		player->set("master.targetname",npc);
		cQue = sprintf("%s:\nSư phụ vừa nãy nhận được một lá thư từ %s Tổng Quản Vương Phủ , trong thư nói rằng đêm qua có thích khách lẻn vào %s Vương phủ muốn ám sát %s Vương gia. Dù cuối cùng ám sát thất bại, Vương gia cũng không hề bị thương, nhưng thích khách lại bỏ trốn mất. Tổng Quản hy vọng chúng ta giúp ông ấy bắt tên thích khách, để tránh hậu họan. Khi phát hiện mục tiêu thì giết không tha.\n", master->get_name(), npc,npc, npc ) ;
		break;*/
	}

	if (!stringp(cQue))
		return;
	cQue += sprintf("Số lần nhiệm vụ đã tích lũy của ngày hôm nay: %d lần\n" ESC "Tiếp nhận \ntalk %x# accept_quest\n" + ESC "Từ chối\ntalk %x# apprentice.13\n", player->get_save_2("mastertask.count"), getoid(master), getoid(master));
	send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), cQue);
}

void check_random_bonus(object player)
{
	string *book, name, result;
	int size, date, rate;
	object obj;
	/*	if (MAIN_D->get_host_type()==1||MAIN_D->get_host_type()==1000)
	{
		obj = new("item/sell/0021");
		date = obj->move(player,-1);
		if ( !date )
			destruct(obj);
		else
		{
			send_user( player, "%c%s", '!', "Bạn đạt được Tài Thần Phù !!" );
			obj->add_to_user(date);
		}
	}*/
	rate = random(10000);
	if (rate < 1000)
	{
		obj = new ("item/std/8000");
		date = obj->move(player, -1);
		if (!date)
			destruct(obj);
		else
		{
			send_user(player, "%c%s", '!', "Bạn đạt được Tàng Bảo Đồ");
			obj->add_to_user(date);
		}
	}
	else if (rate < 1100)
	{
		obj = new ("item/44/4488");
		date = "quest/pet"->get_drop_skill1();
		if (date)
			obj->set("special", sprintf("%d", date));
		date = obj->move(player, -1);
		if (!date)
			destruct(obj);
		else
		{
			send_user(player, "%c%s", '!', "Bạn đạt được Tinh Nguyên Đơn");
			obj->add_to_user(date);
		}
	}
	else if (rate < 1400)
	{
		name = player->get_fam_name();
		if (!name)
			return;
		book = FamilyBook[name];
		size = sizeof(book);
		if (size == 0)
			return;
		obj = new (sprintf("/item/95/%s", book[random(size)]));
		if (!obj)
			return;
		if (USER_INVENTORY_D->can_carry(player, obj) >= 1)
		{
			date = obj->move(player, -1);
			obj->add_to_user(date);
			result = sprintf("Ngươi đạt được %s.", obj->get_name());
			send_user(player, "%c%s", '!', result);
		}
		else
		{
			destruct(obj);
		}
		return;
	}
	else if (rate < 1405)
	{
		name = player->get_fam_name();
		if (!name)
			return;
		size = sizeof(giftname);
		if (size == 0)
			return;
		obj = new (sprintf("/item/96/%s", giftname[random(size)]));
		if (!obj)
			return;
		if (USER_INVENTORY_D->can_carry(player, obj) >= 1)
		{
			date = obj->move(player, -1);
			obj->add_to_user(date);
			result = sprintf("Ngươi đạt được %s.", obj->get_name());
			send_user(player, "%c%s", '!', result);
		}
		else
		{
			destruct(obj);
		}
		return;
	}
}

//检查每次增加经验和潜能处
void check_quest(object me, int point, int type)
{
	if (point < 0)
		return;
	if (!me->get_fam_name())
		return;
	if (type > 3 || type < 2)
		return;
	if (me->get_save_2("mastertask.type") != type)
		return;
	if (me->get_save_2("mastertask.status") == 99)
		return;
	me->add_save_2("mastertask.targetxy", point);
	if (me->get_save_2("mastertask.targetxy") >= me->get_save_2("mastertask.targetpic"))
	{
		me->set_save_2("mastertask.status", 99);

		if (type == 2)
			send_user(me, "%c%s", '!', sprintf("Nhiệm vụ " HIY " %d " NOR " hoàn thành, Rèn luyện xong hãy trở về bẩm báo với Sư Phụ.\n", me->get_save_2("mastertask.time") + 1));
		else
			send_user(me, "%c%s", '!', sprintf("Nhiệm vụ " HIY " %d " NOR " hoàn thành,Du lịch xong hãy trở về bẩm báo với Sư Phụ.\n", me->get_save_2("mastertask.time") + 1));
	}
	send_task_desc(me, 1);
}

// 函数:Thu mua 掌门及王爷
int accept_object(object who, object player, object obj)
{
	string name1, name2, result;
	int date, level, time, exp, pot, type, size;
	object gift;

	name1 = who->get_fam_name();
	name2 = player->get_fam_name();

	player->to_front_eachother(who);
	type = player->get_save_2("mastertask.type");
	level = player->get_level();
	time = player->get_save_2("mastertask.time");
	if (type == 6 && player->get_save_2("mastertask.giftname") == obj->get_name() && player->get_save_2("mastertask.targetname") == who->get_name() && player->get_save_2("mastertask.status") == 2)
	{
		player->set_save_2("mastertask.giftname", 0);
		//有50%的机率获得特殊物品
		if (!random(2))
		{
			size = sizeof(giftname);
			name1 = giftname[random(size)];
			gift = new (sprintf("/item/95/%s.c", name1));
		}
		else
		{
			gift = new ("/item/44/4488");
		}
		if (gift)
		{
			if (USER_INVENTORY_D->can_carry(player, gift) >= 1)
			{
				date = gift->move(player, -1);
				gift->add_to_user(date);
				if (player->get_gender() == 1)
					result = sprintf("%s\nTiểu huynh đệ xem ra tiền đồ cũng khá, cuốn sách ta lưu trữ cũng ko tác dụng nhiều, ta sẽ đưa ngươi đi.", who->get_name());
				else
					result = sprintf("%s\nTiểu cô nương xem ra tiền đồ cũng khá, cuốn sách ta lưu trữ cũng ko tác dụng nhiều, ta sẽ đưa ngươi đi.", who->get_name());
				send_user(player, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			}
			else
			{
				if (player->get_gender() == 1)
					result = sprintf("%s\nTiểu huynh đệ xem ra tiền đồ cũng khá, ta vốn định tặng ngươi bảo vật nhưng suy nghĩ lại thôi thì không tặng nữa.", who->get_name());
				else
					result = sprintf("%s\nTiểu cô nương xem ra tiền đồ cũng khá, ta vốn định tặng ngươi bảo vật nhưng suy nghĩ lại thôi thì không tặng nữa.", who->get_name());
				send_user(player, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				destruct(gift);
			}
		}
		else
			send_user(player, "%c%c%w%s", ':', 3, who->get_char_picid(), who->get_name() + ":\n    Hà hà, hậu bối bây giờ đúng là hiểu chuyện đời, vậy ta không khách khí nhận vậy.");
		return 1;
	}

	return 0;
}

// 函数:司库接收物品
int accept_object2(object who, object player, object obj)
{
	string name1, name2, result;
	int date, level, time, exp, pot, type, size;
	object gift;

	name1 = who->get_fam_name();
	name2 = player->get_fam_name();

	player->to_front_eachother(who);
	if (name1 != name2)
		return 0;
	type = player->get_save_2("mastertask.type");
	if (type != 4)
		return 0;
	name1 = player->get_save_2("mastertask.targetname");
	name2 = obj->get_name();
	if (name1 == name2 || "男装" + name2 == name1 || "女装" + name2 == name1)
	{
		//		if ( type == 5 )
		//		{
		//			player->add_save_2("mastertask.targetxy",-1*obj->get_amount());
		//			if ( player->get_save_2("mastertask.targetxy") > 0 )
		//			{
		//				send_user( player,"%c%c%w%s", ':',3,who->get_char_picid(),sprintf("%s:\n    谢谢啊，这正是我需要的.请继续努力哦～", who->get_name() ) );
		//				return 1;
		//			}
		//		}
		if (obj->is_combined())
			obj->add_amount(-1);
		else
		{
			obj->remove_from_user();
			destruct(obj);
		}
		task_bonus(player, who);
		send_user(player, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf(" %s :\n Được lắm, đã tìm được đồ về nhanh như vậy, xem ra ta không lựa chọn sai người! Ta đã bẩm báo với sư phụ về công lao của con, đây là phần thưởng sư phụ cho con.", who->get_name()));
		return -99;
	}
	else
	{
		send_user(player, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s:\n    Vật phẩm này không phải là thứ ta yêu cầu ngươi đi mua,làm việc phải cẩn thận chứ không sư phụ biết sẽ trách tội ngươi đấy.", who->get_name()));
		return 0;
	}
	return 0;
}

// 帮派司库，王府总管Nhận财物

int accept_money(object who, object player, int gold)
{
	string name, gift;
	if (gold < 500)
		return 0;
	if (who->get_city_name())
		if (who->get_fam_name() != "" && who->get_fam_name() != player->get_save_2("mastertask.targetcity"))
			return 0;
	if (who->get_city_name() != "" && who->get_city_name() != player->get_save_2("mastertask.targetcity"))
		return 0;
	if (sizeof(who->get_fam_name()))
		name = "Bổn Môn Chưởng Môn";
	else
		name = "Vương Gia";
	if (player->get_save_2("mastertask.type") == 6 && player->get_save_2("mastertask.status") <= 2)
	{
		gift = COLLECT_FILE->get_collect_name();
		player->set_save_2("mastertask.giftname", gift);
		if (player->get_gender() == 1)
			send_user(player, "%c%s", ':', sprintf("%s:\nHa ha, vị tiểu huynh đệ này thật thú vị, ta nói riêng cho ngươi biết %s đang tìm " HIR " %s " NOR ".", who->get_name(), name, gift));
		else
			send_user(player, "%c%s", ':', sprintf("%s:\nHa ha, vị tiểu cô nương này thật thú vị, ta nói riêng cho ngươi biết %s đang tìm " HIR " %s " NOR ".", who->get_name(), name, gift));
		player->set_save_2("mastertask.status", 2);
		return 1;
	}
	return 0;
}
//Thăm viếng
int do_look2(object player, object master)
{
	string result = "";
	if (player->get_save_2("mastertask.type") == 6 && master->get_name() == player->get_save_2("mastertask.targetname"))
	{
		if (player->get("master.type") != 69)
		{
			player->set("master.type", 69);
			send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), sprintf(" %s :\n Khà khà……sư phụ của con vẫn nhớ phái người đến viến thăm ta, thật là không tiếc khi kết bạn với người như vậy! Bảo sư phụ con hãy yên tâm! Ta rất khỏe, Nếu có thời gian ta muốn cùng với sư phụ con cùng Rèn luyện thuật đánh cờ!\n" ESC "Hoàn thành nhiệm vụ\nlook %x#\n", master->get_name(), getoid(master)));
		}
		else
		{
			player->set("master.type", 0);
			task_bonus(player, master);
		}
		return 1;
	}

	return 0;
}

//典狱官的 do_look
string do_look_quest6(object player, object master)
{
	string id;
	object npc;
	if (master->get_city_name() != player->get_save_2("mastertask.targetname"))
		return "";
	if (player->get_save_2("mastertask.type") != 8)
		return "";
	if (player->get_save_2("mastertask.status") == 1 && (!stringp(id = player->get_save_2("mastertask.target")) || (!objectp(npc = find_char(id))) || npc->get("user") != player->get_number()))
		return "";
	return sprintf(ESC "Hiệp trợ trị an\ntalk %x# accept_task\n", getoid(master));
}
//典狱官 Hiệp trợ trị an
void accept_task11(object player, object master)
{
	int status, x, y, z, p, level;
	object map, npc, *target;
	string name;

	if (player->get_save_2("mastertask.type") == 8 && master->get_city_name() == player->get_save_2("mastertask.targetname"))
	{

		status = player->get_save_2("mastertask.status");
		switch (status)
		{
		case 0: //刚接到 nhiệm vụ
			player->set_save_2("mastertask.status", 1);
			z = get_z(master);
			if (!objectp(map = get_map_object(z)) || !map->is_scene())
				return;
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				return 0;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			level = player->get_level();
			npc = new ("npc/task/master_1");
			if (!npc)
				return 0;
			npc->set("level", level);
			npc->set_level(level);
			NPC_ENERGY_D->init_level(npc, level);
			npc->add_max_hp(npc->get_max_hp() / 10 * 3);
			npc->set_walk_speed(6);
			npc->set_attack_speed(15);
			npc->set_char_type(FIGHTER_TYPE_2);
			npc->set_char_picid(0251);
			npc->add_to_scene(z, x, y, 3);
			map->add_reset(npc); // 加入复位列表
			npc->set("user", player->get_number());
			npc->set_name(sprintf("Lưu Manh (%d)", player->get_number()));
			player->set_save_2("mastertask.target", sprintf("%x#", getoid(npc)));
			player->set_save_2("mastertask.targetxy", x * 1000 + y);
			player->set_save_2("mastertask.status", 1);
			x = x + random(60) - 30;
			y = y + random(60) - 30;
			if (x < 1)
				x = 1;
			if (y < 1)
				y = 1;
			player->set_save_2("mastertask.targetxy1", x * 1000 + y);
			send_user(player, "%c%s", ':',
					  sprintf("%s:\n    %s phái của nhiên bất phàm, cử ra người võ nghệ cao cường như vậy đến hỗ trợ.Tên tiểu tặc kia hắn thường lui tới ở (%d,%d). Có thể sử dụng Công Văn Truy Nã để tìm chính xác toạ độ của hắn.",
							  master->get_name(), player->get_fam_name(), x, y));
			send_task_desc(player, 0);
			break;
		case 1:
			x = player->get_save_2("mastertask.targetxy1");
			y = x % 1000;
			x = x / 1000;
			send_user(player, "%c%s", ':', sprintf("%s:\n    Nghe nói ở tên Tiểu tặc kia đang ở (%d,%d) vùng thường lui tới. Sử dụng Công Văn Truy Nã để tìm ra vị trí chính xác của hắn.", master->get_name(), x, y));
			break;
		case 2:
			send_user(player, "%c%s", ':', sprintf("%s:\nThật không hổ danh là thiếu niên anh hùng, nhanh thế đã hoàn thành nhiệm vụ!\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# accept_task", master->get_name(), getoid(master)));
			player->set_save_2("mastertask.status", 99);
			break;
		case 99:
			task_bonus(player, master);
			break;
		default:
			return;
		}
		return;
	}
	return;
}

//Môn phái tỷ thýĐệ tử的 do_look
int do_look_quest8(object player, object master)
{
	int status, family, p, x, y, z, level, d, pic;
	string result, cityname;
	object npc, map, cityobj;
	if (player->get_save_2("mastertask.type") == 10)
	{
		status = player->get_save_2("mastertask.status");
		if (status != 99 && master->get_fam_name() == player->get_save_2("mastertask.targetname"))
		{
			result = sprintf("%s\n    Ngươi chính là đệ tử của %s phái tới để tỷ thý hả ? Nhìn ngươi bộ dạng gầy yếu chắc ko đánh nổi ai..Ta nói trước ta không nương tay đâu đấy !\n" ESC "Lập tức Khiêu chiến\ntalk %x# accept_quest\n" ESC "Ta phải chuẩn bị đã\nclose\n", master->get_name(), player->get_fam_name(), getoid(master));
			send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), result);
			return 1;
		}
	}
	//	if (player->get_save_2("masterfight.status")==1 && master->get_fam_name()==player->get_fam_name())
	//	{
	//		result = sprintf("%s:\nĐệ tử%s，前来向师叔请教，不知师叔是否在内？\n\n%s:\n那好，你进去吧.",
	//			player->get_name(), player->get_name(), player->get_fam_name());
	//		send_user( player, "%c%s", ':', result );
	//		if( ( z = find_map_flag(1000, 2999, 0) ) <= 0 ) return 1;
	//		x = ( p % 1000000 ) / 1000;  y = p % 1000;
	//		level = player->get_save_2("masterfight.targetxy");
	//		npc = new( "npc/90/app_fight" );
	//		if (!npc) return 0;
	//		npc->set("level", level);
	//		switch(master->get_fam_name())
	//		{
	//		case "Đào Hoa Nguyên":
	//		        family = 10;
	//		        d = 891;
	//		        cityname = "Đào Hoa Đảo";
	//		        break;
	//		case "Thục Sơn":
	//		        family = 20;
	//		        d = 892;
	//		        cityname = "Thục Lĩnh Phong";
	//		        break;
	//		case "Cấm Vệ Quân":
	//		        family = 30;
	//		        d = 893;
	//		        cityname = "Doanh trại Cấm vệ quân";
	//		        break;
	//		case "Đường Môn":
	//		        family = 40;
	//		        d = 894;
	//		        cityname = "Đường Môn Mật Thất";
	//		        break;
	//		case "Mao Sơn":
	//		        family = 50;
	//		        d = 895;
	//		        cityname = "Quỷ Môn Phủ";
	//		        break;
	//		case "Côn Luân":
	//		        family = 60;
	//		        d = 896;
	//		        cityname = "Côn Luân Tiên Cảnh";
	//		        break;
	//		default:
	//		        family = 70;
	//		        d = 897;
	//		        cityname = "Tử Vong Đầm Lầy";
	//		        break;
	//		}
	//                init_virtual_map(z, d);
	//                map = new( NEWBIE );
	//                map->set_client_id(d);
	//                map->set_owner(player);
	//                set_map_object( map, map->set_id(z) );
	//                map->set_name(cityname);
	//                p = get_jumpin(z, 1);
	//		NPC_ENERGY_2_D->init_family(npc, family, level, -1);
	//		npc->set_fam_name(master->get_fam_name());
	//		npc->set_char_type(FIGHTER_TYPE_2);
	//		npc->set_name(sprintf("%s的师叔", player->get_name()));
	//		npc->init_pic(npc, family);
	//		x = p/1000, y = p % 1000;
	//		npc->add_to_scene(z, x, y, 3);
	//		npc->set("user", player->get_number());
	//                player->set_2("masterfight.x", get_x(player));
	//		player->set_2("masterfight.y", get_y(player));
	//		player->set_2("masterfight.z", get_z(player));
	//		if( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) )
	//                {
	//                        x = p/1000, y = p % 1000;
	//                        player->add_to_scene(z, x, y, 3);
	//
	//                }
	//		return 1;
	//	}
	TASK_APPRENTICE_D->do_look(player, master);
}
//Môn phái tỷ thý
void accept_quest8(object player, object master, string arg)
{
	int status, family, p, x, y, z, level, d, pic;
	string result, cityname, id;
	object npc, map, cityobj;
	if (player->get_save_2("mastertask.type") != 10)
		return;
	status = player->get_save_2("mastertask.status");
	if (master->get_fam_name() == player->get_save_2("mastertask.targetname"))
	{
		if (status != 99)
		{
			player->set_save_2("mastertask.status", 1);
			if (stringp(id = player->get_save_2("mastertask.target")) && (npc = find_char(id)) && npc->get("user") == player->get_number())
			{
				player->set_2("mastertask.x", get_x(player));
				player->set_2("mastertask.y", get_y(player));
				player->set_2("mastertask.z", get_z(player));
				player->add_to_scene(get_z(npc), get_x(npc), get_y(npc), 3);
				npc->set_hp(npc->get_max_hp());
				npc->set_mp(npc->get_max_mp());
				npc->set_char_type(FIGHTER_TYPE_2);
				SAY_CMD->say(npc, npc->get_name() + ", tiến đến lãnh giáo");
				return;
			}
			if ((z = find_map_flag(1000, 2999, 0)) <= 0)
				return;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			level = player->get_level();
			npc = new ("npc/task/master_5");
			if (!npc)
				return;
			npc->set("level", level);
			switch (master->get_fam_name())
			{
			case "Đào Hoa Nguyên":
				family = 10;
				d = 891;
				cityname = "Đào Hoa Đảo";
				break;
			case "Thục Sơn":
				family = 20;
				d = 892;
				cityname = "Thục Lĩnh Phong";
				break;
			case "Cấm Vệ Quân":
				family = 30;
				d = 893;
				cityname = "Doanh trại Cấm vệ quân";
				break;
			case "Đường Môn":
				family = 40;
				d = 894;
				cityname = "Đường Môn Mật Thất";
				break;
			case "Mao Sơn":
				family = 50;
				d = 895;
				cityname = "Quỷ Môn Phủ";
				break;
			case "Côn Luân":
				family = 60;
				d = 896;
				cityname = "Côn Luân Tiên Cảnh";
				break;
			default:
				family = 70;
				d = 897;
				cityname = "Tử Vong Đầm Lầy";
				break;
			}
			init_virtual_map(z, d);
			map = new (NEWBIE);
			map->set_client_id(d);
			set_map_object(map, map->set_id(z));
			map->set_name(cityname);
			map->set_owner(player);
			p = get_jumpin(z, 1);
			npc->set_level(level);
			NPC_ENERGY_D->init_level(npc, level);
			npc->add_max_hp(npc->get_max_hp() * 3);
			npc->add_dp(npc->get_dp() / 2);
			npc->add_pp(npc->get_pp() / 2);
			npc->set_walk_speed(3);
			npc->set_attack_speed(10);
			npc->set_fam_name(master->get_fam_name());
			npc->set_char_type(FIGHTER_TYPE_2);
			npc->set_name(sprintf("%s đệ tử", master->get_fam_name()));
			npc->init_pic(npc, family);
			x = p / 1000, y = p % 1000;
			npc->add_to_scene(z, x, y, 3);
			map->add_reset(npc); // 加入复位列表
			npc->set("user", player->get_number());
			player->set_save_2("mastertask.target", sprintf("%x#", getoid(npc)));
			player->set_2("mastertask.x", get_x(player));
			player->set_2("mastertask.y", get_y(player));
			player->set_2("mastertask.z", get_z(player));
			if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
			{
				x = p / 1000, y = p % 1000;
				player->add_to_scene(z, x, y, 3);
			}
			SAY_CMD->say(npc, npc->get_name() + ", tiến đến lãnh giáo");
			return;
		}
	}
}

//帮派司库的 do_look
int do_look_quest9(object player, object master)
{
	string name1, name2, result = "", *nTmp;
	object obj, *inv;
	int p, level, i, size, type;
	name1 = player->get_fam_name();
	name2 = master->get_fam_name();
	// 取消多余的Ngân Phiếu
	obj = present("Ngân Phiếu", player, 1, MAX_CARRY * 4);
	if (objectp(obj) && player->get_save_2("mastertask.type") != 11)
	{
		send_user(player, "%c%s", '!', "你身上的Ngân Phiếu消失了.");
		obj->remove_from_user();
		destruct(obj);
	}

	if (player->get_save_2("mastertask.type") == 6)
	{
		if (player->get_save_2("mastertask.status") == 0 && player->get_save_2("mastertask.targetcity") == master->get_fam_name())
		{
			player->set_save_2("mastertask.status", 1);
			send_user(player, "%c%s", ':', sprintf("%s:\nBổn môn Chưởng Môn không những võ nghệ siêu quần, hơn nữa lại còn rất thích thưởng thức tranh!\n" ESC "Cho hắn 500 lượng\ngive %x# 0#0 0#0 0#0 0#0 0#0 0#0 $500\n" ESC "Ta không có hứng thứ biết\nclose", master->get_name(), getoid(master)));
			return 1;
		}
	}
	if (name1 == "" || name1 != name2)
	{
		TASK_APPRENTICE_D->do_look(player, master);
		return 1;
	}
	if ((type = player->get_save_2("mastertask.type")) == 4)
	{
		if (player->get_save_2("mastertask.status") == 0)
		{
			result = TASK_APPRENTICE_D->get_chat(player, master);

			result = result + "\n" ESC + sprintf("Thu mua\ntalk %x# accept_task.1\n", getoid(master));
			send_user(player, "%c%s", ':', result);
			player->set("master.type", 4);
			//			player->delete("master.targetname");

			return 1;
		}
		else if (player->get_save_2("mastertask.status") < 99)
		{
			result = sprintf(" %s :\n Mua sắm vật phẩm, không nên mờ mắt, phải chú ý điểm đối ứng của nó. Sau khi lựa chọn đầy đủ rồi thì dùng phương thức cho (nhanh chóng nhấn ALT+G) để đưa cho ta là được rồi\n" ESC "Rời khỏi\nCLOSE\n",
							 master->get_name());
			send_user(player, "%c%s", ':', result);
			player->set("master.type", 5);
			return 1;
		}
		return 1;
	}
	else if (type == 5)
	{
		if (player->get_save_2("mastertask.status") == 0)
		{
			result = TASK_APPRENTICE_D->get_chat(player, master);

			result = result + "\n" ESC + sprintf("Thu thập\ntalk %x# accept_task.2\n", getoid(master));
			send_user(player, "%c%s", ':', result);
			player->set("master.type", 5);
			return 1;
		}
		else if (player->get_save_2("mastertask.status") < 99)
		{
			task_finish9(player, master);
			return 1;
		}
		return 1;
	}
	else if (type == 11)
	{
		name1 = player->get_name();
		name2 = master->get_name();
		if (player->get_save_2("mastertask.status") == 0)
		{
			if (present("Ngân Phiếu", player, 1, MAX_CARRY * 4))
			{
				send_user(player, "%c%s", '!', "您已经领了Ngân Phiếu了.");
				return 1;
			}
			obj = new ("/item/std/0003");
			obj->set_orgin_money(50000);
			obj->set_money(50000);
			if (USER_INVENTORY_D->can_carry(player, obj) < 1)
			{
				send_user(player, "%c%s", ';', "Lĩnh nhiệm vụ vật phẩm thất bại");
				destruct(obj);
				return 1;
			}
			if (p = obj->move(player, -1))
				obj->add_to_user(p);
			else
				destruct(obj);
			player->set_save_2("mastertask.status", 1);
			player->set_save_2("mastertask.targetxy", player->get_level() * 500 + 20000);
			send_user(player, "%c%s", ':', sprintf("%s:\n    Hey, bổn môn càng ngày chi tiêu càng nhiều, ta lệnh cho ngươi xuống núi kiếm chút tiền về cho bổn môn!", name2));
			send_user(player, "%c%s", '!', "你获得了通商Ngân Phiếu");
			player->set_save_2("mastertask.endtime", time() + 7200);
			player->add_exp(20);
			send_user(player, "%c%s", ';', "Bạn đạt được 20 điểm Kinh nghiệm");
			send_task_desc(player, 0);
			return 1;
		}
		else if (player->get_save_2("mastertask.status") == 1)
			send_user(player, "%c%s", ':', sprintf("%s:\n    Buôn bán ? Ngươi phải chú ý đến giá thị trường, vật phẩm chênh lệch giá thì nên trả giá cho đến cùng !", master->get_name()));
		else if (player->get_save_2("mastertask.status") == 98)
		{
			inv = all_inventory(player, 1, MAX_CARRY * 4);
			size = sizeof(inv);
			if (size > 0)
			{
				for (i = 0; i < size; i++)
				{
					if (inv[i]->get_item_type() == ITEM_TYPE_GOOD)
					{
						inv[i]->remove_from_user();
						destruct(inv[i]);
					}
				}
			}
			obj = present("Ngân Phiếu", player, 1, MAX_CARRY * 4);
			if (obj->get_money() - obj->get_orgin_money() < player->get_save_2("mastertask.targetxy"))
			{
				send_user(player, "%c%s", ':', sprintf("%s:\nSố lượng Ngân Phiếu trên người không đúng....", master->get_name()));
				return 1;
			}
			obj->remove_from_user();
			destruct(obj);
			player->set_save_2("mastertask.status", 99);
			send_user(player, "%c%s", ':', sprintf("%s:\nHaha, ta quả nhiên không nhìn lầm người, ngươi làm thương nhân rất là tài đó !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#\n", master->get_name(), getoid(master)));
			return 1;
		}
		else if (player->get_save_2("mastertask.status") == 99)
		{
			task_bonus(player, master);
		}
		return 1;
	}
	TASK_APPRENTICE_D->do_look(player, master);
}
//王府总管的 do_look
int do_look_quest10(object player, object master)
{
	string name1, npc, result = "";
	string *Citys;
	object target, map;
	int p, status, size, x, y, z, level, i, x1, y1;
	string *targetnpc;
	name1 = master->get_city_name();
	if (player->get_save_2("mastertask.type") == 6)
	{
		if (player->get_save_2("mastertask.status") == 0 && player->get_save_2("mastertask.targetcity") == master->get_city_name())
		{
			player->set_save_2("mastertask.status", 1);
			send_user(player, "%c%s", ':', sprintf("%s:\nNhà của Vương Gia ta hùng tài đại lượt, ta có hứng thú đi dạo rồi tìm xem có món nào mới đem về cho Vương Gia\n" ESC "Cho hắn 500 lượng\ngive %x# 0#0 0#0 0#0 0#0 0#0 0#0 $500\n" ESC "Ta không có hứng thứ biết\nclose", master->get_name(), getoid(master)));
			return 1;
		}
		return 0;
	}
	if (player->get_save_2("mastertask.type") == 12)
	{
		if (player->get_save_2("mastertask.targetname") != master->get_city_name())
			return 0;
		status = player->get_save_2("mastertask.status");
		if (status == 0)
		{
			Citys = cityname - ({name1});
			size = sizeof(Citys);
			npc = Citys[random(size)];
			player->set_save_2("mastertask.giftname", npc);
			z = get_city_number(npc);
			if (!objectp(map = get_map_object(z)) || !map->is_scene())
				return;
			target = new ("/npc/task/master_3.c");
			if (!target)
				return 0;
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				return 0;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			x1 = x + random(60) - 30;
			y1 = y + random(60) - 30;
			if (x1 < 1)
				x1 = 1;
			if (y1 < 1)
				y1 = 1;
			send_user(player, "%c%s", ':', sprintf("%s:\n    Không gạt ngươi, có một vị quan lớn không hiểu dạo này cứ trốn tránh ra ngoài thành \nTa Nghe nói ở hắn đang chạy trốn ở %s (%d,%d). Thật là đáng lo ngại nếu hắn tiết lộ cơ mật quốc gia.Ngươi hãy đi bắt hắn về đây !", master->get_name(), npc, x1, y1));
			level = player->get_level();
			target->set("level", level);

			target->set_level(level + 5);
			NPC_ENERGY_D->init_level(target, level + 5);
			target->add_max_hp(target->get_max_hp() * 3);
			target->add_dp(target->get_dp() / 2);
			target->add_pp(target->get_pp() / 2);
			target->set_walk_speed(3);
			target->set_attack_speed(10);

			target->set_char_type(FIGHTER_TYPE_2);
			target->set_char_picid(0053);
			target->set_name(sprintf("叛逃官员(%d)", player->get_number()));
			target->add_to_scene(z, x, y, 3);
			map->add_reset(target); // 加入复位列表
			target->set("user", player->get_number());
			targetnpc = ({sprintf("%x#", getoid(target))});

			player->set_save_2("mastertask.targetpic", "叛逃官员");
			player->set_save_2("mastertask.status", 1);
			player->set_save_2("mastertask.targetxy", x * 1000 + y);

			target = new ("/npc/task/master_3.c");
			if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
				return 0;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			level = player->get_level();
			target->set("level", level);
			target->set_level(level);
			NPC_ENERGY_D->init_level(target, level);
			target->add_max_hp(target->get_max_hp());
			target->set_walk_speed(4);
			target->set_attack_speed(15);
			target->set_char_type(FIGHTER_TYPE_2);
			target->set_name(sprintf("随从(%d)", player->get_number()));
			target->set_char_picid(0052);
			target->add_to_scene(z, x, y, 3);
			map->add_reset(target); // 加入复位列表
			target->set("user", player->get_number());
			targetnpc += ({sprintf("%x#", getoid(target))});
			target = new ("/npc/task/master_3.c");
			if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
				return 0;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			level = player->get_level();
			target->set("level", level);

			target->set_level(level);
			NPC_ENERGY_D->init_level(target, level);
			target->add_max_hp(target->get_max_hp());
			target->set_walk_speed(4);
			target->set_attack_speed(15);

			target->set_char_type(FIGHTER_TYPE_2);
			target->set_name(sprintf("随从(%d)", player->get_number()));
			target->set_char_picid(0052);
			target->add_to_scene(z, x, y, 3);
			map->add_reset(target); // 加入复位列表
			target->set("user", player->get_number());
			targetnpc += ({sprintf("%x#", getoid(target))});
			player->set_save_2("mastertask.target", implode(targetnpc, "|"));
			player->set_save_2("mastertask.targetxy1", x1 * 1000 + y1);
			player->add_exp(50);
			send_user(player, "%c%s", ';', "Bạn đạt được 50 điểm Kinh nghiệm");
			send_task_desc(player, 0);
			return 1;
		}
		else if (status == 4)
		{
			if (random(100) < 30)
			{
				player->set_save_2("mastertask.status", 99);
				send_user(player, "%c%s", ':', sprintf("%s:\nThật là tốt quá, ta thật lòng cám ơn ngươi.Ngươi hãy nhận chút lễ vật này !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#", master->get_name(), getoid(master)));
			}
			else
			{
				player->set_save_2("mastertask.status", 98);
				send_user(player, "%c%s", ':', sprintf("%s:\nThật là tốt quá, ta thật lòng cám ơn ngươi, ơn này mãi không quên !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#", master->get_name(), getoid(master)));
			}
			return 1;
		}
		else if (status == 98)
		{
			task_bonus(player, master);
			return 1;
		}
		else if (status == 99)
		{
			target = new (sprintf("/item/91/%d", 9160 + random(8)));
			if (USER_INVENTORY_D->can_carry(player, target) >= 1)
			{
				p = target->move(player, -1);
				target->add_to_user(p);
				task_bonus(player, master);
				return 1;
			}
			else
			{
				notify("Hành trang không đủ chỗ");
				destruct(target);
			}
			return 1;
		}
		else
		{
			send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), sprintf("%s:\n    Lòng như lửa đốt,Đại vương một ngày hỏi ta mấy lần tình hình tiến triển thế nào rồi ? Ta mong %s bớt lo lắng hơn !\n" ESC "Rời khỏi", master->get_name(), NPC_RANK_D->get_respect_2(player)));
			return 1;
		}
		return 0;
	}
	if (player->get_save_2("mastertask.type") == 13)
	{
		if (player->get_save_2("mastertask.targetname") != master->get_city_name())
			return 0;
		status = player->get_save_2("mastertask.status");
		if (status == 0)
		{
			Citys = cityname - ({name1});
			size = sizeof(Citys);
			npc = Citys[random(size)];

			player->set_save_2("mastertask.giftname", npc);
			z = get_city_number(npc);
			if (!objectp(map = get_map_object(z)) || !map->is_scene())
				return;
			target = new ("/npc/task/master_4.c");
			if (!target)
				return 0;
			if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
				return 0;
			x = (p % 1000000) / 1000;
			y = p % 1000;
			x1 = x + random(60) - 30;
			y1 = y + random(60) - 30;
			if (x1 < 1)
				x1 = 1;
			if (y1 < 1)
				y1 = 1;
			send_user(player, "%c%s", ':', sprintf("%s:\nTa bắt được tin tức, thích khách chạy tới %s liền mất dạng.Ta tin hắn vẫn chưa chạy xa, ắt hẳn là đang ở %s (%d,%d) .Mong rằng thiếu hiệp hãy cố gắng tìm được hắn !", master->get_name(), npc, npc, x1, y1));
			level = player->get_level();
			target->set("level", level);

			target->set_level(level);
			NPC_ENERGY_D->init_level(target, level + 2);
			target->add_max_hp(target->get_max_hp() * 4);
			target->add_dp(target->get_dp() / 5 * 4);
			target->add_pp(target->get_pp() / 5 * 4);
			target->set_walk_speed(3);
			target->set_attack_speed(10);
			target->set_char_type(FIGHTER_TYPE_2);
			target->set_char_type(FIGHTER_TYPE_2);
			target->set_name(sprintf("刺客首领(%d)", player->get_number()));
			target->set_char_picid(1000);
			target->add_to_scene(z, x, y, 3);
			map->add_reset(target); // 加入复位列表
			target->set("user", player->get_number());
			targetnpc = ({sprintf("%x#", getoid(target))});
			for (i = 0; i < 4; i++)
			{
				target = new ("/npc/task/master_4.c");
				if (!(p = efun::get_xy_point(z, IS_CHAR_BLOCK)))
					return 0;
				x = (p % 1000000) / 1000;
				y = p % 1000;
				level = player->get_level();
				target->set("level", level);
				target->set_level(level);
				NPC_ENERGY_D->init_level(target, level + 2);
				target->add_max_hp(target->get_max_hp());
				target->add_dp(target->get_dp() / 5);
				target->add_pp(target->get_pp() / 5);
				target->set_walk_speed(4);
				target->set_attack_speed(15);
				target->set_char_type(FIGHTER_TYPE_2);
				target->set_name(sprintf("蒙面刺客(%d)", player->get_number()));
				target->set_char_picid(202);
				target->add_to_scene(z, x, y, 3);
				map->add_reset(target); // 加入复位列表
				target->set("user", player->get_number());
				targetnpc += ({sprintf("%x#", getoid(target))});
			}
			player->set("targets", targetnpc);
			player->set_save_2("mastertask.status", 1);
			player->set_save_2("mastertask.targetxy", x * 1000 + y);
			player->set_save_2("mastertask.targetxy1", x1 * 1000 + y1);
			player->set_save_2("mastertask.target", implode(targetnpc, "|"));
			player->set_save_2("mastertask.x", 0);
			player->set_save_2("mastertask.y", 0);
			player->add_exp(50);
			send_user(player, "%c%s", ';', "Bạn đạt được 50 điểm Kinh nghiệm");
			send_task_desc(player, 0);
			return 1;
		}
		else if (status == 6)
		{
			if (random(100) < 50)
			{
				player->set_save_2("mastertask.status", 99);
				send_user(player, "%c%s", ':', sprintf("%s:\nThật sự là tin tức tốt, ta lập tức bẩm báo lại với Vương Gia. đây là chút lễ vật %s, mong ngươi nhận cho !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#", master->get_name(), NPC_RANK_D->get_respect_2(player), getoid(master)));
			}
			else
			{
				player->set_save_2("mastertask.status", 98);
				send_user(player, "%c%s", ':', sprintf("%s:\nThật sự là tin tức tốt, ta lập tức bẩm báo lại với Vương Gia. Chắc chắn Vương Gia sẽ rất cao hứng !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#", master->get_name(), getoid(master)));
			}
			return 1;
		}
		else if (status == 98)
		{
			task_bonus(player, master);
			return 1;
		}
		else if (status == 99) //九转丹或者混天丹、同等级的随机配方（三选一）
		{
			if (random(2))
				target = new ("/item/std/0086");
			else
				target = new ("/item/std/0087");
			if (USER_INVENTORY_D->can_carry(player, target) >= 1)
			{
				p = target->move(player, -1);
				target->add_to_user(p);
				task_bonus(player, master);
				return 1;
			}
			else
			{
				notify("Hành trang không đủ chỗ");
				destruct(target);
			}
			return 1;
		}
		else
		{
			send_user(player, "%c%c%w%s", ':', 3, master->get_char_picid(), sprintf("%s:\n    Đại Vương vừa rồi lại triệu ta yết kiến, hỏi xem đã bắt được thích khách hay chưa? ta mong %s đừng có lo lắng !\n" ESC "Rời khỏi", master->get_name(), NPC_RANK_D->get_respect_2(player)));
			return 1;
		}
		return 0;
	}
}

int get_city_number(string city)
{
	switch (city)
	{
	case "Tề Quốc":
		return 10;
	case "Hàn Quốc":
		return 20;
	case "Triệu Quốc":
		return 30;
	case "Ngụy Quốc":
		return 40;
	case "Tần Quốc":
		return 50;
	case "Sở Quốc":
		return 60;
	case "Yên Quốc":
		return 70;
	case "Chu Quốc":
		return 80;
	}
	return 1;
}

void set_seller_locate(int p)
{
	SellerLocate = p; // z * 1000000 + x * 1000 + y
}

int get_seller_locate()
{
	return SellerLocate;
}

// 函数:询问 Vân Du Thương Nhân所在
void do_info(object me, object who)
{
	int z;
	object map;
	string buf;

	if (SellerLocate == 0)
		return;
	z = SellerLocate / 1000000;
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	switch (random(3))
	{
	case 0:
		buf = "%s:\n    Nghe nói ở Vân Du Thương Nhân sẽ ở %s (%d,%d) một thời gian.";
		break;
	case 1:
		buf = "%s:\n    Có người nói đã gặp qua Vân Du Thương Nhân ở %s (%d,%d) , không biết là thật hay giả.";
		break;
	default:
		buf = "%s:\n    Vân Du Thương Nhân sẽ đi bán dạo một thời gian tại %s (%d,%d).";
		break;
	}
	buf = sprintf(buf, me->get_name(), map->get_name(), (SellerLocate % 1000000) / 1000, SellerLocate % 1000);
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), buf);
}

void accept_quest(object player, object master)
{
	int date, type, level, size, p, x, y, z;
	string npc;
	object target, map;
	string *Masters;

	check_date(player);
	type = player->get("master.type");
	if (!type)
		return;
	player->delete ("master.type");
	player->set_save_2("mastertask.type", type);
	player->set_save_2("mastertask.begintime", time());
	player->set_save_2("mastertask.endtime", time() + 3600);
	player->set_save_2("mastertask.status", 0);
	player->set_save_2("mastertask.target", 0);

	switch (type)
	{
	default:
		player->set_save_2("mastertask.type", 0);
		return;
	case 1:
		level = player->get_level();
		player->set_save_2("mastertask.targetname", player->get("master.targetname")[0]);
		player->set_save_2("mastertask.target", player->get("master.targetname")[1]);
		break;
	case 2:
		player->set_save_2("mastertask.targetpic", player->get("master.exp"));
		player->set_save_2("mastertask.targetxy", 0);
		break;
	case 3:
		player->set_save_2("mastertask.targetpic", player->get("master.pot"));
		player->set_save_2("mastertask.targetxy", 0);
		break;
	case 4:
	case 5:
	case 7:
		player->delete_save_2("mastertask.targetname");
		player->delete_save_2("mastertask.targetpic");
		player->set_save_2("mastertask.status", 0);
		break;
	case 6:
		player->set_save_2("mastertask.targetname", player->get("master.targetname"));
		player->set_save_2("mastertask.targetcity", player->get("master.targetcity"));
		break;
	case 8:
		player->set_save_2("mastertask.targetname", player->get("master.targetname"));
		break;
	case 9:
		z = get_z(master);
		if (!objectp(map = get_map_object(z)) || !map->is_scene())
			return;
		target = new ("/npc/task/master_2.c");
		if (!target)
			return;
		p = player->get("mastertask.targetxy");
		x = p / 1000;
		y = p % 1000;
		level = player->get_level();
		target->set("level", level);

		target->set_level(level);
		NPC_ENERGY_D->init_level(target, level);
		target->add_max_hp(target->get_max_hp() * 2);
		target->add_dp(target->get_dp() / 5 * 4);
		target->add_pp(target->get_pp() / 2);
		target->set_walk_speed(4);
		target->set_attack_speed(15);

		target->set_char_type(FIGHTER_TYPE_2);
		target->set_name(sprintf("Cuồng đồ (%d)", player->get_number()));
		target->set_char_picid(0200);
		target->add_to_scene(z, x, y, 3);
		map->add_reset(target); // 加入复位列表
		target->set("user", player->get_number());
		player->set_save_2("mastertask.target", sprintf("%x#", getoid(target)));
		player->set_save_2("mastertask.targetxy1", player->get("mastertask.targetxy1"));
		break;
	case 10:
		player->set_save_2("mastertask.targetname", player->get("master.targetname"));
		break;
		/*	case 11:
		player->set_save_2("mastertask.endtime", time()+7200);
		break;
	case 12:
		player->set_save_2("mastertask.targetname",player->get("master.targetname"));
		break;
	case 13:
		player->set_save_2("mastertask.targetname",player->get("master.targetname"));
		break;*/
	}
	//	player->set_save("cambayquest", 1);
	player->add_save_2("mastertask.count", 1);
	send_task_desc(player, 1);
}

void task_info(object player, object master)
{
	string name1, name2, result = "";
	int id, status, level, order1, order2, exp, pot, date;
	int type, x, y;
	object item, pet;

	name1 = player->get_fam_name();
	name2 = master->get_fam_name();
	if (name1 == "" || name1 != name2 || player->get_fam_master() != master->get_name())
		return;
	id = getoid(master);
	order1 = player->get_fam_order();
	order2 = master->get_fam_order();

	type = player->get_save_2("mastertask.type");
	if (type == 0)
		return;
	status = player->get_save_2("mastertask.status");

	if (status != 99)
	{
		if (type == 1)
		{
			if ((pet = USER_BEAST_D->have_beast(player, player->get_save_2("mastertask.targetname"))))
			{
				if (player->get("mastertask.finish")) //抓宠 nhiệm vụ完成
				{
					player->delete ("mastertask.finish");
					USER_BEAST_D->destruct_pet(player, pet);
					task_bonus(player, master);
					return;
				}
				else
				{
					player->set("mastertask.finish", 1);
					send_user(player, "%c%s", ':', sprintf("%s:\n    Đồ đệ làm việc nhanh nhẹ, vi sư cảm thấy vui mừng lắm. Đầy là vi sư cho ngươi hãy nhận đi !\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# task_info\n" ESC "Rời khỏi", master->get_name(), getoid(master)));
					return;
				}
			}
			else
				result = sprintf("%s:\n    Đồ nhi, ngươi hãy mở bảng kĩ năng, trong mục Chiến Đấu, sẽ nhìn thấy kĩ năng Bắt Bảo Thú.\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		}
		else if (type == 2)
			result = sprintf("%s:\n    Hoàn thành nhiệm ta giao hay không ? ngươi phải chú ý đến phương pháp nha !\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		else if (type == 3)
			result = sprintf("%s:\n    Võ học của ngươi không tiến triển nhanh như vi sư mong đợi. Ngươi hãy đi ra giết yếu quái hoặc sử dụng vật phẩm.\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		else if (type == 7)
			result = sprintf("%s:\n    Vân Du Thương Nhân bốn bể là nhà, ngươi hãy thử đi hỏi Chủ Tửu Lầu hoặc các người chơi khác thử xem.\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		else if (type == 9)
		{
			x = player->get_save_2("mastertask.targetxy1");
			y = x % 1000;
			x = x / 1000;
			if (status == 2)
			{
				player->set_save_2("mastertask.status", 99);
				result = sprintf("%s:\n    Đồ nhi làm việc tốt lắm !\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# task_info\n", master->get_name(), id);
				send_user(player, "%c%s", ':', result);
				return;
			}
			else
				result = sprintf("%s:\n    Sư phụ Nghe nói ở bổn môn gần đây có tên gian tặc xuất hiện tại sư môn (%d,%d), Ngươi hãy đi giáo huấn hắn cho sư phụ !\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), x, y, id);
		}
		else if (type == 10)
			result = sprintf("%s:\n    Tỷ thý là phải nhanh nhẹn tay chân và cặp mắt phải quan sát những chiêu thức của đối phương !\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		else
			result = sprintf("%s:\n    Bổn môn bát đại tinh thâm, đồ nhi ngươi phải cần học hỏi nhiều thứ mới giỏi được !\n" ESC "Học kĩ năng\ntalk %x# skills\n", master->get_name(), id);
		if (order1 == order2 && order2 != 1)
			result += sprintf(ESC "Khiêu chiến\ntalk %x# apprentice.1\n", id);
		result += sprintf(ESC "Làm sao có thể mua được vũ khí môn phái?\ntalk %x# apprentice.11\n", getoid(master));
		result += ESC "Thỉnh an Sư phụ\nCLOSE";
		send_user(player, "%c%s", ':', result);
		return;
	}
	switch (type)
	{
	case 9:
	case 10:
		send_user(player, "%c%s", ':', sprintf("%s:\n    Đồ đệ làm việc nhanh nhẹ, vi sư cảm thấy vui mừng lắm. Đầy là vi sư cho ngươi hãy nhận đi !", master->get_name()));
		break;
	case 7:
		name1 = player->get_save_2("mastertask.targetname");
		if (stringp(name1))
		{
			item = present(name1, player, 1, MAX_CARRY * 4);
			if (objectp(item))
			{
				item->remove_from_user();
				destruct(item);
			}
		}
		send_user(player, "%c%s", ':', sprintf("%s:\n    Đồ đệ làm việc nhanh nhẹ, vi sư cảm thấy vui mừng lắm. Đầy là vi sư cho ngươi hãy nhận đi !", master->get_name()));
		break;
	case 2:
	case 3:
		send_user(player, "%c%s", ':', sprintf("%s:\n    Làm rất là tốt, xem ra đây là sự rèn luyện cố gắng của ngươi.", master->get_name()));
		break;
		//	case 1:
		//		player->del_beast(player->get_save_2("mastertask.targetname"));
		//		send_user( player, "%c%s", ':', sprintf("%s:\n    Đồ đệ làm việc nhanh nhẹ, vi sư cảm thấy vui mừng lắm. Đầy là vi sư cho ngươi hãy nhận đi !", master->get_name() ) );
		//		break;
	default:
		return;
	}
	task_bonus(player, master);
	return;
}
//司库Nhận nhiệm vụ
void accept_task9(object player, object npc, string arg)
{
	int i, j, level, size;
	object obj, *inv, *nTask = ({}), item;
	string result, *nTmp, *nResult, result1;

	i = player->get_save_2("mastertask.type");
	j = player->get("master.type");
	if (j != 4 && j != 5 && j != 41 && j != 52 && j != 59)
		return;
	player->set("master.type", 0);
	i = to_int(arg);
	if (i == 1)
	{
		if (!stringp(result = player->get("master.targetname")) || !stringp(result1 = player->get("master.giftname")))
		{
			level = player->get_level();
			if (level < 30)
				j = 1;
			else if (level < 50)
				j = 2;
			else if (level < 70)
				j = 3;
			else
				j = 4;
			if (j > 1 && random(100) < 40)
				j--;
			nResult = "sys/task/quest1"->get_random_siku(j);
			result = nResult[0];
			result1 = nResult[1];
			player->set("master.targetname", result);
			player->set("master.giftname", result1);
		}
		player->set("master.type", 41);

		send_user(player, "%c%s", ':', sprintf("%s:\nNgươi hãy đi tới %s mua %s rồi trở về đưa cho ta. (Nhấn Alt+G là có thể giao vật phẩm)\n" ESC "Nhận\ntalk %x# accept_task.11\n" ESC "Cự tuyệt\ntalk %x# accept_task.10\n", npc->get_name(), result1, result, getoid(npc), getoid(npc)));
		return;
	}
	if (i == 2)
	{
		level = player->get_level();

		if (!stringp(player->get_save_2("mastertask.targetname")) || !stringp(player->get_save_2("mastertask.targetpic")))
		{
			nTmp = "sys/task/quest1"->get_random_quest3(level);
			player->set_save_2("mastertask.targetname", nTmp[0]);
			player->set_save_2("mastertask.targetpic", nTmp[1]);
		}
		player->set("master.type", 52);
		send_user(player, "%c%s", ':', sprintf("%s:\nTa nghe nói ở %s ,ngươi hãy đi thu thập về đây cho ta.\n" ESC "Nhận\ntalk %x# accept_task.21\n" ESC "Cự tuyệt\ntalk %x# accept_task.20\n", npc->get_name(), player->get_save_2("mastertask.targetpic"), getoid(npc), getoid(npc)));
	}
	if (i == 10 || i == 20)
	{
		item = player->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(player, "%c%c%s", 0x59, 1, sprintf("Ngươi muốn sử dụng Phù để tiêu trừ khoảng cách thời gian nhiệm vụ?\n" ESC "%c\n" ESC "use %x# master2\n", 1, getoid(item)));
			return;
		}
		clear_task(player, 1);
		player->set_save_2("master.questtime", time());
		return;
	}
	if (i == 11)
	{
		if (!stringp(player->get("master.targetname")) || !stringp(player->get("master.giftname")))
			return;
		player->set_save_2("mastertask.status", 1);
		player->set_save_2("mastertask.targetname", player->get("master.targetname"));
		player->set_save_2("mastertask.giftname", player->get("master.giftname"));
		player->delete ("master.targetname");
		player->delete ("master.giftname");
		player->add_exp(20);
		send_user(player, "%c%s", ';', "Bạn đạt được 20 điểm Kinh nghiệm");
		send_task_desc(player, 0);
		return;
	}
	else if (i == 21)
	{
		if (!stringp(player->get_save_2("mastertask.targetname")) || !stringp(player->get_save_2("mastertask.targetpic")))
			return;
		player->set_save_2("mastertask.status", 1);
		player->set_save_2("mastertask.targetxy", 5);
		player->add_exp(20);
		send_task_desc(player, 0);
		send_user(player, "%c%s", ';', "Bạn đạt được 20 điểm Kinh nghiệm");
		return;
	}
	else if (i == 29) //是否完成
	{
		inv = all_inventory(player, 1, MAX_CARRY * 4);
		size = sizeof(inv);
		j = 0;
		for (i = 0; i < size; i++)
		{
			if (inv[i]->get_name() == player->get_save_2("mastertask.targetname") && !inv[i]->get_no_give())
			{
				nTask += ({inv[i]});
				j += inv[i]->get_amount();
				if (j >= 5)
					break;
			}
		}
		if (j < 5)
			return;
		j = 5;
		for (i = 0, size = sizeof(nTask); i < size; i++)
		{
			if (nTask[i]->get_amount() <= j)
			{
				j -= nTask[i]->get_amount();
				nTask[i]->remove_from_user();
				destruct(nTask[i]);
			}
			else
			{
				nTask[i]->set_amount(nTask[i]->get_amount() - j);
				j = 0;
			}
			if (j == 0)
				break;
		}
		task_bonus(player, npc);
	}
}

void task_bonus(object player, object master)
{
	int level, exp, pot, knb, date, time, type, iCash, con, count, gold, p;
	string result, tmp = "", tmp2 = "", cQue;

	count = player->get_save_2("mastertask.count");
	type = player->get_save_2("mastertask.type");
	if (type == 0)
		return;
	level = player->get_level();
	time = player->get_save_2("mastertask.time") + 1;
	switch (time)
	{
	case 1..2:
		con = 1;
		break;
	case 3..4:
		con = 1;
		break;
	case 5..6:
		con = 1;
		break;
	case 7..8:
		con = 2;
		break;
	case 9..10:
		con = 3;
		break;
	}
	exp = level * 10 + time * time * level * 5;
	pot = level + 20 * time;
	gold = 500 + level * 6 * (time - 1);
	knb = 1;
	if (type == 1)
		iCash = 500;
	else if (type == 2)
		iCash = 250;
	else if (type == 3)
		iCash = 250;
	else if (type == 4)
		iCash = 650;
	else if (type == 5)
		iCash = 700;
	else if (type == 6)
		iCash = 250;
	else if (type == 7)
		iCash = 250;
	else if (type == 8)
		iCash = 500;
	else if (type == 9)
		iCash = 250;
	else if (type == 10)
		iCash = 850;
	/*	else if ( type == 11 )
		iCash = 20000;
	else if ( type == 12 )
		iCash = 10000;
	else if ( type == 13 )
		iCash = 15000;*/
	iCash += gold;
	if (count > 20) //每天次数超过20次奖励减少
	{
		pot = pot * 2 / 5;
		exp = exp * 2 / 5;
		con = con * 1;
		iCash = iCash * 2 / 5;
		knb = knb * 1;
	}
	else if (player->get_vip()) //vip玩家
	{
		pot = pot * 3 / 2;
		exp = exp * 3 / 2;
		con = con * 3 / 2;
		iCash = iCash * 3 / 2;
		knb = knb * 1;
	}
	if (player->get_level() < 20)
		exp = exp * 6 / 10;
	con = con * 1;
	iCash = iCash * 1;
	pot = pot * player->get_online_rate() / 100;
	exp = exp * 1;
	knb = knb * 1;
	//	con = con * player->get_online_rate() / 100;
	if (con)
	{
		player->set_fam_contribute(player->get_fam_contribute() + con);
		tmp = sprintf("Điểm cống hiến môn phái " HIY " %d " NOR "điểm", con);
	}
	if (iCash)
	{
		player->add_cash(iCash);
		player->log_money("Sư môn", iCash);
		"/sys/sys/count"->add_income("mastertask", iCash);
		result = sprintf("Ngươi hoàn thành nhiệm vụ thứ " HIY " %d " NOR ", thu được " HIY " %d " NOR " lượng, Kinh nhiệm " HIY " %d " NOR " Tiềm năng " HIY " %d " NOR " điểm %s.", time, iCash, exp, pot, tmp);
	}
	else
		result = sprintf("Ngươi hoàn thành nhiệm vụ thứ " HIY " %d " NOR ", thu được Kinh nhiệm " HIY " %d " NOR " Tiềm năng " HIY " %d " NOR " điểm %s.", time, exp, pot, tmp);
	send_user(player, "%c%s", ';', result);
	player->add_exp(exp);
	player->add_potential(pot);
	"sys/sys/test_db"->add_yuanbao(player, knb);
	//	if ( time==5 || time==10 )
	//		give_five_bonus(player);
	if (time >= 10) //每10次奖励
	{
		//	player->add_save("diemsumon.score", 1);
		//	"sys/sys/test_db"->add_yuanbao(player,10);
		player->set_save_2("mastertask.time", 0);
		if (random100() < player->get_online_rate())
		{
			if (count <= 20)
				check_random_bonus(player);
			// 奖励宝箱
			if (random100() < 5)
				"/quest/box"->give_box(player);
			// Nhiệm vụ Ẩn Tàng
			if (random100() < 30)
			{
				player->set("m_hide", 1);
				cQue = sprintf("    Ngươi nhận được Nhiệm vụ Ẩn Tàng\n" + ESC "Nhận\nmaster_hide 0\n" + ESC "Cự tuyệt\nmaster_hide 1");
				if (!stringp(cQue))
					return;
				//			send_user( player, "%c%c%w%s", ':', 3, master->get_char_picid(), cQue);
				send_user(player, "%c%c%s", ':', 3, cQue);
			}
		}
	}
	else
		player->add_save_2("mastertask.time", 1);
	check_date(player);
	player->add_log("$master", iCash);
	player->add_log("&master", exp);
	player->add_log("*master", pot);
	player->add_log("#master", 1);
	clear_task(player, 0);
	extra_skill_bonus(player);
	"/sys/sys/count"->add_task("Sư môn", 1);
}
//司库询问 nhiệm vụ完成
void task_finish9(object player, object master)
{
	string result;
	object *inv;
	int i, size, iCount = 0, type;

	inv = all_inventory(player, 1, MAX_CARRY * 4);
	size = sizeof(inv);
	for (i = 0; i < size; i++)
	{
		if (inv[i]->get_name() == player->get_save_2("mastertask.targetname") && !inv[i]->get_no_give())
		{
			iCount += inv[i]->get_amount();
		}
	}
	if (iCount < 5)
		result = master->get_name() + sprintf(":\n    Nghe nói ở %s đó, đi tìm thử xem.", player->get_save_2("mastertask.targetpic"));
	else
	{
		player->set("master.type", 59);
		result = sprintf("%s:\n    Nhanh như vậy đã tìm vật phẩm về cho ta à, tốt lắm ta sẽ bẩm báo sư phụ công lao của ngươi, đây là ta thưởng cho ngươi !\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# accept_task.29\n" ESC "Rời khỏi\nclose\n",
						 master->get_name(), getoid(master));
	}
	send_user(player, "%c%s", ':', result);
}
// Vân Du Thương Nhân给予Linh dược
void accept_task10(object player, object npc, string arg)
{
	object item;
	int p;

	if (player->get_save_2("mastertask.type") != 7)
		return;
	p = to_int(arg);
	if (p == 1)
	{
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s\n    Ta bốn biến là nhà, du lịch bốn phương ko ai rõ tung tích. Ngươi tìm được ta ắt cũng là duyên phận.\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# accept_task.2\n" ESC "Rời khỏi", npc->get_name(), getoid(npc)));
		return;
	}
	if (player->get_save_2("mastertask.status") == 99)
		return;
	item = new (sprintf("/item/98/%d", 9872 + random(7)));
	if (!objectp(item))
		return;
	if (USER_INVENTORY_D->can_carry(player, item) >= 1)
	{
		p = item->move(player, -1);
		item->add_to_user(p);
	}
	else
	{
		destruct(item);
		notify("Hành trang không đủ chỗ");
		return;
	}
	player->set_save_2("mastertask.targetname", item->get_name());
	player->set_save_2("mastertask.status", 99);
	player->add_exp(1000);
	send_user(player, "%c%s", ';', "Bạn đạt được 1000 điểm Kinh nghiệm");
	send_task_desc(player, 1);
}
//连续5次的奖励
void give_five_bonus(object who)
{
	string name, unit;
	int i, j, level, *nTmp;
	object item;
	mapping mpFood = ([130:({3301, 3302}),
					   110:({3310, 3311}),
						90:({3303, 3304}),
						70:({3320, 3280}),
						50:({3281, 3285}),
						30:({3283, 3284}),
						10:({3282, 3325}),
	]);

	return; //不奖励了

	name = who->get_fam_name();
	level = who->get_level();
	i = who->add_save_2("mastertask.fivebonus", 1);
	if (i > 4)
		return;
	if (i < 1)
		i = 1;
	if (name == "Côn Luân" || name == "Mao Sơn" || name == "Vân Mộng Cốc") //酒
	{
		if (level >= 130)
			item = new ("item/31/3156");
		else if (level >= 110)
			item = new ("item/31/3155");
		else if (level >= 90)
			item = new ("item/31/3154");
		else if (level >= 70)
			item = new ("item/31/3153");
		else if (level >= 50)
			item = new ("item/31/3152");
		else if (level >= 30)
			item = new ("item/31/3151");
		else
			item = new ("item/31/3150");
	}
	else //食物
	{
		if (level >= 130)
			level = 130;
		else if (level >= 110)
			level = 110;
		else if (level >= 90)
			level = 90;
		else if (level >= 70)
			level = 70;
		else if (level >= 50)
			level = 50;
		else if (level >= 30)
			level = 30;
		else
			level = 10;
		nTmp = mpFood[level];
		level = nTmp[random(sizeof(nTmp))];
		item = new (sprintf("item/%d/%d", level / 100, level));
	}
	if (!objectp(item))
		return;
	item->set_amount(i * 4);
	unit = item->get_unit();
	name = item->get_name();
	if (USER_INVENTORY_D->can_carry(who, item) >= 1)
	{
		j = item->move(who, -1);
		item->add_to_user(j);
		send_user(who, "%c%s", '!', sprintf("Bạn đạt được %s ", name));
	}
	else
	{
		destruct(item);
		notify("Hành trang không đủ chỗ");
	}
}
//清除 nhiệm vụ变量,发送 nhiệm vụ取消信息到客户端
void clear_task(object player, int iCancel)
{
	int type;
	type = player->get_save_2("mastertask.type");
	player->delete_save_2("mastertask.status");
	player->delete_save_2("mastertask.type");
	player->delete_save_2("mastertask.target");
	player->delete_save_2("mastertask.targetxy");
	player->delete_save_2("mastertask.targetxy1");
	player->delete_save_2("mastertask.targetname");
	player->delete_save_2("mastertask.targetpic");
	player->delete_save_2("mastertask.begintime");
	player->delete_save_2("mastertask.endtime");
	player->delete_save_2("master.questtime");
	player->delete_save_2("mastertask.giftname");
	//player->delete_save("cambayquest");
	if (iCancel == 1)
		player->delete_save_2("mastertask.time");

	clear_task_desc(player, type);
}
//取消 nhiệm vụ
void task_giveup(object player)
{
	int date, type, status, i, size, z;
	object obj, map, item;
	string result, *team2;

	check_date(player);
	if ((type = player->get_save_2("mastertask.type")) == 0)
		return;
	// 取消 nhiệm vụ必须在三分钟之后
	if (time() - player->get_save_2("mastertask.begintime") < 0)
		player->set_save_2("mastertask.begintime", 0);
	if (time() - player->get_save_2("mastertask.begintime") < 3 * 60)
	{
		item = player->get_equip(HAND_TYPE);
		if (item && item->get_item_number() == 10001078)
		{
			send_user(player, "%c%c%s", 0x59, 1, sprintf("Ngươi muốn sử dụng Phù để tiêu trừ khoảng cách thời gian nhiệm vụ?\n" ESC "%c\n" ESC "use %x# master\n", 1, getoid(item)));
			return;
		}
		send_user(player, "%c%s", '!', "Một lần nữa huỷ bỏ nhiệm vụ");
		return;
	}
	status = player->get_save_2("mastertask.status");

	if (type == 1 || type == 2 || type == 3 || type == 7)
	{
		if (status == 99)
			send_user(player, "%c%s", '!', " Nhiệm vụ đã hoàn thành, trở về bẩm báo với Sư phụ.");
		else
			clear_task(player, 1);
	}
	else if (type == 4 || type == 5 || type == 6)
	{
		clear_task(player, 1);
	}
	else if (type == 8)
	{
		if (status == 0)
			clear_task(player, 1);
		else if (status == 2 || status == 99)
			send_user(player, "%c%s", '!', sprintf(" Nhiệm vụ đã hoàn thành, hãy trở về bẩm báo với %s Giám Ngục Quan", player->get_save_2("mastertask.targetname")));
		else if (status == 1)
		{
			obj = find_char(player->get_save_2("mastertask.target"));
			if (objectp(obj) && obj->get("user") == player->get_number())
			{
				obj->remove_from_scene();
				obj->before_destruct();
				destruct(obj);
			}
			clear_task(player, 1);
		}
	}
	else if (type == 9)
	{
		if (status == 99 || status == 2)
			send_user(player, "%c%s", '!', " Nhiệm vụ đã hoàn thành, trở về bẩm báo với Sư phụ.");
		else
		{
			obj = find_char(player->get_save_2("mastertask.target"));
			if (objectp(obj) && obj->get("user") == player->get_number())
			{
				obj->remove_from_scene();
				obj->before_destruct();
				destruct(obj);
			}
			clear_task(player, 1);
		}
	}
	else if (type == 10)
	{
		if (status == 99)
			send_user(player, "%c%s", '!', " Nhiệm vụ đã hoàn thành, trở về bẩm báo với Sư phụ.");
		else
		{
			obj = find_char(player->get_save_2("mastertask.target"));
			if (objectp(obj) && obj->get("user") == player->get_number())
			{
				z = get_z(obj);
				if (z == get_z(player))
				{
					send_user(player, "%c%s", '!', "Không thể huỷ bỏ nhiệm vụ!");
					return;
				}
				obj->remove_from_scene();
				obj->before_destruct();
				destruct(obj);
				map = get_map_object(z);
				NEWBIE->destruct_virtual_map(map, z);
			}
			clear_task(player, 1);
		}
	}
	/*	else if ( type == 11 )
	{
		if ( status == 0 )
			clear_task(player,1);
		else if ( status == 98 || status == 99 )
			send_user( player, "%c%s", '!', sprintf(" Nhiệm vụ đã hoàn thành, báo cáo với %s","/sys/task/quest1"->get_manager_name(player->get_fam_name())) );
		else if ( status == 1 )
		{
		        obj = present("Ngân Phiếu", player, 1, MAX_CARRY*4);
		        if ( objectp(obj) )
		        {
		                obj->remove_from_user();
		                destruct(obj);
		        }
			clear_task(player,1);
		}
	}
	else if ( type == 12 )
	{
		if ( status == 0 )
			clear_task(player,1);
		else if ( status == 4 || status == 98 || status == 99 )
			send_user( player, "%c%s", '!', sprintf(" Nhiệm vụ đã hoàn thành, hãy trở về gặp %s Tổng Quản",player->get_save_2("mastertask.targetname")) );
		else
		{
			if ( stringp(player->get_save_2("mastertask.target")) )
			{
				team2 = explode(player->get_save_2("mastertask.target"),"|");
				for(i=0,size=sizeof(team2);i<size;i++)
				{
					obj = find_char(team2[i]);
					if ( !objectp(obj) || obj->get("user") != player->get_number() )
						continue;
					obj->remove_from_scene();
					obj->before_destruct();
					destruct(obj);
				}
			}
			clear_task(player,1);
		}
	}
	else if ( type == 13 )
	{
		if ( status == 0 )
			clear_task(player,1);
		else if ( status == 6 || status == 98 || status == 99 )
			send_user( player, "%c%s", '!', sprintf(" Nhiệm vụ đã hoàn thành, hãy trở về gặp %s Tổng Quản",player->get_save_2("mastertask.targetname")) );
		else
		{
			if ( stringp(player->get_save_2("mastertask.target")) )
			{
				team2 = explode(player->get_save_2("mastertask.target"),"|");
				for(i=0,size=sizeof(team2);i<size;i++)
				{
					obj = find_char(team2[i]);
					if ( !objectp(obj) || obj->get("user") != player->get_number() )
						continue;
					obj->remove_from_scene();
					obj->before_destruct();
					destruct(obj);
				}
			}
			clear_task(player,1);
		}
	}*/
}

void task_giveup2(object who)
{
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_MASTERFIGHT, 1, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTERFIGHT, 1, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTERFIGHT, "");
	who->delete_save_2("masterfight");
}

//清除 nhiệm vụ miêu tả
void clear_task_desc(object who, int type)
{
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, TID_MASTER, type, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, type, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTER, "");
}

void send_task_list(object who, int type)
{
	int status;
	status = who->get_save_2("mastertask.status");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTER, "Nhiệm Vụ Sư Môn");
	switch (type)
	{
	case 1:
		if (status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 1, "Bắt yêu quái");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 1, "Bắt yêu quái(Đã hoàn thành)");
		break;
	case 2:
		if (status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 2, "Rèn luyện");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 2, "Rèn luyện(Đã hoàn thành)");
		break;
	case 3:
		if (status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 3, "Du lịch");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 3, "Du lịch(Đã hoàn thành)");
		break;
	case 4:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 4, "Thu mua");
		break;
	case 5:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 5, "Thu thập");
		break;
	case 6:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 6, "Thăm viếng");
		break;
	case 7:
		if (status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 7, "Tìm tung tích");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 7, "Tìm tung tích(Đã hoàn thành)");
		break;
	case 8:
		if (status != 2 && status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 8, "Hiệp trợ trị an");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 8, "Hiệp trợ trị an(Đã hoàn thành)");
		break;
	case 9:
		if (status != 2 && status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 9, "Tuần sơn");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 9, "Tuần sơn(Đã hoàn thành)");
		break;
	case 10:
		if (status != 99)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 10, "Môn phái tỷ thý");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER, 10, "Môn phái tỷ thý(Đã hoàn thành)");
		break;
		/*		case 11:
			if ( status != 98 && status != 99 )
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,11,"Trù tập" );
			else
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,11,"Trù tập(Đã hoàn thành)" );
			break;
		case 12:
			if ( status < 4 )
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,12,"Truy sát phản đồ" );
			else
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,12,"Truy sát phản đồ(Đã hoàn thành)" );
			break;
		case 13:
			if ( status < 6 )
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,13,"Truy bắt Thích khách" );
			else
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_MASTER,13,"Truy bắt Thích khách(Đã hoàn thành)" );
			break;*/
	}
}

//发送 nhiệm vụ详细 miêu tả
void send_task_intro(object me)
{
	int type, status, z, x, y, i, size, flag;
	string result, id, name, *team2;
	object who, npc, owner;

	type = me->get_save_2("mastertask.type");
	status = me->get_save_2("mastertask.status");
	result = " nhiệm vụ thất bại";
	switch (type)
	{
	case 1:
		if (status != 99)
			result = sprintf(BLK "Bắt yêu quái (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Bắt " HIR " %s " BLK " rồi trở về.\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Hiện nay thiên hạ đại loạn, yêu ma quỷ quái hoành hành bốn bể. Sư phụ muốn ta đi bắt một con yêu quái về giao nộp. Nghe nói ở %s , đi tìm thử xem \n" BLK "Trước khi đi bắt yêu quái hãy nhớ đến chủ tiệm tạp hóa mua Dây Càn Khôn. Sử dụng dụng kỹ năng “Bắt Bảo Thú” để hoàn thành nhiệm vụ. huyết khí của quái vật càng thấp, tỷ lệ bắt được càng cao.", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetname"), me->get_save_2("mastertask.target"));
		else
			result = sprintf(BLK "Bắt yêu quái (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Bắt " HIR " %s " BLK " rồi trở về.\n" BLK "%s  1/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Hiện nay thiên hạ đại loạn, yêu ma quỷ quái hoành hành bốn bể. Sư phụ muốn ta đi bắt một con yêu quái về giao nộp. Nghe nói ở %s , đi tìm thử xem \n" BLK "Trước khi đi bắt yêu quái hãy nhớ đến chủ tiệm tạp hóa mua Dây Càn Khôn. Sử dụng dụng kỹ năng “Bắt Bảo Thú” để hoàn thành nhiệm vụ. huyết khí của quái vật càng thấp, tỷ lệ bắt được càng cao.", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetname"), me->get_save_2("mastertask.targetname"), me->get_save_2("mastertask.target"));
		break;
	case 2:
		if (me->get_save_2("mastertask.status") != 99)
			result = sprintf(BLK "Rèn luyện (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tăng lên %d điểm Kinh nghiệm.\n" BLK "Tăng lên kinh nghiệm:  %d/%d\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này.\n", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetxy"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"));
		else
			result = sprintf(BLK "Rèn luyện (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tăng lên %d điểm Kinh nghiệm.\n" BLK "Tăng lên kinh nghiệm:  %d/%d\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này.\n", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"));
		break;
	case 3:
		if (me->get_save_2("mastertask.status") != 99)
			result = sprintf(BLK "Du lịch (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tăng lên %d điểm Tiềm Năng.\n" BLK "Tăng lên Tiềm Năng:  %d/%d\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Nếu muốn đạt đến đỉnh cao trong võ học, ngươi phải biết khổ luyện cho nhiều.Vi sư hy vọng ngươi ra ngoài vừa đi vừa khổ luyện.\n", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetxy"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"));
		else
			result = sprintf(BLK "Du lịch (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tăng lên %d điểm Tiềm Năng.\n" BLK "Tăng lên Tiềm Năng:  %d/%d\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Nếu muốn đạt đến đỉnh cao trong võ học, ngươi phải biết khổ luyện cho nhiều.Vi sư hy vọng ngươi ra ngoài vừa đi vừa khổ luyện.\n", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"), me->get_save_2("mastertask.targetpic"));
		break;
	case 4:
		if (me->get_save_2("mastertask.status") == 0)
			result = sprintf(BLK "Thu mua (Lượt thứ %d )\n" BLK "Mục tiêu nhiệm vụ:\n" BLK "    Đi tìm %s .\n" BLK " nhiệm vụ miêu tả:\n:" BLK "    Dạo gần đây một số vật phẩm của bổn môn dự trữ không đủ, cần gấp phải ra ngoài đi thu mua một số vật phẩm về. %s đang lo lắng đến phát điên, ta phải đi tìm %s hỏi rõ tình hình, xem có thể giúp được gì không. \n",
							 me->get_save_2("mastertask.time") + 1, name = "/sys/task/quest1"->get_manager_name(me->get_fam_name()), name, name);
		else
			result = sprintf(BLK "Thu mua (Lượt thứ %d )\n" BLK "Mục tiêu nhiệm vụ:\n" BLK " Thu mua 1 %s , và giao cho %s .\n" BLK "Miêu tả nhiệm vụ:\n " BLK " %s dạo gần đây báo rằng một số vật phẩm của bổn môn dự trữ không đủ, cần gấp phải ra ngoài đi thu mua một số vật phẩm về. Sư phụ bảo ta đi tìm hỏi rõ tình hình, xem có thể giúp được gì không.\n" BLK " Do ngày thường không cẩn thận lưu ý, bổn môn có một số vật phẩm dự trữ rõ ràng không đủ, nếu như không tranh thủ thời gian giải quyết, sẽ làm cho bổn môn gặp không ít rắc rồi. Nhưng lúc này ngươi làm việc không đủ, %s nhờ ta đi %s thu mua %s về giao cho ông ta. Lúc giao cho ông ta dùng dùng chỉ lệnh dành cho thì được rồi(Alt＋G).\n",
							 me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetname"), name = "/sys/task/quest1"->get_manager_name(me->get_fam_name()), name, name, me->get_save_2("mastertask.giftname"), me->get_save_2("mastertask.targetname"));
		break;
	case 5:
		if (me->get_save_2("mastertask.status") == 0)
			result = sprintf(BLK "Thu thập (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Đi tìm %s .\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Sư phụ bảo ta đi tìm %s xem có giúp đỡ được chuyện gì hay không.\n",
							 me->get_save_2("mastertask.time") + 1, name = "/sys/task/quest1"->get_manager_name(me->get_fam_name()), name);
		else
			result = sprintf(BLK "Thu thập (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Thu thập 5 cái %s , và giao cho %s .\n" BLK " nhiệm vụ miêu tả:\n" BLK "    %s khi tìm được ta, %s vội vàng bảo ta đi thu thập %s . Nghe nói ở %s , ta phải đi tìm thử.\n",
							 me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetname"), name = "/sys/task/quest1"->get_manager_name(me->get_fam_name()), name, name, me->get_save_2("mastertask.targetname"), me->get_save_2("mastertask.targetpic"));
		break;
	case 6:
		result = sprintf(BLK "Thăm viếng (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Thăm viếng %s\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Sư phụ bế quan tu hành đã mấy hôm rồi, cũng không biết tình hình mấy người bạn già của sư phụ như thế nào. Trước đây họ thường đến thăm viếng sư phụ, nếu lâu quá sư phụ không đi thăm hỏi lại họ thì cũng có phần thất lễ. Do đó sư phụ bảo ta đi tới %s để hỏi thăm sức khoẻ %s giùm sư phụ.", me->get_save_2("mastertask.time") + 1, me->get_save_2("mastertask.targetname"), me->get_save_2("mastertask.targetcity"), me->get_save_2("mastertask.targetname"));
		break;
	case 7:
		if (me->get_save_2("mastertask.status") == 99)
			result = sprintf(BLK "Tìm tung tích (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "  Tìm tung tích Vân Du Thương Nhân\n" BLK "Linh dược:1/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "     Vân Du Thương Nhân đã cho tinh Linh dược, ta phải về bẩm báo với sư phụ .",
							 me->get_save_2("mastertask.time") + 1);
		else
			result = sprintf(BLK "Tìm tung tích (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tìm kiếm Vân Du Thương Nhân\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Gần đây sư phụ muốn thử luyện chế một loại đơn dược, nhưng luyện chế loại đơn dược này cần phải có linh dược làm dược dẫn, Nghe nói ở chỉ có Vân Du Thương Nhân mới có loại linh dược này. Sư phụ sai ta thử đi tìm Vân Du Thương Nhân, nếu như tìm được ông ta thì xin ông ta loại linh dược này.Hành tung của Vân Du Thương Nhân rất bí ẩn nhưng ta nghe nói Chủ Tửu Lầu biết rất rõ ông ta đang ở đâu. Hãy tới hỏi thử xem.\n",
							 me->get_save_2("mastertask.time") + 1);
		break;
	case 8:
		status = me->get_save_2("mastertask.status");
		x = me->get_save_2("mastertask.targetxy1");
		y = x % 1000;
		x = x / 1000;
		if (status == 2 || status == 99)
			result = sprintf(BLK "Hiệp trợ trị an (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tiêu diệt lưu manh ngoài thành.\n" BLK "Lưu manh: 1/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "%s Giám Ngục Quan gửi thư nhờ vả, khi ta đi vào %s Nghe nói ở có tên lưu manh ngoài thành sinh sự. Hắn đang ở (%d, %d) vùng thường lui tới.",
							 me->get_save_2("mastertask.time") + 1, name = me->get_save_2("mastertask.targetname"), name, x, y);
		else if (status == 0)
			result = sprintf(BLK "Hiệp trợ trị an (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tìm %s Giám Ngục Quan\n" BLK " nhiệm vụ miêu tả:\n" BLK "    %s Giám Ngục Quan gửi thư, nói %s tình hình càng ngày càng ác liệt, một tên lưu manh sinh sự đã làm náo loạn cả lên, mong ta đến hỗ trợ.\n",
							 me->get_save_2("mastertask.time") + 1, name = me->get_save_2("mastertask.targetname"), name, name);
		else if (stringp(id = me->get_save_2("mastertask.target")) && (npc = find_char(id)) && npc->get("user") == me->get_number())
			result = sprintf(BLK "Hiệp trợ trị an (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tiêu diệt lưu manh ngoài thành.\n" BLK "Lưu manh: 0/1" HIR "（Thời hạn 60 phút）" BLK "\n" BLK " nhiệm vụ miêu tả:\n" BLK "%s Giám Ngục Quan gửi thư nhờ vả, khi ta đi vào %s Nghe nói ở có tên lưu manh ngoài thành sinh sự. Hắn đang ở (%d, %d) vùng thường lui tới.",
							 me->get_save_2("mastertask.time") + 1, name = me->get_save_2("mastertask.targetname"), name, x, y);
		else
			result = sprintf(BLK "Hiệp trợ trị an (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tiêu diệt lưu manh ngoài thành.\n" BLK "Lưu manh: 0/1" HIR "（ nhiệm vụ thất bại）" BLK "\n",
							 me->get_save_2("mastertask.time") + 1);
		break;
	case 9:
		x = me->get_save_2("mastertask.targetxy1");
		y = x % 1000;
		x = x / 1000;
		if ((status = me->get_save_2("mastertask.status")) == 99 || status == 2)
			result = sprintf(BLK "Tuần sơn (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tuần tra ở bổn môn, bắt hết kẻ khả nghi\n" BLK "Kẻ khả nghi:1/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Có đệ tử bẩm báo ở Sư môn (%d,%d) xuất hiện kẻ khả nghi.\n",
							 me->get_save_2("mastertask.time") + 1, x, y);
		else if (stringp(id = me->get_save_2("mastertask.target")) && (npc = find_char(id)) && npc->get("user") == me->get_number())
			result = sprintf(BLK "Tuần sơn (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tuần tra ở bổn môn, bắt hết kẻ khả nghi\n" BLK "Kẻ khả nghi:0/1" HIR "（Thời hạn 60 phút）" BLK "\n" BLK " nhiệm vụ miêu tả:\n" BLK "    Có đệ tử bẩm báo ở Sư môn (%d,%d) xuất hiện kẻ khả nghi.\n",
							 me->get_save_2("mastertask.time") + 1, x, y);
		else
			result = sprintf(BLK "Tuần sơn (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Tuần tra ở bổn môn, bắt hết kẻ khả nghi\n" BLK "Kẻ khả nghi:0/1" HIR "（ nhiệm vụ thất bại）" BLK "\n",
							 me->get_save_2("mastertask.time") + 1);
		break;
		//		case 10:
	default:
		if (me->get_save_2("mastertask.status") == 99)
			result = sprintf(BLK "Môn phái tỷ thý (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Đi tới %s tỷ thý võ công.\n" BLK "%s đệ tử:1/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "    %s Chưởng môn đã sai người đến đây phát thư mời đệ tử của bổn môn ra tỷ thí võ công, tự bổ sung vào những điểm khiếm khuyết của võ học, sư phụ lệnh cho ta đi, ta không thể bỏ lỡ cơ hội lần này, thời gian có hạn, ta phải lập tức đi ngay. Đến mục tiêu, nói chuyện với đệ tử của môn phái này, bạn sẽ được chuyển đến võ trường, đánh bại đối thủ để hoàn thành nhiệm vụ.\n",
							 me->get_save_2("mastertask.time") + 1, name = me->get_save_2("mastertask.targetname"), name, name);
		else
			result = sprintf(BLK "Môn phái tỷ thý (Lượt thứ %d)\n" BLK " nhiệm vụ:\n" BLK "    Đi tới %s tỷ thý võ công.\n" BLK "%s đệ tử:0/1\n" BLK " nhiệm vụ miêu tả:\n" BLK "    %s Chưởng môn đã sai người đến đây phát thư mời đệ tử của bổn môn ra tỷ thí võ công, tự bổ sung vào những điểm khiếm khuyết của võ học, sư phụ lệnh cho ta đi, ta không thể bỏ lỡ cơ hội lần này, thời gian có hạn, ta phải lập tức đi ngay. Đến mục tiêu, nói chuyện với đệ tử của môn phái này, bạn sẽ được chuyển đến võ trường, đánh bại đối thủ để hoàn thành nhiệm vụ.\n",
							 me->get_save_2("mastertask.time") + 1, name = me->get_save_2("mastertask.targetname"), name, name);
		break;
		//		case 11:
		/*		default:
			status = me->get_save_2("mastertask.status");
			if (status==0)
				result = sprintf(BLK"Trù tập (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Tìm %s hỏi hắn rồi giải quyết vấn đề.\n"BLK" nhiệm vụ miêu tả:\n"BLK"    %s như đang bị tâm thần, hãy đến hỏi hắn thử xem.\n",
					me->get_save_2("mastertask.time")+1, name="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name );
			else
				result = sprintf(BLK"Trù tập (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Kiếm %d mang về cho tư khố\n"BLK" nhiệm vụ miêu tả:\n"BLK"    %s như đang bị tâm thần, ngươi hãy qua hỏi hắn thử xem.Cùng %s trò chuyện mới biết tiền bạc đang thiếu trầm trọng.Ở %s , ngươi hãy xuống núi kiếm thêm tiền về.\n",
					me->get_save_2("mastertask.time")+1, me->get_save_2("mastertask.targetxy"), name="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name,name );
			break;
		case 12:
			status = me->get_save_2("mastertask.status");
			flag = 0;
			if (status!=0 && status<4)
			{
				team2 = explode(me->get_save_2("mastertask.target"),"|");
				
				for(i=0,size=sizeof(team2);i<size;i++)
				{
					owner = find_char(team2[i]);
					if ( !objectp(owner) || owner == me )
						continue;
					if (owner->get("user")!=me->get_number()) continue;
					flag ++;				
				}	
			}						
			if (status==0)
				result = sprintf(BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Tìm %s Tổng Quản Vương Phủ\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ.Sư phụ ra lệnh cho ta đi %s .\n",
					me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name,name );
			else
			if (flag==0 && status<4)
				result = sprintf(BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"  Đuổi giết %s ở %s\n"BLK"%s    0/1"HIR "（ nhiệm vụ thất bại）"BLK"\n",
					me->get_save_2("mastertask.time")+1, id=me->get_save_2("mastertask.targetname"), name=me->get_save_2("mastertask.targetpic"), name );
			else			
			if (status<4)
				result = sprintf(BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"  Đuổi giết %s ở %s\n"BLK"%s    0/1"HIR "（Thời hạn 60 phút）"BLK"\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ.Sư phụ ra lệnh cho ta đi %s . \n"BLK" cùng %s Tổng Quản gặp mặt ta mới biết có kẻ phản quốc.%s Tổng Quản báo rằng %s đang ở "HIR " %s (%d,%d) "BLK" chạy trốn.Hơn nữa %s đã mua chuộc bọn sơn tặc.\n",
					me->get_save_2("mastertask.time")+1,id=me->get_save_2("mastertask.targetname"), name=me->get_save_2("mastertask.targetpic"),name,id,id,id,id,name,me->get_save_2("mastertask.giftname"),((z=me->get_save_2("mastertask.targetxy1"))/1000),z%1000,name,id);
			else
				result = sprintf(BLK"Truy sát phản đồ (Lượt thứ %d)（Đã hoàn thành）\n"BLK" nhiệm vụ:\n"BLK"  Đuổi giết %s phản đồ %s\n"BLK"%s    1/1\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ.Sư phụ ra lệnh cho ta đi %s . \n"BLK" cùng %s Tổng Quản gặp mặt ta mới biết có kẻ phản quốc.%s Tổng Quản báo rằng %s đang ở "HIR " %s (%d,%d) "BLK" chạy trốn.Hơn nữa %s đã mua chuộc bọn sơn tặc.\n",
					me->get_save_2("mastertask.time")+1,id=me->get_save_2("mastertask.targetname"), name=me->get_save_2("mastertask.targetpic"),name,id,id,id,id,name,me->get_save_2("mastertask.giftname"),((z=me->get_save_2("mastertask.targetxy1"))/1000),z%1000,name,id);
			break;
		default:
			status = me->get_save_2("mastertask.status");
			flag = 0;
			if (status!=0 && status<6)
			{
				team2 = explode(me->get_save_2("mastertask.target"),"|");
				
				for(i=0,size=sizeof(team2);i<size;i++)
				{
					owner = find_char(team2[i]);
					if ( !objectp(owner) || owner == me )
						continue;
					if (owner->get("user")!=me->get_number()) continue;
					flag ++;				
				}	
			}			
			if (status==0)
				result = sprintf(BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Tìm %s Tổng Quản Vương Phủ Truy bắt Thích khách.\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ báo tối hôm qua có thích khách lẻn vào.\n",
					me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name);
			else
			if (status<6 && flag==0)
				result = sprintf(BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Đuổi bắt tới %s Thích Khách"HIR "（Thời hạn 60 phút）"BLK"\n"BLK"刺客首领	%d/1\n"BLK"蒙面刺客	%d/4\n"HIR "（ nhiệm vụ thất bại）\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ báo tối hôm qua có thích khách lẻn vào.\n"BLK"    Đi vào %s biết dược đã chạy trốn đến %s liền mất dạng, Tổng Quản vẫn tin ắt hắn vẫn còn ở vùng %s\n",
					me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.giftname"),me->get_save_2("mastertask.y"),me->get_save_2("mastertask.x"),id=me->get_save_2("mastertask.targetname"),id,name,name);
			else			
				result = sprintf(BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Đuổi bắt tới %s Thích Khách\n"BLK"刺客首领	%d/1\n"BLK"蒙面刺客	%d/4\n"HIR "（Thời hạn 60 phút）\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ báo tối hôm qua có thích khách lẻn vào.\n"BLK"    Đi vào %s biết dược đã chạy trốn đến %s liền mất dạng, Tổng Quản vẫn tin ắt hắn vẫn còn ở vùng %s\n",
					me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.giftname"),me->get_save_2("mastertask.y"),me->get_save_2("mastertask.x"),id=me->get_save_2("mastertask.targetname"),id,name,name);
	//				else
	//					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ:\n"BLK"    Đuổi bắt tới %s Thích Khách\n"BLK"刺客首领	1/1\n"BLK"蒙面刺客	4/4\n"BLK" nhiệm vụ miêu tả:\n"BLK"    Sư phụ nhận được thư từ %s Tổng Quản Vương Phủ báo tối hôm qua có thích khách lẻn vào.\n"BLK"    来到%s后，得知行刺者已经逃窜到%s后便失去了踪影.总管大人相信他们仍潜藏在%s.\n"BLK"    大人已经颁发了追杀令，一旦发现目标，格杀无论!\n",
	//						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.giftname"),id=me->get_save_2("mastertask.targetname"),id,name,name);
			break;*/
	}
	if (stringp(result))
		send_user(me, "%c%c%c%w%w%s", 0x51, 1, 3, TID_MASTER, type, result);
}

//发送 nhiệm vụ详细 miêu tả
void send_task_intro2(object me)
{
	int type, status, z, x, y;
	string result, id, name;
	object who, npc;
	status = me->get_save_2("masterfight.status");
	if (status == 0)
		return;
	result = BLK "Sư môn Khiêu chiến\n" BLK " nhiệm vụ:\n" BLK "    Đánh thắng sư thúc, được Bái sư phụ tiếp theo.\n";
	send_user(me, "%c%c%c%w%w%s", 0x51, 1, 3, TID_MASTERFIGHT, 1, result);
}

//发送 nhiệm vụ miêu tả
void send_task_desc(object who, int iFlag)
{
	int type;

	if ((type = who->get_save_2("mastertask.type")) == 0)
		return;
	if (iFlag == 0)
	{
		send_task_intro(who);
		return;
	}
	if (iFlag == 1)
		clear_task_desc(who, type);
	send_task_list(who, type);
	send_task_intro(who);
}

void do_init_gift(object who, object npc, string arg)
{
	int i;
	i = to_int(arg);
	if (i == 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\nNgươi chỉ có tẩy điểm miễn phí được một lần mà thôy!\n" ESC "Xác nhận\ntalk %x# init.2\n" ESC "Rời khỏi", getoid(npc)));
	}
	if (i == 2)
	{
		if (who->get_save_2("init_gift7"))
			return;
		who->set_save_2("init_gift7", 1);
		"/cmd/user/gift"->init_gift_point(who);
		who->log_legend(sprintf("Ngươi ở %s đã tẩy điểm tiềm năng.", npc->get_name()));
		send_user(who, "%c%s", '!', "Tẩy điểm thành công!");
	}
}
// 函数:消除之前处理
void before_destruct()
{
	"npc/00/0008"->set("SellerLocate", SellerLocate);
}

void create()
{
	SellerLocate = "npc/00/0008"->get("SellerLocate");
}
//额外提升10级以下的技能
void extra_skill_bonus(object who)
{
	int *nSkill, i, size, *nTmp;
	string cSkill;

	if (MAIN_D->get_host_type() == 2) //台湾除外
		return;
	if (random100() >= who->get_online_rate())
		return;
	nSkill = mpSkill[who->get_fam_name()];
	nTmp = ({});
	for (i = 0, size = sizeof(nSkill); i < size; i++)
	{
		if (who->get_skill(nSkill[i]) < 20)
			nTmp += ({nSkill[i]});
	}
	size = sizeof(nTmp);
	if (size)
	{
		i = nTmp[random(size)];
		who->set_skill(i, who->get_skill(i) + 1);
		cSkill = SKILL->get_skill_file(i);
		send_user(who, "%c%s", '!', sprintf("Bạn hoàn thành nhiệm vụ, " HIR "%s " NOR "thăng thêm 1 cấp.", cSkill->get_name()));
	}
}

//NhậnSư mônNhiệm vụ Ẩn Tàng
void hide_quest(object me)
{
	int z, x, y, p, iTime, level;
	string cName;
	object npc, map;
	if (me->get("m_hide") != 1)
		return;
	me->delete ("m_hide");
	if (!(p = XY_D->get_city_point(-1, IS_CHAR_BLOCK)))
		return;
	z = p / 1000000;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	//	level = who->get_level() > user->get_level() ?  who->get_level() : user->get_level();
	level = me->get_level();
	iTime = time();
	npc = new ("npc/task/8400");
	if (!npc)
		return;
	cName = "Tây Vực" + NPC_NAME_D->get_banditi_name();
	npc->set_name(cName);
	npc->set("hide1", me->get_number());
	//	npc->set("hide2",user->get_number());
	NPC_ENERGY_D->init_level(npc, level);
	init_npc(npc);
	npc->set_max_seek(8);
	map->add_reset(npc);

	npc->add_to_scene(z, x, y);
	npc->set("user", me->get_number());
	me->delete_save_2("master_hide");
	me->set_save_2("master_hide.npcid", getoid(npc));
	me->set_save_2("master_hide.name", cName);
	me->set_save_2("master_hide.country", map->get_name());
	me->set_save_2("master_hide.x", x);
	me->set_save_2("master_hide.y", y);
	me->set_save_2("master_hide.x1", x + random(20));
	me->set_save_2("master_hide.y1", y + random(20));
	me->set_save_2("master_hide.time", iTime);
	me->set_save_2("master_hide.exp", level * level * 20);
	me->set_save_2("master_hide.potential", level * level + level * 100);
	send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTER_HIDE, "Nhiệm Vụ Sư Môn");
	send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER_HIDE, 1, "Nhiệm vụ Ẩn Tàng");
}

//Sư mônNhiệm vụ Ẩn Tàng怪
void init_npc(object npc)
{
	int p, level;

	level = npc->get_level();
	p = random(100);
	if (p < 20) //低物防高敏型
	{
		npc->set_skill(348, level);
		npc->set_skill(251, level);
		npc->set_skill(241, level);
		npc->set_char_picid(8011);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 4);
		npc->add_max_hp(npc->get_max_hp() * 8);
		npc->add_sp(npc->get_sp() * 2);
		npc->add_ap(npc->get_ap() * 4 / 5);
		npc->add_mp(npc->get_mp() / 2);
		npc->set("hide.type", 1);
	}
	else if (p < 40) //高物防低法防型
	{
		npc->set_skill(221, level);
		npc->set_skill(231, level);
		npc->set_char_picid(0252);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(npc->get_dp() * 3);
		npc->add_max_hp(npc->get_max_hp() * 4);
		npc->add_pp(-1 * npc->get_pp() * 3 / 10);
		npc->add_ap(npc->get_ap() * 4 / 5);
		npc->add_mp(npc->get_mp() / 2);
		npc->set("hide.type", 2);
	}
	else if (p < 60) //高法防低物防型
	{
		npc->set_skill(423, level);
		npc->set_skill(424, level);
		npc->set_skill(425, level);
		npc->set_char_picid(8010);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 4);
		npc->add_max_hp(npc->get_max_hp() * 4);
		npc->add_sp(npc->get_sp());
		npc->add_pp(npc->get_pp() * 3 / 2);
		npc->add_cp(npc->get_cp());
		npc->add_mp(npc->get_mp() * 6);
		npc->set("hide.type", 3);
	}
	else if (p < 70) //长血型:拳脚类
	{
		npc->set_skill(211, level);
		npc->set_skill(317, level);
		npc->set_char_picid(8000);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(-1 * npc->get_dp() / 5);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_pp(-1 * npc->get_pp() / 5);
		npc->add_mp(npc->get_mp() / 2);
		npc->add_ap(npc->get_ap() * 9 / 10);
		npc->set("hide.type", 4);
	}
	else if (p < 90) //长血高物防高法防型:远程暗器类
	{
		npc->set_skill(261, level);
		npc->set_char_picid(8012);
		npc->set_walk_speed(4);
		npc->set_attack_speed(10);
		npc->add_dp(npc->get_dp() * 9 / 20);
		npc->add_max_hp(npc->get_max_hp() * 5);
		npc->add_sp(npc->get_sp() * 3);
		npc->add_pp(npc->get_pp() * 9 / 5);
		npc->add_mp(npc->get_mp());
		npc->add_ap(npc->get_ap() / 2);
		npc->set("hide.type", 5);
	}
	else //强攻型加召唤
	{
		npc->set_skill(414, level);
		npc->set_char_picid(8013);
		npc->set_walk_speed(4);
		npc->set_attack_speed(8);
		npc->add_dp(npc->get_dp() * 9 / 20);
		npc->add_ap(npc->get_ap());
		npc->add_max_hp(npc->get_max_hp() * 5);
		npc->add_sp(npc->get_sp() * 3);
		npc->add_pp(npc->get_pp() * 9 / 20);
		npc->add_mp(npc->get_mp() * 3 / 2);
		npc->set("hide.type", 6);
	}
}

//Sư mônNhiệm vụ Ẩn Tàng玩家死亡处理
void hide_task_die(object who)
{
	int *men_pai = ({289, 273, 80, 324, 269, 54, 165});
	int *shi_fu = ({
		039070,
		218169,
		226052,
		109165,
		276192,
		102144,
		091033,
		112083,
		205174,
		196031,
		134143,
		273195,
		091140,
		087030,
		047063,
		223163,
		169064,
		077129,
		279189,
		110152,
		097035,
		080054,
		205158,
		185074,
		092117,
		266183,
		111137,
		103026,
	});
	int aa, bb, x, y, z;
	aa = who->get_fam_type() - 1;
	bb = who->get_fam_order() - 1;
	z = men_pai[aa];
	x = shi_fu[bb * 7 + aa] / 1000 + random(3);
	y = shi_fu[bb * 7 + aa] % 1000 + random(3);
	who->add_to_scene(z, x, y, 3);
	send_user(who, "%c%s", '!', "Ngươi bị Tây Vực Nhân đánh bại");
}

//取消Sư mônNhiệm vụ Ẩn Tàng
master_hide_giveup(object who, object npc)
{
	if (objectp(npc = find_char(sprintf("%x#", who->get_save_2("master_hide.npcid")))) && npc->is_master_hide_task())
	{
		npc->remove_from_scene();
		destruct(npc);
	}
	who->delete_save_2("master_hide");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_MASTER_HIDE, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_MASTER_HIDE, 1, "");
}
