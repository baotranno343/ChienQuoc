
#include <ansi.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 变量：随机对话
string *TalkTable = ({ 
        "昨天隔壁小丫头采了好多" HIY "花" NOR "，说是有梅花、兰花、文竹、菊花、玫瑰花什么的，可香了.",
        "昨天隔壁小丫头采了好多" HIY "花" NOR "，说是有茉莉花、牡丹花、桃花、山茶花、芍药花什么的，可香了.",
        "昨天隔壁小丫头采了好多" HIY "花" NOR "，说是有牵牛花、大红花、水仙花、海棠花、百合花、丁香花什么的，可香了.",
        "想变漂亮点吗?把十朵相同的花插在柳条环上就有" HIY "花环" NOR "戴了哦.",

        "通常茶叶铺里都会有红茶、绿茶、茉莉花茶、普洱茶卖，这些都是比较大众化的" HIY "茶" NOR ".",
        "茶叶铺里的铁观音茶、龙井茶、云雾茶、铁观音茶叶、云雾茶叶都是属于比较上等的" HIY "茶" NOR ".",

        "城东的老李头喜欢喝米酒、黄酒、老酒，这些" HIY "酒" NOR "不容易醉人.",
        "城西的老马头喜欢喝烧刀子、汾酒、杜康酒、女儿红，这些可都是烈" HIY "酒" NOR "哦.",

        "人不吃饭会饿死，自古以来我华夏儿女皆食" HIY "五谷" NOR "杂粮.",
        "您知道我们每天吃的" HIY "五谷" NOR "杂粮都有哪些吗?我来告诉您，就是水稻、麦子、玉米、小米、高粱.",

        "今年" HIY "农产品" NOR "大丰收，集市上到处都是冬瓜、南瓜、黄瓜、萝卜、白菜、青菜.",
        "今年" HIY "农产品" NOR "大丰收，集市上到处都是番薯、莲藕、茄子、竹笋、蘑菇.",
        "今年" HIY "农产品" NOR "大丰收，集市上到处都是绿豆、黄豆、扁豆、花生、辣椒、葱、大蒜、姜.",

        "补身子最好的办法就是多吃" HIY "蛋" NOR "，象鸡蛋、鸭蛋、鸟蛋、乌龟蛋对身体都是挺有好处的.",

        "集市上的" HIY "小吃" NOR "可好吃了，象烧饼、煎饼、红豆糕、绿豆糕什么的.",
        "集市上的" HIY "小吃" NOR "可好吃了，象牛肉干、烤肉串、烤番薯、豆腐干什么的.",
        "集市上的" HIY "小吃" NOR "可好吃了，象臭豆腐、炒瓜子、炒花生、冰糖葫芦什么的.",

        "锄禾日当午，汗滴禾下土，还多亏有了铁铲、锄头、铁犁、镰刀这些" HIY "生产用具" NOR ".",
        "锄禾日当午，汗滴禾下土，还多亏有了钉耙、草叉、铁锤、木槌这些" HIY "生产用具" NOR ".",
        "锄禾日当午，汗滴禾下土，还多亏有了凿子、刨子、锯子、簸箕、小木桶这些" HIY "生产用具" NOR ".",

        "过节或有大事需要" HIY "拜祭" NOR "的时候，得先把柱香、蜡烛、檀香、纸钱、小香炉和鹤嘴炉准备好.",
        "黄纸、朱砂、法笔是" HIY "道士" NOR "做法时的必需用品.",
        "祷告的时候燃着" HIY "檀香" NOR "，散发出来的香气可以使您心情更平静.",
        "祷告的时候会用到" HIY "鹤嘴炉" NOR "，您要是见到了可要记得留下来哦.",

        "居家过日子，铁锅、陶碗、金碗、竹筷、银筷等" HIY "生活用品" NOR "可是少不了的.",
        "居家过日子，碟子、盘子、勺子、水瓢等" HIY "生活用品" NOR "可是少不了的.",
        "居家过日子，菜刀、剪刀、茶壶、打火石等" HIY "生活用品" NOR "可是少不了的.",

        "女孩子都爱漂亮，随身带着胭脂、水粉等" HIY "化妆品" NOR "，可以随时补补妆.",
        "女孩子都爱漂亮，随身带着敷面粉、红印纸等" HIY "化妆品" NOR "，可以随时补补妆.",
        "女孩子都爱漂亮，随身带着发刷、粉扑、发夹等" HIY "化妆品" NOR "，可以随时补补妆.",
        "女孩子都爱漂亮，随身带着铜镜、手镜等" HIY "化妆品" NOR "，可以随时补补妆.",

        "听说前街的张乐师把锣、鼓、钹这几样" HIY "乐器" NOR "玩得挺拿手的.",
        "听说后街的赵乐师把笛子、唢呐这几样" HIY "乐器" NOR "玩得挺拿手的.",
        "听说左街的胡乐师把萧、竽、筝这几样" HIY "乐器" NOR "玩得挺拿手的.",
        "听说右街的黄乐师把琵琶、二胡这几样" HIY "乐器" NOR "玩得挺拿手的.",

        "您会打麻将吗?知道麻将牌中的\"" HIY "筒" NOR "\"字牌是九张吗?",
        "您会打麻将吗?知道麻将牌中的\"" HIY "条" NOR "\"字牌是九张吗?",
        "您会打麻将吗?知道麻将牌中的\"" HIY "万" NOR "\"字牌是九张吗?",
        "麻将牌中的东风、南风、西风、北风、红中、发财、白板合称为\"" HIY "风头牌" NOR "\".",
        "您会打麻将吗?万字牌、条字牌、筒字牌和风头牌合起来才成为一副完整的" HIY "麻将牌" NOR ".",

        "您会下" HIY "象棋" NOR "吗?知道红子、黑子加起来是３２个吗?",
        "您会下" HIY "象棋" NOR "吗?一套完整的象棋不单包括红子和黑子，还包括棋盘呢.",

        "您会下" HIY "围棋" NOR "吗?知道围棋有１８１个黑子和１８０个白子吗?",
        "您会下" HIY "围棋" NOR "吗?黑子、白子和棋盘合起来才成为一套完整的围棋.",

        "您读过四书吗?我告诉你哦，" HIY "四书" NOR "指的是《大学》、《中庸》、《论语》、《孟子》.",
        "您读过五经吗?我告诉你哦，" HIY "五经" NOR "指的是《诗经》、《尚书》、《礼记》、《周易》、《春秋》.",

        "您知道吗?读书人家里都置有白纸、墨块、毛笔、砚台，这些称为" HIY "文房四宝" NOR ".",

        "拿竹蜻蜓、小风车、小泥人这些" HIY "手工艺品" NOR "去哄小孩子是最有效的了.",

        "达官贵人们都喜欢用" HIY "玉佩" NOR "显示身份的高贵，象龙纹玉佩、凤纹玉佩、虎纹玉佩、雀纹玉佩、鸳鸯玉佩这些就是.",

        "前几天和药行的老师傅聊天才知道，原来古石灰、雄黄都是" HIY "矿物类药材" NOR "，我原以为都是些没用的东西呢.",
        "前几天和药行的老师傅聊天才知道，原来吡石、砂汞、硫磺都是" HIY "矿物类药材" NOR "，我原以为都是些没用的东西呢.",
        "前几天和药行的老师傅聊天才知道，原来慈石、绿矾都是" HIY "矿物类药材" NOR "，我原以为都是些没用的东西呢.",

        "如果您受了伤，可以用些" HIY "补血补法药" NOR "，象行军散、活络丸、造化丹就是.",
        "如果您受了伤，可以用些" HIY "补血补法药" NOR "，象正气散、安神丸、补心丹就是.",
        "如果您受了伤，可以用些" HIY "补血补法药" NOR "，象救急丹、活心丹、再造丸就是.",

        "听人说山里有宝藏，但是需要有残图左上角、右上角、左下角、右下角才能拼成一幅" HIY "残破藏宝图" NOR ".",

        "听说" HIY "残缺宝石" NOR "可以合成完美的宝石，我听说过残缺橙晶石、灰晶石、白晶石，您知道这些宝石吗?",
        "听说" HIY "残缺宝石" NOR "可以合成完美的宝石，我听说过残缺黄晶石、红晶石、黑晶石，您知道这些宝石吗?",
        "听说" HIY "残缺宝石" NOR "可以合成完美的宝石，我听说过残缺青晶石、绿晶石、蓝晶石、紫晶石，您知道这些宝石吗?",
});

