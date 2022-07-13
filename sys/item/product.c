#include <effect.h>
#include <skill.h>
#include <ansi.h>
#include <item.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

mapping lvalue = (["0":({
						   55,
						   56,
						   57,
						   58,
					   }),
				   "1":({
						   58,
						   59,
						   60,
						   61,
					   }),
				   "2":({
						   61,
						   62,
						   63,
						   64,
						   65,
					   }),
				   "3":({
						   64,
						   65,
						   66,
						   67,
						   68,
					   }),
				   "4":({
						   67,
						   68,
						   69,
						   70,
						   71,
						   72,
					   }),
				   "5":({
						   71,
						   72,
						   73,
						   74,
						   75,
					   }),

]);

mapping lvalue2 = (["0":({
							101,
						}),
					"1":({
							101,
							102,
						}),
					"2":({
							101,
							102,
						}),
					"3":({
							102,
							103,
							104,
						}),
					"4":({
							103,
							104,
							105,
						}),
					"5":({
							104,
							105,
						}),

]);

mapping lvalue3 = (["0":({}),
					"1":({}),
					"2":({}),
					"3":({}),
					"4":({
							104,
							105,
						}),
					"5":({
							104,
							105,
						}),

]);
//中间产品掉落概率
mapping mpMidProduct = (["/item/stuff/0009":400,
						 "/item/stuff/0020":20, "/item/stuff/0085":120,
						 "/item/stuff/0010":170, "/item/stuff/0021":50, "/item/stuff/0063":120,
						 "/item/stuff/0011":220, "/item/stuff/0276":50, "/item/stuff/0086":120,
						 "/item/stuff/0012":40, "/item/stuff/0274":50, "/item/stuff/0064":120,
						 "/item/stuff/0013":50, "/item/stuff/0264":50, "/item/stuff/0087":120,
						 "/item/stuff/0196":170, "/item/stuff/0055":400, "/item/stuff/0065":120,
						 "/item/stuff/0199":220, "/item/stuff/0078":400, "/item/89/8991":300,
						 "/item/stuff/0197":180, "/item/stuff/0056":400, "/item/89/8994":60,
						 "/item/stuff/0200":50, "/item/stuff/0079":400, "/item/stuff/0088":50,
						 "/item/stuff/0198":100, "/item/stuff/0057":180, "/item/stuff/0066":50,
						 "/item/stuff/0203":180, "/item/stuff/0080":200, "/item/stuff/0089":50,
						 "/item/stuff/0204":160, "/item/stuff/0058":180, "/item/stuff/0067":50,
						 "/item/stuff/0208":100, "/item/stuff/0081":220, "/item/stuff/0093":50,
						 "/item/stuff/0040":400, "/item/stuff/0059":220, "/item/stuff/0070":50,
						 "/item/stuff/0043":10, "/item/stuff/0082":220, "/item/stuff/0095":50,
						 "/item/stuff/0041":100, "/item/89/8990":300, "/item/stuff/0073":50,
						 "/item/stuff/0207":270, "/item/89/8993":150, "/item/stuff/0098":50,
						 "/item/stuff/0206":270, "/item/stuff/0083":160, "/item/stuff/0075":50,
						 "/item/stuff/0209":100, "/item/stuff/0060":220, "/item/stuff/0096":50,
						 "/item/stuff/0017":400, "/item/stuff/0061":160, "/item/stuff/0072":150,
						 "/item/stuff/0018":220, "/item/stuff/0084":160, "/item/89/8995":50,
						 "/item/stuff/0019":50, "/item/stuff/0062":120,

]);

int *m_stuff = ({
	55,
	93,
	78,
	93,
	56,
	93,
	79,
	70,
	57,
	70,
	80,
	70,
	58,
	95,
	81,
	95,
	59,
	95,
	82,
	73,
	60,
	73,
	83,
	73,
	61,
	98,
	84,
	98,
	62,
	98,
	85,
	75,
	63,
	75,
	86,
	75,
	64,
	96,
	87,
	96,
	65,
	96,
	88,
	72,
	66,
	72,
	89,
	72,
	67,
	94,
	90,
	94,
	68,
	94,
	91,
	71,
	69,
	71,
	92,
	71,
	97,
	71,
});

int check_vita_skill(object me, int type);
int add_vita_skill(object me, int type);

