
#define CHECK           INI_DIR "check.ini"     // 检查设置文件

private string *PassIP = ({ });
private string *BanIP = ({ });
private string *BanId = ({ });
private string *BanName = ({ });
private string *GM1_IP = ({ });
private string *GM2_IP = ({ });
private string *GM3_IP = ({ });
private string *GOD_IP = ({ });

private void load_check();

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
private void create() { load_check(); }

// -------------------------------------------------------------

// 函数：读取检查设置
private void load_check()
{
        string *line, lemma, content;
        int i, size;

        // 读出检查设置
        line = explode( read_file( CHECK ), "\n" );
        if (sizeof(line)==0) return;

        // 历遍检查设置
        for( i = 0, size = sizeof(line); i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( !sscanf( line[i], "%s : %s", lemma, content ) ) 
                {
                        log_file( ERROR, sprintf( "错误: " CHECK " 第 %d 行检查定义错.\n", i + 1 ) );
                        continue;
                }
                switch( lemma ) 
                {
                        case "+IP" : PassIP += ({ content });  break;
                        case "-IP" : BanIP += ({ content });  break;
                        case "-ID" : BanId += ({ content });  break;
                        case "-NAME" : BanName += ({ content });  break;
                        case "GM1" : GM1_IP += ({ content });  break;
                        case "GM2" : GM2_IP += ({ content });  break;
                        case "GM3" : GM3_IP += ({ content });  break;
                        case "GOD" : GOD_IP += ({ content });  break;
                }
        }
}

