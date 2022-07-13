
// 函数：命令处理
int main( object me, string arg )
{
        object *item;
        int *id, *amount;
        int i, flag, flag2;

        if( !arg ) return 1;

        item = ({ 0, 0, 0, 0 });  id = ({ 0, 0, 0, 0 });  amount = ({ 0, 0, 0, 0 });

        if( sscanf( arg, "? %x# %x# %x# %x#",id[0], id[1], id[2], id[3] ) == 4 ) flag = 1;
        else if( sscanf( arg, "%x#%d %x#%d %x#%d %x#%d",
                id[0], amount[0], id[1], amount[1], id[2], amount[2], id[3], amount[3] ) == 8 ) flag = 2;
        else
        {
                notify( "Bạn muốn luyện chế đồ gì?" );
                return 1;
        }

        flag2 = 0;

        if( flag == 1 )
        {
                for( i = 0; i < 4; i ++ ) 
                {
                        if( !objectp( item[i] = present( sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4 ) ) )    // 物品是否存在？
                        {
//                              notify( "您找不到第 %d 样原料。", i + 1 );
//                              return 1;
                        }
                        if( objectp( item[i] ) && item[i]->is_poison() ) flag2 ++;
                }

                if( flag2 ) 
                        ITEM_HERB_D->make_poison_check( me, item[0], 1, item[1], 1, item[2], 1, item[3], 1 );
                else    ITEM_HERB_D->make_herb_check( me, item[0], 1, item[1], 1, item[2], 1, item[3], 1 );
        }
        else
        {
                for( i = 0; i < 4; i ++ ) if( amount[i] > 0 )
                {
                        if( !objectp( item[i] = present( sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4 ) ) )    // 物品是否存在？
                        {
                                notify( "您找不到第 %d 样原料。", i + 1 );
                                return 1;
                        }
                        if( item[i]->is_poison() ) flag2 ++;
                }

                if( flag2 ) 
                        ITEM_HERB_D->make_poison( me, item[0], amount[0], item[1], amount[1], item[2], amount[2], item[3], amount[3] );
                else    ITEM_HERB_D->make_herb( me, item[0], amount[0], item[1], amount[1], item[2], amount[2], item[3], amount[3] );
        }

        return 1;
}
