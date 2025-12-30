**
  ******************************************************************************

  ******************************************************************************
  *
  *
  
  *
  ******************************************************************************
  *
/* Define to prevent recursive inclusion -------------------------------------*/
/* Xác d?nh d? ngan ch?n bao g?m d? quy -------------------------------------*/
#ifndef __STM32F1xx_HAL_I2C_H
#define __STM32F1xx_HAL_I2C_H
#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
/*Bao g?m------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"
/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */
/** @addtogroup I2C
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Các lo?i dã xu?t ------------------------------------------------------------*/
/** @defgroup I2C_Exported_Types I2C Exported Types
/** @Defgroup I2C_Exported_Types I2C Các lo?i xu?t kh?u
  * @{
  */
/** @defgroup I2C_Configuration_Structure_definition I2C Configuration Structure definition
/** @Defgroup I2C_Configuration_Structure_Definition I2C C?u trúc c?u hình Ð?nh nghia
  * @brief  I2C Configuration Structure definition
* @brief I2C C?u trúc c?u trúc
  * @{
  *
{
  uint32_t ClockSpeed;       /*!< Specifies the clock frequency.
<Sd1> uint32_t   clockspeed  ;  /*! <Ch? d?nh t?n s? d?ng h?.
                                  This parameter must be set to a value lower than 400kHz */
Tham s? này ph?i du?c d?t thành giá tr? th?p hon 400kHz */
  uint32_t DutyCycle;        /*!< Specifies the I2C fast mode duty cycle.
 uint32_t   nhi?m v?  ;  /*!
                                  This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */
Tham s? này có th? là giá tr? c?a @ref i2c_duty_cycle_in_fast_mode */
  uint32_t OwnAddress1;      /*!< Specifies the first device own address.
<Sd1> uint32_t   ownAddress1  ;  /*!
                                  This parameter can be a 7-bit or 10-bit address. */
Tham s? này có th? là d?a ch? 7 bit ho?c 10 bit. */
  uint32_t AddressingMode;   /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
<Sd1> uint32_t   addressingMode  ;  /*!
                                  This parameter can be a value of @ref I2C_addressing_mode */
Tham s? này có th? là giá tr? c?a @ref i2c_addressing_mode */
  uint32_t DualAddressMode;  /*!< Specifies if dual addressing mode is selected.
<Sd1> uint32_t   dualaddressmode  ;  /*!
                                  This parameter can be a value of @ref I2C_dual_addressing_mode */
Tham s? này có th? là giá tr? c?a @ref i2c_dual_addressing_mode */
  uint32_t OwnAddress2;      /*!< Specifies the second device own address if dual addressing mode is selected
 uint32_t   ownAddress2  ;  /*!
                                  This parameter can be a 7-bit address. */
Tham s? này có th? là m?t d?a ch? 7 bit. */
  uint32_t GeneralCallMode;  /*!< Specifies if general call mode is selected.
<Sd1> uint32_t   GeneralCallMode  ;  /*!
                                  This parameter can be a value of @ref I2C_general_call_addressing_mode */
Tham s? này có th? là giá tr? c?a @ref i2c_general_call_addressing_mode */
  uint32_t NoStretchMode;    /*!< Specifies if nostretch mode is selected.
<Sd1> uint32_t   nostretchmode  ;  /*!
                                  This parameter can be a value of @ref I2C_nostretch_mode */
Tham s? này có th? là giá tr? c?a @ref i2c_nostretch_mode *//
} I2C_InitTypeDef;
<Sd1>}   i2c_inittypedef  ; 
/**
  * @}
  */
/** @defgroup HAL_state_structure_definition HAL state structure definition
/*:
  * @brief  HAL State structure definition
* @brief Hal d?nh nghia c?u trúc tr?ng thái
  * @note  HAL I2C State value coding follow below described bitmap :
*
  *          b7-b6  Error information
* Thông tin l?i B7-B6
  *             00 : No Error
* 00: Không có l?i
  *             01 : Abort (Abort user request on going)
* 01: h?y b? (h?y b? yêu c?u c?a ngu?i dùng khi di)
  *             10 : Timeout
* 10: Th?i gian ch?
  *             11 : Error
* 11: L?i
  *          b5     Peripheral initialization status
* B5 tr?ng thái kh?i t?o ngo?i vi
  *             0  : Reset (Peripheral not initialized)
* 0: Ð?t l?i (ngo?i vi không du?c kh?i t?o)
  *             1  : Init done (Peripheral initialized and ready to use. HAL I2C Init function called)
* 1.
  *          b4     (not used)
* B4 (không du?c s? d?ng)
  *             x  : Should be set to 0
* x: nên du?c d?t thành 0
  *          b3* B3
  *             0  : Ready or Busy (No Listen mode ongoing)
* 0: S?n sàng ho?c b?n (không có ch? d? nghe)
  *             1  : Listen (Peripheral in Address Listen Mode)
* 1: Nghe (Ch? d? nghe ngo?i vi ? ch? d? nghe d?a ch?)
  *          b2     Intrinsic process state
* Tr?ng thái quy trình n?i t?i B2
  *             0  : Ready
* 0: S?n sàng
  *             1  : Busy (Peripheral busy with some configuration or internal operations)
* 1: b?n (b?n r?n ngo?i vi v?i m?t s? c?u hình ho?c ho?t d?ng n?i b?)
  *          b1     Rx state
* B1 RX State
  *             0  : Ready (no Rx operation ongoing)
* 0: S?n sàng (không có ho?t d?ng RX dang di?n ra)
  *             1  : Busy (Rx operation ongoing)
* 1: b?n (ho?t d?ng RX dang di?n ra)
  *          b0     Tx state
* B0 TX State
  *             0  : Ready (no Tx operation ongoing)
* 0: S?n sàng (không có ho?t d?ng TX dang di?n ra)
  *             1  : Busy (Tx operation ongoing)
* 1: b?n (ho?t d?ng TX dang di?n ra)
  * @{
  */
typedef enum<Sd1> typedef   enum 
{
  HAL_I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */
<SD1> HAL_I2C_STATE_RESET   =   0x00u  
  HAL_I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
<SD1> HAL_I2C_STATE_READY  
  HAL_I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
<SD1> HAL_I2C_STATE_BUSY  
  HAL_I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
<Sd1> HAL_I2C_STATE_BUSY_TX   =   0x21u  
  HAL_I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
<SD1> HAL_I2C_STATE_BUSY_RX   =   0x22u  
  HAL_I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
<SD1> HAL_I2C_STATE_LISTEN  
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
<SD1> HAL_I2C_STATE_BUSY_TX_LISTEN  
                                                 process is ongoing                         */
quá trình dang di?n ra */
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
<SD1> HAL_I2C_STATE_BUSY_RX_LISTEN  
                                                 process is ongoing                         */
quá trình dang di?n ra */
  HAL_I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
<Sd1> HAL_I2C_STATE_ABORT  
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
 HAL_I2C_STATE_TIMEOUT  
  HAL_I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */
 HAL_I2C_STATE_ERROR  
} HAL_I2C_StateTypeDef;
<Sd1>}   HAL_I2C_STATETYPEDEF  ; 
/**
  * @}
  */
/** @defgroup HAL_mode_structure_definition HAL mode structure definition
/** @Defgroup HAL_Mode_Structure_Definition Ð?nh nghia c?u trúc ch? d? HAL
  * @brief  HAL Mode structure definition
* Ð?nh nghia c?u trúc ch? d? HAL c?a @Brief
  * @note  HAL I2C Mode value coding follow below described bitmap :\n
* @Note Hal i2c Mode Mode Mã hóa theo dõi bên du?i Bitmap du?c mô t?: \ N
  *          b7     (not used)\n
* B7 (không du?c s? d?ng) \ n
  *             x  : Should be set to 0\n
* x: nên du?c d?t thành 0 \ n
  *          b6\n* B6 \ n
  *             0  : None\n
* 0: Không \ n
  *             1  : Memory (HAL I2C communication is in Memory Mode)\n
* 1: B? nh? (giao ti?p HAL I2C ? ch? d? b? nh?) \ n
  *          b5\n* B5 \ n
  *             0  : None\n
* 0: Không \ n
  *             1  : Slave (HAL I2C communication is in Slave Mode)\n
* 1: nô l? (giao ti?p HAL I2C ? ch? d? nô l?) \ n
  *          b4\n* B4 \ n
  *             0  : None\n
* 0: Không \ n
  *             1  : Master (HAL I2C communication is in Master Mode)\n
* 1: Master (giao ti?p HAL I2C ? ch? d? ch?) \ n
  *          b3-b2-b1-b0  (not used)\n
* B3-B2-B1-B0 (không du?c s? d?ng) \ n
  *             xxxx : Should be set to 0000
* xxxx: nên du?c d?t thành 0000
  * @{
  */
