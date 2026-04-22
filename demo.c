// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"
#include "stdlib.h"
#include "string.h"

static int px = 0;
static int py = 0;

static SpriteGrid world;

void GK_init() {

	set_clear_color(10, 40, 130);

	world.w = 16;
	world.h = 16;
	world.sprites = malloc(sizeof(sprite_t) * world.w * world.h);

	for (int i = 0; i < world.w * world.h; i++) {

		if (ITOY(world, i) < 4 || ITOY(world, i) > 12 || ITOX(world, i) < 4 || ITOX(world, i)> 12)
			world.sprites[i] = 12;
		else
			world.sprites[i] = 30;
	}

	// prettify dirt-grass boundary
	for (int i = 0; i < world.w * world.h; i++) {

		if (world.sprites[i] != 30)
			continue;

		world.sprites[i] = 30
			+ (world.sprites[i + XYTOI(world,  1,  0)] == 12 ?   1 : 0)	// right
			+ (world.sprites[i + XYTOI(world, -1,  0)] == 12 ?  -1 : 0)	// left
			+ (world.sprites[i + XYTOI(world,  0,  1)] == 12 ?  16 : 0)	// down
			+ (world.sprites[i + XYTOI(world,  0, -1)] == 12 ? -16 : 0);// up
	}
}

void GK_frame(const Input *input) {

	if (input->up)
		py--;

	if (input->down)
		py++;

	if (input->left)
		px--;

	if (input->right)
		px++;

	draw_sprite_grid(&world, (WIDTH - SPR_DIM) / 2 - px, (HEIGHT - SPR_DIM) / 2 - py);
	draw_sprite(0, (WIDTH - SPR_DIM) / 2, (HEIGHT - SPR_DIM) / 2, 0);
}