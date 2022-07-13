
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00031
#define PF_NAME        "Tra sứ mệnh nhân vật"

#define TASK_TIME       1800

// 函数:获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\nTruy tìm sứ mệnh nhân vật ở Tân Thủ Thôn, U Cốc và Thanh Khê.\n"; 
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *task, map;
        string result, result2;
        int z, x0, y0, dx, dy, time, i, size;

        if( !arg || arg == "" )
        {
                if( size = sizeof( task = TASK_D->get_task_npc() ) )
                {
                        result = "Liệt kê sứ mệnh nhân vật, đội nhóm hãy hoàn thành:\n";
                        for( i = 0; i < size; i ++ )
                        {
                                if( objectp( task[i] ) )
                                {
                                        z = get_z( task[i] );
                                        map = get_map_object(z);

                                        if( objectp(map) ) 
                                                result2 = sprintf( "%s(%s)%s\npf2 00031.%d\n", 
                                                        task[i]->get_name(), map->get_name(), z == get_z(me) ? "√" : "", i + 1 );
                                        else    result2 = "(Dừng hoàn thành)\nCLOSE\n";
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

                        result = sprintf( "Phải đợi %s lúc mới có nhiệm vụ sứ mệnh nhân vật.\n"
                                ESC "Tiếp tục chờ đợi.\nCLOSE\n", result );
                }

                send_user( me, "%c%c%w%s", ':', 3, 5501, result );
        }
        else if( x = to_int(arg) )
        {
                if( !objectp( who = TASK_D->get_task_npc_2(x) ) ) return 1;

                z = get_z(who);  x = get_x(who);  y = get_y(who);
                if( !objectp( map = get_map_object(z) ) ) return 1;

                if( z == get_z(me) )
                {
                        x0 = get_x(me);  y0 = get_y(me);
                        dx = abs(x0 - x);  dy = abs(y0 - y);

                        if( dx <= 20 && dy <= 20 )
                                result = sprintf( "Xuang quanh bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 40 && dy <= 40 )
                                result = sprintf( "Gần bên cạnh bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 60 && dy <= 60 )
                                result = sprintf( "Rất gần bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 80 && dy <= 80 )
                                result = sprintf( "Ở nơi không xa bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 100 && dy <= 100 )
                                result = sprintf( "Ở nơi rất xa bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                        else    result = sprintf( "Ở nơi cực xa bạn %s.", PF_NO_00031->get_direction(x0, y0, x, y) );
                }
                else
                {
                        x0 = get_map_max_x(z) / 2;  y0 = get_map_max_y(z) / 2;
                        dx = abs(x0 - x);  dy = abs(y0 - y);

                        if( dx <= 20 && dy <= 20 )
                                result = sprintf( "%s xung quanh giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 40 && dy <= 40 )
                                result = sprintf( "%s phụ cận giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 60 && dy <= 60 )
                                result = sprintf( "Khoảng cách %s rất gần giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 80 && dy <= 80 )
                                result = sprintf( "Khoảng cách %s không xa giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else if( dx <= 100 && dy <= 100 )
                                result = sprintf( "Khoảng cách %s rất xa giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                        else    result = sprintf( "Khoảng cách %s cực xa giữa bạn %s.", map->get_name(), PF_NO_00031->get_direction(x0, y0, x, y) );
                }
                
                send_user( me, "%c%c%w%s", ':', 3, 5501, sprintf( "Sứ mệnh nhân vật " HIR "%s" NOR " hiện tại đang:\n\n%s\n", who->get_name(), result ) );
        }

        return 1;
}

// 函数:获取方向字串
string get_direction( int x0, int y0, int x1, int y1 )
{
        int dx, dy, xy;

        dx = x1 - x0;  dy = y1 - y0;

        if( dx > 0 )
        {
                if( dy > 0 )    // 第一象限
                {
                        xy = abs( dy * 1000 / dx );
                        if( xy < 1000 / 3 ) return "Phía Đông";
                        else if( xy < 3000 ) return "Phía Đông Bắc";
                        else return "Phía Bắc";
                }
                else if( dy < 0 )    // 第四象限
                {
                        xy = abs( dy * 1000 / dx );
                        if( xy < 1000 / 3 ) return "Phía Đông";
                        else if( xy < 3000 ) return "Phía Đông Nam";
                        else return "Phía Nam";
                }
                else    return "Phía Đông";
        }
        else if( dx < 0 )
        {
                if( dy > 0 )    // 第二象限
                {
                        xy = abs( dy * 1000 / dx );
                        if( xy < 1000 / 3 ) return "Phía Tây";
                        else if( xy < 3000 ) return "Phía Tây Bắc";
                        else return "Phía Bắc";
                }
                else if( dy < 0 )    // 第三象限
                {
                        xy = abs( dy * 1000 / dx );
                        if( xy < 1000 / 3 ) return "Phía Tây";
                        else if( xy < 3000 ) return "Phía Tây Nam";
                        else return "Phía Nam";
                }
                else    return "Phía Tây";
        }
        else
        {
                if( dy > 0 ) return "Phía Bắc";
                else if( dy < 0 ) return "Phía Nam";
                else return "Xung quanh";
        }
}

// 函数:获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数:能否使用指令
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
