#include "basic_movement.h"

int flip_stage = 0;

//  step 1
//  setup all perameter of maxon
//  all cilinder off
//  fix all m3508 in non-calibrate 0 degree

//  step 2
//  lock arm turn, calibrate arm move

//  step 3
//  turn arm move to middle, calibrate arm turn

//  step 4
//  lock arm turn, lock arm move, calibrate arrow tail

//  step 5
//  turn all to real 0 degree 
void initial_state_0()
{
    //  step 1
    //  setup all perameter of maxon
    //  all cilinder off
    gripper_relay_5=0;
    gripper_relay_4=0;
    gripper_relay_3=0;
    gripper_relay_2=0;
    gripper_relay_1=0;
    lift_relay=0;
    
    //  fix all m3508 in non-calibrate 0 degree
    loaderLevelPosition(0);
    loaderRotationPosition(0);
    arrowAnglePosition(0);
    
    
    //  step 2
    //  lock arm turn, calibrate arm move
    setAllPid(1);
    loaderLevel_normal_PID();
    while(!arm_move_limSwit_right)
    {
        loaderLevelMove(2000);
        loaderLevelMotor_pos[0] = m3508Set.global_angle[loaderLevelMotor_id];
    }
    while(!arm_move_limSwit_left)
    {
        loaderLevelMove(-2000);
        loaderLevelMotor_pos[6] = m3508Set.global_angle[loaderLevelMotor_id];
    }
    for(int i=0;i<5;i++)//calculate all arrow degree
    {
        loaderLevelMotor_pos[i+1]=loaderLevelMotor_pos[0]+(loaderLevelMotor_pos[6]-loaderLevelMotor_pos[0])*i/4;
    }
    loaderLevelPosition(loaderLevelMotor_pos[3]);
    safe_delay(2000);
    /*
    //for testing
    while(1)
    {
        loaderLevelPosition(loaderLevelMotor_pos[3]);
        safe_delay(2000);
    }
    */
    
    
    //  step 3
    //  turn arm move to middle, calibrate arm turn
    setAllPid(1);
    loaderRotation_normal_PID();
    while(!arm_turn_limSwit_right)
    {
        loaderRotation(1000);
        loaderRotationMotor_pos[0] = m3508Set.global_angle[loaderRotationMotor_id];
    }
    loaderRotationMotor_pos[1] = loaderRotationMotor_pos[0]- 15*3591*7/187;
    loaderRotationMotor_pos[2] = loaderRotationMotor_pos[1] -180*3591*7/187;
    loaderRotationPosition(loaderRotationMotor_pos[1]);
    safe_delay(1000);
    setAllPid(1);
    
    /*
    //for testing
    while(1)
    {
        loaderRotationPosition(loaderRotationMotor_pos[2]);
        safe_delay(2000);
    }
    */
    
    //  step 4
    //  lock arm turn, lock arm move, calibrate arrow tail
    //skipped
    
    //  step 5
    //  turn all to real 0 degree 
    //setAllPid(0);
    loaderLevelPosition(loaderLevelMotor_pos[3]);
    loaderRotationPosition(loaderRotationMotor_pos[1]);
    //arrowAnglePosition(arrowAngleMotor_pos[0]);
    safe_delay(3000);
    /*
    //for testing
    while(1)
    {
        safe_delay(2000);
    }
    */
}

void stand_by_1()
{
    //empty
}

void grip_2()
{
    gripper_relay_5=1;
    gripper_relay_4=1;
    gripper_relay_3=1;
    gripper_relay_2=1;
    gripper_relay_1=1;
    safe_delay(1000);
    lift_relay=1;
    safe_delay(1000);
    lift_relay=0;
}

void flip_3(int flip_stage_input)//just for testing
{
    flip_stage = flip_stage_input;
    
    setAllPid(1);
    loaderLevel_normal_PID();
    loaderLevelPosition((loaderLevelMotor_pos[4]+loaderLevelMotor_pos[5])/2);
    safe_delay(1500);
    setAllPid(1);
    loaderRotation_normal_PID();
    
    switch(flip_stage)
    {
        case 1://stage 1, flip to shoot
            for(float target_degree=loaderRotationMotor_pos[1];target_degree>loaderRotationMotor_pos[2];target_degree=target_degree-2)
            {
                loaderRotationPosition(target_degree);
                update_all_m3508();
            }
            loaderRotationPosition(loaderRotationMotor_pos[2]);
            safe_delay(1000);
            break;
            
        case 2://stage 2, flip to pick
            for(float target_degree=loaderRotationMotor_pos[2];target_degree<loaderRotationMotor_pos[1];target_degree=target_degree+2)
            {
                loaderRotationPosition(target_degree);
                update_all_m3508();
            }
            loaderRotationPosition(loaderRotationMotor_pos[1]);
            safe_delay(1000);
            break;
    }
    loaderLevel_normal_PID();
    loaderLevelPosition(loaderLevelMotor_pos[3]);
    safe_delay(4000);
}

void rotate_4()
{
}

void load_5()
{
}

void config_6()
{
    allow_controllYaw=true;
}

void shoot_7()
{
}

void reload_8()
{
}