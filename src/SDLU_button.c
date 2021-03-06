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
#include "SDLU_hints.h"
#include "SDLU_common.h"
#include "SDLU_userdata_c.h"
#include <stdio.h>

/** for unused variables **/
#define UNUSED(x) (void)x

/** button event ids **/
static Uint32 button_hover = 0;
static Uint32 button_press = 0;
static Uint32 button_release = 0;
static Uint32 button_lostfocus = 0;
static int button_events_status = 0;

/*
 * how much the color changes when the button is hovered
 * should be a positive value
 */
#define VAL 50

/**
 * returns the calculated color when a button is hovered.
 * practically, if the value of the channel exceeds 255 after editing, we lower
 * it instead. For example:
 *      if value+VAL < 255 then returned==value+VAL
 *      if value+VAL > 255 then returned==value-VAL
 *
 *      (this macro is used for easier to read code in SDLU_RenderButton_BuiltIn
 */
#define calculate(value) \
    (( value + VAL <= 255 ) ? value + VAL : value - VAL)

/** unpack a color. **/
#define UNPACK(color) \
    color.r, color.g, color.b, color.a
#define UNPACK_RGB(color) \
    color.r, color.g, color.b

static SDL_Rect SDLU_GetRealPosition(SDLU_Button*);
static int SDLU_RenderButton_BuiltIn(SDLU_Button*);
static int SDLU_EventWatch(void*, SDL_Event*);
static int SDLU_CheckButtonEvents(SDLU_Button*, SDL_Event);
static void SDLU_PushButtonEvent(Uint32, SDLU_Button*);

/* Will be used to keep track of all buttons internally */
static Uint32 num_buttons = 0;
static SDLU_Button* buttons = NULL;
static Uint32 next_id = 1;

static int
SDLU_CheckButtonEvents( SDLU_Button* button, SDL_Event event )
{
    SDL_Rect mouse_rect;
    int ret = SDLU_IDLE;
    SDL_Cursor* old_cursor;
    Uint32 hover;
    SDL_Rect button_rect;
    int sdl_revision = SDL_GetRevisionNumber();

    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (button->flags & SDLU_BUTTON_HIDDEN) {
        return SDLU_IDLE;
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == button->hotkey) {
			if (button->callback[SDLU_PRESS_CALLBACK]) {
				button->callback[SDLU_PRESS_CALLBACK](button, button->arg[SDLU_PRESS_CALLBACK]);
			}

			SDLU_PushButtonEvent(SDLU_BUTTON_PRESS, button);
        }
    }

    /*
     * Revision 8234 in hg.libsdl.org/SDL fixed a bug where the event watchers
     * are run in the order that they are set.
     *
     * That means that we no longer need SDLU_GetRealPosition(), because the
     * mouse coordinates have been already fixed. The check is needed to not
     * break the behaviour with older SDL versions.
     */
    if ((button->flags & SDLU_BUTTON_FOREIGN) || (sdl_revision >= 8234)) {
        button_rect = button->rect;
    } else {
        button_rect = SDLU_GetRealPosition(button);
    }

    hover = button->action[SDLU_HOVER_ACTION];

    if (event.type == SDL_WINDOWEVENT) {
        /** handle case where mouse left the window **/
        if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
            if (button->state != SDLU_IDLE) {
                if ((button->state==SDLU_HOVERED)&&(hover & SDLU_HOVER_CURSOR))
                {
                    old_cursor = SDLU_GetButtonData(button,"_SDLU_old_cursor");
                    SDLU_AddButtonData(button, "_SDLU_old_cursor", NULL);
                    SDL_SetCursor(old_cursor);
                }
                SDLU_PushButtonEvent(SDLU_BUTTON_LOSTFOCUS, button);
                button->state = SDLU_IDLE;
            }
        }
        return button->state;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        mouse_rect.x = event.button.x ;
        mouse_rect.y = event.button.y ;
        mouse_rect.w = mouse_rect.h = 1;

        if ( SDL_HasIntersection(&button_rect, &mouse_rect ) ) {
            if (button->state != SDLU_PRESSED) {
                if (button->callback[SDLU_PRESS_CALLBACK]) {
                    button->callback[SDLU_PRESS_CALLBACK](button, button->arg[SDLU_PRESS_CALLBACK]);
                }
                SDLU_PushButtonEvent(SDLU_BUTTON_PRESS, button);
            }
            button->state = SDLU_PRESSED;
            ret = SDLU_PRESSED;
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (button->state == SDLU_PRESSED) {
            SDLU_PushButtonEvent(SDLU_BUTTON_RELEASE, button);
            button->state = SDLU_HOVERED;
        }
    }

    if (event.type == SDL_MOUSEMOTION) {
        mouse_rect.x = event.motion.x ;
        mouse_rect.y = event.motion.y ;
        mouse_rect.w = mouse_rect.h = 1;

        if (SDL_HasIntersection(&button_rect, &mouse_rect)) {
            if (button->state != SDLU_HOVERED) {
                if (hover & SDLU_HOVER_CURSOR) {
                    old_cursor = SDL_GetCursor();
                    SDLU_AddButtonData(button, "_SDLU_old_cursor", old_cursor);
                    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
                }
                button->state = SDLU_HOVERED;
                if (button->callback[SDLU_HOVER_CALLBACK]) {
                    button->callback[SDLU_HOVER_CALLBACK](button, button->arg[SDLU_HOVER_CALLBACK]);
                }
                SDLU_PushButtonEvent(SDLU_BUTTON_HOVER, button);
            }
            ret = SDLU_HOVERED;
        } else {
            if (button->state == SDLU_HOVERED) {
                if (hover & SDLU_HOVER_CURSOR) {
                    old_cursor = SDLU_GetButtonData(button,"_SDLU_old_cursor");
                    SDLU_AddButtonData(button, "_SDLU_old_cursor", NULL);
                    SDL_SetCursor(old_cursor);
                }
                SDLU_PushButtonEvent(SDLU_BUTTON_LOSTFOCUS, button);
            }
            button->state = SDLU_IDLE;
        }
    }
    return ret;
}

