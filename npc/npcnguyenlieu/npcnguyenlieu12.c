
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 7009; }

// 函数：获取人物造型
int get_char_picid() { return 9212; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome(string arg);

// 函数：构造处理
void create()
{
	set_name("Thương Nhân Dược Liệu 12");
	set_city_name("Vô gia cư");

	set_2("good", (["01":"/item/stuff/0273",
					  "02":"/item/stuff/0274",
					  "03":"/item/stuff/0275",
					  "04":"/item/stuff/0276",
					  "05":"/item/stuff/0277",
					  "06":"/item/stuff/0278",
					  "07":"/item/stuff/0279",
					  "08":"/item/stuff/0280",
					  "09":"/item/stuff/0281",
					  "10":"/item/stuff/0282",
					  "11":"/item/stuff/0283",
					  "12":"/item/stuff/0284",
					  "13":"/item/stuff/0285",
					  "14":"/item/stuff/0286",
					  "15":"/item/stuff/0287",
					  "16":"/item/stuff/0288",
					  "17":"/item/stuff/0289",
					  "18":"/item/stuff/0290",
					  "19":"/item/stuff/0291",
					  "20":"/item/stuff/0292",
					  "21":"/item/stuff/0293",
					  "22":"/item/stuff/0294",
					  "23":"/item/stuff/0295",
					  "24":"/item/stuff/0296",
	]));

	set_2("soluong", (["01":20,
						 "02":20,
						 "03":20,
						 "04":20,
						 "05":20,
						 "06":20,
						 "07":20,
						 "08":20,
						 "09":20,
						 "10":20,
						 "11":20,
						 "12":20,
						 "13":20,
						 "14":20,
						 "15":20,
						 "16":20,
						 "17":20,
						 "18":20,
						 "19":20,
						 "20":20,
						 "21":20,
						 "22":20,
						 "23":20,
						 "24":20,
	]));
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));
	setup();
}

// 函数：对话处理
void do_look(object who)
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    " + "/quest/word"->get_normal_word(me) + "\n", me->get_name());
	result += sprintf(ESC "Bạn muốn mua gì nào？\ntalk %x# welcome.99\n", getoid(me));
	result += sprintf(ESC "Giao dịch\nlist0 %x#\n" ESC "Rời khỏi\nCLOSE\n", getoid(me));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}

void do_welcome(string arg)
{
	object me = this_object();
	"/npc/base/0005"->do_welcome2(me, "99");
}