
#include <city.h>

private int *Effect = ({ });    // 征状存盘数据

int get_login_flag();
int get_game_time();
int get_login_time();

// 函数：获取征状数据
int *get_effect_data() { return copy(Effect); }

// 函数：取存盘文件名
string get_save_file()
{
        string id = this_object()->get_id();
        return sprintf( "data/%c/%c/%c/%s/user" SAVE_EXTENSION, id[0], id[1], id[2], id );
}

string get_save_money_log()
{
        string id = this_object()->get_id();
        return sprintf( "data/%c/%c/%c/%s/money.dat", id[0], id[1], id[2], id );
	
}

void log_money(string type, int money)
{
	string result;
	result = sprintf("%s %d %s %d\n", short_time(), this_object()->get_level(), type, money);
	write_file(get_save_money_log(), result, 0);
}


// 函数：准备保存资料
void prepare_save()
{
        object me, npc;
        string file, name, xyz;
        int z, x, y, d;

        if( !stringp( file = get_save_file() ) ) return 0;

        me = this_object();

        // 设置存盘地点
        if( ( z = get_z(me) ) && !MAP_D->is_inside_battle(z) ) 
        {
        	if (me->get_2("jiguan.z"))
        		me->set_start_place( sprintf( "%d:(%d,%d)%d", me->get_2("jiguan.z"), me->get_2("jiguan.x"), me->get_2("jiguan.y"), get_d(me) ) );
        	else
                	me->set_start_place( sprintf( "%d:(%d,%d)%d", get_z(me), get_x(me), get_y(me), get_d(me) ) );
        }
        else if( ( name = me->get_org_name() ) != "" 
        &&      objectp( npc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) ) ) )
        {
                me->set_start_place( sprintf( "%d:(%d,%d)%d", get_z(npc), get_x(npc) + random(11) - 5, get_y(npc) + random(11) - 5, 3 ) );
        }
        else if( !stringp( xyz = me->get_start_place() ) 
        ||      sscanf(xyz, "%d:(%d,%d)%d", z, x, y, d) != 4 
        ||      z == 0 )
        {
                d = MAP_D->get_birth_xy(me);
                z = d / 1000000;
                x = ( d % 1000000 ) / 1000;
                y = d % 1000;
                me->set_start_place( sprintf( "%d:(%d,%d)%d", z, x, y, 3 ) );
        }

        // 保存身上物品
        if( get_login_flag() > 1 ) me->save_inventory();
	//保存宠物信息
	me->save_beast();
        Effect = get_effect_dbase(me);
}

// 函数：保存物体资料
int save()
{
        object me = this_object();
        if (me->get("is_gm")) return 0;
        prepare_save();
        return db_user_save( me, me->get_id() );    // save_object(file);
}

// 函数：载入物体资料
int restore()
{
        string file;
        int flag;

        if( !stringp( file = get_save_file() ) ) return 0;
        flag = restore_object(file);
        if( !arrayp(Effect) ) Effect = ({ });
        set_effect_dbase( this_object(), Effect );

        return flag;
}

// 函数：备份物体资料
int backup()
{
        string file = get_save_file();
//      string now = short_time();
        if( !stringp(file) ) return 0;
//      file = sprintf( "%s.%s%s%s-%s%s", file, now[2..3], now[5..6], now[8..9], now[11..12], now[14..15] );
        file += "_bak";
        Effect = get_effect_dbase( this_object() );
        return save_object(file);
}

// 函数：记录传奇日志
int log_legend( string legend )
{
        string id, file, result = "";
        int time, day, hour;

        id = this_object()->get_id();
        file = sprintf( "data/%c/%c/%c/%s/legend.txt", id[0], id[1], id[2], id );

        time = abs( get_game_time() + gone_time( get_login_time() ) );
        time /= 3600;  hour = time % 24;  
        time /= 24;  day = time;

        if( day ) result += sprintf( " %d 天", day );
        result += sprintf( " %d 时", hour );

        return efun::log_file(file, sprintf( "%s 第%s，%s\n", short_time(), result, legend ) );
}

// 函数：记录传奇日志
int log_item( string legend )
{
        string id, file, result = "";
        int time, day, hour;

        id = this_object()->get_id();
        file = sprintf( "data/%c/%c/%c/%s/item.txt", id[0], id[1], id[2], id );
        return efun::log_file(file, sprintf( "%s %s\n", short_time(), legend ) );
}