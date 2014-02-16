-- this scripts does all the hard work so that we keep premake4.lua clean

srcdir_rel = path.getdirectory(_SCRIPT)
srcdir_rel = path.join(srcdir_rel, "../..")
srcdir = path.getabsolute(srcdir_rel)
builddir = srcdir .. "/build"

--------------------------------------------------------------------------------

newoption{
    trigger = "with-sdl2-ttf-library",
    value = "FILE",
    description = "Full path to the SDL2_ttf library (SDL2_TTF_LIBRARY)"
}

newoption{
    trigger = "with-sdl2-ttf-include-dir",
    value = "DIR",
    description = "Directory of SDL_ttf.h (SDL2_TTF_INCLUDE_DIR)"
}

newoption{
    trigger = "with-sdl2-library",
    value = "FILE",
    description = "Full path to the SDL2 library (SDL2_LIBRARY)"
}

newoption{
    trigger = "with-sdl2-include-dir",
    value = "DIR",
    description = "Directory of SDL.h (SDL2_INCLUDE_DIR)"
}

newoption{
    trigger = "enable-cxx",
    description = "Enable the cxx interface"
}

newoption{
    trigger = "enable-static",
    description = "Build the static library"
}

newoption{
    trigger = "extra-include-dirs",
    value = "DIR1;DIR2;DIR3",
    description = "A ';' separated list of directories to search for headers"
}

newoption{
    trigger = "extra-lib-dirs",
    value = "DIR1;DIR2;DIR3",
    description = "A ';' separated list of directories to search for libraries"
}

--------------------------------------------------------------------------------

enable_cxx            =  _OPTIONS["enable-cxx"]                 or  false
enable_static         =  _OPTIONS["enable-static"]              or  false
sdl2_include_dir      =  _OPTIONS["with-sdl2-include-dir"]      or  false
sdl2_library          =  _OPTIONS["with-sdl2-library"]          or  false
sdl2_ttf_include_dir  =  _OPTIONS["with-sdl2-ttf-include-dir"]  or  false
sdl2_ttf_library      =  _OPTIONS["with-sdl2-ttf-library"]      or  false
include_dirs          =  _OPTIONS["extra-include-dirs"]         or  ""
lib_dirs              =  _OPTIONS["extra-lib-dirs"]             or  ""

extra_include_dirs = { }
extra_lib_dirs = { }

config_h_in = path.join(srcdir, "include/SDLU_config_premake.h.in")
config_h    = path.join(builddir, "include/SDLU_config.h")

local fin = assert(io.open(config_h_in, "r"))
local buf = fin:read("*a")
fin:close()

if not enable_cxx then
  lang = "C"
  sources = { "src/**.c" }
else
  lang = "C++"
  sources = { "src/**.c", "src/**.cxx" }

  buf = buf:gsub("#undef SDLU_CXX", "#define SDLU_CXX 1")
  buf = buf:gsub("#undef SDLU_STL", "#define SDLU_STL 1")
end

local fout = assert(io.open(config_h, "w"))
fout:write(buf)
fout:close()

-- Include directories
sdl2_include_dir = sdl2_include_dir or os.getenv("SDL2_INCLUDE_DIR")
sdl2_ttf_include_dir = sdl2_ttf_include_dir or os.getenv("SDL2_TTF_INCLUDE_DIR")

-- Libraries
sdl2_library = sdl2_library or os.getenv("SDL2_LIBRARY") or "SDL2"
sdl2_ttf_library = sdl2_ttf_library or os.getenv("SDL2_TTF_LIBRARY") or "SDL2_ttf"

-- Extra include directories
include_dirs = ";" .. include_dirs
for dir in include_dirs:gmatch("%;([^;]+)") do
    table.insert(extra_include_dirs, dir)
end

-- Extra lib directories
lib_dirs = ";" .. lib_dirs
for dir in lib_dirs:gmatch("%;([^;]+)") do
    table.insert(extra_lib_dirs, dir)
end

-- Static or shared
library_kind = (os.is "windows" or enable_static) and "StaticLib" or "SharedLib"

-- Prepare build dir
local includes = os.matchfiles(srcdir .. "/include/*.h")
for _, j in pairs(includes) do
    os.copyfile(j, builddir .. "/include/" .. path.getname(j))
end

-- Better clean action
if _ACTION == "clean" then
    os.rmdir(builddir)
end
