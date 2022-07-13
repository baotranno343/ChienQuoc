//用来设置游戏giờ间，供某些活动测试用
#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{
	int year,mon,day,hour,min,sec;
	string tmp;
	
        if( !is_gm2(me) && !is_god(me) ) 
        {
                notify( "Bạn không đủ quyền hạn." );
		return 1;
        }
        if ( !arg )
        {
        	tell_user(me,"Thời gian trò chơi hoạt động:%s",short_time(get_party_time()));
        	tell_user(me,"Thiết lập:/set_party_time Năm-Tháng-Ngày giờ:phút:giây");
        	return 1;	
        }
	if ( sscanf(arg,"%d-%d-%d %d:%d:%d",year,mon,day,hour,min,sec) != 6 )
	{
		send_user(me,"%c%s",'!',"Sai cú pháp");
        	tell_user(me,"Thời gian trò chơi hoạt động:%s",short_time(get_party_time()));
        	tell_user(me,"Thiết lập:/set_party_time Năm-Tháng-Ngày giờ:phút:giây");
		return 1;
	}
	tell_user(me,"Thiết lập thời gian trò chơi hoạt động là:%s",short_time(set_party_time(year,mon,day,hour,min,sec)));
	return 1;
	
}