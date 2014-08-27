-- this scripts does all the hard work so that we keep premake4.lua clean

srcdir_rel = path.getdirectory(_SCRIPT)
srcdir_rel = path.join(srcdir_rel, "../..")
srcdir = path.getabsolute(srcdir_rel)
builddir = srcdir .. "/build"
auxdir = srcdir .. "/scripts/premake"

dofile(auxdir .. "/functions.lua")

--------------------------------------------------------------------------------

-- parse all _ARGS that are _OPTIONS
for _, arg in pairs(_ARGS) do
  local is_option = false
  if arg:startswith '/' then
    arg = arg:sub(2) is_option = true
  elseif arg:startswith '--' then
    arg = arg:sub(3)
    is_option = true
  end

  if is_option then
    local first, last = arg:find('=')
    if first and last then
      _OPTIONS[arg:sub(1,first-1)] = arg:sub(last+1)
    else
      _OPTIONS[arg] = ""
    end
  end
end

--------------------------------------------------------------------------------

newoption{
  trigger = "interactive",
  description = "Run in interactive mode"
}

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
  trigger = "with-tests",
  description = "Also build the test programs"
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
interactive           =  _OPTIONS["interactive"]                or  false
build_tests           =  _OPTIONS["with-tests"]                 or  false

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
end

local fout = assert(io.open(config_h, "w"))
fout:write(buf)
fout:close()

-- Include directories
sdl2_include_dir = sdl2_include_dir or os.getenv("SDL2_INCLUDE_DIR") or false
sdl2_ttf_include_dir = sdl2_ttf_include_dir or os.getenv("SDL2_TTF_INCLUDE_DIR") or false

if not sdl2_include_dir and interactive then
  io.write "Enter location of the SDL2 headers: "
  sdl2_include_dir = io.read('*l')
else
  if type(sdl2_include_dir) == "boolean" then sdl2_include_dir = "" end
  if not os.isfile(sdl2_include_dir .. "/SDL.h") then
    print"* Warning: SDL.h was not found. Proceeding with compiler's result"
  end
end

if not sdl2_ttf_include_dir and interactive then
  io.write "Enter location of the SDL2_ttf headers: "
  sdl2_ttf_include_dir = io.read('*l')
else
  if type(sdl2_ttf_include_dir) == "boolean" then sdl2_ttf_include_dir = "" end
  if not os.isfile(sdl2_ttf_include_dir .. "/SDL_ttf.h") then
    print"* Warning: SDL_ttf.h was not found. Proceeding with compiler's result"
  end
end

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

-- File dialog backend
if os.is "windows" then
  setup_gui_backend = function()
    defines("FILEDIALOG_WIN32")
    linkoptions("-mwindows")
  end
elseif os.is "macosx" then
  setup_gui_backend = function()
    defines { "FILEDIALOG_COCOA" }
    files { "src/**.m" }
    links { "objc", "Cocoa.framework" }
    buildoptions { "-x objective-c -fpascal-strings" }
  end
else
  local have_gtk = pc_module_exists("gtk+-3.0")
  if have_gtk then
    setup_gui_backend = function()
      defines("FILEDIALOG_GTK")
      linkoptions(pc_libs("gtk+-3.0"))
      buildoptions(pc_cflags("gtk+-3.0"))
    end
  else
    setup_gui_backend = function()
      defines( "FILEDIALOG_DUMMY" )
    end
  end
end

-- Static or shared
library_kind = enable_static and "StaticLib" or "SharedLib"

-- Prepare build dir
local includes = os.matchfiles(srcdir .. "/include/*.h")
for _, j in pairs(includes) do
  os.copyfile(j, builddir .. "/include/" .. path.getname(j))
end

-- Better clean action
if _ACTION == "clean" or _OPTIONS["help"] or not _ACTION then
  os.rmdir(builddir)
end

-- Tests
dofile(auxdir .. "/tests.lua")

