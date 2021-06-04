//first order = motor id
//second order = 0 is position's PID, 1 is velocity's PID
//third order = 0 is P, 1 is I, 2 is D

const float normalPID[4][2][3] = {{ {1,0.01,0},     {1,0.01,0}},
                                    {{10,0.1,0},    {1,0.01,0}},
                                    {{1,0.01,0},    {1,0.01,0}},
                                    {{1,0.01,0},    {1,0.01,0}}};
                                    
const float lockPID[4][2][3] = {{   {1,0.01,0},     {1,0.01,0}},
                                    {{65,5,0.05},   {1,0.01,0}},
                                    {{1,0.01,0},    {1,0.01,0}},
                                    {{10,1,0},      {1,0.01,0}}};




//fail {30,3,0.03}
//lock {65,5,0}