typedef enum<Sd1> typedef   enum 
{
  HAL_I2C_MODE_NONE               = 0x00U,   /*!< No I2C communication on going             */
<SD1> HAL_I2C_MODE_NONE  
  HAL_I2C_MODE_MASTER             = 0x10U,   /*!< I2C communication is in Master Mode       */
<SD1> HAL_I2C_MODE_MASTER  
  HAL_I2C_MODE_SLAVE              = 0x20U,   /*!< I2C communication is in Slave Mode        */
<SD1> HAL_I2C_MODE_SLAVE   =   0x20u  
  HAL_I2C_MODE_MEM                = 0x40U    /*!< I2C communication is in Memory Mode       */
<Sd1> HAL_I2C_MODE_MEM  
} HAL_I2C_ModeTypeDef;
<Sd1>}   hal_i2c_modetypedef  ; 
/**
  * @}
  */
/** @defgroup I2C_Error_Code_definition I2C Error Code definition
/** @Defgroup I2C_ERROR_CODE_DEFINITION I2C Ð?nh nghia mã l?i
  * @brief  I2C Error Code definition
* @brief I2C Ð?nh nghia mã l?i
  * @{
  */
#define HAL_I2C_ERROR_NONE              0x00000000U    /*!< No error              */
<Sd1> #define   hal_i2c_error_none   0x00000000u  / *!
#define HAL_I2C_ERROR_BERR              0x00000001U    /*!< BERR error            */
<Sd1> #define   hal_i2c_error_berr   0x00000001u  / *!
#define HAL_I2C_ERROR_ARLO              0x00000002U    /*!< ARLO error            */
 #define   HAL_I2C_ERROR_ARLO </SD2> <SD3> 0x00000002U  / *!
#define HAL_I2C_ERROR_AF                0x00000004U    /*!< AF error              */
<Sd1> #Define   hal_i2c_error_af   0x00000004u  / *! <L?i AF */
#define HAL_I2C_ERROR_OVR               0x00000008U    /*!< OVR error             */
<Sd1> #define   hal_i2c_error_ovr   0x00000008u  / *!
#define HAL_I2C_ERROR_DMA               0x00000010U    /*!< DMA transfer error    */
<Sd1> #define   hal_i2c_error_dma   0x00000010u  / *!
#define HAL_I2C_ERROR_TIMEOUT           0x00000020U    /*!< Timeout Error         */
<Sd1> #Define   HAL_I2C_ERROR_TIMEOUT   0x00000020U  / *!
#define HAL_I2C_ERROR_SIZE              0x00000040U    /*!< Size Management error */
<Sd1> #define   hal_i2c_error_size   0x00000040U  / *! <L?i qu?n lý kích thu?c */
#define HAL_I2C_ERROR_DMA_PARAM         0x00000080U    /*!< DMA Parameter Error   */
<Sd1> #define   hal_i2c_error_dma_param   0x00000080U  / *! <L?i tham s? DMA */
#define HAL_I2C_WRONG_START             0x00000200U    /*!< Wrong start Error     */
<Sd1> #define   HAL_I2C_WRONG_START   0x00000200U  / *!
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
#define HAL_I2C_ERROR_INVALID_CALLBACK  0x00000100U    /*!< Invalid Callback error */
<Sd1> #define   HAL_I2C_ERROR_INVALID_CALLBACK </SD2> <SD3> 0x00000100U  / *!
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
<Sd1> #endif  / * use_hal_i2c_register_callbacks */
/**
  * @}
  */
/** @defgroup I2C_handle_Structure_definition I2C handle Structure definition
/** @Defgroup I2C_Handle_Structure_Definition I2C Tay c?m Ð?nh nghia
  * @brief  I2C handle Structure definition
* @Brief I2C Tay c?m d?nh nghia c?u trúc
  * @{
  */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
typedef struct __I2C_HandleTypeDef
<Sd1> typedef   struct   __i2c_handletypedef 
#else#khác
typedef struct<Sd1> typedef   struct 
#endif  /* USE_HAL_I2C_REGISTER_CALLBACKS */
<Sd1> #endif  / * use_hal_i2c_register_callbacks */
{
  I2C_TypeDef                *Instance;      /*!< I2C registers base address               */
<Sd1>
  I2C_InitTypeDef            Init;           /*!< I2C communication parameters             */
 i2c_inittypedef   init  ;  / *!
  uint8_t                    *pBuffPtr;      /*!< Pointer to I2C transfer buffer           */
 uint8_t  *  pbuffptr  ;
  uint16_t                   XferSize;       /*!< I2C transfer size                        */
<Sd1> uint16_t   xfersize  ;  / *!
  __IO uint16_t              XferCount;      /*!< I2C transfer counter                     */
<Sd1> __io   uint16_t   Xfercount  ;  / *!
  __IO uint32_t              XferOptions;    /*!< I2C transfer options                     */
 __io   uint32_t   Xferoptions  ;
  __IO uint32_t              PreviousState;  /*!< I2C communication Previous state and mode
 __io   uint32_t   tru?c dó  ;  /*!
                                                  context for internal usage               */
b?i c?nh s? d?ng n?i b? */
  DMA_HandleTypeDef          *hdmatx;        /*!< I2C Tx DMA handle parameters             */
<Sd1> dma_handletypedef  *  hdmatx  ;
  DMA_HandleTypeDef          *hdmarx;        /*!< I2C Rx DMA handle parameters             */
<Sd1> dma_handletypedef  *  hdmarx  ;
  HAL_LockTypeDef            Lock;           /*!< I2C locking object                       */
<Sd1> Hal_locktypedef   khóa  ;  / *!
  __IO HAL_I2C_StateTypeDef  State;          /*!< I2C communication state                  */
<Sd1> __io HAL_I2C_STATETYPEDEF   state  ;  / *!
  __IO HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode                   */
<Sd1> __io HAL_I2C_MODETYPEDEF   ch? d?  ;  / *!
  __IO uint32_t              ErrorCode;      /*!< I2C Error code                           */
 __io   uint32_t   ErrorCode  ;  / *!
  __IO uint32_t              Devaddress;     /*!< I2C Target device address                */
<Sd1> __io   uint32_t   devaddress  ;
  __IO uint32_t              Memaddress;     /*!< I2C Target memory address                */
<Sd1> __io   uint32_t   memaddress  ;
  __IO uint32_t              MemaddSize;     /*!< I2C Target memory address  size          */
 __io   uint32_t   memaddsize  ;  / *! <
  __IO uint32_t              EventCount;     /*!< I2C Event counter                        */
<Sd1> __io   uint32_t   eventcount  ;  / *!
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
  void (* MasterTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);           /*!< I2C Master Tx Transfer completed callback */
<Sd1> VOID    *  hi2c  );
  void (* MasterRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);           /*!< I2C Master Rx Transfer completed callback */
<Sd1> void   (*  masterrxcpltcallback  ) (  struct    *  hi2c  );
  void (* SlaveTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);            /*!< I2C Slave Tx Transfer completed callback  */
<Sd1> VOID    *  hi2c  );
  void (* SlaveRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);            /*!< I2C Slave Rx Transfer completed callback  */
<Sd1> void   (*  slaverxcpltcallback  ) (  struct   *  hi2c  );
  void (* ListenCpltCallback)(struct __I2C_HandleTypeDef *hi2c);             /*!< I2C Listen Complete callback              */
<Sd1> void   (*  listencpltcallback  ) (  struct    *  hi2c  );
  void (* MemTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);              /*!< I2C Memory Tx Transfer completed callback */
 void   (*  memtxcpltcallback  ) (  struct    *  hi2c  );
  void (* MemRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);              /*!< I2C Memory Rx Transfer completed callback */
