
#include <ansi.h>

inherit ITEM;
inherit USABLE;

int get_item_value() {return 20 ;}
int get_item_value_2() {return 20 ;}
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name( "Góc Trái Tàng Bảo Đồ" );
        set_picid_1(8001);
        set_picid_2(8001);
        set_unit( "张" );
        set_value(100);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Thông qua nó có thể tìm được bảo tàng"; 
}

// 函数：使用效果
int get_use_effect( object me )
{
        object obj, obj2, obj3, obj4;
        int p;

        if(     !( obj2 = present("Góc Phải Tàng Bảo Đồ", me, 1, MAX_CARRY) )
        ||      !( obj3 = present("Góc Dưới Tàng Bảo Đồ", me, 1, MAX_CARRY) )
        ||      !( obj4 = present("Góc Trên Tàng Bảo Đồ", me, 1, MAX_CARRY) ) )
        {
                send_user(me, "%c%s", '!', "Ngài trên người tàng bảo đồ tàn phiến không được đầy đủ, vô pháp xác nhập.");
                return 0;
        }

        obj2->remove_from_user();
        destruct(obj2);
        obj3->remove_from_user();
        destruct(obj3);
        obj4->remove_from_user();
        destruct(obj4);

        obj = new( "/item/std/8005" );
        if( p = obj->move(me, -1) ) obj->add_to_user(p);
        else destruct(obj);

        if( obj ) write_user(me, ECHO "Ngài đem bốn trương tàng bảo đồ tàn phiến xác nhập thành một trương tàn cũ tàng bảo đồ.");

        return 1;
}
