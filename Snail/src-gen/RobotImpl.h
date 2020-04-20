#ifndef __ROBOT_IMPL_H__
#define __ROBOT_IMPL_H__

#include "RP.h"

#include <set>
#include <algorithm>
#include <iostream>

class RobotImpl : public RP
{
public:
		
	bool shouldTriggerIn() override
	{
		std::cout<<"Should trigger event 'In'? (y/n)";
		char trigger;
		
		do { std::cin >> trigger; } while((trigger != 'y') && (trigger != 'n'));
		
		return trigger == 'y';
	}
	
	std::tuple<unsigned int> getInArgs() override
	{
		unsigned int ret;
		std::cout<<"Enter value for argument (unsigned int):";
		std::cin>>ret;
		return ret;
	};
	
	void tryEmitOut(void* sender, std::tuple<unsigned int> args) override
	{
		std::cout<<"Emitting signal Out"<<std::endl;
	}
	
	
};

#endif
