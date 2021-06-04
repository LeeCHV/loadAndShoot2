//  state_machine guide
//  motor number refer to draw.io
//  motor 0     Yaw             m3508   ID=0
//  motor 1     shooter motor   maxon
//  motor 2     arrow turn      m3508   ID=1
//  motor 3     arrow tail      m3508   ID=2
//  motor 5     arrow move      m3508   ID=3

const int yawMotor_id = 0;
const int loaderRotationMotor_id = 1;
const int arrowAngleMotor_id = 2;
const int loaderLevelMotor_id = 3;