<<<<<<< Updated upstream
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Key_value.h"
#include "Passenger.h"
#include <cstring>
#include <queue>

using namespace std;


class elevator
{
#define Command_queue Ele.Command_queue
public:
	elevator();
	int get_state();
	void second_cheack();
	void getcommand();
	void state_command_flash();
	void Push_passenger_in(int floor);
	void Push_passenger_out(int floor);
	void add(int floor, int goal_floor, int giveup_time);
	void run();
	void wait_func();

	int get_floor()
	{
		return Floor;
	}
	int get_direction()
	{
		return Direction;
	}

private:
	int Floor;
	int Goal_floor;
	int The_state;
	int Direction;

	int Callcar[5];
	int Callup[5];
	int Calldown[5];

	int First_command;

	int The_idle_cnt;
	int The_up_cnt;
	int The_down_cnt;

	int The_up_idle_cnt;
	int The_down_idle_cnt;

	int The_wait_cnt;

	P Pas_buffer[1005];
	int Number_of_passenger;
};

elevator::elevator()
{
	/*
		初始化所有变量.
	*/
	Floor = 1;
	Goal_floor = -1;
	The_state = idle;
	Direction = -1;

	The_state = idle;

	The_idle_cnt = 0;
	The_up_cnt = 0;
	The_down_cnt = 0;

	The_up_idle_cnt = 0;
	The_down_idle_cnt = 0;

	The_wait_cnt = 0;

	memset(Callcar, 0, sizeof Callcar);
	memset(Callup, 0, sizeof Callup);
	memset(Calldown, 0, sizeof Calldown);

	Number_of_passenger = 0;
}

int elevator::get_state()
{
	/*
	返回电梯状态值.
	*/

	if (The_state == idle)
	{
		return idle;
	}

	if (The_state == up)
	{
		return up;
	}

	if (The_state == down)
	{
		return down;
	}
	if (The_state == wait)
	{
		return wait;
	}
}

void elevator::add(int floor, int goal_floor, int giveup_time)
{
	Pas_buffer[Number_of_passenger].Floor = floor;
	Pas_buffer[Number_of_passenger].Goal_floor = goal_floor;
	Pas_buffer[Number_of_passenger].Giveup_time = giveup_time;

	goal_floor>floor ? Pas_buffer[Number_of_passenger].direction = up :
		Pas_buffer[Number_of_passenger].direction = down;

	Number_of_passenger++;
	cout << "Add coustomer finish" << endl;
}

void elevator::getcommand()
{
	/*
	更新电梯命令
	*/
	for (int i = 0; i < Number_of_passenger; i++)
	{
		Callcar[Pas_buffer[i].Floor] = 1;
	}

	for (int i = 0; i <= 4; i++)
	{
		cout << i << "Callcar command:" << Callcar[i] << endl;
	}
}

void elevator::Push_passenger_in(int floor)
{
	int Dir=-1;

	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Pas_buffer[i].Floor == floor)
		{
			if (Pas_buffer[i].Giveup_time != -1)
			{
				if (Dir == -1 || Dir == Pas_buffer[i].direction)
				{
					Pas_buffer[i].Giveup_time = -1;
					Dir = Pas_buffer[i].direction;
				}
			}

			switch (Dir)
			{
				case up:
				{
					Callup[Pas_buffer[i].Goal_floor] = 1;
					break;
				}
				case down:
				{
					Calldown[Pas_buffer[i].Goal_floor] = 1;
					break;
				}
			}
		}
	}

	The_state = wait;
}

void elevator::Push_passenger_out(int floor)
{
	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Pas_buffer[i].Goal_floor == floor)
			if (Pas_buffer[i].Giveup_time == -1)
			{
				Number_of_passenger--;
				for (int j = i; j < Number_of_passenger - 1; j++)
				{
					Pas_buffer[j] = Pas_buffer[j + 1];
				}
			}
	}
	cout << "The " << floor << "passenger out" << endl;

	The_state = wait;
}

