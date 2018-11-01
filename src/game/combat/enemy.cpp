#include "enemy.hpp"

Enemy::Enemy() :
	Unit(UnitType::ENEMY),
	sprite("res/assets/WyvernFighter_Sprite.png")
{
	sprite.setSize(sprite_width, sprite_height);

}

Enemy::~Enemy()
{
}

void Enemy::render()
{

	if (state != UnitState::DEAD) {
		shadow.render();

		sprite.setPos(screenPosition.x(), screenPosition.y());
		sprite.render();
	}

	drawHealth();

}

void Enemy::drawHealth() {
	// ScreenCoord pos = screenPosition + ScreenCoord((tile_width - sprite_width) / 2, (tile_height - sprite_height) / 2);
	ScreenCoord pos = screenPosition;
	pos.x() += (sprite_width - tile_width) / 2;
	int healthBarWidth = tile_width;
	int tick = lerp(0, healthBarWidth, static_cast<float>(health) / static_cast<float>(maxHealth));
	// TODO: Use rectangle rendering (implement in engine)
	for (int i = 0; i < 10; ++i) {
		Core::Renderer::drawLine(pos + ScreenCoord(0, i), pos + ScreenCoord(tick, i), Colour(0.0f, 1.0f, 0.0f));
		Core::Renderer::drawLine(pos + ScreenCoord(tick, i), pos + ScreenCoord(healthBarWidth, i), Colour(1.0f, 0.0f, 0.0f));
	}
	Core::Renderer::drawLine(pos + ScreenCoord(0, 0), pos + ScreenCoord(healthBarWidth, 0), Colour(0.0f, 0.0f, 0.0f));
	Core::Renderer::drawLine(pos + ScreenCoord(0, 0), pos + ScreenCoord(0, 10), Colour(0.0f, 0.0f, 0.0f));
	Core::Renderer::drawLine(pos + ScreenCoord(healthBarWidth, 0), pos + ScreenCoord(healthBarWidth, 10), Colour(0.0f, 0.0f, 0.0f));
	Core::Renderer::drawLine(pos + ScreenCoord(0, 10), pos + ScreenCoord(healthBarWidth, 10), Colour(0.0f, 0.0f, 0.0f));
	
}

void Enemy::update(int delta) {
	switch (state) {
	case UnitState::ATTACK: {
		if (compareCounter(ENEMY_DEFAULT_ATTACK_COUNTER)) {
			state = UnitState::DONE;
		} else {
			incrementCounter();
		}
	} break;
	default: {
		// do nothing
	} break;
	}
}

void Enemy::takeTurn() {
	int key = rand() % 2;
	switch (key) {
	case 0: {
		// do the action here
		// attack1.attack(to, combat);
		state = UnitState::ATTACK;
		startCounter();
	} break;
	case 1: {
		// do the action here
		// attack2.attack(to, combat);
		state = UnitState::ATTACK;
		startCounter();
	} break;
	default: {
		// do nothing
	} break;
	}
}