<Sd1> VOID    *  hi2c  );  /*!
  void (* ErrorCallback)(struct __I2C_HandleTypeDef *hi2c);                  /*!< I2C Error callback                        */
 void   (*  ErrorCallback  ) (  struct   __I2C_handletypedef  *  hi2c  );
  void (* AbortCpltCallback)(struct __I2C_HandleTypeDef *hi2c);              /*!< I2C Abort callback                        */
<Sd1> VOID    *  hi2c  );
  void (* AddrCallback)(struct __I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);  /*!< I2C Slave Address Match callback */
 void   (*  addrcallback  ) (  struct   __I2c_handletedef  *  hi2c  ,  <SD10> uint8_t   SD11> <Sd12>,   uint16_t   addrmatchcode  ); I2C d?a ch? nô l? kh?p v?i cu?c g?i l?i */
  void (* MspInitCallback)(struct __I2C_HandleTypeDef *hi2c);                /*!< I2C Msp Init callback                     */
<Sd1> VOID    *  hi2c  );
  void (* MspDeInitCallback)(struct __I2C_HandleTypeDef *hi2c);              /*!< I2C Msp DeInit callback                   */
<Sd1> void   (*  mspdeinitcallback  ) (  struct    *  hi2c  );
#endif  /* USE_HAL_I2C_REGISTER_CALLBACKS */
<Sd1> #endif  / * use_hal_i2c_register_callbacks */
} I2C_HandleTypeDef;
<Sd1>}   i2c_handletypedef  ; 
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
/**
  * @brief  HAL I2C Callback ID enumeration definition
* @Brief Hal I2C ID g?i l?i d?nh nghia ID
  */
typedef enum<Sd1> typedef   enum 
{
  HAL_I2C_MASTER_TX_COMPLETE_CB_ID      = 0x00U,    /*!< I2C Master Tx Transfer completed callback ID  */
<Sd1> HAL_I2C_MASTER_TX_COMPLETE_CB_ID  
  HAL_I2C_MASTER_RX_COMPLETE_CB_ID      = 0x01U,    /*!< I2C Master Rx Transfer completed callback ID  */
<Sd1> HAL_I2C_MASTER_RX_COMPLETE_CB_ID  
  HAL_I2C_SLAVE_TX_COMPLETE_CB_ID       = 0x02U,    /*!< I2C Slave Tx Transfer completed callback ID   */
<SD1> HAL_I2C_SLAVE_TX_COMPLETE_CB_ID  
  HAL_I2C_SLAVE_RX_COMPLETE_CB_ID       = 0x03U,    /*!< I2C Slave Rx Transfer completed callback ID   */
<SD1> HAL_I2C_SLAVE_RX_COMPLETE_CB_ID  
  HAL_I2C_LISTEN_COMPLETE_CB_ID         = 0x04U,    /*!< I2C Listen Complete callback ID               */
<SD1> HAL_I2C_LISTEN_COMPLETE_CB_ID  
  HAL_I2C_MEM_TX_COMPLETE_CB_ID         = 0x05U,    /*!< I2C Memory Tx Transfer callback ID            */
<SD1> HAL_I2C_MEM_TX_COMPLETE_CB_ID  
  HAL_I2C_MEM_RX_COMPLETE_CB_ID         = 0x06U,    /*!< I2C Memory Rx Transfer completed callback ID  */
<SD1> HAL_I2C_MEM_RX_COMPLETE_CB_ID  
  HAL_I2C_ERROR_CB_ID                   = 0x07U,    /*!< I2C Error callback ID                         */
<SD1> HAL_I2C_ERROR_CB_ID  
  HAL_I2C_ABORT_CB_ID                   = 0x08U,    /*!< I2C Abort callback ID                         */
<SD1> HAL_I2C_ABORT_CB_ID   =   0x08u  
  HAL_I2C_MSPINIT_CB_ID                 = 0x09U,    /*!< I2C Msp Init callback ID                      */
<Sd1> HAL_I2C_MSPINIT_CB_ID   =  
  HAL_I2C_MSPDEINIT_CB_ID               = 0x0AU     /*!< I2C Msp DeInit callback ID                    */
<SD1> HAL_I2C_MSPDEINIT_CB_ID </SD1> <SD2>
} HAL_I2C_CallbackIDTypeDef;
<Sd1>}   hal_i2c_callbackidtypedef  ; 
/**
  * @brief  HAL I2C Callback pointer definition
* @Brief Hal I2C Ð?nh nghia con tr? g?i l?i
  */
typedef  void (*pI2C_CallbackTypeDef)(I2C_HandleTypeDef *hi2c); /*!< pointer to an I2C callback function */
<Sd1> typedef   void   (*  pi2c_callbacktypedef  )  *  hi2c  );
typedef  void (*pI2C_AddrCallbackTypeDef)(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode); /*!< pointer to an I2C Address Match callback function */
<Sd1> typedef   void   (*  pi2c_addrrcallbacktypedef  )  *  hi2c  ,  <SD10> uint8_t   SD11> <Sd12>,   uint16_t   addrmatchcode  ); Con tr? t?i ch?c nang g?i l?i kh?p d?a ch? i2c */
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
<Sd1> #endif  / * use_hal_i2c_register_callbacks */
/**
  * @}
  */
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/* H?ng s? xu?t kh?u ------------------------------------------------------------*//
/** @defgroup I2C_Exported_Constants I2C Exported Constants
/** @Defgroup I2C_Exported_Constants i2C H?ng s? xu?t kh?u
  * @{
  */
/** @defgroup I2C_duty_cycle_in_fast_mode I2C duty cycle in fast mode
/** @defgroup i2c_duty_cycle_in_fast_mode I2C Chu k? nhi?m v? ? ch? d? nhanh
  * @{
  */
#define I2C_DUTYCYCLE_2                 0x00000000U
<Sd1> #Define   i2c_dutycycle_2   0x00000000u 
#define I2C_DUTYCYCLE_16_9              I2C_CCR_DUTY
<Sd1> #Define   i2c_dutycycle_16_9 i2c_ccr_duty 
/**
  * @}
  */
/** @defgroup I2C_addressing_mode I2C addressing mode
/** @defgroup i2c_addressing_mode i2c Ch? d? d?a ch?
  * @{
  */
#define I2C_ADDRESSINGMODE_7BIT         0x00004000U
<Sd1> #Define   i2c_addressingmode_7bit   0x00004000u 
#define I2C_ADDRESSINGMODE_10BIT        (I2C_OAR1_ADDMODE | 0x00004000U)
<Sd1> #define   i2c_addressingmode_10bit  
/**
  * @}
  */
/** @defgroup I2C_dual_addressing_mode  I2C dual addressing mode
/** @defgroup i2c_dual_addressing_mode i2c Ch? d? d?a ch? kép
  * @{
  */
#define I2C_DUALADDRESS_DISABLE        0x00000000U
<Sd1> #define   i2c_dualaddress_disable   0x00000000u 
#define I2C_DUALADDRESS_ENABLE         I2C_OAR2_ENDUAL
<Sd1> #Define   i2c_dualaddress_enable i2c_oar2_endual 
/**
  * @}
  */
/** @defgroup I2C_general_call_addressing_mode I2C general call addressing mode
/** @Defgroup I2C_General_Call_Addressing_Mode I2C Ch? d? d?a ch? cu?c g?i chung
  * @{
  */
#define I2C_GENERALCALL_DISABLE        0x00000000U
<Sd1> #define   i2c_generalcall_disable   0x00000000u 
#define I2C_GENERALCALL_ENABLE         I2C_CR1_ENGC
<Sd1> #define   i2c_generalcall_enable i2c_cr1_engc 
/**
  * @}
  */
/** @defgroup I2C_nostretch_mode I2C nostretch mode
/** @defgroup i2c_nostretch_mode i2c ch? d? Nostretch
  * @{
  */
#define I2C_NOSTRETCH_DISABLE          0x00000000U
<Sd1> #define   i2c_nostretch_disable   0x00000000u 
#define I2C_NOSTRETCH_ENABLE           I2C_CR1_NOSTRETCH
<Sd1> #Define   i2c_nostretch_enable i2c_cr1_nostretch 
/**
  * @}
  */
