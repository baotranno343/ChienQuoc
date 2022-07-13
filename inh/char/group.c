
class Group
{
        string Name;                            // 家族名称
        int    Position;                        // 家族辈份
        int    Order;                           // 升级顺序
        string Title;                           // 家族头衔
        string Master;                          // 师父姓名
        string MasterId;                        // 师父标识
        int    Time;                            // 加入时间        
}

private class Group Family = new( class Group );// 门派属性
private class Group Org = new( class Group );   // 帮派属性
private class Group City = new( class Group );  // 城市属性

private static string Leader;                   // 队长对象
private static object BonusMember;              // 带的新手
private static int team_id;                   	// 队伍ID
private static int group_id;                   	// 团队ID

int Contrib;			// 门派贡献
int FamilyType;				// 门派类别
int OrgContrib;				// 帮派贡献

// -------------------------------------------------------------

// 函数：获取门派名称
string get_fam_name() { return Family->Name ? Family->Name : ""; }

// 函数：获取门派辈份
int get_fam_position() { return Family->Position; }

// 函数：获取升级顺序
int get_fam_order() { return Family->Order; }

// 函数：获取门派头衔
string get_fam_title() { return Family->Title ? Family->Title : ""; }

// 函数：获取师父姓名
string get_fam_master() { return Family->Master ? Family->Master : ""; }

// 函数：获取师父标识
string get_fam_master_id() { return Family->MasterId ? Family->MasterId : ""; }

// 函数：获取加入时间
int get_fam_time() { return Family->Time; }

// 函数：获取门派贡献
int get_fam_contribute() { return Contrib; }

// -------------------------------------------------------------

// 函数：设置门派名称
string set_fam_name( string name ) 
{
        if( Family->Name ) FAMILY_D->sub_family( this_object() );

        if( !name || name == "" )
        {
                Family->Name = 0; 
                send_user( this_object(), "%c%c%c", 0x3d, 47, 0 );
        }
        else 
        {
                Family->Name = name; 
                send_user( this_object(), "%c%c%s", 0x3d, 47, name );
                FAMILY_D->add_family( this_object() );
        }
	switch(name)
	{
	case "Đào Hoa Nguyên":
		FamilyType = 1;
		break;
        case "Thục Sơn":
        	FamilyType = 2;
        	break;
        case "Cấm Vệ Quân":
        	FamilyType = 3;
        	break;
        case "Đường Môn":
        	FamilyType = 4;
        	break;
        case "Mao Sơn":
        	FamilyType = 5;
        	break;
        case "Côn Luân":
        	FamilyType = 6;
        	break;
        case "Vân Mộng Cốc":
        	FamilyType = 7;
        	break;		
        default:
        	FamilyType = 0;
        	break;
	}
        return Family->Name;
}

int get_fam_type() {return FamilyType;}

// 函数：设置门派辈份
int set_fam_position( int position ) { return Family->Position = position; }

// 函数：设置升级顺序
int set_fam_order( int order ) { return Family->Order = order; }

// 函数：设置门派贡献
int set_fam_contribute(int value) 
{ 
	object me= this_object();	
        if( me->is_user() &&  me->get_login_flag() >= 3 ) 
                send_user( me, "%c%c%d", 0x3d, 46, value );	
	return Contrib= value ; 
}

// 函数：获取门派头衔
string set_fam_title( string title ) { return Family->Title = title; }

// 函数：设置师父姓名
string set_fam_master( string name ) 
{ 
        if( !name || name == "" )
        {
                Family->Master = 0; 
                send_user( this_object(), "%c%c%c", 0x3d, 48, 0 );
        }
        else 
        {
                Family->Master = name; 
                send_user( this_object(), "%c%c%s", 0x3d, 48, name );
        }

        return Family->Master; 
}

// 函数：设置师父标识
string set_fam_master_id( string id ) { return Family->MasterId = id; }

// 函数：设置加入时间
int set_fam_time( int enter ) { return Family->Time = enter; }

// -------------------------------------------------------------

// 函数：获取帮派名称
string get_org_name() { return Org->Name ? Org->Name : ""; }

// 函数：获取帮派辈份
int get_org_position() { return Org->Position; }

// 函数：获取帮派贡献
int get_org_contrib() { return OrgContrib; }

// 函数：获取升级顺序
int get_org_order() { return Org->Order; }

// 函数：获取帮派头衔
string get_org_title() { return Org->Title ? Org->Title : ""; }

