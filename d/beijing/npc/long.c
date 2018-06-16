//Cracked by Roath

inherit NPC;

void create()
{
	seteuid(getuid());

	set_name("龙啸天", ({"long xiaotian",
			     "long",
			     "xiaotian",
			     "zongguan"}));
	set("gender", "男性");
	set("age", 40);
	set("long", "带刀侍卫副统领");
	set("attitude","heroism");
	set("generation",0);
	set("winner","none");

	set("str",30);
	set("con",29);
	set("int",25);
	set("dex",30);
	set("max_qi",800);
	set("eff_qi",800);
	set("qi",80);
	set("max_jing",300);
	set("jing",300);
	set("neili",400);
	set("max_neili",400);
	set("shen_type",1);
	set("no_clean_up",1);
	set("combat_exp",100000);

	set_skill("force",100);
	set_skill("unarmed",100);
	set_skill("dodge",90);
	set_skill("parry",90);

	setup();
}