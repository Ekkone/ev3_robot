set_project("ev3_robot")

add_includedirs("$(projectdir)/ev3dev")

add_linkdirs("$(projectdir)/ev3dev")
add_links("ev3dev")

set_languages("cxx11")

target("guitar")
    set_kind("binary")
    add_files("$(projectdir)/guitar/*.cpp")