/** @defgroup I2C_Memory_Address_Size I2C Memory Address Size
/** @Defgroup I2C_Memory_Address_Size I2C Kích thu?c d?a ch? b? nh?
  * @{
  */
#define I2C_MEMADD_SIZE_8BIT            0x00000001U
<Sd1> #define   i2c_memadd_size_8bit   0x00000001u 
#define I2C_MEMADD_SIZE_16BIT           0x00000010U
<Sd1> #define   i2c_memadd_size_16bit   0x00000010u 
/**
  * @}
  */
/** @defgroup I2C_XferDirection_definition I2C XferDirection definition
/** @Defgroup I2C_XFerDirection_Definition I2C XferDirection Ð?nh nghia
  * @{
  */
#define I2C_DIRECTION_RECEIVE           0x00000000U
<Sd1> #define   i2c_direction_receive   0x00000000u 
#define I2C_DIRECTION_TRANSMIT          0x00000001U
<Sd1> #define   i2c_direction_transmit   0x00000001u 
/**
  * @}
  */
/** @defgroup I2C_XferOptions_definition I2C XferOptions definition
/** @Defgroup I2C_XFerOptions_Definition I2C Xferoptions Ð?nh nghia
  * @{
  */
#define  I2C_FIRST_FRAME                0x00000001U
 #Define   i2c_first_frame   0x00000001u 
#define  I2C_FIRST_AND_NEXT_FRAME       0x00000002U
<Sd1> #Define   i2c_first_and_next_frame   0x00000002u 
#define  I2C_NEXT_FRAME                 0x00000004U
<Sd1> #define   i2c_next_frame   0x00000004u 
#define  I2C_FIRST_AND_LAST_FRAME       0x00000008U
<Sd1> #Define   i2c_first_and_last_frame   0x00000008u 
#define  I2C_LAST_FRAME_NO_STOP         0x00000010U
<Sd1> #define   i2c_last_frame_no_stop   0x00000010u 
#define  I2C_LAST_FRAME                 0x00000020U
<Sd1> #define   i2c_last_frame   0x00000020u 
/* List of XferOptions in usage of :
/* Danh sách Xferoptions trong vi?c s? d?ng:
 * 1- Restart condition in all use cases (direction change or not)
* 1- Kh?i d?ng l?i di?u ki?n trong t?t c? các tru?ng h?p s? d?ng (thay d?i hu?ng ho?c không)
 */
#define  I2C_OTHER_FRAME                (0x00AA0000U)
<Sd1> #define   i2c_other_frame   (  0x00aa0000u  ) 
#define  I2C_OTHER_AND_LAST_FRAME       (0xAA000000U)
<Sd1> #Define   i2c_other_and_last_frame  
/**
  * @}
  */
/** @defgroup I2C_Interrupt_configuration_definition I2C Interrupt configuration definition
/** @Defgroup I2C_interrupt_configuration_definition I2C Ð?nh nghia c?u hình ng?t I2C
  * @brief I2C Interrupt definition
* @brief I2C Ð?nh nghia ng?t
  *        Elements values convention: 0xXXXXXXXX
* Các ph?n t? giá tr? quy u?c: 0xxxxxxxxx
  *           - XXXXXXXX  : Interrupt control mask
* - xxxxxxxxx: M?t n? di?u khi?n ng?t
  * @{
  */
#define I2C_IT_BUF                      I2C_CR2_ITBUFEN
<Sd1> #define   i2c_it_buf i2c_cr2_itbufen 
#define I2C_IT_EVT                      I2C_CR2_ITEVTEN
<Sd1> #define   i2c_it_evt i2c_cr2_itevten 
#define I2C_IT_ERR                      I2C_CR2_ITERREN
<Sd1> #Define   i2c_it_err i2c_cr2_iterren 
/**
  * @}
  */
/** @defgroup I2C_Flag_definition I2C Flag definition
/** @defgroup I2C_FLAG_DEFINITION I2C Ð?nh nghia c?
  * @{
  */
#define I2C_FLAG_OVR                    0x00010800U
<Sd1> #Define   i2c_flag_ovr   0x00010800U 
#define I2C_FLAG_AF                     0x00010400U
<Sd1> #define   i2c_flag_af   0x00010400U 
#define I2C_FLAG_ARLO                   0x00010200U
<Sd1> #define   i2c_flag_arlo   0x00010200U 
#define I2C_FLAG_BERR                   0x00010100U
<Sd1> #define   i2c_flag_berr   0x00010100U 
#define I2C_FLAG_TXE                    0x00010080U
<Sd1> #define   i2c_flag_txe   0x00010080U 
#define I2C_FLAG_RXNE                   0x00010040U
<Sd1> #define   i2c_flag_rxne   0x00010040U 
#define I2C_FLAG_STOPF                  0x00010010U
<Sd1> #Define   i2c_flag_stopf   0x00010010u 
#define I2C_FLAG_ADD10                  0x00010008U
<Sd1> #Define   i2c_flag_add10   0x00010008u 
#define I2C_FLAG_BTF                    0x00010004U
<Sd1> #Define   i2c_flag_btf   0x00010004u 
#define I2C_FLAG_ADDR                   0x00010002U
<Sd1> #Define   i2c_flag_addr   0x00010002u 
#define I2C_FLAG_SB                     0x00010001U
<Sd1> #define   i2c_flag_sb   0x00010001u 
#define I2C_FLAG_DUALF                  0x00100080U
 #define   i2c_flag_dualf   0x00100080U 
#define I2C_FLAG_GENCALL                0x00100010U
<Sd1> #Define   i2c_flag_gencall   0x00100010u 
#define I2C_FLAG_TRA                    0x00100004U
<Sd1> #define   i2c_flag_tra   0x00100004U 
#define I2C_FLAG_BUSY                   0x00100002U
<Sd1> #define   i2c_flag_busy   0x00100002u 
#define I2C_FLAG_MSL                    0x00100001U
<Sd1> #Define   i2c_flag_msl   0x00100001u 
/**
  * @}
  */
/**
  * @}
  */
/* Exported macros -----------------------------------------------------------*/
/* Xu?t kh?u macro -------------------------------------------------------------------*/
/** @defgroup I2C_Exported_Macros I2C Exported Macros
/** @Defgroup I2C_Exported_Macros I2C dã xu?t Macro
  * @{
  */
/** @brief Reset I2C handle state.
/** @brief Ð?t l?i tr?ng thái x? lý i2c.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @retval None
* @retval không có
  */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__)                do{                                                   \
<Sd1> #define   __hal_i2c_reset_handle_state   (  __ \ 
                                                                    (__HANDLE__)->State = HAL_I2C_STATE_RESET;       \
<Sd1> (  __ x? lý __  )->   State  
                                                                    (__HANDLE__)->MspInitCallback = NULL;            \
<Sd1> (  __ x? lý __  )->   mspinitcallback  
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;          \
<Sd1> (  __ x? lý __  )->   mspdeinitcallback  
                                                                  } while(0)<Sd1>}   trong khi   (  0  ) 
#else#khác
#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_I2C_STATE_RESET)
<Sd1> #Define   __Hal_i2c_reset_handle_state   (  __ x? lý __  )  <s D6> ((  __ x? lý __  )->   State  <SD10> =   HAL_I2C_STATE_RESET  ) 
#endif
/** @brief  Enable or disable the specified I2C interrupts.
/** @brief Kích ho?t ho?c vô hi?u hóa các ng?t I2C du?c ch? d?nh.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
* @param __Interrupt__ Ch? d?nh ngu?n ng?t d? b?t ho?c vô hi?u hóa.
  *         This parameter can be one of the following values:
* Tham s? này có th? là m?t trong các giá tr? sau:
  *            @arg I2C_IT_BUF: Buffer interrupt enable
* @arg i2c_it_buf: B?t ng?t b? d?m
  *            @arg I2C_IT_EVT: Event interrupt enable
* @arg i2c_it_evt: B?t ng?t s? ki?n
  *            @arg I2C_IT_ERR: Error interrupt enable
* @Arg I2C_IT_ERR: B?t l?i ng?t l?i
  * @retval None
* @retval không có
  */
