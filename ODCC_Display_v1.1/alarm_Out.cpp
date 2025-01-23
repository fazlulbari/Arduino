#include "alarm_Out.h"

void dryAlarmOut_Loop() {
  if (fanFault_Alarm) {
    alarm_DryOut(FAN_FAULT_AL_PIN, ON);
  } else {
    alarm_DryOut(FAN_FAULT_AL_PIN, OFF);
  }

  if (smoke_Alarm) {
    alarm_DryOut(SMOKE_AL_PIN, ON);
  } else {
    alarm_DryOut(SMOKE_AL_PIN, OFF);
  }

  if (highTemp_Alarm) {
    alarm_DryOut(HIGH_TEMP_AL_PIN, ON);
  } else {
    alarm_DryOut(HIGH_TEMP_AL_PIN, OFF);
  }

  if (door_Status) {
    alarm_DryOut(DOOR_AL_PIN, ON);
  } else {
    alarm_DryOut(DOOR_AL_PIN, OFF);
  }
}