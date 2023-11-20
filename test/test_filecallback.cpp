#include "CppUTest/TestHarness.h"
#include "file_callback.h"
#include "model.h"
#include<cstdio>
#include<cstring>

FileCallback* fc;
char test_stream[80];

char* getline(const char* filename, int line_number);

TEST_GROUP(FileCallback)
{
    void setup()
    {
        theModel = new Model;
        fc = new FileCallback;
    }
    void teardown()
    {
        delete fc;
        delete theModel;
    }
};

// Map to KAN-22
TEST(FileCallback, Dep_001)
{
    CHECK_TEXT(true == fc->open("..\\test\\test001.json"), "Failed to open file.");
    CHECK_TEXT(true == fc->generate_code("C"), "Failed to generated code.");
    STRCMP_EQUAL("#include \"sensors.h\"\n", getline("..\\test\\test001.c", 6));
}

// Map to KAN-86
TEST(FileCallback, Internal_001)
{
    CHECK_TEXT(true == fc->open("..\\test\\test001.json"), "Failed to open file.");
    CHECK_TEXT(true == fc->generate_code("C"), "Failed to generated code.");
    STRCMP_EQUAL("static uint16_t timer;\n", getline("..\\test\\test001.c", 9));
}

char* getline(const char* filename, int line_number)
{
    std::FILE* f;
    char* retval = NULL;

    f = std::fopen(filename, "r");
    if (f != NULL)
    {
        for (int idx = 0; idx < line_number; idx++)
        {
            std::memset(test_stream, 0, sizeof(test_stream));
            if (NULL == std::fgets(test_stream, sizeof(test_stream), f))
            {
                return NULL;
            }
        }
        
        retval = test_stream;
        
        std::fclose(f);
    }

    return retval;
}
