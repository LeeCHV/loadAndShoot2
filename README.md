# loadAndShoot2
// m3508 motor follow draw.io graph
//  motor 0     Yaw             m3508   ID=0
//  motor 1     shooter motor   maxon
//  motor 2     arrow turn      m3508   ID=1
//  motor 3     arrow tail      m3508   ID=2
//  motor 5     arrow move      m3508   ID=3

const int yawMotor_id = 0;
const int loaderRotationMotor_id = 1;
const int arrowAngleMotor_id = 2;
const int loaderLevelMotor_id = 3;

//pinout
InterruptIn button(USER_BUTTON);//(PC_13)     
CAN can2(PB_12, PB_13, 1000000);

DigitalIn arm_move_limSwit_right (PA_5);        //D13
DigitalIn arm_move_limSwit_left(PA_6);          //D12
DigitalIn arm_turn_limSwit_right(PA_7);         //D11
DigitalIn arm_turn_limSwit_left(PB_6);          //D10
DigitalIn arrow_tail_limSwit_right(PC_7);       //D9
DigitalIn arrow_tail_limSwit_left(PA_9);        //D8

DigitalOut gripper_relay_5(PA_8);  //D7
DigitalOut gripper_relay_4(PB_10); //D6
DigitalOut gripper_relay_3(PB_4);  //D5
DigitalOut gripper_relay_2(PB_5);  //D4
DigitalOut gripper_relay_1(PB_3);  //D3
DigitalOut lift_relay(PA_10);      //D2
