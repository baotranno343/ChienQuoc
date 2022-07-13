#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "三魂六魄" );
        set_picid_1(4101);
        set_picid_2(4101);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.若蝉姑娘的三魂六魄。"; 
}

void say_hello(int i)
{
	object who;
	who = environment();
	if ( !who )
		return ;
	if ( i == 1 )
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "唐追：……蝉儿……你还怪我么……我错了……你听得到么……压制你的气息已散了吧……");
	else if ( i == 2 )
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "若蝉：哎……一直听得到的……只是口不能言。妾不怪，妾在家中以死拒嫁，时时盼郎携妾于飞……虽未料似而今，堪与唐郎为伴妾已觉幸甚。");
	else if ( i == 3 )
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "唐追：这些人可以帮你还魂！只需带你三魂六魄去对你身体念咒“魂兮归来”……");
	else if ( i == 4 )
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "若蝉：勿要顾我，只愿来生能与唐郎在天为比翼鸟，在地为连理枝……");
	else if ( i == 5 )
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "唐追：蝉儿，你要好好的……今生无缘，来生却定要一起……");
	else if ( i == 6 )
	{
		send_user(who, "%c%c%d%s", 0x43, 6,0,CHAT "若蝉：唐郎啊……");
		return ;
	}
	else
		return;
	call_out("say_hello",4,i+1);
}