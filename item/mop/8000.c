
#include <ansi.h>
#include <item.h>

#define MONSTER         "/npc/task/8001"
#define ZOMBIE          "/npc/task/8002"

inherit ITEM;
inherit USABLE;

private int Z, X, Y;

int get_item_color() { return 1; }
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
        set_name( "黄帝宝藏探险地图" );
        set_picid_1(8000);
        set_picid_2(8000);
        set_unit( "张" );
        set_value(1);
        set_no_give(1);
        set_no_sell(1);
}

// 函数：获取描述
string get_desc() 
{ 
        object map;
        int p, z;

        if( !( map = get_map_object(Z) ) )
        {
        	if (random(2)==0) z = 2;
        	else z = 3;
        	p = get_xy_point(z, IS_ITEM_BLOCK);
                if( p )
                {
                        set_map_z( z );
                        set_map_x( ( p % 1000000 ) / 1000 );
                        set_map_y( p % 1000 );
                }
        }
        return "通过它可以找到宝藏"; 
}

// 函数：使用效果	改为普通藏宝图的作用
//int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }
int get_use_effect( object me ) { return "/item/std/8000" ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
        object map, *monster, npc;
        string name, file, result = "";
        int total, amount;
        int z0, x0, y0, z, x, y, p;

        if(     get_z(me) != item->get_map_z()
        ||      abs( get_x(me) - item->get_map_x() ) > 2
        ||      abs( get_y(me) - item->get_map_y() ) > 2 )
        {
                send_user(me, "%c%s", '!', "您挖宝的位置不对。");
                return 0;
        }
        name = item->get_name();
	item->remove_from_user();    // 空出位置
	remove_item(item);
        item = new( "item/04/7777" );
        total = 1;
	amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
	if( amount > 0 && item->set_amount(amount) )
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
	write_user(me, ECHO "您沿着%s的线索，得到一个七国令。", name );
        return 0;
}