int get_use_effect(object me, object obj)
{
	object *user, file;
	int type, skill;
	int *pf, i, size;
	if (obj->get_item_type_2() != ITEM_TYPE_2_PRODUCT)
		return 0;
	type = obj->get_product_type();
	if (type == 0)
		return 0;
	skill = obj->get_product_skill();
	if (!me->get_skill(skill))
	{
		send_user(me, "%c%s", '>', HIY "Bạn không học kĩ năng tương ứng");
		return 0;
	}
	if (me->get_skill(skill) < obj->get_product_level())
	{
		send_user(me, "%c%s", '>', HIY "Kĩ năng cấp bậc không đủ, không thể học");
		return 0;
	}
	/*	
	if (me->get_skill_degree(skill)<obj->get_product_exp())
	{
		send_user( me, "%c%s", '>', HIY"您的技能熟练度不够，无法学习.");
		return 0;
	}
	if (me->get_product_sort()&&me->get_product_sort()!=me->get_save_2(sprintf("vita.%dtype", skill)))
	{
		send_user( me, "%c%s", '>', HIY"您无法学习其他系的技能.");
		return 0;
	}
*/
	if (check_vita_skill(me, type + skill * 100) == 1)
	{
		send_user(me, "%c%s", '>', HIY "Bạn đã học kĩ năng này rồi");
		return 0;
	}
	add_vita_skill(me, type + skill * 100);
	if (file = load_object(SKILL->get_perform_file(type + skill * 100)))
		file->can_perform(me);
	return 1;
}

// 判断有无这个技能
int check_vita_skill(object me, int type)
{
	int skill;
	int *pf, i, size, pos;
	skill = type / 1000 * 10;
	if (!me->get_skill(skill))
		return -1;
	pos = type % 1000;
	i = pos / 32;
	pos = pos % 32;
	if (pos == 31)
	{
		pf = me->get_save_2(sprintf("vita2.%d", skill));
		size = sizeof(pf);
		if (i < size && pf[i] == 1)
			return 1;
	}
	pf = me->get_save_2(sprintf("vita.%d", skill));
	size = sizeof(pf);
	if (i >= size)
		return 0;
	if (pf[i] & (1 << pos))
		return 1;

	return 0;
}

// 增加生活特技标志
int add_vita_skill(object me, int type)
{
	int skill;
	int *pf, i, size, pos, *pf2, size2;
	skill = type / 1000 * 10;
	if (!me->get_skill(skill))
		return -1;
	pf = me->get_save_2(sprintf("vita.%d", skill));
	if (pf == 0)
		pf = ({});
	pos = type % 1000;
	size = sizeof(pf);
	while (size <= pos / 32)
	{
		pf += ({0});
		size++;
	}
	i = pos / 32;
	pos = pos % 32;
	pf[i] = pf[i] | (1 << pos);
	if (pos == 31)
	{
		pf2 = me->get_save_2(sprintf("vita2.%d", skill));
		if (pf2 == 0)
			pf2 = ({});
		size2 = sizeof(pf2);
		while (size2 <= i)
		{
			pf2 += ({0});
			size2++;
		}
		pf2[i] = 1;
		me->set_save_2(sprintf("vita2.%d", skill), pf2);
	}
	me->set_save_2(sprintf("vita.%d", skill), pf);
	return 1;
}

// 删除生活特技标志
int sub_vita_skill(object me, int type)
{
	int skill;
	int *pf, i, size, pos, *pf2, size2;
	skill = type / 1000 * 10;
	if (!me->get_skill(skill))
		return -1;
	pf = me->get_save_2(sprintf("vita.%d", skill));
	if (pf == 0)
		pf = ({});
	pos = type % 1000;
	size = sizeof(pf);
	while (size <= pos / 32)
	{
		pf += ({0});
		size++;
	}
	i = pos / 32;
	pos = pos % 32;
	pf[i] = pf[i] & (~(1 << pos));
	if (pos == 31)
	{
		pf2 = me->get_save_2(sprintf("vita2.%d", skill));
		if (pf2 == 0)
			pf2 = ({});
		size2 = sizeof(pf2);
		while (size2 <= i)
		{
			pf2 += ({0});
			size2++;
		}
		pf2[i] = 0;
		me->set_save_2(sprintf("vita2.%d", skill), pf2);
	}
	me->set_save_2(sprintf("vita.%d", skill), pf);
	return 1;
}

