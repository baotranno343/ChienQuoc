
#include <item.h>

private int LatestCity;                 // 最近去过城市

private static int AttackMode;          // 攻击模式
private int NoGive = 0;                 // 禁止给予
private int NoFly = 0;                  // 禁止瞬移
private int NoTrans = 0;                // 禁止传送
private int NoTeam = 0;                 // 禁止组队
private int NoFriend = 0;               // 禁止交友
private int NoTell = 0;                 // 禁止私聊
private int NoTrade = 0;                // 禁止交易

private int ChatOpen = 1;               // 闲聊开关
private int RumorOpen = 1;              // 谣言开关
private int CityOpen = 1;               // 城市开关
private int OrgOpen = 1;                // 帮派开关
private int FamilyOpen = 1;             // 门派开关
private int SayOpen = 1;                // 说话开关
private int TeamOpen = 1;               // 队伍开关
private int TradeOpen = 1;              // 交易开关

private string IdProtect;               // 密码保护
private int IdLocked;                   // 用户锁定

private int Mode;			// 显示模式
private int Mouse;			// 鼠标模式

private int AttackMove;			// 攻击时的移动模式

private static object Snooper;          // 跟踪对象

private int Immortal;
private string CurWorkDir;
private string CurWorkFile;

int get_login_flag();

// -------------------------------------------------------------

// 函数：获取最近去过城市
int get_latest_city() { return LatestCity; }

// 函数：设置最近去过城市
int set_latest_city( int flag ) 
{ 
        object me, *inv;
        int i, size;

        me = this_object();  inv = all_inventory(me, 0, 0);
        inv = filter_array( inv, (: objectp($1) && $1->get_item_type() == $2 :), ITEM_TYPE_FLY_SEAL );
        for( i = 0, size = sizeof(inv); i < size; i ++ ) send_user( me, "%c%d%c", 0x31, getoid( inv[i] ), 0 );

        return LatestCity = flag; 
}

// -------------------------------------------------------------

// 函数：获取攻击模式
int get_attack_mode() { return AttackMode; }

// 函数：设置攻击模式
int set_attack_mode( int flag ) 
{ 
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 120, flag );
        return AttackMode = flag; 
}

// 函数：获取禁止给予
int get_no_give() { return NoGive; }

// 函数：设置禁止给予
int set_no_give( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 121, flag );
        return NoGive = flag; 
}

// 函数：判断鼠标模式
int get_mouse() { return Mouse; }

// 函数：设置鼠标模式
int set_mouse( int flag ) 
{ 
	flag = range_value(flag, 0, 1);
	if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 143, flag );
	return Mouse = flag; 
}

// 函数：判断攻击时的移动模式
int get_attack_move() { return AttackMove; }

// 函数：设置攻击时的移动模式
int set_attack_move( int flag ) 
{ 
	flag = range_value(flag, 0, 1);
	send_user( this_object(), "%c%c%c", 0x3d, 145, flag );
	return AttackMove = flag; 
}

// 函数：判断显示模式
int get_mode() { return Mode; }

// 函数：设置显示模式
int set_mode( int flag ) 
{ 
	flag = range_value(flag, 0, 1);
	if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 144, flag );
	return Mode = flag; 
}

// 函数：获取禁止瞬移
int get_no_fly() { return NoFly; }

// 函数：设置禁止瞬移
int set_no_fly( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 122, flag );
        return NoFly = flag; 
}

// 函数：获取禁止传送
int get_no_trans() { return NoTrans; }

// 函数：设置禁止传送
int set_no_trans( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 123, flag );
        return NoTrans = flag; 
}

// 函数：获取禁止组队
int get_no_team() { return NoTeam; }

// 函数：设置禁止组队
int set_no_team( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 124, flag );
        return NoTeam = flag; 
}

// 函数：获取禁止交友
int get_no_friend() { return NoFriend; }

// 函数：设置禁止交友
int set_no_friend( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 125, flag );
        return NoFriend = flag; 
}

// 函数：获取禁止私聊
int get_no_tell() { return NoTell; }

// 函数：设置禁止私聊
int set_no_tell( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 126, flag );
        return NoTell = flag; 
}

// 函数：获取禁止交易
int get_no_trade() { return NoTrade; }

// 函数：设置禁止交易
int set_no_trade( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 127, flag );
        return NoTrade = flag; 
}

// 函数：获取说话开关
int get_say_open() { return SayOpen; }

// 函数：设置说话开关
int set_say_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 130, flag );
        return SayOpen = flag; 
}

// 函数：获取闲聊开关
int get_chat_open() { return ChatOpen; }

// 函数：设置闲聊开关
int set_chat_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 131, flag );
        return ChatOpen = flag; 
}

// 函数：获取交易开关
int get_trade_open() { return TradeOpen; }

// 函数：设置交易开关
int set_trade_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 132, flag );
        return TradeOpen = flag; 
}

// 函数：获取城市开关
int get_city_open() { return CityOpen; }

// 函数：设置城市开关
int set_city_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 133, flag );
        return CityOpen = flag; 
}

// 函数：获取门派开关
int get_family_open() { return FamilyOpen; }

// 函数：设置门派开关
int set_family_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 134, flag );
        return FamilyOpen = flag; 
}

// 函数：获取帮派开关
int get_org_open() { return OrgOpen; }

// 函数：设置帮派开关
int set_org_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 135, flag );
        return OrgOpen = flag; 
}

// 函数：获取队伍开关
int get_team_open() { return TeamOpen; }

// 函数：设置队伍开关
int set_team_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 136, flag );
        return TeamOpen = flag; 
}

// 函数：获取谣言开关
int get_rumor_open() { return RumorOpen; }

// 函数：设置谣言开关
int set_rumor_open( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 137, flag );
        return RumorOpen = flag; 
}

// 函数：获取用户锁定
int get_id_locked() { return IdLocked; }

// 函数：设置用户锁定
int set_id_locked( int flag ) 
{ 
        flag = range_value(flag, 0, 1);
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%c", 0x3d, 140, flag );
        return IdLocked = flag; 
}

// 函数：获取密码保护
string get_id_protect() { return IdProtect; }

// 函数：设置密码保护
string set_id_protect( string passwd ) 
{ 
        if( !passwd ) passwd = "";
        if( strlen(passwd) > 200 ) passwd = passwd[0..199];
        if( get_login_flag() > 1 ) send_user( this_object(), "%c%c%s", 0x3d, 141, passwd );
        return IdProtect = passwd; 
}

// -------------------------------------------------------------

// 函数：获取跟踪对象
object get_snooper() { return Snooper; }

// 函数：设置跟踪对象
object set_snooper( object who ) { return Snooper = who; }

// 函数：获取不死标志
int get_immortal() { return Immortal; }

// 函数：设置不死标志
int set_immortal( int flag ) { return Immortal = flag; }

// 函数：获取当前目录
string get_cwd() { return CurWorkDir; }

// 函数：设置当前目录
string set_cwd( string dir ) { return CurWorkDir = dir; }

// 函数：获取当前文件
string get_cwf() { return CurWorkFile; }

// 函数：设置当前文件
string set_cwf( string file ) { return CurWorkFile = file; }
