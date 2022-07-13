#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int p, diem;
	string result, arg2;
	object item, item1, who;

	if (is_player(me))
	{
		write_user(me, ECHO "Bạn không đủ quyền hạn !");
		return 1;
	}

	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "%s %d", arg2, diem) == 2)
	{
		if (arg2 && !(who = find_any_object(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			return 1;
		}
		who->add_exp(diem);
	}

	return 1;
}