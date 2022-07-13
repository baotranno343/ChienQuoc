#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

void create()
{
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, i, size;
	mixed *mixTime;
	object *user;
	remove_call_out("check_time");
	iTime = time();
	mixTime = localtime(iTime);
	i = 60 * (60 - mixTime[TIME_MIN]);

	if (mixTime[TIME_HOUR] == 0 && mixTime[TIME_MIN] == 0) // 0 giờ thì xóa save
	{

		if (arrayp(user = USER_D->get_user()))
		{
			size = sizeof(user);
			if (size < 200)
			{

				for (i = 0; i < size; i++)
					if (user[i])
					{
						"cmd/func/allfunc"->xoa_save(user[i], 1);
						if (mixTime[TIME_MDAY] == 1)
							"cmd/func/allfunc"->check_chientruong(user[i]);
					}
			}
		}
	}
	call_out("check_time", 3600 * (23 - mixTime[TIME_HOUR]) + 60 * (59 - mixTime[TIME_MIN]) + (60 - mixTime[TIME_SEC]));

	return;
}
