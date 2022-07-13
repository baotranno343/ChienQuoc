
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name( "Đại Bá Công" );
        set_char_photoid(5303);
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();    
}


void do_look( object who )
{
        int status;
        string result;
        object me = this_object();
        result = sprintf("%s：\n    嘿～你来了，果然是个爱学习的好孩子，你想知道些什么呢？\n", me->get_name());
        status = who->get("dabogong");
        if ( (status & 1)==0)
                result += sprintf(ESC "我想了解物品的相关知识。\ntalk %x# welcome.1\n",getoid(me) );
        if ( (status & 2)==0)
                result += sprintf(ESC "当铺是作什么用的？\ntalk %x# welcome.4\n",getoid(me) );        
        result +=         ESC "没什么，路过而已。\nCLOSE\n";
        send_user( who, "%c%c%s", ':', 2, result);        
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i;
        object who, obj;
//        object me;        
        string cmd1, result;
//        me = this_object();
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        status = who->get("dabogong");
        switch(flag)
        {
        case 1:
                cmd1 = sprintf("talk %x# welcome.2", getoid(me));
                result = sprintf("%s：\n    在凡间，活络丸是用来补充你的气血的，当你看到界面左上角那个红色气血条上气血不够时，用鼠标右键单击它一下就可以马上就使用补充你的气血了。另外，你可以用鼠标左键将活络丸拖曳到游戏画面的快捷栏中，以后只有点击预设的快捷键就能直接使用。行军散和活络丸的作用相同，不过行军散补充气血的量没有活络丸多哦。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );
                send_user( who, "%c%c%w%s", ':', 4, 5301, result );        
                break;
        case 2:
                cmd1 = sprintf("talk %x# welcome.3", getoid(me));
                result = sprintf("%s：\n    装备呢，是用来保护自己的，分白色、蓝色、金色三种，档次由低到高，高级装备不仅能更好的保护自己，还能让你的攻击变得更强。装备的用法跟活络丸一样，鼠标右键单击就能马上装备在身上。当然，装备跟其他道具一样，可以拖曳到道具快捷栏中使用。\n"
                        ESC "继续\n%s\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), cmd1 );
                send_user( who, "%c%c%w%s", ':', 4, 5301, result );     
                break;        
        case 3:              
                result = sprintf("%s：\n    通常消灭怪物后，物品都会掉落在地上，这时只要点击一下地上的物品，就会自动放置在你的道具栏中了，这样道具的说明基本都讲解完毕了，如果还有其他方面的疑问，你可以去问问别的神仙哦。\n"
                        ESC "关闭\nCLOSE\n", me->get_name() );
                send_user( who, "%c%c%w%s", ':', 4, 5301, result );    
                break;        
        case 4:      
                result = sprintf("%s：\n    哈哈，问得好！当铺的作用可大啦！在往后闯荡江湖的日子里，贵重的物品或者暂时无用的物品会慢慢占据你身上的道具栏。如果在战斗的时候道具栏不够用，可是损失很大哦，或许有很多好的物品你没法捡，或许你要忍痛割爱丢下其他的物品才行，要避免这种损失，找当铺帮忙就绝对没错！可不是我自吹，由我一手所创立的当铺连锁经营店已经遍布全天下，为江湖各界提供最齐全最优质最有安全最有保障的服务！\n"
                        ESC "关闭\nCLOSE\n", me->get_name() );
                send_user( who, "%c%c%w%s", ':', 4, 5301, result );    
                break;                                                                
        }
}
