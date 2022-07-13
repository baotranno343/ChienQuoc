
private int ItemLevel;                  // 物品等级
private string RealName;		// 物品真实名字

string set_name( string name );
string get_name();
int set_value( int value );

string set_real_name(string name)
{
	return RealName = name;
}

string get_real_name()
{
	if (!RealName) set_real_name(get_name());
	return RealName;
}

// 函数：获取等级属性
int get_item_level() { return ItemLevel; }

// 函数：设置等级属性
int set_item_level( int level ) 
{ 
        string file = get_file_name( this_object() );

        if( level < 1 ) 
        {
                set_value( file->get_value() );
                set_name( file->get_name() );
        }
        else 
        {
                set_value( file->get_value() * ( 100 + level * 20 ) / 100 );
                set_name( sprintf( "%s%+d", file->get_name(), level ) );
        }

        return ItemLevel = level; 
}

// 函数：增添等级属性
int add_item_level( int level ) { return set_item_level( ItemLevel + level ); }
