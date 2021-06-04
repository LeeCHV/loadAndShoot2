#include "CANOpen.h"
#include "motion.h"

class Motor {
    public:
        void init();
        void update(int motor1, int motor2, int motor3, int motor4);
        void manual();
        int getMaxPVelocity();
        void set_initial_angle(int angle);
        void set_shoot_angle(int angle);
        void set_rpm(int RPM);
        int initial_arm_angle;
        int shoot_angle;
        Motor();
        
        
        
        
    private:
        static const int maxPVelocity = 8700;
};