#define __HAL_I2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->CR2,(__INTERRUPT__))
<Sd1> #define   __hal_i2c_enable_it   Set_bit   ((  __ x? lý __  )->   cá th?  <Sd13>->   cr2  , (  __ ng?t __  )) </SD17>
#define __HAL_I2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))
<Sd1> #define   __hal_i2c_disable_it   (  __ x? lý __  Clear_bit   ((  __ x? lý __  )->   cá th?   -> </SD13> <SD14> CR2 </SD14> <SD15>, </SD15> <SD16> (  __ ng?t __ </sd17
/** @brief  Checks if the specified I2C interrupt source is enabled or disabled.
/** @brief ki?m tra xem ngu?n ng?t i2c du?c ch? d?nh du?c b?t ho?c t?t.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @param  __INTERRUPT__ specifies the I2C interrupt source to check.
* @param __interrupt__ Ch? d?nh ngu?n ng?t i2C d? ki?m tra.
  *          This parameter can be one of the following values:
* Tham s? này có th? là m?t trong các giá tr? sau:
  *            @arg I2C_IT_BUF: Buffer interrupt enable
* @arg i2c_it_buf: B?t ng?t b? d?m
  *            @arg I2C_IT_EVT: Event interrupt enable
* @arg i2c_it_evt: B?t ng?t s? ki?n
  *            @arg I2C_IT_ERR: Error interrupt enable
* @Arg I2C_IT_ERR: B?t l?i ng?t l?i
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
* @retval Tr?ng thái m?i c?a __Interrupt__ (dúng ho?c sai).
  */
#define __HAL_I2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR2 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)
<Sd1> #define   __hal_i2c_get_it_source   (  __ x? lý __  , </sd5 __Interrupt __  )   ((( <. =  <Sd19> (  __ ng?t __  )) Ð?t  :   Ð?t l?i  ) 
/** @brief  Checks whether the specified I2C flag is set or not.
/** @brief ki?m tra xem c? I2C du?c ch? d?nh có du?c d?t hay không.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @param  __FLAG__ specifies the flag to check.
* @param __flag__ Ch? d?nh c? d? ki?m tra.
  *         This parameter can be one of the following values:
* Tham s? này có th? là m?t trong các giá tr? sau:
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag
* @Arg I2C_FLAG_OVR: C? ghi dè/Underrun
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
* @Arg I2C_FLAG_AF: C? th?t b?i
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag
* @arg I2C_FLAG_ARLO: Tr?ng tài b? m?t c?
  *            @arg I2C_FLAG_BERR: Bus error flag
* @arg i2c_flag_berr: c? l?i xe buýt
  *            @arg I2C_FLAG_TXE: Data register empty flag
* @Arg I2C_FLAG_TXE: D? li?u Ðang ký c? tr?ng
  *            @arg I2C_FLAG_RXNE: Data register not empty flag
* @arg i2c_flag_rxne: Ðang ký d? li?u không ph?i c? tr?ng
  *            @arg I2C_FLAG_STOPF: Stop detection flag
* @arg I2C_FLAG_STOPF: D?ng c? phát hi?n
  *            @arg I2C_FLAG_ADD10: 10-bit header sent flag
* @arg I2C_FLAG_ADD10: C? du?c g?i tiêu d? 10 bit
  *            @arg I2C_FLAG_BTF: Byte transfer finished flag
* @arg i2c_flag_btf: Byte chuy?n thành công
  *            @arg I2C_FLAG_ADDR: Address sent flag
* @arg i2c_flag_addr: d?a ch? du?c g?i c?
  *                                Address matched flag
* Ð?a ch? c? phù h?p
  *            @arg I2C_FLAG_SB: Start bit flag
* @arg i2c_flag_sb: B?t d?u c? bit
  *            @arg I2C_FLAG_DUALF: Dual flag
* @arg I2C_FLAG_DUALF: C? kép
  *            @arg I2C_FLAG_GENCALL: General call header flag
* @arg I2C_FLAG_GENCALL: C? tiêu d? cu?c g?i chung
  *            @arg I2C_FLAG_TRA: Transmitter/Receiver flag
* @arg I2C_FLAG_TRA: C? máy phát/máy thu
  *            @arg I2C_FLAG_BUSY: Bus busy flag
* @Arg I2C_FLAG_BUSY: Bus Busy FLAG
  *            @arg I2C_FLAG_MSL: Master/Slave flag
* @arg I2C_FLAG_MSL: C? ch?/nô l?
  * @retval The new state of __FLAG__ (TRUE or FALSE).
* @retval Tr?ng thái m?i c?a __flag__ (dúng ho?c sai).
  */
#define __HAL_I2C_GET_FLAG(__HANDLE__, __FLAG__) ((((uint8_t)((__FLAG__) >> 16U)) == 0x01U) ? \
<Sd1> #define   __hal_i2c_get_flag   __Flag __  )   ((( SD13 >>> </SD13> <SD14> 16U </SD14> <SD15>)) \ 
                                                  (((((__HANDLE__)->Instance->SR1) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET) : \
<Sd1> (((((  __ x? lý __  )->   instance  ->  <SD6> D6> )   &   ((  __ c? __  )   &  I2C_FLAG_MASK </SD13> <SD14>)) </SD14> <SD15> I2C_FLAG_MASK  ))  ? Ð?t l?i  )  :   \ 
                                                  (((((__HANDLE__)->Instance->SR2) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET))
<Sd1> (((((  __ x? lý __  )->   instance  ->   sr2 </sd4 D6> )   &   ((  __ c? __  )   &  I2C_FLAG_MASK </SD13> <SD14>)) </SD14> <SD15> I2C_FLAG_MASK </SD20> <SD21>))
/** @brief  Clears the I2C pending flags which are cleared by writing 0 in a specific bit.
/** @brief xóa các c? dang ch? x? lý I2C du?c xóa b?ng cách vi?t 0 theo m?t bit c? th?.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @param  __FLAG__ specifies the flag to clear.
* @param __flag__ Ch? d?nh c? d? xóa.
  *         This parameter can be any combination of the following values:
* Tham s? này có th? là b?t k? s? k?t h?p nào c?a các giá tr? sau:
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
* @arg I2C_FLAG_OVR: C? ghi dè/Underrun (ch? d? nô l?)
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
* @Arg I2C_FLAG_AF: C? th?t b?i
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
* @Arg I2C_FLAG_ARLO: Tr?ng tài b? m?t c? (Ch? d? chính)
  *            @arg I2C_FLAG_BERR: Bus error flag
* @arg i2c_flag_berr: c? l?i xe buýt
  * @retval None
* @retval không có
  */
#define __HAL_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->SR1 = ~((__FLAG__) & I2C_FLAG_MASK))
<Sd1> #define   __hal_i2c_clear_flag   (  __ x? lý __  </sd5 __Flag __  )   ((  __ x? lý __  )->   <.
/** @brief  Clears the I2C ADDR pending flag.
/** @brief xóa c? dang ch? I2C addr.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  *         This parameter can be I2C where x: 1, 2, or 3 to select the I2C peripheral.
* Tham s? này có th? là I2C trong dó X: 1, 2 ho?c 3 d? ch?n ngo?i vi I2C.
  * @retval None
* @retval không có
  */
#define __HAL_I2C_CLEAR_ADDRFLAG(__HANDLE__)    \
<Sd1> #define   __hal_i2c_clear_addrflag   (  __ x? lý __  )
  do{                                           \
 do   {  \ 
    __IO uint32_t tmpreg = 0x00U;               \
<Sd1> __io   uint32_t   tmpreg  
    tmpreg = (__HANDLE__)->Instance->SR1;       \
<Sd1> tmpreg <. \ 
    tmpreg = (__HANDLE__)->Instance->SR2;       \
<Sd1> tmpreg <. \ 
    UNUSED(tmpreg);                             \
<Sd1> không s? d?ng   (  tmpreg  );   \ 
  } while(0)<Sd1>}   trong khi   (  0  ) 
/** @brief  Clears the I2C STOPF pending flag.
/** @brief xóa c? I2C d?ng dang ch? x? lý.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @retval None
* @retval không có
  */
#define __HAL_I2C_CLEAR_STOPFLAG(__HANDLE__)           \
<Sd1> #define   __hal_i2c_clear_stopflag   (  __ x? lý __  )
  do{                                                  \
 do   {  \ 
    __IO uint32_t tmpreg = 0x00U;                      \
<Sd1> __io   uint32_t   tmpreg  
    tmpreg = (__HANDLE__)->Instance->SR1;              \
<Sd1> tmpreg <. \ 
    SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE);  \
<Sd1> set_bit   I2C_CR1_PE  );   \ 
    UNUSED(tmpreg);                                    \
<Sd1> không s? d?ng   (  tmpreg  );   \ 
  } while(0)<Sd1>}   trong khi   (  0  ) 
