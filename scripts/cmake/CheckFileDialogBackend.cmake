macro(CheckFileDialogBackend)

  set(BACKEND "dummy")
  if (WIN32 OR WINDOWS OR CYGWIN)
    set(BACKEND "windows")
  endif()
  if (APPLE AND NOT IPHONEOS)
    set(BACKEND "cocoa")
  endif()
  if (UNIX AND NOT APPLE OR ANDROID)
    find_package(PkgConfig)
    if (PKG_CONFIG_FOUND)
      pkg_search_module(GTK "gtk+-3.0" "gtk+-2.0")
      if (GTK_FOUND)
        set(BACKEND "gtk")
      endif()
    endif()
  endif()

  if ("${BACKEND}" STREQUAL "windows")
    add_definitions("-DFILEDIALOG_WINDOWS")
    # set(LIBS ${LIBS} -mwindows)
    set(FILEDIALOG_BACKEND_SOURCES "${CMAKE_SOURCE_DIR}/src/filedialog/SDLU_filedialog_windows*")
  endif()

  if ("${BACKEND}" STREQUAL "cocoa")
    add_definitions("-DFILEDIALOG_COCOA")
    set(LIBS ${LIBS} -Wl,-framework,Cocoa -lobjc)
    set(FILEDIALOG_BACKEND_SOURCES "${CMAKE_SOURCE_DIR}/src/filedialog/SDLU_filedialog_cocoa*")
  endif()

  if ("${BACKEND}" STREQUAL "gtk")
    add_definitions("-DFILEDIALOG_GTK")
    set(LIBS ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
    set(FILEDIALOG_BACKEND_SOURCES "${CMAKE_SOURCE_DIR}/src/filedialog/SDLU_filedialog_gtk*")
  endif()

  if ("${BACKEND}" STREQUAL "dummy")
    add_definitions("-DFILEDIALOG_DUMMY")
  endif()

endmacro()
