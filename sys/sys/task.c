#include <ansi.h>
#define TASK_TIME       1800
#define TASK_AMOUNT     16

object *TaskNPC = ({ });
object *TaskItem = ({ });

void init_task();

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：获取使命 NPC
object *get_task_npc() { return copy(TaskNPC); }

object get_task_npc_2( int id ) { return id < 1 || id > sizeof(TaskNPC) ? 0 : TaskNPC[id-1]; }

// 函数：获取使命物品
object *get_task_item() { return copy(TaskItem); }

object get_task_item_2( int id ) { return id < 1 || id > sizeof(TaskItem) ? 0 : TaskItem[id-1]; }

// 函数：构造处理
void create() { init_task(); }

// 函数：重新设定使命
void init_task()
{
        object obj;
        string *Task;
        int p, i, size;
        string result;

        remove_call_out( "init_task" );
        call_out( "init_task", ( time() + 10 + TASK_TIME ) / TASK_TIME * TASK_TIME - time() + 5 );    // 滞后 5 秒

        reset_eval_cost();

        // 清除旧的使命

        for( i = 0, size = sizeof(TaskNPC); i < size; i ++ )
        {
                if( !TaskNPC[i] ) continue;
                TaskNPC[i]->remove_from_scene();
                destruct( TaskNPC[i] );
        }
        for( i = 0, size = sizeof(TaskItem); i < size; i ++ )
        {
                if( !TaskItem[i] ) continue;
                if( !environment( TaskItem[i] ) ) 
                {
                        TaskItem[i]->remove_from_scene();
                        destruct( TaskItem[i] );
                }
        }

        // 布置新的使命

        TaskNPC = ({ });
        Task = TASK_FILE->get_task_npc( TASK_AMOUNT );

        for( i = 0, size = sizeof(Task); i < size; i ++ )
        {
                if( !( p = XY_D->get_newbie_point(IS_CHAR_BLOCK) ) ) continue;

                obj = new( Task[i] );
                obj->add_to_scene( p / 1000000+random(3)*3, ( p % 1000000 ) / 1000, p % 1000, 3 );
                TaskNPC += ({ obj });
        }

        TaskItem -= ({ 0 });
        Task = TASK_FILE->get_task_item( TASK_AMOUNT - sizeof(TaskItem) );

        for( i = 0, size = sizeof(Task); i < size; i ++ )
        {
                if( !( p = XY_D->get_newbie_point(IS_ITEM_BLOCK) ) ) continue;

                obj = new( Task[i] );
                obj->add_to_scene( p / 1000000+random(3)*3, ( p % 1000000 ) / 1000, p % 1000 );
                TaskItem += ({ obj });
        }
        result = HIY+ "Nghe nói Tân Thủ Thôn, Thanh Khê, U Cốc lại xuất hiện một nhóm nhân vật sứ mệnh đợi sự khiêu chiến của các Dũng sĩ.";
        CHAT_D->sys_channel( 0, result );   
}