void elevator::state_command_flash()
{
	for (int i = 0; i <= 4; i++)
	{
		if (Callcar[i])
		{
			if (The_state == idle)
			{
				if (Floor == i)
				{
					Push_passenger_in(Floor);
				}
				else
				{
					i > Floor ? The_state = up : The_state = down;
					Goal_floor = i;
				}

				return;
			}
		}
	}

	for (int i = 0; i <= 4; i++)
	{
		if (Callup[i])
		{
			if (The_state == idle)
			{
				i > Floor ? The_state = up : The_state = down;
				Goal_floor = i;

				return;
			}
		}
	}

	for (int i = 0; i <= 4; i++)
	{
		if (Calldown[i])
		{
			if (The_state == idle)
			{
				i > Floor ? The_state = up : The_state = down;
				Goal_floor = i;

				return;
			}
		}
	}

	if (The_state == idle)
	{
		The_idle_cnt++;
		if (The_idle_cnt == Free_cnt_time)
		{
			The_idle_cnt = 0;
			Callcar[1] = 1;
		}
	}
}

void elevator::run()
{
	int temp_goal;
	bool Have_passenger_out;

	The_idle_cnt = 0;

	switch (The_state)
	{
		case up:
		{
			Have_passenger_out = false;

			if (The_up_cnt == 50)
			{
				for (int i = 0; i <= 4; i++)
				{
					if (Callcar[i] == 1 && i == Floor + 1)
					{
						Have_passenger_out = true;
					}
				}

				if (Have_passenger_out)
				{
					if (The_up_idle_cnt != Elevator_up_to_idle)
					{
						cout << "The_up_idle_cnt" << The_up_idle_cnt++ << endl;
					}
					else
					{
						Floor++;
						The_up_idle_cnt = 0;
						The_up_cnt = 0;
						Push_passenger_out(Floor);
					}
				}
				else
				{
					The_up_cnt = 0;
					Floor++;
				}
			}
			else
			{
				cout << "The_up_cnt" << The_up_cnt << endl;
				The_up_cnt++;
			}

			break;
		}

		case down:
		{
			Have_passenger_out = false;

			if (The_down_cnt == Elevator_down)
			{
				for (int i = 0; i < Number_of_passenger; i++)
				{
					if (Pas_buffer[i].Goal_floor == Floor - 1 && Pas_buffer[i].direction == down)
					{
						Have_passenger_out = true;
					}
				}
				if (Have_passenger_out)
				{
					if (The_down_idle_cnt != Elevator_down_to_idle)
					{
						The_down_idle_cnt++;
					}
					else
					{
						Floor--;
						The_state = wait;
						The_down_cnt = 0;
						Push_passenger_out(Floor);
					}
				}
				else
				{
					The_down_cnt = 0;
					Floor--;
				}
			}
			else
			{
				The_down_cnt++;
			}

			break;
		}

	}
}

void elevator::second_cheack()
{
	cout << "second cheack" << endl;
}

void elevator::wait_func()
{
	if (The_wait_cnt != Wait_passenger_time)
	{
		The_wait_cnt++;
	}
	else
	{
		The_wait_cnt = 0;
		The_state = idle;
	}
}
#endif
=======
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Key_value.h"
#include <cstring>
#include <queue>

using namespace std;


class elevator
{
#define Command_queue Ele.Command_queue
public:
	//init
	elevator();

	//return state
	int get_state();

	//add passenger get the information about passenger floor and goal
	void add(int floor, int goal_floor, int giveup_time);
	void getcommand();

	//flash passenger give up time
	void flash_passenger_giveup_time();

	//flash the command when is in the idle state
	void idle_state_command_flash();

	//control the dir of elevator
	void control_the_dir();

	//passenger in or out
	void Push_passenger_in(int floor);
	void Push_passenger_out(int floor);


	//cheack passenger whether can in the elevator or not
	bool cheack_passenger_in(int id);

	//cheack passenger whether can out the elevator or not
	//bool cheack_passenger_out(int id);

	//elevator work.
	void run();

