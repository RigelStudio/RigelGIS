# Set porject name
set(TargetName MapBase)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all Files
set(headers
			Export.h
			LayerLoader.h
			LayerMgr.h
			)

set(sources
			InputLib.cpp
			LayerLoader.cpp
			LayerMgr.cpp
			)

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Set porject filiter
source_group("Header Files" FILES ${headers})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources}  ${headers})

target_link_libraries(${TargetName} )
