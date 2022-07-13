
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6010; }

// 函数：构造处理
void create()
{
        object me = this_object();
        set_name( "Dao Cơ Tiên Tử" );
        NPC_EQUIP_D->init_figure( this_object(), GIRL, FEMALE, 15 );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        int status;
        object me = this_object();

        status = who->get_2("yaoji.status");
        if (status==0)
        {                
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    想不到你这么快就来了，我妹妹百合才刚刚跟我提起你。\n    还没有自我介绍呢。我是瑶姬仙子，专门负责掌管天界的祭祀典礼。其实我也没有什么特别的东西可以教你。不过你要清楚，与别人交流是以后在游戏世界中收集情报所必须的，你可以在与别人对话中学会很多新的东西。不仅是 NPC，从其他的玩家那里收集情报也十分重要，你能从中了解许多之前不了解的事情。\n"
                        ESC "继续\ntalk %x# welcome.1", me->get_name(), getoid(me) ) );        
                who->set_2("yaoji.status", 1);                        
        }                        
        else        
                do_welcome("1");     
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, status;
        object who;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    想要与 NPC 交谈，你只要用鼠标单击需要交谈的 NPC 就可以了。而要与其他玩家交流，就要用到游戏所提供的聊天功能。\n    还有，为了保持玩家之间的交流不受到其他人的干扰，游戏中一共划分了" HIR "七个聊天频道" NOR "，分别是：" HIR "当前、公众、国家、帮派、门派、队伍、交易、谣言" NOR "。\n"
                        ESC "继续\ntalk %x# welcome.2\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                who->set_2("yaoji.status", 1);
                break;
        case 2:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    当前频道为最基本的聊天频道，在这个频道中你所说的话只有同一个屏幕的玩家能接收到。不过这个聊天频道最特别之处就是说话的内容会在说话者的头上显示出来。\n    公众频道是一个世界性的频道，游戏中所有的玩家都能通过这个频道畅所欲言，自由地交流。\n"
                        ESC "继续\ntalk %x# welcome.3\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;     
        case 3:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    国家频道是专门为同一个国家的玩家而设的，只有所属国相同的玩家，才能利用这个频道中互通消息。\n    帮派频道、队伍频道与国家频道作用类似，不过其作用范围限定有所区别而已。帮派频道只能作于帮派内部交流用途，而队伍频道则用于小队队员之间的相互通讯。\n"
                        ESC "继续\ntalk %x# welcome.4\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;            
        case 4:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    交易频道其实也与公众频道一样，但是为了方便玩家们经商交易而特别设定的频道。\n    谣言频道是一个比较特殊的频道，不仅仅是玩家可以在这里以匿名的方式发送信息，一个神秘组织也经常利用这个频道报道游戏中所发生的一切大事。\n"
                        ESC "继续\ntalk %x# welcome.5\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;      
        case 5:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    聊天频道的功用大致如此……嗯……如果你有时候觉得频道中的信息太多而厌烦的话，可以利用频道管理的功能，将一些过于嘈杂的频道封锁就可以了。有时候把频道全部封锁，享受一下宁静时刻感觉还真是不错的。\n"
                        ESC "继续\ntalk %x# welcome.6\n"
                        ESC "关闭\nCLOSE\n", me->get_name(), getoid(me) ) );
                break;                                                    
        case 6:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    记住，与别人交谈时态度一定要亲切哦，要学会活用各种表情表达出自己的心情。没有经过自己的任何努力，光靠一味地问别人，同样不会得到什么好结果的。\n    最后嘛……在你今后遇到无数的人中，一定会有能与你交心的好友。不要犹豫，利用添加好友功能，把朋友的名字添加到自己的好友手册中。这样的话，以后无论你们分隔各地，都能利用好友功能互发信件来联系。\n"
                        ESC "继续\ntalk %x# welcome.7\n", me->get_name(), getoid(me) ) );                
                break;
        case 7:
                send_user( who, "%c%c%w%s", ':', 4, 6010,
                        sprintf("%s：\n    真高兴你肯听完我说的话。看来百合妹妹说你是一个勤奋的人一点都没错。保持一个好的心情继续努力吧。我会永远祝福你一路平安。\n"
                        ESC "关闭\nCLOSE\n", me->get_name() ) );                
                break;                
        }
}