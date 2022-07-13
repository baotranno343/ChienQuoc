
#include <task.h>

private int *Legend = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, });    // 传奇记录表(主线任务)

private int *Legend2 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, });    // 传奇记录表(故事任务)

private int *Legend3 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, });    // 传奇记录表(其它事件)

private mapping mpTask = ([ ]);                 // 任务数据集
private mapping mpQuest = ([ ]);                // 任务数据集

// =============================================================

// 函数：获取传奇记录
int *get_legend_dbase() { return copy(Legend); }
int *get_legend_2_dbase() { return copy(Legend2); }
int *get_legend_3_dbase() { return copy(Legend3); }

// 函数：初始传奇记录
int *init_legend_dbase() 
{ 
        return Legend = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }); 
}

int *init_legend_2_dbase()
{ 
        return Legend2 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }); 
}

int *init_legend_3_dbase()
{ 
        return Legend3 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }); 
}

// -------------------------------------------------------------

// 函数：初始传奇记录
int init_legend_1( int key, int flag )
{
        key = range_value(key, 0, 49);
        return Legend[key] = flag;
}

int init_legend_2( int key, int flag )
{
        key = range_value(key, 0, 49);
        return Legend2[key] = flag;
}

int init_legend_3( int key, int flag )
{
        key = range_value(key, 0, 49);
        return Legend3[key] = flag;
}

int init_legend( int key, int point )
{	
	if ( key < 50 )
		return init_legend_1(key,point);
	else if ( key < 100 )
		return init_legend_2(key-50,point);
	else
		return init_legend_3(key-100,point);
}
//发送标记到客户端
void send_legend()
{
	int i,size;
	string cTmp;
	int *nTmp;
	object me = this_object();
	cTmp = "%c%c";
	nTmp = ({0x3d, 32});
	for(i=0,size=sizeof(Legend);i<size;i++)
	{
		cTmp += "%d";
		nTmp += ({Legend[i]});	
	}
	for(i=0,size=sizeof(Legend2);i<size;i++)
	{
		cTmp += "%d";
		nTmp += ({Legend2[i]});	
	}	
	send_user(me,cTmp,nTmp);
}

// 函数：获取传奇记录
int get_legend_1( int key, int point )
{	
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);        
        return Legend[key] & ( 1 << point );
}

int get_legend_2( int key, int point )
{
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        return Legend2[key] & ( 1 << point );
}

int get_legend_3( int key, int point )
{
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        return Legend3[key] & ( 1 << point );
}

int get_legend( int key, int point )
{	
	if ( key < 50 )
		return get_legend_1(key,point);
	else if ( key < 100 )
		return get_legend_2(key-50,point);
	else
		return get_legend_3(key-100,point);
}
// 函数：设置传奇记录
int set_legend_1( int key, int point )
{
	object me = this_object();
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        send_user(me, "%c%c%d%c", 0x3d, 33, key*32+point, 1);
        return Legend[key] |= ( 1 << point );
}

int set_legend_2( int key, int point )
{
	object me = this_object();
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        send_user(me, "%c%c%d%c", 0x3d, 33, (50+key)*32+point, 1);
        return Legend2[key] |= ( 1 << point );
}

int set_legend_3( int key, int point )
{
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        return Legend3[key] |= ( 1 << point );
}

int set_legend( int key, int point )
{	
	if ( key < 50 )
		return set_legend_1(key,point);
	else if ( key < 100 )
		return set_legend_2(key-50,point);
	else
		return set_legend_3(key-100,point);
}
// 函数：删除传奇记录
int remove_legend_1( int key, int point )
{
	object me = this_object();
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        send_user(me, "%c%c%d%c", 0x3d, 33, key*32+point, 0);
        return Legend[key] &= ~( 1 << point );
}

int remove_legend_2( int key, int point )
{
	object me = this_object();
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        send_user(me, "%c%c%d%c", 0x3d, 33, (50+key)*32+point, 0);
        return Legend2[key] &= ~( 1 << point );
}

int remove_legend_3( int key, int point )
{
        key = range_value(key, 0, 49);
        point = range_value(point, 1, 30);
        return Legend3[key] &= ~( 1 << point );
}

int remove_legend( int key, int point )
{	
	if ( key < 50 )
		return remove_legend_1(key,point);
	else if ( key < 100 )
		return remove_legend_2(key-50,point);
	else
		return remove_legend_3(key-100,point);
}
// =============================================================

// 函数：获取任务数据集
mapping get_task_dbase() { return copy(mpTask); }

// 函数：获取任务数据集
mapping get_quest_dbase() { return copy(mpQuest); }

// 函数：初始任务数据集
void init_task_dbase() { mpTask = ([ ]); }

// 函数：初始任务数据集
void init_quest_dbase() { mpQuest = ([ ]); }

// -------------------------------------------------------------

// 函数：获取任务数据集
mixed get_task( string key ) { return mpTask[key]; }

// 函数：设置任务数据集
mixed set_task( string key, mixed value ) { return mpTask[key] = value; }

// 函数：添加任务数据集
mixed add_task( string key, mixed value )
{
        mixed old;

        if( !( old = get_task(key) ) ) 
                return set_task(key, value);
        else    return set_task(key, old + value);
}

// 函数：删除任务数据集
void delete_task( string key ) { map_delete(mpTask, key); }

// -------------------------------------------------------------

// 函数：获取任务数据集
mixed get_quest( string key ) { return mpQuest[key]; }

// 函数：设置任务数据集
mixed set_quest( string key, mixed value ) { return mpQuest[key] = value; }

// 函数：添加任务数据集
mixed add_quest( string key, mixed value )
{
        mixed old;

        if( !( old = get_quest(key) ) ) 
                return set_quest(key, value);
        else    return set_quest(key, old + value);
}

// 函数：删除任务数据集
void delete_quest( string key ) { map_delete(mpQuest, key); }
