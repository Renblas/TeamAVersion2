#include <string>
#include "vexDevices.h"

using std::string;

// custom button class

class customButton
{
public:
    // ----- Variables -----
    bool isToggle = false;
    bool rawPressed = false;
    bool pressed = false;

    std::string buttonName;

    // ----- Functions -----

    // constructor
    customButton(bool toggle, std::string buttonName);
    // function called when callback occurs
    void onPressInput();
    // called once per frame, holds logic for if it is realeased
    void checkRelease();
    // called by above, is master list for determining if button is being pressed
    bool isReleased();


};

// Instances of class
customButton button_l1 = customButton(false, "l1");
customButton button_l2 = customButton(true, "l2");
customButton button_r1 = customButton(false, "r1");
customButton button_r2 = customButton(true, "r2");
customButton button_up = customButton(false, "up");
customButton button_down = customButton(false, "down");
customButton button_left = customButton(false, "left");
customButton button_right = customButton(false, "right");
customButton button_x = customButton(false, "x");
customButton button_b = customButton(false, "b");
customButton button_y = customButton(false, "y");
customButton button_a = customButton(false, "a");

/*
 *   Button class definitions
 */

customButton::customButton(bool toggle, string buttonName_f)
{
    isToggle = toggle;
    buttonName = buttonName_f;
}
bool customButton::isReleased()
{
    if (buttonName == "l1" && !Controller.ButtonL1.pressing())
        return true;
    else if (buttonName == "l2" && !Controller.ButtonL2.pressing())
        return true;
    else if (buttonName == "r1" && !Controller.ButtonR1.pressing())
        return true;
    else if (buttonName == "r2" && !Controller.ButtonR2.pressing())
        return true;
    else if (buttonName == "up" && !Controller.ButtonUp.pressing())
        return true;
    else if (buttonName == "down" && !Controller.ButtonDown.pressing())
        return true;
    else if (buttonName == "left" && !Controller.ButtonLeft.pressing())
        return true;
    else if (buttonName == "right" && !Controller.ButtonRight.pressing())
        return true;
    else if (buttonName == "x" && !Controller.ButtonX.pressing())
        return true;
    else if (buttonName == "y" && !Controller.ButtonY.pressing())
        return true;
    else if (buttonName == "a" && !Controller.ButtonA.pressing())
        return true;
    else if (buttonName == "b" && !Controller.ButtonB.pressing())
        return true;
    else
        return false;
}
void customButton::checkRelease()
{
    if (isReleased())
    {
        rawPressed = false;

        if (!isToggle)
        {
            pressed = rawPressed;
        }
    }
}
void customButton::onPressInput()
{
    rawPressed = true;

    if (isToggle)
    {
        pressed = !pressed;
    }
    else
    {
        pressed = rawPressed;
    }
}