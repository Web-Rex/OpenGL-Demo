function(copy_config_hpp)
    configure_file(
        "${CMAKE_SOURCE_DIR}/cmake/cpp.in/config.hpp.in"
        "${CMAKE_BINARY_DIR}/configured/include/config.h" ESCAPE_QUOTES
    )
endfunction(copy_config_hpp)

macro(copy_files GLOBPAT DESTINATION EXECUTABLE_SRC_LOCATION)
  file(GLOB_RECURSE COPY_FILES CMAKE_CONFIGURE_DEPENDS ${GLOBPAT})

  foreach(FILE_NAME ${COPY_FILES})
    string(REPLACE "/" ";" NEW_FILES_COPY ${FILE_NAME})
    list(LENGTH NEW_FILES_COPY lenght)
    MATH(EXPR new_lenght "${lenght}-1")
    list (GET NEW_FILES_COPY ${new_lenght} file_name)

    set(SRC "${FILE_NAME}")
    set(DST "${DESTINATION}/${file_name}")

    # message("")
    # message("-----------------------    " ${SRC})
    # message("-----------------------    " ${DST})
    # message("")

    add_custom_command(
      OUTPUT ${DST}
      COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST}

      DEPENDS ${SRC}
      COMMAND cmake -E echo "-------------- Copying files: ${file_name}"
    )

    set_property(SOURCE ${EXECUTABLE_SRC_LOCATION} APPEND PROPERTY OBJECT_DEPENDS ${DST})
    endforeach(FILE_NAME)
endmacro(copy_files)