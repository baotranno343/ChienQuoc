#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>
#include <task.h>

#define _TEST
inherit OFFICER;

mapping mpTask = ([
20: ([
	"独眼兽" : "在首阳山可以杀到独眼兽 ",
	"鬼火" : "在无定河畔可以杀到鬼火 ",
	"幽灵" : "在无定河可以杀到幽灵 ",
	"飞贼" : "在马陵道可以杀到飞贼 ",
	"巡城小兵" : "在马陵道可以杀到巡城小兵 ",
	"巡城小兵" : "在巨鹿可以杀到巡城小兵 ",
	"草寇" : "在桂陵可以杀到草寇 ",
	"燕Quốc巡逻兵" : "在巨鹿可以杀到赵Quốc巡逻兵 ",
	"秦Quốc守军" : "在雁门关杀秦Quốc守军 ",
	"骷髅兵" : "在长平杀骷髅兵 ",
	]),
30: ([
	"褐尾蝎" : "在沼泽可以杀到褐尾蝎 ",
	"蛛蛛怪" : "在沼泽可以杀到蜘蛛怪 ",
	"毒刺蜂" : "在沼泽边缘可以杀到毒刺蜂 ",
	"牛头怪" : "在大别山脚可以杀到牛头怪 ",
	"水贼" : "在赤壁可以杀到水贼 ",
	"癞蛤蟆" : "在太湖可以杀到癞蛤蟆 ",
	"黑熊" : "在泰山山脚可以杀到黑熊 ",
	"赤炎蛇" : "在泰山可以杀到赤炎蛇 ",
	"螳螂妖" : "在泰山可以杀到螳螂妖 ",
	]),
40: ([
	"虾兵" : "在东海渔村可以杀到虾兵 ",
	"蟹将" : "在东海渔村可以杀到蟹将 ",
	"壮丁" : "在郑Quốc渠可以杀到壮丁 ",
	"苦役" : "在郑Quốc渠可以杀到苦役 ",
	"劳役" : "在郑Quốc渠可以杀到劳役 ",
	]),
50: ([
	"绿壳蜘蛛" : "在长白山可以杀到绿壳蜘蛛 ",
	"大笨熊" : "在玉柱峰可以杀到大笨熊 ",
	"魍魉" : "在白云峰可以杀到魍魉 ",
	"花豹精" : "在白云峰可以杀到花豹精 ",
	"豺狼" : "在白云峰可以杀到豺狼 ",
	"燕Quốc刀盾兵" : "在燕长城可以杀到燕Quốc刀盾兵 ",
	"燕Quốc剑盾兵" : "在燕长城可以杀到燕Quốc剑盾兵 ",
	"燕Quốc枪兵" : "在燕长城可以杀到燕Quốc枪兵 ",
	]),
60: ([
	"赵Quốc刀盾兵" : "在赵长城可以杀到赵Quốc刀盾兵 ",
	"赵Quốc剑盾兵" : "在赵长城可以杀到赵Quốc剑盾兵 ",
	"赵Quốc弓兵" : "在赵长城可以杀到赵Quốc弓兵 ",
	"秦Quốc刀盾兵" : "在秦长城可以杀到秦Quốc刀盾兵 ",
	"秦Quốc枪兵" : "在秦长城可以杀到秦Quốc枪兵 ",
	"秦Quốc弓兵" : "在秦长城可以杀到秦Quốc弓兵 ",
	]),
70: ([
	"劫匪" : "在弯道可以杀到劫匪 ",
	"密探" : "在弯道可以杀到密探 ",
	"水鬼" : "在弯道可以杀到水鬼 ",
	"罐中妖" : "在灵谷洞二层可以杀到罐中妖 ",
	"豆兵" : "在灵谷洞二层可以杀到豆兵 ",
	"冤魂" : "在灵谷洞二层可以杀到冤魂 ",
	"魍魉鬼" : "在灵谷洞二层可以杀到魍魉鬼 ",
	"疫鬼" : "在灵谷洞二层可以杀到疫鬼 ",
	"恶灵" : "在灵谷洞二层可以杀到恶灵 ",
	]),
80: ([
	"铜甲尸" : "在灵谷洞一层可以杀到铜甲尸 ",
	"侍卫亡灵" : "在灵谷洞二层可以杀到侍卫亡灵 ",
	"铁甲尸" : "在灵谷洞二层可以杀到铁甲尸 ",
	"刀盾骷髅" : "在万人坑一层可以杀到刀盾骷髅 ",
	"剑盾骷髅" : "在困魔阵一层可以杀到剑盾骷髅 ",
	"双刀骷髅" : "在万人坑二层可以杀到双刀骷髅 ",
	"僵尸" : "在万人坑四层可以杀到僵尸 ",
	"石狮" : "在将军古墓一层可以杀到石狮 ",
	"石虎" : "在将军古墓二层可以杀到石虎 ",
	"刀俑" : "在将军古墓二层可以杀到刀俑 ",
	"弓箭石俑" : "在将军古墓三层可以杀到弓箭石俑 ",
	"枪俑" : "在将军古墓三层可以杀到枪俑 ",
	"剑俑" : "在将军古墓三层可以杀到剑俑 ",
	]),
90: ([
	"骷髅妖" : "在将军古墓三层可以杀到骷髅妖 ",
	"骸骨精" : "在将军古墓三层可以杀到骸骨精 ",
	"邪灵" : "在困魔阵二层可以杀到邪灵 ",
	"尸魔" : "在困魔阵二层可以杀到尸魔 ",
	"怨灵" : "在困魔阵二层可以杀到怨灵 ",
	"金精" : "在虚灵洞可以杀到金精 ",
	"木精" : "在虚灵洞可以杀到木精 ",
	"水精" : "在虚灵洞可以杀到水精 ",
	"火精" : "在虚灵洞可以杀到火精 ",
	"土精" : "在虚灵洞可以杀到土精 ",
	]),
100: ([
	"罐中仙" : "在九曲桥可以杀到罐中仙 ",
	"龟仙人" : "在九曲桥可以杀到龟仙人 ",
	"天罡门众守" : "在天门阵一层可以杀到天罡门众守 ",
	"守阵天兵" : "在天门阵一层可以杀到守阵天兵 ",
	"守阵神将" : "在天门阵一层可以杀到守阵神将 ",
	"地煞门众守" : "在天门阵二层可以杀到地煞门众守 ",
	"太极门众守" : "在天门阵二层可以杀到太极门众守 ",
	"刀魂" : "在诛仙阵三层可以杀到刀魂 ",
	"剑魂" : "在诛仙阵四层可以杀到剑魂 ",
	"枪魂" : "在诛仙阵五层可以杀到枪魂 ",
	]),

		]);

