#ifndef _FND_DRV_H_
#define _FND_DRV_H_

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)

typedef struct FNDWriteDataForm_tag
{
    char DataNumeric[FND_DATA_BUFF_LEN];
    char DataDot[FND_DATA_BUFF_LEN];
    char DataValid[FND_DATA_BUFF_LEN];
}stFndWriteForm,*pStFndWriteForm;

void fnd_static_dis(long a);
int fnd_time_dis(void);
void fnd_count_dis(long a);
void fnd_rev_count_dis(long a);
int fndOff();

#endif