/**
 *  get the real position on the screen, even when 'SDL_RenderSetLogicalSize()'
 *  is used
 */
static SDL_Rect
SDLU_GetRealPosition(SDLU_Button* button)
{
    SDL_Renderer * renderer = SDL_GetRenderer(button->window);
    return SDLU_GetScaledRect(renderer, button->rect, SDL_TRUE);
}

/**
 *  generate geometry for round corners
 */
static void
SDLU_GenButtonGeometry(SDL_Rect rect, SDL_Point** points, int *count)
{
    int x1, x2, y1, y2;
    SDL_Point* p = NULL;

    x1 = rect.x;
    x2 = rect.x + rect.w;
    y1 = rect.y;
    y2 = rect.y + rect.h;

    *count = 0;

    if (rect.w >= 10 && rect.h >= 10) {
        *points = (SDL_Point*) SDL_malloc(sizeof(SDL_Point) * 20);
        if (!points)
            SDLU_ExitError("could not allocate memory", );

        p = *points;

        /* x coordinates */
        p[4].x = p[5].x = x1;
        p[2].x = p[3].x = p[6].x = p[7].x = x1 + 1;
        p[0].x = p[1].x = p[8].x = p[9].x = x1 + 2;
        p[19].x = p[18].x = p[11].x = p[10].x = x2 - 2;
        p[17].x = p[16].x = p[13].x = p[12].x = x2 - 1;
        p[15].x = p[14].x = x2;

        /* y coordinates */
        p[0].y = p[19].y = y1;
        p[1].y = p[2].y = p[18].y = p[17].y = y1 + 1;
        p[3].y = p[4].y = p[16].y = p[15].y = y1 + 2;
        p[5].y = p[6].y = p[14].y = p[13].y = y2 - 2;
        p[7].y = p[8].y = p[12].y = p[11].y = y2 - 1;
        p[9].y = p[10].y = y2;

        /* number of points */
        *count = 20;
    } else {
        *points = (SDL_Point*) SDL_malloc(8 * sizeof(SDL_Point));

        if (!points)
            SDLU_ExitError("could not allocate memory", );

        p = *points;

        /* x coordinates */
        p[0].x = p[7].x = x1;
        p[1].x = p[6].x = x1 + 1;
        p[2].x = p[5].x = x2 - 1;
        p[3].x = p[4].x = x2;

        /* y coordinates */
        p[1].y = p[2].y = y1;
        p[0].y = p[3].y = y1 + 1;
        p[7].y = p[4].y = y2 - 1;
        p[6].y = p[5].y = y2;

        /* number of points */
        *count = 8;
    }
}

