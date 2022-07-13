inherit OFFICER;
inherit "/inh/std/box";

// 函数:构造处理
void create()
{
        set_name("Thanh Đồng Bảo Rương");
        set("time", 1);
        set("level", 1);
        set("reset_time", 3600);
        setup();
}

void drop_item(object me)
{
	int i, size, p, cash, amount, total, count;
	string file, result;
	object item, *team;
	size = 1 + random(3);
	result = "";
	for (i=0;i<size;i++)
	{
		p = random(10000);
		amount = 0;
		if( p < 2540)		// 金钱
		{
			cash = 2000+random(50);
			me->add_cash(cash);
			if (strlen(result)==0)
				result += sprintf(" %d lượng", cash);
			else
				result += sprintf(", %d lượng", cash);
			continue;
		} 
		if( p < 2550)		// 武器
		{
                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(20);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(30);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(40);  break;
                	}
                }
                else	
		if( p < 2560)		// 防具
		{
                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(20);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(30);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(40);  break;
                	}
		}
		else                            
		if( p < 3560)		// 机关中间产品
		{
                        switch( random(3) )
                        {
                       case 0 : file = "/item/final/16/1600";  break;
                       case 1 : file = "/item/final/16/1605";  break;
                       case 2 : file = "/item/final/16/1603";  break;
                	}
                }		
                else   	
                if( p < 4560)		// 矿石
                {
                        switch( random(3) )
                        {
                       case 0 : file = "/item/stuff/0001";  break;
                       case 1 : file = "/item/stuff/0002";  break;
                       case 2 : file = "/item/stuff/0003";  break;
                	}                	
                }	
                else   	
                if( p < 5560)		// 食材
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/stuff/0220";  break;
                       case 1 : file = "/item/stuff/0145";  break;
                	}               	
                }                 
                else   	
                if( p < 6560)		// 草药资源
                {
                        switch( random(3) )
                        {
                       case 0 : file = "/item/stuff/0110";  break;
                       case 1 : file = "/item/stuff/0112";  break;
                       case 2 : file = "/item/stuff/0115";  break;
                	}                	
                }      
                else   	
                if( p < 7460)		// 镶嵌资源
                {
                        switch( random(4) )
                        {
                       case 0 : file = "/item/stuff/0078";  break;
                       case 1 : file = "/item/stuff/0079";  break;
                       case 2 : file = "/item/stuff/0083";  break;
                       case 3 : file = "/item/stuff/0057";  break;
                	}                	
                }      
                else   	
                if( p < 7960)		// 宝石矿
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/89/8990";  break;
                       case 1 : file = "/item/89/8991";  break;
                	}                	
                }       
                else   	
                if( p < 8960)		// 裁缝
                {
                        file = "/item/stuff/0045";  
                }     
                else   	
                if( p < 9460)		// 血药
                {
                        file = "/item/91/9100"; 
                        amount = 5;

        	}     
                else   	
                if( p < 9960)		// 法药
                {
                        file = "/item/91/9110"; 
                        amount = 5;

        	}      
                else   	
                if( p < 9970)		// 配方
                {
                        file = "/quest/product2"->get_random_level_product(30, 50); 

        	}              
                else 
                	file = "/quest/book"->get_book_file();                                            
                if( load_object(file))
                {
                	
                        item = new(file);
                        if (amount>0) item->set_amount(amount);
                        item->set_user_id(me->get_id());
                        if (item->get_equip_type()) ITEM_EQUIP_D->init_equip_prop_1(item);
                        if (USER_INVENTORY_D->can_carry(me, item)==0)
                        {
                        	tell_user(me, "Hành trang không đủ ô trống");
                        	destruct(item);
                        	continue;
                        }
			if( item->get_max_combined()>1 )
			{
				if (amount<=0) amount = 1;
				total = amount;	
				count = USER_INVENTORY_D->carry_combined_item(me, item, total);
				if (result=="") result = item->get_name();
				else result += sprintf(", %s ", item->get_name());
		                if( count > 0 && item->set_amount(count) )
		                {      
		                	        	
		                        if( p = item->move(me, -1) )
		                        {
		                                item->add_to_user(p);
		                        }
		                        
		                }
		                else    
		                {
		                	item->add_amount( -total );					
		                }  
			}
			else
			{
				if( p = item->move(me, -1) )
		                {
		                	if (result=="") result = item->get_name();
		                        else result += sprintf(", %s ", item->get_name());
		                        item->add_to_user(p);		                        
		                }
		                else
		                {
		                	destruct(item);
		                }
			}    
						                  
                } 
	}	
	send_user(me, "%c%s", ';', "Bạn nhận được:" + result +".");
	team = me->get_team();
	size = sizeof(team);
	if (size>0)
	{
		for (i=0;i<size;i++)
		{
			if (team[i]->get_number()!=me->get_number()) send_user(team[i], "%c%s", ';', me->get_name()+" mở rương nhận được:" + result +".");
		}
	}
}