// 函数：保存检查设置
void save_check()
{
        string *check, file = "";
        int i, size;

        check = sort_array(PassIP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "+IP : " + check[i] + "\n";

        check = sort_array(BanIP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "-IP : " + check[i] + "\n";

        check = sort_array(BanId, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "-ID : " + check[i] + "\n";

        check = sort_array(BanName, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "-NAME : " + check[i] + "\n";
                
        check = sort_array(GM1_IP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "GM1 : " + check[i] + "\n";

        check = sort_array(GM2_IP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "GM2 : " + check[i] + "\n";

        check = sort_array(GM3_IP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "GM3 : " + check[i] + "\n";

        check = sort_array(GOD_IP, 1);
        for( i = 0, size = sizeof(check); i < size; i ++ )
                file += "GOD : " + check[i] + "\n";
                
        rm( CHECK );
        write_file( CHECK, file );
}

// -------------------------------------------------------------

// 函数：显示开放ＩＰ
string *get_passed_ip() { return copy(PassIP); }

// 函数：显示封闭ＩＰ
string *get_banned_ip() { return copy(BanIP); }

// 函数：显示禁止标识
string *get_banned_id() { return copy(BanId); }

// 函数：显示禁止名称
string *get_banned_name() { return copy(BanName); }

// -------------------------------------------------------------

// 函数：是否开放ＩＰ
int is_passed_ip( string ip )
{
        int len, i, size;

        for( i = 0, size = sizeof(PassIP); i < size; i ++ ) 
        {
//              if( sizeof( regexp( ({ ip }), PassIP[i] ) ) ) return 1;
                if( PassIP[i] == ip ) return 1;
                len = strlen( PassIP[i] ) + 1;
                if( strlen(ip) > len && PassIP[i] + "." == ip[0..len - 1] ) return 1;
        }

        return 0;
}

// 函数：是否封闭ＩＰ
int is_banned_ip( string ip )
{
        int len, i, size;

        for( i = 0, size = sizeof(BanIP); i < size; i ++ ) 
        {
//              if( sizeof( regexp( ({ ip }), BanIP[i] ) ) ) return 1;
                if( BanIP[i] == ip ) return 1;
                len = strlen( BanIP[i] ) + 1;
                if( strlen(ip) > len && BanIP[i] + "." == ip[0..len - 1] ) return 1;
        }

        return 0;
}

// 函数：是否禁止标识
int is_banned_id( string id )
{
        int i, size = sizeof(BanId);

        for( i = 0; i < size; i ++ ) 
        {
                if( BanId[i][<1] == '*' ) 
                {
                        if( sscanf( BanId[i][0..<2] + "%*s", id ) ) return 1;
                }
                else    if( BanId[i] == id ) return 1;
        }
        return 0;
}

// 函数：是否禁止名称
int is_banned_name( string name )
{
        int i, size = sizeof(BanName);

        for( i = 0; i < size; i ++ ) if( BanName[i] == name ) return 1;
        return 0;
}

// -------------------------------------------------------------

// 函数：增加开放ＩＰ
void add_passed_ip( string ip )
{
        PassIP += ({ ip });
        save_check();
}

// 函数：增加封闭ＩＰ
void add_banned_ip( string ip )
{
        BanIP += ({ ip });
        save_check();
}

// 函数：增加禁止标识
void add_banned_id( string id )
{
        BanId += ({ id });
        save_check();
}

// 函数：增加禁止名称
void add_banned_name( string name )
{
        BanName += ({ name });
        save_check();
}

// -------------------------------------------------------------

// 函数：删除开放ＩＰ
void remove_passed_ip( string ip )
{
        PassIP -= ({ ip });
        save_check();
}

// 函数：删除封闭ＩＰ
void remove_banned_ip( string ip )
{
        BanIP -= ({ ip });
        save_check();
}

// 函数：删除禁止标识
void remove_banned_id( string id )
{
        BanId -= ({ id });
        save_check();
}

// 函数：删除禁止名称
void remove_banned_name( string name )
{
        BanName -= ({ name });
        save_check();
}

// -------------------------------------------------------------

// 函数：是否合法标识
int is_legal_id( object me, string id )
{
        int i, len;

        if( !stringp(id) || id == "" )
        {
                send_user( me, "%c%s", '!', "Tài khoản phải từ 3~20 ký tự" );
                return 0;
        }

        len = strlen(id);

        if( len < 3 || len > 20 )    // 3～20字符
        {
                send_user( me, "%c%s", '!', "Tài khoản phải từ 3~20 ký tự" );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }

        id = strlwr(id);

        for( i = 0; i < len; i ++ )    // 取值范围：a～z, 中划线，下划线，0～9
        {
                if(     ( id[i] < 'a' || id[i] > 'z' ) 
                &&      id[i] != '-' && id[i] != '_'
                &&      ( id[i] < '0' || id[i] > '9' ) ) 
                {
                        send_user( me, "%c%s", '!', "您的帐号只能使用字母、数字、中划线或下划线." );
                        send_user(me, "%c%c", 0xff, 0x11); 
                        return 0;
                }
        }

        if(     ( id[0] < 'a' || id[0] > 'z' ) 
        &&      ( id[0] < '0' || id[0] > '9' ) )    // 以字母数字开始
        {
                send_user( me, "%c%s", '!', "您的帐号必须以字母或者数字开始." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
        if(     ( id[<1] < 'a' || id[<1] > 'z' ) 
        &&      ( id[<1] < '0' || id[<1] > '9' ) )    // 以字母数字结束
        {
                send_user( me, "%c%s", '!', "您的帐号必须以字母或者数字结束." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
/*
        if(     strstr( id, "--" ) >= 0
        ||      strstr( id, "__" ) >= 0
        ||      strchr( id, '-' ) >= 0 && strchr( id, '_' ) >= 0 )    // 过多下划线
        {
                send_user( me, "%c%s", '!', "您的帐号使用了过多的中划线或下划线." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
*/
        return 1;
}

// 函数：是否合法密码
int is_legal_passwd( object me, string passwd )
{
        int len = strlen(passwd);

        if( !stringp(passwd) || passwd == "" )
        {
                send_user( me, "%c%s", '!', "Mật khẩu phải từ 5~14 ký tự" );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }

        if( len < 5 || len > 14 )    // 5～14字符
        {
                send_user( me, "%c%s", '!', "Mật khẩu phải từ 5~14 ký tự" );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }

        return 1;
}

// 函数：是否合法名字
int is_legal_name( object me, string name )
{
        int len = strlen(name), exist, i, size;
		string *line, *data;

		if( !stringp(name) || name == "" )
        {
                send_user( me, "%c%s", '!', "Tên nhân vật phải từ 2 tới 12 ký tự." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
        if( !is_chinese(name) )
        {
                send_user( me, "%c%s", '!', "Tên nhân vật không hợp lệ." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
        if( len < 2 || len > 12 )
        {
                send_user( me, "%c%s", '!', "Tên nhân vật phải từ 2 tới 12 ký tự." );
                send_user(me, "%c%c", 0xff, 0x11); 
                return 0;
        }
		line = explode(read_file("tennhanvat.txt"), "\n");
		for (i = 0, size = sizeof(line); i < size; i++) 
		{
			data = explode(line[i], " ");
			if (name == data[0]) 
			{
            exist = 1;
			break;
			}
		}
		if (exist >= 1) {
				send_user( me, "%c%s", '!', "Tên nhân vật này đã tồn tại." );
                send_user(me, "%c%c", 0xff, 0x11);
				return 0;
		}
		else {
		ghi_file("tennhanvat.txt",sprintf("%s 1\n",name));				
        }

        return 1;
}

// 函数：是否合法帮派名
int is_legal_org( object me, string name )
{
        int len = strlen(name);

        if( !stringp(name) || name == "" )
        {
                send_user( me, "%c%s", '!', "Tên Bang phái phải từ 2 tới 10 ký tự." );
                return 0;
        }
        if( !is_chinese(name) )
        {
                send_user( me, "%c%s", '!', "Tên không hợp lệ." );
                return 0;
        }
        if( len < 2 || len > 10 )
        {
                send_user( me, "%c%s", '!', "Tên Bang phái phải từ 2 tới 10 ký tự." );
                return 0;
        }

        return 1;
}

// 函数：是否合法摊档名
int is_legal_store( object me, string name )
{
        int i, len;

        if( !stringp(name) )
        {
                send_user( me, "%c%s", '!', "Tên cửa hàng không hợp lệ!" );
                return 0;
        }

        for( i = 0, len = strlen(name); i < len; i ++ )    // 禁止：逗号、引号
        {
                if( name[i] == ',' || name[i] == '\'' || name[i] == '\"' )
                {
                        send_user( me, "%c%s", '!', "Tên cửa hàng có chứa từ ngữ cấm!" );
                        return 0;
                }
        }

        return 1;
}
//限制GM的登陆IP
int check_gm_ip(string ip,int flag)
{
	int i,size,len;
	string *nTmp;
		
	if ( flag == 1 )
		nTmp = GM1_IP;
	else if ( flag == 2 )
		nTmp = GM2_IP;	 
	else if ( flag == 3 )
		nTmp = GM3_IP;	 
	else if ( flag == 4 )
		nTmp = GOD_IP;			
	else 
		return 0;
	size = sizeof(nTmp);
	if ( !size )
		return 1;
	for( i = 0; i < size; i ++ ) 
        {
                if( nTmp[i] == ip ) return 1;
                len = strlen( nTmp[i] ) + 1;
                if( strlen(ip) > len && nTmp[i] + "." == ip[0..len - 1] ) return 1;
        }
        return 0;
}