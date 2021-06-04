#include "Motor.h"

//Serial pc(PA_2, PA_3, 115200);

Motor::Motor()
{
    init();
}

void Motor::init() 
{
    initial_arm_angle = -0;
    //////Maxon motor
    CANOpen_SETUP(1000000, 0.1);
    //wait(1.0);
    wait_us(1000000);
    STOP_SYNC();
    printf("Going to CLEAR_FAULT");
    SDO_CW(1, CLEAR_FAULT);
    SDO_CW(2, CLEAR_FAULT);
    SDO_CW(3, CLEAR_FAULT);
    SDO_CW(4, CLEAR_FAULT);
    printf("FAULT CLEARED.");
    SET_NMT(RESET_COMMU);
    //wait(0.01);
    wait_us(10000);

    //while(!PDO_INIT());

    SDO_CW(1, SHUT_DOWN);
    SDO_CW(2, SHUT_DOWN);
    SDO_CW(3, SHUT_DOWN);
    SDO_CW(4, SHUT_DOWN);
    SET_NMT(SET_OP);
    //wait(0.01);
    wait_us(10000);

    //**********CONFIGURATION DONE! READY FOR MOTION**********

    START_SYNC(0.05);
    //TEST P-VELOCITY MODE
    
    SET_OP_MODE(1, PPM);
    SET_OP_MODE(2, PPM);
    SET_OP_MODE(3, PPM);
    SET_OP_MODE(4, PPM);
    
    SET_MAX_FOLLOWING_ERROR(1, 5000);
    SET_MAX_FOLLOWING_ERROR(2, 5000);
    SET_MAX_FOLLOWING_ERROR(3, 5000);
    SET_MAX_FOLLOWING_ERROR(4, 5000);
    
    SET_PROFILE_VELOCITY(1, 1000);  //2000 rpm 2200 = 7.25m, 2100 = 6.7m, 2000 = 6.3m, 1900 = 6.0m, 1800 = 5.5m, 1700 = 5.0m, 1600 = 4.2m, 1500 = 3.5m, 1400 = 2.8m, 1300 = 2.2m
    SET_PROFILE_VELOCITY(2, 1000);  //rpm max = 9000?
    SET_PROFILE_VELOCITY(3, 1000);  //@ speed
    SET_PROFILE_VELOCITY(4, 1000);
//4950
    SET_MAX_P_VELOCITY(1, 25000);
    SET_MAX_P_VELOCITY(2, 25000);
    SET_MAX_P_VELOCITY(3, 25000);
    SET_MAX_P_VELOCITY(4, 25000);

    SET_P_ACCELERATION(1, 60000);//soft -> 30000, best -> 60000
    SET_P_ACCELERATION(2, 60000);
    SET_P_ACCELERATION(3, 60000);
    SET_P_ACCELERATION(4, 60000);

    SET_P_DECELERATION(1, 60000);//soft -> 30000, soft ->10000
    SET_P_DECELERATION(2, 60000);
    SET_P_DECELERATION(3, 60000);
    SET_P_DECELERATION(4, 60000);

    SET_QUICK_STOP_DECELERATION(1, 80000);//soft -> 10000
    SET_QUICK_STOP_DECELERATION(2, 80000);
    SET_QUICK_STOP_DECELERATION(3, 80000);
    SET_QUICK_STOP_DECELERATION(4, 80000);

    SET_MOTION_PROFILE_TYPE(1, SIN);
    SET_MOTION_PROFILE_TYPE(2, SIN);
    SET_MOTION_PROFILE_TYPE(3, SIN);
    SET_MOTION_PROFILE_TYPE(4, SIN);


    //////////////////////////////////////////////////////////////////

    SDO_CW(1, SHUT_DOWN);
    SDO_CW(2, SHUT_DOWN);
    SDO_CW(3, SHUT_DOWN);
    SDO_CW(4, SHUT_DOWN);

    SDO_CW(1, SWITCH_ON_ENABLE_OP);
    SDO_CW(2, SWITCH_ON_ENABLE_OP);
    SDO_CW(3, SWITCH_ON_ENABLE_OP);
    SDO_CW(4, SWITCH_ON_ENABLE_OP);
    printf("SDO Complete");
    //wait(2);    
}

