#include <stdio.h>
#include <stdint.h>

#include <limits.h>
#include <inttypes.h>

#include <pthread.h>

#include "generator.h"
#include "project_def.h"


uint32_t    main_printf_debug = 1;
#define MAIN_DEBUG(...)      if(main_printf_debug) { printf("MAIN >" __VA_ARGS__ ); }
#define MAIN_ERROR(...)      { printf("MAIN [ERROR] >" __VA_ARGS__ ); }

int32_t  i32var1 = 0;

const int32_t    KEY_SOURCE = 294967295;
/***************************** PUBLIC FUNCTION ********************************/
/**
 *\ingroup producer / consummer test
 *\function uint32_t main(int argc, char const *argv[])
 *\brief    starts the main routine for the code
 *
 *\return   always zero
 */
/******************************************************************************/
uint32_t main(int argc, char const *argv[]) {

  int32_t ret = 0;

  uint8_t u8_tab[32];
  int32_t i = 0;


 /** print a debug message : start routine */
  MAIN_DEBUG("start MAIN\n");

 /** call ui32ui32_random_generator with various input values */

 ret = i32_get_AES_key(24,KEY_SOURCE,u8_tab);
 if(ret >= 0)
 {
   for(i=0; i< 24; i++)
   printf("0x%02x ,",u8_tab[i]);

   printf("\n");
 }
 else
 {
   MAIN_ERROR("erreur i32_get_AES_key : erreur = %d\n", ret);
 }



 /** print a debug message : end routine */
  MAIN_DEBUG("end MAIN\n")

/** return zero at the end of execution */
  return 0;
}
