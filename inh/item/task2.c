
#include <ansi.h>
#include <task.h>

string get_name();
mixed get( string key );
int remove_from_user();
void remove_from_scene();

// 函数：特殊任务物品
int is_thief_item() { return 1; }

// 函数：复位处理
void reset() 
{
        object who;
        string *member, id;
        int flag, i, size,iKind;

        if( gone_time( get("birthday") ) >= 1800 )    // 15 分钟
        {
                if(   ( who = find_player( sprintf("%d", get("task") ) ) )
                &&    ( flag = who->get_quest("thief.flag") )
                &&    ( flag == 2 || flag == 4 )    // 2. 失窃任务(物品)  // 4. 失窃任务(人物)
                &&      who->get_quest("thief.thief") == get_name() )
                {
                	iKind = who->get_quest("thief.flag");
                        who->delete_quest("thief.flag");
                        who->delete_quest("thief.time");
                        who->delete_quest("thief.thief");
                        who->delete_quest("thief.z");
                        who->delete_quest("thief.x");
                        who->delete_quest("thief.y");
                        who->delete_quest("thief.count");

		        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_THIEF,iKind,0,"" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_THIEF,iKind,"" ); 
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_THIEF,"" ); 
                }
                if( remove_from_user() )    // 是否在身上
                {
                        if( ( who = environment() ) && userp(who) )
                                send_user( who, "%c%s", '!', ECHO "Bạn bị mất vật phẩm." );
                }
                else    remove_from_scene();    // 是否在地上

                destruct( this_object() );
        }
        else
        {
                member = get("user");
                for( i = 0, size = sizeof(member); i < size; i ++ )
                        if( !( who = find_player( member[i] ) ) ) member[i] = "";
                if( sizeof( member - ({ "" }) ) < 1 )
                {
                        if(   ( who = find_player( sprintf("%d", get("task") ) ) )
                        &&    ( flag = who->get_quest("thief.flag") )
                        &&    ( flag == 2 || flag == 4 )    // 2. 失窃任务(物品)  // 4. 失窃任务(人物)
                        &&      who->get_quest("thief.thief") == get_name() )
                        {
                        	iKind = who->get_quest("thief.flag");
                                who->delete_quest("thief.flag");
                                who->delete_quest("thief.time");
                                who->delete_quest("thief.thief");
                                who->delete_quest("thief.z");
                                who->delete_quest("thief.x");
                                who->delete_quest("thief.y");
                                who->delete_quest("thief.count");
                                
			        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_THIEF,iKind,0,"" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_THIEF,iKind,"" ); 
				send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_THIEF,"" );                                 
                        }
                        if( remove_from_user() )    // 是否在身上
                        {
                                if( ( who = environment() ) && userp(who) )
                                        send_user( who, "%c%s", '!', ECHO "Bạn bị mất vật phẩm." );
                        }
                        else    remove_from_scene();    // 是否在地上

                        destruct( this_object() );
                }
        }
}
