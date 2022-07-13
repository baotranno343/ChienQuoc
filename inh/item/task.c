
#include <ansi.h>
#include <music.h>

#define TASK_BONUS      100

string get_name();

// 函数：使命物品
int is_task_item() { return 1; }

// 函数：复位处理
void reset() { }

// 函数：给予奖励
void give_bonus( object who )
{
	int exp;
        if( who->is_npc() ) return;
	
	exp = TASK_BONUS * who->get_online_rate()/100;
        who->add_exp( exp );

        who->add_log("&task", exp);
        who->add_log("#task", 1);

        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
        write_user( who, ECHO "Bạn hoàn thành %s sứ mệnh, kinh nghiệm %+d.", get_name(), exp );
}
