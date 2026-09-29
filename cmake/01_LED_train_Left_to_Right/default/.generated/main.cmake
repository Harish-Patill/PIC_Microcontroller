include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(01_LED_train_Left_to_Right_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_assemble)
add_library(A_01_LED_train_Left_to_Right_default_default_XC8_assemble OBJECT ${01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_assemble})
    A_01_LED_train_Left_to_Right_default_default_XC8_assemble_rule(A_01_LED_train_Left_to_Right_default_default_XC8_assemble)
    list(APPEND 01_LED_train_Left_to_Right_default_library_list "$<TARGET_OBJECTS:A_01_LED_train_Left_to_Right_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(A_01_LED_train_Left_to_Right_default_default_XC8_assemblePreprocess OBJECT ${01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_assemblePreprocess})
    A_01_LED_train_Left_to_Right_default_default_XC8_assemblePreprocess_rule(A_01_LED_train_Left_to_Right_default_default_XC8_assemblePreprocess)
    list(APPEND 01_LED_train_Left_to_Right_default_library_list "$<TARGET_OBJECTS:A_01_LED_train_Left_to_Right_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_compile)
add_library(A_01_LED_train_Left_to_Right_default_default_XC8_compile OBJECT ${01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_compile})
    A_01_LED_train_Left_to_Right_default_default_XC8_compile_rule(A_01_LED_train_Left_to_Right_default_default_XC8_compile)
    list(APPEND 01_LED_train_Left_to_Right_default_library_list "$<TARGET_OBJECTS:A_01_LED_train_Left_to_Right_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(01_LED_train_Left_to_Right_default_image_AkAQ1ppP ${01_LED_train_Left_to_Right_default_library_list})

set_target_properties(01_LED_train_Left_to_Right_default_image_AkAQ1ppP PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${01_LED_train_Left_to_Right_default_output_dir}")
target_link_libraries(01_LED_train_Left_to_Right_default_image_AkAQ1ppP PRIVATE ${01_LED_train_Left_to_Right_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
A_01_LED_train_Left_to_Right_default_link_rule( 01_LED_train_Left_to_Right_default_image_AkAQ1ppP)



