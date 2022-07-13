/*****************************
	**Halloween**
*****************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>

#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

int iStart,iFinish,iFinish2,close_val,open_val;

// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
	iStart = mktime(2009,10,29,0,0,0);
	iFinish = mktime(2009,11,5,23,0,0);
	iFinish2 = mktime(2009,11,10,23,59,0);
}