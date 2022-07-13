#include <item.h>
#include <ansi.h>
#include <equip.h>

int check_match(object equip, object diamond);
int mix1(object me, object *item);

// 函数：命令处理
int main(object me, string arg)
{
	object *item, who;
	string name, make, result, forge, index, ngoc, ngoc1, ngoc2, ngoc3, ngoc4;
	int *id;
	int i, flag, level, rate, xx, ben, ben2, cap, cap1, cap2, cap3, cap4, check1, check2, check3, check4, check5;

	if (!arg)
		return 1;

	item = ({
		0,
		0,
		0,
		0,
		0,
	});
	id = ({
		0,
		0,
		0,
		0,
		0,
	});

	if (sscanf(arg, "%x# %x# %x# %x# %x#", id[0], id[1], id[2], id[3], id[4]) == 5)
	{
		if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
			return 1;
		}
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Số lượng 2 trở lên mới có thể Hợp thành !");
			return 1;
		} //1-2-3-4
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Số lượng 2 trở lên mới có thể Hợp thành !");
			return 1;
		} //1-2-3-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Số lượng 2 trở lên mới có thể Hợp thành !");
			return 1;
		} //1-2-4-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Số lượng 2 trở lên mới có thể Hợp thành !");
			return 1;
		} //1-3-4-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Số lượng 2 trở lên mới có thể Hợp thành !");
			return 1;
		} //2-3-4-5
		//=======================================
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-2-3-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-2-4-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-3-4-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-3-4-5
		//===============================
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-4
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-3
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //3-4-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //4-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //3-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //3-4
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-4
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-3
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-3-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-4-5
		if (sprintf("%x#", id[0]) == "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //2-3-4
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-4-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-3-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) == "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-3-4
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-2-5
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			notify("Xin sắp xếp đúng thứ tự !");
			return 1;
		} //1-2-4
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) != "0#")
		{
			ben = 5;
			xx = 100;
		} // Tỉ lệ thành công cánh pp
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) != "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			ben = 4;
			xx = 50;
		}
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) != "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			ben = 3;
			xx = 30;
		}
		if (sprintf("%x#", id[0]) != "0#" &&
			sprintf("%x#", id[1]) != "0#" &&
			sprintf("%x#", id[2]) == "0#" &&
			sprintf("%x#", id[3]) == "0#" &&
			sprintf("%x#", id[4]) == "0#")
		{
			ben = 2;
			xx = 20;
		}
		for (i = 0; i < ben; i++)
		{
			if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
			{
				return 1;
			}
		}
		if (ben == 2)
		{
			if (item[0] == item[1])
			{
				notify("Sai quy tắc ! Không thể hợp thành !");
				return 1;
			}
			for (i = 0; i < 2; i++)
			{
				if (!item[i]->is_nangcap())
				{
					if (item[i]->get_item_type() != ITEM_TYPE_DIAMOND_3)
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (!item[i]->get_real_name())
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (item[i]->get_no_give())
					{
						notify("Loại Tinh thạch này không thể hợp thành!");
						return 1;
					}
					if (item[i]->get_diamond_type() == "forge")
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
				}
			}
			if (!item[0]->is_nangcap())
			{
				if (item[0]->get_real_name() != item[1]->get_real_name())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_diamond_type() != item[1]->get_diamond_type())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_level() != item[1]->get_level())
				{
					notify("Cấp bậc Tinh thạch không tương xứng.");
					return 1;
				}
			}
			else
			{
				ngoc = item[0]->get("make");
				ngoc1 = item[1]->get("make");
				if (ngoc == 0)
					ngoc = "";
				if (ngoc1 == 0)
					ngoc1 = "";
				cap = strlen(ngoc);
				cap1 = strlen(ngoc1);
				if (item[0]->get_name() != item[1]->get_name())
				{
					notify("Phi Phong hoặc Cánh không cùng loại.");
					return 1;
				}
				if (cap != cap1)
				{
					notify("Phi Phong hoặc Cánh không cùng cấp.");
					return 1;
				}
				if (cap >= 3)
				{
					notify("Phi Phong hoặc Cánh đã đạt giới hạn.");
					return 1;
				}
			}
		}
		if (ben == 3)
		{
			if (item[0] == item[1] || item[0] == item[2] || item[1] == item[2])
			{
				notify("Sai quy tắc ! Không thể hợp thành !");
				return 1;
			}
			for (i = 0; i < 3; i++)
			{
				if (!item[i]->is_nangcap())
				{
					if (item[i]->get_item_type() != ITEM_TYPE_DIAMOND_3)
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (!item[i]->get_real_name())
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (item[i]->get_no_give())
					{
						notify("Loại Tinh thạch này không thể hợp thành!");
						return 1;
					}
					if (item[i]->get_diamond_type() == "forge")
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
				}
			}
			if (!item[0]->is_nangcap())
			{
				if (item[0]->get_real_name() != item[1]->get_real_name() ||
					item[0]->get_real_name() != item[2]->get_real_name() ||
					item[1]->get_real_name() != item[2]->get_real_name())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_diamond_type() != item[1]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[2]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[2]->get_diamond_type())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_level() != item[1]->get_level() ||
					item[0]->get_level() != item[2]->get_level() ||
					item[1]->get_level() != item[2]->get_level())
				{
					notify("Cấp bậc Tinh thạch không tương xứng.");
					return 1;
				}
			}
			else
			{
				ngoc = item[0]->get("make");
				ngoc1 = item[1]->get("make");
				ngoc2 = item[2]->get("make");
				if (ngoc == 0)
					ngoc = "";
				if (ngoc1 == 0)
					ngoc1 = "";
				if (ngoc2 == 0)
					ngoc2 = "";
				cap = strlen(ngoc);
				cap1 = strlen(ngoc1);
				cap2 = strlen(ngoc2);
				if (item[0]->get_name() != item[1]->get_name() ||
					item[0]->get_name() != item[2]->get_name() ||
					item[1]->get_name() != item[2]->get_name())
				{
					notify("Phi Phong hoặc Cánh không cùng loại.");
					return 1;
				}
				if (cap != cap1 || cap != cap2 || cap1 != cap2)
				{
					notify("Phi Phong hoặc Cánh không cùng cấp.");
					return 1;
				}
				if (cap >= 3)
				{
					notify("Phi Phong hoặc Cánh đã đạt giới hạn.");
					return 1;
				}
			}
		}
		if (ben == 4)
		{
			if (item[0] == item[1] || item[0] == item[2] || item[0] == item[3] || item[1] == item[2] || item[1] == item[3] || item[2] == item[3])
			{
				notify("Sai quy tắc ! Không thể hợp thành !");
				return 1;
			}
			for (i = 0; i < 4; i++)
			{
				if (!item[i]->is_nangcap())
				{
					if (item[i]->get_item_type() != ITEM_TYPE_DIAMOND_3)
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (!item[i]->get_real_name())
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (item[i]->get_no_give())
					{
						notify("Loại Tinh thạch này không thể hợp thành!");
						return 1;
					}
					if (item[i]->get_diamond_type() == "forge")
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
				}
			}
			if (!item[0]->is_nangcap())
			{
				if (item[0]->get_real_name() != item[1]->get_real_name() ||
					item[0]->get_real_name() != item[2]->get_real_name() ||
					item[0]->get_real_name() != item[3]->get_real_name() ||
					item[1]->get_real_name() != item[2]->get_real_name() ||
					item[1]->get_real_name() != item[3]->get_real_name() ||
					item[2]->get_real_name() != item[3]->get_real_name())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_diamond_type() != item[1]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[2]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[3]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[2]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[3]->get_diamond_type() ||
					item[2]->get_diamond_type() != item[3]->get_diamond_type())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_level() != item[1]->get_level() ||
					item[0]->get_level() != item[2]->get_level() ||
					item[0]->get_level() != item[3]->get_level() ||
					item[1]->get_level() != item[2]->get_level() ||
					item[1]->get_level() != item[3]->get_level() ||
					item[2]->get_level() != item[3]->get_level())
				{
					notify("Cấp bậc Tinh thạch không tương xứng.");
					return 1;
				}
			}
			else
			{
				ngoc = item[0]->get("make");
				ngoc1 = item[1]->get("make");
				ngoc2 = item[2]->get("make");
				ngoc3 = item[3]->get("make");
				if (ngoc == 0)
					ngoc = "";
				if (ngoc1 == 0)
					ngoc1 = "";
				if (ngoc2 == 0)
					ngoc2 = "";
				if (ngoc3 == 0)
					ngoc3 = "";
				cap = strlen(ngoc);
				cap1 = strlen(ngoc1);
				cap2 = strlen(ngoc2);
				cap3 = strlen(ngoc3);
				if (item[0]->get_name() != item[1]->get_name() ||
					item[0]->get_name() != item[2]->get_name() ||
					item[0]->get_name() != item[3]->get_name() ||
					item[1]->get_name() != item[2]->get_name() ||
					item[1]->get_name() != item[3]->get_name() ||
					item[2]->get_name() != item[3]->get_name())
				{
					notify("Phi Phong hoặc Cánh không cùng loại.");
					return 1;
				}
				if (cap != cap1 || cap != cap2 || cap != cap3 || cap1 != cap2 || cap1 != cap3 || cap2 != cap3)
				{
					notify("Phi Phong hoặc Cánh không cùng cấp.");
					return 1;
				}
				if (cap >= 3)
				{
					notify("Phi Phong hoặc Cánh đã đạt giới hạn.");
					return 1;
				}
			}
		}
		if (ben == 5)
		{
			if (item[0] == item[1] || item[0] == item[2] || item[0] == item[3] || item[0] == item[4] || item[1] == item[2] || item[1] == item[3] || item[1] == item[4] || item[2] == item[3] || item[2] == item[4] || item[3] == item[4])
			{
				notify("Sai quy tắc ! Không thể hợp thành !");
				return 1;
			}
			for (i = 0; i < 5; i++)
			{
				if (!item[i]->is_nangcap())
				{
					if (item[i]->get_item_type() != ITEM_TYPE_DIAMOND_3)
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (!item[i]->get_real_name())
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
					if (item[i]->get_no_give())
					{
						notify("Loại Tinh thạch này không thể hợp thành!");
						return 1;
					}
					if (item[i]->get_diamond_type() == "forge")
					{
						notify("%s không phải Tinh thạch.", item[i]->get_name());
						return 1;
					}
				}
				else
				{
					if (item[i]->get_no_give())
					{
						notify("Phi phong và cánh khóa không thể hợp thành!");
						return 1;
					}
				}
			}
			if (!item[0]->is_nangcap())
			{
				if (item[0]->get_real_name() != item[1]->get_real_name() ||
					item[0]->get_real_name() != item[2]->get_real_name() ||
					item[0]->get_real_name() != item[3]->get_real_name() ||
					item[0]->get_real_name() != item[4]->get_real_name() ||
					item[1]->get_real_name() != item[2]->get_real_name() ||
					item[1]->get_real_name() != item[3]->get_real_name() ||
					item[1]->get_real_name() != item[4]->get_real_name() ||
					item[2]->get_real_name() != item[3]->get_real_name() ||
					item[2]->get_real_name() != item[4]->get_real_name() ||
					item[3]->get_real_name() != item[4]->get_real_name())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_diamond_type() != item[1]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[2]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[3]->get_diamond_type() ||
					item[0]->get_diamond_type() != item[4]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[2]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[3]->get_diamond_type() ||
					item[1]->get_diamond_type() != item[4]->get_diamond_type() ||
					item[2]->get_diamond_type() != item[3]->get_diamond_type() ||
					item[2]->get_diamond_type() != item[4]->get_diamond_type() ||
					item[3]->get_diamond_type() != item[4]->get_diamond_type())
				{
					notify("Tinh thạch không cùng loại.");
					return 1;
				}
				if (item[0]->get_level() != item[1]->get_level() ||
					item[0]->get_level() != item[2]->get_level() ||
					item[0]->get_level() != item[3]->get_level() ||
					item[0]->get_level() != item[4]->get_level() ||
					item[1]->get_level() != item[2]->get_level() ||
					item[1]->get_level() != item[3]->get_level() ||
					item[1]->get_level() != item[4]->get_level() ||
					item[2]->get_level() != item[3]->get_level() ||
					item[2]->get_level() != item[4]->get_level() ||
					item[3]->get_level() != item[4]->get_level())
				{
					notify("Cấp bậc Tinh thạch không tương xứng.");
					return 1;
				}
			}
			else
			{
				ngoc = item[0]->get("make");
				ngoc1 = item[1]->get("make");
				ngoc2 = item[2]->get("make");
				ngoc3 = item[3]->get("make");
				ngoc4 = item[4]->get("make");
				if (ngoc == 0)
					ngoc = "";
				if (ngoc1 == 0)
					ngoc1 = "";
				if (ngoc2 == 0)
					ngoc2 = "";
				if (ngoc3 == 0)
					ngoc3 = "";
				if (ngoc4 == 0)
					ngoc4 = "";
				cap = strlen(ngoc);
				cap1 = strlen(ngoc1);
				cap2 = strlen(ngoc2);
				cap3 = strlen(ngoc3);
				cap4 = strlen(ngoc4);
				if (item[0]->get_name() != item[1]->get_name() ||
					item[0]->get_name() != item[2]->get_name() ||
					item[0]->get_name() != item[3]->get_name() ||
					item[0]->get_name() != item[4]->get_name() ||
					item[1]->get_name() != item[2]->get_name() ||
					item[1]->get_name() != item[3]->get_name() ||
					item[1]->get_name() != item[4]->get_name() ||
					item[2]->get_name() != item[3]->get_name() ||
					item[2]->get_name() != item[4]->get_name() ||
					item[3]->get_name() != item[4]->get_name())
				{
					notify("Phi Phong hoặc Cánh không cùng loại.");
					return 1;
				}
				if (cap != cap1 || cap != cap2 || cap != cap3 || cap != cap4 || cap1 != cap2 || cap1 != cap3 || cap1 != cap4 || cap2 != cap3 || cap2 != cap4 || cap3 != cap4)
				{
					notify("Phi Phong hoặc Cánh không cùng cấp.");
					return 1;
				}
				// giới hạn phi phong +0
				// if (cap >= 0)
				// {
				// 	notify("Hiện Tại Phi Phong hoặc Cánh đã đạt giới hạn.");
				// 	return 1;
				// }
				if (cap >= 3)
				{
					notify("Phi Phong hoặc Cánh đã đạt giới hạn.");
					return 1;
				}
			}
		}
		// check1 = item[0] ? item[0]->get_no_give() : 0;
		// check2 = item[1] ? item[1]->get_no_give() : 0;
		// check3 = item[2] ? item[2]->get_no_give() : 0;
		// check4 = item[3] ? item[3]->get_no_give() : 0;
		// check5 = item[4] ? item[4]->get_no_give() : 0;
		// if (check1 || check2 || check3 || check4 || check5)
		// {
		// 	notify("Vật Phẩm khóa không thể hợp thành");
		// 	return 1;
		// }

		if (!item[0]->is_nangcap())
		{
			if (item[0]->get_level() >= 10)
			{
				notify("Cấp bậc của Tinh thạch đã đạt 10.");
				return 1;
			}
		}
		else
		{
			if (strlen(item[0]->get("make")) >= 0)
			{
				notify("Cấp bậc của Phi Phong đã đạt tối đa");
				return 1;
			}
		}
		if (me->get_strength() < 5)
		{
			notify("Thể lực không đủ 5 điểm.");
			return 1;
		}

		me->add_strength(-5);
		if (is_god(me))
			tell_user(me, sprintf("Số lượng %d, xác xuất thành công %d", ben, xx));
		if (random100() < xx)
		{
			if (!item[0]->is_nangcap())
			{
				level = item[0]->get_level();
				item[0]->set_level(level + 1);
				item[0]->add_to_user(get_d(item[0]));
				write_user(me, sprintf(ECHO "Hợp thành %s lên %s thành công !",
									   item[1]->get_name(), item[0]->get_name()));
			}
			else
			{
				ngoc = item[0]->get("make");
				if (ngoc == 0)
					ngoc = "";
				ngoc += "b";
				item[0]->set("make", ngoc);
				// check1 = item[0] ? item[0]->get_no_give() : 0;
				// check2 = item[1] ? item[1]->get_no_give() : 0;
				// check3 = item[2] ? item[2]->get_no_give() : 0;
				// check4 = item[3] ? item[3]->get_no_give() : 0;
				// check5 = item[4] ? item[4]->get_no_give() : 0;
				// if (check1 || check2 || check3 || check4 || check5)
				// {
				// 	item[0]->set_no_give(1);
				// }
				if (item[0]->get_name() == "Vương Giả Phi Phong" || item[0]->get_name() == "Xí Nhiệt Phi Phong")
				{
					item[0]->add("ap", 250);
					item[0]->add("pp", 250);
					item[0]->add("hp", 650);
					item[0]->add("mp", 650);
					item[0]->add("double", 400);
					item[0]->add("sp", 50);
				}
				if (item[0]->get_name() == "Thánh Linh Chi Dực·Trắng Thuần" ||
					item[0]->get_name() == "Thánh Linh Chi Dực·Vàng Nhạt")
				{
					item[0]->add("cp", 250);
					item[0]->add("dp", 250);
					item[0]->add("hp", 650);
					item[0]->add("mp", 650);
					item[0]->add("double", 550);
					item[0]->add("sp", 15);
				}

				item[0]->add_to_user(get_d(item[0]));
				write_user(me, sprintf(ECHO "Bạn nhận được %s +%d !",
									   item[0]->get_name(), strlen(item[0]->get("make"))));
			}
			item[1]->remove_from_user();
			destruct(item[1]);
			if (item[2])
			{
				item[2]->remove_from_user();
				destruct(item[2]);
			}
			if (item[3])
			{
				item[3]->remove_from_user();
				destruct(item[3]);
			}
			if (item[4])
			{
				item[4]->remove_from_user();
				destruct(item[4]);
			}

			notify("Hợp thành vật phẩm thành công !");
			return 1;
		}
		else
		{
			if (!item[0]->is_nangcap())
				write_user(me, ECHO "Hợp thành thất bại, Tinh thạch biến mất !");
			else
				write_user(me, sprintf(ECHO "Hợp thành thất bại, %s biến mất !", item[0]->get_name()));
			item[0]->remove_from_user();
			destruct(item[0]);
			item[1]->remove_from_user();
			destruct(item[1]);
			if (item[2])
			{
				item[2]->remove_from_user();
				destruct(item[2]);
			}
			if (item[3])
			{
				item[3]->remove_from_user();
				destruct(item[3]);
			}
			if (item[4])
			{
				item[4]->remove_from_user();
				destruct(item[4]);
			}
			notify("Hợp thành thất bại !");
			return 1;
		}
	}
	else
	{
		notify("Ngươi muốn hợp thành vật gì?");
		return 1;
	}
}
