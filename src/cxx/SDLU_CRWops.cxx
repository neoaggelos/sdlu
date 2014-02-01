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

SDLU::RWops::RWops(void)
{
    this->rwops = SDL_AllocRW();
}

SDLU::RWops::RWops(const char* file, const char* mode)
{
    this->rwops = SDL_RWFromFile(file, mode);
}

#if defined(SDLU_STL)
SDLU::RWops::RWops(std::string file, std::string mode)
{
    this->rwops = SDL_RWFromFile(file.c_str(), mode.c_str());
}
#endif

SDLU::RWops::RWops(FILE* fp, SDL_bool autoclose)
{
    this->rwops = SDL_RWFromFP(fp, autoclose);
}

SDLU::RWops::RWops(void* mem, int size)
{
    this->rwops = SDL_RWFromMem(mem, size);
}

SDLU::RWops::RWops(const void* mem, int size)
{
    this->rwops = SDL_RWFromConstMem(mem, size);
}

SDLU::RWops::RWops(SDL_RWops* rwops)
{
    this->rwops = rwops;
}

SDLU::RWops::~RWops(void)
{
    if (this->rwops->type == SDL_RWOPS_UNKNOWN) {
        SDL_FreeRW(this->rwops);
    } else {
        this->rwops->close(this->rwops);
    }
}

SDL_RWops* SDLU::RWops::GetRWops(void)
{
    return this->rwops;
}

Sint64 SDLU::RWops::size(void)
{
    return this->rwops->size(this->rwops);
}

Sint64 SDLU::RWops::seek(Sint64 offset, int whence)
{
    return this->rwops->seek(this->rwops, offset, whence);
}

size_t SDLU::RWops::read(void *ptr, size_t size, size_t maxnum)
{
    return this->rwops->read(this->rwops, ptr, size, maxnum);
}

size_t SDLU::RWops::write(const void* ptr, size_t size, size_t num)
{
    return this->rwops->write(this->rwops, ptr, size, num);
}
