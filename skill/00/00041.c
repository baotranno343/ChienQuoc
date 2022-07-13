
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00041
#define PF_NAME        "Truy nã tội phạm"

#define SUB_MP          10

// 函数:获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\nTruy tìm tội phạm của nhiệm vụ Sư Gia.\n"; 
}

// 
void check_target(object me, object npc);

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object npc, *targets;
        string id, result;
        int z, x0, y0, dx, dy;
        int i, mp, size, flag;
        
        flag = 0;
        if (npc=me->get("target"))
        {
        	if ( npc->get("user")==me->get_number() )
                {
        		check_target(me, npc);
        		flag = 1;
        	}
        }
        if (targets=me->get("targets"))
        {
        	targets -= ({ 0 });
        	me->set("targets", targets);
        	size = sizeof(targets);
        	for (i=0;i<size;i++)
        		if ( objectp(targets[i]) && (targets[i]->get("user")==me->get_number()) )
                        {        		        
        			check_target(me, targets[i]);
        			flag = 1;
        		}
        }
        if (flag==0)
        {                
                if(    !stringp( id = me->get_task("robber") ) 
                ||   !( npc = find_char(id) ) || !npc->is_robber() )    // 30 phút钟
                {
                        send_user(me, "%c%s", '!', "Bạn không có nhận nhiệm vụ Sư Gia.");
                        return 1;
                }
                else
                        check_target(me, npc);
        }        
}                

void check_target(object me, object npc)
{
        string id, result;
        int z, x0, y0, dx, dy, x, y;
        int i, mp;
        z = get_z(npc);  x = get_x(npc);  y = get_y(npc);

        if( get_z(me) != z )
        {
                send_user( me, "%c%s", '!', sprintf( "%s không ở trong này.", npc->get_name() ) );
                return ;
        }

        mp = SUB_MP;    // 小心准备 level

        if( me->get_mp() < mp )
        {
                send_user(me, "%c%s", '!', sprintf( "Truy tìm cần %d điểm Pháp Lực.", mp ) );
                return ;
        }

        x0 = get_x(me);  y0 = get_y(me);
        dx = abs(x0 - x);  dy = abs(y0 - y);

        if( dx <= 20 && dy <= 20 )
                result = sprintf( "Xuang quanh bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );
        else if( dx <= 40 && dy <= 40 )
                result = sprintf( "Gần bên cạnh bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );
        else if( dx <= 60 && dy <= 60 )
                result = sprintf( "Rất gần bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );
        else if( dx <= 80 && dy <= 80 )
                result = sprintf( "Ở nơi không xa bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );
        else if( dx <= 100 && dy <= 100 )
                result = sprintf( "Ở nơi rất xa bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );
        else    result = sprintf( "Ở nơi cực xa bạn %s", PF_NO_00031->get_direction(x0, y0, x, y) );

        tell_user( me, "Truy tìm %s tại %s.", npc->get_name(), result );    // write_user

        me->add_mp(-mp);
}

// 函数:获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数:能否使用指令
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
