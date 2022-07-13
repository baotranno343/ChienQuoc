
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <cmd.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数:获取人物造型
int get_char_picid() { return 0950; } 

// 函数:构造处理
void create()
{
        set_name( "Lục Đạo Luân Hồi (Nhân vật tự sát)" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        int status, time, id;
        string result;
        object me = this_object();
        status = who->get("xiannv.status");
        if (who->get_org_name()!="" && who->get_org_name()!=0)
        {
                send_user( who, "%c%c%w%s", ':', 3, 950,
                        sprintf(" %s :\n Ngươi vẫn còn đang ở trong bang phái, không thể tự sát.\n"
                        , me->get_name() ) );
                return;         
        }
//              send_user( who, "%c%c%w%s", ':', 3, 950,
//                      sprintf("%s:\n    你现在还不能自杀.\n"
//                      , me->get_name() ) );
//              return;          
        id = getoid(me);
        result = sprintf(" %s :\n Ngươi muốn làm lại từ đầu không? Ta có thể giúp được ngươi.\n", me->get_name() );
	time = who->get_save("suicide");               
	if (time>0)
	{
		if (time()>time)
		{
			result = sprintf("%s:\n    Ngươi xác định phải tự sát ?\n", me->get_name() );
			result += sprintf(ESC "Ta đã suy nghĩ 1 tuần, ta quyết định tự sát.\ntalk %x# welcome.1\n", id);
			
		}
		else
		{
			time = time - time();
			time /= 60;
			if (time<60)			
				result = sprintf("%s:\n    Người còn %d phút để quyết định, trong đầu của ngươi vẫn còn ý định tự sát à ?\n", me->get_name(), time );
			else
			{
				time /= 60;
				if (time<24) result = sprintf("%s:\n    Người còn %d giờ để quyết định, trong đầu của ngươi vẫn còn ý định tự sát à ?\n", me->get_name(), time );
				else
				{
					time /= 24;
					result = sprintf("%s:\n    Người còn %d ngày để quyết định, trong đầu của ngươi vẫn còn ý định tự sát à ?\n", me->get_name(), time );
				}
			}
		}
		result += sprintf(ESC "Ta quyết định không tự sát nữa.\ntalk %x# welcome.20\n", id);
	}  
	else
	{
		result += sprintf(ESC "Ta muốn làm lại từ đầu, ngươi giúp ta nhé.\ntalk %x# welcome.1\n", id );
	}              
        result += ESC "Ta chọn sai rồi, tạm biệt\nCLOSE\n";
	send_user( who, "%c%c%w%s", ':', 3, 950, result );               
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        object npc, who, *inv, obj;
        int i, flag, size, time;
        string result, name1, name2, id, order;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
                send_user( who, "%c%c%w%s", ':', 3, 950,
                        sprintf("%s:\n    Ngươi nguyện ý tư sát làm lại từ đầu thiệt à ?\n"
                        ESC "Ta quyết định làm lại từ đầu\ntalk %x# welcome.2\n"
                        ESC "Ta vẫn còn chút lo lắng\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;
        case 2:
                send_user( who, "%c%c%w%s", ':', 3, 950,
                        sprintf("%s:\n    Ta khuyên ngươi phải suy nghĩ thật kĩ, ngươi vẫn còn muốn tự sát không ?\n"
                        ESC "Ta đã quyết định, ngươi đừng khuyên ta\ntalk %x# welcome.3\n"
                        ESC "Ta vẫn còn chút lo lắng\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;
        case 3:
        	time = who->get_save("suicide");   
        	if (time==0 )
        	{
        		who->set_save("suicide", time() + 7*24*3600);
        		send_user( who, "%c%s", '!', "Ngươi sẽ có 1 tuần để quyết định có tự sát hay không.");
	                result = sprintf( "%s ngươi nổi lên ý định tự sát!", short_time(time()) );
	                who->log_legend(result);            		
        		return;
        	}
                send_user( who, "%c%s", '!', "Ngươi đã tự sát thành công.");
                who->add_gold_log("Tự sát", 0);
                if( arrayp( who->get_team() ) ) TEAM_CMD->main( me, sprintf( "x %d", who->get_number() ) );
                result = sprintf( "%s Ngươi tự sát!", short_time(time()) );
                who->log_legend(result);         
                who->remove_from_scene();
                who->before_destruct();         
                if (who->get_fam_name()!="" && who->get_fam_name()!=0)
                        "/sys/sys/count"->add_family(who->get_fam_name(), -1);
                if( npc = who->get("soldier") )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                        who->delete("soldier");
                }

                if( arrayp( inv = who->get("zombie") ) && (size = sizeof(inv) ) )
                {                       
                        for( i = 0; i < size; i ++ ) if( inv[i] )
                        {
                                inv[i]->remove_from_scene();
                                destruct(inv[i]);                               
                        }
                        who->delete("zombie");
                }         
                time = gone_time( who->get_login_time() );
                who->set_game_time( who->get_game_time() + time );              
	        if (MAIN_D->get_host_type()==4||MAIN_D->get_host_type()==0||MAIN_D->get_host_type()==1000)
	        {
	                obj = new ("/inh/user/list");
	                id = who->get_id();
	                obj->set_owner(who->get_real_id());
	                if (who->get_real_id()==id ) order = "1";
	                else order = id[<1..<1];
	                obj->delete_save_2(order);
	                obj->save();
	                name1 = obj->get_save_file();
	                name2 = name1[0..<4]+"txt";
	                rename(name1, name2);
	                destruct(obj);
	                
		}                
                // 自杀档案
                db_user_fee( who, sprintf( MAIN_D->get_php_ip()+":80\n"
                        "GET /xq2/delete.php?id=%s&start=%d&end=%d&time=%d&count=%d&region=%d&host=%d&ip=%s\r\n", 
                        rawurlencode( who->get_id() ), who->get_login_time(), who->get_login_time()+time, time, who->get_feetime(), MAIN_D->get_region(), MAIN_D->get_host(), get_ip_name(who) ) );    // 扣费!                
                if (MAIN_D->get_host_type()!=0||MAIN_D->get_host_type()!=1000)
                	db_user_delete(who, who->get_id());             
                destruct(who);          
                break;      
	case 20:                       
		who->set_save("suicide", 0);
		send_user( who, "%c%s", '!', "Ngươi đã huỷ bỏ ý định tự sát.");
		break;
        }
}