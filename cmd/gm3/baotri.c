
#include <ansi.h>
#include <cmd.h>
#include <city.h>
int tatgame();
// 函数：命令处理
int main(object me, string arg)
{
	object *user, who;
	int z, x, y, x0, y0, p, i, size, number, kenh;
	string *list = MAIN_D->getlist();
	kenh = MAIN_D->get_kenh();
	if (is_player(me))
	{
		notify("Không đủ quyền hạn.");
		return 1;
	}

	if (arg == "0" || arg == "1")
	{
		rm("baotri.txt");
		ghi_file("baotri.txt", arg);
	}
	if (arg == "0")
	{
		tell_user(me, "Đã tắt Bảo Trì");
	}
	if (arg == "1")
	{
		for (i = 0; i < sizeof(list); i++)
		{
			if (kenh == to_int(list[i]))
				continue;
			ghi_file(sprintf("bang/check%s.txt", list[i]), "\nkickall");
		}
		"cmd/debug/kickall"->kick_all();
		tell_user(me, "Đã Bảo Trì");
	}

	return 1;
}
int baotri()
{
	int i, kenh;
	string *list = MAIN_D->getlist();
	kenh = MAIN_D->get_kenh();

	rm("baotri.txt");
	ghi_file("baotri.txt", "1");

	for (i = 0; i < sizeof(list); i++)
	{
		if (kenh == to_int(list[i]))
			continue;
		ghi_file(sprintf("bang/check%s.txt", list[i]), "\nkickall");
	}
	"cmd/debug/kickall"->kick_all();
	return 1;
}
int baotri0()
{
	rm("baotri.txt");
	ghi_file("baotri.txt", 0);
	return 1;
}