int find_stuff(object me, int type)
{
	object *inv, item;
	int ret = 0;
	int i, size;
	if (type == 0)
		return 0;
	inv = all_inventory(me, 1, MAX_CARRY * 4);
	inv -= ({0});
	for (i = 0, size = sizeof(inv); i < size; i++)
	{
		if (objectp(item = inv[i]))
		{
			if (item->get_stuff_type() == type || item->get_fin_type() == type)
			{
				if (item->get_amount() == 0)
					ret += 1;
				else
					ret += item->get_amount();
			}
		}
	}
	return ret;
}

void sub_stuff(object me, int type, int count)
{
	object *inv, item;
	int i, size, amount;
	if (type == 0)
		return;
	if (count == 0)
		return;
	inv = all_inventory(me, 1, MAX_CARRY * 4);
	inv -= ({0});
	for (i = 0, size = sizeof(inv); i < size; i++)
	{
		if (objectp(item = inv[i]))
		{
			if (item->get_stuff_type() == type || item->get_fin_type() == type)
			{
				amount = item->get_amount();
				if (amount == 0)
					amount = 1;
				if (count > amount)
				{
					count -= amount;
					if (item->get_amount() > 0)
						item->add_amount(-amount);
					else
					{
						item->remove_from_user();
						destruct(item);
					}
				}
				else
				{
					if (item->get_amount() > 0)
						item->add_amount(-count);
					else
					{
						item->remove_from_user();
						destruct(item);
					}
					count = 0;
					return;
				}
			}
		}
	}
}

string get_random_product()
{
	return "/quest/product2"->get_random_product();
}

string get_random_drop_product(int type)
{
	return "/quest/product2"->get_random_drop_product(type);
}

string get_random_diamond()
{
	int i = random(6);
	if (i < 3)
		return sprintf("/item/stuff/%04d", 55 + i);
	else
		return sprintf("/item/stuff/%04d", 78 + i - 3);
}

void make_item(object item, int type, int rate)
{
	int rate2;
	int base1, random1, base2, random2;
	string add1, add2;
	if (type == 1)
	{
		"/sys/item/equip"->init_equip_prop_1(item);
	}
	if (type == 2)
	{
		"/sys/item/equip"->init_equip_prop_3(item);
	}
	else
	{
		if (random(100) == 0)
			"/sys/item/equip"->init_equip_prop_1(item);
	}
	switch (item->get_equip_type())
	{
	case WEAPON_TYPE:
		if (item->get_weapon_type() == SWORD)
		{
			base1 = -3;
			random1 = 9;
			base2 = -5;
			random2 = 14;
		}
		else
		{
			base1 = -5;
			random1 = 14;
			base2 = 0;
			random2 = 0;
		}
		add1 = "ap";
		add2 = "cp";
		break;
	case ARMOR_TYPE:
	case HEAD_TYPE:
		switch (item->get_family())
		{
		case 2: // Thục Sơn
			base1 = -4;
			random1 = 12;
			base2 = -4;
			random1 = 12;
			break;
		case 1:
		case 3:
		case 4:
			base1 = -5;
			random1 = 14;
			base2 = -5;
			random1 = 11;
			break;
		default:
			base1 = -5;
			random1 = 14;
			base2 = -5;
			random1 = 11;
			break;
		}
		add1 = "dp", add2 = "pp";
		break;
	case BOOTS_TYPE:
		base1 = -2;
		random1 = 6;
		base1 = -4;
		random1 = 11;
		add1 = "dp", add2 = "sp";
		break;
	case WAIST_TYPE:
		switch (item->get_family())
		{
		case 2: // Thục Sơn
			base1 = -3;
			random1 = 10;
			base2 = -4;
			random1 = 10;
			break;
		case 1:
		case 3:
		case 4:
			base1 = -3;
			random1 = 10;
			base2 = 0;
			random1 = 0;
			break;
		default:
			base1 = -3;
			random1 = 10;
			base2 = -5;
			random1 = 14;
			break;
		}
		add1 = "pp", add2 = "pp";
		break;
	default:
		return;
	}
	if (rate == 0)
	{
		item->add(add1, base1 + random(random1));
		item->add(add2, base2 + random(random2));
	}
	else
	{
		rate2 = random(100);
		if (rate2 < rate)
		{
			item->add(add1, base1 + random1 - 1);
			item->add(add2, base2 + random2 - 1);
		}
		else
		{
			item->add(add1, random(random1 - 1));
			item->add(add2, random(random2 - 1));
		}
	}
}

