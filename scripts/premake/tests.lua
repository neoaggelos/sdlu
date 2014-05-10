testdir = srcdir .. "/test"

local std_tests = {
    "testbutton", "testcollision", "testcolorkey", "testcombo", "testini",
    "testmath", "testmulticopy", "testrender", "testsprite", "testtext",
    "testturtle"
}
local gl_tests = {
    "testgl", "testrender2"
}
local gles2_tests = {
    "testgles2"
}
local cxx_tests = {
    "testcxx"
}

function add_test_common()
    project "test_common"
      language "c"
      kind "staticlib"
      files(testdir .. "/common.c")
      defines("DATA_DIR=\\\"" .. testdir .. "/data\\\"")
      links "SDLU"
      targetdir "build/tests"
end

function add_test(test)
    project(test)
      language "c"
      kind "windowedapp"
      files(testdir .. "/" .. test .. ".c")
      links { "SDLU", "test_common" }
      defines("DATA_DIR=" .. testdir .. "/data")
      targetdir "build/tests"
      includedirs { builddir .. "/include" }
end

function add_cxx_test(test)
    project(test)
      language "c++"
      kind "windowedapp"
      files(testdir .. "/" .. test .. ".cxx")
      links { "SDLU", "test_common" }
      defines("DATA_DIR=" .. testdir .. "/data")
      targetdir "build/tests"
      includedirs { builddir .. "/include" }
end

function add_gl_tests()
    for _, test in pairs(gl_tests) do
        add_test(test)
        configuration "windows" links "opengl32"
        configuration "macosx" links "OpenGL.framework"
        configuration {"not windows", "not macosx" } links "GL"
    end
end

function add_gles2_tests()
    for _, test in pairs(gl_tests) do
        add_test(test)
        links "GLESv2"
    end
end

function add_cxx_tests()
    for _, test in pairs(cxx_tests) do
        add_cxx_test(test)
    end
end

function add_tests()
    if not build_tests then
        return
    end

    add_test_common()
    for _, test in pairs(std_tests) do
        add_test(test)
    end
    add_gl_tests()
    add_gles2_tests()
    if enable_cxx then add_cxx_tests() end
end
