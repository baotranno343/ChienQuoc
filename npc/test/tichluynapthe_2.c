#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

int iStart2, iFinish2, close_val, open_val, BatDau, KetThuc;

// 函数:获取人物造型
int get_char_picid() { return 9971; }
void do_gift(string arg);
// 函数：小贩识别
int is_seller() { return 7010; }
int is_self_look() { return 1; }

void create()
{

	set_name("Thiên Nhân");
	set_real_name("Sứ Giả Tích Lũy");
	set_2("good", ([
					  //"01":"/ken/goiquy/50",
					  "01":"/ken/goiquy/100",
					  "02":"/ken/goiquy/200",
					  "03":"/ken/goiquy/500",
					  "04":"/ken/goiquy/1000",

					  //	"05" : "/item/sell/0031",
					  //	"06" : "/item/sell/0031_2",
	]));
	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	int dtlnt = who->get_save("diemtlnt");
	object me = this_object();
	string result;
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ngươi hiện có:" HIR " %d " NOR " Điểm Tích Lũy Nạp Thẻ \n" ESC HIY "Mua vật phẩm (Bằng Điểm Tích Lũy Nạp Thẻ)\nlist10 %x#\n" ESC "Rời khỏi", get_name(), dtlnt, id, id, id, id, id));
}
