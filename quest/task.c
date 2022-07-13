
// 变量：使命人物表

string *FileTable = ({
        "/npc/98/9800",
        "/npc/98/9801",
        "/npc/98/9802",
        "/npc/98/9803",
        "/npc/98/9804",
        "/npc/98/9805",
        "/npc/98/9806",
        "/npc/98/9807",
        "/npc/98/9808",
        "/npc/98/9809",
        "/npc/98/9810",
        "/npc/98/9811",
        "/npc/98/9812",
        "/npc/98/9813",
        "/npc/98/9814",
        "/npc/98/9815",
        "/npc/98/9816",
        "/npc/98/9817",
/*        "/npc/98/9818",        
        "/npc/98/9819",
        "/npc/98/9820",
        "/npc/98/9821",
        "/npc/98/9822",
        "/npc/98/9823",
        "/npc/98/9824",
        "/npc/98/9825",
        "/npc/98/9826",
        "/npc/98/9827",
        "/npc/98/9828",
        "/npc/98/9829",
*/        
});

// 变量：使命物品表

string *FileTable2 = ({
        "/item/98/9800",
        "/item/98/9801",
        "/item/98/9802",
        "/item/98/9803",
        "/item/98/9804",
        "/item/98/9805",
        "/item/98/9806",
        "/item/98/9807",
        "/item/98/9808",
        "/item/98/9809",
        "/item/98/9810",
        "/item/98/9811",
        "/item/98/9812",
        "/item/98/9813",
        "/item/98/9814",
        "/item/98/9815",
//        "/item/98/9816",
//        "/item/98/9817",
//        "/item/98/9818",
//        "/item/98/9819",
});

int sizeof_npc = sizeof(FileTable);
int sizeof_item = sizeof(FileTable2);

// 函数：获取使命人物表
string *get_task_npc( int total ) 
{ 
        string *Task = copy(FileTable);
        int size = sizeof_npc;

        if( total < 1 ) total = 1;

        while( size > total )
        {
                Task -= ({ Task[ random(size) ] });
                size --;
        }

        return Task;
}

// 函数：获取使命物品表
string *get_task_item( int total )
{ 
        string *Task = copy(FileTable2);
        int size = sizeof_item;

        if( total < 1 ) total = 1;

        while( size > total )
        {
                Task -= ({ Task[ random(size) ] });
                size --;
        }

        return Task;
}

string get_random_item_file()
{
	return FileTable2[random(sizeof(FileTable2))];
}