/**
 * This function is automatically added upon creation of the first button
 * and automatically deleted when the last is destroyed
 *
 * It watches for new events, and when one arrives, it checks if any of the
 * existing buttons has been pressed, released, hovered or lost focus
 */
static int
SDLU_EventWatch(void *_button, SDL_Event* event)
{
    SDLU_Button *button = (SDLU_Button*)_button;

    /**
     * only interested in left clicks, mouse motion and window leave events
     */
    switch(event->type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            if (event->button.button != 1) {
                return 1;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_LEAVE) {
                break;
            } else {
                return 1;
            }
        case SDL_MOUSEMOTION:
        case SDL_KEYDOWN:
            break;
        default:
            return 1;
    }

    if (event->button.windowID == SDL_GetWindowID(button->window)) {
        SDLU_CheckButtonEvents(button, *event);
    }
    return 1;
}

/** Push a new button event of 'type' **/
static void
SDLU_PushButtonEvent(Uint32 type, SDLU_Button* button)
{
    SDL_Event event;
    const char* hint;

    /* If SDLU_HINT_BUTTON_PUSH_EVENTS is 0, then pushing events is disabled */
    hint = SDLU_GetHint(SDLU_HINT_BUTTON_PUSH_EVENTS);
    if (!SDL_strcmp("0", hint)) {
        return;
    }

    if (button_events_status == 1) {
        /* Prepare the event */
        event.type = type;
        event.user.code = button->id;
        event.user.windowID = SDL_GetWindowID(button->window);
        event.user.timestamp = SDL_GetTicks();

        /* Push the event */
        SDL_PushEvent(&event);
    } else {
        SDLU_Log("button events are not registered");
    }
}

/* Internal function to create a new generic button */
static SDLU_Button*
SDLU_CreateGenericButton(SDL_Window* window, Uint32 flags)
{
    SDLU_Button* ret;

    if (window == NULL)
        SDLU_ExitError("invalid parameter 'window'", NULL);

    if (!(flags & SDLU_BUTTON_FOREIGN)) {
        if (SDL_GetRenderer(window) == NULL)
            SDLU_ExitError("window doesn't have a renderer", NULL);
    }

    ret = (SDLU_Button*) SDL_malloc(sizeof(SDLU_Button));
    if ( ret == NULL )
        SDLU_ExitError("could not allocate memory", NULL);

    ret->id = next_id++ ;
    ret->flags = flags;

    /* No callbacks by default */
    ret->callback[0] = ret->callback[1] = NULL;
    ret->arg[0] = ret->arg[1] = NULL;

    /* default button actions */
    ret->action[SDLU_PRESS_ACTION] = SDLU_PRESS_NONE;
    ret->action[SDLU_HOVER_ACTION] = SDLU_HOVER_BG;

    /* Initialize the button data */
    ret->window = window;
    ret->rect.x = ret->rect.y = 0;
    ret->state = SDLU_IDLE;
    ret->hotkey = 0;

    /* Default render function */
    if (!(flags & SDLU_BUTTON_FOREIGN)) {
        ret->render = SDLU_RenderButton_BuiltIn;
    }

    /* Update the internal button list */
    LL_PREPEND(buttons, ret);
    num_buttons++;

    /* Add a new button event watch */
    SDL_AddEventWatch(SDLU_EventWatch, ret);

    /* Register button events if needed */
    if (button_events_status == 0) {
        button_hover = SDL_RegisterEvents(4);
        if (button_hover == (Uint32) - 1) {
            button_events_status = -1;
            SDLU_Log("could not register button events");
        } else {
            button_press = button_hover + 1;
            button_release = button_hover + 2;
            button_lostfocus = button_hover + 3;
            button_events_status = 1;
        }
    }

    return ret;
}

static SDLU_Button*
SDLU_CreateTextButton(SDLU_Button* ret, const char* text)
{
    SDLU_Styles* styles;

    text = text ? text : "Button";

    styles = SDLU_GetDefaultStyles();
    if (styles == NULL) {
        SDL_free(ret);
        SDL_DelEventWatch(SDLU_EventWatch, ret);
        SDLU_ExitError("could not allocate memory", NULL);
    }

    SDLU_GetUTF8Size(styles->font, text, &ret->rect.w, &ret->rect.h);

    ret->rect.w         += 25;
    ret->rect.h         += 20;

    styles->title = text;
    ret->content  = (void*)styles;

    return ret;
}

