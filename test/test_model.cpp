#include "CppUTest/TestHarness.h"
#include "model.h"  // unit under test
extern void simulate_script_load_failure(bool value);

TEST_GROUP(Test_Model)
{
};


// file_exists method
TEST(Test_Model, failed_script001)
{
    simulate_script_load_failure(true);

    Model* m = new Model;
    bool result = m->file_exists("lzsmgen.lua");  // file actually does exist
    delete m;
    CHECK_TEXT(result == false, "With no script, should return false.");
}

// io_failure method
TEST(Test_Model, failed_script002)
{
    simulate_script_load_failure(true);

    Model* m = new Model;
    bool result = m->io_failure();
    delete m;
    CHECK_TEXT(result == true, "With no script, should return true.");
}

#if 0
// test mocking
TEST(Test_Model, failed_script003)
{
    mock().expectOneCall("fake_function");

    Model* m = new Model;
    mock().checkExpectations();
    delete m;
}
#endif
