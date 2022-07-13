
#define ADVICE_LOG      "advice.txt"

// 函数:命令处理
int main( object me, string arg )
{
        object mailbox;
        string who;
        int id;

        if( !arg )
        {
                mailbox = new(MAILBOX);
                mailbox->set_owner( me->get_id() );

                if( mailbox->check_mails() )
                {
                        mailbox->read_mail(me, 1);
                        mailbox->discard_mail(1);
                }

                destruct(mailbox);

                return 1;
        }
        if (time()<me->get_save("nomail"))
        {
        	notify( "你现在无法发信." );
        	return 1;
        }

        if( gone_time( me->get_time("mail") ) < 1 )
        {
                me->set_time( "mail", time() );
                notify( "请勿频繁发送邮件." );
                return 1;
        }
        me->set_time( "mail", time() );
        if( sscanf( arg, ">>%s %d %s", who, id, arg ) )    // GM 专用
        {
                if( is_player(me) ) 
                {
                        notify( "您没有足够的权限." );
        		return 1;
                }

                arg = replace_string(arg, "\\n", "\n" );        
                if( !MAILBOX->sys_mail(who, id, arg) )
                {
                        notify( "信件发送失败!" );
        		return 1;
                }
                printf("信件发送成功.");
                return 1;
        }
        else
        if( sscanf( arg, ">%s %s", who, arg ) )    // GM 专用
        {
                if( is_player(me) ) 
                {
                        notify( "您没有足够的权限." );
        		return 1;
                }

                arg = replace_string(arg, "\\n", "\n" );
        
                mailbox = new(MAILBOX);
                mailbox->set_owner( me->get_id() );
                if( !mailbox->send_mail_2(me, who, arg) )
                {
                        destruct(mailbox);

                        notify( "信件发送失败!" );
        		return 1;
                }
                printf("信件发送成功.");

                destruct(mailbox);

                return 1;
        }
        else if( sscanf( arg, "%d %s", id, arg ) ) 
        {
                arg = replace_string(arg, "\\n", "\n" );
                if( strlen(arg)>250 ) 
                {
                        notify( "您的信件太长了." );
        		return 1;
                }                
                arg = replace_string(arg, "%", "％" );
                if( id == 0 )    // 给 GM 提建议
                {
                        log_file( ADVICE_LOG, sprintf( @LONG
%s(%d)-%s %s
%s

LONG
, me->get_name(), me->get_number(), me->get_id(), short_time(), arg ) );
			notify( "您的问题我们已经收到.感谢您提供宝贵的建议." );
                        return 1;
                }

                mailbox = new(MAILBOX);
                mailbox->set_owner( me->get_id() );
                mailbox->send_mail(me, id, arg);

                destruct(mailbox);

                return 1;
        }

        return 1;
}
