
private
static mapping Database = ([]); // 普通数据集
private
static mapping Database2 = ([]); // 普通数据集(多层结构)

private
mapping SaveDatabase = ([]); // 存盘数据集
private
mapping SaveDbase2 = ([]); // 存盘数据集(多层结构)
private
mapping HuynhDe = ([]);
private
mixed _get(mapping db, string *key);
private
mixed _set(mapping db, string *key, mixed value);
private
int _delete(mapping db, string *key);

// -------------------------------------------------------------

// 函数：获取普通数据集
mapping get_dbase() { return copy(Database); }

// 函数：获取存盘数据集
mapping get_save_dbase() { return copy(SaveDatabase); }

// 函数：获取普通数据集(多层结构)
mapping get_dbase_2() { return copy(Database2); }

// 函数：获取存盘数据集(多层结构)
mapping get_save_dbase_2() { return copy(SaveDbase2); }

// 函数：初始普通数据集
void init_dbase() { Database = ([]); }

// 函数：初始存盘数据集
void init_save_dbase() { SaveDatabase = ([]); }

// 函数：初始普通数据集(多层结构)
void init_dbase_2() { Database2 = ([]); }

// 函数：初始存盘数据集(多层结构)
void init_save_dbase_2() { SaveDbase2 = ([]); }

// =============================================================

// 函数：获取数据集内容
mixed get(string key) { return Database[key]; }

// 函数：设置数据集内容
mixed set(string key, mixed value) { return Database[key] = value; }

// 函数：添加数据集内容
mixed add(string key, mixed value)
{
        mixed old;

        if (!(old = get(key)))
                return set(key, value);
        else
                return set(key, old + value);
}

// 函数：删除数据集内容
void delete (string key) { map_delete(Database, key); }

// -------------------------------------------------------------

// 函数：获取存盘数据集内容
mixed get_save(string key) { return SaveDatabase[key]; }

// 函数：设置存盘数据集内容
mixed set_save(string key, mixed value) { return SaveDatabase[key] = value; }

// 函数：添加存盘数据集内容
mixed add_save(string key, mixed value)
{
        mixed old;

        if (!(old = get_save(key)))
                return set_save(key, value);
        else
                return set_save(key, old + value);
}

// 函数：删除存盘数据集内容
void delete_save(string key) { map_delete(SaveDatabase, key); }

// =============================================================

// 函数：获取数据集内容(多层结构)
mixed get_2(string key)
{
        if (strchr(key, '.') == -1)
                return Database2[key];
        else
                return _get(Database2, explode(key, "."));
}

// 函数：设置数据集内容(多层结构)
mixed set_2(string key, mixed value)
{
        if (strchr(key, '.') == -1)
                return Database2[key] = value;
        else
                return _set(Database2, explode(key, "."), value);
}

// 函数：添加数据集内容(多层结构)
mixed add_2(string key, mixed value)
{
        mixed old;

        if (!(old = get_2(key)))
                return set_2(key, value);
        else
                return set_2(key, old + value);
}

// 函数：删除数据集内容(多层结构)
void delete_2(string key)
{
        if (strchr(key, '.') == -1)
                map_delete(Database2, key);
        else
                _delete(Database2, explode(key, "."));
}

// -------------------------------------------------------------

// 函数：获取存盘数据集内容(多层结构)
mixed get_save_2(string key)
{
        if (strchr(key, '.') == -1)
                return SaveDbase2[key];
        else
                return _get(SaveDbase2, explode(key, "."));
}

// 函数：设置存盘数据集内容(多层结构)
mixed set_save_2(string key, mixed value)
{
        if (strchr(key, '.') == -1)
                return SaveDbase2[key] = value;
        else
                return _set(SaveDbase2, explode(key, "."), value);
}

// 函数：添加存盘数据集内容(多层结构)
mixed add_save_2(string key, mixed value)
{
        mixed old;

        if (!(old = get_save_2(key)))
                return set_save_2(key, value);
        else
                return set_save_2(key, old + value);
}

// 函数：删除存盘数据集内容(多层结构)
void delete_save_2(string key)
{
        if (strchr(key, '.') == -1)
                map_delete(SaveDbase2, key);
        else
                _delete(SaveDbase2, explode(key, "."));
}
// -------------------------------------------------------------

// 函数：获取存盘数据集内容(多层结构)
mixed get_huynhde(string key)
{
        if (strchr(key, '.') == -1)
                return HuynhDe[key];
        else
                return _get(HuynhDe, explode(key, "."));
}

// 函数：设置存盘数据集内容(多层结构)
mixed set_huynhde(string key, mixed value)
{
        if (strchr(key, '.') == -1)
                return HuynhDe[key] = value;
        else
                return _set(HuynhDe, explode(key, "."), value);
}

// 函数：添加存盘数据集内容(多层结构)
mixed add_huynhde(string key, mixed value)
{
        mixed old;

        if (!(old = get_huynhde(key)))
                return set_huynhde(key, value);
        else
                return set_huynhde(key, old + value);
}

// 函数：删除存盘数据集内容(多层结构)
void delete_huynhde(string key)
{
        if (strchr(key, '.') == -1)
                map_delete(HuynhDe, key);
        else
                _delete(HuynhDe, explode(key, "."));
}
// -------------------------------------------------------------

// 函数：获取映射变量 db 中属性 key 的内容
private
mixed _get(mapping db, string *key)
{
        mixed result = db;
        int i, size;

        for (i = 0, size = sizeof(key); i < size; i++)
        {
                result = result[key[i]];
                if (undefinedp(result) || !mapp(result))
                        break;
        }
        return result;
}

// 函数：设置映射变量 db 中属性 key 的内容
private
mixed _set(mapping db, string *key, mixed value)
{
        if (sizeof(key) == 0)
                return db = value;
        else if (sizeof(key) == 1)
                return db[key[0]] = value;
        else if (undefinedp(db[key[0]]) || !mapp(db[key[0]]))
                db[key[0]] = ([key[1]:0]);

        return _set(db[key[0]], key[1.. < 1], value);
}

// 函数：删除映射变量 db 中属性 key 的内容
private
int _delete(mapping db, string *key)
{
        int size = sizeof(key);

        if (size == 0)
        {
                db = 0;
                return 1;
        }
        else if (size == 1)
        {
                map_delete(db, key[0]);
                if (sizeof(db) == 0)
                        db = 0;
                return 1;
        }
        else if (undefinedp(db[key[0]]) || !mapp(db[key[0]]))
                return 0;

        return _delete(db[key[0]], key[1.. < 1]);
}
