#ifdef FILEDIALOG_GTK

#include "SDLU.h"
#include <gtk/gtk.h>

const char*
SDLU_FileDialog(const char* title, Uint32 mode)
{
    gchar* file;
    GtkFileChooserAction action;
    GtkWidget *dialog;

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

    gtk_dialog_run(GTK_DIALOG(dialog));

    if ((file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog))))
    {
        return (const char*) file;
    }

    return NULL;
}

void
SDLU_FreeFileDialogFilename(char* filename)
{
    if (filename) g_free(filename);
}

#endif