mapping mpExchange = ([
	0015	: ([	1:(["give":(["稻草":2]),"object":"桔子","unit":"个","question":"两根稻草交换一个桔子"]),	
			2:(["give":(["蚂蚁卵":2]),"object":"梨","unit":"个","question":"两个蚂蚁卵交换一个梨"]),	
			3:(["give":(["闪光的石头":3]),"object":"蜂蜜","unit":"罐","question":"三块闪光的石头交换一罐蜂蜜"]),
			]),		
	1015	: ([	1:(["give":(["蝎尾":2]),"object":"梨","unit":"个","question":"两条蝎尾交换一个梨子"]),	
			2:(["give":(["蛛网":2]),"object":"桃子","unit":"个","question":"两张蛛网交换一个桃子"]),	
			3:(["give":(["火凤之翼":2]),"object":"牛肉干","unit":"块","question":"两件火凤之翼交换一块牛肉干"]),
			4:(["give":(["玉束髻":2]),"object":"烤肉串","unit":"串","question":"两根玉束髻交换一串烤肉串"]),
			]),
	1016	: ([	1:(["give":(["鼻环":2]),"object":"黄酒","unit":"坛","question":"两个鼻环交换一坛黄酒"]),	
			2:(["give":(["红色小石头":2]),"object":"老酒","unit":"坛","question":"两块红色小石头交换一坛老酒"]),	
			3:(["give":(["寒铁剑鞘":2]),"object":"杜康酒","unit":"坛","question":"两把寒铁剑鞘交换一坛杜康酒"]),
			]),	
	2015	: ([	1:(["give":(["蛙蹼":2]),"object":"黄酒","unit":"坛","question":"两只蛙蹼交换一坛黄酒"]),	
			2:(["give":(["铜罐":2]),"object":"烧刀子","unit":"坛","question":"两个铜罐交换一坛烧刀子"]),	
			]),
	2016	: ([	1:(["give":(["蜥蜴尾巴":2]),"object":"苹果","unit":"个","question":"两条蜥蜴尾巴交换一个苹果"]),	
			2:(["give":(["闪光的石头":2]),"object":"梨","unit":"个","question":"两个闪光的石头交换一个梨"]),	
			3:(["give":(["鱼叉":2]),"object":"西瓜","unit":"个","question":"两把鱼叉交换一个西瓜"]),
			4:(["give":(["黄色小石头":2]),"object":"烤番薯","unit":"个","question":"两块黄色小石头交换一个烤番薯"]),
			]),							
	3015	: ([	1:(["give":(["破旧的头盔":2]),"object":"米酒","unit":"坛","question":"两顶破旧的头盔交换一坛米酒"]),	
			2:(["give":(["剑鞘":2]),"object":"烧刀子","unit":"坛","question":"两把剑鞘交换一坛烧刀子"]),	
			]),
	3016	: ([	1:(["give":(["破旧的盔甲":2]),"object":"苹果","unit":"个","question":"两件破旧的盔甲交换一个苹果"]),	
			2:(["give":(["箭筒":2]),"object":"烤番薯","unit":"个","question":"两个箭筒交换一个烤番薯"]),	
			]),
	4015	: ([	1:(["give":(["死者遗物":2]),"object":"桃子","unit":"个","question":"两个死者遗物交换一只桃子"]),	
			2:(["give":(["蛛网":2]),"object":"香蕉","unit":"条","question":"两张蛛网交换一条香蕉"]),	
			3:(["give":(["铜罐":2]),"object":"西瓜","unit":"个","question":"两个铜罐交换一个西瓜"]),
			4:(["give":(["黄色小石头":2]),"object":"烤番薯","unit":"个","question":"两块黄色小石头交换一个烤番薯"]),
			]),
	4016	: ([	1:(["give":(["破布衣":2]),"object":"老酒","unit":"坛","question":"两件破布衣交换一坛老酒"]),	
			2:(["give":(["腐骨":2]),"object":"烧刀子","unit":"坛","question":"两根腐骨交换一坛烧刀子"]),	
			]),														
	5015	: ([	1:(["give":(["帽缨":2]),"object":"老酒","unit":"坛","question":"两个帽缨交换一坛老酒"]),	
			2:(["give":(["腐骨":2]),"object":"烧刀子","unit":"坛","question":"两根腐骨交换一坛烧刀子"]),	
			]),
	5016	: ([	1:(["give":(["红色小石头":2]),"object":"香蕉","unit":"条","question":"两块红色小石头交换一条香蕉"]),	
			2:(["give":(["鱼叉":2]),"object":"西瓜","unit":"个","question":"两把鱼叉交换一个西瓜"]),	
			3:(["give":(["箭筒":2]),"object":"烤番薯","unit":"个","question":"两个箭筒交换一个烤番薯"]),
			]),													
	6015	: ([	1:(["give":(["破损的头盔":2]),"object":"米酒","unit":"坛","question":"两件破损的头盔交换一坛米酒"]),	
			2:(["give":(["鼻环":2]),"object":"黄酒","unit":"坛","question":"两个鼻环交换一坛黄酒"]),	
			]),
	6016	: ([	1:(["give":(["狗尾巴":2]),"object":"冰糖葫芦","unit":"串","question":"两条狗尾巴交换一串冰糖葫芦"]),	
			2:(["give":(["黄蜂刺":2]),"object":"桔子","unit":"个","question":"两根黄蜂刺交换一个桔子"]),	
			3:(["give":(["剧毒刺":2]),"object":"苹果","unit":"个","question":"两根剧毒刺交换一个苹果"]),
			4:(["give":(["蜘蛛丝":2]),"object":"梨","unit":"个","question":"两条蜘蛛丝交换一个梨"]),
			]),		
	7015	: ([	1:(["give":(["腐骨":2]),"object":"烧刀子","unit":"坛","question":"两根腐骨交换一坛烧刀子"]),	
			2:(["give":(["魔之心":2]),"object":"汾酒","unit":"坛","question":"两个魔之心交换一坛汾酒"]),	
			]),
	7016	: ([	1:(["give":(["腐骨":2]),"object":"西瓜","unit":"个","question":"两根腐骨交换一个西瓜"]),	
			2:(["give":(["甲胄":2]),"object":"红豆糕","unit":"块","question":"两件甲胄交换一块红豆糕"]),	
			3:(["give":(["锁魔链":2]),"object":"绿豆糕","unit":"块","question":"两条锁魔链交换一块绿豆糕"]),
			]),			
	8015	: ([	1:(["give":(["小太极":2]),"object":"汾酒","unit":"坛","question":"两个小太极交换一坛汾酒"]),	
			2:(["give":(["寒铁枪头":2]),"object":"杜康酒","unit":"坛","question":"两根寒铁枪头交换一坛杜康酒"]),	
			3:(["give":(["寒铁":2]),"object":"女儿红","unit":"坛","question":"两块寒铁交换一坛女儿红"]),
			]),	
	8016	: ([	1:(["give":(["甲胄":2]),"object":"红豆糕","unit":"块","question":"两件甲胄交换一块红豆糕"]),	
			2:(["give":(["魔之心":2]),"object":"绿豆糕","unit":"块","question":"两个魔之心交换一块绿豆糕"]),	
			3:(["give":(["寒铁刀柄":2]),"object":"烤肉串","unit":"串","question":"两把寒铁刀柄交换一串烤肉串"]),
			4:(["give":(["寒铁枪头":2]),"object":"牛肉干","unit":"块","question":"两根寒铁枪头交换一块牛肉干"]),	
			5:(["give":(["寒铁":2]),"object":"烧饼","unit":"个","question":"两块寒铁交换一个烧饼"]),	
			]),																			
]);
mapping mpFile = ([
	"黄酒" : "/item/31/3151",
	"冰糖葫芦"	: "/item/33/3325",
	"桔子"	: "/item/32/3282",
	"烤肉串"	: "/item/33/3311",
	"烤番薯"	: "/item/33/3320",
	"杜康酒"	: "/item/31/3155",
	"苹果"	: "/item/32/3283",
	"牛肉干"	: "/item/33/3310",
	"米酒"	:	"/item/31/3150",
	"女儿红"	: "/item/31/3156",
	"老酒"	: "/item/31/3152",
	"绿豆糕"	: "/item/33/3304",
	"梨"	:	"/item/32/3284",
	"烧饼"	: "/item/33/3301",
	"烧刀子"	: "/item/31/3153",
	"西瓜"	: "/item/32/3280",
	"桃子"	: "/item/32/3285",
	"香蕉"	: "/item/32/3281",
	"汾酒"	: "/item/31/3154",
	"蜂蜜"	:	"/item/32/3244",
	"红豆糕"	: "/item/33/3303",
]);
int sizeof_talk = sizeof(TalkTable);

