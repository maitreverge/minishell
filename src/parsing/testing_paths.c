// #include <stdio.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     char* args[] = {"../../../../../bin/echo", "test", NULL};
//     char* env[] = {NULL};

//     pid_t pid = fork();
//     if (pid == 0) {
//         execve("../../../../../bin/echo", args, env);
//         perror("execve");
//         return 1;
//     } else if (pid > 0) {
//         wait(NULL);
//     } else {
//         perror("fork");
//         return 1;
//     }

//     return 0;
// }

// /*

// char* args1[] = {"/bin/echo", "test", NULL};  // Absolute path
// char* args2[] = {"./echo", "test", NULL};     // Relative path
// char* args3[] = {"echo", "test", NULL};       // Command name


// */