static SDLU_Button*
SDLU_CreateImageButton(SDLU_Button* ret, SDL_Texture* image)
{
    ret->content = image;
    ret->rect.x = ret->rect.y = 0;

    SDLU_GetTextureSize(image, &(ret->rect.w), &(ret->rect.h) );

    return ret;
}

SDLU_Button*
SDLU_CreateButton(SDL_Window* window, const void* data, Uint32 flags)
{
    SDLU_Button* ret;

    /** check to see that flags are compatible **/
    if ((flags & SDLU_BUTTON_TEXT) && (flags & SDLU_BUTTON_IMAGE)) {
        SDLU_ExitError(
            "Flags SDLU_BUTTON_TEXT and SDLU_BUTTON_IMAGE are not compatible",
            NULL
        );
    }

    /** default to SDLU_BUTTON_TEXT **/
    if (!(flags & SDLU_BUTTON_IMAGE))
        flags |= SDLU_BUTTON_TEXT;

    ret = SDLU_CreateGenericButton(window, flags);
    if (ret == NULL)
        return NULL; /* the error message has been set */

    if (flags & SDLU_BUTTON_TEXT) {
        return SDLU_CreateTextButton(ret, (const char*)data);
    } else {
        return SDLU_CreateImageButton(ret, (SDL_Texture*)data);
    }
}

int
SDLU_SetButtonRenderFunc(SDLU_Button * button, int (*render)(SDLU_Button*))
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (render) {
        button->render = render;
    } else {
        button->render = SDLU_RenderButton_BuiltIn;
    }
    return 0;
}

Uint32
SDLU_GetButtonFlags(SDLU_Button* button)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", 0);

    return button->flags;
}

int
SDLU_SetButtonCallback(SDLU_Button* button, int type,
                       SDLU_Callback callback, void* arg)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if ((type != SDLU_PRESS_CALLBACK) && (type != SDLU_HOVER_CALLBACK))
        SDLU_ExitError("invalid parameter 'type'", -1);

    button->callback[type]  = callback;
    button->arg[type]       = arg;

    return 0;
}

int
SDLU_DelButtonCallback(SDLU_Button* button, int type)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if ((type != SDLU_PRESS_CALLBACK) && (type != SDLU_HOVER_CALLBACK))
        SDLU_ExitError("invalid parameter 'type'", -1);

    button->callback[type]  = NULL;
    button->arg[type]       = NULL;

    return 0;
}

int
SDLU_SetButtonGeometry(SDLU_Button* button, int x, int y, int w, int h)
{
    SDL_Rect *rect;

    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    rect = &(button->rect);

    /** -1 keeps the old value **/
    if (x != -1) rect->x = x;
    if (y != -1) rect->y = y;
    if (w != -1) rect->w = w;
    if (h != -1) rect->h = h;

    return 0;
}

int
SDLU_GetButtonGeometry(SDLU_Button* button, int* x, int* y, int* w, int* h)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (x) *x = button->rect.x;
    if (y) *y = button->rect.y;
    if (w) *w = button->rect.w;
    if (h) *h = button->rect.h;

    return 0;
}

int
SDLU_SetButtonStyles(SDLU_Button* button, SDLU_Styles *styles)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (!(button->flags & SDLU_BUTTON_TEXT))
        SDLU_ExitError("not a text button", -1);

    if (styles) {
        button->content = styles;
        return 0;
    } else {
        return -1;
    }
}

int
SDLU_GetButtonStyles(SDLU_Button* button, SDLU_Styles *styles)
{
    if (button == NULL)
        SDLU_ExitError("invliad parameter 'button'", -1);

    if (!(button->flags & SDLU_BUTTON_TEXT))
        SDLU_ExitError("not a text button", -1);

    styles = (SDLU_Styles*) button->content;
    UNUSED(styles);

    return 0;
}

int
SDLU_SetButtonImage(SDLU_Button* button, SDL_Texture* image)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (image == NULL)
        SDLU_ExitError("invalid parameter 'texture'", -1);

    if (!(button->flags & SDLU_BUTTON_IMAGE))
        SDLU_ExitError("not an image button", -1);

    button->content = (void*)image;
    return 0;
}

