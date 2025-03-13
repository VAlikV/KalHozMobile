#include "env.hpp"

//TODO отключение ШИМА при маленьких значениях

void motors(){

    int speed_left_mapped = map(abs(speed_left), 0, 100, 0, 255);
    int speed_right_mapped = map(abs(speed_right), 0, 100, 0, 255);

    
    analogWrite(LEFT_MOTOR_EN, speed_left_mapped);
    digitalWrite(LEFT_MOTOR_A, !dir_left);
    digitalWrite(LEFT_MOTOR_B, dir_left);

    analogWrite(RIGHT_MOTOR_EN, speed_right_mapped);
    digitalWrite(RIGHT_MOTOR_A, !dir_right);
    digitalWrite(RIGHT_MOTOR_B, dir_right);
}