	//count the wait time
	void count_wait_time(int cnt);

	//belows are some rubblish func.
	void wait_func();
	bool run_cheack();

	int get_floor()
	{
		return Floor;
	}
	int get_direction()
	{
		return Direction;
	}

private:
	int Floor;
	int The_state;
	int Direction;

	int Callcar[5];
	int Callup[5];
	int Calldown[5];

	int First_command;

	int The_idle_cnt;
	int The_up_cnt;
	int The_down_cnt;

	int The_up_idle_cnt;
	int The_down_idle_cnt;

	int The_wait_cnt;

	int wait_next_state;

	P Pas_buffer[1005];
	int Number_of_passenger;

	int Dir_value;

};

//ok
elevator::elevator()
{
	/*
		初始化所有变量.
	*/
	Dir_value = -1;

	Floor = 1;
	The_state = idle;
	Direction = -1;

	The_idle_cnt = 1;
	The_up_cnt = 1;
	The_down_cnt = 1;

	The_up_idle_cnt = 1;
	The_down_idle_cnt = 1;

	The_wait_cnt = 1;

	wait_next_state = idle;

	memset(Callcar, 0, sizeof Callcar);
	memset(Callup, 0, sizeof Callup);
	memset(Calldown, 0, sizeof Calldown);

	Number_of_passenger = 0;
}

//ok
int elevator::get_state()
{
	/*
	返回电梯状态值.
	*/
	return The_state;
}

//ok
void elevator::add(int floor, int goal_floor, int giveup_time)
{
	Pas_buffer[Number_of_passenger].Floor = floor;
	Pas_buffer[Number_of_passenger].Goal_floor = goal_floor;
	Pas_buffer[Number_of_passenger].Giveup_time = giveup_time;

	goal_floor>floor ? Pas_buffer[Number_of_passenger].direction = up :
		Pas_buffer[Number_of_passenger].direction = down;

	Number_of_passenger++;
}

//ok
void elevator::flash_passenger_giveup_time()
{
	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Pas_buffer[i].Giveup_time == 0)
		{
			for (int j = i; j < Number_of_passenger; j++)
			{
				Pas_buffer[j] = Pas_buffer[j + 1];
			}
			Number_of_passenger--;
		}
		else if (Pas_buffer[i].Giveup_time != -2 && Pas_buffer[i].Giveup_time != -1)
		{
			Pas_buffer[i].Giveup_time--;
		}
	}
}

//ok
void elevator::getcommand()
{
	/*
	更新电梯命令
	*/

	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Callcar[i]) continue;

		if (Pas_buffer[i].Giveup_time != -1 && Pas_buffer[i].Giveup_time != -2)
			Callcar[Pas_buffer[i].Floor] = 1;

	}
}

void elevator::idle_state_command_flash()
{
	getcommand();
	control_the_dir();


 	for (int i = Floor; i <= Floor+5; i++)
	{
		if (Callcar[i%5])
		{
			if (Floor == i%5)
			{
				Callcar[i%5] = 0;
				Push_passenger_in(Floor);
			}
			else
			{
				if(Dir_value==-1)
					i%5 > Floor ? The_state = up ,Dir_value=up: The_state = down,Dir_value=down;
				else The_state = Dir_value;
			}
			return;
		}
	}

	if (The_state == idle&&Floor != 1)
	{
		The_idle_cnt++;
		if (The_idle_cnt == Free_cnt_time)
		{
			The_idle_cnt = 0;
			if (Floor > 1)
			{
				The_state = down_to_idle;
			}
			else if (Floor < 1)
			{
				The_state = up_to_idle;
			}
			else The_state = idle;
		}
	}
	else The_idle_cnt = 0;
}

