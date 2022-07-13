
private static mapping mpPawn = ([ ]);          // 典当数据集

private static mapping mpTime = ([ ]);          // 时间数据集(警告：不存盘！)

private mixed _get( mapping db, string *key );
private mixed _set( mapping db, string *key, mixed value );
private int _delete( mapping db, string *key );

// =============================================================

// 函数：获取典当数据集
mapping get_pawn_dbase() { return copy(mpPawn); }

// 函数：初始典当数据集
void init_pawn_dbase() { mpPawn = ([ ]); }

// -------------------------------------------------------------

// 函数：获取典当数据集
mixed get_pawn( string key ) 
{ 
        if( strchr( key, '.' ) == -1 ) return mpPawn[key];
        else return _get( mpPawn, explode( key, "." ) );
}

// 函数：设置典当数据集
mixed set_pawn( string key, mixed value ) 
{ 
        if( strchr( key, '.' ) == -1 ) return mpPawn[key] = value;
        else return _set( mpPawn, explode( key, "." ), value );
}

// 函数：添加典当数据集
mixed add_pawn( string key, mixed value )
{
        mixed old;

        if( !( old = get_pawn(key) ) ) 
                return set_pawn(key, value);
        else    return set_pawn(key, old + value);
}

// 函数：删除典当数据集
void delete_pawn( string key ) 
{ 
        if( strchr( key, '.' ) == -1 ) map_delete(mpPawn, key);
        else _delete( mpPawn, explode( key, "." ) );
}

// =============================================================

// 函数：获取时间数据集
mapping get_time_dbase() { return copy(mpTime); }

// 函数：初始时间数据集
void init_time_dbase() { mpTime = ([ ]); }

// -------------------------------------------------------------

// 函数：获取时间数据集
mixed get_time( string key ) { return mpTime[key]; }

// 函数：设置时间数据集
mixed set_time( string key, mixed value ) { return mpTime[key] = value; }

// 函数：添加时间数据集
mixed add_time( string key, mixed value )
{
        mixed old;

        if( !( old = get_time(key) ) ) 
                return set_time(key, value);
        else    return set_time(key, old + value);
}

// 函数：删除时间数据集
void delete_time( string key ) { map_delete(mpTime, key); }
