#include <ansi.h>
#include <time.h>
#include <effect.h>
#include <skill.h>


int check_revive(object who);
int add_revive(object who,int i);
int check_revive2(object who);
int add_revive2(object who,int i);
int check_revive3(object who);
int add_revive3(object who,int i);
int check_revive4(object who);
int add_revive4(object who,int i);

//检查复活次数
int check_revive(object who)
{
	mixed *mxTmp;
	
	if ( !who->have_title("Z888") )
		return 0;
	mxTmp = localtime(time());
	if ( who->get_save_2("menhlenhchuthanh.day") != mxTmp[TIME_YDAY] )
	{
		who->set_save_2("menhlenhchuthanh.day",mxTmp[TIME_YDAY]);
		who->delete_save_2("camchat.solan");	
	//	send_user( who, "%c%w%s", 0x82, 7401, "");
	//	send_user( who, "%c%c%c", 0xA2, 3, 3);
	}
	return 3-who->get_save_2("camchat.solan");
}
//累计当天复活次数
int add_revive(object who,int i)
{
	int j;
	
	if ( !who->have_title("Z888") )
		return 0;
	j = check_revive(who);
	if ( i > j )
	{
		send_user(who, "%c%s", ';', "Hôm nay đã dùng 3 lần chức năng Cấm chat, không thể sử dụng thêm nữa !");
		return 0;
	}
	j = who->add_save_2("camchat.solan",i);	
//	send_user( who, "%c%w%s", 0x82, 7401, "");
//	send_user( who, "%c%c%c", 0xA2, 3, 3-j);

	return i;	
}
//检查复活次数
int check_revive2(object who)
{
	mixed *mxTmp;
	
	if ( !who->have_title("Z888") )
		return 0;
	mxTmp = localtime(time());
	if ( who->get_save_2("menhlenhchuthanh2.day") != mxTmp[TIME_YDAY] )
	{
		who->set_save_2("menhlenhchuthanh2.day",mxTmp[TIME_YDAY]);
		who->delete_save_2("nhottu.solan");	
	//	send_user( who, "%c%w%s", 0x82, 7401, "");
	//	send_user( who, "%c%c%c", 0xA2, 3, 3);
	}
	return 3-who->get_save_2("nhottu.solan");
}
//累计当天复活次数
int add_revive2(object who,int i)
{
	int j;
	
	if ( !who->have_title("Z888") )
		return 0;
	j = check_revive2(who);
	if ( i > j )
	{
		send_user(who, "%c%s", ';', "Hôm nay đã dùng 3 lần chức năng Nhốt tù, không thể sử dụng thêm nữa !");
		return 0;
	}	
	j = who->add_save_2("nhottu.solan",i);	
//	send_user( who, "%c%w%s", 0x82, 7401, "");
//	send_user( who, "%c%c%c", 0xA2, 3, 3-j);

	return i;	
}
//检查复活次数
int check_revive3(object who)
{
	mixed *mxTmp;
	
	if ( !who->have_title("Z888") )
		return 0;
	mxTmp = localtime(time());
	if ( who->get_save_2("menhlenhchuthanh3.day") != mxTmp[TIME_YDAY] )
	{
		who->set_save_2("menhlenhchuthanh3.day",mxTmp[TIME_YDAY]);
		who->delete_save_2("thongbao.solan");	
	//	send_user( who, "%c%w%s", 0x82, 7401, "");
	//	send_user( who, "%c%c%c", 0xA2, 3, 3);
	}
	return 10-who->get_save_2("thongbao.solan");
}
//累计当天复活次数
int add_revive3(object who,int i)
{
	int j;
	
	if ( !who->have_title("Z888") )
		return 0;
	j = check_revive3(who);
	if ( i > j )
	{
		send_user(who, "%c%s", ';', "Hôm nay đã dùng 10 lần chức năng Thông báo, không thể sử dụng thêm nữa !");
		return 0;
	}	
	j = who->add_save_2("thongbao.solan",i);	
//	send_user( who, "%c%w%s", 0x82, 7401, "");
//	send_user( who, "%c%c%c", 0xA2, 3, 3-j);

	return i;	
}
//检查复活次数
int check_revive4(object who)
{
	mixed *mxTmp;
	
	if ( !who->have_title("Z888") )
		return 0;
	mxTmp = localtime(time());
	if ( who->get_save_2("menhlenhchuthanh4.day") != mxTmp[TIME_YDAY] )
	{
		who->set_save_2("menhlenhchuthanh4.day",mxTmp[TIME_YDAY]);
		who->delete_save_2("huycamchat.solan");	
	//	send_user( who, "%c%w%s", 0x82, 7401, "");
	//	send_user( who, "%c%c%c", 0xA2, 3, 3);
	}
	return 3-who->get_save_2("huycamchat.solan");
}
//累计当天复活次数
int add_revive4(object who,int i)
{
	int j;
	
	if ( !who->have_title("Z888") )
		return 0;
	j = check_revive4(who);
	if ( i > j )
	{
		send_user(who, "%c%s", ';', "Hôm nay đã dùng 3 lần chức năng giải Phong bế kênh Chat, không thể sử dụng thêm nữa !");
		return 0;
	}	
	j = who->add_save_2("huycamchat.solan",i);	
//	send_user( who, "%c%w%s", 0x82, 7401, "");
//	send_user( who, "%c%c%c", 0xA2, 3, 3-j);

	return i;	
}