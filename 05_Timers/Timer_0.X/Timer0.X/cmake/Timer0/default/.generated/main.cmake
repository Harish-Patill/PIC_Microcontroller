include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Timer0_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(Timer0_default_default_XC8_FILE_TYPE_assemble)
add_library(Timer0_default_default_XC8_assemble OBJECT ${Timer0_default_default_XC8_FILE_TYPE_assemble})
    Timer0_default_default_XC8_assemble_rule(Timer0_default_default_XC8_assemble)
    list(APPEND Timer0_default_library_list "$<TARGET_OBJECTS:Timer0_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(Timer0_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(Timer0_default_default_XC8_assemblePreprocess OBJECT ${Timer0_default_default_XC8_FILE_TYPE_assemblePreprocess})
    Timer0_default_default_XC8_assemblePreprocess_rule(Timer0_default_default_XC8_assemblePreprocess)
    list(APPEND Timer0_default_library_list "$<TARGET_OBJECTS:Timer0_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(Timer0_default_default_XC8_FILE_TYPE_compile)
add_library(Timer0_default_default_XC8_compile OBJECT ${Timer0_default_default_XC8_FILE_TYPE_compile})
    Timer0_default_default_XC8_compile_rule(Timer0_default_default_XC8_compile)
    list(APPEND Timer0_default_library_list "$<TARGET_OBJECTS:Timer0_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(Timer0_default_image_Kd5SFhnv ${Timer0_default_library_list})

set_target_properties(Timer0_default_image_Kd5SFhnv PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${Timer0_default_output_dir}")
target_link_libraries(Timer0_default_image_Kd5SFhnv PRIVATE ${Timer0_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
Timer0_default_link_rule( Timer0_default_image_Kd5SFhnv)



