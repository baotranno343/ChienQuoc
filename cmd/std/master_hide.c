/******************
    师门隐藏任务
*******************/
#include <ansi.h>
#include <item.h>
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
	string *nTmp;
        if( !arg ) return 1;
	nTmp = explode(arg," ");
	switch(to_int(nTmp[0]))
	{
	default:
		break;
	case 0:					
		if (me->get("m_hide")==1)
		{
			send_user(me,"%c%s",'!',"Ngươi nhận được Nhiệm vụ Ẩn Tàng");
			"sys/task/master"->hide_quest(me);		
		}
		break;
	case 1:					
		send_user(me,"%c%s",'!',"Ngươi huỷ bỏ Nhiệm vụ Ẩn Tàng");
		me->delete("m_hide");
		break;
	}
}