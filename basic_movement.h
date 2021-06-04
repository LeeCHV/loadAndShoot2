#include "Motor.h"
#include "m3508.h"
#include "common.h"

#include "PIDsetting.h"
#include "motorID.h"
#include "pinout.h"

#include <ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>

static Motor maxon;
static m3508 m3508Set;


float loaderRotationMotor_pos[4]={0};  //(0)cw limit, (1)face up, (2)face down, (3)ccw limit
float arrowAngleMotor_pos[2]={0};  //(0)botton limit, (1)upper limit
float loaderLevelMotor_pos[7]={0};  //(0)left limit, (1)arrow 1, (2)arrow 2, (3)arrow 3, (4)arrow 4,(5)arrow 5, (6)right limit


bool allow_controllYaw=false;
int pos=0;

void controllYaw(const std_msgs::Float64& yawAngle)//ROS
{
    if(allow_controllYaw)
    {
        pos += yawAngle.data;
        m3508Set.set_position(yawMotor_id,pos);
        wait_us(50000);  
    }
    allow_controllYaw=false;
}

void delay_us(int time) // delay in micro sec
{
  Timer t;
  
  t.start();
  while (t.read()*1000000 <= time);
  t.stop();
  t.reset();
}

void update_all_m3508()
{
    m3508Set.c620_read();
    m3508Set.c620_write();
    
    delay_us(500);
}

void safe_delay(int ms) //1000 cycle ~ 1secs
{
    for(int i=0;i<(ms*2);i++)
    {
        update_all_m3508();
    }
}

void setAllPid(int mode){
    //need set v_pid first, than set p_pid
    //otherwise it will bug
    
    switch(mode){
        //normal
        case 0:
            for(int i = 0;i<4;i++){
                m3508Set.set_v_pid_param(i,normalPID[i][1][0],normalPID[i][1][1],normalPID[i][1][2]); 
                m3508Set.set_p_pid_param(i,normalPID[i][0][0],normalPID[i][0][1],normalPID[i][0][2]);               
            }
            break;
            
        case 1:
            //set default PID
            for(int i = 0;i<4;i++){
                m3508Set.set_v_pid_param(i,lockPID[i][1][0],lockPID[i][1][1],lockPID[i][1][2]);
                m3508Set.set_p_pid_param(i,lockPID[i][0][0],lockPID[i][0][1],lockPID[i][0][2]);              
            }
            
        default:
            break;
    }
}

void loaderLevelMove(int speed){
    //speed > 0 move to left
    //speed < 0 move to right
    m3508Set.set_velocity(loaderLevelMotor_id,speed);
    update_all_m3508();
}

void loaderLevelPosition(float targetPosition){
    //0 position is the start position
    
    m3508Set.set_position(loaderLevelMotor_id,targetPosition);
    update_all_m3508();
}

void loaderLevel_normal_PID()
{
    m3508Set.set_v_pid_param(loaderLevelMotor_id,normalPID[loaderLevelMotor_id][1][0],normalPID[loaderLevelMotor_id][1][1],normalPID[loaderLevelMotor_id][1][2]);
    m3508Set.set_p_pid_param(loaderLevelMotor_id,normalPID[loaderLevelMotor_id][0][0],normalPID[loaderLevelMotor_id][0][1],normalPID[loaderLevelMotor_id][0][2]);
}




void loaderRotation(int speed){
    //speed > 0 turn to right
    //speed < 0 turn to left
    m3508Set.set_velocity(loaderRotationMotor_id,speed);
    update_all_m3508();
}

void loaderRotationPosition(float targetPosition){
    //0 position is the start position
    
    m3508Set.set_position(loaderRotationMotor_id,targetPosition);
    update_all_m3508();
}

void loaderRotation_normal_PID()
{
    m3508Set.set_v_pid_param(loaderRotationMotor_id,normalPID[loaderRotationMotor_id][1][0],normalPID[loaderRotationMotor_id][1][1],normalPID[loaderRotationMotor_id][1][2]);
    m3508Set.set_p_pid_param(loaderRotationMotor_id,normalPID[loaderRotationMotor_id][0][0],normalPID[loaderRotationMotor_id][0][1],normalPID[loaderRotationMotor_id][0][2]);
}


void arrowAngleVelocity(int speed){
    //speed > 0 => lager angle of arrow
    //speed < 0 => smaller angle of arrow
    
    m3508Set.set_velocity(arrowAngleMotor_id,speed);
    update_all_m3508();
}

void arrowAnglePosition(float targetPosition){   
    m3508Set.set_position(arrowAngleMotor_id,targetPosition);
    update_all_m3508();
}


/*
void m3508_ini_pos(int m3508_id)
{
    switch(m3508_id)
    {
        
        yawMotor_id:
            break;
            
        loaderRotationMotor_id:
            break;
            
        arrowAngleMotor_id:   
            break;
            
        loaderLevelMotor_id:    
            break;
    }
}
*/