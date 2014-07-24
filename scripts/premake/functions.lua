function outputof(cmd)
    local p = io.popen(cmd)
    local buf = p:read("*a")
    p:close()
    return buf
end

function pc_module_exists(module)
    local a = outputof("pkg-config --errors-to-stdout --modversion " .. module)
    -- if 'a' is not a version like 'XXX.YYY.ZZZ', then there has been
    -- an error, and pkg-config has written the 'not found' message
    return not a:find("No package")
end

function pc_libs(module)
    return outputof("pkg-config --libs " .. module)
end

function pc_cflags(module)
    return outputof("pkg-config --cflags " .. module)
end
