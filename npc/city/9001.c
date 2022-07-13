/****************************************/
/*************PVP场景传送员**************/
/****************************************/

#include <npc.h>
#include <ansi.h>
#include <effect.h>


inherit OFFICER;

mapping Map=([
		"Đông Võ":({501, 256 ,159}),"Tiểu Bái":({502, 257, 156}),"Bành Thành":({503, 65, 108}),"Tuyết Phong Sơn Bí Đạo":({530, 241, 83}),
		"Vũ Lăng Bí Đạo":({529, 243, 86}),"Hành Sơn Bí Đạo":({528, 185, 47}),"Âm Sơn":({513, 154, 216}),"Âm Sơn Thảo Nguyên":({512, 177, 213}),
		"Kỳ Liên Sơn":({511, 169, 222}),"Kỳ Liên Thảo Nguyên":({510, 167, 222}),"Mang Sơn Bí Đạo":({527, 37, 125}),"Lang Gia Bí Đạo":({526, 238, 81}),
		"Tung Nguyên Bí Đạo":({525, 107, 81}),"Tung Sơn Bí Đạo":({524, 37, 125}),"Mạnh Tân":({517, 254, 160}),"Hoằng Nông":({516, 294, 124}),
		"Dịch Kinh":({515, 254, 157}),"Hồ Quan":({ 514, 231, 178}),"Ô Giang":({505, 259, 154}),"Quảng Lăng":({ 504, 262, 155}),
		"Thiên Thừa":({509, 201, 205}),"Cao Đường":({508, 260, 154}),"Nhạc Lăng":({507, 55, 107}),"Tức Mặc":({506, 63, 103}),
		"Hán Trung":({522, 260,91}),"Tử Ngọ Cốc":({520,171, 35}),"Dương Bình Quan":({523, 220, 178}),"Tây Thành":({521, 278, 140}),
		"Thượng Đảng":({532,256,160}),"Bình Dương":({ 531, 165, 215}),"Vũ Quan":({519, 231, 179}),"Đồng Quan":({ 518, 84, 83}),
		"Tỉ Võ Trường":({885,99,71}),"Cấm Vệ Quân":({080,185,74}),"Cầu Cửu Khúc 3":({374,54,84}),
		"Thiên Môn Trận 1":({091,216,81}),"Thiên Môn Trận 2":({092,230,87}),"Thiên Môn Trận 3":({093,199,63}),
		]);

//获取NPC造型
int get_char_picid()
{
	return 5109;
}

void do_welcome(string arg);

//构造初始化
void create()
{
	set_name("PVP Trường Cảnh Truyền Tống Viên");
	set_2("talk",(["welcome":(:do_welcome:)]));
	setup();
}

//对话处理
void do_look(object who)
{
	string result;
	object me=this_object();
	
	result=sprintf(me->get_name()+":\n    Bằng hữu có hứng thú, ta có thể đưa đi đến nơi luyện cấp thích hợp.Bằng hữu hãy lựa chọn nơi muốn đến nào！\n");
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 45~50\ntalk %x# welcome.1\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 55~60\ntalk %x# welcome.2\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 65~70\ntalk %x# welcome.3\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 75~80\ntalk %x# welcome.4\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 85~90\ntalk %x# welcome.5\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 95~100\ntalk %x# welcome.6\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ PVP cấp 105~110\ntalk %x# welcome.7\n",getoid(me));
	result+=sprintf(ESC "Chuyển đến bản đồ linh ta linh tinh\ntalk %x# welcome.8\n",getoid(me));
	result+=sprintf(ESC "Rời khỏi");
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
}

void do_welcome(string arg)
{
	object me=this_object();
	__FILE__->do_welcome2(me,arg);
}

