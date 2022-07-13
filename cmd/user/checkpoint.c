#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{
	string arg2, ketqua, *so;

	so = ({"kkss", "jddt", "ollx", "zill", "goow", "azxx", "kzll", "oakk", "sjja", "xloo"});
	ketqua = so[random(10)];
	if (!arg)
	{
		me->set("checkpoint", ketqua);
		send_user(me, "%c%c%d%s", '?', 16, 5, "Xin nhập mã: " + ketqua + "    (Tối đa 5 ký tự):\n" ESC "checkpoint + %s\n");
		return 1;
	}
	if (arg == 0)
		return 1;
	if (sscanf(arg, "+ %s", arg2) != 1)
		return 1;

	if (arg2 == me->get("checkpoint"))
	{
		send_user(me, "%c%s", ';', "Xác minh thành công bạn có thể vào lại!.");
		me->set("checkpointsuccess", 1);
	}
	else
	{
		"cmd/user/checkpoint"->main(me);
		send_user(me, "%c%s", ';', "Xác minh thất bại hãy thử lại!.");
	}
	// 20 code

	return 1;
}