#include <stdio.h>
#include <stdint.h>
#include "par_cfe_tblhktlm.h"
cfe_h   pri_header;
ds_h    sec_header;
CFE_TBL_HousekeepingTlm_t   payload; // size 측정용 structure 정의

int main(void)
{
    FILE *fp = NULL; // 파일 열기
    fp = fopen("../cFS/build/exe/cpu1/cf/hw/cthk00000000.tlm", "rb");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return -1;
        }
    printf("파일 열기 성공\n");

    fseek(fp, 0L, SEEK_END); // 통합 패킷이 몇개 왔는지 측정(count)
    long size = ftell(fp);
    int count = ((int)size - 140)/sizeof(payload);
    if (size != count*sizeof(payload) + 140) 
        printf("The count is not integer\n");
    
    CFE_TBL_HousekeepingTlm_t payloads[count]; // 통합 패킷 배열 선언

    fseek(fp, 0L, SEEK_SET); // 포인터 초기 위치로 돌리고 header 정보 출력
    size_t header_1 = fread(&pri_header, sizeof(pri_header), 1, fp);
    size_t header_2 = fread(&sec_header, sizeof(sec_header), 1, fp);

    for (int i = 0; i < count; i++) { // 순차적으로 도착한 payload를 payloads 배열에 담기
        size_t one = fread(&payloads[i], sizeof(payloads[0]), 1, fp);
    }
    fclose(fp);

    for (int i = 0; i<count; i++) {
        printf("streamid: %x\n", (payloads[i].tel_header.StreamId[0] << 8) | payloads[i].tel_header.StreamId[1]);
    }
    return 0;
}