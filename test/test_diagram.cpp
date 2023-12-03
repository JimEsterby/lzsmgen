#include "CppUTest/TestHarness.h"
#include "diagram.h"  // unit under test

Diagram* dia;

TEST_GROUP(Test_Diagram)
{
    void setup()
    {
        dia = new Diagram;
    }
    void teardown()
    {
        delete dia;
    }
};


// Determining transition destination (default state)
// Map to KAN-19
TEST(Test_Diagram, transition_dest001)
{
    CTransition* tn = new CTransition("dont care", "tn", 375, 320, 549, 216);
    CState* super = new CState("super", 537, 78, 1191, 512);
    CState* dest = new CState("dest", 566, 112, 662, 168, true);  // State that should be returned
    // Add a few more states to see if the software can be "confused".
    CState* ws1 = new CState("WrongState1", 590, 273, 1161, 477);
    CState* ws2 = new CState("WrongState2", 612, 319, 777, 438);
    CState* ws3 = new CState("WrongState3", 968, 307, 1137, 428);
    dia->add_transition(tn);
    dia->add_state(super);
    dia->add_state(dest);
    dia->add_state(ws1);
    dia->add_state(ws2);
    dia->add_state(ws3);
    CState* result = dia->transition_dest(*tn);

    STRCMP_EQUAL("dest", result->name());
}

// Determining transition destination (nested default states)
// Map to KAN-19
TEST(Test_Diagram, transition_dest002)
{
    CTransition* tn = new CTransition("dont care", "tn", 99, 201, 216, 278);
    CState* begin = new CState("begin", 28, 168, 103, 213);
    CState* a = new CState("a", 206, 124, 518, 393);
    CState* b = new CState("b", 221, 159, 490, 245, true);
    CState* d = new CState("d", 371, 189, 446, 234);
    CState* e = new CState("e", 396, 308, 471, 353);
    CState* dest = new CState("dest", 245, 189, 320, 234, true);

    dia->add_transition(tn);
    dia->add_state(begin);
    dia->add_state(a);
    dia->add_state(b);
    dia->add_state(d);
    dia->add_state(e);
    dia->add_state(dest);
    CState* result = dia->transition_dest(*tn);

    STRCMP_EQUAL("dest", result->name());
}

// Determining transition destination (nested states)
// Map to KAN-19
TEST(Test_Diagram, transition_dest003)
{
    CTransition* tn = new CTransition("dont care", "tn", 99, 201, 257, 215);
    CState* begin = new CState("begin", 28, 168, 103, 213);
    CState* a = new CState("a", 206, 124, 518, 393);
    CState* b = new CState("b", 221, 159, 490, 245);
    CState* d = new CState("d", 371, 189, 446, 234);
    CState* e = new CState("e", 396, 308, 471, 353);
    CState* dest = new CState("dest", 245, 189, 320, 234);

    dia->add_transition(tn);
    dia->add_state(begin);
    dia->add_state(a);
    dia->add_state(b);
    dia->add_state(d);
    dia->add_state(e);
    dia->add_state(dest);
    CState* result = dia->transition_dest(*tn);

    STRCMP_EQUAL("dest", result->name());
}
