#ifndef T4_INSTALLED_DEVICES_AND_TOPICS_H
#define T4_INSTALLED_DEVICES_AND_TOPICS_H

#include <FlexCAN_T4.h>
 
#define INSTALLED_DEVICE_CT 4

typedef void (**device_ptr_array_t)(const CAN_message_t &msg);
typedef void (*topic_ptr_array_t)(const CAN_message_t &msg);

////////////////////////////////////////////////////////////////////////////////////////
// General Use DREQ Functions
 void dreq_nop(const CAN_message_t &msg);
 void dreq_res(const CAN_message_t &msg);


////////////////////////////////////////////////////////////////////////////////////////
// 0x0000 EMBDSYS  Embedded System Info
#define EMBSYS_TOPIC_CT     18

// EMBDSYS Topics
  // 0x0000 NOP
  // 0x0001- 0x000F RES
 void embsys_subsysct(const CAN_message_t &msg);
 void embsys_conndevct(const CAN_message_t &msg);

topic_ptr_array_t dreq_EMBSYS[EMBSYS_TOPIC_CT] =
  {
    dreq_nop,         // 0x0000
    dreq_res,         // 0x0001
    dreq_res,         // 0x0002
    dreq_res,         // 0x0003
    dreq_res,         // 0x0004
    dreq_res,         // 0x0005
    dreq_res,         // 0x0006
    dreq_res,         // 0x0007
    dreq_res,         // 0x0008
    dreq_res,         // 0x0009
    dreq_res,         // 0x000A
    dreq_res,         // 0x000B
    dreq_res,         // 0x000C
    dreq_res,         // 0x000D
    dreq_res,         // 0x000E
    dreq_res,         // 0x000F
    embsys_subsysct,  // 0x0010
    embsys_conndevct  // 0x0011
  };

////////////////////////////////////////////////////////////////////////////////////////
// 0x0001 PWRSYS  Power System
#define PWRSYS_TOPIC_CT     30

// PWRSYS Topics
  // 0x0000 RES
 void pwrsys_vbatt(const CAN_message_t &msg);           // 0x0001
 void pwrsys_vrail0(const CAN_message_t &msg);          // 0x0002
 void pwrsys_vrail1(const CAN_message_t &msg);          // 0x0003
 void pwrsys_vrail2(const CAN_message_t &msg);          // 0x0004
 void pwrsys_vrail3(const CAN_message_t &msg);          // 0x0005
 void pwrsys_vrail4(const CAN_message_t &msg);          // 0x0006
 void pwrsys_vrail5(const CAN_message_t &msg);          // 0x0007
 void pwrsys_vrail6(const CAN_message_t &msg);          // 0x0008
 void pwrsys_vrail7(const CAN_message_t &msg);          // 0x0009
  // 0x000A RES
 void pwrsys_ibatt(const CAN_message_t &msg);           // 0x000B
 void pwrsys_irail0(const CAN_message_t &msg);          // 0x000C
 void pwrsys_irail1(const CAN_message_t &msg);          // 0x000D
 void pwrsys_irail2(const CAN_message_t &msg);          // 0x000E
 void pwrsys_irail3(const CAN_message_t &msg);          // 0x000F
 void pwrsys_irail4(const CAN_message_t &msg);          // 0x0010
 void pwrsys_irail5(const CAN_message_t &msg);          // 0x0011
 void pwrsys_irail6(const CAN_message_t &msg);          // 0x0012
 void pwrsys_irail7(const CAN_message_t &msg);          // 0x0013
  // 0x0014 - 0x0019 RES
 void pwrsys_tbatt(const CAN_message_t &msg);           // 0x001A
 void pwrsys_trail0(const CAN_message_t &msg);          // 0x001B
 void pwrsys_trail1(const CAN_message_t &msg);          // 0x001C
 void pwrsys_trail2(const CAN_message_t &msg);          // 0x001D

topic_ptr_array_t dreq_PWRSYS[PWRSYS_TOPIC_CT] =
  {
    dreq_res,
    pwrsys_vbatt,
    pwrsys_vrail0,
    pwrsys_vrail1,
    pwrsys_vrail2,
    pwrsys_vrail3,
    pwrsys_vrail4,
    pwrsys_vrail5,
    pwrsys_vrail6,
    pwrsys_vrail7,
    dreq_res,
    pwrsys_ibatt,
    pwrsys_irail0,
    pwrsys_irail1,
    pwrsys_irail2,
    pwrsys_irail3,
    pwrsys_irail4,
    pwrsys_irail5,
    pwrsys_irail6,
    pwrsys_irail7,    // 0x0013
    dreq_res,
    dreq_res,
    dreq_res,
    dreq_res,
    dreq_res,
    dreq_res,
    pwrsys_tbatt,
    pwrsys_trail0,
    pwrsys_trail1,
    pwrsys_trail2
  };


////////////////////////////////////////////////////////////////////////////////////////
// 0x0002 WAYFDVL  Wayfinder DVL
#define WAYFDVL_TOPIC_CT    16

  // 0x0000 NOP
 void wayfdvl_velocity_3(const CAN_message_t &msg);
 void wayfdvl_velocity_x(const CAN_message_t &msg);
 void wayfdvl_velocity_y(const CAN_message_t &msg);
 void wayfdvl_velocity_z(const CAN_message_t &msg);
 void wayfdvl_velocity_e(const CAN_message_t &msg);
  // 4x res
 void wayfdvl_dist_mean(const CAN_message_t &msg);
 void wayfdvl_dist_1(const CAN_message_t &msg);
 void wayfdvl_dist_2(const CAN_message_t &msg);
 void wayfdvl_dist_3(const CAN_message_t &msg);
 void wayfdvl_dist_4(const CAN_message_t &msg);
  // 1x res


topic_ptr_array_t dreq_WAYFDVL[WAYFDVL_TOPIC_CT] =
  {
    dreq_nop,
    wayfdvl_velocity_3,
    wayfdvl_velocity_x,
    wayfdvl_velocity_y,
    wayfdvl_velocity_z,
    wayfdvl_velocity_e,
    dreq_res,
    dreq_res,
    dreq_res,
    dreq_res,
    wayfdvl_dist_mean,
    wayfdvl_dist_1,
    wayfdvl_dist_2,
    wayfdvl_dist_3,
    wayfdvl_dist_4,
    dreq_res
  };

////////////////////////////////////////////////////////////////////////////////////////
// 0x0003 MS5837  MS5837 Pressure and Temp Sensor
#define MS5837_TOPIC_CT     4

  // 0x0000 NOP
 void ms5837_data(const CAN_message_t &msg);
 void ms5837_depth(const CAN_message_t &msg);
 void ms5837_temp(const CAN_message_t &msg);

topic_ptr_array_t dreq_MS5837[MS5837_TOPIC_CT] =
  {
    dreq_nop,
    ms5837_data,
    ms5837_depth,
    ms5837_temp
  };



////////////////////////////////////////////////////////////////////////////////////////
// Device Array
device_ptr_array_t dreq_topic[INSTALLED_DEVICE_CT] =
  {
    dreq_EMBSYS,
    dreq_PWRSYS,
    dreq_WAYFDVL,
    dreq_MS5837
    
  };



// Super important wrapper macro for easy nested array access
 void dreq_access(uint16_t *device, uint16_t *topic, const CAN_message_t &msg);

#endif
