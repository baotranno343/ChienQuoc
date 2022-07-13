#include <effect.h>
#include <ansi.h>
#include <item.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
void create() 
{
}

int main( object me, object obj, int count, string sex, object diamond1, object diamond2, object diamond3 )
{
        int level, mp, size, i, stuff, tool_type, tool_level, x, y, z, flag;
        string * name, final;
        object file, *char, tool;
        mapping product;
	int bag, b, c, d, allcount;
	bag = me->have_bag();
        b = bag % 100;
        c = (bag / 100)%100;
        d = bag / 10000;
	if (b>0 && me->get_bag1_time()>0 && time()>me->get_bag1_time()) b = 0;
	if (c>0 && me->get_bag2_time()>0 && time()>me->get_bag2_time()) c = 0;
	if (d>0 && me->get_bag3_time()>0 && time()>me->get_bag3_time()) d = 0;
        if( me->get_reincarnation() ) b = MAX_CARRY;	
        allcount = MAX_CARRY + b + c + d;        
	level = me->get_skill(obj->get_skill());	
	if (level<obj->get_skill_level()) 
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" cấp bậc kĩ năng không đủ" );
		return 1;
	}
	// 检查有无相应技能
	if (count<0) 
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" số lượng không đủ" );
		return 1;
	}
	if ("/sys/item/product"->check_vita_skill(me, obj->get_skill() * 100 + obj->get_number())==0)
	{
		printf( ECHO "Bạn chưa học \"" + obj->get_name() + "\"。" );
		return 1;
	}
	if (me->get_strength()<obj->get_tili())
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" thể lực không đủ" );
		return 1;
	}
	product = obj->get_product();
	// 检查原料是否齐全	
	name = keys(product);		
	size = sizeof(name);
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		if ("/sys/item/product"->find_stuff(me, stuff)<product[name[i]])
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" nguyên liệu không đủ" );
			return 1;
		}
	}
	// 检查工具
	if (obj->get_tool())
	{
		tool = me->get_equip(107);
		if (!tool)
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" thiếu công cụ" );
			return 1;			
		}
		file = load_object(sprintf("/item/stuff/%04d", obj->get_tool()));
		if (file)
		{
			tool_type = file->get_item_type_2();
			tool_level = file->get_level();
			if (tool_type!=tool->get_item_type_2())
			{
				printf( ECHO "Sử dụng \"" + obj->get_name() + "\" công cụ không đúng" );
				return 1;				
			}
			if (tool_level>tool->get_level())
			{
				printf( ECHO "Sử dụng \"" + obj->get_name() + "\" công cụ cấp bậc quá thấp" );
				return 1;				
			}			
		}
	}
	// 检查是否需要师父
	if (obj->get_master() &&obj->get_master()!="0" )
	{
		z = get_z(me); x = get_x(me); y = get_y(me);
		char = get_range_object(z, x, y, 5, CHAR_TYPE);
		size = sizeof(char);
		flag = 0;
		for (i=0;i<size;i++)
		{
			if (file = char[i])
			{
				if (file->get_name()==obj->get_master())
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag==0)
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" cần ở bên cạnh " + obj->get_master() + " ." );
			return 1;				
		}
	}
	if( sizeof_inventory(me, 1, MAX_CARRY*4) >= allcount )
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" đạo cụ ít nhất cần một không vị" );
		return 1;
	}	
	final = obj->get_final();
	// 判断如果是普通物品或者生活技能工具，不让Sử dụng 鲁班宝石
	if (final->get_equip_type()==0 || final->get_equip_type()==HAND_TYPE)
	{
		if (diamond1 && diamond1->is_luban())
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" không thể phụ gia Lỗ Ban Bảo Thạch" );
			return 1;			
		}
		if (diamond2 && diamond2->is_luban())
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" không thể phụ gia Lỗ Ban Bảo Thạch" );
			return 1;			
		}
		if (diamond3 && diamond3->is_luban())
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" không thể phụ gia Lỗ Ban Bảo Thạch" );
			return 1;			
		}				
	}
        set_effect_2(me, EFFECT_PROGRESS, count, 3);
        me->set_progress_file(get_file_name(obj));
        me->set_progress_arg(sex);
        me->set("progress", ({tool, diamond1, diamond2, diamond3}));
        send_user(me, "%c%c%w%s", 0x5a, 0, 3, obj->get_name()+" tiến hành....");	        
        return 1;	
}

