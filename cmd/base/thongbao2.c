#include <ansi.h>
	
int main( object me, string arg )
{
	 if( !is_god(me) )
	 {
	  return 1;
	 }
	 if( !arg )
	 {
	  notify( "Nội dung thông báo phải có ít nhất 1 ký tự" );
	  return 1;
	 }
	 send_user( CHAT_D->get_chat(), "%c%s", 0xA3, HIY+arg );
	 send_user( CHAT_D->get_chat(), "%c%s", 0xA3, HIY+arg );
	 send_user( CHAT_D->get_chat(), "%c%s", 0xA3, HIY+arg );
	 return 1;
}