// 函数：获取师父姓名
string get_org_master() { return Org->Master ? Org->Master : ""; }

// 函数：获取师父标识
string get_org_master_id() { return Org->MasterId ? Org->MasterId : ""; }

// 函数：获取加入时间
int get_org_time() { return Org->Time; }

// -------------------------------------------------------------

// 函数：设置帮派名称
string set_org_name( string name ) 
{
        if( Org->Name ) FAMILY_D->sub_org( this_object() );

        if( !name || name == "" )
        {
                Org->Name = 0; 
                send_user( this_object(), "%c%c%c", 0x3d, 49, 0 );
        }
        else 
        {
                Org->Name = name; 
                send_user( this_object(), "%c%c%s", 0x3d, 49, name );
                FAMILY_D->add_org( this_object() );
        }

        return Org->Name;
}

// 函数：设置帮派辈份
int set_org_position( int position ) { return Org->Position = position; }

// 函数：设置帮派贡献
int set_org_contrib( int value ) { return OrgContrib = value; }

// 函数：设置升级顺序
int set_org_order( int order ) { return Org->Order = order; }

// 函数：获取帮派头衔
string set_org_title( string title ) { return Org->Title = title; }

// 函数：设置师父姓名
string set_org_master( string name ) { return Org->Master = name; }

// 函数：设置师父标识
string set_org_master_id( string id ) { return Org->MasterId = id; }

// 函数：设置加入时间
int set_org_time( int enter ) { return Org->Time = enter; }

// -------------------------------------------------------------

// 函数：获取城市名称
string get_city_name() { return City->Name ? City->Name : ""; }

// 函数：获取城市地位
int get_city_position() { return City->Position; }

// 函数：获取升级顺序
int get_city_order() { return City->Order; }

// 函数：获取城市头衔
string get_city_title() { return City->Title ? City->Title : ""; }

// 函数：获取师父姓名
string get_city_master() { return City->Master ? City->Master : ""; }

// 函数：获取师父标识
string get_city_master_id() { return City->MasterId ? City->MasterId : ""; }

// 函数：获取加入时间
int get_city_time() { return City->Time; }

// -------------------------------------------------------------

// 函数：设置城市名称
string set_city_name( string name ) 
{ 
        if( City->Name ) FAMILY_D->sub_city( this_object() );

        if( !name || name == "" )
        {
                City->Name = 0; 
                send_user( this_object(), "%c%c%c", 0x3d, 50, 0 );
        }
        else 
        {
                City->Name = name; 
                send_user( this_object(), "%c%c%s", 0x3d, 50, name );
                FAMILY_D->add_city( this_object() );
        }

        return City->Name;
}

// 函数：设置城市地位
int set_city_position( int position ) { return City->Position = position; }

// 函数：设置升级顺序
int set_city_order( int order ) { return City->Order = order; }

// 函数：获取城市头衔
string set_city_title( string title ) { return City->Title = title; }

// 函数：设置师父姓名
string set_city_master( string name ) { return City->Master = name; }

// 函数：设置师父标识
string set_city_master_id( string id ) { return City->MasterId = id; }

// 函数：设置加入时间
int set_city_time( int enter ) { return City->Time = enter; }

// -------------------------------------------------------------

// 函数：获取队长对象
string get_leader() { return Leader; }

// 函数：设置队长对象
string set_leader( string id ) { return Leader = id; }

// 函数：是否队长对象
int is_leader() { return Leader && sprintf( "%d", this_object()->get_number() ) == Leader; }

// 函数：获取队伍成员
object *get_team() { return Leader ? TEAM_D->get_team(Leader) : 0; }

// 函数：获取队伍id
int get_team_id() { return team_id; }

// 函数：设置队伍id
int set_team_id(int id) { return team_id=id; }

// 函数：获取团队id
int get_group_id() { return group_id; }

// 函数：设置团队id
int set_group_id(int id) { return group_id=id; }

// 函数：获取带的新手
object get_bonus_member() { return BonusMember; }

// 函数：设置带的新手
object set_bonus_member( object who ) { return BonusMember = who; }

// 函数：获取带新手的队长
object get_bonus_leader()
{
        object who;

        if( !Leader || !( who = find_player(Leader) ) ) return 0;    // 找不到队长
        if( who->get_level() < 50 ) return 0;    // 队长等级不够
        if( who->get_bonus_member() != this_object() ) return 0;    // 不是被带新手
        if( this_object()->get_max_level() >= 30 ) return 0;    // 自己等级太高

        return who;
}
