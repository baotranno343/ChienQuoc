
// 函数：命令处理
int main( object me, string arg )
{
        mapping skls;
        object who = me;
        string *name, file;
        int skill, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( who = find_any_char(arg) ) ) 
        {
                notify( "您无法找到这个人。" );
		return 1;
        }

        if( !sizeof( skls = who->get_skill_dbase() ) )
        {
                tell_user( me, who->get_name() + "不会任何技能。" );
		return 1;
        }
        
        name = sort_array( keys(skls), 1 );
        tell_user( me, who->get_name() + "学会的技能：" );
        for( i = 0, size = sizeof(name); i < size; i ++ )
        {
                skill = to_int( name[i] );
                file = SKILL->get_skill_file(skill);
                file = load_object(file) ? file->get_name() : "－－－－";
                tell_user( me, "%s %-12s %3d/%5d", name[i], file, who->get_skill(skill), who->get_skill_degree(skill) );
        }

        return 1;
}
