file(GLOB_RECURSE sourcelist
        *.c
        *.cc
        *.cpp
        *.cxx)
string(REGEX REPLACE "${RDIR}/" "" relative_sources "${sourcelist}")
string(REPLACE ";" "\nsrc/" sources_string "${relative_sources}")
set(sources_string "set(sources\nsrc/${sources_string})")
file(WRITE sources.cmake "${sources_string}")