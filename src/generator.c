#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <limits.h>
#include <inttypes.h>

#include <time.h>
#include <stdlib.h>

#include <pthread.h>

#include "generator.h"
#include "project_def.h"

uint32_t    gen_printf_debug = 0;
#define GEN_DEBUG(...)      if(gen_printf_debug) { printf("GEN > " __VA_ARGS__ ); }
#define GEN_ERROR(...)      { printf("GEN [ERROR] > " __VA_ARGS__ ); }

#define LSB_32BITS_NUMBER   0x00000001      /** 1st bit : LSB bit */
#define MSB_32BITS_NUMBER   0x10000000      /** 32nd bit : MSB bit */

#define MSB_4BYTES_NUMBER   0xFF000000      /** 4th byte : MSB byte */
#define LSB_4BYTES_NUMBER   0x000000FF      /** 1st byte : LSB byte */

#define LSB_4BITS_NUMBER    0x0000000F
#define LSB_8BITS_NUMBER    0x000000F0

#define EE_4BYTES_NUMBER    0x00000F0F      // 0 & 8
#define EO_4BYTES_NUMBER    0x0000F0F0      // 4 & 12
#define OE_4BYTES_NUMBER    0x000F0F00      // 8 & 16
#define OO_4BYTES_NUMBER    0x00F0F000      // 12 & 20

/*******************************************************************************/
/** \ingroupe : producer / consummer test
 *  \function : uint32_t  i32_random_generator(uint32 ui32_limit_param)
 *  \brief : this function generates a random number and gives it back as output
 *  \param : ui32_limit_param : the generated value should be smaller than this
 *  \return : -1 if error, > 0 if okay
 */
 /******************************************************************************/
int32_t  i32_random_generator(uint32_t ui32_limit_param)
{
  int32_t  i32_return_val = 0;
  int32_t  i32_error = -1;

  /** we test the parameter value, it should be grater than zero and, in all cases
   * smaller than the defined MAX_PARAM_GENERATOR
   */
  if(ui32_limit_param <= MAX_PARAM_GENERATOR && ui32_limit_param > 0)
  {
    /** we start the srand call based on time value, this allow us to have a better
     * randomness after the execution of the code
     */

    GEN_DEBUG("given limit value : %d\n", ui32_limit_param);
    srand(time(NULL));

    /** loop : while the return value is devisible by the input param, than we stay
     * on the loop
     */
    do {
      i32_return_val = rand();
    } while( (i32_return_val / ui32_limit_param) != 0);
  }
  else
  {
    /** if the input value is not as expected, we set an error value and we leave
     */
    GEN_ERROR("invalid limit value\n");
    i32_error = -1;
    return i32_error;
  }

  /** as at this point of the execution, we give back the result and we leave
   */

  GEN_DEBUG("generated random number : %d\n", i32_return_val);
  return i32_return_val;
}

/*******************************************************************************/
/** \ingroupe producer / consummer test
 * \fn int32_t i32_get_sum_of_32bits_in_8bits(uint32_t original_32bits)
 * \brief this routine takes 32bits numbers and generates from it an 8bits numbers
 *        based on binary operations
 * \param original_32bits : 32bits number to begin with
 * \return returns -1 if the parameter is nil, otherwise the resulting number
 */
/*******************************************************************************/
int32_t i32_get_sum_of_32bits_in_8bits(uint32_t original_32bits)
{
  int32_t ret = -1;
  int32_t bit_count = 0;
  int32_t bit_sum = 0;

  /** first, we test the value of the parameter */
  if(original_32bits == (int32_t)0)
  {
    /** if nil, we print an error message and we leave */
    GEN_ERROR("generation impossible avec un nombre nul : %d\n");
    return ret;
  }
  else
  {
    for(bit_count = 1; bit_count <= 32; bit_count++)
    {
      bit_sum = bit_sum + ((original_32bits>>bit_count) & LSB_32BITS_NUMBER);
    }
  }

  ret = (int32_t )bit_sum;

  GEN_DEBUG("generated number from 0x%08x is %d\n",original_32bits, ret);
  return ret;
}

/*******************************************************************************/
/** \ingroupe producer / consummer test
 * \fn int32_t i32_get_sum_of_4bytes_in_1byte(uint32_t ui32_original_4bytes)
 * \brief this routine takes 4bytes number and generates from it an 1byte numbers
 *        based on binary operations
 * \param original_32bits : 32bits number to begin with
 * \return returns -1 if the parameter is nil, otherwise the resulting number
 */
