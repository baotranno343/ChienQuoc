#include <ansi.h>
#include <public.h>

// 变量：收藏品文件列表
string *FileTable = ({
        "/item/97/9701", 
        "/item/97/9702", 
        "/item/97/9703", 
        "/item/97/9704", 
        "/item/97/9705", 
        "/item/97/9706", 
        "/item/97/9707", 
        "/item/97/9708", 
        "/item/97/9709", 
        "/item/97/9710", 
        "/item/97/9711", 
        "/item/97/9712", 
        "/item/97/9713", 
        "/item/97/9714", 
        "/item/97/9715", 
        "/item/97/9716", 
        "/item/97/9717", 
        "/item/97/9720", 
        "/item/97/9721", 
        "/item/97/9722", 
        "/item/97/9723", 
        "/item/97/9724", 
        "/item/97/9725", 
        "/item/97/9726", 
        "/item/97/9727", 
        "/item/97/9728", 
        "/item/97/9729", 
        "/item/97/9730", 
        "/item/97/9731", 
        "/item/97/9732", 
        "/item/97/9733", 
        "/item/97/9750", 
        "/item/97/9751", 
        "/item/97/9752", 
        "/item/97/9753", 
        "/item/97/9754", 
        "/item/97/9755", 
        "/item/97/9770", 
        "/item/97/9771", 

});

int sizeof_file = sizeof(FileTable);

// 变量：收藏品名称列表

string *NameTable = ({
        "大学", 
        "中庸", 
        "论语", 
        "孟子", 
        "诗经", 
        "尚书", 
        "礼记", 
        "周易", 
        "春秋", 
        "轩辕本记", 
        "十洲记", 
        "周书", 
        "九歌", 
        "天问", 
        "古镜记", 
        "归藏", 
        "龙鱼河图", 
        "四季图·春", 
        "四季图·夏", 
        "四季图·秋", 
        "四季图·冬", 
        "写意花草·梅", 
        "写意花草·兰", 
        "写意花草·菊", 
        "写意花草·竹", 
        "荷塘月色图", 
        "碧水鸳鸯图", 
        "云山飞瀑图", 
        "百凤朝凰图", 
        "天女散花图", 
        "白泽图", 
        "龙纹玉佩", 
        "凤纹玉佩", 
        "虎纹玉佩", 
        "雀纹玉佩", 
        "鸳鸯玉佩", 
        "和氏璧", 
        "青花鱼纹盘", 
        "青铜古镜",         
});

int sizeof_name = sizeof(NameTable);

// 函数：获取收藏品文件
string get_collect_file() { return FileTable[ random(sizeof_file) ]; }

// 函数：获取收藏品名称
string get_collect_name() { return NameTable[ random(sizeof_name) ]; }
//云游商人do_look
void do_look( object who,object npc)
{
	string cmd="";
	if ( who->get_save_2("qixi.flag") == 3 && time()<"sys/party/qixi"->get_qixi_time())
		cmd=sprintf(ESC "找寻王母娘娘\ntalk %x# qixi.1\n",getoid(npc));
	if ( time()<"sys/party/qixi"->get_qixi_time() &&( who->get_save_2("qixi.flag") == 8 || who->get_save_2("qixi.flag") == 9 || who->get_save_2("qixi.flag") == 10 || who->get_save_2("qixi.flag") == 11 ) )
		cmd=sprintf(ESC "七夕天赐奇缘（2）\ntalk %x# qixi.1\n",getoid(npc));
	if ( sizeof(npc->get_2("good")) != 0 )
	{
		if ( who->get_save_2("mastertask.type") != 7 || who->get_save_2("mastertask.status") == 99)
		        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(), 
		                sprintf("%s：\n    嘿嘿，只有有缘人才能找到我，既然你能够这么快的来到我这里，看来你就是我的有缘人，我身上的东西，你尽管挑吧！对待有缘人，我从不吝啬。"+"/quest/word"->get_normal_word(npc)+"\n"
		                        ESC "交易\nlist %x#\n"
		                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc) ) +cmd);   
		else
		        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(), 
		                sprintf("%s：\n    嘿嘿，只有有缘人才能找到我，既然你能够这么快的来到我这里，看来你就是我的有缘人，我身上的东西，你尽管挑吧！对待有缘人，我从不吝啬。"+"/quest/word"->get_normal_word(npc)+"\n"
		                        ESC "求得灵药\ntalk %x# accept_task.1\n"
		                        ESC "交易\nlist %x#\n"
		                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc),getoid(npc) ) );   
	}
	else
	{
		if ( who->get_save_2("mastertask.type") != 7 || who->get_save_2("mastertask.status") == 99)
		        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(), 
		                sprintf("%s：\n    唉，你晚来了一步，刚刚我的最后一件收藏品已经被别人买走了，看来我们的缘分还未到，别心急，慢慢等待吧，总有一天缘分会到来的。"+"/quest/word"->get_normal_word(npc)+"\n"	
		                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc) ) +cmd);   
		else
		        send_user( who, "%c%c%w%s", ':', 3, npc->get_char_picid(), 
		                sprintf("%s：\n    唉，你晚来了一步，刚刚我的最后一件收藏品已经被别人买走了，看来我们的缘分还未到，别心急，慢慢等待吧，总有一天缘分会到来的。"+"/quest/word"->get_normal_word(npc)+"\n"
		                        ESC "求得灵药\ntalk %x# accept_task.1\n"
		                        ESC "离开\nCLOSE\n", npc->get_name(), getoid(npc),getoid(npc) ) );   
	}		
		
}
