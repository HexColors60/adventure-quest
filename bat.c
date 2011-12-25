#include "game.h"

void bat_attack(struct creature *this, struct creature *player)
{
	printf("%s attacks you for %d damage!\n",
	       this->name, this->strength);

	player->do_hurt(player, this);
}

void bat_die(struct creature *this)
{
	struct room *room = current_room();
	int gold = p(90) ? rand() % 10 : 0;
	struct item *armor = p(10) ? create_random_armor() : NULL;
	struct item *potion = p(50) ? create_random_potion() : NULL;

	if (gold) {
		printf("%s drops %d gold!\n", this->name, gold);
		room->gold += gold;
	}

	if (armor) {
		printf("%s drops %s!\n", this->name, armor->name);
		list_add_tail(&armor->list, &room->items);
	}

	if (potion) {
		printf("%s drops %s!\n", this->name, potion->name);
		list_add_tail(&potion->list, &room->items);
	}
}

void bat_hurt(struct creature *this, struct creature *hurter)
{
	this->health -= hurter->strength;
	if (this->health <= 0) {
		printf("%s dies!\n", this->name);
		this->die(this);
		hurter->give_experience(hurter, this->experience);
	}
}

struct creature *create_bat()
{
	int rc;
	struct creature *bat;

	bat = calloc(1, sizeof(*bat));
	assert(bat);

	bat->color = BLUE;
	bat->symbol = 'b';

	rc = asprintf(&bat->name, "a bat");
	assert(rc != -1);
	bat->health = bat->max_health = 20;
	bat->mana = bat->max_mana = 0;
	bat->strength = 3;
	bat->intelligence = 3;
	bat->dexterity = 3;
	bat->level = 1;
	bat->experience = 20;

	bat->do_hurt = bat_hurt;
	bat->attack = bat_attack;
	bat->die = bat_die;

	return bat;
}

