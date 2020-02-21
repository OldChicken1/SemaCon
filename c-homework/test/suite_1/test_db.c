#include <unity.h>
#include <db.h>

void setUp(void){

}

void tearDown(void){

}

// test for open database
void test_open_1(void){
    db_t* db = db_new();
    // TEST_ASSERT_EQUAL_INT(0, db_open(db, "test.txt"));
    db_free(db);
}

void test_open_2(void){
    db_t* db = db_new();
    // TEST_ASSERT_EQUAL_INT(0, db_open(db, "test.txt"));
    db_free(db);
}
//testing for db not exist, create a new db
//this test can only run once, because after a single run
//the text file changed, and id 1, 3, 400, 4000 are already existed.
void test_insert_1(void){
    db_t* db = db_new();
    db_open(db, "new1.txt");
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 1));//id 1 already existed.
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 3));
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 400));
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 4000));
    db_free(db);
}

//test for existing file, inserting existing ids.
void test_insert_2(void){
    db_t* db = db_new();
    db_open(db, "test.txt");
    TEST_ASSERT_EQUAL_INT(0,db_insert(db, 1));//id 1 already existed.
    TEST_ASSERT_EQUAL_INT(0,db_insert(db, 3));
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 3));
    TEST_ASSERT_EQUAL_INT(0,db_insert(db, 400));
    TEST_ASSERT_EQUAL_INT(0,db_insert(db, 4000));
    TEST_ASSERT_EQUAL_INT(EEXIST,db_insert(db, 4000));
    db_free(db);
}


void test_find_1(void){
    db_t * db = db_new();
    db_open(db, "test.txt");
    TEST_ASSERT_EQUAL_INT(1, db_find(db, 1));
    TEST_ASSERT_EQUAL_INT(1, db_find(db, 3));
    TEST_ASSERT_EQUAL_INT(1, db_find(db, 400));
    TEST_ASSERT_EQUAL_INT(1, db_find(db, 4000));
    TEST_ASSERT_EQUAL_INT(0, db_find(db, 5));
    db_free(db);
}



void test_delete_1(void){
    db_t * db = db_new();
    db_open(db, "test.txt");
    TEST_ASSERT_EQUAL_INT(1, db_delete(db, 1));
    TEST_ASSERT_EQUAL_INT(1, db_delete(db, 3));
    TEST_ASSERT_EQUAL_INT(1, db_delete(db, 400));
    TEST_ASSERT_EQUAL_INT(1, db_delete(db, 4000));
    // TEST_ASSERT_EQUAL_INT(0, db_find(db, 5));
    db_free(db);
}
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_open_1);
    RUN_TEST(test_open_2);
    RUN_TEST(test_insert_1);
    RUN_TEST(test_insert_2);
    RUN_TEST(test_find_1);
    RUN_TEST(test_delete_1);
    return UNITY_END();
}