#include "../common/common.h"
#include "support.h"


GtkWidget* lookup_widget(GtkWidget *widget, const gchar *widget_name)
{
        GtkWidget *parent, *found_widget;

        for (;;)
        {
                if (GTK_IS_MENU (widget))
                        parent = gtk_menu_get_attach_widget (GTK_MENU (widget));
                else
                        parent = widget->parent;
                if (!parent)
                        parent = gtk_object_get_data (GTK_OBJECT (widget), "GladeParentKey");
                if (parent == NULL)
                        break;
                widget = parent;
        }

        found_widget = (GtkWidget*) gtk_object_get_data (GTK_OBJECT (widget),
                        widget_name);
        if (!found_widget)
                g_warning ("Widget not found: %s", widget_name);
        return found_widget;
}

/* This is an internally used function to create pixmaps. */
GtkWidget* create_pixmap(GtkWidget *widget, const gchar *filename)
{
        GtkWidget *pixmap;
        gchar *pathname;

        if (!filename || !filename[0])
                return gtk_image_new ();

        pathname = gnome_program_locate_file (NULL, GNOME_FILE_DOMAIN_APP_PIXMAP,
                                              filename, TRUE, NULL);
        if (!pathname)
        {
                g_warning (_("Couldn't find pixmap file: %s"), filename);
                return gtk_image_new ();
        }

        pixmap = gtk_image_new_from_file (pathname);
        g_free (pathname);
        return pixmap;
}

/* This is an internally used function to create pixmaps. */
GdkPixbuf* create_pixbuf(const gchar *filename)
{
        gchar *pathname = NULL;
        GdkPixbuf *pixbuf;
        GError *error = NULL;

        if (!filename || !filename[0])
                return NULL;

        pathname = gnome_program_locate_file (NULL, GNOME_FILE_DOMAIN_APP_PIXMAP,
                                              filename, TRUE, NULL);

        if (!pathname)
        {
                g_warning (_("Couldn't find pixmap file: %s"), filename);
                return NULL;
        }

        pixbuf = gdk_pixbuf_new_from_file (pathname, &error);
        if (!pixbuf)
        {
                fprintf (stderr, "Failed to load pixbuf file: %s: %s\n",
                         pathname, error->message);
                g_error_free (error);
        }
        g_free (pathname);
        return pixbuf;
}
