add_library(db STATIC
    db.c    
)

target_include_directories(db PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)