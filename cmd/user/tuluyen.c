
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>
#include <task.h>
#include <cmd.h>

int main( object me, string arg )
{
	int gender,gender1,p,x,y,i,z,iTime,iDay;
	object item, item1;
	string result,cmd1;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);     
	iDay = mxTime[TIME_YDAY];
	
		if( !objectp( item = present("Tu Luyện Bao", me, 1, MAX_CARRY*4) ) )
        {
                write_user(me, ECHO "Bạn không có Tu Luyện Bao !");
                return 1;
        }	
	if ( arg==0 )
	{
		result = sprintf("Bạn đang sử dụng Tu Luyện Bao, xin hãy lựa chọn chức năng : \n" ); 
		if (me->get_save("nhanquaonline")>0)
		result += ESC HIR "Nhận quà mỗi 5 phút online...\ntuluyen nhanqua\n"; 
		else
		result += ESC HIG"Nhận quà mỗi 5 phút online...\ntuluyen nhanqua\n";	
		result += ESC HIC"Nhận hỗ trợ hằng ngày...\ntuluyen hotro\n";  
		result += ESC HIY"Tu Luyện...\ntuluyen tuluyen2\n";  
		send_user( me, "%c%s", ':', result);
                return 1;
	}
	if ( arg=="nhanqua" )
	{
		if (me->get_save_2("nhanqua.day")==iDay)
		{
			send_user(me,"%c%s",':',"Hôm nay đã nhận đủ 5 phần quà rồi ! \n"ESC"Xác nhận.");
			return 1;
		}
		if (me->get_save("nhanquaonline")>0)
		{
			send_user(me,"%c%s",':',sprintf("Bạn còn %d giây nữa sẽ được nhận phần quà tiếp theo ! \n"ESC"Xác nhận.",me->get_save("nhanquaonline") ));
			return 1;
		}
		if(USER_INVENTORY_D->get_free_count(me) < 3 )
		{
				notify( "Hành trang không đủ 3 chỗ trống" );
		return 1;
		}
		if ( me->get_save("nhanqua") < 1 )
		{
			me->set_save("nhanquaonline",300);
			me->add_save("nhanqua",1);
			
			item1 = new("/item/08/0002");
			item1->set_amount(2);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
		send_user(me,"%c%s",':',sprintf("Phần quà ( 1 ) : \nTù Và Chiến Quốc + 2 \n"ESC"Xác nhận."));
			return 1;
		}
		if ( me->get_save("nhanqua") == 1 )
		{
			me->set_save("nhanquaonline",300);
			me->add_save("nhanqua",1);
			
			item1 = new("/item/tuiquatanthuhieu/0002");
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0004");
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
		send_user(me,"%c%s",':',sprintf("Phần quà ( 2 ) : \nĐại Huyết Thạch + 1 \nĐại Pháp Lực Thạch + 1 \n"ESC"Xác nhận."));
			return 1;
		}
		if ( me->get_save("nhanqua") == 2 )
		{
			me->set_save("nhanquaonline",300);
			me->add_save("nhanqua",1);
			
			item1 = new("/item/tuiquatanthuhieu/0008");
			item1->set_amount(2);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0010");
			item1->set_amount(2);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
		send_user(me,"%c%s",':',sprintf("Phần quà ( 3 ) : \nTrị Dược(khoá) + 2 \nPhục Dược(khoá) + 2 \n"ESC"Xác nhận."));
			return 1;
		}
		if ( me->get_save("nhanqua") == 3 )
		{
			me->set_save("nhanquaonline",300);
			me->add_save("nhanqua",1);
			
			item1 = new("/item/tuiquatanthuhieu/0008");
			item1->set_amount(4);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0010");
			item1->set_amount(4);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
		send_user(me,"%c%s",':',sprintf("Phần quà ( 4 ) : \nTrị Dược(khoá) + 4 \nPhục Dược(khoá) + 4 \n"ESC"Xác nhận."));
			return 1;
		}
		if ( me->get_save("nhanqua") == 4 )
		{
			me->set_save_2("nhanqua.day", iDay);
			me->set_save("nhanqua",0);
			
			item1 = new("/item/tuiquatanthuhieu/0008");
			item1->set_amount(4);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0010");
			item1->set_amount(4);
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0002");
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
			item1 = new("/item/tuiquatanthuhieu/0004");
			i = item1->move2(me,-1);
			item1->add_to_user(i);
			
		send_user(me,"%c%s",':',sprintf("Phần quà ( 5 ) : \nTrị Dược(khoá) + 4 \nPhục Dược(khoá) + 4 \nĐại Huyết Thạch + 1 \nĐại Pháp Lực Thạch + 1 \n"ESC"Xác nhận."));
			return 1;
		}
                return 1;
	}
	if ( arg=="hotro" )
	{
		if (me->get_save_2("fride.day")==iDay)
		{
			send_user(me,"%c%s",':',"Hôm nay đã nhận rồi ! \n"ESC"Xác nhận.");
			return 1;
		}
		if(USER_INVENTORY_D->get_free_count(me) < 1 )
		{
				notify( "Hành trang không đủ 1 chỗ trống" );
		return 1;
		}
		me->set_save_2("fride.day", iDay);
			item1 = new("/item/08/0006");
			i = item1->move2(me,-1);
			item1->add_to_user(i);
	//	me->add_cash( me->get_level()*777 );
		me->add_exp( me->get_level()*555 );
		"sys/sys/test_db"->add_yuanbao(me, me->get_level()/7 );
		send_user(me,"%c%s",':',sprintf("Chiến Quốc Lệnh + 1 \nKinh nghiệm + %d \nNgân Bảo + %d \n"ESC"Xác nhận.",me->get_level()*555,me->get_level()/7));
	//	send_user(me,"%c%s",':',sprintf("Chiến Quốc Lệnh + 1 \nNgân lượng + %d \nKinh nghiệm + %d \nNgân Bảo + %d \n"ESC"Xác nhận.",me->get_level()*777,me->get_level()*555,me->get_level()/7));
                return 1;
	}
	if ( arg=="tuluyen2" )
	{
		i = gone_time( me->get_login_time() );	
			result = sprintf("Bạn đang sử dụng Tu Luyện Bao, xin hãy lựa chọn chức năng :\n" );
		result += ESC HIC"Nhận thời gian gấp đôi kinh nghiệm\ntuluyen gapdoi\n"; 
		result += ESC HIY"Nhận thời gian gấp đôi kinh nghiệm VIP\ntuluyen gapdoi2\n";  
		if (me->get_save_2("double_time.freeze")>0)
		result += ESC HIG"Giải trừ đóng băng thời gian nhân đôi kinh nghiệm\ntuluyen giaidongbang\n";
		else if ( i+ me->get_game_time()<me->get_double_time())
		result += ESC HIG"Đóng băng thời gian nhân đôi kinh nghiệm\ntuluyen dongbang\n";
		send_user( me, "%c%s", ':', result);
                return 1;
	}
	if (arg=="gapdoi")
	{
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
			me->set_save_2("double_time.freeze", 0);	//冻结的双倍时间
		}
		if (me->get_save_2("double_time.time")>=8)
		{
			y = 7*24*3600 - ((time() - 4 * 24*3600+8*3600) % (7*24*3600));
			if (y<24*3600)
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d giờ sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y/3600 ));			
			}
			else
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d ngày sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y / (24*3600) ));				
			}
			return 1;
		}
               result = sprintf("Xin hãy lựa chọn thời gian muốn nhân đôi :\n" );
		result += ESC HIC"1 giờ\ntuluyen 1gio\n"; 
		result += ESC HIY"2 giờ\ntuluyen 2gio\n"; 
		result += ESC HIG"4 giờ\ntuluyen 4gio\n";    
		send_user( me, "%c%s", ':', result);	
			return 1;
    }
	if (arg=="gapdoi2")
	{
		if ( !me->get_vip() )
		{
			send_user(me,"%c%s",':', sprintf("Bạn không phải hội viên VIP.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		x = me->get_save_2("vip_package.doubles");
		y = x / 2;
		z = x % 2;
	                	
	    if ( z ) {
		result = sprintf("Bạn có thể nhận nhân đôi kinh nghiệm còn "HIR "%d giờ 30 phút"NOR ".Muốn nhận nhân đôi kinh nghiệm không ?\n",y);
		result += ESC HIC"30 phút\ntuluyen 30phut\n"; 
		result += ESC HIY"1 giờ\ntuluyen 60phut\n"; 
		result += ESC HIG"2 giờ\ntuluyen 120phut\n";    
		send_user( me, "%c%s", ':', result);
		}
		else {
		result = sprintf("Bạn có thể nhận nhân đôi kinh nghiệm còn "HIR "%d giờ"NOR ".Muốn nhận nhân đôi kinh nghiệm không ?\n",y);
		result += ESC HIC"30 phút\ntuluyen 30phut\n"; 
		result += ESC HIY"1 giờ\ntuluyen 60phut\n"; 
		result += ESC HIG"2 giờ\ntuluyen 120phut\n";    
		send_user( me, "%c%s", ':', result);
		}
			return 1;
    }
	if (arg=="1gio")
	{
			p = 2;
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
			me->set_save_2("double_time.freeze", 0);	//冻结的双倍时间
		}
		if (me->get_save_2("double_time.freeze")>0)
		{
		send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi của bạn đã bị đóng băng, hãy giải trừ đóng băng trước khi nhận thời gian nhân đôi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}				
		if (me->get_save_2("double_time.time")>=8)
		{
			y = 7*24*3600 - ((time() - 4 * 24*3600+8*3600) % (7*24*3600));
			if (y<24*3600)
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d giờ sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y/3600 ));
			}
			else
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d ngày sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y / (24*3600) ));
			}
			return 1;
		}		
		if (me->get_save_2("double_time.time")+p>8)
		{
		        p = 8 - me->get_save_2("double_time.time");
		}
		send_user(me,"%c%s",':', sprintf("Bạn nhận được %d phút nhân đôi kinh nghiệm !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		
		me->add_save_2("double_time.time", p);
		p *= 1800;
		if ( i+ me->get_game_time()<me->get_double_time())
			me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);
		send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ %d thời gian nhân đôi kinh nghiệm, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", (me->get_double_time()-i-me->get_game_time()) / 60 ));		
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="2gio")
	{
			p = 4;
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
			me->set_save_2("double_time.freeze", 0);	//冻结的双倍时间
		}
		if (me->get_save_2("double_time.freeze")>0)
		{
		send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi của bạn đã bị đóng băng, hãy giải trừ đóng băng trước khi nhận thời gian nhân đôi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}				
		if (me->get_save_2("double_time.time")>=8)
		{
			y = 7*24*3600 - ((time() - 4 * 24*3600+8*3600) % (7*24*3600));
			if (y<24*3600)
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d giờ sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y/3600 ));
			}
			else
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d ngày sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y / (24*3600) ));
			}
			return 1;
		}		
		if (me->get_save_2("double_time.time")+p>8)
		{
		        p = 8 - me->get_save_2("double_time.time");
		}
		send_user(me,"%c%s",':', sprintf("Bạn nhận được %d phút nhân đôi kinh nghiệm !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		
		me->add_save_2("double_time.time", p);
		p *= 1800;
		if ( i+ me->get_game_time()<me->get_double_time())
			me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);
		send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ %d thời gian nhân đôi kinh nghiệm, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", (me->get_double_time()-i-me->get_game_time()) / 60 ));		
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="4gio")
	{
			p = 8;
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
			me->set_save_2("double_time.freeze", 0);	//冻结的双倍时间
		}
		if (me->get_save_2("double_time.freeze")>0)
		{
		send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi của bạn đã bị đóng băng, hãy giải trừ đóng băng trước khi nhận thời gian nhân đôi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}				
		if (me->get_save_2("double_time.time")>=8)
		{
			y = 7*24*3600 - ((time() - 4 * 24*3600+8*3600) % (7*24*3600));
			if (y<24*3600)
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d giờ sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y/3600 ));
			}
			else
			{
			send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ thời gian nhân đôi vượt quá 4 giờ, hãy chờ %d ngày sau rồi hãy nhận.\n"
			ESC"Ta biết rồi\nCLOSE\n", y / (24*3600) ));
			}
			return 1;
		}		
		if (me->get_save_2("double_time.time")+p>8)
		{
		        p = 8 - me->get_save_2("double_time.time");
		}
		send_user(me,"%c%s",':', sprintf("Bạn nhận được %d phút nhân đôi kinh nghiệm !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		
		me->add_save_2("double_time.time", p);
		p *= 1800;
		if ( i+ me->get_game_time()<me->get_double_time())
			me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);
		send_user(me,"%c%s",':', sprintf("Bạn đã tích luỹ %d thời gian nhân đôi kinh nghiệm, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", (me->get_double_time()-i-me->get_game_time()) / 60 ));		
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="30phut")
	{
			p = 1;
		if ( !me->get_vip() )
		{
			send_user(me,"%c%s",':', sprintf("Bạn không phải hội viên VIP.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		if ( me->get_save_2("vip_package.doubles") < p )
		{
			send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi kinh nghiệm VIP đã dùng rồi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
		}
		me->add_save_2("vip_package.doubles",-p);
		send_user(me,"%c%s",':', sprintf("Bạn nhận %d phút nhân đôi kinh nghiệm VIP, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		

		p *= 1800;
	        if ( i+ me->get_game_time()<me->get_double_time())
	        	me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);		
		send_user( me, "%c%c%c%w%c", 0x51, 1, 1,0001, 0 );
		send_user( me, "%c%c%c%w%w%c", 0x51, 1, 2, 0001, 1, 0 );
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="60phut")
	{
			p = 2;
		if ( !me->get_vip() )
		{
			send_user(me,"%c%s",':', sprintf("Bạn không phải hội viên VIP.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		if ( me->get_save_2("vip_package.doubles") < p )
		{
			send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi kinh nghiệm VIP đã dùng rồi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
		}
		me->add_save_2("vip_package.doubles",-p);
		send_user(me,"%c%s",':', sprintf("Bạn nhận %d phút nhân đôi kinh nghiệm VIP, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		

		p *= 1800;
	        if ( i+ me->get_game_time()<me->get_double_time())
	        	me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);		
		send_user( me, "%c%c%c%w%c", 0x51, 1, 1,0001, 0 );
		send_user( me, "%c%c%c%w%w%c", 0x51, 1, 2, 0001, 1, 0 );
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="120phut")
	{
			p = 4;
		if ( !me->get_vip() )
		{
			send_user(me,"%c%s",':', sprintf("Bạn không phải hội viên VIP.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		if ( me->get_save_2("vip_package.doubles") < p )
		{
			send_user(me,"%c%s",':', sprintf("Thời gian nhân đôi kinh nghiệm VIP đã dùng rồi.\n"
			ESC"Ta biết rồi\nCLOSE\n" ));
			return 1;
		}
		i = gone_time( me->get_login_time() );
		x = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
		if (me->get_save_2("double_time.week")!=x)
		{
			me->set_save_2("double_time.week", x);
			me->set_save_2("double_time.time", 0);		//双
			me->set_save_2("double_time.time1", 0);	//战国令
			me->set_save_2("double_time.time2", 0);	//战国号角
			me->set_save_2("double_time.time3", 0);
		}
		me->add_save_2("vip_package.doubles",-p);
		send_user(me,"%c%s",':', sprintf("Bạn nhận %d phút nhân đôi kinh nghiệm VIP, hãy tận dụng !\n"
			ESC"Ta biết rồi\nCLOSE\n", p * 30 ));		

		p *= 1800;
	        if ( i+ me->get_game_time()<me->get_double_time())
	        	me->set_double_time(me->get_double_time()+p);
		else
			me->set_double_time(i+ me->get_game_time()+p);		
		send_user( me, "%c%c%c%w%c", 0x51, 1, 1,0001, 0 );
		send_user( me, "%c%c%c%w%w%c", 0x51, 1, 2, 0001, 1, 0 );
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
		"/quest/help"->send_help_tips(me, 3);
		"/sys/task/task"->send_task_intro(me, 1, 1, 1);
			return 1;
    }
	if (arg=="dongbang")
	{
		result = sprintf("Bạn có muốn đóng băng thời gian nhân đôi kinh nghiệm không ? Vào ngày Chủ Nhật 23:59 nếu bạn không giải trừ đóng băng thời gian nhân đôi kinh nghiệm sẽ biến mất !\n");
		result += ESC HIC"Đóng băng thời gian nhân đôi kinh nghiệm\ntuluyen dongbang2\n";     
		send_user( me, "%c%s", ':', result);
			return 1;
    }
	if (arg=="dongbang2")
	{
		i = gone_time( me->get_login_time() );
		if ( i+ me->get_game_time()<me->get_double_time())
		{
			me->set_save_2("double_time.freeze", me->get_double_time() - i - me->get_game_time() );
			send_user(me,"%c%s",':', sprintf("Bạn đã đóng băng %d giây thời gian nhân đôi kinh nghiệm !\n"
			ESC"Ta biết rồi\nCLOSE\n", me->get_double_time() -i -me->get_game_time() ));
			me->set_double_time(0);
			send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
			send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
			"/sys/task/task"->send_task_intro(me, 1, 1, 1);						
		}
			return 1;
    }
	if (arg=="giaidongbang")
	{
		result = sprintf("Bạn có muốn giải trừ đóng băng thời gian nhân đôi kinh nghiệm không ? \n");
		result += ESC HIC"Giải đóng băng thời gian nhân đôi kinh nghiệm\ntuluyen giaidongbang2\n";     
		send_user( me, "%c%s", ':', result);
			return 1;
    }
	if (arg=="giaidongbang2")
	{
		if (me->get_save_2("double_time.freeze")>0)
		{
			i = gone_time( me->get_login_time() );
			if ( i+ me->get_game_time()<me->get_double_time())
				me->set_double_time(me->get_double_time()+me->get_save_2("double_time.freeze"));
			else
				me->set_double_time(i+ me->get_game_time()+me->get_save_2("double_time.freeze"));
			me->set_save_2("double_time.freeze", 0);
			send_user(me,"%c%s",':', sprintf("Bạn đã giải đóng băng thời gian nhân đôi thành công, hiện bạn có %d giây thời gian nhân đôi kinh nghiệm !\n"
			ESC"Ta biết rồi\nCLOSE\n", me->get_double_time() -i -me->get_game_time() ));
			send_user( me, "%c%c%c%w%s", 0x51, 1, 1,0001,"Viện Trợ trò chơi" );
			send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "Thời Gian Nhân Đôi" );
			"/sys/task/task"->send_task_intro(me, 1, 1, 1);			
		}
			return 1;
    }
 
        return 1;
}