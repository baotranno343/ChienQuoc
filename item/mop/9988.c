#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <time.h>
#include <equip.h>

inherit TALISMAN;
int get_talisman_type() { return 1; }

int is_limit_time_item() { return 1; }

int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}
int get_item_number() {return 10001101 ;}
int get_item_color() {return 2 ;}

// 函数:构造处理
void create()
{
        set_name("Nhật Nguyệt Tinh Thần");
        set_picid_1(1016);//未确定。
        set_picid_2(1016);
        set_unit("个");
        set_value(50);
		set_save("knb",300);
        set("time_item",1);
        set("ap_power",3);
        set("cp_power",3);
	set("ap_power_2",100);
	set("cp_power_2",100);
	set("dp_power_2",100);
        set_no_give(1);
        set_no_sell(1);
        set_max_lasting(35099);
        setup();
          
}   
// 函数:获取描述
string get_desc() 
{
	object item = this_object();
//---------------------------------------------------------//新服的
	if(item->get_lock_time()== 0)
	{
		item->set_lock_time(time()+24*3600*14);
	}
//---------------------------------------------------------//
	return HIY"Ngoại Công:+3%\n"HIY"Nội Công:+3%\nGia tăng 100 Ngoại Công \nGia tăng 100 Nội Công \nGia tăng 100 Ngoại Kháng";
}
string get_short()
{
	return "Gia tăng 3% Ngoại và Nội Công, 100 Ngoại Công, 100 Nội Công, 100 Ngoại Kháng, thời gian sử dụng 14 ngày";
}

void start_loop_perform(object me)
{
	object item;
	item = me->get_equip(HAND_TYPE);
	if(time() < item->get_lock_time() || item->get_lock_time() == 0)
	{
		USER_ENERGY_D->count_ap(me);
		USER_ENERGY_D->count_cp(me);
		USER_ENERGY_D->count_dp(me);
		CHAR_CHAR_D->init_loop_perform(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9009, 1,UNDER_FOOT, PF_LOOP );
	//	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
	}
}
void stop_loop_perform(object me)
{
	USER_ENERGY_D->count_ap(me);
	USER_ENERGY_D->count_cp(me);
	USER_ENERGY_D->count_dp(me);
	CHAR_CHAR_D->init_loop_perform(me);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9009, 1, UNDER_FOOT, PF_STOP );
//	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
	
}