/*******************************************************************************/
int32_t i32_get_sum_of_4bytes_in_1byte(uint32_t ui32_original_4bytes)
{
  int32_t ret = -1;
  int32_t byte_count = 0;
  int32_t byte_sum = 0;

  /** first, we test the value of the parameter */
  if(ui32_original_4bytes == (int32_t)0)
  {
    /** if nil, we print an error message and we leave */
    GEN_ERROR("generation impossible avec un nombre nul\n");
    return ret;
  }
  else
  {
    /** we make an 8bits translation to get the next 8bits as a LSB */
    for(byte_count = 0; byte_count <= 24; byte_count=byte_count+8)
    {
      /** we make a sum out of the LSB and the precedent one */
      byte_sum = ((byte_sum & LSB_4BYTES_NUMBER )+ ((ui32_original_4bytes >> byte_count) & LSB_4BYTES_NUMBER)) & LSB_4BYTES_NUMBER;
    }
  }

  /** once we've finished, we write the result to the output retval */
  ret = (int32_t )byte_sum & LSB_4BYTES_NUMBER;

  GEN_DEBUG("generated number from 0x%08x is %d\n",ui32_original_4bytes, ret);
  return ret;
}

/*******************************************************************************/
/** \ingroupe
 *  \fn int32_t i32_get_random_1byte_circul_integration(uint8_t ui8_phi, uint8_t ui8_radius)
 *  \brief  we calculate the area of a circul portion based on the given phi ( this is turned into Pi by a 32 portions )
 *          and the value of the radius
 *  \param ui8_phi : this is an approximation to the value of the angle
 *  \param ui8_radius : the radius of the circle
 *
/*  \return
/*******************************************************************************/
int32_t i32_get_random_1byte_circul_integration(uint8_t ui8_phi, uint8_t ui8_radius)
{
  int32_t ret = -1;
  int32_t i32_prod = 0;
  int32_t i32_2pi = 8;

  int32_t i32_first_result = 0;
  int32_t i32_mid_result = 0;
  int32_t i32_final_result = 0;
  int32_t i32_result = 0;
  /** test if the parameters are different from zero */
  if (ui8_phi == 0 || ui8_radius == 0)
  {
    /** if nil, we print an error message and we leave */
    GEN_ERROR("generation impossible avec un nombre nul\n");
    return ret;
  }
  else
  {
      if(ui8_phi > 32)
      {
        GEN_ERROR("valeur non autorisée pour phi : %d\n", ui8_phi);
        return ret;
      }
      else
      {
        /** we calculate the amount of 2xPi we need based on Phi value */
        i32_2pi = i32_2pi * ((uint32_t)ui8_phi & LSB_4BYTES_NUMBER);

        /** we calculate the value of the radius power 2 */
        i32_prod = ((uint32_t)ui8_radius & LSB_4BYTES_NUMBER) * ((uint32_t)ui8_radius & LSB_4BYTES_NUMBER);

        /** we get the value of Phi x Radius power 2 */
        i32_first_result = i32_2pi * i32_prod ;
      }
      GEN_DEBUG("first 0x%08x\n",i32_first_result);
      /** finaly we need to get only 8bits out of the calculation we made */
      /** based on the combination of Phi and Radius and the fact that some are event and some are odd
          we take one part or another of the resulting number */
      if((ui8_phi % 2) == 0 && (ui8_radius % 2) == 0)
      {
        GEN_DEBUG("is EE\n");
        i32_mid_result = i32_first_result & EE_4BYTES_NUMBER;
        GEN_DEBUG("mid 0x%08x\n",i32_mid_result);
        GEN_DEBUG("mid 1 : 0x%08x\n",((i32_mid_result >> 0) &  LSB_4BITS_NUMBER));
        GEN_DEBUG("mid 2 : 0x%08x\n",((i32_mid_result >> 4) &  LSB_8BITS_NUMBER));
        i32_final_result = ((i32_mid_result >> 0) &  LSB_4BITS_NUMBER) | ((i32_mid_result >> 4) &  LSB_8BITS_NUMBER);
      }
      if((ui8_phi % 2) == 0 && (ui8_radius % 2) != 0)
      {
        GEN_DEBUG("OE\n");
        i32_mid_result = i32_first_result & EO_4BYTES_NUMBER;
        GEN_DEBUG("mid 0x%08x\n",i32_mid_result);
        GEN_DEBUG("mid 1 : 0x%08x\n",((i32_mid_result >> 4) &  LSB_4BITS_NUMBER));
        GEN_DEBUG("mid 2 : 0x%08x\n",((i32_mid_result >> 8) &  LSB_8BITS_NUMBER));
        i32_final_result = ((i32_mid_result >> 4) &  LSB_4BITS_NUMBER) | ((i32_mid_result >> 8) &  LSB_8BITS_NUMBER);
      }
      if((ui8_phi % 2) != 0 && (ui8_radius % 2) == 0)
      {
        GEN_DEBUG("EO\n");
        i32_mid_result = i32_first_result & OE_4BYTES_NUMBER;
        GEN_DEBUG("mid 0x%08x\n",i32_mid_result);
        GEN_DEBUG("mid 1 : 0x%08x\n",((i32_mid_result >> 8) &  LSB_4BITS_NUMBER));
        GEN_DEBUG("mid 2 : 0x%08x\n",((i32_mid_result >> 12) &  LSB_8BITS_NUMBER));
        i32_final_result = ((i32_mid_result >> 8) &  LSB_4BITS_NUMBER) | ((i32_mid_result >> 12) &  LSB_8BITS_NUMBER);
      }
      if((ui8_phi % 2) != 0 && (ui8_radius % 2) != 0)
      {
        GEN_DEBUG("OO\n");
        i32_mid_result = i32_first_result & OO_4BYTES_NUMBER;
        GEN_DEBUG("mid 0x%08x\n",i32_mid_result);
        GEN_DEBUG("mid 1 : 0x%08x\n",((i32_mid_result >> 12) &  LSB_4BITS_NUMBER));
        GEN_DEBUG("mid 2 : 0x%08x\n",((i32_mid_result >> 16) &  LSB_8BITS_NUMBER));
        i32_final_result = ((i32_mid_result >> 12) &  LSB_4BITS_NUMBER) | ((i32_mid_result >> 16) &  LSB_8BITS_NUMBER);
      }
  }

  ret = (int32_t) i32_final_result;
  GEN_DEBUG("generated number from 0x%02x and 0x%02x is : 0x%02x\n",ui8_phi, ui8_radius, ret);
  return ret;
}

