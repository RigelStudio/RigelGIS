# Set porject name
set(TargetName MeMeasure)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all Files
set(headers
			Export.h
			OECore.h
			FileUtils.h
			)

set(sources InputLib.cpp
			OECore.cpp
			FileUtils.cpp
			)

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Set porject filiter
source_group("Header Files" FILES ${headers})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${headers})

# .
target_link_libraries(${TargetName} OpenThreads.lib)

INSTALL(
    FILES       ${headers}
    DESTINATION include/${TargetName}
)
INSTALL(
		TARGETS ${TargetName}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION bin
		ARCHIVE DESTINATION lib
	)
