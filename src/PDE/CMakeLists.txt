project(PDE CXX)

add_library(PDE
            PDEStack.cpp
            Limiter.cpp
            MultiMat/MiscMultiMatFns.cpp
            MultiSpecies/MiscMultiSpeciesFns.cpp
            PrefIndicator.cpp
            Reconstruction.cpp
            ConfigureTransport.cpp
            ConfigureCompFlow.cpp
            ConfigureMultiMat.cpp
            ConfigureMultiSpecies.cpp
            CGPDE.cpp
            FVPDE.cpp
            DGPDE.cpp)

target_include_directories(PDE PUBLIC
                           ${QUINOA_SOURCE_DIR}
                           ${QUINOA_SOURCE_DIR}/Base
                           ${QUINOA_SOURCE_DIR}/Control
                           ${QUINOA_SOURCE_DIR}/Inciter
                           ${QUINOA_SOURCE_DIR}/Mesh
                           ${QUINOA_SOURCE_DIR}/PDE
                           ${BRIGAND_INCLUDE_DIRS}
                           ${PEGTL_INCLUDE_DIRS}
                           ${HIGHWAYHASH_INCLUDE_DIRS}
                           ${CHARM_INCLUDE_DIRS}
                           ${LAPACKE_INCLUDE_DIRS}
                           ${CBLAS_INCLUDE_DIRS}
                           ${PROJECT_BINARY_DIR}/../Main)

set_target_properties(PDE PROPERTIES LIBRARY_OUTPUT_NAME quinoa_pde)

INSTALL(TARGETS PDE
  	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
 	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

# Configure target for numerical integrals
add_subdirectory(Integrate)

# Configure targets for physics and problem types
add_subdirectory(Transport/Physics)
add_subdirectory(Transport/Problem)
add_subdirectory(CompFlow/Problem)
add_subdirectory(MultiMat/Physics)
add_subdirectory(MultiMat/Problem)
add_subdirectory(MultiSpecies/Problem)
add_subdirectory(EoS)
