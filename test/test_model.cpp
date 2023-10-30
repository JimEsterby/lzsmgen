#include "CppUTest/TestHarness.h"
#include "model.h"  // unit under test
extern void simulate_script_load_failure(bool value);

TEST_GROUP(Test_Model)
{
};


// file_exists method
// Map to KAN-7
TEST(Test_Model, failed_script001)
{
    simulate_script_load_failure(true);

    Model* m = new Model;
    bool result = m->file_exists("lzsmgen.lua");  // file actually does exist
    delete m;
    CHECK_TEXT(result == false, "With no script, should return false.");
}

// io_failure method
// Map to KAN-7
TEST(Test_Model, failed_script002)
{
    simulate_script_load_failure(true);

    Model* m = new Model;
    bool result = m->io_failure();
    delete m;
    CHECK_TEXT(result == true, "With no script, should return true.");
}

// open_file method
// successful open of demo
// Map to KAN-10
TEST(Test_Model, opensuccess001)
{
    Model* m = new Model;
    m->open_file("..\\demos\\thermostat.json");
    STRCMP_EQUAL("..\\demos\\thermostat", m->module_name());
    delete m;
}

// open_file method
// NULL file name
// Map to KAN-10
TEST(Test_Model, openfailure001)
{
    Model* m = new Model;
    bool result = m->open_file(0);
    delete m;
    CHECK_TEXT(result == false, "Needs to fail gracefully");
}

// open_file method
// bogus file name
// Map to KAN-10
TEST(Test_Model, openfailure002)
{
    FAIL("TODO: This is not working, yet.");
    Model* m = new Model;
    bool result = m->open_file("thefiledoenstexist.json");
    delete m;
    CHECK_TEXT(result == false, "Needs to fail gracefully");
}

// check generation of module base name
// Map to KAN-19
TEST(Test_Model, basename001)
{
    Model* m = new Model;
    m->file_name("test_file.json");
    STRCMP_EQUAL("test_file", m->module_name());
    delete m;
}

