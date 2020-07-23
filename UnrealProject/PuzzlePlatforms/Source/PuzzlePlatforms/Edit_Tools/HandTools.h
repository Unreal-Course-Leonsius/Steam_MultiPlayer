#pragma once

//#include "CoreMinimal.h"

#define LOGGING 1


#if LOGGING

#define LOG_S(x) UE_LOG(LogTemp, Warning, TEXT("STRING = %s"), *x)
#define LOG_I(x) UE_LOG(LogTemp, Warning, TEXT("Integer = %i"), x)

#else

#define LOG_S(x)
#define LOG_I(x)

#endif
