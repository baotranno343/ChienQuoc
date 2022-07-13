#include <npc.h>
#include <ansi.h>
#include <time.h>

inherit OFFICER;

mapping maps = ([
	101:	([ "name" : 	"Sở Phương Thành 1",
		   "locate" :	({ 061,208,133, }),
		]),		   
	102:	([ "name" : 	"Sở Phương Thành 2",
		   "locate" :	({ 062,43,40, }),
		]),		   
	103:	([ "name" : 	"Sở Phương Thành 3",
		   "locate" :	({ 063,196,151, }),
		]),		   
	104:	([ "name" : 	"Thượng Dung Quan",
		   "locate" :	({ 284,252,198, }),
		]),		   
	105:	([ "name" : 	"Thúy Hoa Sơn",
		   "locate" :	({ 283,208,28, }),
		]),		   
	106:	([ "name" : 	"Đào Hoa Nguyên",
		   "locate" :	({ 282,185,127, }),
		]),		   
	107:	([ "name" : 	"Triều Dương Phong",
		   "locate" :	({ 281,29,150, }),
		]),		   

	201:	([ "name" : 	"Thủ Dương Sơn",
		   "locate" :	({ 081,244,154, }),
		]),		   
	202:	([ "name" : 	"Thúy Hoa Sơn",
		   "locate" :	({ 082,200,80, }),
		]),		   
	203:	([ "name" : 	"Hàm Cốc Quan",
		   "locate" :	({ 251,227,34, }),
		]),		   

	301:	([ "name" : 	"Vô Định Hà 1",
		   "locate" :	({ 042,337,218, }),
		]),		   
	302:	([ "name" : 	"Vô Định Hà 2",
		   "locate" :	({ 043,192,169, }),
		]),		   
	303:	([ "name" : 	"Bờ Vô Định Hà",
		   "locate" :	({ 041,89,128, }),
		]),		   
	304:	([ "name" : 	"Tương Lăng",
		   "locate" :	({ 021,176,54, }),
		]),		   
	305:	([ "name" : 	"Mã Lăng Đạo",
		   "locate" :	({ 141,136,67, }),
		]),		   
	306:	([ "name" : 	"Bạch Mã Trang",
		   "locate" :	({ 142,100,56, }),
		]),		   
	307:	([ "name" : 	"Mã Đạp Hồ",
		   "locate" :	({ 211,159,141, }),
		]),		   

	401:	([ "name" : 	"Hổ Lao Quan",
		   "locate" :	({ 089,85,59 }),
		]),		   
	402:	([ "name" : 	"Ky Quan",
		   "locate" :	({ 181,226,48, }),
		]),		   
	403:	([ "name" : 	"Cự Lộc",
		   "locate" :	({ 131,64,63, }),
		]),		   
	404:	([ "name" : 	"Trác Lộc",
		   "locate" :	({ 271,199,183, }),
		]),		   
	405:	([ "name" : 	"Dị Thủy",
		   "locate" :	({ 272,113,180, }),
		]),		   
	406:	([ "name" : 	"Quế Lăng",
		   "locate" :	({ 242,133,40, }),
		]),		   
	407:	([ "name" : 	"Mục Dã",
		   "locate" :	({ 241,138,43, }),
		]),		   
	408:	([ "name" : 	"Thái Hành Sơn",
		   "locate" :	({ 132,83,35, }),
		]),		   
	409:	([ "name" : 	"Tấn Dương",
		   "locate" :	({ 182,134,32, }),
		]),		   
	410:	([ "name" : 	"Bình Nguyên",
		   "locate" :	({ 243,120,51, }),
		]),		   
	411:	([ "name" : 	"Nhạn Môn Quan",
		   "locate" :	({ 155,131,44, }),
		]),		   
	412:	([ "name" : 	"Trường Bình",
		   "locate" :	({ 231,157,158, }),
		]),
		
	501:	([ "name" : 	"Ranh Giới Đầm Lầy",
		   "locate" :	({ 163,81,109, }),
		]),	
	502:	([ "name" : 	"Địa Giới Đầm Lầy",
		   "locate" :	({ 164,76,102, }),
		]),
	503:	([ "name" : 	"Chân núi Đại Biệt",
		   "locate" :	({ 261,101,42, }),
		]),
	504:	([ "name" : 	"Đại Biệt Sơn",
		   "locate" :	({ 262,91,35, }),
		]),
	505:	([ "name" : 	"Vu Sơn",
		   "locate" :	({ 263,53,46, }),
		]),
	506:	([ "name" : 	"Bà Dương Hồ",
		   "locate" :	({ 264,48,117, }),
		]),
	507:	([ "name" : 	"Xích Bích",
		   "locate" :	({ 265,79,47, }),
		]),
	508:	([ "name" : 	"Thái Hồ",
		   "locate" :	({ 266,81,75, }),
		]),
	509:	([ "name" : 	"Chân núi Thái Sơn",
		   "locate" :	({ 112,149,178, }),
		]),
	510:	([ "name" : 	"Thái Sơn",
		   "locate" :	({ 111,136,180, }),
		]),		
			
	601:	([ "name" : 	"Đông Hải Ngư Thôn",
		   "locate" :	({ 011,51,43, }),	
		]),		   
	602:	([ "name" : 	"Bờ Đông Hải",
		   "locate" :	({ 012,108,52, }),
		]),		   
	603:	([ "name" : 	"Hải tân１",
		   "locate" :	({ 013,51,121, }),
		]),		   
	604:	([ "name" : 	"Hải tân２",
		   "locate" :	({ 014,70,77, }),
		]),		   
	605:	([ "name" : 	"Đông Hải Đảo",
		   "locate" :	({ 015,130,29, }),
		]),		   
	606:	([ "name" : 	"Kênh Trịnh Quốc 1",
		   "locate" :	({ 151,76,24, }),
		]),		   
	607:	([ "name" : 	"Kênh Trịnh Quốc 2",
		   "locate" :	({ 152,47,40, }),
		]),		   
	608:	([ "name" : 	"Kênh Trịnh Quốc 3",
		   "locate" :	({ 153,31,48, }),	
		]),		   	   		   		   		   		   		   		   															
]);




