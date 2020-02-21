add_executable(suite_1_app
    test_db.c
)

target_link_libraries(suite_1_app
    db
    Unity
)

add_test(suite_1_test suite_1_app)
