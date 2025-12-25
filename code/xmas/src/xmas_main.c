/**************************************************************************
 --                     STM32N6 Santa and snow
 --
 --           Copyright (C) 2025 By Ulrik Hørlyk Hjort
 --
 --  This Program is Free Software; You Can Redistribute It and/or
 --  Modify It Under The Terms of The GNU General Public License
 --  As Published By The Free Software Foundation; Either Version 2
 --  of The License, or (at Your Option) Any Later Version.
 --
 --  This Program is Distributed in The Hope That It Will Be Useful,
 --  But WITHOUT ANY WARRANTY; Without Even The Implied Warranty of
 --  MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See The
 --  GNU General Public License for More Details.
 --
 -- You Should Have Received A Copy of The GNU General Public License
 -- Along with This Program; if not, See <Http://Www.Gnu.Org/Licenses/>.
 ***************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "tree.h"
#include "snow.h"
#include "santas.h"
#include "display.h"

#define SNOW_DEPTH 10

#define GREEN 0x07E0
#define WHITE 0xFFFFFF 
#define BLACK 0x000000

#define MAX_SNOW 100

#define delay_ms HAL_Delay

extern void draw_xbm_pixmap(uint32_t x0, uint32_t y0, uint8_t *px_buf,
		uint32_t height, uint32_t width, uint32_t color);
extern int32_t random_range(int32_t limit);
extern uint32_t random32(void);

uint32_t SNOW = 4;
uint32_t TREES = 4;

struct Snow {
	int16_t x;
	int16_t y;
	int speed_x;
	int speed_y;
	uint8_t *pixmap;
	int16_t w;
	int16_t h;
} snow[MAX_SNOW];

#define SANTAS 4

struct Santa {
	int16_t w;
	int16_t h;
	uint32_t *pixmap;
} santa[SANTAS] = { { SANTA1_WIDTH, SANTA1_HEIGHT, santa1 }, { SANTA2_WIDTH,
		SANTA2_HEIGHT, santa2 }, { SANTA3_WIDTH, SANTA3_HEIGHT, santa3 }, {
		SANTA4_WIDTH, SANTA4_HEIGHT, santa4 }, };

#define MAX_TREES 100

struct Tree {
	int16_t x;
	int16_t y;
} trees[MAX_TREES];

void draw_trees() {
	for (size_t i = 0; i < TREES; i++) {
		draw_xbm_pixmap(trees[i].x, trees[i].y, tree, TREE_HEIGHT, TREE_WIDTH,
				GREEN);
	}

}

void draw_snow() {

	for (size_t i = 0; i < SNOW; i++) {
		if (snow[i].y < LCD_HEIGHT - SNOW_DEPTH) { // Add some snow in the bottom of the screen
			// Delete current snow flake (draw it in black). Not deleted if at screen bottom
			draw_xbm_pixmap(snow[i].x, snow[i].y, snow[i].pixmap, snow[i].w,
					snow[i].h, BLACK);
		}

		// Add some randomness ('wind' )to the snow falling path
		// so it just don't fall down straight
		snow[i].y = 1 + (snow[i].y + random_range(snow[i].speed_y));
		snow[i].x = snow[i].x + random_range(snow[i].speed_x * 2);

		// Keep snow inside screen and restat snowflake if outside
		if ((snow[i].x < 0) || (snow[i].x > LCD_WIDTH - 1)
				|| (snow[i].y > LCD_HEIGHT - 1)) {
			snow[i].x = random32() % LCD_WIDTH - 1;
			snow[i].y = 0;

		}
		if (snow[i].y < 0) {
			snow[i].y = 0;
		}
	}
	for (size_t i = 0; i < SNOW; i++) {
		draw_xbm_pixmap(snow[i].x, snow[i].y, snow[i].pixmap, snow[i].w, snow[i].h,
				WHITE);
	}

}

void init_trees(size_t number_of_trees) {
	for (size_t i = 0; i < number_of_trees; i++) {
		trees[i].x = random32() % LCD_WIDTH;
		trees[i].y = random32() % LCD_HEIGHT;
	}
	TREES = number_of_trees;
}

void init_snow(size_t number_of_snowflakes) {
	// Create snowflakes. All snow flakes are keept in a
	// list to keep track of position etc. 
	for (size_t i = 0; i < number_of_snowflakes; i++) {
		snow[i].x = random32() % 400;
		snow[i].y = random32() % 300;
		snow[i].speed_x = random32() % 5;
		snow[i].speed_y = random32() % 3;

		uint32_t snowflake_idx = random32() % SNOWFLAKE_PIXMAPS;
		snow[i].w = snowflake_pixmaps[snowflake_idx].width;
		snow[i].h = snowflake_pixmaps[snowflake_idx].height;
		snow[i].pixmap = snowflake_pixmaps[snowflake_idx].pixmap;
	}
	SNOW = number_of_snowflakes;
}

#define SANTA_START_X 100
#define SANTA_START_Y 100

uint32_t old_x = SANTA_START_X;
uint32_t old_y = SANTA_START_Y;

void draw_santa(uint32_t px, uint32_t py) {

	static size_t s = 0;

	// Clear Santa
	uint16_t w = santa[s].w;
	if (old_x + santa[s].w > LCD_WIDTH - 1)
		w = LCD_WIDTH - old_x;

	lcd_clear_area(old_x, old_y, w, santa[s].h, 0x000000);
	old_x = px;
	old_y = py;

	// Draw Santa
	w = santa[s].w;
	uint16_t w_full = w;
	if (px + santa[s].w > LCD_WIDTH - 1)
		w = LCD_WIDTH - px;

	for (size_t h = 0; h < santa[s].h; h++) {
		lcd_draw_area(px, py + h, w, 1, santa[s].pixmap + (w_full * h));
	}

	s = (s + 1) % 4;
}

uint32_t s_x = 100;
uint32_t s_y = 50;

void run_xmas() {
	lcd_clear(0x000000, LCD_WIDTH, LCD_HEIGHT);
	init_snow(20);
	init_trees(10);

	while (1) {
		draw_snow();
		draw_trees();
		draw_santa(s_x, s_y);
		s_x = (s_x + 1) % LCD_WIDTH;
		HAL_Delay(50);
	}
}
