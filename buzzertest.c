#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
#include "buzzer.h"

int main(){
    //int tm = 2; //노래반복횟수
    
    buzzerInit();
    Frequency();
    buzzerON();

    sleep(5);
    buzzerOFF();
    //buzzerPlaySong();
    //buzzerStopSong();

    return 0;
}
