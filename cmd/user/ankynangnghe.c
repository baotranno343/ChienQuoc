#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me)
{

	object file;
	mapping skls;
	string *name, fam;
	int level, skill, flag;
	int i, size;

	if (me->get("ankynangnghe") == 1)
	{
		me->set("ankynangnghe", 2);
		if (mapp(skls = me->get_skill_dbase()) && sizeof(skls))
		{
			name = keys(skls);
			for (i = 0, size = sizeof(name); i < size; i++)
			{
				skill = to_int(name[i]);
				if (skill >= 610 && skill <= 680)
					me->delete_skill();
				send_user(me, "%c%c%w", 0x60, 0, skill);
			}
		}
		tell_user(me, "Bạn đã ẩn kỹ năng nghề");
	}
	else
	{
		me->set("ankynangnghe", 1);
		if (mapp(skls = me->get_skill_dbase()) && sizeof(skls)) // 列示特殊技
		{

			name = sort_array(keys(skls), 1);
			for (i = 0, size = sizeof(name); i < size; i++)
			{
				skill = to_int(name[i]);
				if ((file = load_object(SKILL->get_skill_file(skill))) && file->get_name())
				{
					if (file->is_vita_skill())
						send_user(me, "%c%c%w%w%d%s", 0x60, 1, skill, me->get_skill(skill), me->get_skill_degree(skill), file->get_name());
					file->can_perform(me);
				}
			}
		}
		tell_user(me, "Bạn đã kích hoạt kỹ năng nghề");
	}

	return 1;
}