
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00999
#define PF_START       "00999"
#define PF_NAME        "Mệnh lệnh chủ thành"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Mệnh lệnh đặc biệt của chủ Vô Song Thành.\n "; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
	int gender,gender1,p,i,z;
	object item;
	string result,cmd1;
	gender = me->get_gender();
	gender1 = me->get_gender() == 1 ? 0 : 1000;
		
		if ( !me->have_title("Z888") ) return 1;
		if ( arg=="" )
		{
		result = sprintf("Đặc quyền Vô Song : \nThưa chủ thành đại nhân tôn kính, ngài có chỉ thị gì? Tuyên bố thông báo mỗi ngày hạn chế 10 lần, bắt giữ tội phạm 1 người và chỉ có thể bắt giam 15 phút, cấm Chat 3 lần và chỉ có thể cấm mỗi lần 15 phút. \n" );
		result += ESC "Tuyên bố thông báo\npf2 00999.thongbao\n";
		result += ESC "Bắt giữ tội phạm\npf2 00999.nhottu\n";
		result += ESC "Cấm Chat\npf2 00999.camchat\n"; 
		result += ESC "Giải trừ cấm chat\npf2 00999.xoacamchat\n"; 
		result += ESC "Hủy bỏ\n";		
		send_user( me, "%c%c%w%s", ':', 3, 5502, result);
                return 1; 
		}
		if ( arg=="thongbao" )
		{
		send_user( me, "%c%c%d%s", '?', 16, 100, "Đặc quyền Vô Song :\n\nXin nhập nội dung bạn muốn gửi (giới hạn 100 chữ):\n" ESC "vstchu @ %s\n" );	
		return 1;
		}
		if ( arg=="nhottu" )
		{
		send_user( me, "%c%c%d%s", '?', 16, 10, "Đặc quyền Vô Song :\n\nXin nhập ID muốn Nhốt tù : \n" ESC "vstchu - %s\n" );	
		return 1;
		}
		if ( arg=="camchat" )
		{
		send_user( me, "%c%c%d%s", '?', 16, 10, "Đặc quyền Vô Song :\n\nXin nhập ID muốn Cấm chat :\n" ESC "vstchu + %s\n" );	
		return 1;
		}
		if ( arg=="xoacamchat" )
		{
		send_user( me, "%c%c%d%s", '?', 16, 10, "Đặc quyền Vô Song :\n\nXin nhập ID muốn Mở chat :\n" ESC "vstchu ? %s\n" );	
		return 1;
		}
 
        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform( object me )
{
        if ( !me->have_title("Z888") )
		{
		send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 0, 0, PF_NAME );
		return ;
		}
		send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
