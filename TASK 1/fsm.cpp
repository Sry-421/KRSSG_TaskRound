/*Program to emulate a lift using Finite State Machine*/
/*Task accomplished by assuming different states of the object and events affecting those object*/
/*
	state  :
	->UP
	->DOWN
	->STOP

	events :
	->reaching a floor with up or down key pressed
	->reaching a floor with lift button pressed	
	->reaching the maximum floor on either side 			
*/


#include <bits/stdc++.h>
using namespace std;

enum STATE
{
	UP=1,STOP=0,DOWN=-1
};


void UPDATE();
void STATE_TRANSITION();
STATE OPTIMIZE(int*,int*,int,int);
STATE CHECK_STOP(int*,int*);
bool remainingtasks(int*,int*);



STATE state=STOP;
int current,max_below,max_above,min_below,min_above,n;


int main()
{
	//------------------Input----------------------
	cout << "No. of floor?" <<endl;
	cin>>n;
	cout << "Initial floor?" <<endl;
	int initial_floor;
	cin>>initial_floor;

	int floor_event[n+1]={0};
	int lift_event[n+1];
	
	cout << "Input on floors: 2: Up and Down  1:Up  -1:Down 0:None"<<endl;
	for(int i=0;i<=n;i++)
	{
		lift_event[i]=0;
		if(i==initial_floor)
			continue;
		cout <<"Floor:"<<i<<endl;
		cin >> floor_event[i];
	}

	int x;
	cout <<"Enter buttons pressed in lift:  -1 to stop"<<endl;
	cin >> x;
	int p=x;
	while(x!=-1)
	{
		lift_event[x]=1;
		cin >> x;
	}

	min_above=initial_floor;
	max_above=initial_floor;
	min_below=initial_floor;
	max_below=initial_floor;
//-----------------------------------Input--------------------------------------


	//Calculating initial direction by optimizing total distance travelled
	state =OPTIMIZE(lift_event,floor_event,initial_floor,p);
	
	//Lift traversal begins
	current=initial_floor;
	cout << "Lift begins at :"<<current<<endl;



//---------------------------------------------------------------	
	while(remainingtasks(floor_event,lift_event))
	{
		if(!(CHECK_STOP(lift_event,floor_event)))
			cout <<"Lift stops  at:"<<current<<endl;

		STATE_TRANSITION();
		UPDATE();
	}	
//----------------------------------------------------------------
	

	return 0;
}



void STATE_TRANSITION()
{
	if(current==max_below || current==max_above)
	{
		if(state==UP)
			state=DOWN;
		else if(state==DOWN)
			state=UP;
	}

}

void UPDATE()
{
	current=current+state;
}


STATE CHECK_STOP(int* lift_event,int* floor_event)
{
	int stop=0;
	if(current==max_below || current==max_above)
	{
		if(lift_event[current]!=0 || floor_event[current]!=0)
		stop=1;
		lift_event[current]=0;
		floor_event[current]=0;
	}
	else
	{
		if(floor_event[current]==2)
		{
			floor_event[current]=state*(-1);
			stop=1;
		}
		else if(floor_event[current]==state)
		{
			floor_event[current]=0;
			stop=1;
		}
		if(lift_event[current]==1)
		{
			lift_event[current]=0;
			stop=1;
		}			
	}

	if(stop)
		return STOP;
	else
		return UP;
}


bool remainingtasks(int a[],int b[])//Checking for unremaining events
{
	for(int i=0;i<=n;i++)
	{
		if(a[i]!=0 || b[i]!=0)
			return true;
	}
	return false;
}

STATE OPTIMIZE(int* lift_event,int* floor_event,int initial_floor,int p)
{
	if(initial_floor==0)
		return UP;
	else if(initial_floor==n)
		return DOWN;
	else
	{
		int flag=1;
		for(int i=initial_floor+1;i<=n;i++)
		{
			if(lift_event[i]==1 || floor_event[i]!=0)
				max_above=i;

			if((floor_event[i]==-1 || floor_event[i]==2) && flag==1)
			{
				flag=0;
				min_above=i;
			}
		}

		flag=1;
		for(int i=initial_floor-1;i>=0;i--)
		{
			if(lift_event[i]==1 || floor_event[i]!=0)
				max_below=i;
			if(flag==1 && (floor_event[i]==1 || floor_event[i]==2))
			{
				flag=0;
				min_below=i;
			}
		}



		if(min_above==initial_floor)
		{
			min_above=max_above;
		}
		if(min_below==initial_floor)
		{
			min_below=max_below;
		}

		if(min_above+min_below<2*initial_floor)
			return UP;
		else if(min_above+min_below>2*initial_floor)
			return DOWN;
		else
		{
			if(p>initial_floor)
				return UP;
			else
				return DOWN;
		}
	}
}