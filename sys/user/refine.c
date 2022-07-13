
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <npc.h>
#include <time.h>

mapping level_message = ([
	50:	({ "Trường Bạch Sơn hoặc Phong Yêu Kính", "50", "54", }), // ~
	55:	({ "Yên Trường Thành hoặc Phong Yêu Kính", "55", "59", }),
	60:	({ "Triệu Trường Thành hoặc Phong Yêu Kính", "60", "65", }),
	65:	({ "Tần Trường Thành hoặc Phong Yêu Kính", "65", "69", }),
	70:	({ "Loan Đạo hoặc Phong Yêu Kính", "70", "75", }),
	75:	({ "Linh Cốc Động hoặc Phong Yêu Kính", "75", "86", }),
	80:	({ "Hầm Vạn Nhân hoặc Phong Yêu Kính", "80", "88", }),
	85:	({ "Tướng Quân Cổ Mộ hoặc Phong Yêu Kính", "85", "93", }),
	90:	({ "Khốn Ma Trận hoặc Phong Yêu Kính", "90", "97", }),
	95:	({ "Tử Vân Động hoặc Phong Yêu Kính", "95", "100", }),
	100:	({ "Cầu Cửu Khúc hoặc Phong Yêu Kính", "100", "108", }),
	105:	({ "Thiên Môn Trận hoặc Phong Yêu Kính", "105", "112", }),
	110:	({ "Tru Tiên Trận", "110", "116", }),
	115:	({ "Tru Tiên Trận", "110", "116", }),
	]);


// 函数:生成二进制码
void SAVE_BINARY() { }

void do_welcome(object me, object who, string arg)
{
	int type = to_int(arg);
	string result, *name;
	int iTime, day, p, level, i, size;
	mixed *mxTime;
	object item;
	level = me->get_level();
	if (MAIN_D->get_host_type()==6012)
	{
		result = sprintf("%s:\n    Trước mắt nhiệm vụ Thu Yêu chưa mở ra.\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}
	if (level<50)
	{
		result = sprintf("%s:\n    Cấp bậc chưa đủ 50, không thể thu yêu.\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}
	if (level>120) 
	{
		result = sprintf("%s:\n    Cấp bậc của ngươi hiện tại đã quá cao.\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}	
	if (me->get_city_name()!=who->get_city_name())
	{
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), sprintf("%s:\n    Nhiệm vụ này không cần nói đến nữa.\n", who->get_name()));
		return;
	}	
	if (me->get_save_2("refine.status")==1)
	{
		result = sprintf("%s:\n    Sao ngươi còn ở đây, mau đi thu yêu trừ hại cho dân chúng đi\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}
	iTime = time();
	mxTime = localtime(iTime);
	day = mxTime[TIME_YDAY];	
	if (me->get_save_2("refine.status")==2&&me->get_save_2("refine.day")==day)
	{
		result = sprintf("%s:\n    Ngày mai hãy đến nhé!\n", who->get_name());
		result += ESC"Rời khỏi\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}
	if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY )
	{
		result = sprintf("%s:\n    Hành trang không đủ ô trống!\n", who->get_name());
		result += ESC"Rời khỏi\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;		
	}		
	switch(type)
	{
	case 1000:
		result = sprintf("%s:\n    Từ sau trận chiến Trường Bình, yêu quái xuất hiện khắp nơi, ngươi hãy đi trảm 450 con yêu quái thu hồn vào Hồ Lô cho ta.\n", who->get_name());
		result += sprintf(ESC"Nhận\ntalk %x# welcome.1001\n", getoid(who));
		result += ESC"Cự tuyệt\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 1001:		
		item = new ("/item/01/0100");
		if (!item) return;
                p =item->move(me, -1);
		item->add_to_user(p);  	
		level = (level/5)*5;
		if (level>110) level = 110;
		name = level_message[level];
		result = sprintf("%s:\n    Một cái Hồ Lô Thu Yêu có thể thu 450 con quái, hiên tại ngươi có thể đi "HIR "%s thu %s~%s cấp yêu quái.\n", who->get_name(), name[0], name[1], name[2]);		
		result += ESC"Rời khỏi\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		me->delete_save_2("refine");
		me->set_save_2("refine.status", 1);
		me->set_save_2("refine.level", me->get_level());
		me->set_save_2("refine.level1", to_int(name[1]));
		me->set_save_2("refine.level2", to_int(name[2]));
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_REFINE, "Nhiệm vụ Thu Yêu" ); 
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "Nhiệm vụ Hồ Lô Thu Yêu" ); 
		send_user( me, "%c%s", '!', "Bạn nhận được Hồ Lô Thu Yêu");
		break;	
	}
}

string send_task_intro(object me)
{
	int level, i, size, exp;
	string result, *name, result2;
	if (me->get_save_2("refine.status")!=1) return "";
	level = me->get_save_2("refine.level");
	exp = "/sys/npc/energy"->get_exp_bonus(level);
	exp = exp*450/2;
	level = (level/5)*5;
	if (level<50) return "";
	if (level>110) level = 110;
	name = level_message[level];	
	result = sprintf(BLK"Mục đích nhiệm vụ:\n"BLK"    Đem %s~%s cấp 450 yêu quái thu vào Hồ Lô Thu Yêu.\n"BLK"    Đã thu được:%d/450.\n"BLK"Miêu tả nhiệm vụ:\n"BLK"    Đi đến %s tiêu diệt %s cấp 450 yêu quái.\n"BLK"Phần thưởng:%d điểm kinh nghiệm\n",
	                        name[1], name[2], me->get_save_2("refine.count"), name[0], name[1], exp);	                
	return result;	                        
}

void task_giveup(object player )
{
	int time;
	object item;
	send_user( player, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "" );
	send_user( player, "%c%c%c%w%s", 0x51, 1, 1, TID_REFINE, "" );
	player->delete_save_2("refine");
	// 删除Hồ Lô Thu Yêu
	item = present("Hồ Lô Thu Yêu", player, 1, MAX_CARRY*4);
	if (item)
	{
		item->remove_from_user();
	        destruct(item);	
	}	       
}