// 函数：获取人物造型
int get_char_picid() { return 5416; }
void do_welcome(string arg);


// 函数：构造处理
void create()
{
        set_name("大胖");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
	set("mpLegend",([0:({32}),]));
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }
void do_look_call(object me,object who)
{
	int id = getoid(me);
	
	if ( who->get_save_2("dapang.name") )
	{
		if ( who->get_save_2("dapang.count") < who->get_save_2("dapang.total") )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你想知道我横着走的秘诀吗？如果你能够在30分钟内，完成我所交给你的任务，你就可以和我一样享受横着走的乐趣！想什么呢？还不赶快来试试～！\n"ESC"离开",me->get_name(),id,));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你想知道我横着走的秘诀吗？如果你能够在30分钟内，完成我所交给你的任务，你就可以和我一样享受横着走的乐趣！想什么呢？还不赶快来试试～！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),id,));
	}
	else	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你想知道我横着走的秘诀吗？如果你能够在30分钟内，完成我所交给你的任务，你就可以和我一样享受横着走的乐趣！想什么呢？还不赶快来试试～！\n"ESC"领取大胖任务\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),id,));
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,level,iLev;
       	object who, item;
       	string name,*nTmp,tmp1,tmp2;
	mapping mpInfo;	
	
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
	case 1:
		if ( gone_time(who->get_2("dapang.time")) < 180 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    过会你再来找我好吗？我现在手头上有点事情正忙着呢！呵呵～！你可以考虑先去押趟镖再来找我吧～！\n"ESC"离开",me->get_name(),));
			return ;	
		}
		if ( (level=who->get_level()) < 30 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你年纪尚小，以你目前的能力恐怕很难参悟其中的奥秘，呵呵～还是等你多增长些阅历（等级大于等于30级）再来找我吧！\n"ESC"离开",me->get_name(),));
			return ;	
		}
		if ( get_effect(who, EFFECT_MAGIC_CARD) )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    呵呵～！怎么样？好玩吧！按我说的去做没错吧～！等你变身效果消失后，你再来找我吧～！\n"ESC"离开",me->get_name(),));
			return ;	
		}
		tmp1 = who->get_2("dapang.name");
		tmp2 = who->get_2("dapang.where");
		if ( !tmp1 || !tmp2 )
		{
			level = level/10*10 - 10;
			if ( level > 100 )
				level = 100;
			if ( level < 20 )
				level = 20;
			mpInfo = mpTask[level];
			nTmp = keys(mpInfo);
			tmp1 = nTmp[random(sizeof(nTmp))];
			tmp2 = mpInfo[tmp1];
			who->set_2("dapang.time",time());
			who->set_2("dapang.name",tmp1);
			who->set_2("dapang.where",tmp2);
		}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    如今天下世道纷乱不堪，妖魔鬼怪四出肆虐，此乃天理不容。为拯救苍生，你前去杀20只%s，只望以此来警示那些蠢蠢欲动的妖孽，完成此使命还望告知我一声。\n"ESC"接受\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),tmp1,id,));
		break;
	case 2:
		tmp1 = who->get_2("dapang.name");
		tmp2 = who->get_2("dapang.where");
		if ( !tmp1 || !tmp2 )
			return ;
		who->delete_2("dapang.name");
		who->delete_2("dapang.where");
		who->set_save_2("dapang.time",time());
		who->set_save_2("dapang.name",tmp1);
		who->set_save_2("dapang.where",tmp2);
		who->set_save_2("dapang.total",20);
        	send_user(who,"%c%s",'!',"你接受了大胖的委托");
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_DAPANG,"大胖任务" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "杀20只"+tmp1 );
		break;	
	case 3:
		if ( !who->get_save_2("dapang.name") )
			return ;
		if ( who->get_save_2("dapang.count") < who->get_save_2("dapang.total") )
			return ;
		if ( "sys/sys/magic_card"->change_shape(who,0200,600) != 1 )
			return ;
		who->delete_save_2("dapang");
		who->add_cash(3000);
		who->add_exp(1000);
		who->add_potential(200);
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DAPANG, 1, "" );
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    呵呵～！怎么样？好玩吧！按我说的去做没错吧～！等你变身效果消失后，你再来找我吧～！\n"ESC"离开",me->get_name(),));
		send_user(who,"%c%s",';',"大胖任务 金钱 3000 经验 1000 潜能 200");
		break;	
	}


}
