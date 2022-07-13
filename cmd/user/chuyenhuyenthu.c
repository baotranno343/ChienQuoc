#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me)
{

	if (me->get("zombie2"))
	{
		notify("Vui lòng tắt Huyễn thú đang triệu hồi!");
	}
	else
	{
		if (TASK_LEGEND_D->check_tui_huyenthu(me, "Huyễn Thú - Hỏa Sư") >= 1 || TASK_LEGEND_D->check_tui_huyenthu(me, "Huyễn Thú - Hắc Hỏa Sư") >= 1)
		{

			if (me->get("chuyenhuyenthu") == 1)
			{
				me->set("chuyenhuyenthu", 0);
				notify("Bạn đã thay đổi Huyễn Thú thành triệu hồi.");
			}

			else
			{
				me->set("chuyenhuyenthu", 1);
				notify("Bạn đã thay đổi Huyễn Thú thành thú cưỡi.");
			}
		}
		else
		{
			notify("Không có Huyễn Thú hoặc Huyễn Thú không đủ cấp");
		}
	}

	return 1;
}