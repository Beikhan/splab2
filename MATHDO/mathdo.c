#include <sys/types.h>      /* needed to use pid_t, etc. */
#include <sys/wait.h>       /* needed to use wait() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>         /* LINUX constants and functions (fork(), etc.) */
#include <string.h>

void systemCustom(char *arg) {
    pid_t pid = fork();
    if (pid == 0){
        char *name[] = { "/bin/bash","-c",arg,NULL };
        execvp(name[0], name);
    } else {
        waitpid(pid, 0, 0);
    }
}
int main(int argc, char *argv[]) {
    const char * scripts[][4] = {
        {"java ", "mathdo "},
        {"node ", "mathdo.js "},
        {"python ", "mathdo.py "},
        {"sh ","mathdo.sh "},
    };
    int arraySize = sizeof(scripts)/sizeof(scripts[0]);
    for (int i = 0; i < arraySize; i++) {
        char a[50] = "";
        strcat(a, scripts[i][0]);
        strcat(a, scripts[i][1]);
        strcat(a, argv[1]);
        strcat(a, " ");
        strcat(a, argv[2]);  
        systemCustom(a);
    }
    return 0;
}
