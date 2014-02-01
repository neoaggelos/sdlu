/*
 * The SDL Utility library
 * Copyright (c) 2014 Aggelos Kolaitis <neoaggelos@gmail.com>
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

#include <stdio.h>
#include <ctype.h>

static const char*
get_property_from_section(SDLU_IniSection *s, const char* p)
{
    SDLU_IniProperty *property;
    LL_FOREACH(s->properties, property) {
        if (SDL_strcmp(property->key, p) == 0) {
            return property->value;
        }
    }

    return NULL;
}

static int rwprintf(SDL_RWops* rwops, const char* fmt, ...)
{
    char* str;
    va_list args;
    va_start(args, fmt);
    SDLU_vasprintf(&str, fmt, args);
    va_end(args);

    return rwops->write(rwops, str, sizeof(char), strlen(str));
}

static int
add_property_to_section(SDLU_IniSection **s, const char* p, const char* v)
{
    SDLU_IniProperty *property = NULL;
    SDLU_IniProperty *temp;

    /* check if the property already exists */
    LL_FOREACH((*s)->properties, temp) {
        if (SDL_strcmp(temp->key, p) == 0) {
            temp->value = v;
            return 0;
        }
    }

    property = SDLU_malloc(SDLU_IniProperty);
    if (!property)
        SDLU_ExitError("could not allocate memory", -1);

    property->key = p;
    property->value = v;

    LL_APPEND((*s)->properties, property);
    (*s)->num_properties++;
    return 0;
}

static int
add_section_to_handler(SDLU_IniHandler** handler, const char* section)
{
    SDLU_IniSection *temp;
    SDLU_IniSection *s = NULL;

    /* check if section already exists */
    LL_FOREACH((*handler)->sections, temp) {
        if (SDL_strcmp(temp->name, section) == 0) {
            return 0;
        }
    }

    s = SDLU_malloc(SDLU_IniSection);
    if (!s)
        SDLU_ExitError("could not allocate memory", -1);

    s->name = section;
    s->num_properties = 0;
    s->properties = NULL;
    LL_APPEND((*handler)->sections, s);

    (*handler)->num_sections ++;
    return 0;
}

static SDLU_IniSection*
get_section_from_handler(SDLU_IniHandler* handler, const char* s)
{
    SDLU_IniSection *section;

    LL_FOREACH(handler->sections, section) {
        if (SDL_strcmp(s, section->name) == 0) return section;
    }
    return NULL;
}

static int
del_property_from_section(SDLU_IniSection **s, const char* property)
{
    SDLU_IniProperty *p;

    LL_FOREACH((*s)->properties, p) {
        if (SDL_strcmp(p->key, property) == 0) {
            LL_DELETE((*s)->properties, p);
            free(p);
            (*s)->num_properties --;
            return 0;
        }
    }

    SDLU_ExitError("property not found", -1);
}

SDLU_IniHandler*
SDLU_CreateIni(void)
{
    SDLU_IniHandler* handler = NULL;

    handler = SDLU_malloc(SDLU_IniHandler);
    if (!handler)
        SDLU_ExitError("could not allocate memory", NULL);

    handler->name = NULL;
    handler->num_sections = 0;
    handler->sections = NULL;

    add_section_to_handler(&handler, "__global");

    return handler;
}

int
SDLU_SetIniProperty(SDLU_IniHandler** handler, const char* _section, const char* property, const char* value)
{
    SDLU_IniSection *s;
    const char* section = _section ? _section : "__global";

    LL_FOREACH((*handler)->sections, s) {
        if (SDL_strcmp(s->name, section) == 0) {
            return add_property_to_section(&s, property, value);
        }
    }

    /** if section does not exist, create a new one **/
    add_section_to_handler(handler, section);
    s = get_section_from_handler(*handler, section);

    if (s != NULL)
        return add_property_to_section(&s, property, value);

    SDLU_ExitError("could not find section", -1);
}

const char*
SDLU_GetIniProperty(SDLU_IniHandler* handler, const char* _section, const char* property)
{
    SDLU_IniSection *s;
    const char* section = _section ? _section : "__global";

    LL_FOREACH(handler->sections, s) {
        if (SDL_strcmp(s->name, section) == 0) {
            return get_property_from_section(s, property);
        }
    }

    SDLU_ExitError("property not found", NULL);
}

int
SDLU_SaveIniRW(SDLU_IniHandler* handler, SDL_RWops* rwops, int freesrc)
{
    SDLU_IniSection *s;
    SDLU_IniProperty *p;

    LL_FOREACH(handler->sections, s) {
        if (s->num_properties == 0) continue;

        if (SDL_strcmp(s->name, "__global") != 0) {
            rwprintf(rwops, "\n[%s]\n", s->name);
        }
        LL_FOREACH(s->properties, p) {
            rwprintf(rwops, "%s=%s\n", p->key, p->value);
        }
    }

    if (freesrc) rwops->close(rwops);

    return 0;
}

int
SDLU_DelIniProperty(SDLU_IniHandler** handler, const char* _section, const char* property)
{
    SDLU_IniSection* s;
    const char* section = _section ? _section : "__global";

    s = get_section_from_handler(*handler, section);
    if (s != NULL)
        return del_property_from_section(&s, property);

    SDLU_ExitError("property not found", -1);
}

int
SDLU_DelIniSection(SDLU_IniHandler** handler, const char* _section)
{
    SDLU_IniSection *s;
    SDLU_IniProperty *p;
    int result;
    const char* section = _section ? _section : "__global";

    result = 0;
    s = get_section_from_handler(*handler, section);
    if (s == NULL)
        return -1;

    LL_FOREACH(s->properties, p) {
        result |= SDLU_DelIniProperty(handler, s->name, p->key);
    }

    if (SDL_strcmp(section, "__global") != 0) {
        LL_DELETE((*handler)->sections, s);
        SDLU_free(s);
    }

    (*handler)->num_sections--;

    return result;
}

int
SDLU_DestroyIni(SDLU_IniHandler* handler)
{
    SDLU_IniSection* s;
    int result = 0;

    LL_FOREACH(handler->sections, s) {
        result |= SDLU_DelIniSection(&handler, s->name);
    }

    /* free memory */
    SDLU_free(handler->sections);
    SDLU_free(handler);

    return result;
}

SDLU_IniHandler*
SDLU_LoadIniRW(SDL_RWops* rwops, int freesrc)
{
    char* buf;
    Sint64 size;
    SDLU_IniHandler* handler;
    char* current_section;
    int i;

    buf = SDLU_ReadFile(rwops);
    size = SDL_RWsize(rwops);
    if (freesrc) rwops->close(rwops);

    handler = SDLU_CreateIni();
    if (handler == NULL) return NULL;

    current_section = SDL_strdup("__global");
    buf[size-1] = '\0';
    i = 0;
    while(i < size) {
        /* char* buffers */
        char *first = SDLU_malloc2(char, 200);
        char *second = SDLU_malloc2(char, 200);

        /* parse line */
        if (buf[i] != ';') {
            if (SDL_sscanf(&buf[i], "%[^=\n]=%[^\n]", first, second) == 2) {
                SDLU_SetIniProperty(&handler, current_section, first, second);
            } else if (sscanf(&buf[i], "[%[^]\n]]", first) == 1) {
                free(current_section);
                current_section = SDL_strdup(first);
            }
        }

        /* continue to next line */
        while( buf[i] != '\n' && buf[i] != '\0' && i < size )
            i++;

        /* move to next char */
        i++;
    }

    return handler;
}