// 函数:获取人物造型
int get_char_picid() { return 6010; }
void do_welcome(string arg);

// 函数:构造处理
void create()
{
        set_name("Tân Thủ Tiên Cô");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
}

void do_look(object who)
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, "");
}

void do_welcome( string arg )
{
        object who = this_object();
        __FILE__ ->do_welcome2(who, arg);
}

void do_welcome2( object who, string arg )
{
	int flag,id,i,size,p, x, y, z, *locate;
       	object me, robber;
       	string result;
       	mapping temp;
        me = this_player();
        flag = to_int(arg);
        me->set_time( "talk",  0);
        id = getoid(who);
        if (arg=="")
        {
        	if (me->get_level()>50)
        		result = sprintf(" %s :\n Bạn đã vượt quá cấp 50. Bây giờ nếu vẩn muốn sử dụng phương thức chuyển gửi cung cấp cho người mới, mỗi lần chuyển gửi đều phải trả cho tôi 500 lượng vàng.\n", who->get_name() );
        	else
        		result = sprintf(" %s :\n Ái chà, bạn mới đến phải không, nhận ra ta không? Ta chính là đỉnh đỉnh đại danh Tân Thủ đặc phái Dịch Phu viên đây! Chưởng Môn các môn phái vì sự phát triển của các đệ tử mới, nên đã nhờ ta ở đây xem xem có người nào mới giống bạn không, để có thể gửi bạn đến khu vực đẳng cấp thích hợp để luyện cấp. Chỉ giới hạn người mới từ cấp 10 đến cấp 50, nắm bắt cơ hội đi!\n", who->get_name() );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 10 đến cấp 14\ntalk %x# welcome.100\n", id );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 15 đến cấp 19\ntalk %x# welcome.200\n", id );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 20 đến cấp 24\ntalk %x# welcome.300\n", id );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 25 đến cấp 30\ntalk %x# welcome.400\n", id );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 31 đến cấp 40\ntalk %x# welcome.500\n", id );
        	result += sprintf(ESC "Chuyển đến bản đồ luyện cấp từ cấp 41 đến cấp 50\ntalk %x# welcome.600\n", id );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return ;
        }
        if (me->get_level()<10)
        {
        	result = sprintf(" %s :\n Ngươi vẫn còn rất kém cỏi, hãy hoàn thành một số nhiệm vụ ở gần Tân Thủ Thôn, đạt đến cấp 10 rồi hãy đến tìm ta.\n", who->get_name() );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return;
        }
	if( me->get_save_2("51cuanye.time")  )
	{
        	result = sprintf("%s:\n    你领取了接受极限穿越任务，我就暂不接待了.\n", who->get_name() );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return;
	}
        if( present("钱票", me, 1, MAX_CARRY) )
        {
        	result = sprintf("%s:\n    你身上有钱票，我就暂不接待了.\n", who->get_name() );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return;        	
        }
        if( present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY) )
        {
        	result = sprintf("%s:\n    你身上有Vật Phẩm Quý Bấu，我就暂不接待了.\n", who->get_name() );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return;   
        }
        if( objectp( robber = me->get_quest("escort.robber#") ) && robber->is_escort_robber() )    // 寻找蒙面人
        {
        	result = sprintf("%s:\n    你附近有蒙面人，我就暂不接待了.\n", who->get_name() );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	return;         	
        }        
        switch(flag)
        {
        case 100:
        	result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 10 trở lên cấp 15 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<7;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[101+i]["name"], id, 101+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;
        case 200:
        	result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 15 trở lên cấp 20 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<3;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[201+i]["name"], id, 201+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;        	
        case 300:
        	result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 20 trở lên cấp 25 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<7;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[301+i]["name"], id, 301+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;           
        case 400:
        	result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 25 trở lên cấp 30 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<12;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[401+i]["name"], id, 401+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;     
        case 500:
			result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 31 trở lên cấp 40 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<10;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[501+i]["name"], id, 501+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;          
        case 600:
			result = sprintf(" %s :\n Ngươi muốn đi bản đồ luyện cấp từ cấp 41 trở lên cấp 50 trở xuống phải không? Lại đây, hãy lựa chọn đi! Nhấn Alt+M thì có thể tra xem chủng loại quái vật cụ thể bản đồ này.\n", who->get_name() );
        	for (i=0;i<8;i++)
        		result += sprintf(ESC "%s\ntalk %x# welcome.%d\n", maps[601+i]["name"], id, 601+i );
        	result += ESC"Rời khỏi\nCLOSE";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
        	break;           		
        default:     	        	
        	temp = 	maps[flag];
        	if (!temp) return;
        	if (temp["name"]==0) return;
        	locate = temp["locate"];
        	if (sizeof(locate)!=3) return;
        	if (me->get_level()>50)
        	{
        		if (me->get_cash()<500)
        		{
        			result = sprintf("%s:\n    Ngươi thật sự không có tiền ?\n", who->get_name() );
		        	result += ESC"Rời khỏi\nCLOSE";
		        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
				return ;        			
        		}
        		me->add_cash(-500);
        	}
        	z = locate[0], x = locate[1], y = locate[2];
        	if( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) )
        	{
	                x = p / 1000;  y = p % 1000;	
	                me->add_to_scene( z, x, y, 3 );        		
        	}
        	break;
        }
}
