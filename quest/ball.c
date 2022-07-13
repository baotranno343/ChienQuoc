void drop_black_ball(object me)
{
	object item, leader;
	int i, p;
	string owner, id;
	int z, x, y;
	item = new ("/item/04/0443");
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = me->get_leader();
	if (!id)
		owner = me->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = me->get_id();
	}
	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	{
		TEAM_D->drop_item(item, me);
		item->set_user_id(owner);
		ITEM_EQUIP_D->init_equip_prop(item);
		item->add_to_scene(z, p / 1000, p % 1000);
		item->set("winner", me);
		item->set("time", time());
	}
	else
		destruct(item);
}

void drop_blue_ball(object me)
{
	object item, leader;
	int i, p;
	string owner, id;
	int z, x, y;
	item = new ("/item/04/0444");
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = me->get_leader();
	if (!id)
		owner = me->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = me->get_id();
	}
	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	{
		TEAM_D->drop_item(item, me);
		item->set_user_id(owner);
		ITEM_EQUIP_D->init_equip_prop(item);
		item->add_to_scene(z, p / 1000, p % 1000);
		item->set("winner", me);
		item->set("time", time());
	}
	else
		destruct(item);
}

void drop_red_ball(object me)
{
	object item, leader;
	int i, p;
	string owner, id;
	int z, x, y;
	item = new ("/item/04/0445");
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = me->get_leader();
	if (!id)
		owner = me->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = me->get_id();
	}
	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	{
		TEAM_D->drop_item(item, me);
		item->set_user_id(owner);
		ITEM_EQUIP_D->init_equip_prop(item);
		item->add_to_scene(z, p / 1000, p % 1000);
		item->set("winner", me);
		item->set("time", time());
	}
	else
		destruct(item);
}

void drop_flower_ball(object me)
{
	object item, leader;
	int i, p;
	string owner, id;
	int z, x, y;
	item = new ("/item/04/0446");
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = me->get_leader();
	if (!id)
		owner = me->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = me->get_id();
	}
	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	{
		TEAM_D->drop_item(item, me);
		item->set_user_id(owner);
		ITEM_EQUIP_D->init_equip_prop(item);
		item->add_to_scene(z, p / 1000, p % 1000);
		item->set("winner", me);
		item->set("time", time());
	}
	else
		destruct(item);
}