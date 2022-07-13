inherit OFFICER;
inherit "/inh/std/box";

// 函数:构造处理
void create()
{
        set_name("Thiết Bảo Rương");
        set("time", 1);
        set("level", 3);
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
		if( p < 2540)		//  lượng钱
		{
			cash = 2500+random(50);
			me->add_cash(cash);
			if (strlen(result)==0)
				result += sprintf("%d lượng", cash);
			else
				result += sprintf(",%d lượng", cash);
			continue;
		} 
		if( p < 2550)		// 武器
		{
                        switch( random(3) )
                        {
                       case 0 : file = WEAPON_FILE->get_weapon_file_2(40);  break;
                       case 1 : file = WEAPON_FILE->get_weapon_file_2(50);  break;
                       case 2 : file = WEAPON_FILE->get_weapon_file_2(60);  break;
                	}
                }
                else	
		if( p < 2560)		// 防具
		{
                        switch( random(3) )
                        {
                       case 0 : file = ARMOR_FILE->get_armor_file_2(40);  break;
                       case 1 : file = ARMOR_FILE->get_armor_file_2(50);  break;
                       case 2 : file = ARMOR_FILE->get_armor_file_2(60);  break;
                	}
		}
		else                            
		if( p < 3560)		// 机关中间产品
		{
                        switch( random(4) )
                        {
                       case 0 : file = "/item/final/16/1609";  break;
                       case 1 : file = "/item/final/16/1610";  break;
                       case 2 : file = "/item/final/16/1607";  break;
                       case 3 : file = "/item/stuff/0209";  break;
                	}
                }		
                else   	
                if( p < 4560)		// 矿石
                {
                        switch( random(3) )
                        {
                       case 0 : file = "/item/stuff/0003";  break;
                       case 1 : file = "/item/stuff/0007";  break;
                       case 2 : file = "/item/stuff/0008";  break;
                	}                	
                }	
                else   	
                if( p < 5560)		// 食材
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/stuff/0144";  break;
                       case 1 : file = "/item/stuff/0171";  break;
                	}               	
                }                 
                else   	
                if( p < 6560)		// 草药资源
                {
                        switch( random(4) )
                        {
                       case 0 : file = "/item/stuff/0116";  break;
                       case 1 : file = "/item/stuff/0117";  break;
                       case 2 : file = "/item/stuff/0118";  break;
                       case 3 : file = "/item/stuff/0122";  break;
                	}                	
                }      
                else   	
                if( p < 7460)		// 镶嵌资源
                {
                        switch( random(4) )
                        {
                       case 0 : file = "/item/stuff/0058";  break;
                       case 1 : file = "/item/stuff/0082";  break;
                       case 2 : file = "/item/stuff/0060";  break;
                       case 3 : file = "/item/stuff/0083";  break;
                	}                	
                }      
                else   	
                if( p < 7960)		// 宝石矿
                {
                        switch( random(2) )
                        {
                       case 0 : file = "/item/89/8991";  break;
                       case 1 : file = "/item/89/8992";  break;
                	}                	
                }       
                else   	
                if( p < 8960)		// 裁缝
                {
                        file = "/item/stuff/0048";  
                }     
                else   	
                if( p < 9460)		// 血药
                {
                        file = "/item/91/9101"; 
                        amount = 5;

        	}     
                else   	
                if( p < 9960)		// 法药
                {
                        file = "/item/91/9111"; 
                        amount = 5;

        	}      
                else   	
                if( p < 9970)		// 配方
                {
                        file = "/quest/product2"->get_random_level_product(40, 70); 

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
                        	tell_user(me, "Hành trang không đủ ô trống.");
                        	destruct(item);
                        	continue;
                        }
			if( item->get_max_combined()>1 )
			{
				if (amount<=0) amount = 1;
				total = amount;	
				count = USER_INVENTORY_D->carry_combined_item(me, item, total);
				if (result=="") result = item->get_name();
				else result += sprintf("、%s", item->get_name());
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
		                        else result += sprintf("、%s", item->get_name());
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
			if (team[i]->get_number()!=me->get_number()) send_user(team[i], "%c%s", ';', me->get_name()+" mở Bảo Rương nhận được:" + result +".");
		}
	}
}