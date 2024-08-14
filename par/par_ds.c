#include <stdio.h>
#include <stdint.h>
#include "par_ds.h"
cfe_h   pri_header;
ds_h    sec_header;
comb_pac    payload; // size 측정용 structure 정의

int main(void)
{
    FILE *fp = NULL; // 파일 열기
    fp = fopen("cFS/build/exe/cpu1/cf/test/ds00000000.tlm", "rb");
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
    
    comb_pac payloads[count]; // "통합 패킷 배열 선언

    fseek(fp, 0L, SEEK_SET); // 포인터 초기 위치로 돌리고 header 정보 출력
    size_t header_1 = fread(&pri_header, sizeof(pri_header), 1, fp);
    size_t header_2 = fread(&sec_header, sizeof(sec_header), 1, fp);
    
    for (int i = 0; i < count; i++) { // 순차적으로 도착한 payload를 payloads 배열에 담기
        size_t one = fread(&payloads[i], sizeof(payloads[0]), 1, fp);
    }
    fclose(fp);
 
    printf("how many comb_packet stack: %d\n", count); // 필요한 정보 추출
    printf("comb_packet MID: %x\n", (payloads[0].tel_header.StreamId[0] << 8) | payloads[0].tel_header.StreamId[1]);
    printf("comb_packet MID: %x\n", (payloads[1].tel_header.StreamId[0] << 8) | payloads[1].tel_header.StreamId[1]);
    for (int i=0; i<10; i++) {
        printf("ds_CmdAcceptedCounter: %d\n", payloads[i].ds_payload.CmdAcceptedCounter);
    }
    return 0;
}
// printf("description: %s\n", pri_header.Description); 
// printf("FileName: %s\n", sec_header.FileName);
// printf("comb_packet MID: %x\n", (payloads[0].tel_header.StreamId[0] << 8) | payloads[0].tel_header.StreamId[1]);
// printf("comb_packet MID: %x\n", (payloads[1].tel_header.StreamId[0] << 8) | payloads[1].tel_header.StreamId[1]);