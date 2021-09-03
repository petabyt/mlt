#include <dryos.h>
#include <module.h>
#include <menu.h>
#include <config.h>
#include <console.h>
#include <bmp.h>
#include <patch.h>

void strcat(char *a, char *b);

/* Selected language to translate to */
#define MLT_LANG "es"

/* Expected to be bigger than bmp_puts input */
#define MLT_MAX_STRING 128

char *current_translation = 0;
uint32_t size = 0;
char buffer[MLT_MAX_STRING];

void translate(char output[], char input[])
{
    if (!strcmp(MLT_LANG, "en"))
    {
        return;
    }

    /* Open and read translation file if
    not already read */
    if (current_translation == 0)
    {
        char file[16] = "ML/";
        strcat(file, MLT_LANG);

        FIO_GetFileSize(file, &size);
        current_translation = fio_malloc(size);

        FILE *f = FIO_OpenFile(file, O_RDWR | O_SYNC);
        if (!f)
        {
            current_translation = 0;
            return;
        }

        FIO_ReadFile(f, current_translation, size);
    }

    if (!current_translation)
    {
        return;
    }

    strcpy(output, input);

    char eng[MLT_MAX_STRING];
    char new[MLT_MAX_STRING];

    int i = 0;
    int c = 0;

    while (1)
    {
        if (i >= size - 2)
        {
            break;
        }

        /* Get english string */
        c = 0;
        while (current_translation[i] != '|')
        {
            eng[c] = current_translation[i];
            c++;
            i++;
        }

        eng[c] = '\0';

        i++; /* skip '|' */

        /* Get new translation */
        c = 0;
        while (current_translation[i] != '\n')
        {
            new[c] = current_translation[i];
            c++;
            i++;
        }

        new[c] = '\0';

        /* Finish remaining newlines */
        while (current_translation[i] == '\n')
        {
            i++;
        }

        /* Skip if not equal */
        if (strcmp(input, eng))
        {
            continue;
        }

        strcpy(output, new);
    }
}

void hijack(uint32_t* regs, uint32_t* stack, uint32_t pc)
{
    translate(buffer, regs[3]);
    regs[3] = buffer;
}

static void translate_task()
{
    /* ... */
}

static struct menu_entry translate_menu[] =
{
    {
        .name       = "Magic Lantern Translation",
        .select     = run_in_separate_task,
        .priv       = translate_task,
        .help       = "Translate the Magic Lantern Menus.",
    },
};

static unsigned int translate_init()
{
    menu_add("Translation Settings", translate_menu, COUNT(translate_menu));

    printf("Applying bmp_puts translation patch...");
    uint32_t *func = (uint32_t*)bmp_puts;
    patch_hook_function(bmp_puts, *func, hijack, "Translation patch");

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