
#include <ansi.h>
#include <task.h>
#include <skill.h>

#define MAX_MEMBER      5              // 队员人数上限
void group_info(object who);
void quest_group(object me,object who);

// 函数:命令处理
int main( object me, string arg )
{
        object *team, *team2, *team3, who,oLeader,oJoiner,map,map1,map2;
        string id, id2, cmd, fam, name, name2;
        int level, z, i, size,tId1,tId2,gId1,gId2;

        if( gone_time( me->get_time("team") ) < 1 )    // 时间限制
                return 1;

        if( !arg ) return 1;

        if( !arg || sscanf( arg, "%s %s",arg, id2 ) != 2  ) return 1;
        if( arg != "follow" && arg != "bet" && arg != "gain" && arg != "give" && !objectp( who = find_player(id2) ) ) return 1;

        switch( arg )
        {
     case "follow":	//队伍跟随
     		if ( me->is_leader() )		//队员跟随队长
     			return ;
     		if ( me->get("team_follow") )	//取消跟随
     		{
     			send_user( me, "%c%w%w%c", 0x81, 0011, 0, EFFECT_GOOD );
     			send_user( me, "%c%c%c", 0xA5, 3, 0 );
     			me->delete("team_follow");
     		}
     		else				//队伍跟随
     		{
     			send_user( me, "%c%w%w%c", 0x81, 0011, -1, EFFECT_GOOD );
     			send_user( me, "%c%c%c", 0xA5, 3, 1 );
     			me->set("team_follow",1);
     		}
     		return ;
     case "cancel" :
     		if( arrayp( team3 = who->get("pending_team") ) )
			who->set( "pending_team", team3 - ({ me, 0 })  );
     		me->set("pending_time", 0);
        	send_user( me, "%c%c%c", 0x59, 1, 0);
        	send_user( who,"%c%s",'!',sprintf("%s cự tuyệt xin vào nhóm của bạn",me->get_name()));
        	return 1;
     case "g@cancel" :
     		me->set("pending_time", 0);
        	send_user( me, "%c%c%c", 0x59, 1, 0);
        	send_user( who,"%c%s",'!',sprintf("%s cự tuyệt lời mời vào nhóm của bạn",me->get_name()));
        	return 1;
     case "+" :
     case "++" :
        	me->set_time( "team", time() );
                if( me->get_no_team() )
                {
                        notify( "Bạn phải lập nhóm" );
                        return 1;
                }
                if( !arrayp( team = me->get_team() ) && me == who )    // 自己组队
                {
                        id = sprintf( "%d", me->get_number() );
                        if ( TEAM_D->new_team(me) != 1 )
                        {
                        	notify( "Lập nhóm thất bại" );
                        	return 1;
                        }
                        me->set_leader(id);
                        if ("/sys/sys/count"->get_new_person())
                        	send_user( me, "%c%c%d%d%c%s", 0x54, 1, me->get_number(), me->get_photo(), me->get_level(), me->get_name() );
                        else
                        	send_user( me, "%c%c%d%d%c%s", 0x54, 1, me->get_number(), me->get_armor_code(), me->get_level(), me->get_name() );
//			send_user( me, "%c%c%d%s", 0x54, 1, me->get_number(), me->get_name() );
                        send_user( me, "%c%c%d%s", 0x43, 7, 0, WHT "Bạn tự mình lập một nhóm." );
			send_user( me, "%c%c%d%w%w", 0x54, 3, me->get_number(), me->get_hp(), me->get_max_hp() );
			send_user( me, "%c%c%d%w%w", 0x54, 4, me->get_number(), me->get_mp(), me->get_max_mp() );
			"/quest/help"->send_help_tips(me, 22);
			"/quest/help"->send_help_tips(me, 43);
			CHAR_CHAR_D->init_loop_perform(me);
                        return 1;
                }

                if( who->get_no_team() )
                {
                        notify( "%s thiết lập cấm tổ đội", who->get_name() );
                        return 1;
                }

                if( !arrayp( team2 = who->get_team() ) && !arrayp(team) )
                {
                        id = sprintf( "%d", me->get_number() );
                        if ( TEAM_D->new_team(me) != 1 )
                        {
                        	notify( "Lập nhóm thất bại" );
                        	return 1;
                        }
                        me->set_leader(id);
                        if ("/sys/sys/count"->get_new_person())
                        	send_user( me, "%c%c%d%d%c%s", 0x54, 1, me->get_number(), me->get_photo(), me->get_level(), me->get_name() );
                        else
                        	send_user( me, "%c%c%d%d%c%s", 0x54, 1, me->get_number(), me->get_armor_code(), me->get_level(), me->get_name() );
//			send_user( me, "%c%c%d%s", 0x54, 1, me->get_number(), me->get_name() );
                        send_user( me, "%c%c%d%s", 0x43, 7, 0, WHT "Bạn tự mình lập một nhóm." );
			send_user( me, "%c%c%d%w%w", 0x54, 3, me->get_number(), me->get_hp(), me->get_max_hp() );
			send_user( me, "%c%c%d%w%w", 0x54, 4, me->get_number(), me->get_mp(), me->get_max_mp() );
			team = me->get_team();
			"/quest/help"->send_help_tips(me, 22);
			"/quest/help"->send_help_tips(me, 43);
			CHAR_CHAR_D->init_loop_perform(me);
                }
                if (arrayp(team) && sizeof(team)==1 && arg=="++")
                {
                	TEAM_D->remove_member( me->get_leader(), me );
                	team = 0;
                }
                if( arrayp(team) )    // 本人有队伍
                {
                        if( !me->is_leader() )
                        {
                                notify( "Bạn không phải đội trưởng" );
                                return 1;
                        }
                        if( member_array(who, team) != -1 )
                        {
                                notify( "%s đã ở trong nhóm rồi", who->get_name() );
                                return 1;
                        }
                        if( arrayp(team2) )
                        {
                        	if( sizeof(team) >= 2 )
                        	{
//	                                notify( "%s在另一支队伍中.", who->get_name() );
					quest_group(me,who);
	                                return 1;                        		
                        	}
                        	if (arg=="+")
	                        {
	                                send_user( me, "%c%c%s", 0x59, 1, sprintf("Gia nhập nhóm mới phải thoát nhóm cũ ra, bạn xác định muốn rời nhóm phải không ?\n"
	                                	ESC "%c\n"ESC"team ++ %d\n", 
	                                	1, who->get_number(), 2) );
	                                return 1;
	                        }                        	

                        }
                        if( sizeof(team) >= MAX_MEMBER )
                        {
                                notify( "Nhóm đã đạt thành viên tối đa" );
                                return 1;
                        }
                        map1 = get_map_object(get_z(me));
                        map2 = get_map_object(get_z(who));
						if ( get_z(me)!=704 && get_z(who)==704 )
						{
						notify( "Đối phương đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(me)==704 && get_z(who)!=704 ) 
						{
						notify( "Bạn đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(me)==704 && get_z(who)==704 ) 
						{
						notify( "Trong Nhà Ngục không thể lập nhóm !" );
	                    return 1;
						}
                        if ( map1->is_changping() || map2->is_changping() )
                        {
                        	if ( map1 != map2 )
                        	{
	                                notify( "Trong Chiến Trường 2 phe đối địch không thể lập nhóm !" );
	                                return 1;
                        	}		
                        	if ( me->can_fight(who) )
                        	{
	                                notify( "Chiến Trường không cho phép lập nhóm cùng địch !" );
	                                return 1;
                        	}	
                        }
                }
                else if( arrayp(team2) )    // 对方有队伍
                {
//                        if( !who->is_leader() )
//                        {
//                                notify( "%s不是队伍的队长.", who->get_name() );
//                                if( who = find_player( who->get_leader() ) )
//                                        printf( ECHO "该队队长:%s(%d).", who->get_name(), who->get_number() );
//                                return 1;
//                        }
	                if( !who->is_leader() && !objectp( who = find_player( who->get_leader() ) ) )
                        {
                                notify( "Tìm không thấy đội trưởng" );
                                return 1;
                        }
                        if( sizeof(team2) >= MAX_MEMBER )
                        {
                                notify( "Đội nhóm thành viên đã đạt cao nhất" );
                                return 1;
                        }
                        map1 = get_map_object(get_z(me));
                        map2 = get_map_object(get_z(who));
						if ( get_z(me)!=704 && get_z(who)==704 )
						{
						notify( "Đối phương đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(me)==704 && get_z(who)!=704 ) 
						{
						notify( "Bạn đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(me)==704 && get_z(who)==704 ) 
						{
						notify( "Trong Nhà Ngục không thể lập nhóm !" );
	                    return 1;
						}
                        if ( map1->is_changping() || map2->is_changping() )
                        {
                        	if ( map1 != map2 )
                        	{
	                                notify( "Trong Chiến Trường 2 phe đối địch không thể lập nhóm !" );
	                                return 1;
                        	}		
                        	if ( me->can_fight(who) )
                        	{
	                                notify( "Chiến Trường không cho phép lập nhóm cùng địch !" );
	                                return 1;
                        	}	
                        }
                }

                if( who->get_no_team() )
                {
                        notify( "%s thiết lập cấm tổ đội", who->get_name() );
                        return 1;
                }
                if (time()- who->get("pending_time")<60)
                {
//                        notify( "%s忙碌中.", who->get_name() );
//                        return 1;                	
                }

                if( arrayp( team3 = who->get("pending_team") ) && member_array(me, team3) != -1 )    // 回应
                {
			if( me->is_leader() && !who->is_leader() )
			{
				oLeader = me;
				oJoiner = who;
			}
			else
			{
				oLeader = who;
				oJoiner = me;
			}
			map1 = get_map_object(get_z(oLeader));
			map2 = get_map_object(get_z(oJoiner));
						if ( get_z(oLeader)!=704 && get_z(oJoiner)==704 )
						{
						notify( "Đối phương đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(oLeader)==704 && get_z(oJoiner)!=704 ) 
						{
						notify( "Bạn đang ở trong Nhà Ngục !" );
	                    return 1;
						}
						else if ( get_z(me)==704 && get_z(who)==704 ) 
						{
						notify( "Trong Nhà Ngục không thể lập nhóm !" );
	                    return 1;
						}
                        if ( map1->is_changping() || map2->is_changping() )
                        {
                        	if ( map1 != map2 )
                        	{
	                                notify( "Trong Chiến Trường 2 phe đối địch không được lập nhóm" );
	                                return 1;
                        	}		
                        	if ( oLeader->can_fight(oJoiner) )
                        	{
	                                notify( "Chiến Trường không cho phép lập nhóm cùng địch !" );
	                                return 1;
                        	}	
                        }	
                        id = sprintf( "%d", oLeader->get_number() );
                        if ( TEAM_D->add_member(id, oJoiner) != 1 )
                        	return 1;
                        oJoiner->set_leader(id);
			oJoiner->set("templeader", 0);
                        z = get_z(oJoiner);
                        team = oLeader->get_team();  size = sizeof(team);
                        if ("/sys/sys/count"->get_new_person())
                        	send_user( team - ({ oJoiner }), "%c%c%d%d%c%s", 0x54, 2, oJoiner->get_number(), oJoiner->get_photo(), oJoiner->get_level(), oJoiner->get_name() );
                        else
                        	send_user( team - ({ oJoiner }), "%c%c%d%d%c%s", 0x54, 2, oJoiner->get_number(), oJoiner->get_armor_code(), oJoiner->get_level(), oJoiner->get_name() );
                        for( i = 0; i < size; i ++ ) if( team[i] )
                        {
                        	if ("/sys/sys/count"->get_new_person())
                                	send_user( oJoiner, "%c%c%d%d%c%s", 0x54, team[i] == oLeader ? 1 : 2, team[i]->get_number(), team[i]->get_photo(), team[i]->get_level(), team[i]->get_name() );
                                else
                                	send_user( oJoiner, "%c%c%d%d%c%s", 0x54, team[i] == oLeader ? 1 : 2, team[i]->get_number(), team[i]->get_armor_code(), team[i]->get_level(), team[i]->get_name() );
                                if( team[i] != oJoiner && get_z( team[i] ) == z )    // 更新队员坐标
                                {
                                        send_user( oJoiner, "%c%c%d%w%w", 0x54, 10, team[i]->get_number(), get_x( team[i] ), get_y( team[i] ) );
					send_user( oJoiner, "%c%c%d%w%w", 0x54, 3, team[i]->get_number(), team[i]->get_hp(), team[i]->get_max_hp() );
					send_user( oJoiner, "%c%c%d%w%w", 0x54, 4, team[i]->get_number(), team[i]->get_mp(), team[i]->get_max_mp() );
					send_user( team[i], "%c%c%d%w%w", 0x54, 3, oJoiner->get_number(), oJoiner->get_hp(), oJoiner->get_max_hp() );
					send_user( team[i], "%c%c%d%w%w", 0x54, 4, oJoiner->get_number(), oJoiner->get_mp(), oJoiner->get_max_mp() );
				}
				else
				{
					send_user( oJoiner, "%c%c%d%w%w", 0x54, 3, team[i]->get_number(), team[i]->get_hp(), team[i]->get_max_hp() );
					send_user( oJoiner, "%c%c%d%w%w", 0x54, 4, team[i]->get_number(), team[i]->get_mp(), team[i]->get_max_mp() );						
				}
				
                        }                                

                        send_user( team, "%c%c%d%s", 0x43, 7, 0, sprintf( WHT "%s(%d) ở %s mời bạn gia nhập nhóm",
                                oJoiner->get_name(), oJoiner->get_number(), oLeader->get_name() ) );

                        team -= ({ oJoiner });
                        team = filter_array( team, (: $1 && get_z($1) == $2 :), z );    // 更新队员坐标
                        send_user( team, "%c%c%d%w%w", 0x54, 10, oJoiner->get_number(), get_x(oJoiner), get_y(oJoiner) );
                        oJoiner->add_to_scene( get_z(oJoiner), get_x(oJoiner), get_y(oJoiner), get_d(oJoiner) );    // 重进场景
                        me->to_front_eachother(who);

                        if( arrayp( team3 = who->get("pending_team") ) && sizeof( team3 -= ({ 0 }) ) > 0 )
                                send_user( team3, "%c%d%w%c%c%c", 0x6f, getoid(who), 9001, 1, OVER_BODY, PF_STOP );
                        who->delete( "pending_team" );
                        who->set("pending_time", 0);
                        me->set("pending_time", 0);
			"/quest/help"->send_help_tips(oJoiner, 22);
			"/quest/help"->send_help_tips(oJoiner, 43);
                        return 1;
                }
                else    // 邀请
                {
                        if( arrayp(team) || !arrayp(team2) )
                        {
                                name = me->get_name();
                                name = replace_string(name, "#", "＃");      
                                name2 = who->get_name();                  	
                                name2 = replace_string(name2, "#", "＃");      
                                printf( ECHO "Bạn mời %s gia nhập vào nhóm", name2 );
                                write_user( who, ECHO " %s ( %d ) mời bạn gia nhập nhóm.", name, me->get_number() );

                                send_user( who, "%c", 0x54 );
                                who->set("pending_time", time());
                                send_user( who, "%c%c%d%s", 0x4d, 0xff, me->get_number(),
                                        sprintf( " %s ( %d ) mời bạn gia nhập nhóm.", name, me->get_number() ) );
                                send_user( who, "%c%d%w%c%c%c", 0x6f, getoid(me), 9001, 1, OVER_BODY, PF_LOOP );
                                fam = me->get_fam_name();
                                if (fam==""||!fam) fam = "Vô Môn Phái.";

                                send_user( who, "%c%c%s", 0x59, 1, sprintf("%d cấp %s của nhóm %s mời bạn gia nhập vào nhóm, bạn có đồng ý không?\n"
                                	ESC "%c\n"ESC"team + %d\n"
                                	ESC "%c\n"ESC"team cancel %d\n",
                                	me->get_level(), fam, name, 1, me->get_number(), 2,me->get_number()) );
                        }
                        else
                        {
                                name = me->get_name();
                                name = replace_string(name, "#", "＃");                              	
                                name2 = who->get_name();                  	
                                name2 = replace_string(name2, "#", "＃");                           	
                                printf( ECHO "Bạn xin gia nhập vào nhóm của %s ",name2 );
                                write_user( who, ECHO "%s(%d) xin gia nhập vào nhóm của bạn", name, me->get_number() );

                                send_user( who, "%c", 0x54 );
                                send_user( who, "%c%c%d%s", 0x4d, 0xff, me->get_number(),
                                        sprintf( "%s(%d) xin gia nhập vào nhóm của bạn", name, me->get_number() ) );
                                send_user( who, "%c%d%w%c%c%c", 0x6f, getoid(me), 9001, 1, OVER_BODY, PF_LOOP );
                                fam = me->get_fam_name();
                                if (fam==""||!fam) fam = "Vô Môn Phái.";
//				send_user(who,"%c%c%w%s",':',3,0,sprintf("%s申请加入你的队伍，你同意吗？\n"ESC"同意\nteam + %d\n"ESC"拒绝\nteam refuse %d\n",me->get_name(),me->get_number(),me->get_number()));
                                name = me->get_name();
                                name = replace_string(name, "#", "＃");
                                send_user( who, "%c%c%s", 0x59, 1, sprintf("%d cấp %s của %s xin gia nhập vào nhóm của bạn, đồng ý không ?\n"
                                	ESC "%c\n"ESC"team + %d\n"
                                	ESC "%c\n"ESC"team cancel %d\n",
                                	me->get_level(), fam, name, 1, me->get_number(), 2,me->get_number()) );

                        }
                        if( arrayp( team3 = me->get("pending_team") ) )
                                me->set( "pending_team", team3 - ({ who, 0 }) + ({ who }) );
                        else    me->set( "pending_team", ({ who }) );

                        return 1;
                }
                return 1;

     case "x" :
                me->set_time( "team", time() );
                if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                if( !me->is_leader() )    // 不是队长，脱离队伍
                {
                        if( me != who )
                        {
                                notify( "Bạn không phải đội trưởng, chỉ có thể tự mình rời nhóm" );
                                return 1;
                        }
                        send_user( team, "%c%c%d%s", 0x43, 7, 0, sprintf( WHT "%s(%d) đã rời nhóm", me->get_name(), me->get_number() ) );
                        TEAM_D->remove_member( who->get_leader(), who );
                        who->add_to_scene( get_z(who), get_x(who), get_y(who), get_d(who) );    // 重进场景
                        return 1;
                }
                if( sprintf( "%d", me->get_number() ) != who->get_leader() )
                {
                        notify( "%s không ở trong nhóm", who->get_name() );
                        return 1;
                }
                if( me != who )
                        send_user( team, "%c%c%d%s", 0x43, 7, 0, sprintf( WHT "Trưởng nhóm %s ( %d ) khai trừ %s ( %d )ra khỏi nhóm .",
                                me->get_name(), me->get_number(), who->get_name(), who->get_number() ) );
                else    send_user( team, "%c%c%d%s", 0x43, 7, 0, sprintf( WHT "Trưởng nhóm %s ( %d )đã rời khỏi nhóm.", me->get_name(), me->get_number() ) );
                TEAM_D->remove_member( who->get_leader(), who );
                who->add_to_scene( get_z(who), get_x(who), get_y(who), get_d(who) );    // 重进场景
                return 1;

     case "-" :
                if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                if( !me->is_leader() )    // 不是队长，脱离队伍
                {
                        if( me != who )
                        {
                                notify( "Bạn không phải đội trưởng, chỉ có thể tự mình rời nhóm" );
                                return 1;
                        }
                        send_user( me, "%c%s", ':', "Bạn muốn rời khỏi nhóm phải không ?\n"
                                ESC "Chấp nhận.\nteam x " + sprintf( "%d", me->get_number() ) + "\n"
                                ESC "Ta suy nghĩ lại……\nCLOSE\n" );
                        return 1;
                }
                if( sprintf( "%d", me->get_number() ) != who->get_leader() )
                {
                        notify( "%s hiện tại không ở trong nhóm", who->get_name() );
                        return 1;
                }
                cmd = sprintf( "team x %d\n", who->get_number() );
                if( me != who )
                        send_user( me, "%c%s", ':', "Bạn muốn khai trừ " + who->get_name() + " ra khỏi nhóm phải không ？\n"
                                ESC "Chấp nhận.\n" + cmd +
                                ESC "Ta suy nghĩ lại……\nCLOSE\n" );
                else    send_user( me, "%c%s", ':', "Trưởng nhóm có chắc rằng muốn rời khỏi nhóm không?\n"
                                ESC "Chấp nhận.\n" + cmd +
                                ESC "Ta suy nghĩ lại……\nCLOSE\n" );
                return 1;

     case "=" :
                if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                if( !me->is_leader() )
                {
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
                if( me == who )
                {
                        notify( "Bạn đã là đội trưởng" );
                        return 1;
                }
                if( sprintf( "%d", me->get_number() ) != who->get_leader() )
                {
                        notify( "%s hiện tại không ở trong nhóm", who->get_name() );
                        return 1;
                }
                send_user( team, "%c%c%d%s", 0x43, 7, 0, sprintf( WHT "Trưởng nhóm %s(%d) đã nhường chức cho %s(%d) ",
                        me->get_name(), me->get_number(), who->get_name(), who->get_number() ) );
                TEAM_D->change_leader(me, who);

                return 1;
	case "gain" :
		if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                if( !me->is_leader() )
                {
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
                TEAM_D->change_gain_mode(me,me->get_leader(),id2);
                return 1;                
	case "give" :
		if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                
		TEAM_D->leader_give_item(me,id2);
		return;
	case "bet":
		if( !arrayp( team = me->get_team() ) )
                {
                        notify( "Bạn hiện tại không ở trong nhóm" );
                        return 1;
                }
                TEAM_D->add_bet(me,id2);
                return ;
	 case "refuse" :
	 	if( arrayp( team3 = who->get("pending_team") ) )
                                who->set( "pending_team", team3 - ({ me, 0 })  );
		write_user( who, ECHO "%s(%d) cự tuyệt xin nhập nhóm của bạn", me->get_name(), me->get_number() );
		send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(who), 9001, 1, OVER_BODY, PF_STOP );
		return;
	case "g+":	//组团邀请
		if ( is_god(me) )
			quest_group(me,who);
		break;
	case "g@+":
		if ( !me->is_leader() )
		{
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
                if ( !stringp(id=who->get_leader()) || !objectp(who=find_char(id)) )
		{
                        notify( "Đối phương không ở trong nhóm" );
                        return 1;
                }
		gId1 = me->get_group_id();
		gId2 = who->get_group_id();
		if ( gId1 && gId2 )
		{
                        notify( "Hai bên đã ở trong nhóm" );
                        return 1;
                }
		tId1 = me->get_team_id();
		tId2 = who->get_team_id();
		if ( who->get("pending_group") != tId1 )
		{
                        notify( "Đối phương không muốn cùng ngươi lập nhóm" );
                        return 1;
        	}
        	who->delete("pending_group");   
                if ( gId1 && !gId2 )	//接受对方申请
		{
			if ( TEAM_D->get_group_amount(gId1) >= 8 )
	                {
	                 	send_user(me,"%c%s",'!',"Trước mặt đội nhóm đã đạt cao nhất, không thể gia nhập nhóm lại !");	
	                }
			TEAM_D->add_group_team(gId1,tId2);
                }
                else if ( !gId1 && gId2 )	//加入对方
		{
			if ( TEAM_D->get_group_amount(gId2) >= 8 )
	                {
	                 	send_user(me,"%c%s",'!',"Đội nhóm của đối phương đã đạt cao nhất, gia nhập thất bại !");	
	                }
			TEAM_D->add_group_team(gId2,tId1);
                }
                else if ( !gId1 && !gId2 )	//新建团队
		{
			gId2 = TEAM_D->add_group_team(0,tId2);
			TEAM_D->add_group_team(gId2,tId1);
                }
		send_user(me,"%c%s",'!',who->get_name()+" của đội ngũ cùng bạn kết thành đồng đội !");	
		send_user(who,"%c%s",'!',me->get_name()+" của đội ngũ cùng bạn kết thành đồng đội !");	
		break;
	case "gInfo":
		group_info(me);
		break;
	case "gl":
		if ( !me->is_leader() )
		{
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
                if ( !me->get_group_id() )
		{
                        notify( "Bạn không ở trong nhóm" );
                        return 1;
                }
		TEAM_D->leave_group(me->get_team_id());
		send_user(me,"%c%c",0xA2,8);
		notify( "Bạn rời khỏi nhóm" );
		break;	            
	case "g-":
		if ( !me->is_leader() )
		{
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
                if ( !(gId1=me->get_group_id()) )
		{
                        notify( "Bạn không ở trong nhóm" );
                        return 1;
                }
                if ( TEAM_D->get_first_group_team(gId1) != me->get_team_id() )
		{
                        notify( "Bạn không phải đội trưởng" );
                        return 1;
                }
		TEAM_D->leave_group(who->get_team_id());
		send_user(me,"%c%c",0xA2,8);
		notify( "Bạn đem "+who->get_name()+" khai trừ ra khỏi nhóm" );
		break;	
        }

                
        return 1;
}
//发送团队信息给团队成员
void group_info(object who)
{
	int gId,*nTeam,i,size,m,n,tId;
	object *nObj,player;
	string cName;
	
	gId = who->get_group_id();
	if ( !gId )
		return ;
	nTeam = TEAM_D->get_group_member(gId);
	if ( !nTeam )
		return ;
	for(i=0,size=sizeof(nTeam);i<size;i++)
	{
		tId = nTeam[i];
		nObj = TEAM_D->get_team_by_id(tId);
		nObj -= ({0});
		for(m=0,n=sizeof(nObj);m<n;m++)
			if ( objectp(player=nObj[m]) )
			{
				if ( i==0 && m==0 )
					cName = player->get_name()+"(Đội trưởng)";
				else
					cName = player->get_name();
				send_user(who,"%c%c%c%d%d%s",
					0xA2,7,i+1,player->get_number(),player->get_level(),cName);
			}
	}
}
//组建邀请
void quest_group(object me,object who)
{
	int tId1,tId2,gId1,gId2;
	
	if ( !me->is_leader() )
	{
                notify( "Bạn không phải đội trưởng" );
                return ;
        }
	gId1 = me->get_group_id();
	if ( TEAM_D->get_group_amount(gId1) >= 8 )
        {
         	send_user(me,"%c%s",'!',"Trước mặt đội nhóm đã đạt cao nhất, không thể gia nhập nhóm lại !");	
        }
        if( !who->is_leader() && !objectp( who = find_player( who->get_leader() ) ) )
        {
                notify( "Tìm không thấy đội trưởng" );
                return ;
        }
	tId1 = me->get_team_id();
	tId2 = who->get_team_id();
	gId2 = who->get_group_id();
	if ( gId1 && gId2 )
	{
                notify( "Đối phương đã có nhóm, không thể mời gia nhập" );
                return ;
        }
        printf( ECHO "Bạn mời %s của đội nhóm kết thành đồng đội", who->get_name() );
	me->set("pending_group",tId2);
        send_user( who, "%c%c%s", 0x59, 1, sprintf("%s của đội nhóm muốn cùng bạn kết thành đồng đội, đồng ý không ?\n"
        	ESC "%c\n"ESC"team g@+ %d\n"
        	ESC "%c\n"ESC"team g@cancel %d\n",
        	me->get_name(),1,me->get_number(),2,who->get_number() ) );	
	
	
}