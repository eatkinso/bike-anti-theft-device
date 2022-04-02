/**
  ******************************************************************************
  * @file    ca_ecc_mbed.h
  * @author  MCD Application Team
  * @brief   This file contains the ECC router includes and definitions of
  *          the Cryptographic API (CA) module to the MBED Cryptographic library.
  * @note    This file shall never be included directly by application but
  *          through the main header ca_hash.h
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CA_ECC_MBED_H
#define CA_ECC_MBED_H

#if !defined(CA_ECC_H)
#error "This file shall never be included directly by application but through the main header ca_ecc.h"
#endif /* CA_ECC_H */

/* Configuration defines -----------------------------------------------------*/


/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ECC ECDSA */
#if defined(CA_ROUTE_ECC_ECDSA) && ((CA_ROUTE_ECC_ECDSA & CA_ROUTE_MASK) == CA_ROUTE_MBED)
/* Includes ------------------------------------------------------------------*/


/* Defines ------------------------------------------------------------------*/
#define CA_ECDSA_REQUIRED_WORKING_BUFFER    1024UL

#define CA_ECDSA_PUBKEY_MAXSIZE  ((2UL * (CA_CRL_ECC_BIGGEST_SIZE)) + 1UL)      /*!< Maximum Size of ECDSA's Public key */
#define CA_ECDSA_PRIVKEY_MAXSIZE (CA_CRL_ECC_BIGGEST_SIZE)                      /*!< Maximum Size of ECDSA's Private key */
#define CA_ECDSA_SIGN_MAXSIZE    ((CA_CRL_ECC_BIGGEST_SIZE)*2UL)                /*!< Maximum Size of Buffer containing R and S */

/* Typedef ------------------------------------------------------------------*/

/**
  * @brief  Enumeration to specify the possible flags for an Elliptic Curve Point
  */
typedef enum CA_ECPntFlags_e
{

  CA_E_POINT_GENERAL = 0,    /*!< The point is not normalized (Coordinate Z != 1) */

  CA_E_POINT_NORMALIZED = 1, /*!< The point is normalized (Coordinate Z == 1)*/

  CA_E_POINT_INFINITY = 2,   /*!< The point is the O point */

  CA_E_POINT_MONTY = 4       /*!< The point's coordinates are expressed in Montgomery domain */
} CA_ECPntFlags_et;

/**
  * @brief   Enumeration for the coordinates of an elliptic curve point
  */
typedef enum CA_ECcoordinate_e
{
  CA_E_ECC_POINT_COORDINATE_X = 0,  /*!< Coordinate X */

  CA_E_ECC_POINT_COORDINATE_Y = 1,   /*!< Coordinate Y */

  CA_E_ECC_POINT_COORDINATE_Z = 2,   /*!< Coordinate Z */
} CA_ECcoordinate_et;

/**
  * @brief  Enumeration for the values inside the ECDSA signature
  */
typedef enum CA_ECDSAsignValues_e
{
  CA_E_ECDSA_SIGNATURE_R_VALUE = 0,  /*!<  Value R  */
  CA_E_ECDSA_SIGNATURE_S_VALUE = 1,  /*!<  Value S */
} CA_ECDSAsignValues_et;

/**
  * @brief  Object used to store an elliptic curve point.
  */
typedef struct
{

  CA_BigNum_stt *pmX ;     /*!< pmX coordinate  */

  CA_BigNum_stt *pmY ;     /*!< pmY coordinate  */

  CA_BigNum_stt *pmZ ;     /*!< pmZ coordinate, used in projective representations  */

  CA_ECPntFlags_et mFlag;  /*!< Point Flag, allowed values are: \n
                           * - flag=CRL_EPOINT_GENERAL for a point which may have pmZ different from 1
                           * - flag=CRL_EPOINT_NORMALIZED for a point which has pmZ equal to 1
                           * - flag=CRL_EPOINT_INFINITY to denote the infinity point
                          */
} CA_ECpoint_stt;

/**
  * @brief   Object used to store an ECC private key
  */
typedef struct
{
  CA_BigNum_stt *pmD;   /*!<  BigNum Representing the Private Key */
} CA_ECCprivKey_stt;

/**
  * @brief   Object used to store an ECDSA signature
  */
typedef struct
{
  /** R */
  CA_BigNum_stt *pmR ;  /*!< pointer to parameter R*/
  /** S */
  CA_BigNum_stt *pmS ; /*!< pointer to parameter S*/
} CA_ECDSAsignature_stt;

/**
  * @brief  Structure that keeps the Elliptic Curve Parameter
  */
