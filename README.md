# TeamAVersion2

## TODO

Major Stuff
- autonomous
	- 2 side
	- 3 side (DONE needs testing)
        
Minor Stuff:
- print launcher motor speed to controller screen
- draw kewl image to brain screen
- REMEMBER SD CARD!

## Reference

### Gear Ratios:
- red, 200 rpm, ratio6_1
- green, 400 rpm, ratio18_1
- blue, 600 rpm, ratio36_1
- special black, max 3600 rpm, just set as blue but when need rpm multiply by 6

### Roller Specs:
	- Flex Wheel  
		- 3 inch diameter  
		- 9.42477 circumference  

### Roller  
	- 2.4 inch diameter  
	- 7.53982 circumference  

### Ratio 
	9.42477 / 7.53982 = 1.24999 roller rotations per 1 flex rotations  
	need to move roller 1/4 rotations so...  
    1.24999^-1 = 0.800  
    0.800 * 1/4 = 0.20  

            aka to move roller precisely 1/4 turn, move motor by 0.2 rotations
                



    Controls:
        ---- Buttons on Back ----
        L1 - emergency untoggles intake and while held reverses intake, aka emergency clear
        L2 - Toggle, turns on intake and sucks disks (pun intended)
        R1 - Toggle, turns on disk launcher at current speed (default 85%)
        R2 - Roller Motor Clockwise

        ---- Arrow Pad ----
        Up - Endgame string thing clockwise, launch
        Down - Endgame string thing clockwise, reset
        Left - 
        Right - 

        ---- Letter Pad ----
        X (top) - Launch disk if criteria are met
        B (bottom) -
        Y (left) -
        A (right) - 

        ---- Axis ----
        Axis 4 (Left Knob X-Direction) -
        Axis 3 (Left Knob Y-Direction) - Left Drivetrain Motors fwd/back
        Axis 1 (Right Knob X-Direction) -
        Axis 2 (Right Knob Y-Direction) - Right Drivetrain Motors fwd/back


    Robot Class:

        Functions:
            robot();
                - Constructor

            void resetToDefault();
                - reset all variables to default
        
            void updateUserControl();
                - general function for all of user control stuff
        
            void getUserInput();
                - gets input from button objects / axis
        
            int processAxis(int input, int cutoff);
                - Process axis for reasons
        
            void firingProtocol();
                - firing checklist for firing a disk
        
            void updateDriveMotors();
                - applies input to drivechain motors
        
            void updateRollerMotor();
                - applies input to roller motor
        
            void updateIntakeMotor();
                - applies input to intake motor
        
            void adjustLauncherMotor();
                - makes adjustments to Launcher motor speed, automatically called by updateLauncherMotor()
        
            void updateLauncherMotor();
                - applies input to launcher motor
        
            void triggerEndgameLauncher();
                - Trigger Endgame


    customButton Class:
        
        Functions:
            customButton(bool toggle, std::string buttonName);
                - constructor
            
            void onPressInput();
                - function called when callback occurs
        
            void checkRelease();
                - called once per frame, holds logic for if it is realeased
        
            bool isReleased();
                - called by above, is master list for determining if button is being pressed
    
    

 
