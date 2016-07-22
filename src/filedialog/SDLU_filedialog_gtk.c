#ifdef FILEDIALOG_GTK

#include "SDLU.h"
#include <gtk/gtk.h>

const char*
GTK_FileDialog(const char* title, Uint32 mode)
{
    gchar* file;
    GtkFileChooserAction action;
    GtkWidget *dialog;
    int response;

    /* init gtk */
    gtk_init(0, NULL);

    if (mode & SDLU_FILEDIALOG_OPEN) {
        action = GTK_FILE_CHOOSER_ACTION_OPEN;
    } else if (mode & SDLU_FILEDIALOG_SAVE) {
        action = GTK_FILE_CHOOSER_ACTION_SAVE;
    } else if (mode & SDLU_FILEDIALOG_OPENDIR) {
        action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    } else {
        /* default mode is to select a file */
        action = SDLU_FILEDIALOG_OPEN;
    }

    dialog = gtk_file_chooser_dialog_new(title, NULL, action, "OK", "Cancel", NULL);

    response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response != GTK_RESPONSE_NONE) {
        file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (file) {
            char* ret = SDL_strdup(file);
            g_free(file);
            return ret;
        }
    }

    gtk_widget_destroy(dialog);

    return NULL;
}

void
GTK_FreeFileDialogFilename(char* filename)
{
    if (filename) SDL_free(filename);
}

const wchar_t*
GTK_FileDialogW(const wchar_t* title, Uint32 mode)
{
    char *mb_title = SDL_malloc(SDL_wcslen(title) * sizeof(char));
    wcstombs(mb_title, title, SDL_wcslen(title));

    char* tmp = (char*)GTK_FileDialog(mb_title, mode);

    wchar_t *ret = SDL_malloc(SDL_strlen(tmp) * sizeof(wchar_t));
    mbstowcs(ret, tmp, SDL_strlen(tmp));

    SDL_free(mb_title);
    SDL_free(tmp);

    return ret;
}

void
GTK_FreeFileDialogFilenameW(wchar_t *filename)
{
    if (filename) SDL_free(filename);
}

#endif
