set(ZOAT_AI_ROOT   "${ZOAT_DIR_AI}/main.py")
set(ZOAT_AI_TARGET "${ZOAT_DIR_ROOT}/zappy_ai")

ADD_CUSTOM_TARGET(zappy_ai ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ${ZOAT_AI_ROOT} ${ZOAT_AI_TARGET}
                  COMMAND chmod +x ${ZOAT_AI_TARGET})
