
#include <npc.h>
#include <city.h>
#include <ansi.h>

inherit OFFICER;

void do_dismiss( string arg );

// 函数：构造处理
void create()
{
        set_name( "武林盟主" );
        NPC_EQUIP_D->init_figure( this_object(), RICH_YOUNG, MALE, 40 );

        set_2( "talk", ([
                "dismiss" : (: do_dismiss :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
        string cmd1 = sprintf( "talk %x# create\n", id );
        string cmd2 = sprintf( "talk %x# dismiss.?\n", id );
        string cmd3 = sprintf( "talk %x# attack\n", id );
        string cmd4 = sprintf( "talk %x# defense\n", id );
        string cmd5 = sprintf( "talk %x# protect\n", id );

        send_user( who, "%c%s", ':', get_name() + "：\n帮派上的事情，找我就可以了。\n" 
                ESC "申请创立帮派。\n" + cmd1 +
                ESC "解散帮派。\n" + cmd2 +
                ESC "帮派宣战。\n" + cmd3 +
                ESC "帮派应战。\n" + cmd4 +
                ESC "帮派安全保护。\n" + cmd5 +
                ESC "离开。\nCLOSE\n" );
}

// 函数：解散帮派
void do_dismiss( string arg )
{
        object city, org, *team, me, who;
        string name, id, *member, cmd;
        int i, size;

        who = this_player();  me = this_object();

        name = who->get_org_name();

        if( !name || name == "" )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n你还没有加入帮派呢！\n"  );
                return;
        }

        if( !objectp( org = CITY_ZHOU->get_2( sprintf("org.%s", name) ) ) )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n没有“" + name + "”这个帮派！\n"  );
                return;
        }
        id = who->get_id();
        if( id != org->get_master_id() && id != org->get_master_id_2() && id != org->get_presbyter_id_1() && id != org->get_presbyter_id_2() )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n你在“" + name + "”中的地位不够！\n"  );
                return;
        }

        if( gone_time( get( sprintf("dismiss#.%s", name) ) ) > 1800 ) delete( sprintf("dismiss.%s", name) );

        if( arrayp( team = get( sprintf("dismiss.%s", name) ) ) )
        {
                if( member_array(id, team) != -1 )
                {
                        send_user( who, "%c%s", ':', me->get_name() + "：\n你已经投票解散“" + name + "”帮派了！\n"  );
                        return;
                }
        }
        else if( id != org->get_master_id() )
        {
                send_user( who, "%c%s", ':', me->get_name() + "：\n只有帮主才能主动提出解散帮派！\n"  );
                return;
        }

        if( arg == "?" )
        {
                cmd = sprintf( "talk %x# dismiss\n", getoid(me) );
                send_user( who, "%c%s", ':', "您确定要解散“" + name + "”吗？\n" 
                        ESC "是的。\n" + cmd +
                        ESC "我再想想……\nCLOSE\n" );
                return;
        }

        if( id == org->get_master_id() )
        {
                set( sprintf("dismiss.%s", name), ({ id }) );
                set( sprintf("dismiss#.%s", name), time() );
        }
        else
        {
                team += ({ id });
                set( sprintf("dismiss.%s", name), team );

                if( stringp( id = org->get_master_id_2() ) && id != "" ) 
                {
                        if( member_array(id, team) == -1 ) return;
                }
                if( stringp( id = org->get_presbyter_id_1() ) && id != "" ) 
                {
                        if( member_array(id, team) == -1 ) return;
                }
                if( stringp( id = org->get_presbyter_id_2() ) && id != "" )
                {
                        if( member_array(id, team) == -1 ) return;
                }
                if( stringp( id = org->get_master_id() ) && id != "" )
                {
                        if( member_array(id, team) == -1 ) return;
                }

                if( city = CITY_D->get_city_object(who) ) city->delete_save_2( sprintf("org.%s", name) );

                member = org->get_all_member();

                for( i = 0, size = sizeof(member); i < size; i ++ )
                {
                        if( who = find_player( member[i] ) )
                        {
                                who->set_org_name("");
                                who->set_org_position(0);
                                who->set_org_title("");
                                who->set_org_time( time() );
                        }
                        else
                        {
                                name = org->get_member_id( to_int( member[i] ) );
                                who = new( USER );
                                who->set_id(name);
                                if( !who->restore() ) 
                                {
                                        destruct(who);
                                }
                                else
                                {
                                        who->set_org_name("");
                                        who->set_org_position(0);
                                        who->set_org_title("");
                                        who->set_org_time( time() );
                                        who->save();
                                        destruct(who);
                                }
                        }
                }

                name = org->get_save_file();

                org->backup();
                org->remove_from_scene();
                destruct(org);

                rm(name);
        }
}
