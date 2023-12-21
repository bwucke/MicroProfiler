#pragma once
#include <map>
#include <cstdio>
#include <cstdint>
#include <time.h>

#define PRS 	Prof<> __ProfilerP(__func__);
#define PRST(x)	Prof<> __ProfilerP(x);

template <typename T = int>
class Prof
{
public:
	Prof(const char* func){
		Profile(func,1);
		func_=func;
	};
	~Prof(){
		Profile(func_,2);
	};
	static uint64_t GetTime(){
		struct timespec tp;
		clock_gettime(CLOCK_MONOTONIC, &tp);
		return (tp.tv_sec << 32) | tp.tv_nsec;
	};
	static void Profile(const char* func, int option){
		static std::map<const char*, uint64_t> stamps;
		static std::map<const char*, uint64_t> sums;
		static std::map<const char*, uint64_t> maxes;

		switch(option)
		{
		case 1:
			stamps[func] = GetTime();
		break;
		case 2:
		{
			uint64_t dt = GetTime() - stamps[func];
			sums[func] += dt;
			if(dt > maxes[func])
			{
				maxes[func] = dt;
			}
		}
		break;
		case 3:
		default:
			for(auto it = sums.begin(); it != sums.end(); it++)
			{
				printf("%30s : tot. %4u.%010us max %4u.%010us\n",it->first,
						(it->second >> 32) & 0xffffffff, it->second & 0xffffffff,
						( maxes[it->first] >> 32) & 0xffffffff, maxes[it->first] & 0xffffffff
						);
			}
			break;
		case 4:
			stamps.clear();
			sums.clear();
			maxes.clear();
			break;
		}
	};
	static inline void Report(){Profile("",3);};
	static inline void Reset(){Profile("",4);};
	const char* func_;
};

