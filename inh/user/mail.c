
// 邮箱存储物品

private string Owner;                   // 邮箱主人标识
private mapping *Mails = ({ });         // 邮件数据资料

int save();
int restore();
int receive_mail( mapping mail );

// -------------------------------------------------------------

// 函数:设置用户标识
int set_owner( string id )
{
        Owner = id;
        if( !user_exist(Owner) ) return 0;
        return restore();
}

// 函数:获取邮件件数
int check_mails() { return sizeof(Mails); }

// 函数:发送邮件
int send_mail( object me, int number, string text )
{
        mapping mail;
        object who, mailbox;
        string id, name;
        
        if( !text ) return 0;
        
        if( who = find_player( sprintf( "%d", number ) ) ) 
                id = who->get_id();
        else if( !( id = me->get_friend_id(number) ) && !( id = me->get_mail_id(number) ) )
        {
                send_user(me, "%c%s", '!', sprintf(" %d không phải bạn tốt, không thể gửi thư！", number) );
                return 0;
        }
        if( !user_exist(id) ) return 0;
        name = me->get_name();
	name = replace_string(name, "#", "＃");
        mail = ([
                "from" : me->get_number(),
                "name" : name,
                "id"   : me->get_id(),
                "time" : short_time(),
                "text" : text
        ]);

        mailbox = new(MAILBOX);
        mailbox->set_owner(id);
        mailbox->receive_mail(mail);

        destruct(mailbox);
	if (strlen(text)>84) text = text[0..83];
        if( who = find_player( sprintf( "%d", number ) ) ) 
        {
                send_user( who, "%c", 0x4d );
                send_user( who, "%c%c%d%s", 0x4d, 0xff, me->get_number(), 
                        sprintf( "%s(%d):\n%s", me->get_name(), me->get_number(), text ) );
        }

        return 1;
}

// 函数:发送邮件(GM 专用)
int send_mail_2( object me, string id, string text )
{
        mapping mail;
        object mailbox;
        
        if( !id ) return 0;
        if( !text ) return 0;
        
        if( !user_exist(id) ) return 0;

        mail = ([
                "from" : me->get_number(),
                "name" : me->get_name(),
                "id"   : me->get_id(),
                "time" : short_time(),
                "text" : text
        ]);

        mailbox = new(MAILBOX);
        mailbox->set_owner(id);
        mailbox->receive_mail(mail);

        destruct(mailbox);

        return 1;
}
//Hệ thống邮件
int sys_mail( string id,int number, string text )
{
        mapping mail;
        object who, mailbox;
        

        if( !user_exist(id) ) return 0;

        mail = ([
                "from" : 0,
                "name" : "Hệ thống",
                "id"   : "110",
                "time" : short_time(),
                "text" : text
        ]);

        mailbox = new(MAILBOX);
        mailbox->set_owner(id);
        mailbox->receive_mail(mail);

        destruct(mailbox);
        if (strlen(text)>84) text = text[0..83];

        if( who = find_player( sprintf( "%d", number ) ) ) 
        {
//              send_user( who, "%c", 0x4d );//Hệ thống邮件不用这个
                send_user( who, "%c%c%d%s", 0x4d, 0xff, 0, 
                        sprintf( "%s(%d):\n%s", "Hệ thống", 110, text ) );               
        }

        return 1;
}

//Hệ thống邮件
int sys_mail2( string id, int number, string name, string text )
{
        mapping mail;
        object who, mailbox;
        
        if( !user_exist(id) ) return 0;

        mail = ([
                "from" : 0,
                "name" : name,
                "id"   : "160",
                "time" : short_time(),
                "text" : text
        ]);
        mailbox = new(MAILBOX);
        mailbox->set_owner(id);
        mailbox->receive_mail(mail);

        destruct(mailbox);
        if (strlen(text)>84) text = text[0..83];
        if( who = find_player( sprintf( "%d", number ) ) ) 
        {	
                send_user( who, "%c", 0x4d );
                send_user( who, "%c%c%d%s", 0x4d, 0xff, 0, 
                        sprintf( "%s(%d):\n%s", name, 160, text ) );
        }

        return 1;
}

// 函数:接收邮件
int receive_mail( mapping mail )
{
        if( !arrayp(Mails) ) Mails = ({ mail });
        else Mails += ({ mail });
        return save();
}

// 函数:阅读邮件
int read_mail( object me, int num )
{
	
        if( !arrayp(Mails) || num < 1 || num > sizeof(Mails) ) return 0;    	
        num --;
        
        me->set_mail_id( Mails[num]["from"], Mails[num]["id"] );    // 记录发信人
        send_user( me, "%c%c%d%s", 0x4d, sizeof(Mails) > 1, Mails[num]["from"], 
                sprintf( "%19s%-12s%s", Mails[num]["time"], Mails[num]["name"], Mails[num]["text"] ) );
        return 1;
}

// 函数:抛弃邮件
int discard_mail( int num )
{
        if( !arrayp(Mails) || num < 1 || num > sizeof(Mails) ) return 0;
        num --;
        if( sizeof(Mails) <= 1 ) Mails = ({ });
        else if( !num ) Mails = Mails[ num + 1 .. <1 ];
        else Mails = Mails[ 0..num - 1 ] + Mails[ num + 1 .. <1 ];
        return save();
}

// -------------------------------------------------------------

// 函数:取存盘文件名
string get_save_file()
{
        if( !Owner || strlen(Owner) < 3 ) return 0;
        return sprintf( "data/%c/%c/%c/%s/mail" SAVE_EXTENSION, Owner[0], Owner[1], Owner[2], Owner );
}

// 函数:保存物体资料
int save()
{
        string file = get_save_file();
        if( !stringp(file) ) return 0;
        return save_object(file);
}

// 函数:载入物体资料
int restore()
{
        string file = get_save_file();
        if( !stringp(file) ) return 0;
        return restore_object(file);
}

//重启时检查邮件
int check_mails2(object who)
{
	int i,num,pos = 0;
	num = sizeof(Mails);
	for(i=0;i<num;i++)
	{
		if(Mails[i]["from"] == 0)
		{
			send_user( who, "%c%c%d%s", 0x4d, 0xff, 0, 
                        	sprintf( "%s(%s):\n%s", Mails[i]["name"], Mails[i]["id"],Mails[i]["text"] ) ); 
		}
		else
		{
			pos = 1;
		}
	}
	return pos;
}