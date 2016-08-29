/*
 * The SDL Utility library
 * Copyright (c) 2016 Aggelos Kolaitis <neoaggelos@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */


#include "SDLU.h"
#include "SDLU_common.h"

#define UNUSED(x) (void)(x)

static Uint32 next_id = 0;

static Uint32 combobox_event_id = 0;

struct SDLU_ComboBoxItem {
    const char* text;
    SDL_Texture* texture;
    struct SDLU_ComboBoxItem* next;
};

typedef struct SDLU_ComboBoxItem SDLU_ComboBoxItem;

/* check if:   a <= b <= c */
#define lequal(a,b,c) ((a<=b) && (b<=c))

static void
SDLU_PushComboboxEvent(SDLU_ComboBox* combobox)
{
    SDL_Event event;
    if (combobox_event_id == 0 || combobox_event_id == (Uint32) -1) {
        SDLU_Log("events not registered");
        return;
    }

    event.type = combobox_event_id;
    event.user.code = combobox->id;
    event.user.windowID = SDL_GetWindowID(combobox->window);
    event.user.timestamp = SDL_GetTicks();

    SDL_PushEvent(&event);
}

static SDLU_ComboBoxItem*
get_item_by_index(SDLU_ComboBoxItem* head, int index)
{
    SDLU_ComboBoxItem* item = head;
    while (--index) item = item->next;

    return item;
}

static int
ComboBoxEventWatch(void *_this, SDL_Event* event)
{
    SDLU_ComboBox* combobox = (SDLU_ComboBox*) _this;
    SDL_Renderer* renderer;
    SDL_Rect R;

    if (combobox->num_items == 0) {
        combobox->current_item = NULL;
        combobox->current_index = 0;
        combobox->current = "";
        combobox->open = 0;
    }

    /**
     *  Since SDL2 revision 8234, we no longer have to calculate the scaled
     *  rect. This is due to the change in the order the event watchers are
     *  executed.
     */
    if (SDL_GetRevisionNumber() >= 8234) {
        R = combobox->rect;
    } else {
        renderer = SDL_GetRenderer(combobox->window);
        R = SDLU_GetScaledRect(renderer, combobox->rect, SDL_TRUE);
    }

    if (event->type == SDL_KEYDOWN) {
        if (event->key.windowID != SDL_GetWindowID(combobox->window)) {
            return 0;
        }

        if (event->key.keysym.sym == SDLK_ESCAPE) {
            combobox->open = 0;
        }
        return 0;
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.windowID != SDL_GetWindowID(combobox->window)) {
            return 0;
        }

        if (combobox->open) {
            if (lequal(R.x, event->button.x, R.x + R.w)) {
                int index = ((event->button.y - R.y) / R.h) + 1;
                if (event->button.y >= R.y && lequal(1, index, combobox->num_items + 1)) {
                    SDLU_ComboBoxItem* newitem;
                    newitem = get_item_by_index(combobox->data, index);
                    combobox->current = newitem->text;
                    combobox->current_index = index;
                    combobox->current_item = newitem;
                    if (combobox->callback) {
                        combobox->callback(combobox, combobox->arg);
                    }
                    SDLU_PushComboboxEvent(combobox);
                }
            }
            combobox->open = 0;
        } else {
            if (lequal(R.y, event->button.y, R.y + R.h)) {
                combobox->open = 1;
            }
        }
    }

    return 0;
}

SDLU_ComboBox*
SDLU_CreateComboBox(SDL_Window* window)
{
    SDLU_ComboBox* combobox;

    if (window == NULL)
        SDLU_ExitError("invalid window", NULL);

    combobox = (SDLU_ComboBox*) SDL_malloc(sizeof(SDLU_ComboBox));
    if (combobox == NULL)
        SDLU_ExitError("could not allocate memory", NULL);

    combobox->id = ++next_id;
    combobox->name = NULL;
    combobox->styles = SDLU_GetDefaultStyles();

    combobox->window = window;
    combobox->rect = SDLU_CreateRect(0, 0, 100, 30);
    combobox->open = 0;

    combobox->num_items = 0;
    combobox->data = NULL;

    combobox->callback = NULL;
    combobox->arg = NULL;

    combobox->current = "";
    combobox->current_index = 0;
    combobox->current_item = NULL;

    SDL_AddEventWatch(ComboBoxEventWatch, combobox);

    if (combobox_event_id == 0) {
        combobox_event_id = SDL_RegisterEvents(1);
        if (combobox_event_id == (Uint32) -1) {
            SDLU_Log("could not register combobox event");
        }
    }

    return combobox;
}

int
SDLU_SetComboBoxStyles(SDLU_ComboBox* combobox, SDLU_Styles* styles)
{
    if (combobox == NULL)
        SDLU_ExitError("invalid 'combobox'", -1);

    if (styles) {
        combobox->styles = styles;
        return 0;
    } else {
        return -1;
    }
}

int
SDLU_GetComboBoxStyles(SDLU_ComboBox* combobox, SDLU_Styles* styles)
{
    if (combobox == NULL)
        SDLU_ExitError("invalid 'combobox'", -1);

    styles = combobox->styles;
    UNUSED(styles);

    return 0;
}

int
SDLU_SetComboBoxGeometry(SDLU_ComboBox* combobox, int x, int y, int w, int h)
{
    if (combobox == NULL)
        SDLU_ExitError("invalid combo box", -1);

    if (x != -1) combobox->rect.x = x;
    if (y != -1) combobox->rect.y = y;
    if (w != -1) combobox->rect.w = w;
    if (h != -1) combobox->rect.h = h;

    return 0;
}

static void add_item(SDLU_ComboBoxItem** head, SDLU_ComboBoxItem* item)
{
    LL_APPEND((*head), item);
}