void do_welcome2(object me,string arg)
{
	int flag,z,x,y,level,*zxy;
	string *key,result,mapname;
	object who;
	
	who=this_player();
	who->set_time("talk",0);
	level=who->get_level();
	if(!arg) return; 
	key=explode(arg," ");
	flag=to_int(key[0]);
	switch(flag)
	{
		case 1:
			//if(!(level>44)&&!(level<51)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 45 - 50 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Đông Võ\ntalk %x# welcome.10 Đông Võ\n",getoid(me));
			result+=sprintf(ESC "Tiểu Bái\ntalk %x# welcome.10 Tiểu Bái\n",getoid(me));
			result+=sprintf(ESC "Bành Thành\ntalk %x# welcome.10 Bành Thành\n",getoid(me));
			result+=sprintf(ESC "Tuyết Phong Sơn Bí Đạo\ntalk %x# welcome.10 Tuyết Phong Sơn Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Vũ Lăng Bí Đạo\ntalk %x# welcome.10 Vũ Lăng Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Hành Sơn Bí Đạo\ntalk %x# welcome.10 Hành Sơn Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 2:
			//if(!(level>54)&&!(level<61)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 55 - 60 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Âm Sơn\ntalk %x# welcome.10 Âm Sơn\n",getoid(me));
			result+=sprintf(ESC "Âm Sơn Thảo Nguyên\ntalk %x# welcome.10 Âm Sơn Thảo Nguyên\n",getoid(me));
			result+=sprintf(ESC "Kỳ Liên Sơn\ntalk %x# welcome.10 Kỳ Liên Sơn\n",getoid(me));
			result+=sprintf(ESC "Kỳ Liên Thảo Nguyên\ntalk %x# welcome.10 Kỳ Liên Thảo Nguyên\n",getoid(me));
			
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 3:
			//if(!(level>64)&&!(level<71)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 65 - 70 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Mang Sơn Bí Đạo\ntalk %x# welcome.10 Mang Sơn Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Lang Gia Bí Đạo\ntalk %x# welcome.10 Lang Gia Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Tung Nguyên Bí Đạo\ntalk %x# welcome.10 Tung Nguyên Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Tung Sơn Bí Đạo\ntalk %x# welcome.10 Tung Sơn Bí Đạo\n",getoid(me));
			result+=sprintf(ESC "Mạnh Tân\ntalk %x# welcome.10 Mạnh Tân\n",getoid(me));
			result+=sprintf(ESC "Hoằng Nông\ntalk %x# welcome.10 Hoằng Nông\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 4:
			//if(!(level>74)&&!(level<81)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 75 - 80 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Dịch Kinh\ntalk %x# welcome.10 Dịch Kinh\n",getoid(me));
			result+=sprintf(ESC "Hồ Quan\ntalk %x# welcome.10 Hồ Quan\n",getoid(me));
			result+=sprintf(ESC "Ô Giang\ntalk %x# welcome.10 Ô Giang\n",getoid(me));
			result+=sprintf(ESC "Quảng Lăng\ntalk %x# welcome.10 Quảng Lăng\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 5:
			//if(!(level>84)&&!(level<91)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 85 - 90 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Thiên Thừa\ntalk %x# welcome.10 Thiên Thừa\n",getoid(me));
			result+=sprintf(ESC "Cao Đường\ntalk %x# welcome.10 Cao Đường\n",getoid(me));
			result+=sprintf(ESC "Nhạc Lăng\ntalk %x# welcome.10 Nhạc Lăng\n",getoid(me));
			result+=sprintf(ESC "Tức Mặc\ntalk %x# welcome.10 Tức Mặc\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 6:
			//if(!(level>94)&&!(level<101)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 95 - 100 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Hán Trung\ntalk %x# welcome.10 Hán Trung\n",getoid(me));
			result+=sprintf(ESC "Tử Ngọ Cốc \ntalk %x# welcome.10 Tử Ngọ Cốc\n",getoid(me));
			result+=sprintf(ESC "Dương Bình Quan\ntalk %x# welcome.10 Dương Bình Quan\n",getoid(me));
			result+=sprintf(ESC "Tây Thành\ntalk %x# welcome.10 Tây Thành\n",getoid(me));
			
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 7:
			//if(!(level>104)&&!(level<111)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới bản đồ cấp 105 - 110 không ? Ấn Alt+M có thể xem xét trước quái vật trong bản đồ này。\n");
			result+=sprintf(ESC "Thượng Đảng\ntalk %x# welcome.10 Thượng Đảng\n",getoid(me));
			result+=sprintf(ESC "Bình Dương\ntalk %x# welcome.10 Bình Dương\n",getoid(me));
			result+=sprintf(ESC "Vũ Quan\ntalk %x# welcome.10 Vũ Quan\n",getoid(me));
			result+=sprintf(ESC "Đồng Quan\ntalk %x# welcome.10 Đồng Quan\n",getoid(me));
			
			result+=sprintf(ESC "Rời khỏi");
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;
		case 8:
			//if(!(level>79)&&!(level<151)) return;
			result=sprintf(me->get_name()+":\n    Ngươi muốn tới những MAP khó đi hay không ?。\n");
			result+=sprintf(ESC "Ta muốn tới Võ Đài\ntalk %x# welcome.10 Tỉ Võ Trường\n",getoid(me));
//			result+=sprintf(ESC "Ta muốn tới Tu Luyện Trường\ntalk %x# welcome.10 Võ Công Tu Luyện Trường\n",getoid(me));
			result+=sprintf(ESC "Ta muốn tới Cấm Vệ Quân\ntalk %x# welcome.10 Cấm Vệ Quân\n",getoid(me));
			result+=sprintf(ESC "Ta muốn tới Cầu Cửu Khúc 3\ntalk %x# welcome.10 Cầu Cửu Khúc 3\n",getoid(me));
			result+=sprintf(ESC "Ta muốn tới Thiên Môn Trận 1\ntalk %x# welcome.10 Thiên Môn Trận 1\n",getoid(me));
			result+=sprintf(ESC "Ta muốn tới Thiên Môn Trận 2\ntalk %x# welcome.10 Thiên Môn Trận 2\n",getoid(me));
			result+=sprintf(ESC "Ta muốn tới Thiên Môn Trận 3\ntalk %x# welcome.10 Thiên Môn Trận 3\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;	
		case 10:
			if(!sscanf(arg,"%d %s",flag,mapname)==2) return;
			zxy=Map[mapname];
			if(!zxy) return;
			z=zxy[0];x=zxy[1];y=zxy[2];
			__FILE__->send_ok(who,z,x,y);
			break;
			
	}
}

//可以传送
void send_ok(object who,int z,int x,int y)
{
	int p;
	object me=this_object();
	p=x*1000+y;
	send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Đang di chuyển……");
        who->set_2("travel.z",z);
	who->set_2("travel.p",p);
	set_effect(who, EFFECT_TRAVEL, 1);
//	me->add_to_scene(z,x-2,y-2);
}