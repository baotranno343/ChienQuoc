
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00032
#define PF_NAME        "Tra sứ mệnh vật phẩm"

#define TASK_TIME       1800

// 函数:获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\nTruy tìm sứ mệnh vật phẩm ở Tân Thủ Thôn, U Cốc và Thanh Khê.\n"; 
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *task, map, item;
        string result, result2;
        int z, x0, y0, dx, dy, time, i, size;

        if( !arg || arg == "" )
        {
                if( size = sizeof( task = TASK_D->get_task_item() ) )
                {
                        result = "Liệt kê sứ mệnh vật phẩm:\n";
                        for( i = 0; i < size; i ++ )
                        {
                                if( objectp( task[i] ) )
                                {
                                        if( environment( task[i] ) )
                                        {
                                                result2 = sprintf( "%s(Đang tiến hành...)\nCLOSE\n", task[i]->get_name() );
                                        }
                                        else
                                        {
                                                z = get_z( task[i] );
                                                map = get_map_object(z);

                                                if( objectp(map) ) 
                                                        result2 = sprintf( "%s(%s)%s\npf2 00032.%d\n", 
                                                                task[i]->get_name(), map->get_name(), z == get_z(me) ? "√" : "", i + 1 );
                                                else    result2 = "(Dừng hoàn thành)\nCLOSE\n";
                                        }
                                }
                                else    result2 = "(Dừng hoàn thành)\nCLOSE\n";

                                result = sprintf( "%s" ESC "%s", result, result2 );
                        }
                }
                else
                {
                        time = ( time() + TASK_TIME ) / TASK_TIME * TASK_TIME - time();

                        result = "";
                        if( time / 60 ) result += sprintf( " %d phút", time / 60 );
                        result += sprintf( " %d giây", time % 60 );

                        result = sprintf( "Phải đợi %s lúc mới có nhiệm vụ sứ mệnh vật phẩm.\n"
                                ESC "Tiếp tục chờ đợi.\nCLOSE\n", result );
                }

                send_user( me, "%c%c%w%s", ':', 3, 6009,result );
        }
        else if( x = to_int(arg) )
        {
                if( !objectp( item = TASK_D->get_task_item_2(x) ) ) return 1;
                if( environment(item) ) return 1;

                z = get_z(item);  x = get_x(item);  y = get_y(item);
                if( !objectp( map = get_map_object(z) ) ) return 1;

                if( z == get_z(me) )
                {
                        x0 = get_x(me);  y0 = get_y(me);
                        dx = abs(x0 - x);  dy = abs(y0 - y);
                        if( dx <= 50 && dy <= 50 )
                                result = sprintf( "Gần bên cạnh bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        if( dx <= 100 && dy <= 100 )
                                result = sprintf( "Khoảng cách đối diện bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else    result = sprintf( "Khoảng cách khá xa bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                }
                else
                {
                        x0 = get_map_max_x(z) / 2;  y0 = get_map_max_y(z) / 2;
                        dx = abs(x0 - x);  dy = abs(y0 - y);
                        if( dx <= 50 && dy <= 50 )
                                result = sprintf( "%s ở giữa %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        if( dx <= 100 && dy <= 100 )
                                result = sprintf( "%s tương đối gần %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else    result = sprintf( "%s khá xa %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                }
                send_user( me, "%c%c%w%s", ':', 3, 6009,sprintf( "Sứ mệnh vật phẩm " HIY "%s" NOR " hiện tại đang:\n\n%s\n", item->get_name(), result ));
        }

        return 1;
}

// 函数:获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数:能否使用指令
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
