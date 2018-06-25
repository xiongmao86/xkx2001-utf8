// Change by Server
// help.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

string *default_search = DEFAULT_MAP_SEARCH_PATHS;

int main(object me, string arg)
{
	int i;
	string file, *search;

    // mine
    string map_name;

    if( !arg ) map_name = "map";
    else map_name = "map_" + arg;

	// Finally, search the default search paths.
	if( pointerp(default_search) ) {
		i = sizeof(default_search);
		while(i--) if( file_size(default_search[i] + map_name)>0 ) {
			me->start_more( read_file(default_search[i] + map_name) );
			return 1;
		}
	}

	return notify_fail("没有找到这张地图。\n");
}

int help(object me)
{
	write(@HELP
指令格式：map <主题>              例如：> map all

这个指令显示某个名称的地图，若是不指定地图，则提供地图列表。
map all 显示总地图。
HELP
	);
	return 1;
}

