
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <npc.h>
#include <time.h>

#define SAVE_FILE       "data/city/plant" SAVE_EXTENSION

inherit DBASE_F;
inherit SAVE_F;

int Day;

static mapping sayword = ([
	"Tề Quốc" : "Sở Quốc căn bản không trồng ra thứ tốt, chỉ có Sở Quốc của ta mới có thể thôy.",
	"Hàn Quốc" : "Hàn Quốc của ta trồng ra rất nhiều thứ ngon, không giống Nguỵ Quốc toàn châu chấu bay khắp nơi.",
	"Triệu Quốc" : "Triệu Quốc chúng ta có thể nói là mùa màng thu hoạch tốt, không giống như Yên Quốc thường xuyên rét lạnh.",
	"Ngụy Quốc" : "Vùng đất Triệu Quốc rất hoang vu, nên ngươi muốn trồng trọt hãy đến Nguỵ Quốc của chúng ta.",
	"Tần Quốc" : "Ngươi không nên tìm đến Hàn Quốc mà nên đến Tần Quốc của chúng ta mà trồng trọt.",
	"Sở Quốc" : "Trong 7 nước, Sở Quốc của chúng ta trồng trọt ra sản phẩm tốt nhất.",
	"Yên Quốc" : "Tề Quốc hay có gió bão, nếu ngươi muốn trồng trọt thì hãy đến Yên Quốc gặp ta!",
	]);

// 函数:生成二进制码
void SAVE_BINARY() { }

// 函数:构造处理
void create() 
{
	restore_object(SAVE_FILE);	
        call_out( "hour_callout", time() -  time() / 3600 * 3600 ); 
}

int set_day(int d) {return Day = d;}

int get_day() {return Day;}

// 函数:取存盘文件名
string get_save_file() { return SAVE_FILE; }

void reset_plant()
{
	object me = this_object();
	int iTime, day, hour, i, size, j;
	string * country = ({ "Tề Quốc", "Hàn Quốc", "Triệu Quốc", "Ngụy Quốc", "Tần Quốc", "Sở Quốc", "Yên Quốc",  });
	string result;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	hour = mxTime[TIME_HOUR];
	day = time()/(24*3600);	
	me->set_day(day);	
	if (MAIN_D->get_host_type()==6012) return;
	size = sizeof(country);
	for (i=0;i<size;i++)
	{
		me->set_save(country[i], 0);
	}
	i = random(size);
	j = random(2);
	if (j==0)
	{
		me->set_save(country[i], -90);
		result = sprintf("Nghe nói %s có gió bão , những sản phẩm của nông dân bị thiệt hại rất nghiêm trọng ! Còn nghe nói có người đã thấy cả con bò cũng bị cuốn lên Trời, không biết có phải là thực không.", country[i] );
	}
	else
	{
		me->set_save(country[i], -50);
		result = sprintf("Nghe nói %s có gió bão , những sản phẩm của nông dân bị thiệt hại rất nghiêm trọng ! Còn nghe nói có người đã thấy cả con bò cũng bị cuốn lên Trời, không biết có phải là thực không.", country[i] );
	}		
	CHAT_D->rumor_channel( 0, HIM + result );
	country -= ({ country[i] }); 
	size = sizeof(country);
	i = random(size);
	j = random(2);
	if (j==0)
	{
		me->set_save(country[i], 50);
		result = sprintf("Nghe nói gần đây %s mưa thuận gió hòa, sản phẩm trong nông trường phát triển rất tốt.", country[i] );
	}
	else
	{
		me->set_save(country[i], 100);
		result = sprintf("Nghe nói gần đây %s mưa thuận gió hòa, sản phẩm trong nông trường phát triển rất tốt.", country[i] );
	}		
	CHAT_D->rumor_channel( 0, HIM + result );	
	save();	
}

void hour_callout()
{
	object me = this_object();
	int iTime, day, hour, i, size, j;
	string * country = ({ "Tề Quốc", "Hàn Quốc", "Triệu Quốc", "Ngụy Quốc", "Tần Quốc", "Sở Quốc", "Yên Quốc",  });
	string result;
	mixed *mxTime;
	iTime = time();
	call_out( "hour_callout", 3600 ); 
	mxTime = localtime(iTime);
	hour = mxTime[TIME_HOUR];
	day = time()/(24*3600);
	if (hour>=12 && day!=me->get_day())
	{	
		reset_plant();
	}	
}

