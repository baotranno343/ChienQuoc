
// 自动生成：/make/npc/make0010

#include <npc.h>
#include <ansi.h>

inherit OFFICER;

string * get_place_name()
{
	return ({ "Tề Quốc", "Hàn Quốc", "Triệu Quốc", "Ngụy Quốc", "Tần Quốc", "Sở Quốc", "Yên Quốc", "Chu Quốc", "Tân Thủ Thôn", "Đào Hoa Nguyên", "Thục Sơn", "Đường Môn", "Côn Luân", "Mao Sơn", "Vân Mộng Cốc","Cấm Vệ Quân" });
}

void do_goto( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5410; }

// 函数：构造处理
void create()
{
        set_name("Chủ Dịch Trạm");
	set_real_name("Trường Hoằng");
        set_city_name("Chu Quốc");

        set_2( "talk", ([
                "goto"    : (: do_goto :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
//	"/sys/task/travel"->do_look(this_object(), who);        
	__FILE__ ->do_look2(this_object(), who);
}

void do_look2( object npc, object who )
{
	string *name,tmp="";
	int id = getoid( npc );
	name = get_place_name();	
	name -= ({ npc->get_city_name()});
/*	
        if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user(who, "%c%s", '!', "带着钱票不能旅行。");
//              write_user(me, ECHO "……可是没有任何效果。");
                return ;
        }
*/        
        if( present("贵重物品", who, 1, MAX_CARRY*4) )
        {
                send_user(who, "%c%s", '!', "带着贵重物品不能旅行。");
//              write_user(me, ECHO "……可是没有任何效果。");
                return ;
        }		
	name -= ({ 0 });
	if(!objectp(present("Chiến Quốc Bảo Điển", who, 1, MAX_CARRY))) {
		tmp = ESC "Nhận lãnh Chiến Quốc Bảo Điển\n"+sprintf("talk %x# goto.dict\n",id);
	}
//	if (sizeof(name)==15) {
        send_user( who, "%c%s", ':', sprintf( " %s :\n "+"/quest/word"->get_normal_word(npc)+"\n"
        	
                ESC ""+name[0]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[0] ) +
                ESC ""+name[1]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[1] ) +
                ESC ""+name[2]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[2] ) +
                ESC ""+name[3]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[3] ) +
                ESC ""+name[4]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[4] ) +
                ESC ""+name[5]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[5] ) +
                ESC ""+name[6]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[6] ) +
                ESC ""+name[7]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[7] ) +
                ESC ""+name[8]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[8] ) +
                ESC ""+name[9]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[9] ) +
                ESC ""+name[10]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[10] ) +
                ESC ""+name[11]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[11] ) +
                ESC ""+name[12]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[12] ) +
                ESC ""+name[13]+"\n" + sprintf( "talk %x# goto.? %s\n", id, name[13] ) +
                
//                ESC "打开传送地图\n"+sprintf("talk %x# goto.map\n",id)+                
                ESC "Lấy "+npc->get_city_name()+" làm nơi trở lại thành.\n" + sprintf( "talk %x# goto.here\n", id ) +
                tmp+
                ESC "Rời khỏi.\nCLOSE\n", npc->get_name() ) );
//	}
}

// 函数：移动处理
void do_goto( string  arg )
{
	"/sys/task/travel"->do_goto(this_object(), this_player(), arg);     
}