/******************************************************************************/
/** \ingroup
 *  \fn  int32_t i32_get_AES_key( int32_t key_length, int32_t key_source, uint8_t *pu8_key_tab)
 *
 *  \brief this routine generates an AES key of a lenght key_lenght and writes it to the bufer pu8_key_tab
 *  \param key_lenght the lenght of the key
 *  \param key_source this is used in a random generation call
 *  \param pu8_key_tab this is the output table for the AES key
 *
 *  \return -1 if there is an error, 0 if everything is okay
 */
/******************************************************************************/
int32_t i32_get_AES_key( int32_t key_length, int32_t key_source, uint8_t *pu8_key_tab)
{
  uint8_t *pu8_result;
  uint32_t ret = -1;
  uint32_t i = 0, i32_phi = 0, i32_radius = 0, i32var1 = 0, j= 0;

  /** we test the key length parameter */
  if(key_length <= 0 || key_length > 256)
  {
    /** if the key_lenght is not within the accepted range, we stop the execution */
    GEN_ERROR("impossible de generer une clé de taille %d\n", key_length);
    return ret;
  }

  /** we should check the buffer for writing back the resulting key */
  if(pu8_key_tab == NULL)
  {
    /** if the output buffer doesn't existe we stop the execution */
    GEN_ERROR("le buffer de sortie n'existe pas\n");
    return ret;
  }

  /** we check the validity of the key source param */
  if(key_source >= MAX_PARAM_GENERATOR - 1 || key_source <= 0)
  {
    /** if the key source param is not within the accepted range than we stop the execution */
    GEN_ERROR("le paramètre de generation de clé n'est pas dans la limite acceptable\n");
    return ret;
  }

  ret = 0;
  /** the pointer to the resulting table takes the same address as the result buffer */
  pu8_result = pu8_key_tab;

  /** we should initialize the output buffer to zero */
  memset(pu8_key_tab, 0, key_length);

  /** let's generate the key using the 1byte circul integration */
  for(i = 0; i <= key_length; i++)
  {
    /** first, we generate a 4 byte integer */
    i32var1 = i32_random_generator(key_source);

    /** then we generate the Phi value and the Radius value */
    i32_phi = i32_get_sum_of_32bits_in_8bits(i32var1);
    i32_radius = i32_get_sum_of_4bytes_in_1byte(i32var1);

    /** finaly we make the integration which is basically a calculation of a circul portion area */
    *pu8_result = i32_get_random_1byte_circul_integration((uint8_t) i32_phi, (uint8_t) i32_radius);

    /** once we're done, we increment the adresse of the resulting buffer so we would write the next
        value on an empty case */
    pu8_result++;

    /** this is a wait tempo, it let's the memory cash to be reinitialized, otherwise every byte
        generated in this loop would be the same */
    for(j = 0;j < 2*key_source; j++ );
  }

  return ret;
}
