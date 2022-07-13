
#define CALL_ITEM_LOG   "gm/callitem.txt"       // 物体调用日志
#define CALL_USER_LOG   "gm/calluser.txt"       // 玩家调用日志

// 函数：字符串->数据类型
mixed atom( string arg )
{
        mixed *m, m1, m2;
        mapping mp;
        object o;
        string s, s1, s2;
        int i, size;

        // 空字串的情况
	if( !arg ) return arg;    // arg = all_trim(arg)

        // 数字的情况
        if( strlen(arg) > 2 && arg[0..1] == "0x" && sscanf( arg, "%x", i ) ) return i;

	if( sscanf( arg, "%d", i ) ) return i;

        // 字符串的情况
	if( sscanf( arg, "\"%s\"", s ) ) return s;

        // 物体的情况
	if( o = find_any_object(arg) ) return o;

	// (: o, s :) 的情况
        if( sscanf( arg, "(:%s,%s:)", s1, s2 ) == 2 )
	{
		m1 = atom(s1);  m2 = atom(s2);
                // if( objectp(m1) && stringp(m2) ) return (: (object)m1, (string)m2 :);
        }

        // ({ m }) 的情况
	if( sscanf( arg, "({%s})", s ) )
	{
		m = explode( s, "," );
		size = sizeof(m);
		if( size && !m[0] ) return ({ });
		for( i = 0; i < size; i ++ ) m[i] = atom( m[i] );
		return m;
	}

        // ([ mp ])
	if( sscanf( arg, "([%s])", s ) )
	{
		mp = ([ ]);
		m = explode( s, "," );
		size = sizeof(m);
		if( size && !m[0] ) return ([ ]);
		for( i = 0; i < size; i ++ ) if( sscanf( m[i], "%s:%s", s1, s2 ) == 2 ) mp[ atom(s1) ] = atom(s2);
		return mp;
	}

	return arg;
}

// 函数：命令处理
int main( object me, string arg )
{
        object obj;
        string str, func, param;
        mixed *Args, result;
        int i, j, size;

        if( !is_gm2(me) && !is_god(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
                notify( "您要调用什么函数？" );
		return 1;
        }

        // “物体->函数(参数)”格式命令的处理
        // 注意，这里最后一个右括号在后面判断
        if( sscanf(arg, "%s->%s(%s", str, func, param) != 3 ) 
        {
                notify( "您要调用什么函数？" );
		return 1;
        }

        // param = all_trim(param);
        if( sizeof(param) == 1 && param[<1] == ')' ) param = "";
        if( sizeof(param) > 1 ) param = param[0..<2];

        if( !( obj = find_any_object(str) ) ) 
        {
                notify( "您找不到这个物体。" );
		return 1;
        }
        if (obj!=me)
        {
        	notify( "您只能修改自己的数据。" );
        	return 1;
        }
        if( obj != me && func[0..2] != "get" ) 
        {
                if( obj->is_user() ) 
                        log_file( CALL_USER_LOG, sprintf( "%s %s(%s) call %s(%s)->%s(%s)\n",
                                short_time(), me->get_name(), me->get_id(), obj->get_name(), obj->get_id(), func, param ) );
                else    log_file( CALL_ITEM_LOG, sprintf( "%s %s(%s) call %s->%s(%s)\n",
                                short_time(), me->get_name(), me->get_id(), obj->get_name(), func, param ) );
        }

        // 转换字符串为相应的数据类型
        Args = ({ });
        for( i = 0, size = sizeof(param); i < size; i ++ ) 
        {
                if( param[i] == ' ' ) continue;
                else if( param[i] == '(' ) 
                {
                        for( j = i, i ++; param[i] != ')' && i < size; i ++ );
                        Args += ({ param[j..i] });
                        for( j = i, i ++; param[i] != ',' && i < size; i ++ );
                }
                else if( param[i] == '\"' ) 
                {
                        for( j = i, i ++; param[i] != '\"' && i < size; i ++ );
                        Args += ({ param[j..i] });
                        for( j = i, i ++; param[i] != ',' && i < size; i ++ );
                }
                else 
                {
                        for( j = i, i ++; param[i] != ',' && i < size; i ++ );
                        Args += ({ param[j..i-1] });
                }
        }

        // 转换参数字串为相应数据类型
        for( i = 0, size = sizeof(Args); i < size; i ++ ) Args[i] = atom( Args[i] );

        Args = ({ func }) + Args;
        result = call_other(obj, Args);

        for( i = 1, size = sizeof(Args); i < size; i ++ ) Args[i] = sprintf( "%O",Args[i] );

        tell_user( me, "%O->%s(%s) = %O", obj, func, implode(Args[1..<1], ", "), result );

        return 1;
}