string get_random_sell_product()
{
	return "/quest/product2"->get_random_drop_product(30);
}

int make_stuff(object player, object npc, object obj)
{
	int color, level, count, i, rand, *pvalue, size, total, amount, p, rate;
	object item;
	string file;
	if (!obj->is_equip() && (obj->is_diamond() != 2))
	{
		tell_user(player, ECHO "Vật phẩm ấy không có giá trị");
		return 1;
	}
	level = obj->get_level();
	if (player->get_skill(650) == 0)
	{
		tell_user(player, ECHO "Bạn không có kĩ năng Điêu Khắc");
		return 1;
	}
	if (player->get_skill(650) < level)
	{
		tell_user(player, ECHO "Kĩ năng Điêu Khắc của bạn không đủ cấp");
		return 1;
	}
	if (player->get_strength() < 1)
	{
		tell_user(player, ECHO "Điểm thể lực không có");
		return 1;
	}
	if (sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY - 1)
	{
		tell_user(player, ECHO "Phân giải trang bị ít nhất chừa 2 ô trống");
		return 1;
	}
	color = obj->get_item_color();
	if ((color == 0 || color == 4) && obj->get_equip_type() != NECK_TYPE)
	{
		tell_user(player, ECHO "Vật phẩm ấy không có giá trị");
		return 1;
	}
	if (obj->get_equip_type() == HAND_TYPE)
	{
		tell_user(player, ECHO "Vật phẩm ấy không có giá trị");
		return 1;
	}
	if (obj->get_equip_type() == NECK_TYPE)
	{
		if (color == 0)
			color = 1;
		if (color == 4)
			color = 1;
	}
	player->add_strength(-1);
	level /= 5;
	if (level > 30)
		level = 30;
	send_user(player, "%c%d", 0x2d, getoid(obj));
	destruct(obj);
	if (level <= 6)
		file = "/item/stuff/0101";
	else if (level <= 13)
		file = "/item/stuff/0102";
	else if (level <= 18)
		file = "/item/stuff/0103";
	else if (level <= 23)
		file = "/item/stuff/0104";
	else
		file = "/item/stuff/0105";
	item = new (file);
	if (item)
	{
		tell_user(player, ECHO "Bạn nhận được 1 cái %s.", item->get_name());
		total = 1;
		if (total > item->get_amount())
			total = item->get_amount();
		amount = USER_INVENTORY_D->carry_combined_item(player, item, total);
		if (amount > 0 && item->set_amount(amount))
		{
			if (p = item->move(player, -1))
			{
				item->add_to_user(p);
			}
		}
		else
			item->add_amount(-total);
	}
	if (color <= 1)
		rate = 75;
	else
		rate = 85;
	if (random100() < rate)
	{
		file = sprintf("/item/stuff/%04d", m_stuff[level * 2]);
		item = new (file);
		if (item)
		{
			tell_user(player, ECHO "Bạn nhận được 1 cái %s.", item->get_name());
			total = 1;
			if (total > item->get_amount())
				total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(player, item, total);
			if (amount > 0 && item->set_amount(amount))
			{
				if (p = item->move(player, -1))
				{
					item->add_to_user(p);
				}
			}
			else
				item->add_amount(-total);
		}
	}
	if (color <= 1)
		rate = 5;
	else
		rate = 100;
	if (random100() < rate)
	{
		file = sprintf("/item/stuff/%04d", m_stuff[level * 2 + 1]);
		item = new (file);
		if (item)
		{
			tell_user(player, ECHO "Bạn nhận được 1 cái %s.", item->get_name());
			total = 1;
			if (total > item->get_amount())
				total = item->get_amount();
			amount = USER_INVENTORY_D->carry_combined_item(player, item, total);
			if (amount > 0 && item->set_amount(amount))
			{
				if (p = item->move(player, -1))
				{
					item->add_to_user(p);
				}
			}
			else
				item->add_amount(-total);
		}
	}
}
// Phân giải đoạn thạch
int phangiai_dt(object me, object npc, object obj)
{
	int color, level, count, i, rand, *pvalue, size, total, amount, p, rate;
	object item;
	string file;
	if (!npc->is_cantuong_nangcaptb())
	{
		tell_user(me, ECHO "Chỉ có thể phân giải Đoạn Thạch tại Can Tương.");
		return 1;
	}
	if (obj->get_item_type() != ITEM_TYPE_DIAMOND_3)
	{
		tell_user(me, ECHO "Vật phẩm này không phải là Đoạn Thạch.");
		return 1;
	}
	if (me->get_strength() < 1)
	{
		tell_user(me, ECHO "Điểm thể lực không đủ 1 điểm.");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 1)
	{
		tell_user(me, ECHO "Hành trang không đủ 1 ô trống.");
		return 1;
	}
	if (obj->get_name() == "Sơ Cấp Đoạn Thạch")
	{
		if (objectp(item = present("Tái Tạo Thạch", me, 1, MAX_CARRY * 4)) && item->get_amount() < 10000)
		{
			item->add_amount(1);
			send_user(me, "%c%s", '!', "Bạn nhận được 1 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 1 Tái Tạo Thạch !");
		}
		else
		{
			item = new ("item/test2/thanbinhpho/taitaothach");
			item->set_amount(1);
			p = item->move2(me, -1);
			item->add_to_user(p);
			send_user(me, "%c%s", '!', "Bạn nhận được 1 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 1 Tái Tạo Thạch !");
		}
		me->add_strength(-1);
		obj->remove_from_user();
		destruct(obj);
	}
	else if (obj->get_name() == "Trung Cấp Đoạn Thạch")
	{
		if (objectp(item = present("Tái Tạo Thạch", me, 1, MAX_CARRY * 4)) && item->get_amount() < 10000)
		{
			item->add_amount(2);
			send_user(me, "%c%s", '!', "Bạn nhận được 2 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 2 Tái Tạo Thạch !");
		}
		else
		{
			item = new ("item/test2/thanbinhpho/taitaothach");
			item->set_amount(2);
			p = item->move2(me, -1);
			item->add_to_user(p);
			send_user(me, "%c%s", '!', "Bạn nhận được 2 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 2 Tái Tạo Thạch !");
		}
		me->add_strength(-1);
		obj->remove_from_user();
		destruct(obj);
	}
	else if (obj->get_name() == "Cao Cấp Đoạn Thạch")
	{
		if (objectp(item = present("Tái Tạo Thạch", me, 1, MAX_CARRY * 4)) && item->get_amount() < 10000)
		{
			item->add_amount(3);
			send_user(me, "%c%s", '!', "Bạn nhận được 3 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 3 Tái Tạo Thạch !");
		}
		else
		{
			item = new ("item/test2/thanbinhpho/taitaothach");
			item->set_amount(3);
			p = item->move2(me, -1);
			item->add_to_user(p);
			send_user(me, "%c%s", '!', "Bạn nhận được 3 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 3 Tái Tạo Thạch !");
		}
		me->add_strength(-1);
		obj->remove_from_user();
		destruct(obj);
	}
	else if (obj->get_name() == "Cao Cấp Đoạn Thạch bị kết dính")
	{
		if (objectp(item = present("Tái Tạo Thạch", me, 1, MAX_CARRY * 4)) && item->get_amount() < 10000)
		{
			item->add_amount(4);
			send_user(me, "%c%s", '!', "Bạn nhận được 4 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 4 Tái Tạo Thạch !");
		}
		else
		{
			item = new ("item/test2/thanbinhpho/taitaothach");
			item->set_amount(4);
			p = item->move2(me, -1);
			item->add_to_user(p);
			send_user(me, "%c%s", '!', "Bạn nhận được 4 Tái Tạo Thạch !");
			tell_user(me, ECHO "Bạn nhận được 4 Tái Tạo Thạch !");
		}
		me->add_strength(-1);
		obj->remove_from_user();
		destruct(obj);
	}
}

//随机取中间产品
string get_random_mid_product()
{
	int i, size, rate, count;
	string *nTmp, res;

	rate = random(10000);
	nTmp = keys(mpMidProduct);
	for (i = 0, size = sizeof(mpMidProduct); i < size; i++)
	{
		count += mpMidProduct[nTmp[i]];
		if (count > rate)
			break;
	}
	if (i < size)
		res = nTmp[i];
	else
		res = nTmp[random(size)];
	return res;
}