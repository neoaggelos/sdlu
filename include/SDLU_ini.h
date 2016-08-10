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

/**
 *  \file SDLU_ini.h
 *
 *  \brief Ini file handling API
 *
 *  This is a basic API that allows basic ini file loading, handling and saving
 *  with simple get/set functions. Every ini file is described by a handler
 *  structure (SDLU_IniHandler). The ini format supported by this API is the
 *  following:
 *
 *  \code
 *  ; Comments start with a semi-colon (;)
 *  ; All properties should appear as 'key=value' pairs, 'key' or 'value' may
 *  ; or may not have spaces
 *
 *  ; global properties come first
 *  global_property=whatever
 *
 *  ; Sections should appear as '[section]'
 *  [section]
 *  property_in_section=anything
 *  another_property=something else
 *
 *  \endcode
 *
 *  Global properties are under the hypothetical section '__global'. Passing
 *  NULL when asked for a section name will assume that you mean __global. For
 *  example:
 *
 *  \code
 *  SDLU_IniHandler* handler = SDLU_CreateIni();
 *
 *  // the following calls have the same effect
 *  // the first syntax should be preferred
 *  SDLU_SetIniProperty(&handler, NULL, "global_property", "value");
 *  SDLU_SetIniProperty(&handler, "__global", "global_property", "value");
 *
 *  \endcode
 */

#ifndef SDLU_INI_H
#define SDLU_INI_H

#include "SDL.h"

#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDLU_IniHandler SDLU_IniHandler;
typedef struct SDLU_IniProperty SDLU_IniProperty;
typedef struct SDLU_IniSection SDLU_IniSection;


/**
 *  \brief A single ini property
 */
struct SDLU_IniProperty {
    const char* key;
    const char* value;

    struct SDLU_IniProperty* next;
};

/**
 *  \brief A single ini section (set of grouped properties)
 */
struct SDLU_IniSection {
    const char* name;

    int num_properties;
    struct SDLU_IniProperty* properties;

    struct SDLU_IniSection *next;
};

/**
 *  \brief Handler to an ini file
 */
struct SDLU_IniHandler{
    const char* name;

    int num_sections;
    SDLU_IniSection* sections;
};

/**
 *  \brief Create a new empty ini handler
 */
extern DECLSPEC SDLU_IniHandler* SDLCALL SDLU_CreateIni(void);

/**
 *  \brief Load an ini file (passed as SDL_RWops) into a new ini handler
 *
 *  Note that this is a fairly 'stupid' function, and tricky syntax will make
 *  it mess up your program. Stick to the syntax shown in the API description
 *  if you want to use that function.
 *
 *  \param file File to load
 *  \param freesrc Whether to close the RWops after finishing
 *
 *  \return A new ini handler on success, -1 on error
 */
extern DECLSPEC SDLU_IniHandler* SDLCALL SDLU_LoadIniRW(
        SDL_RWops* file,
        int freesrc
);

/**
 *  \brief Load 'file' into an ini handler
 */
#define SDLU_LoadIni(file) \
    SDLU_LoadIniRW(SDL_RWFromFile(file, "r"), 1)

/**
 *  \brief Save ini handler to file
 *
 *  \param handler Ini handler to save
 *  \param file File to write to
 *  \param freesrc Whether to close the RWops after finishing
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SaveIniRW(
        SDLU_IniHandler* handler,
        SDL_RWops* file,
        int freesrc
);

/**
 *  \brief Save ini handler to filename (anything.ini)
 */
#define SDLU_SaveIni(handler, filename) \
    SDLU_SaveIniRW(handler, SDL_RWFromFile(filename, "w"), 1)

/**
 *  \brief Set section.property to value
 *
 *  \param handler Ini handler
 *  \param section Section that contains the property (NULL for global)
 *  \param property Property name
 *  \param value Property value to set
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_SetIniProperty(
        SDLU_IniHandler** handler,
        const char *section,
        const char *property,
        const char *value
);

/**
 *  \brief Get section.property
 *
 *  \param handler Ini handler
 *  \param section Section that contains the property (NULL for global)
 *  \param property Property to query
 *
 *  \return A string containing the value of section.property, NULL on error
 */
extern DECLSPEC const char* SDLCALL SDLU_GetIniProperty(
        SDLU_IniHandler* handler,
        const char* section,
        const char* property
);

/**
 *  \brief Delete section.property
 *
 *  \param handler Ini handler
 *  \param section Section that contains the property (NULL for global)
 *  \param property Property to delete
 *
 *  \return 0 on success, -1 if property wasn't found
 */
extern DECLSPEC int SDLCALL SDLU_DelIniProperty(
        SDLU_IniHandler** handler,
        const char* section,
        const char* property
);

/**
 *  \brief Delete section
 *
 *  \param handler Ini handler
 *  \param section Section to delete (NULL for global)
 *
 *  \return 0 on success, -1 if section does not exist
 */
extern DECLSPEC int SDLCALL SDLU_DelIniSection(
        SDLU_IniHandler** handler,
        const char* section
);

/**
 *  \brief Destroy handler
 *
 *  \param handler Ini handler to destroy
 *
 *  \return 0 on success, -1 on error
 */
extern DECLSPEC int SDLCALL SDLU_DestroyIni(SDLU_IniHandler* handler);

#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDLU_INI_H */
