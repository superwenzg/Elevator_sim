#ifndef KEY_VALUE_H
#define KEY_VALUE_H


/*
	标识常数
*/
#define up 1
#define down 2
#define idle 3
#define wait 4
<<<<<<< Updated upstream
=======
#define up_to_idle 5
#define down_to_idle 6
>>>>>>> Stashed changes


/*
	定义重要常数
*/
//乘客进出时间25t
#define Wait_passenger_time 24
//最长待机时间300t
#define Free_cnt_time 299
//电梯最长等待进出时间
<<<<<<< Updated upstream
#define Elevator_wait_cnt 39
//电梯爬升一层楼的时间
#define Elevator_up 50
//电梯从上升状态减速到静止所需要的时间
#define Elevator_up_to_idle 13
=======
#define Elevator_wait_cnt 40
//The time of up
#define Elevator_up 51
//电梯从上升状态减速到静止所需要的时间
#define Elevator_up_to_idle 14
>>>>>>> Stashed changes
//电梯下降一层所需要的时间
#define Elevator_down 60
//电梯从下降到静止状态所需要的时间
<<<<<<< Updated upstream
#define Elevator_down_to_idle 22
//电梯检查乘客进出时间
#define Elevator_cheack_cnt 39
=======
#define Elevator_down_to_idle 23
#define Elevator_cheack_cnt 40
>>>>>>> Stashed changes


/*
	重要结构体.
	乘客信息结构体与电梯信息结构体.
*/
typedef struct
{
	int Floor;
	int Goal_floor;
	int Giveup_time;
	int State;
	int direction;
}P;

#endif