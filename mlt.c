#include <dryos.h>
#include <module.h>
#include <menu.h>
#include <config.h>
#include <console.h>
#include <bmp.h>
#include <patch.h>
#include <string.h>

CONFIG_INT("mlt.toload", mlt_toload, 1);

/* Selected language to translate to */
#define MLT_LANG "mlt_es"

/* Expected to be bigger than bmp_puts input */
#define MLT_MAX_STRING 128

char *current_translation = 0;
int no_file = 0;
uint32_t size = 0;

char buffer[MLT_MAX_STRING];

void translate(char output[], char input[])
{
    if (!strcmp(MLT_LANG, "mlt_en"))
    {
        return;
    }

    if (current_translation == 0)
    {
        return;
    }

    char eng[MLT_MAX_STRING];
    char new[MLT_MAX_STRING];

    unsigned int i = 0;
    while (i <= size - 2)
    {
        /* Allow "comments" at the beginning of the
        file. Could include Author, contributors, etc. */
        if (i == '#')
        {
            while (current_translation[i] != '\n')
            {
                i++;
            }

            while (current_translation[i] == '\n')
            {
                i++;
            }

            continue;
        }

        /* Get english string */
        int c = 0;
        while (current_translation[i] != '|')
        {
            eng[c++] = current_translation[i++];
        }

        eng[c] = '\0';

        i++; /* skip '|' */

        /* Get the "translated" string */
        c = 0;
        while (current_translation[i] != '\n')
        {
            new[c++] = current_translation[i++];
        }

        new[c] = '\0';

        /* Finish remaining newlines, if any */
        while (current_translation[i] == '\n')
        {
            i++;
        }

        if (strcmp(input, eng))
        {
            continue;
        }
        else
        {
            strcpy(output, new);
            return;
        }
    }

    /* If all fails, copy input string */
    strcpy(output, input);
}

void hijack(uint32_t* regs, uint32_t* stack, uint32_t pc)
{
    translate(buffer, (char*)regs[3]);
    regs[3] = (uint32_t)buffer;
}

static void translate_task()
{
    /* ... */
}

static struct menu_entry translate_menu[] =
{
    {
        .name = "Magic Lantern Translation",
        .select = menu_open_submenu,
        .submenu_width = 700,
        .help = "Language / Idioma / Langue / Sprache",
        .children = (struct menu_entry[])
        {
            {
                .name = "Status",
                .priv = &mlt_toload,
                .max = 1,
                .help = "Turn OFF / Apagar / Eteindre / Schalte aus",
            },
            MENU_EOL,
        },
    },
};

static unsigned int translate_init()
{
    menu_add("Help", translate_menu, COUNT(translate_menu));

    if (mlt_toload)
    {
        char file[8] = "ML/";
        strcat(file, MLT_LANG);

        FIO_GetFileSize(file, &size);
        current_translation = fio_malloc(size);

        FILE *f = FIO_OpenFile(file, O_RDWR | O_SYNC);
        if (!f)
        {
            printf("MLT Could not find ML/%s!\n", MLT_LANG);
            return 0;
        }

        FIO_ReadFile(f, current_translation, size);

        printf("Applying bmp_puts translation patch...\n");
        uint32_t *func = (uint32_t*)bmp_puts;
        patch_hook_function((uintptr_t)bmp_puts, *func, hijack, "Translation patch");
    }

    return 0;
}

static unsigned int translate_deinit()
{
    return 0;
}

MODULE_INFO_START()
MODULE_INIT(translate_init)
MODULE_DEINIT(translate_deinit)
MODULE_INFO_END()

MODULE_CONFIGS_START()
MODULE_CONFIG(mlt_toload)
MODULE_CONFIGS_END()
