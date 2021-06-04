#include "main.h"
#include "movementSet.h"



//ROS
ros::NodeHandle nh;


ros::Subscriber<std_msgs::Float64> sub("/shooter/yau_angle",&controllYaw);

void trig_Flag(const std_msgs::Int8 &cmd){
    //led= !led;
    switch(cmd.data)
    {
        /*
        case "shoot":
        break;
        
        case "load":
        break;
        
        case "set":
        break;
        
        case "stop":
        break;
        */
    }  
}
ros::Subscriber<std_msgs::Int8> sub1("/trig_Flag",&trig_Flag);


















int mainloop_state = 6;
int remainArrow = 0;
bool isLoaded = false;
bool arrowPosition[5] = {false,false,false,false,false};

///////////////////////////////////// m3508 initialize start /////////////////////////////////////
//CAN can1(PA_11, PA_12, 1000000);//RD,TD
CAN can2(PB_12, PB_13, 1000000);

int main(){
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub); 
    nh.subscribe(sub1);   
    
    m3508Set.m3508_init(&can2);     
    setAllPid(0);
    
    while(1){       
        nh.spinOnce();
        //loaderLevelMove(-2000);
        //loaderRotation(1000);
        //arrowAngleVelocity(-500);
        
        switch(mainloop_state){
            case 0:                                         
                initial_state_0();
                mainloop_state++;
                break;
                
            case 1:
                stand_by_1();
                mainloop_state++;
                break;
                
            case 2:
                grip_2();
                mainloop_state++;
                break;
                
            case 3:
                for(int i =1;i<=2;i++)//just for testing
                {
                    flip_3(i);
                } 
                
                while(1)
                {
                    //loaderRotationPosition(loaderRotationMotor_pos[2]);
                    update_all_m3508();
                }
                //mainloop_state++;
                break;
                
            case 4:
                rotate_4();
                //mainloop_state++;
                break;
                
            case 5:
                load_5();
                //mainloop_state++;
                break;
                
            case 6:
                config_6();
                //mainloop_state++;
                break;
                
            case 7:
                shoot_7();
                //mainloop_state++;
                break;
                
            case 8:
            reload_8();
            /*
            if(!isLoaded){
                    //remainArrow = reload();
                    
                    if(remainArrow > 0){
                        mainloop_state = 4;   
                    }
                    else{
                        mainloop_state = 0;   
                    }
                }
                else{
                    mainloop_state = 4;
                }
            */
                break;
                
            default:
                //stopAll();
                break;  
        }
    }    
}