int
SDLU_SetButtonAction(SDLU_Button* button, int type, int action)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (type != SDLU_PRESS_ACTION && type != SDLU_HOVER_ACTION)
        SDLU_ExitError("invalid parameter 'type'", -1);

    button->action[type] = action;
    return 0;
}

int
SDLU_GetButtonAction(SDLU_Button* button, int type)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (type != SDLU_PRESS_ACTION && type != SDLU_HOVER_ACTION)
        SDLU_ExitError("invalid parameter 'type'", -1);

    return button->action[type];
}

SDLU_Button*
SDLU_GetButtonFromID( Uint32 id )
{
    SDLU_Button *button;

    LL_FOREACH(buttons,button) {
        if (button->id == id)
            return button;
    }

    /* No button was found if we are here */
    SDLU_ExitError("parameter 'id' is out of range", NULL);
}

int
SDLU_HideButton(SDLU_Button* button, int hide)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (hide == -1) {
        return (button->flags & SDLU_BUTTON_HIDDEN) ? 1 : 0;
    }

    if (hide) {
        button->flags |= SDLU_BUTTON_HIDDEN;
    } else {
        button->flags &= ~SDLU_BUTTON_HIDDEN;
    }

    return 0;
}

int
SDLU_GetButtonImage( SDLU_Button* button, SDL_Texture** image )
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (!(button->flags & SDLU_BUTTON_IMAGE))
        SDLU_ExitError("not an image button", -1);

    *image = (SDL_Texture*) button->content;

    return 0;
}

int
SDLU_GetButtonState( SDLU_Button* button )
{
    return button->state;
}

int
SDLU_AddButtonData( SDLU_Button* button, const char* key, void *data )
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", -1);

    return SDLU_AddUserData(button->id, 0, key, data);
}

void*
SDLU_GetButtonData( SDLU_Button* button, const char* key )
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", NULL);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", NULL);

    return SDLU_GetUserData(button->id, 0, key);
}

int
SDLU_DelButtonData(SDLU_Button* button, const char* key)
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (key == NULL)
        SDLU_ExitError("invalid parameter 'key'", -1);

    return SDLU_DelUserData(button->id, 0, key);
}

