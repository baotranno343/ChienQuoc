
#include <ansi.h>
#include <item.h>
#include <time.h>

inherit ITEM;
inherit USABLE;

private int Z, X, Y;

int get_item_value() {return 500 ;}
int get_item_value_2() {return 500 ;}
//int get_item_number() {return 10001072 ;}
int get_item_color() { return 2; }
// 函数：藏宝图
// int is_treasure() { return 1; }

// 函数：藏宝图
int get_item_type() { return ITEM_TYPE_TREASURE; }

// 函数：获取Ｚ坐标
int get_map_z() { return Z; }

// 函数：设置Ｚ坐标
int set_map_z( int z ) { return Z = z; }

// 函数：获取Ｘ坐标
int get_map_x() { return X; }

// 函数：设置Ｘ坐标
int set_map_x( int x ) { return X = x; }

// 函数：获取Ｙ坐标
int get_map_y() { return Y; }

// 函数：设置Ｙ坐标
int set_map_y( int y ) { return Y = y; }

// 函数：构造处理
void create()
{
        set_name( "Cái Xiêm" );
        set_picid_1(3406);
        set_picid_2(3406);
        set_unit( "张" );
        set_value(100);
	//	set_save("knb2",500);
}

// 函数：获取描述
string get_desc() 
{ 
        object map;
        int p;
	if (!clonep()) return "Một chiếc xiêm dùng để bắt cá ở Đường Môn.\nMỗi ngày được sử dụng 5 lần (Vật phẩm không thể xếp chồng)"; 
        if( !( map = get_map_object(Z) ) )
        {
            //    if( p = XY_D->get_city_point(-1, IS_ITEM_BLOCK) )
             //   {
                        set_map_z( 324 );
                        set_map_x( 46 );
                        set_map_y( 107 );
               // }
        }
        return "Một chiếc xiêm dùng để bắt cá ở Đường Môn.\nMỗi ngày được sử dụng 5 lần (Vật phẩm không thể xếp chồng)"; 
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        object map, *monster, npc, item1;
        string name, file, result = "";
        int level, level2, pic, gold, p, i, size, u, rate, tien, knb, exp, iTime, iDay;
        int z0, x0, y0, z, x, y;
		mixed *mxTime;
		iTime = time();
		mxTime = localtime(iTime);
		iDay = mxTime[TIME_YDAY];	
		if (me->get_save_2("xiemca.day")==iDay)
		{
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}
		if ( me->get_save("damca.score") > 4 )
		{
			me->set_save_2("xiemca.day", iDay);
			me->set_save("damca.score",0);
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}
		if(     get_z(me) != item->get_map_z()
        ||      abs( get_x(me) - item->get_map_x() ) > 8
        ||      abs( get_y(me) - item->get_map_y() ) > 8 )
        {
                send_user(me, "%c%s", '!', "Vị trí không đúng");
                return 0;
        }
	if(USER_INVENTORY_D->get_free_count(me) < 1 )
		{
				notify( "Hành trang không đủ 1 chỗ trống" );
		return 0;
		}
	rate = random(100);
	if ( rate < 10 )		//战国令
	{
		item1 = new("item/event/ca");
		if ( !item1 )
			return 0;
	}
	else if ( rate < 30 )	//战国号角
	{
		tien = 700000;
	}
	else if ( rate < 40 )	//战国号角
	{
		knb = 200;
	}
	else if ( rate < 50 )	//战国号角
	{
		tien = 500000;
	}
	else if ( rate < 60 )	//战国号角
	{
		knb = 100;
	}
	else if ( rate < 70 )	//战国号角
	{
		exp = 300000;
	}
	else if ( rate < 80 )	//战国号角
	{
		exp = 200000;
	}
	else if ( rate < 90 )	//战国号角
	{
		exp = 150000;
	}
	item->remove_from_user();
	destruct(item);
	if ( item1 )
	{
		me->add_save("damca.score",1);
		send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY "%s ",item1->get_name() ));
		p = item1->move2(me);
		item1->add_to_user(p);
		USER_D->user_channel(sprintf("Bằng hữu %s bắt cá và đã may mắn nhận được %s ", me->get_name(),item1->get_name() ));
		if ( me->get_save("damca.score") > 4 )
		{
			me->set_save_2("xiemca.day", iDay);
			me->set_save("damca.score",0);
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}
	}
	else if ( tien )
	{
		me->add_save("damca.score",1);
		me->add_cash(tien);
		send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY "%d lượng ",tien ));
		USER_D->user_channel(sprintf("Bằng hữu %s bắt cá và đã may mắn nhận được %d lượng",me->get_name(), tien ));
		if ( me->get_save("damca.score") > 4 )
		{
			me->set_save_2("xiemca.day", iDay);
			me->set_save("damca.score",0);
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}
	}
	else if ( knb )
	{
		me->add_save("damca.score",1);
		"sys/sys/test_db"->add_yuanbao(me,knb);
		send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY "%d Kim Bảo ",knb/10 ));
		USER_D->user_channel(sprintf("Bằng hữu %s bắt cá và đã may mắn nhận được %d Kim Bảo",me->get_name(), knb/10 ));
		if ( me->get_save("damca.score") > 4 )
		{
			me->set_save_2("xiemca.day", iDay);
			me->set_save("damca.score",0);
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}
	}
	else if ( exp )
	{
		me->add_save("damca.score",1);
		me->add_exp(exp);
		send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY "%d kinh nghiệm ",exp ));
		USER_D->user_channel(sprintf("Bằng hữu %s bắt cá và đã may mắn nhận được %d kinh nghiệm",me->get_name(), exp ));
		if ( me->get_save("damca.score") > 4 )
		{
			me->set_save_2("xiemca.day", iDay);
			me->set_save("damca.score",0);
			send_user(me, "%c%s", '!', "Hôm nay đã dùng 5 lần rồi !");
			return 0;
		}	
	}

        return 0;
}