void do_look(object me, object who )
{
        string result = "";
	mixed *mxTime;
	int iTime, day, hour;
	iTime = time();
	mxTime = localtime(iTime);
	day = time()/(24*3600);
	hour = mxTime[TIME_HOUR];
	if (MAIN_D->get_host_type()==6012)
	{
		send_user(me, "%c%s", '!', "Gieo trồng系统尚未开放!");
		return;
	}
	if (hour>=12 && day!="/sys/user/plant"->get_day()) reset_plant();
        if (me->get_level()<30)
        {
        	result = sprintf("%s:\n    %s\n    Sau khi ngươi đạt cấp 30, có thể đến tìm ta để sản xuất sản phẩm Nông nghiệp.\n", who->get_name(), sayword[who->get_city_name()] );
        	result += ESC "Rời khỏi\nCLOSE\n";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
        	return;
        }
        if (hour<12)
        {
        	result = sprintf("%s:\n    Khi khác hãy đến tìm ta, vụ mùa bắt đầu từ 12 h trưa và kết thúc là 24h tối.\n", who->get_name() );
        	result += sprintf( ESC "Lĩnh thu hoạch\ntalk %x# welcome.20\n", getoid(who) );
        	result += ESC "Rời khỏi\nCLOSE\n";
        	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
        	return;
        }
        result = sprintf("%s:\n    %s\n", who->get_name(), sayword[who->get_city_name()] );
        result += sprintf( ESC "Sản xuất sản phẩm Nông nghiệp\ntalk %x# welcome.10\n", getoid(who) );
        result += sprintf( ESC "Lĩnh thu hoạch\ntalk %x# welcome.20\n", getoid(who) );
        result += sprintf( ESC "Kiểm tra gieo trồng\ntalk %x# welcome.30\n", getoid(who) );
        if (is_god(me))
        {
        	result += sprintf( ESC "Thiết lập gieo trồng hoàn thành\ntalk %x# welcome.40\n", getoid(who) );
        	result += sprintf( ESC "Tuỳ cơ mưa gió bão bùng\ntalk %x# welcome.50\n", getoid(who) );
        }
	result += ESC "Rời khỏi\nCLOSE\n";
	send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

void do_welcome(object me, object who, string arg )
{
	string result = "", *key, file, result2;
	int type, level, price, flag, p, i;
	object plant;
	mixed *mxTime;
	int iTime, day, hour, count, inv;
	object obj;
	if (MAIN_D->get_host_type()==6012)
	{
		send_user(me, "%c%s", '!', "Gieo trồng系统尚未开放!");
		return;
	}	
	iTime = time();
	mxTime = localtime(iTime);
	hour = mxTime[TIME_HOUR];
	level = me->get_level();
	day = time()/(24*3600);
	if (hour>=12 && day!="/sys/user/plant"->get_day()) reset_plant();
	if (level<30) return;
	if (!arg) return;
	plant = this_object();
	key = explode (arg, " ");
	type = to_int(key[0]);
	switch(type)
	{
	case 10:
		if (hour<12) return;
		if (me->get_save_2("plant1.city") && me->get_save_2("plant1.city")!=who->get_city_name())
		{
			result = sprintf("%s:\n    Nếu như ngươi đã tìm %s Sản xuất sản phẩm Nông nghiệp thì hãy đợi vụ mùa sau rồi đến tìm ta.\n", who->get_name(), me->get_save_2("plant1.city") );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}
		if (me->get_save_2("plant1.count")>0 && me->get_save_2("plant2.count")>0)
		{
			result = sprintf("%s:\n    Nông trường của ta hiện tại đã đầy, muốn sản xuất thêm sản phẩm thì ta nghĩ không được rồi.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if ( (me->get_save_2("plant1.count")>0 && me->get_save_2("plant1.day")!=day ) || (me->get_save_2("plant2.count")>0 && me->get_save_2("plant2.day")!=day ) )
		{
			result = sprintf("%s:\n    Ngươi vẫn còn chút sản phẩm chưa lấy, hãy lấy đi không thôy bị hư ráng chịu nha.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}		
		result = sprintf("%s:\n    Ngươi muốn ta trồng giúp ngươi sản phẩm gì ?\n", who->get_name() );
		result += sprintf( ESC "Khoai Lang\ntalk %x# welcome.220\n", getoid(who) );
		result += sprintf( ESC "Gạo Kê\ntalk %x# welcome.145\n", getoid(who) );
		result += sprintf( ESC "Bắp\ntalk %x# welcome.144\n", getoid(who) );
		result += sprintf( ESC "Trứng Gà\ntalk %x# welcome.171\n", getoid(who) );
		if (level>=45)
			result += sprintf( ESC "Thịt bò\ntalk %x# welcome.181\n", getoid(who) );
		if (level>=50)
			result += sprintf( ESC "Bí Đỏ\ntalk %x# welcome.148\n", getoid(who) );
		if (level>=60)
			result += sprintf( ESC "Cao Lương\ntalk %x# welcome.146\n", getoid(who) );
		if (level>=65)
			result += sprintf( ESC "Cá\ntalk %x# welcome.187\n", getoid(who) );							
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 20:
	case 21:
		if (me->get_save_2("plant1.city")==0 || me->get_save_2("plant1.city") && me->get_save_2("plant1.city")!=who->get_city_name())
		{
			result = sprintf("%s:\n    Ngươi đã tìm nông phu của nước khác, hãy huỷ bỏ rồi đến gặp ta.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}	
		if (me->get_save_2("plant2.day")>0 && me->get_save_2("plant2.day")<day-1 )
		{
			me->delete_save_2("plant2");
		}
		if (me->get_save_2("plant1.day")>0 && me->get_save_2("plant1.day")<day-1 )
		{
			me->delete_save_2("plant1");
			if (me->get_save_2("plant2.day")) me->set_save_2("plant1.city", who->get_city_name());
		}		
		if ( me->get_save_2("plant1.day")>day+10) me->set_save_2("plant1.day", day-1);
		if ( me->get_save_2("plant2.day")>day+10) me->set_save_2("plant2.day", day-1);
		if ( ( me->get_save_2("plant1.day")==0 || me->get_save_2("plant1.day")>=day ) && ( me->get_save_2("plant2.day")==0 || me->get_save_2("plant2.day")>=day ) )
		{
			result = sprintf("%s:\n    Chưa tới thời điểm thu hoạch đâu.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}			
		if (day>plant->get_day())
		{
			result = sprintf("%s:\n    Chưa tới thời điểm thu hoạch đâu.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}				
		flag = plant->get_save(who->get_city_name());	
		if (flag!=0 && type==20)
		{
			switch(flag)
			{
			case -90:
				result = sprintf("%s:\n    Bởi vì gió bão nặng nề, nên sản phẩm của ngươi chỉ còn lại nhường đó.\n", who->get_name() );
				break;
			case -50:
				result = sprintf("%s:\n    Bởi vì gió bão nặng nề, nên sản phẩm của ngươi chỉ còn lại nhường đó.\n", who->get_name() );
				break;
			case 50:
				result = sprintf("%s:\n    Bởi vì mưa thuận gió hoà, sản phẩm của ngươi lĩnh được nhiều hơn.\n", who->get_name() );
				break;
			case 100:
			default:
				result = sprintf("%s:\n    Bởi vì mưa thuận gió hoà, sản phẩm của ngươi lĩnh được nhiều hơn.\n", who->get_name() );
				break;
			}
			result += sprintf( ESC "Lĩnh thu hoạch\ntalk %x# welcome.21\n", getoid(who) );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}		
		// 检查身上的位置够不够	
		count = 0;	
		inv = 0;
		if (me->get_save_2("plant1.day")+1==plant->get_day())
		{
			count = me->get_save_2("plant1.count") * (100 + flag)/100;
			if ((count/30)*30==count) inv += count/30;
			else inv += (count/30+1);
		}
		if (me->get_save_2("plant2.day")+1==plant->get_day())
		{
			count = me->get_save_2("plant2.count") * (100 + flag)/100;			
			if ((count/30)*30==count) inv += count/30;
			else inv += (count/30+1);			
		}
		if( sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - inv )
		{
			result = sprintf("%s:\n    Ngươi hãy chừa %d ô trống rồi đến lĩnh thu hoạch.\n", who->get_name(), inv );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;					
		}			
		if (me->get_save_2("plant2.day")+1==plant->get_day())
		{
			type = me->get_save_2("plant2.type");
			count = me->get_save_2("plant2.count");
			count = count * (100 + flag)/100;
			flag = plant->get_save(who->get_city_name());
			
			me->delete_save_2("plant2");
			for (i=0;i<count/30;i++)
			{
				obj = new (sprintf("/item/stuff/%04d", type));
				if (!obj) continue;
				obj->set_amount(30);
                                p =obj->move(me, -1);
                                obj->add_to_user(p);				
			}
			if ((count/30)*30!=count)
			{
				obj = new (sprintf("/item/stuff/%04d", type));
				if (!obj) return;
				obj->set_amount(count - (count/30)*30);
                                p =obj->move(me, -1);
                                obj->add_to_user(p);				
			}			
		}		
		if (me->get_save_2("plant1.day")+1==plant->get_day())
		{
			type = me->get_save_2("plant1.type");
			count = me->get_save_2("plant1.count");
			// 判断是否同一天						
			count = count * (100 + flag)/100;			
			me->delete_save_2("plant1");
			if (me->get_save_2("plant2.day")) me->set_save_2("plant1.city", who->get_city_name());
			for (i=0;i<count/30;i++)
			{
				obj = new (sprintf("/item/stuff/%04d", type));
				if (!obj) continue;
				obj->set_amount(30);
                                p =obj->move(me, -1);
                                obj->add_to_user(p);				
			}
			if ((count/30)*30!=count)
			{
				obj = new (sprintf("/item/stuff/%04d", type));
				if (!obj) return;
				obj->set_amount(count - (count/30)*30);
                                p =obj->move(me, -1);
                                obj->add_to_user(p);				
			}			
		}
		result = sprintf("%s:\n    Lĩnh thu hoạch thành công.\n", who->get_name() );
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);		
		break;
	case 30:
		if (me->get_save_2("plant2.day")>0 && me->get_save_2("plant2.day")<day-1 )
		{
			me->delete_save_2("plant2");
		}
		if (me->get_save_2("plant1.day")>0 && me->get_save_2("plant1.day")<day-1 )
		{
			me->delete_save_2("plant1");
			if (me->get_save_2("plant2.day")) me->set_save_2("plant1.city", who->get_city_name());
		}	
		if (me->get_save_2("plant1.city")==0 )
		{
			result = sprintf("%s:\n    Ngươi hiện tại không có nhờ trồng sản phẩm gì hết.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;				
		}
		if ( me->get_save_2("plant1.city")!=who->get_city_name())
		{
			result2 = "";
			if (me->get_save_2("plant1.day"))
			{
				type = me->get_save_2("plant1.type");
				count = me->get_save_2("plant1.count");	
				file = sprintf("/item/stuff/%04d", type);			
				result2 = sprintf("%d cái%s", count, file->get_name());
			}
			if (me->get_save_2("plant2.day"))
			{
				type = me->get_save_2("plant2.type");
				count = me->get_save_2("plant2.count");	
				file = sprintf("/item/stuff/%04d", type);			
				if (result2=="")
					result2 = sprintf("%d cái%s", count, file->get_name());
				else
					result2 = sprintf("和%d cái%s", count, file->get_name());
			}			
			result = sprintf("%s:\n    Nghe nói ngươi ở %s nông phu trồng loại %s ? Ta dám chắc chắn hắn sẽ không cho ngươi lĩnh thu hoạch đâu.\n", who->get_name(), me->get_save_2("plant1.city"), result2 );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}	
		result = sprintf("%s:\n    Bạn gieo trồng như sau:\n", who->get_name() );
		if (me->get_save_2("plant1.day"))
		{
			type = me->get_save_2("plant1.type");
			count = me->get_save_2("plant1.count");	
			file = sprintf("/item/stuff/%04d", type);
			result += sprintf("    %s%d cái, Thu hoạch thời gian:", file->get_name(), count);
			if (hour>=12 && me->get_save_2("plant1.day")==plant->get_day())
				result += ("Ngày mai 12 giờ trưa tới ngày kia 12 giờ trưa\n");			
			else	
				result += ("Ngày mai 12 giờ trưa tới ngày kia 12 giờ trưa\n");
		}
		if (me->get_save_2("plant2.day"))
		{
			type = me->get_save_2("plant2.type");
			count = me->get_save_2("plant2.count");	
			file = sprintf("/item/stuff/%04d", type);
			result += sprintf("    %s%d cái, Thu hoạch thời gian:", file->get_name(), count);
			if (hour>=12 && me->get_save_2("plant2.day")==plant->get_day())
				result += ("Ngày mai 12 giờ trưa tới ngày kia 12 giờ trưa\n");			
			else	
				result += ("Ngày mai 12 giờ trưa tới ngày kia 12 giờ trưa\n");
		}		
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;	
	case 40:
		if (!is_god(me)) return;	
		if (me->get_save_2("plant1.day"))		
			me->set_save_2("plant1.day", plant->get_day()-1);	
		if (me->get_save_2("plant2.day"))
			me->set_save_2("plant2.day", plant->get_day()-1);			
		break;
	case 50:
		if (!is_god(me)) return;
		"/sys/user/plant"->reset_plant();
		break;
	case 220:
	case 145:
	case 144:
	case 171:
	case 181:
	case 148:
	case 146:
	case 187:	
		if (hour<12) return;
		if (me->get_save_2("plant1.city") && me->get_save_2("plant1.city")!=who->get_city_name())
		{
			result = sprintf("%s:\n    Nếu như ngươi đã tìm %s Sản xuất sản phẩm Nông nghiệp thì hãy đợi vụ mùa sau rồi đến tìm ta.\n", who->get_name(), me->get_save_2("plant1.city") );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}	
		if ( me->get_save_2("plant1.count")>0 && me->get_save_2("plant2.count")>0  )
		{
			result = sprintf("%s:\n    Nông trường của ta hiện tại đã đầy, muốn sản xuất thêm sản phẩm thì ta nghĩ không được rồi.\n", who->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}	
		file = sprintf("/item/stuff/%04d", type);		
		if ( me->get_save_2("plant1.type")==type || me->get_save_2("plant2.type")==type  )
		{
			result = sprintf("%s:\n    Ngươi muốn %s ta đã giúp ngươi trồng, không cần trồng trọt lại thứ này.\n", who->get_name(), file->get_name() );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}		
		if (me->get_level()<file->get("plant"))
		{
			return;
		}	
		if (sizeof(key)==1)
		{
			result = sprintf("%s:\n    Chỗ ta có thể trồng 90 cái %s, Ngươi muốn trồng %s nhiêu cái?\n", who->get_name(), file->get_name(), file->get_name() );
			result += sprintf( ESC "30\ntalk %x# welcome.%d 30\n", getoid(who), type );
			result += sprintf( ESC "60\ntalk %x# welcome.%d 60\n", getoid(who), type );
			result += sprintf( ESC "90\ntalk %x# welcome.%d 90\n", getoid(who), type );
			result += ESC "Rời khỏi\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		count = to_int(key[1]);
		if (sizeof(key)==2)
		{			
			result = sprintf("%s:\n    Ngươi nói phải trồng %d cái %s, cần giao nộp %d lượng, ngươi muốn trồng không?\n", who->get_name(), count, file->get_name(), count* file->get("pvalue") );
			result += sprintf( ESC "Được rồi, ta muốn trồng\ntalk %x# welcome.%d %d !\n", getoid(who), type, count );
			result += ESC "Như vậy có thể tính toán sổ sách không!\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;			
		}
		if (sizeof(key)==3)
		{
			price = count * file->get("pvalue");
			if (me->get_cash()<price)
			{
				result = sprintf("%s:\n    Ngươi không đủ ngân lượng, khi khác lại đến tìm ta!\n", who->get_name() );
				result += ESC "Rời khỏi\nCLOSE\n";
				send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
			me->add_cash(-price);
			me->add_gold_log("plant", price);
                	me->log_money("Gieo trồng", -price);
                	"/sys/sys/count"->add_use("Gieo trồng", price);
                	me->set_save_2("plant1.city", who->get_city_name());
                	if (me->get_save_2("plant1.count")==0)
                	{
                		me->set_save_2("plant1.type", type);
                		me->set_save_2("plant1.count", count);
                		me->set_save_2("plant1.day", day);
                	}
                	else
                	{
                		me->set_save_2("plant2.type", type);
                		me->set_save_2("plant2.count", count);
                		me->set_save_2("plant2.day", day);
                	}                	
			result = sprintf("%s:\n    Ngươi phải nhớ ngày mai đến lĩnh thu hoạch, nếu không sản phẩm sẽ bị hư.\n", who->get_name() );
			result += ESC "Xác nhận\nCLOSE\n";
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
                	
		}
		break;
	}
}