//ok
void elevator::control_the_dir()
{
	bool Have_more_up;
	bool Have_more_down;

	Have_more_up = false;
	Have_more_down = false;

	if (The_state == idle)
	{
		Dir_value = -1;
	}
	if (Dir_value == -1)
	{
		return;
	}
	else if (Dir_value == up)
	{
		for (int i = 0; i <= 4; i++)
		{
			if(Callcar[i])
				if (i > Floor)
				{
					Have_more_up = true;
				}
		}
		if (Have_more_up)
		{
			Dir_value = up;
		}
		else Dir_value = -1;
	}
	else if (Dir_value == down)
	{
		for (int i = 0; i <= 4; i++)
		{
			if (i < Floor)
			{
				Have_more_down = true;
			}
		}
		if (Have_more_down)
		{
			Dir_value = down;
		}
		else Dir_value = -1;
	}

	if (!Have_more_down && !Have_more_up)
	{
		The_state = idle;
		Dir_value = -1;
	}
}

//ok
void elevator::Push_passenger_in(int floor)
{
	Callcar[Floor] = 0;
	int cnt = 0;

	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Pas_buffer[i].Floor == floor)
		{
			if (Pas_buffer[i].Giveup_time > 0)
			{
				if (Dir_value == -1 || Dir_value == Pas_buffer[i].direction)
				{
					cnt++;
					Pas_buffer[i].Giveup_time = -1;
					Dir_value = Pas_buffer[i].direction;
					The_state = Dir_value;
					Callcar[Pas_buffer[i].Goal_floor] = 1;
				}
			}
		}
	}

	count_wait_time(cnt);

	cout << "The " << floor << "'s floor " << cnt << " passenger in the elevator" << endl;
	cout << "The command right now are below: " << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout <<i<<"'s floor: "<< Callcar[i] << endl;
	}
	getch();

	The_state = wait;
}

//ok
void elevator::Push_passenger_out(int floor)
{
	int cnt = 0;
	Callcar[floor] = 0;

	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (Pas_buffer[i].Goal_floor == floor)
			if (Pas_buffer[i].Giveup_time == -1)
			{
				cnt++;
				Pas_buffer[i].Giveup_time = -2;
			}
	}

	count_wait_time(cnt);
	cout << "The " << floor << "'s floor " << cnt << " passenger out the elevator" << endl;
	cout << "The command right now are below: " << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout << i << "'s floor: " << Callcar[i] << endl;
	}
	getch();

	The_state = wait;
}

//ok
bool elevator::cheack_passenger_in(int id)
{
	bool In_flag = true;

	if (Pas_buffer[id].Giveup_time == -1)	 In_flag = false;
	if (Pas_buffer[id].Giveup_time == -2) In_flag = false;
	if (Pas_buffer[id].Floor != Floor) In_flag = false;
	if (Pas_buffer[id].direction != Dir_value) In_flag = false;

	return In_flag;
}

//ok
bool elevator::run_cheack()
{
	bool Have_command = false;

	for (int i = 0; i <= 4; i++)
	{
		if (Callcar[i])
		{
			Have_command = true;
		}
	}

	return Have_command;
}

