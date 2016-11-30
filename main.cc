#include "main.h"


void menu()
{
	/*
	菜单函数.
	*/
	cout<<"\t\t elevator sim"<<endl;
	cout<<"\t\t\t press ctrl+c out"<<endl;

	cout<<"\t\t below is guid"<<endl;
	cout<<"\t\t key a.add passenger"<<endl;
	cout<<"\t\t from(3 4 20)"<<endl;
	cout<<"\t\t\t floor,goal_floor,giveup_time."<<endl;
}

void flash_command(int *Callup, int *Calldown,int *Callcar,int Number_of_passenger,P *pas_buffer)
{
	/*
	更新电梯命令
	*/
	for (int i = 0; i < Number_of_passenger; i++)
	{
		Callcar[pas_buffer[i].Floor] = 1;
		if (pas_buffer[i].direction == up)
		{
			Callup[pas_buffer[i].Goal_floor] = 1;
		}
		else
		{
			Calldown[pas_buffer[i].Goal_floor] = 1;
		}
	}

	for (int i = 0; i <= 4; i++)
	{
		cout << i << "Callup command:" << Callup[i] << endl;
		cout << i << "Calldown command:" << Calldown[i] << endl;
	}
}

int main()
{
	elevator Ele;

	int World_timeline;
	int Pas_number;

	/*
		添加乘客时使用的临时变量.
	*/
	char Temp_command;

	int Temp_state;
	int Temp_floor;
	int Temp_goal_floor;
	int Temp_giveup_time;

	int Callcar[5];
<<<<<<< Updated upstream
	int Callup[5];
	int Calldown[5];

	int First_cheack;

	Pas_number=0;
	World_timeline=0;

	memset(Calldown, 0, sizeof Calldown);
	memset(Callup, 0, sizeof Callup);
=======

	int Wait_line;

	Wait_line = 0;
	Pas_number=0;
	World_timeline=0;


>>>>>>> Stashed changes
	memset(Callcar, 0, sizeof Callcar);

	menu();
   
	Temp_command = 0;
	while (Temp_command != 27)
	{
<<<<<<< Updated upstream
		if (!_kbhit())
		{
			World_timeline++;
			Sleep(100);
			printf("World_timeline:%d ", World_timeline);

=======
		if (!kbhit())
		{
			World_timeline++;

			Ele.flash_passenger_giveup_time();
			Ele.getcommand();
			sleep(20);
			printf("World_timeline:%d ", World_timeline);
			
>>>>>>> Stashed changes
			/*
				更新电梯命令.
			*/

			//如果电梯处于可以改动的状态情况下，则可以获取电梯命令.
			Temp_state = Ele.get_state();
			switch (Temp_state)
			{
				case idle:
				{
<<<<<<< Updated upstream
					Ele.state_command_flash();
					cout << "Ele is idle" << endl;
=======
					Ele.idle_state_command_flash();
					cout << "Ele is idle " << Ele.get_floor() << endl;
>>>>>>> Stashed changes
					break;
				}
				case up:
				{
					Ele.run();
<<<<<<< Updated upstream
					cout << "Ele is up" << endl;
=======
					cout << "Ele is up " << Ele.get_floor() << endl;
>>>>>>> Stashed changes
					break;
				}
				case down:
				{
					Ele.run();
<<<<<<< Updated upstream
					cout << "Ele is down" << endl;
=======
					cout << "Ele is down " << Ele.get_floor() << endl;
>>>>>>> Stashed changes
					break;
				}
				case wait:
				{
					Ele.wait_func();
<<<<<<< Updated upstream
					cout << "Ele is wait" << endl;
					break;
				}
=======
					cout << "Ele is wait " << Ele.get_floor() << endl;
					break;
				}
				case up_to_idle:
				{
					Ele.idle_state_command_flash();
					Ele.run();
					cout << "Ele is up to idle " << Ele.get_floor() << endl;
				}
				case down_to_idle:
				{
					Ele.idle_state_command_flash();
					Ele.run();
					cout << "Ele is down_to_idle " << Ele.get_floor() << endl;
				}
>>>>>>> Stashed changes
			}
		}
		else
		{	
<<<<<<< Updated upstream
			Temp_command=_getch();
=======
			Temp_command=getch();
>>>>>>> Stashed changes

			if(Temp_command=='a')
			{
				cout<<"add passenger information"<<endl;
				/*
					添加乘客信息.
				*/
                cin>>Temp_floor>>Temp_goal_floor>>Temp_giveup_time;

				Ele.add(Temp_floor, Temp_goal_floor, Temp_giveup_time);
<<<<<<< Updated upstream
				Ele.getcommand();
=======
>>>>>>> Stashed changes
	        }
			else
			{
				cout<<"\t\t may be u input wrong."<<endl;
			}
		}
	}
}

