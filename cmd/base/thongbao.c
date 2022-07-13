#include <ansi.h>
	
int main( object me, string arg )
{
	 if( !is_god(me) ) //Nếu người gõ lệnh không phải là GOD (GM có quyền hạn cao nhất, kiểu như Administrator)
	 {
	  return 1; //Kết thúc
	 }
	 if( !arg ) //Nếu nội dung thông báo trống
	 {
	  notify( "Nội dung thông báo phải có ít nhất 1 ký tự" );
	  return 1; //Kết thúc
	 }
	 send_user( CHAT_D->get_chat(), "%c%s", 0xA3, HIY+arg ); //Thực thi gửi thông báo chữ màu vàng (HIY) với nội dung của giá trị arg
	 return 1; //Kết thúc
}
