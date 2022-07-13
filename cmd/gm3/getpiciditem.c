
#include <ansi.h>
#include <equip.h>

// 函数：命令处理
int main(object me, string arg)
{
	object item;
	string *weapon, file;
	string cmd1, cmd2, cmd3, cmd4;
	int family, z, x, y, p, i, size;
	int min, max, range, pic;
	if (is_player(me))
	{
		notify("您没有足够的权限。");
		return 1;
	}
	z = get_z(me), x = get_x(me), y = get_y(me);

	if (!arg || sscanf(arg, "%d %d", min, max) != 2)
		return 1; //Kiểm tra và scan giá trị

	for (i = 0; i < 20; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{

			//int max = 13000, min = 11000, range;
			range = max - min + 1;
			pic = random(20000) % range + min;
			item = new (sprintf("item/01/0001"));
			item->set_picid_1(pic);
			item->set_picid_2(pic);
			item->set_name(sprintf("%d", pic));

			item->add_to_scene(z, p / 1000, p % 1000);
		}
	}
	/*    for (i = 0; i< 1; i++)
        {        	
        	if ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
        	{
        		item = new ("/item/04/0438");
        		item->set_amount(5);
        		item->add_to_scene(z, p / 1000, p % 1000);
        	}
        }  */
	log_file("gm/gm3.dat", sprintf(" %s %s ( %d ) phần thưởng hoạt động %d ( %d %d )\n", short_time(), me->get_id(), me->get_number(), get_z(me), get_x(me), get_y(me)));
	return 1;
}
