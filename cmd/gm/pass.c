
// 函数：命令处理
int main( object me, string arg )
{
        string *ip, site, result;
        int i, size;

        if( me != this_player(1) || is_player(me) ) 
        {
                notify( "Không đủ quyền lực" );
		return 1;
        }

        if( !arg )
        {
                ip = CHECK_D->get_passed_ip();
                result = "Hãy nhập ID:\n";
                for( i = 0, size = sizeof(ip); i < size; i ++ ) result += ip[i] + "\n";
                tell_user( me, result );
        }
        else if( sscanf( arg, "+ %s", site ) == 1 ) 
        {
                if( site[<1] == '*' || site[<1] == '?' || site[<1] == '+' )
                {
                        notify( "不能开放以 *, +, ? 结尾的ＩＰ。" );
	        	return 1;
                }
                else 
                {
                        CHECK_D->add_passed_ip(site);
                        tell_user( me, "IP này đã mở" );
                }
        }
        else if( sscanf( arg, "- %s", site ) == 1 ) 
        {
                CHECK_D->remove_passed_ip(site);
                tell_user( me, "Huỷ bỏ mở ra IP này" );
        }

        return 1;
}
