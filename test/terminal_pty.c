#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pty.h>

int main() {
  int master, slave;
  char name[256];
  pid_t pid;

  // Open a PTY
  if (openpty(&master, &slave, name, NULL, NULL) < 0) {
    perror("openpty");
    return 1;
  }

  pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    // Child: set up PTY as controlling terminal and exec shell
    close(master);
    setsid();
    if (ioctl(slave, TIOCSCTTY, NULL) < 0)
      perror("ioctl TIOCSCTTY");
    dup2(slave, 0);
    dup2(slave, 1);
    dup2(slave, 2);
    if (slave > 2) close(slave);
    execl("/bin/sh", "sh", NULL);
    perror("execl");
    _exit(1);
  }

  // Parent: communicate through PTY master
  close(slave);

  // Wait for shell to start, read initial output (prompt)
  usleep(200000);
  
  char buf[4096] = {0};

  // Send "XXXX\r" to the shell
  write(master, "XXXX\n", 5);
  usleep(300000);

  // Read all available output
  fd_set rfds;
  struct timeval tv = {0, 100000};
  int n;
  while (1) {
    FD_ZERO(&rfds);
    FD_SET(master, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    int ret = select(master + 1, &rfds, NULL, NULL, &tv);
    if (ret <= 0) break;
    n = read(master, buf + strlen(buf), sizeof(buf) - strlen(buf) - 1);
    if (n <= 0) break;
  }

  printf("=== OUTPUT ===\n%s\n=== END ===\n", buf);
  
  // Check for "not found" 
  if (strstr(buf, "not found"))
    printf("PASS: Found 'not found' in output\n");
  else
    printf("FAIL: Did not find 'not found' in output\n");

  // Send exit and wait
  write(master, "exit\n", 5);
  waitpid(pid, NULL, 0);
  close(master);

  return 0;
}
