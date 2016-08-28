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

#include <stdio.h>
#include <ctype.h>

static const char*
get_property_from_section(SDLU_IniSection *s, const char* p)
{
    SDLU_IniProperty *property;
    LL_FOREACH(s->properties, property) {
        if (SDL_strcmp(property->key, p) == 0) {
            return property->value; /* TODO: strdup needed? */
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

    return rwops->write(rwops, str, sizeof(char), SDL_strlen(str));
}

static int
add_property_to_section(SDLU_IniSection **s, const char* p, const char* v)
{
    SDLU_IniProperty *property = NULL;
    SDLU_IniProperty *temp;

    /* check if the property already exists */
    LL_FOREACH((*s)->properties, temp) {
        if (SDL_strcmp(temp->key, p) == 0) {
            SDL_free(temp->value);
            temp->value = SDL_strdup(v);
            return 0;
        }
    }

    property = (SDLU_IniProperty*) SDL_malloc(sizeof(SDLU_IniProperty));
    if (!property)
        SDLU_ExitError("could not allocate memory", -1);

    property->key = SDL_strdup(p);
    property->value = SDL_strdup(v);

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

    s = (SDLU_IniSection*) SDL_malloc(sizeof(SDLU_IniSection));
    if (!s)
        SDLU_ExitError("could not allocate memory", -1);

    s->name = SDL_strdup(section);
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
            SDL_free(p->key);
            SDL_free(p->value);
            SDL_free(p);
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

    handler = (SDLU_IniHandler*) SDL_malloc(sizeof(SDLU_IniHandler));
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

    if (*handler == NULL)
        SDLU_ExitError("invalid ini handler", -1);

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

    if (handler == NULL)
        SDLU_ExitError("invalid ini handler", NULL);

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

    if (handler == NULL)
        SDLU_ExitError("invalid ini handler", -1);

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

    if (*handler == NULL)
        SDLU_ExitError("invalid ini handler", -1);

    s = get_section_from_handler(*handler, section);
    if (s != NULL)
        return del_property_from_section(&s, property);

    SDLU_ExitError("property not found", -1);
}

int
SDLU_DelIniSection(SDLU_IniHandler** handler, const char* _section)
{
    SDLU_IniSection *s;
    int result;
    const char* section = _section ? _section : "__global";

    if (*handler == NULL)
        SDLU_ExitError("invalid ini handler", -1);

    result = 0;
    s = get_section_from_handler(*handler, section);
    if (s == NULL)
        return -1;

    while(s->properties) {
        result |= SDLU_DelIniProperty(handler, s->name, s->properties->key);
    }

    if (SDL_strcmp(section, "__global") != 0) {
        LL_DELETE((*handler)->sections, s);
        SDL_free(s);
    }

    (*handler)->num_sections--;

    return result;
}

int
SDLU_DestroyIni(SDLU_IniHandler* handler)
{
    int result = 0;

    if (handler == NULL) return 0;

    while(handler->num_sections >= 0) {
        result |= SDLU_DelIniSection(&handler, handler->sections->name);
    }

    /* free memory */
    SDL_free(handler->sections);
    SDL_free(handler);

    return result;
}

#define SDL_strncpy(target, source, n) \
	SDL_snprintf(target, n, "%s", source)

SDLU_IniHandler*
SDLU_LoadIniRW(SDL_RWops* rwops, int freesrc)
{
    char* buf;
    Sint64 size;
    SDLU_IniHandler* handler;
    char* current_section;
    int i;
    char *first, *second;

    if (rwops == NULL)
        SDLU_ExitError("invalid parameter 'rwops'", NULL);

    buf = SDLU_ReadFile(rwops);
    size = SDL_RWsize(rwops);
    if (freesrc) rwops->close(rwops);

    handler = SDLU_CreateIni();
    if (handler == NULL) return NULL;

    current_section = SDL_strdup("__global");
    buf[size-1] = '\0';

    first = (char*) SDL_malloc(sizeof(char) * 200);
    second = (char*) SDL_malloc(sizeof(char) * 200);

	SDL_memset(first, '\0', 200);
	SDL_memset(second, '\0', 200);

	int firstlen = 0;
	int secondlen = 0;

	enum {
		Begin,
		ReadingPairName,
		ReadingPairValue,
		ReadingSectionName,
		Reset
	} mode = Begin;

	i = 0;
	do {
    	if (buf[i] == ';' && mode != ReadingPairValue) {
			mode = Reset;
			continue;
		}
		if (mode == Begin) {
			firstlen = 0;
			secondlen = 0;
			if (buf[i] == '[') {
				mode = ReadingSectionName;
			}
			else if (buf[i] != '=' && buf[i] != ' ' && buf[i] != '\n') {
				mode = ReadingPairName;
				first[firstlen++] = buf[i];
			}
		}
		else if (mode == ReadingPairName) {
			/* TODO: What if firstlen == 200 ?? */
			if (buf[i] == '\n') {
				mode = Reset;
			}
			else if (buf[i] == '=') {
				mode = ReadingPairValue;
			}
			else {
				first[firstlen++] = buf[i];
			}
		}
		else if (mode == ReadingPairValue) {
			/* TODO: what if secondlen == 200 ?? */
			if (buf[i] == '\n' || buf[i] == ';') {
				char *value, *property;
				mode = Begin;
				property = (char*)SDL_malloc(firstlen);
				SDL_strncpy(property, first, firstlen);
				if (secondlen == 0) {
					SDLU_SetIniProperty(&handler, current_section, property, "");
				}
				else {
					value = (char*)SDL_malloc(secondlen);
					SDL_strncpy(value, second, secondlen);

					SDLU_SetIniProperty(&handler, current_section, property, value);
					SDL_free(value);

				}
				firstlen = 0;
				secondlen = 0;
				SDL_free(property);
			
				mode = buf[i] == '\n' ? Begin : Reset;
			}
			else {
				second[secondlen++] = buf[i];
			}
			continue;
		}
		else if (mode == ReadingSectionName) {
			if (buf[i] == '\n') {
				mode = Begin;
			}
			else if (buf[i] == ']') {
				SDL_free(current_section);
				current_section = (char*)SDL_malloc(firstlen);
				SDL_strncpy(current_section, first, firstlen);
				mode = Reset;
			}
			else {
				first[firstlen++] = buf[i];
			}
		}
		else if (mode == Reset) {
			if (buf[i] == '\n') mode = Begin;
		}

		/* next character */
		i++;
	} while (i < size);

    SDL_free(first);
    SDL_free(second);

    return handler;
}
