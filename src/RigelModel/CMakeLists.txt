# Set porject name
set(TargetName RigelModel)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all Files
set(headers
			Export.h
			Style.h
			RigelLayer.h
			Common.h
			BoneAnimeNode.h
			BoneAnimeVisitor.h
			BoneModel.h
			DynamicModel.h
			GCSGeometryBase.h
			GeometryBase.h
			GCSLine.h
			LabelBase.h
			LabelNode.h
			ModelBase.h
			ModelFactory.h
			PlaceNode.h
			Segment.h
			StaticModel.h
			SymbolModel.h
			)

set(sources InputLib.cpp
			Style.cpp
			RigelLayer.cpp
			BoneAnimeNode.cpp
			BoneAnimeVisitor.cpp
			BoneModel.cpp
			DynamicModel.cpp
			GCSGeometryBase.cpp
			#GeometryBase.cpp
			GCSLine.cpp
			LabelBase.cpp
			LabelNode.cpp
			ModelBase.cpp
			ModelFactory.cpp
			PlaceNode.cpp
			Segment.cpp
			StaticModel.cpp
			SymbolModel.cpp
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