/** @brief  Enable the specified I2C peripheral.
/** @brief Kích ho?t ngo?i vi I2C du?c ch? d?nh.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @retval None
* @retval không có
  */
#define __HAL_I2C_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)
<Sd1> #Define   __hal_i2c_enable   Set_bit   I2C_CR1_PE </SD14> <SD15>) </SD15>
/** @brief  Disable the specified I2C peripheral.
/** @brief vô hi?u hóa ngo?i vi I2C du?c ch? d?nh.
  * @param  __HANDLE__ specifies the I2C Handle.
* @param __handle__ Ch? d?nh tay c?m I2C.
  * @retval None
* @retval không có
  */
#define __HAL_I2C_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)
<Sd1> #define   __hal_i2c_disable   Clear_bit   I2C_CR1_PE </SD14> <SD15>) </SD15>
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/* Các ch?c nang dã xu?t ----------------------------------------------------------------*//
/** @addtogroup I2C_Exported_Functions
/** @addtogroup I2C_Exported_Funces
  * @{
  */
/** @addtogroup I2C_Exported_Functions_Group1 Initialization and de-initialization functions
/** @addtogroup i2c_exported_function_group1 Ch?c nang kh?i t?o và kh? ?nh hu?ng
  * @{
  */
/* Initialization and de-initialization functions******************************/
/*Các ch?c nang kh?i t?o và kh? t? do ******/TÌM HI?U/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_INIT   (  i2c_handletypedef  *</sd4
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_DEINIT  
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_mspinit   (  i2c_handletypedef  
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);
<Sd1> void   hal_i2c_mspdeinit  
/* Callbacks Register/UnRegister functions  ***********************************/
/*Các ch?c nang dang ký g?i l?i/các ch?c nang Undgister ******/TÌM HI?U/
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#IF (use_hal_i2c_register_callbacks == 1)
HAL_StatusTypeDef HAL_I2C_RegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID, pI2C_CallbackTypeDef pCallback);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_REGISTERCALLBACK   (  i2c_handletypedef  <SD4> HAL_I2C_CALLBACKIDTYPEDEF   callbackid  ,  
HAL_StatusTypeDef HAL_I2C_UnRegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_UNREGISTERCALLBACK   (  i2c_handletypedef   HAL_I2C_CALLBACKIDTYPEDEF   callbackid  ); 
HAL_StatusTypeDef HAL_I2C_RegisterAddrCallback(I2C_HandleTypeDef *hi2c, pI2C_AddrCallbackTypeDef pCallback);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_REGISTERADDRCALLBACK   (  i2c_handletypedef   pi2c_addrcallbacktypedef pcallback  ); 
HAL_StatusTypeDef HAL_I2C_UnRegisterAddrCallback(I2C_HandleTypeDef *hi2c);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_UNREGISTERADDRCALLBACK   (  i2c_handletypedef  
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
<Sd1> #endif  / * use_hal_i2c_register_callbacks */
/**
  * @}
  */
/** @addtogroup I2C_Exported_Functions_Group2 Input and Output operation functions
/** @addtogroup i2c_exported_function_group2 Ch?c nang ho?t d?ng d?u vào và d?u ra
  * @{
  */
/* IO operation functions  ****************************************************/
/*Ch?c nang ho?t d?ng IO ******/TÌM HI?U
/******* Blocking mode: Polling */
/******* Ch? d? ch?n: b? phi?u*/
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
 HAL_STATUSTYPEDEF HAL_I2C_MASTER_TRANSMIT   (  i2c_handletypedef <. 8> Devaddress  ,   uint8_t  * <sd1 2. D16>,   uint32_t   Th?i gian ch? </SD18> </SD19>); </SD19>
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_RECEIVE   (  i2c_handletypedef <. 8> Devaddress  ,   uint8_t  * <sd1 2. D16>,   uint32_t   Th?i gian ch? </SD18> </SD19>); </SD19>
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_TRANSMIT   (  i2c_handletypedef <. SD11> UINT16_T </SD11> <SD12> Kích thu?c  ,  <SD14> UINT32_T  </SD15> Th?i gian ch? </SD15> <Sd16>
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
 HAL_STATUSTYPEDEF HAL_I2C_SLAVE_RECEIVE   (  i2c_handletypedef <. SD11> UINT16_T </SD11> <SD12> Kích thu?c  ,  <SD14> UINT32_T  </SD15> Th?i gian ch? </SD15> <Sd16>
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_MEM_WRITE   (  i2c_handletypedef <. >  uint16_t   memaddress  ,   uint16_t   memaddsize < /SD14> <Sd15>,   uint8_t  *  6 trang
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
 HAL_STATUSTYPEDEF HAL_I2C_MEM_READ   (  i2c_handletypedef <. >  uint16_t   memaddress  ,   uint16_t   memaddsize < /SD14> <Sd15>,   uint8_t  *  6 trang
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_ISDEVICEREADY   (  i2c_handletypedef <. UINT32_T   th? nghi?m  ,   uint32_t   Th?i gian ch? </SD14> <SD15>)
/******* Non-Blocking mode: Interrupt */
/******* Ch? d? không ch?n: ng?t*/
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_TRANSMIT_IT   (  i2c_handletypedef <. A
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_RECEIVE_IT   (  i2c_handletypedef <. A
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_TRANSMIT_IT   (  i2c_handletypedef <. > pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
 HAL_STATUSTYPEDEF HAL_I2C_SLAVE_RECEIVE_IT   (  i2c_handletypedef <. > pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
 HAL_STATUSTYPEDEF HAL_I2C_MEM_WRITE_IT   (  i2c_handletypedef <. 8> <Sd9>,   uint16_t   memaddress  ,   uint1 6_T  <Sd14> Memaddsize  ,   uint8_t  <SD17>* <s d18> pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MEM_READ_IT   (  i2c_handletypedef <. 8> <Sd9>,   uint16_t   memaddress  ,   uint1 6_T  <Sd14> Memaddsize  ,   uint8_t  <SD17>* <s d18> pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_SEQ_TRANSMIT_IT   (  i2c_handletypedef <. > Devaddress  ,   uint8_t  *  pdata  ,   uint16_t   kích thu?c  , <.
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_SEQ_RECEIVE_IT   (  i2c_handletypedef <. > Devaddress  ,   uint8_t  *  pdata  ,   uint16_t   kích thu?c  , <.
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_SEQ_TRANSMIT_IT   (  i2c_handletypedef <. 11> UINT16_T </SD11> <SD12> Kích thu?c </SD12> <Sd13>,  <SD14> UINT32_T  
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
 HAL_STATUSTYPEDEF HAL_I2C_SLAVE_SEQ_RECEIVE_IT   (  i2c_handletypedef <. 11> UINT16_T </SD11> <SD12> Kích thu?c </SD12> <Sd13>,  <SD14> UINT32_T  
HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_ENABLELISTEN_IT   (  i2c_handletypedef  
HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_DISEBLELISTEN_IT   (  i2c_handletypedef  
HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_ABORT_IT   (  i2c_handletypedef <.
/******* Non-Blocking mode: DMA */
/******* Ch? d? không ch?n: DMA*/
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_TRANSMIT_DMA   (  i2c_handletypedef <. A
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_RECEIVE_DMA   (  i2c_handletypedef <. A
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_TRANSMIT_DMA   (  i2c_handletypedef <. > pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_RECEIVE_DMA   (  i2c_handletypedef <. > pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MEM_WRITE_DMA   (  i2c_handletypedef <. 8> <Sd9>,   uint16_t   memaddress  ,   uint1 6_T  <Sd14> Memaddsize  ,   uint8_t  <SD17>* <s d18> pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MEM_READ_DMA   (  i2c_handletypedef <. 8> <Sd9>,   uint16_t   memaddress  ,   uint1 6_T  <Sd14> Memaddsize  ,   uint8_t  <SD17>* <s d18> pdata  ,   uint16_t   kích thu?c  ); 
HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_SEQ_TRANSMIT_DMA   (  i2c_handletypedef <. > Devaddress  ,   uint8_t  *  pdata  ,   uint16_t   kích thu?c  , <.
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<Sd1> HAL_STATUSTYPEDEF HAL_I2C_MASTER_SEQ_RECEIVE_DMA   (  i2c_handletypedef <. > Devaddress  ,   uint8_t  *  pdata  ,   uint16_t   kích thu?c  , <.
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
<SD1> HAL_STATUSTYPEDEF HAL_I2C_SLAVE_SEQ_TRANSMIT_DMA   (  i2c_handletypedef <. 11> UINT16_T </SD11> <SD12> Kích thu?c </SD12> <Sd13>,  <SD14> UINT32_T  
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
 HAL_STATUSTYPEDEF HAL_I2C_SLAVE_SEQ_RECEIVE_DMA   (  i2c_handletypedef <. 11> UINT16_T </SD11> <SD12> Kích thu?c </SD12> <Sd13>,  <SD14> UINT32_T  
/**
  * @}
  */
/** @addtogroup I2C_IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
/'
 * @{
 */
/******* I2C IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
/******* I2C irqHandler và các cu?c g?i l?i du?c s? d?ng trong các ch? d? không ch?n (ng?t và dma)
void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_ev_irqhandler   ( 
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_er_irqhandler   (  i2c_handletypedef 
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_mastertxcpltcallback   (  i2c_handletedef 
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
<Sd1> void   hal_i2c_masterrxcpltcallback   (  i2c_handletedef 
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void   HAL_I2C_SLAVETXCPLTCALLBACK   (  i2c_handletedef 
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_slaverxcpltcallback   (  i2c_handletedef 
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
 void   hal_i2c_addrcallback   (  i2c_handletypedef <. Trên  ,   uint16_t   addrmatchcode  ); 
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_listencpltcallback   ( 
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
 void   HAL_I2C_MEMTXCPLTCALLBACK   (  i2c_handletedef 
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_memrxcpltcallback   (  i2c_handletedef 
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
 void   hal_i2c_errorcallback   ( 
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c);
 void   HAL_I2C_ABORTCPLTCALLBACK  
/**
  * @}
  */
/** @addtogroup I2C_Exported_Functions_Group3 Peripheral State, Mode and Error functions
/'
  * @{
  */
/* Peripheral State, Mode and Error functions  *********************************/
/*Tr?ng thái ngo?i vi, ch? d? và các hàm l?i ******/TÌM HI?U/
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
<SD1> HAL_I2C_STATETYDEF HAL_I2C_GETSTATE   (  i2c_handletypedef  
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
<SD1> HAL_I2C_MODETYPEDEF HAL_I2C_GETMODE   (  i2c_handletypedef  
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);
<Sd1> uint32_t   hal_i2c_geterror  
/**
  * @}
  */
/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Các lo?i riêng tu ---------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Các bi?n riêng tu -----------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* H?ng s? riêng -------------------------------------------------------------*/
/** @defgroup I2C_Private_Constants I2C Private Constants
/** @Defgroup I2C_Private_Constants I2C H?ng s? riêng
  * @{
  */
#define I2C_FLAG_MASK                    0x0000FFFFU
<Sd1> #define   i2c_flag_mask   0x000000ffffu 
#define I2C_MIN_PCLK_FREQ_STANDARD       2000000U     /*!< 2 MHz                     */
<Sd1> #Define   i2c_min_pclk_freq_standard   200000U  / *! <2 MHz */
#define I2C_MIN_PCLK_FREQ_FAST           4000000U     /*!< 4 MHz                     */
<Sd1> #Define   i2c_min_pclk_freq_fast   4000000U  <SD4>/ *! <4 MHz */</SD4>
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Macro riêng tu --------------------------------------------------------------------*//
/** @defgroup I2C_Private_Macros I2C Private Macros
/** @Defgroup I2C_Private_Macros I2C Macro Private Private
  * @{
  */
#define I2C_MIN_PCLK_FREQ(__PCLK__, __SPEED__)             (((__SPEED__) <= 100000U) ? ((__PCLK__) < I2C_MIN_PCLK_FREQ_STANDARD) : ((__PCLK__) < I2C_MIN_PCLK_FREQ_FAST))
<Sd1> #define   i2c_min_pclk_freq   (  __Speed ??__  )   (((  /SD12> <SD13>) </SD13> <Sd14>? I2C_MIN_PCLK_FREQ_STANDARD  )  :  <SD2 2. I2c_min_pclk_freq_fast  )) 
#define I2C_CCR_CALCULATION(__PCLK__, __SPEED__, __COEFF__)     (((((__PCLK__) - 1U)/((__SPEED__) * (__COEFF__))) + 1U) & I2C_CCR_CCR)
<Sd1> #define   i2c_ccr_calculation   __Coeff __  )   (((((  __ pclk __   ) <. 16> <Sd17>) </SD17> <Sd18>* <Sd19> )) I2c_ccr_ccr  ) 
#define I2C_FREQRANGE(__PCLK__)                            ((__PCLK__)/1000000U)
<Sd1> #Define   I2c_freqrange   (  __ pclk __  )   ((< /sd6>  __ pclk __  )/  1000000U  ) 
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__)            (((__SPEED__) <= 100000U) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))
<Sd1> #define   i2c_rise_time   (  __ freqrange __  ,   __Speed ??__  )   (((  <Sd13>) </SD13> <Sd14>? > <SD20>) </SD20> <SD21> </SD26> <SD27>) </SD27> <SD28>/</SD28> <SD29> 1000U </SD29> <SD30>) </SD30> <SD31>
#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__)            ((I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U) < 4U)? 4U:I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U))
<Sd1> #define   i2c_speed_standard   __Speed ??__  )   ((  i2c_ccr_calculation   ((</sd10 12>),   (  __ t?c d? __  ),  <SD16> 2u  <Sd17> 9> 4U  )? _PCLK __ </SD25> <SD26>),  
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) (((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 3U) : (I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 25U) | I2C_DUTYCYCLE_16_9))
<Sd1> #define   i2c_speed_fast   (  __ pclk __   __Dutycycle __  )   ((( I2c_dutycycle_2  )? </Sd15>  I2c_ccr_calculation   ((  __ pclk __  ),   ( < SD21> __ T?C Ð? __ </SD21> <SD22>),   3U  )   > <Sd27> /sd31>__SPEED__),25U)| I2c_dutycycle_16_9  )) 
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__)      (((__SPEED__) <= 100000U)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
<Sd1> #define   i2c_speed   (  __ pclk __  ,   __Dutycycle __  )   ((( ) <. 17> d20>  (  __ t?c d? __  ))) \ 
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & I2C_CCR_CCR) == 0U)? 1U : \
<Sd1> ((  i2c_speed_fast   ((  __ pclk __  ) __Speed ??__  ),   (  I2C_CCR_CCR </SD13> <SD14>) </SD14> <SD15>
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | I2C_CCR_FS))
<SD1> ((  _Speed ??__  ),   (  __ Dutycycle __  )) I2c_ccr_fs  )) 
#define I2C_7BIT_ADD_WRITE(__ADDRESS__)                    ((uint8_t)((__ADDRESS__) & (uint8_t)(~I2C_OAR1_ADD0)))
<Sd1> #Define   I2c_7bit_add_write   (  __ d?a ch? __  )   ((  S __  )   &   (  uint8_t <.
#define I2C_7BIT_ADD_READ(__ADDRESS__)                     ((uint8_t)((__ADDRESS__) | I2C_OAR1_ADD0))
<Sd1> #Define   I2c_7bit_add_read   (  __ d?a ch? __  )   (( <sd 7. I2c_oar1_add0  )) 
#define I2C_10BIT_ADDRESS(__ADDRESS__)                     ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))
<Sd1> #Define   I2c_10bit_address   (  __ d?a ch? __  )  <s D6> ((  uint8_t  ) ( <. 4.
#define I2C_10BIT_HEADER_WRITE(__ADDRESS__)                ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0x0300)) >> 7) | (uint16_t)0x00F0)))
<Sd1> #Define   I2c_10bit_header_write   (  __ d?a ch? __  )   ((  NT16_T </SD9> <SD10>) ( > <Sd16>) </SD16> <Sd17> &   (  uint16_t  ) </SD20> <Sd21> 0x0300  )) </SD22> <SD23 >>> </SD23 >  7  )   | UINT16_T </SD28> <SD29>) </SD29> <SD30> 0x00F0 </SD30> <SD31>))) </SD31>
#define I2C_10BIT_HEADER_READ(__ADDRESS__)                 ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0x0300)) >> 7) | (uint16_t)(0x00F1))))
<Sd1> #Define   I2c_10bit_header_read   (  __ d?a ch? __  )   T16_T  <SD10>) ( SD16>) </SD16> <Sd17> &   (  uint16_t  < SD20>) </SD20> <SD21> 0x0300  )) </SD22> <SD23 >>> </SD23> < SD24> 7 </SD24> <SD25>) </SD25> <Sd26> | NT16_T  ) (  0x00f1  )))) 
#define I2C_MEM_ADD_MSB(__ADDRESS__)                       ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0xFF00)) >> 8)))
<Sd1> #Define   I2c_mem_add_msb   (  __ d?a ch? __  )   ((</sd6 t  ) ((  uint16_t  ) (((  uint16_t  ) ( <Sd13> __ Ð?a ch? __ </SD13> <SD14>) </SD14> <SD15> & </SD15> <SD16> (</SD16> <SD17> UINT16_T </SD17 SD18>) </SD18> <SD19> 0xFF00 </SD19> <SD20>)) </SD20> <SD21 >>> <
#define I2C_MEM_ADD_LSB(__ADDRESS__)                       ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))
<Sd1> #Define   I2c_mem_add_lsb   (  __ d?a ch? __  )  <sd 6. /SD10> <Sd11> __ Ð?a ch? __  )   &   ( <Sd15> uint16_t  )   0x00ff  ))) </SD18>
/** @defgroup I2C_IS_RTC_Definitions I2C Private macros to check input parameters
/** @defgroup I2C_IS_RTC_DEFINITIONS I2C Macro riêng d? ki?m tra các tham s? d?u vào
  * @{
  */
#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DUTYCYCLE_2) || \
<Sd1> #Define   IS_I2C_DUTY_CYCLE   (  chu k?  )   (((  I2c_dutycycle_2  )   ||   \ 
                                  ((CYCLE) == I2C_DUTYCYCLE_16_9))
<Sd1> ((  chu k?  )   ==   i2c_dutycycle_16_9 <
#define IS_I2C_ADDRESSING_MODE(ADDRESS) (((ADDRESS) == I2C_ADDRESSINGMODE_7BIT) || \
<Sd1> #Define   Is_i2c_addressing_mode   (  d?a ch?  )   (((  I2c_addressingMode_7bit  )   ||   \ 
                                         ((ADDRESS) == I2C_ADDRESSINGMODE_10BIT))
<Sd1> ((  Ð?a ch?  )   ==  
#define IS_I2C_DUAL_ADDRESS(ADDRESS) (((ADDRESS) == I2C_DUALADDRESS_DISABLE) || \
<Sd1> #Define   Is_i2c_dual_address   (  d?a ch?  )   (((  I2c_dualaddress_disable  )   ||   \ 
                                      ((ADDRESS) == I2C_DUALADDRESS_ENABLE))
 ((  Ð?a ch?  )   ==   i2c_dualaddress_enable 
#define IS_I2C_GENERAL_CALL(CALL) (((CALL) == I2C_GENERALCALL_DISABLE) || \
<Sd1> #Define   IS_I2C_General_Call   (  g?i  )   (( I2C_GeneralCall_Disable  )   ||   \ 
                                   ((CALL) == I2C_GENERALCALL_ENABLE))
<Sd1> ((  Call  )   ==   i2c_generalcall_enable 
#define IS_I2C_NO_STRETCH(STRETCH) (((STRETCH) == I2C_NOSTRETCH_DISABLE) || \
<Sd1> #Define   IS_I2C_NO_STRETCH   (  streting  )   (((  I2c_nostretch_disable  )   ||   \ 
                                    ((STRETCH) == I2C_NOSTRETCH_ENABLE))
<Sd1> ((  r?n da  )   ==   i2c_nostretch_enable 
#define IS_I2C_MEMADD_SIZE(SIZE) (((SIZE) == I2C_MEMADD_SIZE_8BIT) || \
<Sd1> #Define   Is_i2c_memadd_size   (  kích thu?c  )   (((  I2c_memadd_size_8bit  )   ||   \ 
                                  ((SIZE) == I2C_MEMADD_SIZE_16BIT))
 ((  kích thu?c  )   ==   i2c_memadd_size_16bit </sd5
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) > 0U) && ((SPEED) <= 400000U))
<Sd1> #Define   IS_I2C_CLOCK_SPEED   (  T?c d?  ) D10> <Sd11>)  <Sd12> &&   ((  T?c d?  <Sd15>) </SD15> <Sd16> <=   400000u  )) </SD18>
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) (((ADDRESS1) & 0xFFFFFC00U) == 0U)
<Sd1> #Define   Is_i2c_own_address1   (  address1  )   d8>)   &   0xfffffc00u  )   ==   0u </sd13
#define IS_I2C_OWN_ADDRESS2(ADDRESS2) (((ADDRESS2) & 0xFFFFFF01U) == 0U)
<Sd1> #Define   Is_i2c_own_address2   (  address2  )   d8>)   &   0xffffff01u  )   ==   0u </sd13
#define IS_I2C_TRANSFER_OPTIONS_REQUEST(REQUEST)      (((REQUEST) == I2C_FIRST_FRAME)              || \
<Sd1> #Define   Is_i2c_transfer_options_request   (  yêu c?u  ) I2c_first_frame  )   ||   \ 
                                                       ((REQUEST) == I2C_FIRST_AND_NEXT_FRAME)     || \
<Sd1> ((  Yêu c?u  )   ==  
                                                       ((REQUEST) == I2C_NEXT_FRAME)               || \
<Sd1> ((  Yêu c?u  )   ==  
                                                       ((REQUEST) == I2C_FIRST_AND_LAST_FRAME)     || \
<Sd1> ((  Yêu c?u  )   ==  
                                                       ((REQUEST) == I2C_LAST_FRAME)               || \
<Sd1> ((  Yêu c?u  )   ==  
                                                       ((REQUEST) == I2C_LAST_FRAME_NO_STOP)       || \
<Sd1> ((  Yêu c?u  )   ==  
                                                       IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST))
 is_i2c_transfer_other_options_request   (  Yêu c?u  )) 
#define IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST) (((REQUEST) == I2C_OTHER_FRAME)     || \
<Sd1> #Define   Is_i2c_transfer_other_options_request   (  Yêu c?u  )   (( </sd7 I2c_other_frame  )   ||   \ 
                                                        ((REQUEST) == I2C_OTHER_AND_LAST_FRAME))
<Sd1> ((  Yêu c?u  )   ==  
#define I2C_CHECK_FLAG(__ISR__, __FLAG__)         ((((__ISR__) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET)
<Sd1> #define   i2c_check_flag   (  __ isr __  ,   __Flag __  )   ((((  __ isr __  )  <SD11 > & <. I2C_FLAG_MASK </SD16> <SD17>)) </SD17> <SD18> I2C_FLAG_MASK </SD23> <SD24>)) </SD24> <SD25>?
#define I2C_CHECK_IT_SOURCE(__CR1__, __IT__)      ((((__CR1__) & (__IT__)) == (__IT__)) ? SET : RESET)
<Sd1> #Define   i2c_check_it_source   (  __ cr1 __ __It __  )   (((  __ cr1 __  <SD10>) T __  ))   Ð?t  :   Ð?t l?i  ) 
/**
  * @}
  */
/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/* Các ch?c nang riêng tu -----------------------------------------------------------------*/
/** @defgroup I2C_Private_Functions I2C Private Functions
/** @Defgroup I2C_Private_Funces I2C Ch?c nang riêng tu
  * @{
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
<Sd1> #ifdef   __cplusplus 
}
#endif
#endif /* __STM32F1xx_HAL_I2C_H */
<Sd1> #endif  / * __stm32f1xx_hal_i2c_h */
