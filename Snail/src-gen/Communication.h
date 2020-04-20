#ifndef ROBOCALC_CONTROLLERS_COMMUNICATION_H_
#define ROBOCALC_CONTROLLERS_COMMUNICATION_H_

#include "rp0.h"
#include "RoboCalcAPI/Controller.h"
#include "DataTypes.h"

#include "SCommunication.h"

class Communication: public robocalc::Controller 
{
public:
	Communication(rp0& _robot) : robot(&_robot){};
	Communication() : robot(nullptr){};
	
	~Communication() = default;
	
	void Execute()
	{
		sCommunication.execute();
	}
	
	struct Channels
	{
		Communication& instance;
		Channels(Communication& _instance) : instance(_instance) {}
		
		EventBuffer* tryEmitUpdateLoc(void* sender, std::tuple<std::tuple<int, int>> args)
		{
			if(instance.sCommunication.canReceiveUpdateLoc(args))
				instance.sCommunication.updateLoc_in.trigger(sender, args);
				
			return &instance.sCommunication.updateLoc_in;
		}
		
		EventBuffer* tryEmitGet(void* sender, std::tuple<std::tuple<int, int>> args)
		{
			if(instance.sCommunication.canReceiveGet(args))
				instance.sCommunication.get_in.trigger(sender, args);
				
			return &instance.sCommunication.get_in;
		}
		
		EventBuffer* tryEmitConnect(void* sender, std::tuple<> args)
		{
			if(instance.sCommunication.canReceiveConnect(args))
				instance.sCommunication.connect_in.trigger(sender, args);
				
			return &instance.sCommunication.connect_in;
		}
		
		EventBuffer* tryEmitConnect_ack(void* sender, std::tuple<> args)
		{
			connect_ack_in.trigger(sender, args);
			return &connect_ack_in;
		}
		
		EventBuffer* tryEmitCoordinatesReq(void* sender, std::tuple<std::tuple<int, int>> args)
		{
			coordinatesReq_in.trigger(sender, args);
			return &coordinatesReq_in;
		}
		
		EventBuffer* tryEmitCoordinatesFiware(void* sender, std::tuple<std::tuple<St, St, St, St>> args)
		{
			if(instance.sCommunication.canReceiveCoordinatesFiware(args))
				instance.sCommunication.coordinatesFiware_in.trigger(sender, args);
				
			return &instance.sCommunication.coordinatesFiware_in;
		}
		
		EventBuffer* tryEmitCoordinates(void* sender, std::tuple<std::tuple<St, St, St, St>> args)
		{
			coordinates_in.trigger(sender, args);
			return &coordinates_in;
		}
		
		EventBuffer* tryEmitUpdateFiware(void* sender, std::tuple<std::tuple<int, int>> args)
		{
			updateFiware_in.trigger(sender, args);
			return &updateFiware_in;
		}
		
		EventBuffer* tryEmitUpdateReq(void* sender, std::tuple<> args)
		{
			updateReq_in.trigger(sender, args);
			return &updateReq_in;
		}
		
		EventBuffer* tryEmitUpdate(void* sender, std::tuple<std::tuple<int, int>> args)
		{
			if(instance.sCommunication.canReceiveUpdate(args))
				instance.sCommunication.update_in.trigger(sender, args);
				
			return &instance.sCommunication.update_in;
		}
		
		EventBuffer* tryEmitFinished(void* sender, std::tuple<> args)
		{
			if(instance.sCommunication.canReceiveFinished(args))
				instance.sCommunication.finished_in.trigger(sender, args);
				
			return &instance.sCommunication.finished_in;
		}
		
		struct Connect_ack_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = sender;
			}
		} connect_ack_in;
		struct CoordinatesReq_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<std::tuple<int, int>> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<std::tuple<int, int>> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_args = args;
				_sender = sender;
			}
		} coordinatesReq_in;
		struct Coordinates_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<std::tuple<St, St, St, St>> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<std::tuple<St, St, St, St>> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_args = args;
				_sender = sender;
			}
		} coordinates_in;
		struct UpdateFiware_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<std::tuple<int, int>> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<std::tuple<int, int>> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_args = args;
				_sender = sender;
			}
		} updateFiware_in;
		struct UpdateReq_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = sender;
			}
		} updateReq_in;
	};
	
	Channels channels{*this};
	
private:
	rp0* robot;
	SCommunication_StateMachine<Channels> sCommunication{*robot, channels};
};

#endif
