
private mapping mpFamily = ([ ]);       // 同门玩家
private mapping mpCity = ([ ]);         // 同城玩家
private mapping mpOrg = ([ ]);          // 同帮玩家

void add_family( object who ); 
void add_city( object who ); 
void add_org( object who ); 

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
                add_family( user[i] );  add_city( user[i] );  add_org( user[i] );
        }
}

// -------------------------------------------------------------

// 函数：获取所有门派
mapping get_all_family() { return copy(mpFamily); }

// 函数：获取所有城市
mapping get_all_city() { return copy(mpCity); }

// 函数：获取所有帮派
mapping get_all_org() { return copy(mpOrg); }

// -------------------------------------------------------------

// 函数：获取门派玩家
object *get_family( string name ) 
{ 
        if( undefinedp( mpFamily[name] ) || !arrayp( mpFamily[name] ) ) return ({ });
        if( sizeof( mpFamily[name] ) ) mpFamily[name] -= ({ 0 });
        return copy( mpFamily[name] ); 
}

// 函数：获取城市玩家
object *get_city( string name ) 
{ 
        if( undefinedp( mpCity[name] ) || !arrayp( mpCity[name] ) ) return ({ });
        if( sizeof( mpCity[name] ) ) mpCity[name] -= ({ 0 });
        return copy( mpCity[name] ); 
}

// 函数：获取帮派玩家
object *get_org( string name ) 
{ 
        if( undefinedp( mpOrg[name] ) || !arrayp( mpOrg[name] ) ) return ({ });
        if( sizeof( mpOrg[name] ) ) mpOrg[name] -= ({ 0 });
        return copy( mpOrg[name] ); 
}

// 函数：增加门派玩家
void add_family( object who ) 
{
        string name;

        if(     objectp(who) && userp(who) 
        &&      stringp( name = who->get_fam_name() ) && name != ""  )
        {
                if( undefinedp( mpFamily[name] ) || !arrayp( mpFamily[name] ) ) mpFamily[name] = ({ who });
                else if( member_array( who, mpFamily[name] ) == -1 ) mpFamily[name] += ({ who });
        }
}

// 函数：增加城市玩家
void add_city( object who ) 
{
        string name;

        if(     objectp(who) && userp(who) 
        &&      stringp( name = who->get_city_name() ) && name != "" )
        {
                if( undefinedp( mpCity[name] ) || !arrayp( mpCity[name] ) ) mpCity[name] = ({ who });
                else if( member_array( who, mpCity[name] ) == -1 ) mpCity[name] += ({ who });
        }
}

// 函数：增加帮派玩家
void add_org( object who ) 
{
        string name;

        if(     objectp(who) && userp(who) 
        &&      stringp( name = who->get_org_name() ) && name != "" && (who->get_org_position()>0) )
        {
                if( undefinedp( mpOrg[name] ) || !arrayp( mpOrg[name] ) ) mpOrg[name] = ({ who });
                else if( member_array( who, mpOrg[name] ) == -1 ) mpOrg[name] += ({ who });
        }
}

// 函数：减少门派玩家
void sub_family( object who ) 
{
        string name;

        if(    !objectp(who) || !( name = who->get_fam_name() )
        ||      undefinedp( mpFamily[name] ) || !arrayp( mpFamily[name] ) ) return;

        if( sizeof( mpFamily[name] ) ) mpFamily[name] -= ({ who, 0 });
        if( !sizeof( mpFamily[name] ) ) map_delete( mpFamily, name );
}

// 函数：减少城市玩家
void sub_city( object who ) 
{
        string name;

        if(    !objectp(who) || !( name = who->get_city_name() )
        ||      undefinedp( mpCity[name] ) || !arrayp( mpCity[name] ) ) return;

        if( sizeof( mpCity[name] ) ) mpCity[name] -= ({ who, 0 });
        if( !sizeof( mpCity[name] ) ) map_delete( mpCity, name );
}

// 函数：减少帮派玩家
void sub_org( object who ) 
{
        string name;

        if(    !objectp(who) || !( name = who->get_org_name() )
        ||      undefinedp( mpOrg[name] ) || !arrayp( mpOrg[name] ) ) return;

        if( sizeof( mpOrg[name] ) ) mpOrg[name] -= ({ who, 0 });
        if( !sizeof( mpOrg[name] ) ) map_delete( mpOrg, name );
}

// -------------------------------------------------------------

// 函数：城市频道
void city_channel( string name, int id, string chat )
{
        if( undefinedp( mpCity[name] ) || !arrayp( mpCity[name] ) ) return;
        if( sizeof( mpCity[name] ) ) mpCity[name] -= ({ 0 });
        if( sizeof( mpCity[name] ) ) send_user( mpCity[name], "%c%c%d%s", 0x43, 3, id, chat );
}

// 函数：帮派频道
void org_channel( string name, int id, string chat )
{
        if( undefinedp( mpOrg[name] ) || !arrayp( mpOrg[name] ) ) return;
        if( sizeof( mpOrg[name] ) ) mpOrg[name] -= ({ 0 });
        if( sizeof( mpOrg[name] ) ) send_user( mpOrg[name], "%c%c%d%s", 0x43, 4, id, chat );
}

// 函数：门派频道
void family_channel( string name, int id, string chat )
{
        if( undefinedp( mpFamily[name] ) || !arrayp( mpFamily[name] ) ) return;
        if( sizeof( mpFamily[name] ) ) mpFamily[name] -= ({ 0 });
        if( sizeof( mpFamily[name] ) ) send_user( mpFamily[name], "%c%c%d%s", 0x43, 5, id, chat );
}
