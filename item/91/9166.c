
inherit ITEM;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_value() {return 50 ;}
int get_item_value_2() {return 50 ;}
//int get_item_number() {return 10001019 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "Bát Tiên Đơn" );
        set_picid_1(9166);
        set_picid_2(9166);
        set_unit( "粒" );
        set_value(50);
	//	set_save("knb2",20);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Tương truyền sau khi Bát Tiên quay về, tập hợp sức mạnh thần kỳ của tám người để luyện thành.\n Có thể làm cho thể lực hoàn toàn hồi phục.Thời gian tái sử dụng 30 giây.";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
      	if( gone_time( me->get_time("eat_bx") ) < 30 )
        {
                send_user( me, "%c%s", '!', sprintf("Sử dụng Bát Tiên Đơn còn phải chờ %d giây", 30 - gone_time( me->get_time("eat_bx") ) ) );
                return 0;
        }
        if (me->get_strength()>=200)
        {
                send_user( me, "%c%s", '!', "Số điểm Thể Lực đã đầy" );
                return 0;
        }        
        me->set_time( "eat_bx", time() );  

        me->add_strength(200);

        return 1;
}