void into_effect(object me, object obj, string arg)
{
	object tool, diamond1, diamond2, diamond3, *temp, item;
	string * name;
	int i, size, rate, stuff, p, total, amount, sex, count;
	mapping product;
	int bag, b, c, d, allcount;
	bag = me->have_bag();
        b = bag % 100;
        c = (bag / 100)%100;
        d = bag / 10000;
	if (b>0 && me->get_bag1_time()>0 && time()>me->get_bag1_time()) b = 0;
	if (c>0 && me->get_bag2_time()>0 && time()>me->get_bag2_time()) c = 0;
	if (d>0 && me->get_bag3_time()>0 && time()>me->get_bag3_time()) d = 0;
        if( me->get_reincarnation() ) b = MAX_CARRY;	
        allcount = MAX_CARRY + b + c + d;    	
	temp = me->get("progress");
	// 检查空位	
	if (sizeof(temp)==4)
	{
		tool = temp[0];
		diamond1 = temp[1];
		diamond2 = temp[2];
		diamond3 = temp[3];
	}
	sex = to_int(arg);
	// 检查东西还在不在
	product = obj->get_product();
	name = keys(product);		
	size = sizeof(name);
	// 检查工具以及宝石
	if( sizeof_inventory(me, 1, MAX_CARRY*4) >= allcount )
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" đạo cụ ít nhất cần một không vị" );
		obj->effect_break(me, "");
		return;
	}	
	if (obj->get_tool() && !tool)
	{
		obj->effect_break(me, "");
		return ;
	}
	if (tool)
	{
		if (tool!=me->get_equip(107))		
		{
			obj->effect_break(me, "");
			return ;
		}
		if (tool->get_lasting()<100)	
		{
			printf( ECHO "Sử dụng \"" + obj->get_name() + "\" độ bền của công cụ không đủ" );
			obj->effect_break(me, "");
			return;
		}					
	}	
	if (diamond1)
	{
		if (diamond1->if_in_user(me)==0)
		{
			obj->effect_break(me, "");
			return ;
		}				
	}	
	if (diamond2)
	{
		if (diamond2->if_in_user(me)==0)
		{
			obj->effect_break(me, "");
			return ;
		}		
	}	
	if (diamond3)
	{
		if (diamond3->if_in_user(me)==0)
		{
			obj->effect_break(me, "");
			return ;
		}		
	}		
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		if ("/sys/item/product"->find_stuff(me, stuff)<product[name[i]])
		{
			obj->effect_break(me, "");
			return ;
		}
	}
	for (i=0;i<size;i++)
	{
		stuff = to_int(name[i]);
		"/sys/item/product"->sub_stuff(me, stuff, product[name[i]]);
	}	
	// 计算成功率和极品率
	rate = obj->get_base_rate();
	if (rate>95) rate = 95;
	if (diamond1) rate += diamond1->get_rate();
	if (diamond2) rate += diamond2->get_rate();
	if (diamond3) rate += diamond3->get_rate();
	if ( me->get_vip() && !me->get_save_2("vip_package.trial") )
		rate += 5;
	me->add_strength(-obj->get_tili());
	if (random(100)<rate)
	{
		item = new (obj->get_final());
		if (item)
		{
			count = obj->get_count();
			if (count<1) count = 1;		
			printf( ECHO "Bạn Sử dụng \"" + obj->get_name() + "\" luyện ra " +item->get_name()+ "。" );
			"/sys/item/product"->make_item(item, obj->get_skill_color(), 0);
			if( ( total = USER_INVENTORY_D->can_carry(me, item) ) < 1 )
			{
	                        send_user( me, "%c%s", '!', "Bạn trên người không có không vị !");
	                        destruct(item);       
	                        obj->effect_break(me, "");
	                        return ;  			
			}	
			if (item->get_item_type()==ITEM_TYPE_EQUIP) 
			{
				item->set_product_id(me->get_name());	
				if (item->get_item_color()==0)
					item->set_item_color(4);	
				item->set_bind(1);
			}
			if (diamond1 && item->is_equip()) diamond1->init_equip(item);
			if (diamond2 && item->is_equip()) diamond2->init_equip(item);
			if (diamond3 && item->is_equip()) diamond3->init_equip(item);

			if( item->get_max_combined()>1 )
			{
				total = count;	
				amount = USER_INVENTORY_D->carry_combined_item_3(me, item, total);
		                if( amount > 0 && item->set_amount(amount) )
		                {              	
		                        if( p = item->move2(me) )
		                        {
		                                item->add_to_user(p);
		                        }
		                }
		                else    item->add_amount( -total );					
			}
			else
			{
				if( p = item->move2(me) )
		                {
		                        item->add_to_user(p);
		                }
			}		               
		}		
		send_user(me, "%c%c%c", 0x5a, 1, 1);
	}
	else
	{
		printf( ECHO "Sử dụng \"" + obj->get_name() + "\" thất bại" );
		item = new ("/item/final/stuff");
		if (item)
		{			
			if( ( total = USER_INVENTORY_D->can_carry_3(me, item) ) < 1 )
			{
	                        send_user( me, "%c%s", '!', "Bạn trên người không có không vị !");
	                        destruct(item);       
	                        obj->effect_break(me, "");
	                        return ;  			
			}			
			total = 1;	
			amount = USER_INVENTORY_D->carry_combined_item_3(me, item, total);
	                if( amount > 0 && item->set_amount(amount) )
	                {              	
	                        if( p = item->move2(me) )
	                        {
	                                item->add_to_user(p);
	                        }
	                }
	                else    item->add_amount( -total );		
		}		
	}
	if (tool) tool->add_lasting(-100);
	if (diamond1) 
	{
		if ( diamond1->is_combined() && diamond1->get_amount() > 1 )
			diamond1->add_amount(-1);
		else
		{
			send_user( me, "%c%d", 0x2d, getoid(diamond1) );
	                destruct(diamond1);		
			diamond1 = 0;
		}
	}
	if (diamond2) 
	{
		if ( diamond2->is_combined() && diamond2->get_amount() > 1 )
			diamond2->add_amount(-1);
		else
		{
			send_user( me, "%c%d", 0x2d, getoid(diamond2) );
	                destruct(diamond2);		
			diamond2 = 0;
		}
	}
	if (diamond3) 
	{
		if ( diamond3->is_combined() && diamond3->get_amount() > 1  )
			diamond3->add_amount(-1);
		else
		{
			send_user( me, "%c%d", 0x2d, getoid(diamond3) );
	                destruct(diamond3);		
			diamond3 = 0;
		}
	}	
	if (obj->get_skill_temp())
	{
		obj->effect_break(me, "");
		"/sys/item/product"->sub_vita_skill(me, obj->get_skill() * 100 + obj->get_number());
		send_user(me, "%c%c%w%w%d", 0x60, 0, obj->get_skill(), obj->get_skill_type(), obj->get_skill() * 100 + obj->get_number() );
		return;
	}
	if (me->get_strength()<obj->get_tili())
	{
		obj->effect_break(me, "");
		return;
	}	
	if( !get_effect_3(me, EFFECT_PROGRESS) ) 
	{
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		me->set("progress", 0 );
	}
	else	
	{
        	me->set("progress", ({tool, diamond1, diamond2, diamond3}));
        	send_user(me, "%c%c%w%s", 0x5a, 0, 3, obj->get_name() + " tiến hành....");
        }
}