
#include <ansi.h>
#include <city.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：帮派技能
void do_skill( object who, object me, string arg )
{
        mapping skls;
        string name1, name2, *name, file;
        int id, skill, i, size;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )    // 本帮帮众
        {
                send_user( who, "%c%c%d%c%w%w%s", 0x95, 30, id, who->get_org_position(), 1, 20, me->get_org_name() );

                if( sizeof( skls = me->get_skill_dbase() ) )
                {
                        name = sort_array( keys(skls), 1 );
                        for( i = 0, size = sizeof(name); i < size; i ++ )
                        {
                                skill = to_int( name[i] );
                                file = SKILL->get_skill_file(skill);
                                file = load_object(file) ? file->get_name() : "Kỹ năng vô danh";
                                send_user( who, "%c%c%w%w%d%s", 0x95, 31, skill, me->get_skill(skill), me->get_skill_degree(skill), file );
                        }
                }

                if( skill = me->get_research() )
                {
                        file = SKILL->get_skill_file(skill);
                        file = load_object(file) ? file->get_name() : "Kỹ năng vô danh";
                        send_user( who, "%c%c%w%s", 0x95, 32, skill, file );
                }
        }
}

// 函数：研究技能
void do_research( object who, object me, string arg )
{
        string name1, name2, file, result;
        string cmd1, cmd2, cmd3;
        int id, skill, level, *research, size, i;
        mapping skls;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();
        skls = me->get_researchs();
	research = keys(skls);
	size = sizeof(research);
        if( stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() > ORG_PRESBYTER )    // 本帮官员
        {
                if( sscanf( arg, "%d.%d", skill, level ) != 2 )
                {
                        if( !( skill = to_int(arg) ) )    // 停止研究
                        {
                                me->set_research(0);
                                send_user( who, "%c%c", 0x95, 33 );

                                FAMILY_D->org_channel( name2, 0, sprintf( HIR "%s(%d) ngưng nghiên cứu tất cả kĩ năng !", 
                                        who->get_name(), who->get_number() ) );
                        }
                        else if( load_object( file = SKILL->get_skill_file(skill) ) && (file->is_basic_skill()||file->is_vita_skill()) )    // 研究技能
                        {
                                cmd1 = sprintf("talk %x# research.%d.1\n", id, skill);
                                cmd2 = sprintf("talk %x# research.%d.2\n", id, skill);
                                cmd3 = sprintf("talk %x# research.%d.3\n", id, skill);
                                send_user( who, "%c%s", ':', me->get_name() + "：\nHãy lựa chọn \"" + file->get_name() + "\" tốc độ nghiên cứu\n" 
                                        ESC "Tốc độ bình thường, mỗi giờ 800 độ thuần thục / 24000 lượng, tiêu hao dự trữ 1\n" + cmd1 +
                                        ESC "Tốc độ nhanh, mỗi giờ 1200 độ thuần thục / 48000 lượng, tiêu hao dự trữ 2\n" + cmd2 +
                                        ESC "Tốc độ siêu nhanh, mỗi giờ 1600 độ thuần thục / 96000 lượng, tiêu hao dự trữ 3\n" + cmd3 +
                                        ESC "Ta còn muốn suy nghĩ……\nCLOSE\n" );
                        }
                        return;
                }
                if (level==0)
                {
                	if (skls[skill]>0)
                	{
                		if( load_object( file = SKILL->get_skill_file(skill) ) )
                		{
	                                me->set_researchs(skill, 0);
	                                send_user( who, "%c%c%w", 0x95, 33, skill );
	
	                                FAMILY_D->org_channel( name2, 0, sprintf( HIR "%s(%d) ngưng nghiên cứu %s !", 
	                                        who->get_name(), who->get_number(), file->get_name() ) );                			
					return;	                                       
                		}
                	}
                	send_user( who, "%c%s", '!', "Bang Phái không có nghiên cứu kĩ năng này !" );
                	return;
                }
                // 不研究奇门遁甲和神游
                if (skill==408||skill==409) return;
                // 检查研究力能够支持的技能数
                if (skls[skill]==0&&size>=me->get_science()/5+1)
                {
                	send_user( who, "%c%s", '!', "Bang Phái nghiên cứu lực không đủ nhiều kĩ năng như vậy" );
                	return;
                }
                if( load_object( file = SKILL->get_skill_file(skill) ) && ( file->is_basic_skill()||file->is_vita_skill() ) )    // 研究技能
                {
                	if (level>me->get_grade())
                	{
                		send_user( who, "%c%s", '!', "Bang Phái quy mô không đủ để tăng tốc độ" );
                		return;
                	}
                        me->set_researchs(skill, level);
                        send_user( who, "%c%c%w%s", 0x95, 32, skill, file->get_name() );

                        switch( level )
                        {
                      default : result = "Tốc độ bình thường";  break;
                       case 2 : result = "Tốc độ nhanh";  break;
                       case 3 : result = "Tốc độ siêu nhanh";  break;
                        }
			me->save();
                        FAMILY_D->org_channel( name2, 0, sprintf( HIR "%s(%d) lấy %s bắt đầu nghiên cứu \"%s\"！", 
                                who->get_name(), who->get_number(), result, file->get_name() ) );
                }
        }
}

// 函数：放弃技能
void do_abandon( object who, object me, string arg )
{
        string name1, name2, file, result;
        string cmd1, cmd2, cmd3;
        int id, skill, level;
        mapping skls;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 && who->get_org_position() > ORG_PRESBYTER )    // 本帮官员
        {
                if( sscanf( arg, "%d.%d", skill, level ) != 2 )
                {
                	skill = to_int(arg);
                        if( load_object( file = SKILL->get_skill_file(skill) ) && me->get_skill(skill) && (file->is_basic_skill()||file->is_vita_skill()) )    // 研究技能
                        {
                                cmd1 = sprintf("talk %x# abandon.%d.1\n", id, skill);
                                send_user( who, "%c%s", ':', me->get_name() + "：\n    Bạn xác định muốn buông tha cho \"" + file->get_name() + "\" ? tất cả tiền tài đều không thể trả\n" 
                                        ESC "Ta quyết định buông tha\n" + cmd1 +
                                        ESC "Ta còn muốn suy nghĩ……\nCLOSE\n" );
                        }
                        return;
                }

                if( load_object( file = SKILL->get_skill_file(skill) ) && me->get_skill(skill) && ( file->is_basic_skill()||file->is_vita_skill() ) )    // 研究技能
                {
                	me->delete_skill(skill);
                	send_user( who, "%c%c%w%w%d%s", 0x95, 31, skill, 0, 0, file->get_name() );
                        FAMILY_D->org_channel( name2, 0, sprintf( HIR "%s(%d) buông tha cho Bang Phái kĩ năng \"%s\" !", 
                                who->get_name(), who->get_number(), file->get_name() ) );
                }
        }
}
