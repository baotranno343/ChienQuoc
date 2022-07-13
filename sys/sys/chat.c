
private object *Chat = ({ });           // 闲聊玩家(公众、闲聊)
private object *Rumor = ({ });          // 造谣玩家(谣言、传闻)

void add_chat( object who );
void add_rumor( object who );

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
void create() 
{ 
        object *user;
        int i, size;

        if( arrayp( user = users() ) )
                for( i = 0, size = sizeof(user); i < size; i ++ ) 
        {
                add_chat( user[i] );  add_rumor( user[i] );
        }
}

// -------------------------------------------------------------

// 函数：获取闲聊数组
object *get_chat() { Chat -= ({ 0 });  return copy(Chat); }

// 函数：获取谣言数组
object *get_rumor() { Rumor -= ({ 0 });  return copy(Rumor); }

// 函数：增加闲聊对象
void add_chat( object who )
{
        if( objectp(who) && who->get_chat_open() ) Chat = Chat - ({ who, 0 }) + ({ who });
}

// 函数：增加谣言对象
void add_rumor( object who )
{
        if( objectp(who) && who->get_rumor_open() ) Rumor = Rumor - ({ who, 0 }) + ({ who });
}

// 函数：减少闲聊对象
void sub_chat( object who )
{
        if( objectp(who) ) Chat -= ({ who, 0 });
}

// 函数：减少谣言对象
void sub_rumor( object who )
{
        if( objectp(who) ) Rumor -= ({ who, 0 });
}

// -------------------------------------------------------------

// 函数：公众频道
void chat_channel( int id, string chat )
{
        Chat -= ({ 0 });
        if( sizeof(Chat) ) send_user( Chat, "%c%c%d%s", 0x43, 1, id, chat );
}

// 函数：谣言频道
void rumor_channel( int id, string chat )
{
        Rumor -= ({ 0 });
        if( sizeof(Rumor) ) send_user( Rumor, "%c%c%d%s", 0x43, 2, id, chat );
}

// 函数：谣言频道(玩家)
void rumor_player_channel( int id, string chat )
{
        object *user = Rumor - USER_D->get_gm();
        if( sizeof(user) ) send_user( user, "%c%c%d%s", 0x43, 2, id, chat );
}

// 函数：谣言频道(ＧＭ)
void rumor_gm_channel( int id, string chat )
{
        object *user = USER_D->get_gm();
        if( sizeof(user) ) send_user( user, "%c%c%d%s", 0x43, 2, id, chat );
}
//系统频道
void sys_channel( int id, string chat )
{
        Chat -= ({ 0 });
        if( sizeof(Chat) ) send_user( Chat, "%c%c%d%s", 0x43, 10, id, chat );
}

// 函数：VIP频道
void vip_channel( int id, string chat )
{
        Chat -= ({ 0 });
        if( sizeof(Chat) ) send_user( Chat, "%c%c%d%s", 0x43, 9, id, chat );
}