// 函数：对话处理
void do_talk( object who, object me )
{
        send_user( who, "%c%s", ':', sprintf( "%s：\n%s\n", me->get_name(), TalkTable[ random(sizeof_talk) ] ) );
}
//交换提示
void do_talk_exchange(object who, object me,int iFlag)
{
	string sTalk,sQues;
	int i,iSize;
	int *nTmp;
	mapping mpTmp,mpTmp1;
	
	mpTmp = mpExchange[iFlag];
	if ( !mapp(mpTmp) )
		return ;
	nTmp = keys(mpTmp);
	iSize = sizeof(nTmp);
	if ( iSize == 0 )
		return;
	sQues = "";
/*	
	for(i=1;i<=iSize;i++)
	{		
		sQues += sprintf("\n" ESC "%s\ntalk %x# inputx.%d\n",mpTmp[i]["question"],getoid(me),i);		
	}
*/	
	sTalk = sprintf("%s: \n    "+"/quest/word"->get_normal_word(me)+"\n    客官，需要换点什么吗?%s" ,me->get_name(),sQues);
//	sTalk += sprintf("\n" ESC "坊间传闻\ntalk %x# info", getoid(me));
	send_user( who, "%c%s", ':', sTalk);	
	
}

void do_inputx(object me,object who,string sArg,int iFlag)
{
	int i;
	string sTmp;
	if ( !mapp(mpExchange[iFlag]) )
		return ;
	i = to_int(sArg);
	if ( !mapp(mpExchange[iFlag][i]) )
		return;	
//	sTmp = sprintf("你想交换多少%s%s\n",mpExchange[iFlag][i]["unit"],mpExchange[iFlag][i]["object"]);
//	send_user( who, "%c%c%d%s", '?', 1, 30, sTmp+sprintf( ESC "talk %x# do_exchange.%d",getoid(me),i)+".%s\n");		
}

