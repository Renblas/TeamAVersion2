#include "customButton.h"

// Every button has its own object and global function, global function is for callbacks

// Back Buttons
void l1_press();
void l2_press();
void r1_press();
void r2_press();
// Arrow buttons
void up_press();
void down_press();
void left_press();
void right_press();
// Letter Buttons
void x_press();
void b_press();
void y_press();
void a_press();

void buttonCallbackInit() {

    // set keyboard callbacks

    Controller.ButtonL1.pressed(l1_press);
    Controller.ButtonL2.pressed(l2_press);
    // Controller.ButtonR1.pressed(r1_press);
    Controller.ButtonR2.pressed(r2_press);
    Controller.ButtonUp.pressed(up_press);
    Controller.ButtonDown.pressed(down_press);
    // Controller.ButtonLeft.pressed(left_press);
    // Controller.ButtonRight.pressed(right_press);
    // Controller.ButtonX.pressed(x_press);
    Controller.ButtonB.pressed(b_press);
    Controller.ButtonY.pressed(y_press);
    Controller.ButtonA.pressed(a_press);
}

// Button Callback Functions

void l1_press()
{
    button_l1.onPressInput();
}
void l2_press()
{
    button_l2.onPressInput();
}
void r1_press()
{
    button_r1.onPressInput();
}
void r2_press()
{
    button_r2.onPressInput();
}
void up_press()
{
    button_up.onPressInput();
}
void down_press()
{
    button_down.onPressInput();
}
void left_press()
{
    button_left.onPressInput();
}
void right_press()
{
    button_right.onPressInput();
}
void x_press()
{
    button_x.onPressInput();
}
void b_press()
{
    button_b.onPressInput();
}
void y_press()
{
    button_y.onPressInput();
}
void a_press()
{
    button_a.onPressInput();
}