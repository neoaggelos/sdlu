-- premake4 build script for SDLU

-- do all the dirty work here
dofile("scripts/premake/dirty.lua")

solution "SDLU"

  configurations { "Release", "Debug" }

  includedirs { sdl2_include_dir, sdl2_ttf_include_dir }
  links { sdl2_library, sdl2_ttf_library }

  libdirs { extra_lib_dirs }
  includedirs { extra_include_dirs }

  setup_gui_backend()

  location "build"
  objdir "build/obj"

  project "SDLU"
    kind(library_kind)
    language(lang)
    files { sources }
    includedirs { "src/common", "build/include" }
    targetdir "build/lib"

  add_tests()
