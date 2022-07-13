#include <skill.h>
#include <effect.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int * change54 =({ 0010,0011,0050,0051,0052,0053,0100,0101,0102,0150,0151,0152,0200,0201,0202,0250,0251,0252,0300,0301,0302,0303,0304,0350,0351,0352,0400,0401,0402,0450,0500,0502,0550,0551,0552,8010,8011,});
// 函数：叠加上限
int get_max_combined() { return 30; }

int is_usable() {return 1;}

// 函数：构造处理
void create()
{
        set_name("新年红包");
        set_picid_1(9985);
        set_picid_2(9985);
        set_value(10);
        set_amount(1);        
}

// 函数：获取描述
string get_desc() 
{ 
        return "新年到了！恭喜发财，红包拿来！\n红包很大，打开时请注意预留道具栏空格。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,i=0;
	object item;
	string result,file;
	result = sprintf(HIR"恭喜%s打开红包，获得", who->get_name());
	rate = random(10000);
	if ( who->get_level()>=30)
	{
		if (rate<10000)
		{
			who->add_cash(1000);
			write_user( who, ECHO "您获得1000金钱。" );	
		}	
		if (rate<2000)
		{
			item = new ("/item/04/baozhu");
                        if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				item->set_amount(30);
				write_user( who, ECHO "您获得"+item->get_name()+"30个。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}	
		if (rate<1000)//变身卡
		{
			item = new (sprintf("/item/54/%04d",change54[random(sizeof(change54))]));
                        if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}	
		if (rate<500)
		{
			who->add_cash(10000);
			write_user( who, ECHO "您获得10000金钱。" );	
		}	
		if (rate<100)
		{
			item = new ("item/std/6002");//乾坤袋
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}	
		if (rate<100) //1级晶石
	        {
	                file = STONE_FILE->get_diamond_file();
	                item = new(file);
	                item->set_level(1);
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
	        }
		if (rate<50)
		{
			item = new ("item/08/0003");//小血石
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}
		if (rate<50)
		{
			item = new ("item/08/0004");//小法石
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}
		if (rate<50)
		{
			item = new ("item/08/0002");//战国号角
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}
		if (rate<20) //2级晶石
	        {
	                file = STONE_FILE->get_diamond_file();
	                item = new(file);
	                item->set_level(2);
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
	        }
		if (rate<10)
		{
			item = new ("item/08/0001");//战国令
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result += "、";
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}
		if (rate<10)
		{
			who->add_cash(100000);
			result += "、";
			result = result + "100000金钱";
			i=i+1;
			write_user( who, ECHO "您获得100000金钱。" );	
		}	
	}
	else
	{
		if (rate<10000)
		{
			who->add_cash(500);
			write_user( who, ECHO "您获得500金钱。" );	
		}	
		if (rate<2000)
		{
			item = new ("/item/04/baozhu");
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				item->set_amount(30);
				write_user( who, ECHO "您获得"+item->get_name()+"30个。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}	
		if (rate<1000)
		{
			who->add_cash(1000);
			write_user( who, ECHO "您获得1000金钱。" );	
		}	
		if (rate<400)//20级白装
		{
	                if( random(2) ) file = ARMOR_FILE->get_armor_file_2( 20 );
	                else file = WEAPON_FILE->get_weapon_file_2( 20 );
                        item = new( file );
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}
                        else
                                destruct(item);
		}
		if (rate<100)//变身卡
		{
			item = new (sprintf("/item/54/%04d",change54[random(sizeof(change54))]));
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}
		if (rate<100)//30级白装
		{
	                if( random(2) ) file = ARMOR_FILE->get_armor_file_2( 30 );
	                else file = WEAPON_FILE->get_weapon_file_2( 30 );
                        item = new( file );
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}
                        else
                                destruct(item);
		}
		if (rate<100)//20级蓝装
		{
	                if( random(2) ) file = ARMOR_FILE->get_armor_file_2( 20 );
	                else file = WEAPON_FILE->get_weapon_file_2( 20 );
                        item = new( file );
                        ITEM_EQUIP_D->init_equip_prop_1(item);
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}
                        else
                                destruct(item);
		}
		if (rate<50)
		{
			item = new ("item/std/6002");//乾坤袋
			if( USER_INVENTORY_D->can_carry_3(who, item)  >=1 )
			{	
				result = result + item->get_name();
				i=i+1;
				write_user( who, ECHO "您获得"+item->get_name()+"。" );	
				p = item->move2(who);
				item->add_to_user(p);			
			}		
                        else
                                destruct(item);
		}	
	}
	result += "的意外惊喜！";
	if (i>0) USER_D->user_channel(result);	
	gift->add_amount(-1);
	return 0;
}

