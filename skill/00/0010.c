
// 函数：能否特殊指令
void can_perform( object me )
{
//        __DIR__ "00101"->can_perform(me);
//        __DIR__ "00102"->can_perform(me);
}

// 函数：删除特殊指令
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 00101 );
        send_user( me, "%c%w%w", 0x50, 0xffff, 00102 );
}