//ok
void elevator::run()
{
	if (!run_cheack()&&The_state!=up_to_idle&&The_state!=down_to_idle)
	{
		The_state = idle;
		return;
	}

	bool Goal_floor;
	bool Hava_passenger_out;
	bool Have_passenger_in;

	/*
		Goal_floor 标识当前方向的下一楼层是否需要停车
	*/
	Goal_floor = false;
	Have_passenger_in = false;
	Hava_passenger_out = false;

	The_idle_cnt = 0;

	switch (The_state)
	{
		case up:
		{
			if (The_up_cnt == Elevator_up)
			{
				for (int i = 0; i <= 4; i++)
				{
					if (Callcar[i] == 1 && i == Floor + 1)
					{
						Goal_floor = true;
					}
				}

				if (Goal_floor)
				{
					if (The_up_idle_cnt == Elevator_up_to_idle)
					{
						Floor++;
						The_up_idle_cnt = 0;
						The_up_cnt = 0;
						Callcar[Floor] = 0;

						for (int i = 0; i < Number_of_passenger; i++)
						{
							if (cheack_passenger_in(i))
							{
								Have_passenger_in = true;
							}
						}

						if (Have_passenger_in) Push_passenger_in(Floor);


						for (int i = 0; i < Number_of_passenger; i++)
						{
							if (Pas_buffer[i].Goal_floor == Floor&&Pas_buffer[i].Giveup_time==-1)
							{
								Hava_passenger_out = true;
							}
						}
						if (Hava_passenger_out) Push_passenger_out(Floor);
					}
					else
					{
						The_up_idle_cnt++;
					}
				}
				else
				{
					The_up_cnt = 0;
					Floor++;
				}
			}
			else
			{
				The_up_cnt++;
			}

			break;
		}

		case down:
		{
			if (The_down_cnt == Elevator_down)
			{
				for (int i = 0; i <= 4; i++)
				{
					if (Callcar[i] == 1 && i == Floor - 1)
					{
						Goal_floor = true;
					}
				}

				if (Goal_floor)
				{
					if (The_down_idle_cnt == Elevator_down_to_idle)
					{
						Floor--;
						The_down_idle_cnt = 1;
						The_down_cnt = 1;
						Callcar[Floor] = 1;

						for (int i = 0; i < Number_of_passenger; i++)
						{
							if (cheack_passenger_in(i))
							{
								Have_passenger_in = true;
							}
						}
						if (Have_passenger_in) Push_passenger_in(Floor);

						for (int i = 0; i < Number_of_passenger; i++)
						{
							if (Pas_buffer[i].Goal_floor == Floor&&Pas_buffer[i].Giveup_time == -1)
								Hava_passenger_out = true;
						}
						if (Hava_passenger_out) Push_passenger_out(Floor);
					}
					else
					{
						The_down_idle_cnt ++;
					}
				}
				else
				{
					The_down_cnt=1;
					Floor--;
				}
			}
			else
			{
				The_down_cnt++;
			}

			break;
		}
		
		case up_to_idle:
		{
				if (The_up_cnt == 51)
				{
					if (The_up_idle_cnt == Elevator_up_to_idle)
					{
						The_up_cnt = 1;
						The_up_idle_cnt = 1;
						Floor++;
						The_state = idle;
					}
					else
					{
						The_up_idle_cnt++;
					}
				}
				else
				{
					The_up_cnt++;
				}

			break;
		}
		
		case down_to_idle:
		{
			if (The_down_cnt == Elevator_down)
			{
				Floor--;
				The_down_cnt = 1;
				if (Floor == 1)
				{
					The_state = idle;
				}
				if (Floor == 2)
				{
					The_down_cnt -= Elevator_down_to_idle;
				}
			}
			else
			{
				The_down_cnt++;
			}

			break;
		}

	}
}

void elevator::count_wait_time(int cnt)
{
	if (cnt == 0)
		return;
	int Wait_temp_time;
	int Wait_real_time;
	double Number_of_wait_time_double;
	int Number_of_wait_time;

	Number_of_wait_time_double = 0;
	Number_of_wait_time = 0;
	Wait_real_time = 0;
	Wait_temp_time = cnt * 25;

	Number_of_wait_time_double = (double)Wait_temp_time / (double)Elevator_cheack_cnt;

	if (Number_of_wait_time_double > (int)Number_of_wait_time_double)
	{
		Number_of_wait_time =(int) Number_of_wait_time_double + 1;
	}

	The_wait_cnt += Number_of_wait_time*Elevator_cheack_cnt;
}

//idle
void elevator::wait_func()
{
	bool Have_new_passenger_in;
	
	Have_new_passenger_in = false;

	for (int i = 0; i < Number_of_passenger; i++)
	{
		if (cheack_passenger_in(i))
		{
			Have_new_passenger_in = true;
		}
	}

	if (Have_new_passenger_in)
	{
		Push_passenger_in(Floor);
		return;
	}
	else if (The_wait_cnt != 1)
	{
		The_wait_cnt--;
	}
	else
	{
		The_wait_cnt = 0;
		The_state = idle;
	}
}
#endif
>>>>>>> Stashed changes
