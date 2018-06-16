//Cracked by Roath
// xiakedao/xkx18.c
// modified by aln 5 / 98

inherit __DIR__"no_pk_room";
int flag = 10;

void create()
{
        set("short", "石室");
        set("long", @LONG
石室之中平平无奇，也是数人切磋武功，或指点石壁(wall)相互
辩论。偶尔众人默然，便听到头顶传来潺潺的水声，想必此处乃是溪
流之下。脚下石砖上遍布青苔，若不小心便要滑倒。
LONG );

      set("exits", ([
		"north" : __DIR__"xiakexing5",
      ]));
	set("item_desc",([
	    "wall" : "
此墙上「邯郸先震惊」几个大字刻在左侧直排。右面图案甚为奇特，
乃是一只巨足踏在平地，别无他物。巨足之上肌肉的纹理有百余条之
多，相互交错，倒也活灵活现。底部有注：壮于趾，征凶，有孚。\n",
	]));

	set("indoors", "xiakedao" );
	set("cost", 0);
	setup();
}
void init()
{
        ::init();
	add_action("do_study", "study");
}

#include "/d/xiakedao/xkx.h"