void do_exchange(string sArg,int iFlag)
{
	int i,iSize,iKind,iAmount,iCount,j;
	mapping mpTmp,mpGive;
	string *nTmp,sTmp,sItemPath;
	object who,obj,item,*inv;
	return;
	if ( sscanf(sArg,"%d.%d",iKind,iAmount) != 2 )
		return ;
	if ( iAmount <= 0 )
		return ;
	if ( iAmount > 30 )
		iAmount = 30;
	who = this_player();
	mpTmp = mpExchange[iFlag];
	if ( !mapp(mpTmp)||!mapp(mpTmp[iKind]) )
		return;
	mpGive = mpTmp[iKind]["give"];
	nTmp = keys(mpGive);
	iSize = sizeof(nTmp);
	if ( iSize == 0 )
		return ;
	inv = all_inventory(who, 1, MAX_CARRY);
	inv -= ({ 0});	
	foreach(sTmp in nTmp)
	{
		iCount = mpGive[sTmp]*iAmount;
		for( i = 0, iSize = sizeof(inv); i < iSize; i ++ )
		{			
			if ( inv[i]->get_name() != sTmp )
				continue;
			iCount -= inv[i]->get_amount();
			if ( iCount <=0 )
				break;
		}
		if ( iCount > 0 )
		{
				send_user( who, "%c%s", ':', "你身上没有足够的物品供交换");
				return ;	
		}
	}					
	sItemPath = mpFile[mpTmp[iKind]["object"]];  
	if ( !stringp(sItemPath) )
	{
		send_user( who, "%c%s", ':', "对不起，物品换完了1");
		return ;
	}
	obj = new (sItemPath);
	
	if ( !obj ) 
	{
		send_user( who, "%c%s", ':', "对不起，物品换完了2");
		return ;
	}
	obj->set_amount(iAmount);
	i =obj->move(who, -1);
	if ( !i )
	{
		destruct(obj);
		send_user( who, "%c%s", '!', "您携带的物品太多了");
		return ;
	}
	obj->add_to_user(i);
	sTmp = sprintf("您得到 " HIY "%s" NOR "！", obj->get_name());
  	send_user( who, "%c%s", '>', sTmp);
  	
	//拿走物品
	foreach(sTmp in nTmp)
	{
		iCount = mpGive[sTmp]*iAmount;
		for( i = 0, iSize = sizeof(inv); i < iSize; i ++ )
		{
			if ( inv[i]->get_name() != sTmp )
				continue;
			j = inv[i]->get_amount();
			if ( iCount >= j )
			{
				iCount -= j;
				inv[i]->remove_from_user();	
				destruct(inv[i]);
				continue;
			}	
			j -= iCount;				
			inv[i]->set_amount(j);	
			break;			
		}
	}					
}