int
SDLU_RenderButton_BuiltIn( SDLU_Button* button )
{
    int result = 0;
    SDL_Renderer* renderer = NULL;  /* renderer */

    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    if (button->flags & SDLU_BUTTON_HIDDEN) {
        return -1;
    }

    if (button->flags & SDLU_BUTTON_FOREIGN)
        SDLU_ExitError("SDLU_BUTTON_FOREIGN flag is enabled", -1);

    renderer = SDL_GetRenderer(button->window);

    if (button->flags & SDLU_BUTTON_IMAGE) {
        SDL_Texture* image = (SDL_Texture*) button->content;
        if (button->flags & SDLU_BUTTON_THEMED) {
            int texw, texh;
            SDLU_GetTextureSize(image, &texw, &texh);
            if (button->state == SDLU_IDLE) {
                SDL_Rect srcrect = SDLU_CreateRect(
                        0, 0,
                        texw/3, texh/3
                );
                SDL_RenderCopy(renderer, image, &srcrect, &(button->rect));
            } else if (button->state == SDLU_HOVERED) {
                SDL_Rect srcrect = SDLU_CreateRect(
                        texw/3, texh/3,
                        texw/3, texh/3
                );
                SDL_RenderCopy(renderer, image, &srcrect, &(button->rect));
            } else if (button->state == SDLU_PRESSED) {
                SDL_Rect srcrect = SDLU_CreateRect(
                        2 * texw/3, 2 * texh/3,
                        texw/3, texh/3
                );
                SDL_RenderCopy(renderer, image, &srcrect, &(button->rect));
            }
        } else {
            result |= SDL_RenderCopy(renderer, image, NULL, &(button->rect));
        }
    } else {
        int text_w, text_h;
        Uint8 r, g, b, a;
        SDL_BlendMode blendmode;
        SDL_Color fill, text;
        SDLU_Styles* styles = (SDLU_Styles*) button->content;
        int press = button->action[SDLU_PRESS_ACTION];
        int hover = button->action[SDLU_HOVER_ACTION];

        /* backup original properties */
        result |= SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        result |= SDL_GetRenderDrawBlendMode( renderer, &blendmode );

        /* set button properties as the current ones */
        result |= SDL_SetRenderDrawBlendMode(renderer, styles->blendmode );

        /* calculate fill color */
        if ((hover & SDLU_HOVER_BG) && button->state == SDLU_HOVERED ) {
            fill.r = calculate(styles->fill_color.r);
            fill.g = calculate(styles->fill_color.g);
            fill.b = calculate(styles->fill_color.b);
            fill.a = styles->fill_color.a;
        } else {
            fill = styles->fill_color;
        }

        /* calculate text color */
        if ((hover & SDLU_HOVER_FG) && button->state == SDLU_HOVERED) {
            text.r = calculate( styles->text_color.r );
            text.g = calculate( styles->text_color.g );
            text.b = calculate( styles->text_color.b );
            text.a = styles->text_color.a;
        } else {
            text = styles->text_color;
        }

        /* draw the box */
        if (button->flags & SDLU_BUTTON_ROUND) {
            SDL_Point* points;
            int num_points;
            SDLU_GenButtonGeometry(button->rect, &points, &num_points);
            if ((press & SDLU_PRESS_INVERT) && button->state == SDLU_PRESSED) {
                SDL_SetRenderDrawColor(renderer, UNPACK(text));
            } else {
                SDL_SetRenderDrawColor(renderer, UNPACK(fill));
            }
            result |= SDLU_RenderFillPolygon(renderer, points, num_points);
            SDL_SetRenderDrawColor(renderer, UNPACK(styles->box_color));
            result |= SDLU_RenderDrawPolygon(renderer, points, num_points);
            SDL_free(points);
        } else {
            if ((press & SDLU_PRESS_INVERT) && button->state == SDLU_PRESSED) {
                result |= SDLU_RenderDrawOutlineRect(
                        renderer, button->rect, styles->box_color, text
                );
            } else {
                result |= SDLU_RenderDrawOutlineRect(
                        renderer, button->rect, styles->box_color, fill
                );
            }
        }

        /* when hovered kick the text a little lower */
        SDL_Rect textRect = button->rect;
        if ((hover & SDLU_HOVER_BG) && button->state == SDLU_HOVERED) {
            textRect.y += 2;
        }

        /* draw the button text */
        if ((press & SDLU_PRESS_INVERT) && button->state == SDLU_PRESSED) {
            result |= SDL_SetRenderDrawColor(renderer, UNPACK(fill));
        } else {
            result |= SDL_SetRenderDrawColor(renderer, UNPACK(text));
        }

        result |= SDLU_RenderUTF8Ex(renderer, styles->font, styles->title, textRect, Center, Center);

        /* for SDLU_HOVER_UL, we underline the text */
        SDLU_GetUTF8Size(styles->font, styles->title, &text_w, &text_h);
        if ((hover & SDLU_HOVER_UL) && button->state == SDLU_HOVERED) {
            result |= SDL_RenderDrawLine(
                    renderer,
                    textRect.x + (textRect.w - text_w) / 2 - 1,
                    textRect.y + text_h + (textRect.h - text_h) / 2,
                    textRect.x + (textRect.w - text_w) / 2 + text_w + 1,
                    textRect.y + text_h + (textRect.h - text_h) / 2
            );
        }

        /* restore original properties */
        result |= SDL_SetRenderDrawColor(renderer, r,g,b,a);
        result |= SDL_SetRenderDrawBlendMode(renderer, blendmode);
    }
    return result;
}

int
SDLU_DestroyButton( SDLU_Button* button )
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    /* close font if needed */
    if (button->flags & SDLU_BUTTON_TEXT && ((SDLU_Styles*)button->content)->freefont) {
        SDLU_CloseFont(((SDLU_Styles*)button->content)->font);
    }

    /** remove from internal button list **/
    if (buttons) LL_DELETE(buttons, button);

    /** delete event watch **/
    SDL_DelEventWatch(SDLU_EventWatch, button);

    if (button) SDL_free(button);
    return 0;
}

int
SDLU_SetButtonHotkey( SDLU_Button * button, SDL_Scancode hotkey )
{
    if (button == NULL)
        SDLU_ExitError("invalid parameter 'button'", -1);

    button->hotkey = hotkey;

    return 0;
}

Uint32 SDLU_GetButtonHoverEvent() {return button_hover;}
Uint32 SDLU_GetButtonPressEvent() {return button_press;}
Uint32 SDLU_GetButtonReleaseEvent() {return button_release;}
Uint32 SDLU_GetButtonLostFocusEvent() {return button_lostfocus;}
