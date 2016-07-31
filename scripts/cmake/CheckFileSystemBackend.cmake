macro(CheckFileSystemBackend)

  if (WIN32 OR WINDOWS OR CYGWIN)
    set(FILESYSTEM_BACKEND_SOURCES "${CMAKE_SOURCE_DIR}/src/filesystem/SDLU_filesystem_windows.c")
    add_definitions("-DFILESYSTEM_WIN32")
  else()
    set(FILESYSTEM_BACKEND_SOURCES "${CMAKE_SOURCE_DIR}/src/filesystem/SDLU_filesystem_dirent.c")
    add_definitions("-DFILESYSTEM_DIRENT")
  endif()
  
endmacro()
