#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("大礼包");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(10);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "可右击打开的大礼包，会带给你意外的惊喜。"; 
}
// 函数：复位处理
void reset()
{
        if( gone_time( get_drop_time() ) >= 1800 )    // 30分钟刷新
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,exp,pot;
	object item;
	
	rate = random(10000);


	if ( rate < 2300 )
	{
		exp = 400;
	}
	else if ( rate < 5100 )
	{
		pot = 30;
	}
	else if ( rate < 5110 )
	{
		item = new("item/08/0001");	//战国令
	}
	else if ( rate < 5140 )
	{
		item = new("item/08/0002");	//战国号角
	}	
	else if ( rate < 5160 )
	{
		item = new("item/08/0003");	//血石
	}
	else if ( rate < 5190 )
	{
		item = new("item/08/0004");	//法力石
	}
	else if ( rate < 5220 )
	{
		item = new(BOOK_FILE->get_book_file());	//技能进阶书
	}	
	else if ( rate < 7820 )
	{
		cash = 1000;
	}	
	else if ( rate < 7825 )
	{
		item = new("item/std/6001");	//百宝囊
	}
	else if ( rate < 7840 )
	{
		item = new("item/91/9178");	//复生丹
	}
	else if ( rate < 8000 )
	{
		item = new(STONE_FILE->get_diamond_file());	//1级晶石
		item->set_level(1);
	}
	else if ( rate < 8500 )
	{
		item = new("item/std/8000");	//普通藏宝图
	}
	else if ( rate < 9250 )			//炼丹成品
	{
		p = random(6);
		switch(p)
		{
		default:	
			item = new("item/final/91/1808");	//银杏子
			break;
		case 1:	
			item = new("item/final/91/1809");	//仙山灵芝
			break;
		case 2:	
			item = new("item/final/91/1810");	//紫箐丹
			break;
		case 3:	
			item = new("item/final/91/1811");	//舍利子
			break;
		case 4:	
			item = new("item/std/5211");		//鹤顶红
			item->set_amount(3);
			break;
		case 5:	
			item = new("item/91/9145");		//清心丹
			item->set_amount(2);
			break;										
		}
	}
	else if ( rate < 9350 )		//玉灵液
	{
		item = new("item/44/4404");	
	}	
	else if ( rate < 9550 )		//对应等级随机蓝装
	{
               if( random(2) ) 
                        item = new( ARMOR_FILE->get_armor_file_2( who->get_level()) );
                else    
                	item = new( WEAPON_FILE->get_weapon_file_2( who->get_level()) );
		ITEM_EQUIP_D->init_equip_prop_1(item);
	}
	else if ( rate < 9560 )		//对应等级随机金装
	{
               if( random(2) ) 
                        item = new( ARMOR_FILE->get_armor_file_2( who->get_level()) );
                else    
                	item = new( WEAPON_FILE->get_weapon_file_2( who->get_level()) );
		ITEM_EQUIP_D->init_equip_prop_3(item);
	}
	else if ( rate < 9830 )		//速效小治愈药水
	{
		item = new("/item/sell/0007");	
	}
	else 				//速效小恢复药水
	{
		item = new("/item/sell/0009");	
	}
			
	gift->remove_from_user();
	destruct(gift);
	if ( item )
	{
		CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s在宝藏大搜寻活动中获得奖品%s",who->get_name(),item->get_name()));
		send_user(who,"%c%s",'!',"恭喜您！您打开大礼包得到了"+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);	
	}
	else if (  cash )
	{
		who->add_cash(cash);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开大礼包得到了%d金",cash));
	}
	else if (  exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开大礼包得到了%d点经验",exp));
	}
	else if (  pot )
	{
		who->add_potential(pot);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开大礼包得到了%d点潜能",pot));
	}
	return 0;
}

