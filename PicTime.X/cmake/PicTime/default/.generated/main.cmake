include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(PicTime_default_library_list )

# Handle files with suffix s, for group default-XC16
if(PicTime_default_default_XC16_FILE_TYPE_assemble)
add_library(PicTime_default_default_XC16_assemble OBJECT ${PicTime_default_default_XC16_FILE_TYPE_assemble})
    PicTime_default_default_XC16_assemble_rule(PicTime_default_default_XC16_assemble)
    list(APPEND PicTime_default_library_list "$<TARGET_OBJECTS:PicTime_default_default_XC16_assemble>")

endif()

# Handle files with suffix S, for group default-XC16
if(PicTime_default_default_XC16_FILE_TYPE_assemblePreproc)
add_library(PicTime_default_default_XC16_assemblePreproc OBJECT ${PicTime_default_default_XC16_FILE_TYPE_assemblePreproc})
    PicTime_default_default_XC16_assemblePreproc_rule(PicTime_default_default_XC16_assemblePreproc)
    list(APPEND PicTime_default_library_list "$<TARGET_OBJECTS:PicTime_default_default_XC16_assemblePreproc>")

endif()

# Handle files with suffix c, for group default-XC16
if(PicTime_default_default_XC16_FILE_TYPE_compile)
add_library(PicTime_default_default_XC16_compile OBJECT ${PicTime_default_default_XC16_FILE_TYPE_compile})
    PicTime_default_default_XC16_compile_rule(PicTime_default_default_XC16_compile)
    list(APPEND PicTime_default_library_list "$<TARGET_OBJECTS:PicTime_default_default_XC16_compile>")

endif()

# Handle files with suffix s, for group default-XC16
if(PicTime_default_default_XC16_FILE_TYPE_dependentObject)
add_library(PicTime_default_default_XC16_dependentObject OBJECT ${PicTime_default_default_XC16_FILE_TYPE_dependentObject})
    PicTime_default_default_XC16_dependentObject_rule(PicTime_default_default_XC16_dependentObject)
    list(APPEND PicTime_default_library_list "$<TARGET_OBJECTS:PicTime_default_default_XC16_dependentObject>")

endif()

# Handle files with suffix elf, for group default-XC16
if(PicTime_default_default_XC16_FILE_TYPE_bin2hex)
add_library(PicTime_default_default_XC16_bin2hex OBJECT ${PicTime_default_default_XC16_FILE_TYPE_bin2hex})
    PicTime_default_default_XC16_bin2hex_rule(PicTime_default_default_XC16_bin2hex)
    list(APPEND PicTime_default_library_list "$<TARGET_OBJECTS:PicTime_default_default_XC16_bin2hex>")

endif()


# Main target for this project
add_executable(PicTime_default_image_cVwh67nv ${PicTime_default_library_list})

set_target_properties(PicTime_default_image_cVwh67nv PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${PicTime_default_output_dir}")
target_link_libraries(PicTime_default_image_cVwh67nv PRIVATE ${PicTime_default_default_XC16_FILE_TYPE_link})

# Add the link options from the rule file.
PicTime_default_link_rule( PicTime_default_image_cVwh67nv)

# Call bin2hex function from the rule file
PicTime_default_bin2hex_rule(PicTime_default_image_cVwh67nv)

