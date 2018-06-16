//Cracked by Roath
// Room: /d/beijing/west/youanmenlou.c

inherit ROOM;

void create()
{
	set("short", "右安门城楼");
	set("long", @LONG
这是右安门城门上的望楼，一队队壮健的守城军丁盔甲鲜
明，手持大刀长矛，强弓利箭，警惕的注视着城下过望行人；
城门两边是长长的北京外城墙。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"chengqiang6",
  "down" : __DIR__"youanmen",
  "east" : __DIR__"chengqiang7",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
