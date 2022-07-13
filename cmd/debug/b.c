#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int p, diem;
	string result, arg2, arg3;
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
	if (sscanf(arg, "%s %s", arg2, arg3) != 2)
		return 1;
	if (arg2 && !(who = find_any_char(arg2)))
	{
		write_user(me, ECHO "Không tìm thấy người này !");
		return 1;
	}

	switch (arg3)
	{
	case "pk+":
		who->set_save("gietnguoi", 1);
		who->add_pk(100);
		write_user(me, sprintf(ECHO "Điểm PK của %s(%d) tăng thêm 100, hiện tại có %d điểm PK.", who->get_name(), who->get_number(), who->get_pk()));
		write_user(who, sprintf(ECHO "Điểm PK của bạn tăng thêm 100, hiện tại bạn có %d điểm PK.", who->get_pk()));
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		return 1;
		break;
	case "pk-":
		if (who->get_pk() <= 0)
			return 1;
		if (who->get_pk() >= 100)
		{
			who->add_pk(-100);
			write_user(me, sprintf(ECHO "Điểm PK của %s(%d) giảm 100, hiện tại có %d điểm PK.", who->get_name(), who->get_number(), who->get_pk()));
			write_user(who, sprintf(ECHO "Điểm PK của bạn giảm 100, hiện tại bạn có %d điểm PK.", who->get_pk()));
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		}
		else if (who->get_pk() < 100)
		{
			send_user(me, "%c%s", '!', sprintf("%s(%d) đã giảm %d điểm PK", who->get_name(), who->get_number(), who->get_pk()));
			send_user(who, "%c%s", '!', sprintf("Bạn đã giảm %d điểm PK", who->get_pk()));
			who->add_pk(-who->get_pk());
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		}
		return 1;
		break;
	}

	return 1;
}