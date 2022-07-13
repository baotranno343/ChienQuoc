#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>

private
string *kt = ({
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
});
// 函数：命令处理
void main(object me, string arg)
{
	int i;
	string tx, code, code1;
	mixed *mixtime;
	mixtime = localtime(time());
	// if (mixtime[TIME_HOUR] > 5)
	// 	return;
	if (!arg)
	{
		code = "";
		if (!me->get("cap"))
			for (i = 0; i < 4; i++)
				code += kt[random(sizeof(kt))];
		else
			code = me->get("cap");
		me->set("cap", code);
		tx = sprintf("Hãy nhập những số sau:\n %s\n", code);
		send_user(me, "%c%c%d%s", '?', 16, 4, tx + ESC "checkpoint2 + %s\n");
		return;
	}
	else if (sscanf(arg, "+ %s", code1) == 1)
	{
		if (!code = me->get("cap"))
			return;
		else if (code != code1)
		{
			me->add("capsai", 1);
			if (me->get("capsai") == 5)
			{
				me->set_save("vaotu", 600);
				me->add_to_scene(704, 35, 25);
				send_user(me, "%c%c%w%s", ':', 3, 9963, "Giám Ngục Quan :\nNgươi đã trả lời sai 5 lần bị nhốt vào tù trong thời gian 10 phút !\n" ESC "Xác nhận\nCLOSE\n");
				send_user(me, "%c%s", ';', sprintf("%s (%d) đã bị Nhốt vào tù 10 phút", me->get_name(), me->get_number()));
				me->delete ("cap");
				me->delete ("capsai");
				return;
			}
			me->delete ("cap");
			"cmd/user/checkpoint2"->main(me);
			tell_user(me, "Bạn đã nhập sai mã");
		}
		else
		{
			tell_user(me, "Bạn đã nhập đúng mã");
			me->delete ("cap");
			me->delete ("capsai");
			return;
		}
	}
	return;
}