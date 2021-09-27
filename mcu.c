#include <mcufont.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bmp.h>

typedef struct {
	char *fontname;
	char *text;
	bool justify;
	enum mf_align_t alignment;
	int width;
	int margin;
	int anchor;
	int scale;
} options_t;

typedef struct {
	options_t *options;
	uint16_t width;
	uint16_t height;
	uint16_t y;
	struct mf_font_s *font;
	uint16_t origx;
	uint16_t origy;
} state_t;

/* Callback to write to a memory buffer. */
static void pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha,
						   void *state)
{
	state_t *s = (state_t*)state;
	
	if (y < 0 || y >= s->height) return;
	if (x < 0 || x + count >= s->width) return;

	while (count--)
	{
		bmp_putpixel(x + s->origx, y + s->origy, COLOR_WHITE);
		x++;
	}
}

/* Callback to render characters. */
static uint8_t character_callback(int16_t x, int16_t y, mf_char character,
								  void *state)
{
	state_t *s = (state_t*)state;
	return mf_render_character(s->font, x, y, character, pixel_callback, state);
}

/* Callback to render lines. */
static bool line_callback(char *line, uint16_t count, void *state)
{
	state_t *s = (state_t*)state;
	
	if (s->options->justify)
	{
		mf_render_justified(s->font, s->options->anchor, s->y,
							s->width - s->options->margin * 2,
							line, count, character_callback, state);
	}
	else
	{
		mf_render_aligned(s->font, s->options->anchor, s->y,
						  s->options->alignment, line, count,
						  character_callback, state);
	}
	s->y += s->font->line_height;
	return true;
}

/* Callback to just count the lines.
 * Used to decide the image height */
int count_lines(const char *line, uint16_t count, void *state)
{
	int *linecount = (int*)state;
	(*linecount)++;
	return true;
}

int mcu_write_text(int scale, uint16_t x, uint16_t y, char *default_text)
{
	int height;
	options_t options;
	state_t state = {};
	struct mf_scaledfont_s scaledfont;

	memset(&options, 0, sizeof(options_t));
	options.fontname = "fixed_10x20";
	options.text = default_text;
	options.width = 1024;
	options.margin = 1;
	options.scale = scale;

	struct mf_font_s *fontload = mf_find_font("fixed_10x20");
	switch (scale) {
	case 2:
		mf_scale_font(&scaledfont, fontload, 2, 2);
		fontload = &scaledfont.font;
		break;
	case 1:
		mf_scale_font(&scaledfont, fontload, 1, 1);
		fontload = &scaledfont.font;
		x += 2; y += 2;
		break;
	}

	/* Count the number of lines that we need. */
	height = 0;
	mf_wordwrap(fontload, options.width - 2 * options.margin,
				options.text, count_lines, &height);
	height *= 100;
	height += 4;

	state.options = &options;
	state.width = options.width;
	state.height = height;
	state.y = -2;
	state.font = fontload;
	state.origx = x;
	state.origy = y;

	/* Render the text */
	mf_wordwrap(fontload, options.width - 2 * options.margin,
				options.text, line_callback, &state);

	return 0;
}

