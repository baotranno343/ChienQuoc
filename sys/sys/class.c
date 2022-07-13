
#define CLASS_LOG       "gm/class.txt"          // 权限等级日志

#define GM_INI          INI_DIR "gm.ini"        // ＧＭ名单文件
#define GM2_INI          INI_DIR "gm2.ini"        // ＧＭ2名单文件
#define GM3_INI          INI_DIR "gm3.ini"        // ＧＭ2名单文件
#define GOD_INI         INI_DIR "god.ini"       // 大神名单文件

#define GM3_CLASS                "(gm3)"

string *GmList = ({ });
string *GodList = ({ });
string *Gm2List = ({ });
string *Gm3List = ({ });

private void load_class();

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
private void create() { load_class(); }

// 函数：读取大神名单
private void load_class()
{
        string *line, result;
        int i, size;

        // 读出ＧＭ名单
        line = explode( read_file( GM_INI ), "\n" );

        // 历遍ＧＭ名单
        for( i = 0, size = sizeof(line); i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
                GmList += ({ line[i] });
        }
        // 读出ＧＭ2名单
        result = read_file( GM2_INI );
        if (result !=0 && result !="")
        {
	        line = explode( result , "\n" );	
	        // 历遍ＧＭ2名单
	        for( i = 0, size = sizeof(line); i < size; i ++ ) 
	        {
	                if( line[i][0] == '#' || line[i] == "" ) continue;
	                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
	                Gm2List += ({ line[i] });
	        }
	}	    
        // 读出ＧＭ2名单
        result = read_file( GM3_INI );
        if (result !=0 && result !="")
        {
	        line = explode( result , "\n" );	
	        // 历遍ＧＭ2名单
	        for( i = 0, size = sizeof(line); i < size; i ++ ) 
	        {
	                if( line[i][0] == '#' || line[i] == "" ) continue;
	                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
	                Gm3List += ({ line[i] });
	        }
	}	   
        // 读出大神名单
        line = explode( read_file( GOD_INI ), "\n" );

        // 历遍大神名单
        for( i = 0, size = sizeof(line); i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( line[i][<1] <= ' ' ) line[i] = line[i][0..<2];    // UNIX 格式
                GodList += ({ line[i] });
        }
}

// 函数：获取ＧＭ名单
string *get_gmlist() { return copy(GmList); }

// 函数：获取ＧＭ2名单
string *get_gm2list() { return copy(Gm2List); }

// 函数：获取ＧＭ3名单
string *get_gm3list() { return copy(Gm3List); }

// 函数：获取大神名单
string *get_godlist() { return copy(GodList); }

// 函数：判断是否玩家
int is_player( mixed who )
{
        string id;

        if( objectp(who) ) id = who->get_real_id();
        else if( stringp(who) ) id = who;
        else return 1;

        // 查等级名单表
        return member_array(id, GodList) == -1 && member_array(id, GmList) == -1 && member_array(id, Gm2List) == -1&& member_array(id, Gm3List) == -1;
}

// 函数：判断是否ＧＭ
int is_gm( mixed who )
{
        string id;

        if( objectp(who) ) id = who->get_real_id();
        else if( stringp(who) ) id = who;
        else return 0;

        // 查ＧＭ名单表
        return member_array(id, GmList) != -1;
}

// 函数：判断是否ＧＭ
int is_gm2( mixed who )
{
        string id;

        if( objectp(who) ) id = who->get_real_id();
        else if( stringp(who) ) id = who;
        else return 0;

        // 查ＧＭ名单表
        return member_array(id, Gm2List) != -1;
}

// 函数：判断是否ＧＭ
int is_gm3( mixed who )
{
        string id;

        if( objectp(who) ) id = who->get_real_id();
        else if( stringp(who) ) id = who;
        else return 0;

        // 查ＧＭ名单表
        return member_array(id, Gm3List) != -1;
}

// 函数：判断是否大神
int is_god( mixed who )
{
        string id;

        if( objectp(who) ) id = who->get_real_id();
        else if( stringp(who) ) id = who;
        else return 0;

        // 查大神名单表
        return member_array(id, GodList) != -1;
}

// 函数：设置用户等级
int set_class( object me, object who, string new_class )
{
        string id, old_class, list;
        int i, size;

        // 行为许可判断
        if( !this_player(1) ) return 0;
        
        if( !userp(me) || !userp(who) ) return 0;

	if( !is_god(me) ) return 0;

        old_class = get_class(who);
        if( new_class == old_class ) return 0;

        // 整理名单资料
        id = who->get_id();  GmList -= ({ id });  Gm2List -= ({ id }); GodList -= ({ id });
        if( new_class == GM_CLASS ) GmList += ({ id });
        else if( new_class == GM2_CLASS ) Gm2List += ({ id });
        else if( new_class == GM3_CLASS ) Gm3List += ({ id });
        else if( new_class == GOD_CLASS ) GodList += ({ id });

        // 写入名单文件
        list = "";  size = sizeof(GmList);
        for( i = 0; i < size; i ++ ) list += GmList[i] + "\n";
        rm( GM_INI );  write_file( GM_INI, list );
        list = "";  size = sizeof(Gm2List);
        for( i = 0; i < size; i ++ ) list += Gm2List[i] + "\n";
        rm( GM2_INI );  write_file( GM2_INI, list );
        list = "";  size = sizeof(Gm3List);
        for( i = 0; i < size; i ++ ) list += Gm3List[i] + "\n";
        rm( GM3_INI );  write_file( GM3_INI, list );
        list = "";  size = sizeof(GodList);
        for( i = 0; i < size; i ++ ) list += GodList[i] + "\n";
        rm( GOD_INI );  write_file( GOD_INI, list );

        // 记录设置日记
        log_file( CLASS_LOG, sprintf( "%s %s Account %s : %s -> %s\n",
                short_time(), this_player(1)->get_id(), id, old_class, new_class ) );

        return 1;
}
