#include <mcufont.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "write_bmp.h"

typedef struct {
    const char *fontname;
    const char *filename;
    const char *text;
    bool justify;
    enum mf_align_t alignment;
    int width;
    int margin;
    int anchor;
    int scale;
} options_t;

static const char default_text[] = "الْعَرَبِيَّةالْعَرَبِيَّة";
    
/********************************************
 * Callbacks to specify rendering behaviour *
 ********************************************/

typedef struct {
    options_t *options;
    uint8_t *buffer;
    uint16_t width;
    uint16_t height;
    uint16_t y;
    const struct mf_font_s *font;
} state_t;

/* Callback to write to a memory buffer. */
static void pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha,
                           void *state)
{
    state_t *s = (state_t*)state;
    uint32_t pos;
    int16_t value;
    
    if (y < 0 || y >= s->height) return;
    if (x < 0 || x + count >= s->width) return;
    
    while (count--)
    {
        pos = (uint32_t)s->width * y + x;
        value = s->buffer[pos];
        value -= alpha;
        if (value < 0) value = 0;
        s->buffer[pos] = value;
        
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
static bool line_callback(const char *line, uint16_t count, void *state)
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
bool count_lines(const char *line, uint16_t count, void *state)
{
    int *linecount = (int*)state;
    (*linecount)++;
    return true;
}

int main(int argc, const char **argv)
{
    int height;
    const struct mf_font_s *font;
    struct mf_scaledfont_s scaledfont;
    options_t options;
    state_t state = {};

	puts(mf_get_font_list()->font->short_name);

	memset(&options, 0, sizeof(options_t));
    options.fontname = mf_get_font_list()->font->short_name;
    options.filename = "out.bmp";
    options.text = default_text;
    options.width = 200;
    options.margin = 5;
    options.scale = 1;
    
    
    font = mf_find_font("DejaVuSans12bw_bwfont");
    
    if (options.scale > 1)
    {
        mf_scale_font(&scaledfont, font, options.scale, options.scale);
        font = &scaledfont.font;
    }
    
    /* Count the number of lines that we need. */
    height = 0;
    mf_wordwrap(font, options.width - 2 * options.margin,
                options.text, count_lines, &height);
    height *= 100;
    height += 4;
    
    /* Allocate and clear the image buffer */
    state.options = &options;
    state.width = options.width;
    state.height = height;
    state.buffer = malloc(options.width * height);
    state.y = 2;
    state.font = font;
    
    /* Initialize image to white */
    memset(state.buffer, 255, options.width * height);
    
    /* Render the text */
    mf_wordwrap(font, options.width - 2 * options.margin,
                options.text, line_callback, &state);
    
    /* Write out the bitmap */
    write_bmp(options.filename, state.buffer, state.width, state.height);
    
    printf("Wrote %s\n", options.filename);
    
    free(state.buffer);
    return 0;
}

