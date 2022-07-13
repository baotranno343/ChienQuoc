
#define CPP_FILE        __DIR__ "drop.cc"
#define TEXT_FILE       __DIR__ "drop.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name, task;
        string *weapon = ({ "", "", "", "", "", "", "", "", "", "" });
        string *item = ({ "", "", "", "", "", "", "", "", "", "" });
        string *result = ({ "", "", "", "", "", "", "", "", "", "" });
        int id, pic, move, level, level2, seek, money, money2, rate ;
        string sColor;
        int color;
        int *wlvl = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *alvl = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *r = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *size = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        string *item9, result_w, result_a;
        int i, j, total, count;

        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        total = sizeof(line);
        file = "make/drop.c";
        rm( LOG_DIR + file );
        count = 0;
        for( i = 0; i < total; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%s %d", 
                        name, rate ) )
                {
                	result[0] = "/make/item/itemlist"->get_item_file( name ); 
			if (count>0)
				log_file(file, "else\n");
			count += rate;
			log_file(file, sprintf("if (random<%d) item = new(%s);\n", count, result[0]) );                        
			if (result[0]=="") tell_user(me, name+" 找不到");
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
