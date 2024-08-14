#include <stdint.h>

typedef struct
{
    uint32_t  ContentType;           /**< \brief Identifies the content type (='cFE1'=0x63464531)*/
    uint32_t  SubType;               /**< \brief Type of \c ContentType, if necessary */
                                   /**< Standard SubType definitions can be found
                                        \link #CFE_FS_SubType_ES_ERLOG here \endlink */
    uint32_t  Length;                /**< \brief Length of primary header */
    uint32_t  SpacecraftID;          /**< \brief Spacecraft that generated the file */
    uint32_t  ProcessorID;           /**< \brief Processor that generated the file */
    uint32_t  ApplicationID;         /**< \brief Application that generated the file */
  
    uint32_t  TimeSeconds;           /**< \brief File creation timestamp (seconds) */
    uint32_t  TimeSubSeconds;        /**< \brief File creation timestamp (sub-seconds) */

    char    Description[32];       /**< \brief File description */

} cfe_h;

typedef struct
{
    uint32_t  CloseSeconds;                               /**< \brief Time when file was closed */
    uint32_t  CloseSubsecs;        

    uint16_t  FileTableIndex;                             /**< \brief Destination file table index */
    uint16_t  FileNameType;                               /**< \brief Filename type - count vs time */

    char    FileName[64];           /**< \brief On-board filename */

} ds_h;

typedef struct
{
    uint8_t   StreamId[2];  /* packet identifier word (stream ID) */
      /*  bits  shift   ------------ description ---------------- */
      /* 0x07FF    0  : application ID                            */
      /* 0x0800   11  : secondary header: 0 = absent, 1 = present */
      /* 0x1000   12  : packet type:      0 = TLM, 1 = CMD        */
      /* 0xE000   13  : CCSDS version:    0 = ver 1, 1 = ver 2    */

   uint8_t   Sequence[2];  /* packet sequence word */
      /*  bits  shift   ------------ description ---------------- */
      /* 0x3FFF    0  : sequence count                            */
      /* 0xC000   14  : segmentation flags:  3 = complete packet  */

   uint8_t  Length[2];     /* packet length word */
      /*  bits  shift   ------------ description ---------------- */
      /* 0xFFFF    0  : (total packet length) - 7                 */

    uint8_t Time[6];
} tel_h;

typedef unsigned char                         osalbool;
typedef osalbool  boolean;
typedef int32_t CFE_ES_MemHandle_t;
typedef struct
{
  uint32_t  Seconds;            /**< \brief Number of seconds since epoch */
  uint32_t  Subseconds;         /**< \brief Number of subseconds since epoch (LSB = 2^(-32) seconds) */
} CFE_TIME_SysTime_t;


typedef struct
{
    /*
    ** Task command interface counters...
    */
    uint8_t                 CommandCounter;                           /**< \cfetlmmnemonic \TBL_CMDPC 
                                                                     \brief Count of valid commands received */
    uint8_t                 CommandErrorCounter;                           /**< \cfetlmmnemonic \TBL_CMDEC ===
                                                                     \brief Count of invalid commands received */

    /*
    ** Table Registry Statistics
    */
    uint16_t                NumTables;                            /**< \cfetlmmnemonic \TBL_NUMTABLES 
                                                                     \brief Number of Tables Registered */
    uint16_t                NumLoadPending;                       /**< \cfetlmmnemonic \TBL_NUMUPDATESPEND 
                                                                     \brief Number of Tables pending on Applications for their update */

    /*
    ** Last Table Validation Results
    */
    uint16_t                ValidationCounter;                        /**< \cfetlmmnemonic \TBL_VALCOMPLTDCTR 
                                                                     \brief Number of completed table validations */
    uint32_t                LastValCrc;                           /**< \cfetlmmnemonic \TBL_LASTVALCRC 
                                                                     \brief Data Integrity Value computed for last table validated */
    int32_t                 LastValStatus;                        /**< \cfetlmmnemonic \TBL_LASTVALS 
                                                                     \brief Returned status from validation function for last table validated */
    boolean               ActiveBuffer;                         /**< \cfetlmmnemonic \TBL_LASTVALBUF 
                                                                     \brief Indicator of whether table buffer validated was 0=Inactive, 1=Active */ 
    char                  LastValTableName[38]; /**< \cfetlmmnemonic \TBL_LASTVALTBLNAME
                                                                            \brief Name of last table validated */
    uint8_t                 SuccessValCounter;                        /**< \cfetlmmnemonic \TBL_VALSUCCESSCTR 
                                                                     \brief Total number of successful table validations */
    uint8_t                 FailedValCounter;                         /**< \cfetlmmnemonic \TBL_VALFAILEDCTR 
                                                                     \brief Total number of unsuccessful table validations */
    uint8_t                 NumValRequests;                       /**< \cfetlmmnemonic \TBL_VALREQCTR 
                                                                     \brief Number of times Table Services has requested validations from Apps */
    
    /*
    ** Ground system interface information
    */
    uint8_t                 NumFreeSharedBufs;                    /**< \cfetlmmnemonic \TBL_NUMFREESHRBUF 
                                                                     \brief Number of free Shared Working Buffers */
    uint8_t                 ByteAlignPad1;                        /**< \cfetlmmnemonic \TBL_BYTEALIGNPAD1 
                                                                     \brief Spare byte to ensure longword alignment */
     CFE_ES_MemHandle_t    MemPoolHandle;                        /**< \cfetlmmnemonic \TBL_MEMPOOLHANDLE 
                                                                     \brief Handle to TBL's memory pool */
    CFE_TIME_SysTime_t    LastUpdateTime;                       /**< \cfetlmmnemonic \TBL_LASTUPDTIME 
                                                                     \brief Time of last table update */
    char                  LastUpdatedTable[38]; /**< \cfetlmmnemonic \TBL_LASTUPDTBLNAME
                                                                          \brief Name of the last table updated */
    char                  LastFileLoaded[64];      /**< \cfetlmmnemonic \TBL_LASTFILELOADED 
                                                                     \brief Path and Name of last table image file loaded */
    char                  LastFileDumped[64];      /**< \cfetlmmnemonic \TBL_LASTFILEDUMPED 
                                                                     \brief Path and Name of last file dumped to */
    char                  LastTableLoaded[38]; /**< \cfetlmmnemonic \TBL_LASTTABLELOADED
                                                                          \brief Name of the last table loaded */
} CFE_TBL_HousekeepingTlm_Payload_t;

typedef struct
{
    tel_h  tel_header;
    CFE_TBL_HousekeepingTlm_Payload_t  ctht_payload;
} CFE_TBL_HousekeepingTlm_t;

# define a = sizeof(CFE_TBL_HousekeepingTlm_t)