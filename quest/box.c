object * get_item(int level)
{
	string file;
	file = sprintf("/quest/box%d", level);
	if (load_object(file))
		return file->get_item();
	else
		return "/quest/box1"->get_item();
}

void give_box(object me)
{
	object item;
	int i, p;
	string result;
	if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY ) return ;
	i = random100();
	if (i<30)
		item = new ("/item/01/0200");
	else
	if (i<70)
		item = new ("/item/01/0201");
	else
		item = new ("/item/01/0202");	
	result = sprintf("Bạn đạt được %s .", item->get_name());
	if( p = item->move(me, -1) )
	{
	        item->add_to_user(p);
	}		
	tell_user(me, result);
	"/sys/sys/count"->add_boxcount(1);
}


void drop_box(object me)
{
	object item, leader;
	int i, p;
	string owner, id;	
	int z, x, y;
	i = random100();
	if (i<30)
		item = new ("/item/01/0200");
	else
	if (i<70)
		item = new ("/item/01/0201");
	else
		item = new ("/item/01/0202");			
	z = get_z(me);  x = get_x(me);  y = get_y(me);
	id = me->get_leader();
        if (!id) owner = me->get_id();
        else
        {
        	if ( leader = find_player(id ) )
        	{
        		owner = leader->get_id();
		}      
		else
			owner = me->get_id();  		
	}	
	if ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
	{
		TEAM_D->drop_item(item,me);
	        item->set_user_id(owner);
	        ITEM_EQUIP_D->init_equip_prop(item);
	        item->add_to_scene(z, p / 1000, p % 1000);
	        item->set("winner", me);
	        item->set( "time", time() );	
	}
	else destruct(item);	    
	"/sys/sys/count"->add_boxcount(1);   	
}