static SDL_Texture* CreateItemTexture(SDLU_ComboBox* combobox, const char* t)
{
    SDL_Renderer* renderer = SDL_GetRenderer(combobox->window);
    SDL_Rect R = combobox->rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    Uint32 font_size;
    int text_w, text_h;
    int x, y;
    SDL_Rect rect = SDLU_CreateRect(1, 1, R.w-2, R.h-2);

    surface = SDL_CreateRGBSurface(0, R.w, R.h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
            0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
#endif
    );

#define UNPACK(color) color.r, color.g, color.b, color.a

    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, UNPACK(combobox->styles->box_color)));
    SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, UNPACK(combobox->styles->fill_color)));

    font_size = SDLU_GetFontSize();
    SDLU_SetFontSize(combobox->styles->font_size);
    SDLU_GetTextOutputSize(t, &text_w, &text_h);

    x = (R.w - text_w) / 2;
    y = (R.h - text_h) / 2;

    SDLU_RenderTextToSurface(surface, x, y, combobox->styles->text_color, "%s", t);
    SDLU_SetFontSize(font_size);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

int
SDLU_AddComboBoxItem(SDLU_ComboBox** combobox, const char* item)
{
    SDLU_ComboBoxItem *newitem;

    if (*combobox == NULL)
        SDLU_ExitError("invalid combo box", -1);

    newitem = (SDLU_ComboBoxItem*) SDL_malloc(sizeof(SDLU_ComboBoxItem));
    if (newitem == NULL)
        SDLU_ExitError("could not allocate memory", -1);

    newitem->text = item;
    newitem->texture = CreateItemTexture(*combobox, item);

    /** 
     * C is a wonderful programming language because the following
     * makes total sense
     */
    add_item((SDLU_ComboBoxItem**) &((*combobox)->data), newitem);

    (*combobox)->num_items++;
    if ((*combobox)->num_items == 1) {
        (*combobox)->current = newitem->text;
        (*combobox)->current_index = 1;
        (*combobox)->current_item = newitem;
    }

    return 0;
}

static void del_item(SDLU_ComboBoxItem** head, SDLU_ComboBoxItem* item)
{
    LL_DELETE((*head), item);
}

int
SDLU_DelComboBoxItem(SDLU_ComboBox** combobox, const char* item)
{
    SDLU_ComboBoxItem* items, *delitem;

    if (*combobox == NULL)
        SDLU_ExitError("invalid combo box", -1);

    /* quick out if there are no items */
    if ((*combobox)->num_items == 0) return 0;

    items = (SDLU_ComboBoxItem*) (*combobox)->data;

    LL_FOREACH(items, delitem) {
        if (SDL_strcmp(delitem->text, item) == 0) {
            del_item((SDLU_ComboBoxItem**) &((*combobox)->data), delitem);

            SDL_DestroyTexture(delitem->texture);

            (*combobox)->num_items --;
            if ((*combobox)->num_items == 0) {
                (*combobox)->current = "";
                (*combobox)->current_index = 0;
                (*combobox)->current_item = NULL;
            }

            if (SDL_strcmp((*combobox)->current, item) == 0) {
                (*combobox)->current = "";
                (*combobox)->current_index = 0;
                (*combobox)->current_item = NULL;
            }
            return 0;
        }
    }

    return 0;
}

int
SDLU_SetComboBoxActiveItem(SDLU_ComboBox* combobox, int new_index)
{
	if (combobox == NULL)
		SDLU_ExitError("invalid combo box", -1);

	if (!lequal(1, new_index, combobox->num_items))
		SDLU_ExitError("new index out of range", -1);

	SDLU_ComboBoxItem *item = combobox->data;
	while (--new_index) item = item->next;

	combobox->current_item = item;
	combobox->current = item->text;
	combobox->current_index = new_index;

	return 0;
}

int
SDLU_RenderComboBox(SDLU_ComboBox* combobox)
{
    SDL_Renderer* renderer;
    SDLU_ComboBoxItem* items, *item;
    int x, y;

    if (combobox == NULL)
        SDLU_ExitError("invalid combo box", -1);

    x = combobox->rect.x;
    y = combobox->rect.y;

    renderer = SDL_GetRenderer(combobox->window);
    items = (SDLU_ComboBoxItem*) combobox->data;

    if (combobox->num_items == 0 || combobox->current_item == NULL) {
        SDL_SetRenderDrawColor(renderer, SDLU_GRAY);
        SDL_RenderFillRect(renderer, &(combobox->rect));
        SDL_SetRenderDrawColor(renderer, SDLU_WHITE);
        SDL_RenderDrawRect(renderer, &(combobox->rect));

        return 0;
    }

    if (combobox->open) {
        LL_FOREACH(items, item) {
            SDLU_CopyTexture(renderer, item->texture, x, y);
            y += combobox->rect.h;
        }
    } else {
        item = combobox->current_item;
        SDLU_CopyTexture(renderer, item->texture, x, y);
    }

    return 0;
}

int
SDLU_SetComboBoxCallback(SDLU_ComboBox* combobox, SDLU_Callback callback, void* arg)
{
    if (combobox == NULL)
        SDLU_ExitError("invalid combo box", -1);

    combobox->callback = callback;
    combobox->arg = arg;

    return 0;
}

int
SDLU_DestroyComboBox(SDLU_ComboBox* combobox)
{
    SDLU_ComboBoxItem* items, *item;

    if (combobox == NULL) return 0;

    items = combobox->data;
    LL_FOREACH(items, item) {
        SDLU_DelComboBoxItem(&combobox, item->text);
    }

    return 0;
}

Uint32
SDLU_GetComboBoxEventID()
{
    return combobox_event_id;
}
