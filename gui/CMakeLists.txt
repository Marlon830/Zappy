# Définissez les répertoires de votre projet
set(ZOAT_DIR_GUI_SRC "${ZOAT_DIR_GUI}/src")
set(ZOAT_DIR_GUI_INC "${ZOAT_DIR_GUI}/include")
set(ZOAT_DIR_GUI_INC_WINDOW "${ZOAT_DIR_GUI_INC}/window")

# Récupérez tous les fichiers sources dans le répertoire src
file(GLOB_RECURSE ZOAT_GUI_SRC "${ZOAT_DIR_GUI_SRC}/*.cpp")

# Ajoutez le répertoire include aux répertoires d'inclusion
include_directories(${ZOAT_DIR_GUI_INC} ${ZOAT_DIR_GUI_INC_WINDOW})

# Déclarez l'exécutable zappy_gui avec les fichiers sources récupérés
add_executable(
    zappy_gui
    ${ZOAT_GUI_SRC}
)

# Définissez les propriétés de l'exécutable
set_target_properties(
    zappy_gui
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ZOAT_DIR_ROOT}"
)


# Liez les bibliothèques à votre projet
target_include_directories(zappy_gui PRIVATE ${rlimgui_INCLUDE_DIRS})
target_link_libraries(zappy_gui raylib rlimgui imgui)
