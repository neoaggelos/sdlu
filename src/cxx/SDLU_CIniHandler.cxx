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

SDLU::IniHandler::IniHandler(void)
{
    this->handler = SDLU_CreateIni();
}

SDLU::IniHandler::IniHandler(SDL_RWops* rwops, int freesrc)
{
    this->handler = SDLU_LoadIniRW(rwops, freesrc);
}

SDLU::IniHandler::IniHandler(SDLU::RWops* rwops, int freesrc)
{
    this->handler = SDLU_LoadIniRW(rwops->GetRWops(), freesrc);
}

SDLU::IniHandler::IniHandler(const char* file)
{
    this->handler = SDLU_LoadIni(file);
}

SDLU::IniHandler::IniHandler(std::string file)
{
    this->handler = SDLU_LoadIni(file.c_str());
}

SDLU::IniHandler::IniHandler(SDLU_IniHandler *handler)
{
    this->handler = handler;
}

SDLU::IniHandler::~IniHandler(void)
{
    SDLU_DestroyIni(this->handler);
}

SDLU_IniHandler* SDLU::IniHandler::GetIniHandler(void)
{
    return this->handler;
}

int SDLU::IniHandler::SetProperty(const char* s, const char* p, const char* v)
{
    return SDLU_SetIniProperty(&(this->handler), s, p, v);
}

const char* SDLU::IniHandler::GetProperty(const char* s, const char* p)
{
    return SDLU_GetIniProperty(this->handler, s, p);
}

int SDLU::IniHandler::DelProperty(const char* s, const char* p)
{
    return SDLU_DelIniProperty(&(this->handler), s, p);
}

int SDLU::IniHandler::DelSection(const char* s)
{
    return SDLU_DelIniSection(&(this->handler), s);
}

int SDLU::IniHandler::SetProperty(std::string s, std::string p, std::string v)
{
    return SDLU_SetIniProperty(&(this->handler), s.c_str(), p.c_str(), v.c_str());
}

std::string SDLU::IniHandler::GetProperty(std::string s, std::string p)
{
    return SDLU_GetIniProperty(this->handler, s.c_str(), p.c_str());
}

int SDLU::IniHandler::DelProperty(std::string s, std::string p)
{
    return SDLU_DelIniProperty(&(this->handler), s.c_str(), p.c_str());
}

int SDLU::IniHandler::DelSection(std::string s)
{
    return SDLU_DelIniSection(&(this->handler), s.c_str());
}

int SDLU::IniHandler::Save(SDL_RWops* rwops, int freesrc)
{
    return SDLU_SaveIniRW(this->handler, rwops, freesrc);
}

int SDLU::IniHandler::Save(SDLU::RWops* rwops, int freesrc)
{
    return SDLU_SaveIniRW(this->handler, rwops->GetRWops(), freesrc);
}

int SDLU::IniHandler::Save(const char* file)
{
    return SDLU_SaveIni(this->handler, file);
}

int SDLU::IniHandler::Save(std::string file)
{
    return SDLU_SaveIni(this->handler, file.c_str());
}
