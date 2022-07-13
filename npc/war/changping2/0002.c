#include <ansi.h>
#include <npc.h>
#include <cmd.h>
#include <city.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

int is_self_look() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 9715; }

void do_welcome(string arg);
void do_look2(object me, object who);

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Thần Cơ Viện Chủ");
	set_city_name("Bang Phái");

	set_2("good", (["01":"/item/std/0401",
					  "02":"/item/std/0498",
					  "03":"/item/std/0499",
					  //                "04" : "/item/std/0497",
					  "05":"/item/std/0413",
					  "06":"/item/std/0591",
					  "07":"/item/32/3231",
					  "08":"/item/91/9100",
					  "09":"/item/91/9101",
					  "10":"/item/91/9110",
					  "11":"/item/91/9111",
					  "12":"/item/stuff/0106",
	]));
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	setup();
}

void do_look(object who)
{
	string result;
	object me = this_object();
	__FILE__->do_look2(me, who);
}

void do_look2(object me, object who)
{
	string result;
	if (me->get_org_name() == who->get_org_name())
	{
		result = sprintf("%s：\nÔng già có thể cung cấp cho bạn tất cả những gì bạn cần trong chiến tranh, và ông già cũng có thể phát triển các thiết bị tấn công cao cấp. Làm thế nào? Bạn có cần một người chồng cũ để làm gì?\n", me->get_name());
		result += sprintf(ESC "Mua hàng hóa\nlist %x#\n", getoid(me));
		if (who->get_org_position() >= 8)
			result += sprintf(ESC "Nghiên cứu con rối chiến đấu\ntalk %x# welcome.1\n", getoid(me));
	}
	else
		return;
	result += ESC "Rời khỏi\nCLOSE\n";
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object who, string arg)
{
	int flag, position, weapon;
	object me, orgnpc;
	string name, result;
	me = this_player();
	position = me->get_org_position();
	name = me->get_org_name();
	if (name == "")
		return;
	if (position < 8)
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	weapon = orgnpc->get_weapon();
	if (weapon == 1)
	{
		result = sprintf("%s：\n    Thiết bị tấn công của Bang Phái đã được phát triển。\n", who->get_name());
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (weapon > 1)
	{
		if (time() < weapon)
		{
			result = sprintf("%s：\n   Bây giờ Bang Phái của chúng tôi đang tiến hành nghiên cứu và phát triển xe ném đá, người lớn chờ đợi %d giây để xem kết quả.\n", who->get_name(), weapon - time());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		else
		{
			remove_call_out("weapon_callout");
			orgnpc->set_weapon(1);
			result = "Trong chiến tranh, các nhà lãnh đạo của viện thần kinh đã phát triển thành công công nghệ rối chiến đấu。";
			FAMILY_D->org_channel(name, 0, result);
			return;
		}
	}
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		result = sprintf("%s：\n    Gỗ Bang Phái hiện tại" HIR "Dự trữ %d, tiền của Bang Phái %d" NOR ". Con rối nghiên cứu chiến tranh phải bị tiêu diệt" HIR "500000Tiền của Bang Phái" NOR "và" HIR " 200 gỗ dự trữ" NOR "Sau khi nghiên cứu thành công có thể tuyển dụng con rối chiến đấu để hỗ trợ chiến đấu tại võ đài, nghiên cứu thời gian" HIR "300 giây" NOR "。\n    Anh chắc là muốn nghiên cứu con rối chiến đấu chứ？\n", who->get_name(), orgnpc->get_wood(), orgnpc->get_gold());
		result += sprintf(ESC "Chắc chắn\ntalk %x# welcome.2\n", getoid(who));
		result += ESC "Hủy bỏ\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 2:
		if (orgnpc->get_gold() < 500000)
		{
			result = sprintf("%s：\n    Các Bang Phái được tài trợ ít hơn 500000 ngân lượng để bắt đầu nghiên cứu.\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_wood() < 200)
		{
			result = sprintf("%s：\n   Gỗ của Bang Phái không đủ 200 để bắt đầu nghiên cứu.\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		orgnpc->add_gold(-500000);
		orgnpc->add_wood(-200);
		orgnpc->set_weapon(time() + 300);
		call_out("weapon_callout", 300, who);
		result = "Trong chiến tranh, các nhà ảo thuật bắt đầu phát triển công nghệ chiến đấu rối。";
		FAMILY_D->org_channel(name, 0, result);
		break;
	}
}

// 函数：心跳处理(循环)
void weapon_callout(object me) // 每１分处理
{
	string name, result;
	int weapon;
	object orgnpc;
	name = me->get_org_name();
	remove_call_out("weapon_callout");
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	weapon = orgnpc->get_weapon();
	if (weapon <= 1)
		return;

	orgnpc->set_weapon(1);
	result = "Trong chiến tranh, các nhà lãnh đạo của viện thần kinh đã phát triển thành công công nghệ rối chiến đấu.";
	FAMILY_D->org_channel(name, 0, result);
}
