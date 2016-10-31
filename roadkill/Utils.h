#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>

#define nullptr NULL

template<typename T>
void printN(T* l, int N){
	for(int i=0; i<N; ++i){
		Serial.print(l[i]);
		if(i+1 != N)
			Serial.print(',');
	}
	Serial.print('\n');
}

#endif
