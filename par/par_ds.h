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

typedef struct
{
    uint8_t   CmdAcceptedCounter;                 /**< \dstlmmnemonic \DS_CMDPC
                                                     \brief Count of valid commands received */
    uint8_t   CmdRejectedCounter;                 /**< \dstlmmnemonic \DS_CMDEC
                                                     \brief Count of invalid commands received */
    uint8_t   DestTblLoadCounter;                 /**< \dstlmmnemonic \DS_DESTLOADCNT
                                                     \brief Count of destination file table loads */
    uint8_t   DestTblErrCounter;                  /**< \dstlmmnemonic \DS_DESTPTRERRCNT
                                                     \brief Count of failed attempts to get table data pointer */
    uint8_t   FilterTblLoadCounter;               /**< \dstlmmnemonic \DS_FILTERLOADCNT
                                                     \brief Count of packet filter table loads */
    uint8_t   FilterTblErrCounter;                /**< \dstlmmnemonic \DS_FILTERPTRERRCNT
                                                     \brief Count of failed attempts to get table data pointer */
    uint8_t   AppEnableState;                     /**< \dstlmmnemonic \DS_APPENASTATE
                                                     \brief Application enable/disable state */
    uint8_t   Spare8;                             /**< \brief Structure alignment padding */

    uint16_t  FileWriteCounter;                   /**< \dstlmmnemonic \DS_FILEWRITECNT
                                                     \brief Count of good destination file writes */
    uint16_t  FileWriteErrCounter;                /**< \dstlmmnemonic \DS_FILEWRITEERRCNT
                                                     \brief Count of bad destination file writes */
    uint16_t  FileUpdateCounter;                  /**< \dstlmmnemonic \DS_FILEUPDCNT
                                                     \brief Count of good updates to secondary header */
    uint16_t  FileUpdateErrCounter;               /**< \dstlmmnemonic \DS_FILEUPDERRCNT
                                                     \brief Count of bad updates to secondary header */
    uint32_t  DisabledPktCounter;                 /**< \dstlmmnemonic \DS_DISABLEDPKTCNT
                                                     \brief Count of packets discarded (DS was disabled) */
    uint32_t  IgnoredPktCounter;                  /**< \dstlmmnemonic \DS_IGNOREDPKTCNT
                                                     \brief Count of packets discarded.  Incoming packets will be discarded when:
                                                     <ul> <li> The File and/or Filter Table has failed to load </li>
                                                          <li> A packet (that is not a DS HK or command packet) has been received that is not 
                                                               listed in the Filter Table </li> </ul> */
    uint32_t  FilteredPktCounter;                 /**< \dstlmmnemonic \DS_FILTEREDPKTCNT
                                                     \brief Count of packets discarded (failed filter test) */
    uint32_t  PassedPktCounter;                   /**< \dstlmmnemonic \DS_PASSEDPKTCNT
                                                     \brief Count of packets that passed filter test */
    char    FilterTblFilename[64]; /**< \dstlmmnemonic \DS_FILTERTBL
                                                     \brief Name of filter table file */
} ds_noh;

typedef struct 
{   
    tel_h  tel_header;
    ds_noh  ds_payload;
} comb_pac;

#define byte_cfe  64
#define byte_ds   76

#define byte_tel  12
#define byte_dsp  96
#define byte_comb 108

#if (byte_tel +\
     byte_dsp) != byte_comb
#error "Packet length invalid!"
#endif