// 函数：获取对话字串
string get_talk_string( int id )
{
        switch( id )    // 0: 等级不够；1: 询问任务；2: 答应任务；3: 没完成任务；4: 刚完成任务；5: 完成任务
        {
    case 0001 : return "走在街上看到姑娘们戴着我种的花，心里别提有多高兴啦.";
    case 0002 : return "最近花园里的花越来越少了，您能帮我找一些花回来吗?";
    case 0003 : return "谢谢您了，帮我找一些花回来吧.";
    case 0004 : return "那些花儿您都找到了吗?";
    case 0005 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0006 : return "前些天您帮我收集的花，现在长的可好啦，有时间来看看吧.";

    case 0011 : return "窈窕淑女，君子好逑.";
    case 0012 : return "我喜欢秀丽小姐，可是不敢向她表白，您能帮我找个花环么?我想送给她.";
    case 0013 : return "谢谢您了，帮我找个花环回来吧.";
    case 0014 : return "您找到花环了吗?";
    case 0015 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0016 : return "我把您找到的花环送给了秀丽小姐，别提她有多高兴啦，谢谢您.";

    case 0021 : return "快来看快来买，上好的茶叶啊.";
    case 0022 : return "最近货源紧张，您能帮我找一些茶回来吗?我可是有报酬给您哦.";
    case 0023 : return "谢谢您了，帮我找一些茶回来吧.";
    case 0024 : return "那些茶您都找到了吗?";
    case 0025 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0026 : return "上次多亏您找的那些茶叶，才使我度过难关呀.";

    case 0101 : return "酒乃粮食精，越喝越年轻.";
    case 0102 : return "好几天没喝酒了，您能帮我找些酒回来吗?";
    case 0103 : return "谢谢您了，帮我找一些酒回来吧.";
    case 0104 : return "好想喝酒啊，酒瘾又犯了.";
    case 0105 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0106 : return "喝了上次您给我的酒，我大醉了三天，爽啊.";

    case 0111 : return "粮食来之不易，可要知道珍惜啊.";
    case 0112 : return "又到播种的日子了，您能帮我找些五谷回来吗?";
    case 0113 : return "谢谢您了，帮我找一些五谷回来吧.";
    case 0114 : return "五谷收集齐备了吗?";
    case 0115 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0116 : return "您前段时间送来的五谷都已经播种下去了，真是太感谢您啦.";

    case 0121 : return "今年收成不错啊，想必农产品也很好销路.";
    case 0122 : return "我想找些农产品来卖，赚几个小钱，您能帮我吗?";
    case 0123 : return "谢谢您了，帮我找一些农产品回来吧.";
    case 0124 : return "请问您帮我找到农产品了吗?";
    case 0125 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0126 : return "上次您找来的那些农产品，真是好卖呀.";

    case 0201 : return "听说吃蛋能补身子，不知道是不是真的?";
    case 0202 : return "我家娘子身子不好，听人说吃蛋能补身子，您能帮我找几个来么?";
    case 0203 : return "谢谢您了，帮我找一些蛋回来吧.";
    case 0204 : return "东西收集好了吗?我娘子在家等着呢.";
    case 0205 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0206 : return "自从吃了您上次找来的蛋，我家娘子的身子比以前好多了.";

    case 0211 : return "好想吃小吃，可是妈妈不给买，呜呜呜……";
    case 0212 : return "好想吃小吃，您能帮我买些回来吗?";
    case 0213 : return "谢谢您了，帮我找一些小吃回来吧.";
    case 0214 : return "呜呜呜……小吃还没买来.";
    case 0215 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0216 : return "吃了上次您带的小吃，至今还忘不了呀.";

    case 0221 : return "对我们庄稼人来说，生产用具可是命根子呀.";
    case 0222 : return "村里的农具坏了大半，您能帮手找一些生产用具回来吗?";
    case 0223 : return "谢谢您了，帮我找一些生产用具回来吧.";
    case 0224 : return "我们要是没了生产用具，那真是没法活了.";
    case 0225 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0226 : return "上次的事情太感谢您啦，我们村的人都会记着您的好.";

    case 0301 : return "快要过节了，大家都会多求神佛保佑的.";
    case 0302 : return "快要过节了，您能帮我找点拜祭用品吗?";
    case 0303 : return "谢谢您了，帮我找一些拜祭用品回来吧.";
    case 0304 : return "拜祭可是非同小可，只有过节或有大事的时候才举行.";
    case 0305 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0306 : return "前几天多亏您帮我找的那些用品，才没有耽误拜祭的大事.";

    case 0311 : return "天灵灵，地灵灵，捉妖除魔，替天行道.";
    case 0312 : return "我看近日妖气弥漫，可否帮我找些道士用品?我来做法.";
    case 0313 : return "谢谢您了，帮我找一些做法用品回来吧.";
    case 0314 : return "我老感觉这里阴深深的，过些时日看我做法驱妖.";
    case 0315 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0316 : return "那日我用您帮我找来的做法用品，发现原来是场雾，虚惊一场，呵呵.";

    case 0321 : return "过几天我们准备在花园里焚香祷告.";
    case 0322 : return "过几天我们准备在花园里焚香祷告，您可否帮我一下?";
    case 0323 : return "谢谢您了，帮我完成焚香祷告吧.";
    case 0324 : return "近日生意不好，看来要祷告一番，求祖宗保佑我财源滚滚来.";
    case 0325 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0326 : return "上次焚香祷告的事多谢您啦.";

    case 0401 : return "真是不当家不知柴米贵啊.";
    case 0402 : return "家里东西坏掉不少，您能帮我收集一些生活用品吗?";
    case 0403 : return "谢谢您了，帮我找一些生活用品回来吧.";
    case 0404 : return "居家过日子，生活用品可少不了啊.";
    case 0405 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0406 : return "谢谢您了，上次帮了我那么大的忙.";

    case 0411 : return "听人说用了化妆品就不会变老，是不是真的呢?";
    case 0412 : return "家人不要我出门，您能帮我找些化妆品吗?";
    case 0413 : return "谢谢您了，帮我找一些化妆品回来吧.";
    case 0414 : return "请问您帮我找到化妆品了吗?";
    case 0415 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0416 : return "谢谢您上次送我的化妆品.";

    case 0421 : return "没事的时候听听音乐，真是享受人生呀！";
    case 0422 : return "鄙人一生喜好乐器，但至今未能收集齐全，不知您能否帮我找一些乐器?";
    case 0423 : return "谢谢您了，帮我找一些乐器回来吧.";
    case 0424 : return "请问您帮我找到乐器了吗?";
    case 0425 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0426 : return "上次多亏您了，我终于把各种乐器都收集齐全了.";

    case 0501 : return "我知道赌博不好，可就是戒不掉.";
    case 0502 : return "赌赌赌，赌场赌圣，唯我独尊.您能帮我找齐麻将的\"万\"字牌吗?";
    case 0503 : return "谢谢您了，帮我找齐麻将的\"万\"字牌回来吧.";
    case 0504 : return "麻将牌还没找齐吗?要不要我们先玩两把?";
    case 0505 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0506 : return "赌赌赌，赌场赌圣，唯我独尊.";

    case 0511 : return "我知道赌博不好，可就是戒不掉.";
    case 0512 : return "赌赌赌，赌场赌王，唯我独尊.您能帮我找齐麻将的\"条\"字牌吗?";
    case 0513 : return "谢谢您了，帮我找齐麻将的\"条\"字牌回来吧.";
    case 0514 : return "麻将牌都找齐了吗?要不要我们先玩两把?";
    case 0515 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0516 : return "赌赌赌，赌场赌王，唯我独尊.";

    case 0521 : return "我知道赌博不好，可就是戒不掉.";
    case 0522 : return "赌赌赌，赌场赌神，唯我独尊.您能帮我找齐麻将的\"筒\"字牌吗?";
    case 0523 : return "谢谢您了，帮我找齐麻将的\"筒\"字牌回来吧.";
    case 0524 : return "找齐麻将牌了吗?要不要我们先玩两把?";
    case 0525 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0526 : return "赌赌赌，赌场赌神，唯我独尊.";

    case 0601 : return "我知道赌博不好，可就是戒不掉.";
    case 0602 : return "赌赌赌，赌场赌仙，唯我独尊.您能帮我找齐麻将的\"风头\"牌吗?";
    case 0603 : return "谢谢您了，帮我找齐麻将的\"风头\"牌回来吧.";
    case 0604 : return "麻将牌都找好了吗?要不要我们先玩两把?";
    case 0605 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0606 : return "赌赌赌，赌场赌仙，唯我独尊.";

    case 0611 : return "如果不赌钱，没事打打麻将也挺好的.";
    case 0612 : return "我急着要开台打麻将，可是找不到麻将了，您能否帮我找找?";
    case 0613 : return "谢谢您了，帮我找到麻将回来吧.";
    case 0614 : return "请问您找到麻将了吗?";
    case 0615 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0616 : return "上次您找到麻将后，居然不记得让你留下了，结果我们三缺一.";

    case 0621 : return "我叫小红，我喜欢下象棋用红子.";
    case 0622 : return "我想研究一下昨天的棋谱，可是红子少了几个，你能帮我吗?";
    case 0623 : return "谢谢您了，帮我找回那几个象棋的红子吧.";
    case 0624 : return "好无聊哦，红棋子还没有找到.";
    case 0625 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0626 : return "谢谢您帮我收集棋子，师父夸我好学，其实都是你的功劳呀.";

    case 0701 : return "我叫小黑，我喜欢下象棋用黑子.";
    case 0702 : return "我想研究一下昨天的棋谱，可是黑子少了几个，你能帮我吗?";
    case 0703 : return "谢谢您了，帮我找回那几个象棋的黑子吧.";
    case 0704 : return "好无聊哦，黑棋子还没有找到.";
    case 0705 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0706 : return "谢谢您帮我收集棋子，师父夸我好学，其实都是你的功劳呀.";

    case 0711 : return "象棋的最高境界是什么呢?";
    case 0712 : return "老夫嗜棋如命，今天我的命不见了，您能否帮我找一套象棋?";
    case 0713 : return "谢谢您了，帮我找一套象棋回来吧.";
    case 0714 : return "请问您找到象棋了吗?";
    case 0715 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0716 : return "谢谢您帮我找到象棋，什么时候有空来杀两盘?";

    case 0721 : return "围棋真是博大精深呀.";
    case 0722 : return "昨天家里的小儿把我心爱的围棋都当暗器丢光了，请问你能帮我再找一套回来吗?";
    case 0723 : return "谢谢您了，帮我找一副围棋回来吧.";
    case 0724 : return "围棋收集好了吗?我老汉可是手痒了.";
    case 0725 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0726 : return "谢谢您帮我找到象棋，什么时候有空来杀两盘?";

    case 0801 : return "书中自有黄金屋，书中自有颜如玉.";
    case 0802 : return "小生家境贫寒，无钱买书，您能否帮我把四书找来?";
    case 0803 : return "谢谢您了，帮我把四书找回来吧.";
    case 0804 : return "请问您帮我把四书找到了吗?";
    case 0805 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0806 : return "寒窗十年苦，有朝一日我一定出人头地.";

    case 0811 : return "书中自有黄金屋，书中自有颜如玉.";
    case 0812 : return "小生家境贫寒，无钱买书，您能否帮我把五经找来?";
    case 0813 : return "谢谢您了，帮我把五经找回来吧.";
    case 0814 : return "请问您帮我把五经找到了吗?";
    case 0815 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0816 : return "寒窗十年苦，有朝一日我一定出人头地.";

    case 0821 : return "书中自有黄金屋，书中自有颜如玉.";
    case 0822 : return "最近总觉得道德经太低了，能否帮我找齐四书五经回来试试?";
    case 0823 : return "谢谢您了，帮我找四书五经回来吧.";
    case 0824 : return "请问找齐四书五经了吗?";
    case 0825 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0826 : return "前两天我拿四书五经当枕头试了一下，发现刚刚好够高.";

    case 0901 : return "读书多了，别人都会尊敬您的.";
    case 0902 : return "听说读书人都有文房四宝，我也想弄来做做摆设，您能帮我收集一下吗?";
    case 0903 : return "谢谢您了，帮我找文房四宝回来吧.";
    case 0904 : return "有了文房四宝后，我也是读书人了，哈哈.";
    case 0905 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0906 : return "多谢您帮我找的东西，现在全城的人都知道我是读书人了.";

    case 0911 : return "邻居家的小孩子玩的手工艺品真是精致得不得了.";
    case 0912 : return "我家小孩子也想玩手工艺品，您能帮我找回来吗?";
    case 0913 : return "谢谢您了，帮我找一些手工艺品回来吧.";
    case 0914 : return "请问您找到手工艺品了吗?我家小孩子等得急了.";
    case 0915 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0916 : return "上次您送手工艺品给我家小孩子，他玩得可高兴了.";

    case 0921 : return "现在兵荒马乱，生意也不好做啦.";
    case 0922 : return "现在兵荒马乱，其它生意都不好做了，您能否帮我找些玉佩来卖?";
    case 0923 : return "谢谢您了，帮我找一些玉佩回来吧.";
    case 0924 : return "玉佩市价很不错，请问您找回来了吗?";
    case 0925 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 0926 : return "上次您找到的玉佩都卖了挺不错的价钱.";

    case 1001 : return "最近兵荒马乱，受伤的人也多了.";
    case 1002 : return "最近缺货，您可否帮我收集一些矿物类药材?";
    case 1003 : return "谢谢您了，帮我找一些矿物类药材回来吧.";
    case 1004 : return "请问您找到矿物类药材了吗?";
    case 1005 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 1006 : return "谢谢您上次帮的忙.";

    case 1011 : return "对我来说，炼药是最快乐的事情.";
    case 1012 : return "鄙人要炼一炉丹药，需要九种补血补法药，您可否帮我收集?";
    case 1013 : return "谢谢您了，帮我找九种补血补法药回来吧.";
    case 1014 : return "快些去收集药吧，我这还等着炼丹呢.";
    case 1015 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 1016 : return "上次多亏您帮我收集了那些药，丹药终于炼出来了.";

    case 1021 : return "战乱时期，对我们来说可是很好的发财机会喔.";
    case 1022 : return "趁着战乱发点小财，您能帮我收集一些残破藏宝图么?";
    case 1023 : return "谢谢您了，帮我找一些残破藏宝图回来吧.";
    case 1024 : return "残破藏宝图收集好了么?我还要赶去挖宝呢.";
    case 1025 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 1026 : return "上次多亏您帮忙才能把残破藏宝图收集齐全，谢谢了.";

    case 1101 : return "现在兵荒马乱，生意也不好做啦.";
    case 1102 : return "近日缺货，您能帮我收集一些残缺宝石吗?";
    case 1103 : return "谢谢您了，帮我找一些残缺宝石回来吧.";
    case 1104 : return "宝石都收集齐全了吗?有很多人都等着要买呢.";
    case 1105 : return "谢谢您了，您这么好心，老天爷一定会保佑您的.";
    case 1106 : return "多亏您才把货源搞定，谢谢啦.";
        }

        return "";
}
