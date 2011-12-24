#include "game.h"

void bat_attack(struct creature *this, struct creature *player)
{
	printf("%s attacks you for %d damage!\n",
	       this->name, this->strength);

	player->do_hurt(player, this);
}

void die(struct creature *this)
{
	struct room *room = current_room();
	int gold = rand() % 20;
	struct item *armor = create_random_armor();

	printf("%s drops %d gold!\n", this->name, gold);
	room->gold += gold;

	printf("%s drops %s!\n", this->name, armor->name);
	room->items = armor;
}

void bat_hurt(struct creature *this, struct creature *hurter)
{
	this->health -= hurter->strength;
	if (this->health <= 0) {
		printf("%s dies!\n", this->name);
		die(this);
	}
}

struct creature *create_bat()
{
	int rc;
	struct creature *bat;

	bat = calloc(1, sizeof(struct creature));
	assert(bat);

	bat->color = B_BLUE;
	bat->symbol = 'b';

	rc = asprintf(&bat->name, "a bat");
	assert(rc != -1);
	bat->health = bat->max_health = 20;
	bat->mana = bat->max_mana = 0;
	bat->strength = 3;
	bat->intelligence = 3;
	bat->dexterity = 3;

	bat->do_hurt = bat_hurt;
	bat->attack = bat_attack;

	return bat;
}