void Motor::update(int motor1, int motor2, int motor3, int motor4) 
{
    //  motor1 is for passing maxon state to library
    switch(motor1)
    {
        //  motor1 = 0 initialize/normal angle (-15 degree)
        case 0:
        SET_TARGET_POSITION(1, initial_arm_angle);
        SET_TARGET_POSITION(2, initial_arm_angle);
        SET_TARGET_POSITION(3, initial_arm_angle);
        SET_TARGET_POSITION(4, initial_arm_angle); 
        printf("waiting");
        printf("\n\r"); 
        break;
        
        //  motor1 = 1 hold arrow (0degree)
        case 1:
        SET_TARGET_POSITION(1, initial_arm_angle+shoot_angle); //25000 -> 180 degree, 8930 -> 60 degree, 8186 -> 55 degree, 7442 -> 50 degree, 10418 -> 70 degree, 13395 ->90 degree, 14883 -> 100 degree   20836
        SET_TARGET_POSITION(2, initial_arm_angle+shoot_angle); // @ degree
        SET_TARGET_POSITION(3, initial_arm_angle+shoot_angle);
        SET_TARGET_POSITION(4, initial_arm_angle+shoot_angle);
        printf("shooted");
        printf("\n\r");  
        break;
        
        //  motor1 = 1 shoot (+70 degree)
        case 2:
        SET_TARGET_POSITION(1, initial_arm_angle+shoot_angle); //25000 -> 180 degree, 8930 -> 60 degree, 8186 -> 55 degree, 7442 -> 50 degree, 10418 -> 70 degree, 13395 ->90 degree, 14883 -> 100 degree   20836
        SET_TARGET_POSITION(2, initial_arm_angle+shoot_angle); // @ degree
        SET_TARGET_POSITION(3, initial_arm_angle+shoot_angle);
        SET_TARGET_POSITION(4, initial_arm_angle+shoot_angle);
        break;
    }
    
    /*
    if(motor1 == 0)
    {
        SET_TARGET_POSITION(1, initial_arm_angle);
        SET_TARGET_POSITION(2, initial_arm_angle);
        SET_TARGET_POSITION(3, initial_arm_angle);
        SET_TARGET_POSITION(4, initial_arm_angle); 
        printf("waiting");
        printf("\n\r");  
    }
    else
    {
        SET_TARGET_POSITION(1, initial_arm_angle+shoot_angle); //25000 -> 180 degree, 8930 -> 60 degree, 8186 -> 55 degree, 7442 -> 50 degree, 10418 -> 70 degree, 13395 ->90 degree, 14883 -> 100 degree   20836
        SET_TARGET_POSITION(2, initial_arm_angle+shoot_angle); // @ degree
        SET_TARGET_POSITION(3, initial_arm_angle+shoot_angle);
        SET_TARGET_POSITION(4, initial_arm_angle+shoot_angle);
        printf("shooted");
        printf("\n\r");  
    }
    */
    
    
    START_ABS_P(1);
    START_ABS_P(2);
    START_ABS_P(3);
    START_ABS_P(4);

    //wait(0.002);
    wait_us(2000);
    RPDO1_EXE(1, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(2, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(3, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(4, SWITCH_ON_ENABLE_OP);
    //wait(0.002);
    wait_us(2000);
}

void Motor::manual(){
    SET_P_ACCELERATION(1, 99999);
    SET_P_ACCELERATION(2, 99999);
    SET_P_ACCELERATION(3, 99999);
    SET_P_ACCELERATION(4, 99999);

    SET_P_DECELERATION(1, 99999);
    SET_P_DECELERATION(2, 99999);
    SET_P_DECELERATION(3, 99999);
    SET_P_DECELERATION(4, 99999);

    SET_QUICK_STOP_DECELERATION(1, 99999);
    SET_QUICK_STOP_DECELERATION(2, 99999);
    SET_QUICK_STOP_DECELERATION(3, 99999);
    SET_QUICK_STOP_DECELERATION(4, 99999);
}

int Motor::getMaxPVelocity()
{
    return maxPVelocity;
}

void Motor::set_initial_angle(int angle)
{
    initial_arm_angle = angle*14883/100;
}

void Motor::set_shoot_angle(int angle)
{
    shoot_angle = angle*14883/100;
}

void Motor::set_rpm(int RPM)
{
    SET_PROFILE_VELOCITY(1, RPM);  //2000 rpm 2200 = 7.25m, 2100 = 6.7m, 2000 = 6.3m, 1900 = 6.0m, 1800 = 5.5m, 1700 = 5.0m, 1600 = 4.2m, 1500 = 3.5m, 1400 = 2.8m, 1300 = 2.2m
    SET_PROFILE_VELOCITY(2, RPM);  //rpm max = 9000?
    SET_PROFILE_VELOCITY(3, RPM);  //@ speed
    SET_PROFILE_VELOCITY(4, RPM);
}







