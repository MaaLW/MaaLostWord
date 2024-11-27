file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_executable(MaaLostWord ${srcs})
target_include_directories(MaaLostWord PUBLIC include)

target_link_libraries(
    MaaLostWord
    PUBLIC
        MaaFramework::MaaFramework
        MaaFramework::MaaToolkit
)

file(GLOB maafw_dlls "${PROJECT_SOURCE_DIR}/deps/MaaFramework/bin/*.dll")
add_custom_command(
    TARGET MaaLostWord
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${maafw_dlls}" $<TARGET_FILE_DIR:MaaLostWord>
    COMMAND_EXPAND_LISTS
    COMMENT "Copying MaaFramework DLLs"
    VERBATIM
)

add_custom_command(
    TARGET MaaLostWord
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${PROJECT_SOURCE_DIR}/deps/MaaFramework/share/MaaAgentBinary" "$<TARGET_FILE_DIR:MaaLostWord>/share/MaaAgentBinary"
    COMMENT "Copying MaaAgentBinaries"
    VERBATIM
)
#
# install(TARGETS MaaLostWord
#     EXPORT MaaLostWordTargets
#     COMPONENT MaaLostWord
#     RUNTIME DESTINATION bin
# )

#install(FILES $<TARGET_RUNTIME_DLLS:MaaLostWord> TYPE BIN)


