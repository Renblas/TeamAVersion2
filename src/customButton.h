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
    customButton(bool toggle, std::string buttonName, controller Controller_f);
    // function called when callback occurs
    void onPressInput();
    // called once per frame, holds logic for if it is realeased
    void checkRelease();
    // called by above, is master list for determining if button is being pressed
    bool isReleased();

private:
    controller Controller_this;
};

// Instances of class
customButton button_l1 = customButton(false, "l1", Controller);
customButton button_l2 = customButton(true, "l2", Controller);
customButton button_r1 = customButton(false, "r1", Controller);
customButton button_r2 = customButton(true, "r2", Controller);
customButton button_up = customButton(false, "up", Controller);
customButton button_down = customButton(false, "down", Controller);
customButton button_left = customButton(false, "left", Controller);
customButton button_right = customButton(false, "right", Controller);
customButton button_x = customButton(false, "x", Controller);
customButton button_b = customButton(false, "b", Controller);
customButton button_y = customButton(false, "y", Controller);
customButton button_a = customButton(false, "a", Controller);

/*
 *   Button class definitions
 */

customButton::customButton(bool toggle, string buttonName_f, controller Controller_f)
{
    isToggle = toggle;
    buttonName = buttonName_f;
    Controller_this = Controller_f;
}
bool customButton::isReleased()
{
    if (buttonName == "l1" && !Controller_this.ButtonL1.pressing())
        return true;
    else if (buttonName == "l2" && !Controller_this.ButtonL2.pressing())
        return true;
    else if (buttonName == "r1" && !Controller_this.ButtonR1.pressing())
        return true;
    else if (buttonName == "r2" && !Controller_this.ButtonR2.pressing())
        return true;
    else if (buttonName == "up" && !Controller_this.ButtonUp.pressing())
        return true;
    else if (buttonName == "down" && !Controller_this.ButtonDown.pressing())
        return true;
    else if (buttonName == "left" && !Controller_this.ButtonLeft.pressing())
        return true;
    else if (buttonName == "right" && !Controller_this.ButtonRight.pressing())
        return true;
    else if (buttonName == "x" && !Controller_this.ButtonX.pressing())
        return true;
    else if (buttonName == "y" && !Controller_this.ButtonY.pressing())
        return true;
    else if (buttonName == "a" && !Controller_this.ButtonA.pressing())
        return true;
    else if (buttonName == "b" && !Controller_this.ButtonB.pressing())
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