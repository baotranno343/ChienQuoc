
#include <npc.h>
#include <ansi.h>
#include <effect.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

string * name = ({ "小乖", "叮当", "驼驼", "独角", "胖胖", "紫毛", "笨笨",  });
string * city = ({ "齐", "韩", "赵", "魏", "秦", "楚", "燕", });

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5402; } 

// 函数：构造处理
void create()
{
        set_name( "宠物商人" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
	int z;
        object me = this_object();
        z = get_z(me);
        z = z/10;
        z -= 1;
        if (z<0||z>6) return;
        send_user( who, "%c%c%w%s", ':', 3, 5402,
        	sprintf("%s：\n    想不想骑上我们%s国的专属宠物%s威风威风？只要你与本国的友好关系达到亲密，即可用一颗6级的任意晶石和我兑换，你的心愿马上就能得到满足了。记住，周国的神秘商人那里就有晶石可以购买。\n"
                ESC "兑换骑宠%s\ntalk %x# welcome.1\n"
                ESC "关闭\nCLOSE\n", me->get_name(), city[z], name[z], name[z], getoid(me) ) );
}

void do_welcome( string arg )
{
        object who, me;
        string result;
        int flag, id;
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	result = me->get_name()+"：\n    您可以用“给予”指令，将晶石交给我。\n";
                send_user( who, "%c%c%w%s", ':', 3, 5402, result );
                break;
	}
}

// 函数：接受物品
int accept_object( object who, object item ){ return __FILE__ ->accept_object_callout( this_object(), who, item ); }

// 函数：接受物品(在线更新)
int accept_object_callout( object me, object who, object item ) 
{
        int level, z;
        string result;
        object obj;

        me->to_front_eachother(who);
	
        if( !item->is_diamond_2() ) 
        {
                return 0;
        }
        if (item->get_level()!=6) 
        {
        	result = me->get_name()+"：\n    您给予的晶石不符合条件。\n";
        	send_user( who, "%c%c%w%s", ':', 3, 5402, result );
        	return -99;
        }
        z = get_z(me);
        z = z/10;
        z -= 1;
        if (z<0||z>6) return 0;        
        if (who->get_city_name()!= city[z]+"国")
        {
        	result = me->get_name()+"：\n    您不是本国的人，不能兑换骑宠。\n";
        	send_user( who, "%c%c%w%s", ':', 3, 5402, result );
        	return -99;
        }       
        item->remove_from_user();
        destruct( item );
        obj = new (sprintf("/item/ride/%03d", z+1));
        if (obj)
        {
		level = obj->move(who, -1);
                obj->add_to_user( level );        	
        }
        result = me->get_name()+"：\n    现在给您兑换骑宠了。\n";
        send_user( who, "%c%c%w%s", ':', 3, 5402, result );
        return -99; 
}       