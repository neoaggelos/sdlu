# These are here to keep CMakeLists.txt clean

function(JOIN_FILES FILES GLUE OUTPUT)
  string(REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${FILES}")
  string(REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}")
  set(${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()
