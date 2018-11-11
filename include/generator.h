#ifndef _GENERATOR_H_
#define _GENERATOR_H_


#ifdef __cplusplus
external "C" {
#endif

int32_t  i32_random_generator(uint32_t ui32_limit_param);
/* test : ui32_limit_param > 0 & < MAX_PARAM_GENERATOR
 * result : ui32_output_val always < ui32_limit_param & > 0
 */

 int32_t i32_get_sum_of_32bits_in_8bits(uint32_t ui32_original_32bits);
 /* test : ui32_original_32bits != 0
  * result : ui32_output_val != 0
  */

int32_t i32_get_sum_of_4bytes_in_1byte(uint32_t ui32_original_4bytes);
/* test : ui32_original_4bytes != 0
 * result : ui32_output_val != 0
 */

int32_t i32_get_random_1byte_circul_integration(uint8_t ui8_phi, uint8_t ui8_radius);
/* test : ui8_phi > 0 && ui8_radius > 0 && ui8_phi <= 32
 * result : ui32_output_val != 0
 */

 int32_t i32_get_AES_key( int32_t key_length, int32_t key_source, uint8_t *pu8_key_tab);


#ifdef __cplusplus
external "C"  }
#endif


#endif /* _GENERATOR_H_ */
