
-- project
set_project("xmake")
-- version
set_version("2.1.7", {build = "%Y%m%d%H%M"})
-- set xmake min version
set_xmakever("2.1.6")

set_languages("c99", "cxx14")
-- add_repositories("https://github.com/VoxelFrame/glfw.git")
-- includes("third/glfw")
-- add projects
target("console")
    set_kind("binary")
    add_files("src/**") 