# TeamAVersion2

main.cpp is the file with the code, is in /src

----------  REFERENCE  ---------

    TODO:
        - pnuematics
        - autonomous
            - 2 side
            - 3 side
        Minor Stuff:
        - print launcher motor speed to controller screen
        - switch roller motor to red?
        - draw kewl image to brain screen
            - REMEMBER SD CARD!
            

    Gear Ratios:
        red, 100 rpm, ratio6_1
        green, 200 rpm, ratio18_1
        blue, 600 rpm, ratio36_1
        special black, max 3600 rpm, just set as blue but when need rpm multiply by 6


    Controls:
        ---- Buttons on Back ----
        L1 - emergency untoggles intake and while held reverses intake, aka emergency clear
        L2 - Toggle, turns on intake and sucks disks (pun intended)
        R1 - Toggle, turns on disk launcher at current speed (default 85%)
        R2 -

        ---- Arrow Pad ----
        Up - Roller Motor Clockwise
        Down - Roller Motor Counter-Clockwise
        Left - Increase Disk Launcher Speed
        Right - Decrease Ddisk Launcher Speed

        ---- Letter Pad ----
        X (top) - Launch disk if criteria are met
        B (bottom) -
        Y (left) -
        A (right) - Launch Endgame string thing

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
    
    

 