typedef struct
{
  const uint8_t *pmA;  /*!< pointer to parameter "a" */
  int32_t mAsize;      /*!< size of parameter "a" */
  const uint8_t *pmB;  /*!< pointer to parameter "b" */
  int32_t mBsize;      /*!< size of parameter "b" */
  const uint8_t *pmP;  /*!<pointer to parameter "p" */
  int32_t mPsize;      /*!<size of parameter "p" */
  const uint8_t *pmN;  /*!< pointer to parameter "n" */
  int32_t mNsize;      /*!< size of parameter "n" */
  const uint8_t *pmGx; /*!< pointer to x coordinate of generator point */
  int32_t mGxsize;     /*!< size of x coordinate of generator point */
  const uint8_t *pmGy; /*!< pointer to y coordinate of generator point */
  int32_t mGysize;     /*!< size of y coordinate of generator point */
  /*intEC_stt *pmInternalEC;*/  /*!< Pointer to internal structure for handling the parameters - not in use for Mbed router */
  /* Additional information to maintain context to communicate with Mbed */
  uint8_t tmp_privKey[CA_ECDSA_PRIVKEY_MAXSIZE];
  uint8_t tmp_pubKey[CA_ECDSA_PUBKEY_MAXSIZE];
  uint8_t tmp_Sign[CA_ECDSA_SIGN_MAXSIZE];
} CA_EC_stt;

#if (CA_ROUTE_ECC_ECDSA & CA_ROUTE_ECC_CFG_VERIFY_ENABLE)
/**
  * @brief  Structure used in ECDSA signature verification function
  */
typedef struct
{

  CA_ECpoint_stt *pmPubKey;  /*!<  Pointer to the ECC Public Key used in the verification */

  CA_EC_stt      *pmEC;      /*!<  Pointer to Elliptic Curve parameters */
} CA_ECDSAverifyCtx_stt;
#endif /* CA_ROUTE_ECC_ECDSA & CA_ROUTE_ECC_CFG_VERIFY_ENABLE */

/* Exported functions -------------------------------------------------------*/
int32_t CA_ECCinitEC(CA_EC_stt *P_pECctx, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCfreeEC(CA_EC_stt *P_pECctx, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCinitPoint(CA_ECpoint_stt **P_ppECPnt, const CA_EC_stt *P_pECctx, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCfreePoint(CA_ECpoint_stt **P_pECPnt, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCsetPointCoordinate(CA_ECpoint_stt *P_pECPnt,
                                 CA_ECcoordinate_et P_Coordinate,
                                 const uint8_t *P_pCoordinateValue,
                                 int32_t P_coordinateSize);
int32_t CA_ECCgetPointCoordinate(const CA_ECpoint_stt *P_pECPnt,
                                 CA_ECcoordinate_et P_Coordinate,
                                 uint8_t *P_pCoordinateValue,
                                 int32_t *P_pCoordinateSize);
int32_t CA_ECCinitPrivKey(CA_ECCprivKey_stt **P_ppECCprivKey, CA_EC_stt *P_pECctx, membuf_stt *P_pMemBuf);
int32_t CA_ECCfreePrivKey(CA_ECCprivKey_stt **P_pECCprivKey, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCsetPrivKeyValue(CA_ECCprivKey_stt *P_pECCprivKey,
                              const uint8_t *P_pPrivateKey,
                              int32_t P_privateKeySize);
int32_t CA_ECCgetPrivKeyValue(const CA_ECCprivKey_stt *P_pECCprivKey,
                              uint8_t *P_pPrivateKey,
                              int32_t *P_pPrivateKeySize);
int32_t CA_ECCscalarMul(const CA_ECpoint_stt *P_pECbasePnt,
                        const CA_ECCprivKey_stt *P_pECCprivKey,
                        CA_ECpoint_stt *P_pECresultPnt,
                        const CA_EC_stt *P_pECctx,
                        CA_membuf_stt *P_pMemBuf);
int32_t CA_ECDSAinitSign(CA_ECDSAsignature_stt **P_ppSignature, const CA_EC_stt *P_pECctx, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECDSAfreeSign(CA_ECDSAsignature_stt **P_pSignature, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECDSAsetSignature(CA_ECDSAsignature_stt *P_pSignature,
                             CA_ECDSAsignValues_et P_RorS,
                             const uint8_t *P_pValue,
                             int32_t P_valueSize);
#if (CA_ROUTE_ECC_ECDSA & CA_ROUTE_ECC_CFG_VERIFY_ENABLE)
int32_t CA_ECDSAverify(const uint8_t      *P_pDigest,
                       int32_t             P_digestSize,
                       const CA_ECDSAsignature_stt   *P_pSignature,
                       const CA_ECDSAverifyCtx_stt *P_pVerifyCtx,
                       CA_membuf_stt *P_pMemBuf);
#endif /* CA_ROUTE_ECC_ECDSA & CA_ROUTE_ECC_CFG_VERIFY_ENABLE */
int32_t CA_ECCvalidatePubKey(const CA_ECpoint_stt *pECCpubKey, const CA_EC_stt *P_pECctx, CA_membuf_stt *P_pMemBuf);
int32_t CA_ECCkeyGen(CA_ECCprivKey_stt *P_pPrivKey,
                     CA_ECpoint_stt    *P_pPubKey,
                     CA_RNGstate_stt   *P_pRandomState,
                     const CA_EC_stt   *P_pECctx,
                     CA_membuf_stt *P_pMemBuf);
#endif /* (CA_ROUTE_ECC_ECDSA & CA_ROUTE_MASK) == CA_ROUTE_MBED */
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ECC ECDSA */


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* CA_ECC_MBED_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

