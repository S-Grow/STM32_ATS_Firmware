/**
 ******************************************************************************
 * @file      syscalls.c
 * @brief     Minimal System calls file for Keil / STM32 test
 *            Redirects stdio to LD2 blink for demo purposes.
 ******************************************************************************
 */

#include "main.h"
#include <stdint.h>

/* Minimal fstat struct definition */
struct stat {
    uint32_t st_mode;
};

/* S_IFCHR for character device */
#define S_IFCHR  0020000

/* Redirected I/O using LD2 */
int __io_putchar(int ch)
{
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); // blink LD2
    HAL_Delay(100); // small delay so blink is visible
    return ch;
}

int __io_getchar(void)
{
    // unused for now
    return 0;
}

/* Environment required by minimal libc */
char *__env[1] = { 0 };
char **environ = __env;

void initialise_monitor_handles() {}

/* Minimal syscall stubs */
int _getpid(void) { return 1; }
int _kill(int pid, int sig) { (void)pid; (void)sig; return -1; }
void _exit(int status) { while(1) {} }
int _read(int file, char *ptr, int len) { (void)file; (void)ptr; (void)len; return 0; }
int _write(int file, char *ptr, int len) { (void)file; for(int i=0;i<len;i++) __io_putchar(ptr[i]); return len; }
int _close(int file) { (void)file; return -1; }
int _fstat(int file, struct stat *st) { (void)file; st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { (void)file; return 1; }
int _lseek(int file, int ptr, int dir) { (void)file; (void)ptr; (void)dir; return 0; }
int _open(char *path, int flags, ...) { (void)path; (void)flags; return -1; }
int _wait(int *status) { (void)status; return -1; }
int _unlink(char *name) { (void)name; return -1; }
int _stat(const char *file, struct stat *st) { (void)file; st->st_mode = S_IFCHR; return 0; }
int _link(char *old, char *new) { (void)old; (void)new; return -1; }
int _fork(void) { return -1; }
int _execve(char *name, char **argv, char **env) { (void)name; (void)argv; (void)env; return -1; }
