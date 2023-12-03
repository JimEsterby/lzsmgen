#include "cruise_demo.h"
extern "C" {
#include "cruise.h"
}

static cruise_state_t* state;
static CruiseControlUI* ui;

void run_sm(void* notUsed)
{
    state = cruise_step(state);
    ui->update();
    Fl::repeat_timeout(1.0, run_sm);
}

int main(int argc, char** argv)
{
    ui = new CruiseControlUI;
    state = initialize_cruise();

    Fl::visual(FL_DOUBLE | FL_INDEX);
    ui->show(argc, argv);
    Fl::add_timeout(1.0, run_sm);

    return Fl::run();
}
