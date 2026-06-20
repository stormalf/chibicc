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
  int err_pipe[2];

  // Create a pipe for stderr separation (like Vim does with err_io: 'pipe')
  if (pipe(err_pipe) < 0) {
    perror("pipe");
    return 1;
  }

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
    // Child: set up PTY and pipe as Vim does
    close(master);
    close(err_pipe[0]);

    // Redirect stderr to the pipe write end
    dup2(err_pipe[1], 2);
    close(err_pipe[1]);

    setsid();
    if (ioctl(slave, TIOCSCTTY, NULL) < 0)
      perror("ioctl TIOCSCTTY");
    dup2(slave, 0);
    dup2(slave, 1);
    if (slave > 2) close(slave);
    execl("/bin/sh", "sh", NULL);
    perror("execl");
    _exit(1);
  }

  // Parent
  close(slave);
  close(err_pipe[1]);

  // Wait for shell to start
  usleep(200000);

  char buf_out[4096] = {0};
  char buf_err[4096] = {0};

  // Send "XXXX\n" to the shell via PTY
  write(master, "XXXX\n", 5);
  usleep(300000);

  // Read from both PTY master (stdout) and error pipe (stderr)
  fd_set rfds;
  struct timeval tv;
  int maxfd = (master > err_pipe[0]) ? master : err_pipe[0];
  
  while (1) {
    FD_ZERO(&rfds);
    FD_SET(master, &rfds);
    FD_SET(err_pipe[0], &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    int ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
    if (ret <= 0) break;
    
    if (FD_ISSET(master, &rfds)) {
      int n = read(master, buf_out + strlen(buf_out), sizeof(buf_out) - strlen(buf_out) - 1);
      if (n <= 0) break;
    }
    if (FD_ISSET(err_pipe[0], &rfds)) {
      int n = read(err_pipe[0], buf_err + strlen(buf_err), sizeof(buf_err) - strlen(buf_err) - 1);
      if (n <= 0) break;
    }
  }

  printf("=== STDOUT ===\n%s\n=== END ===\n", buf_out);
  printf("=== STDERR ===\n%s\n=== END ===\n", buf_err);

  if (strstr(buf_err, "not found"))
    printf("PASS: Found 'not found' on stderr\n");
  else
    printf("FAIL: Did not find 'not found' on stderr (got: '%s')\n", buf_err);

  // Send exit and wait
  write(master, "exit\n", 5);
  waitpid(pid, NULL, 0);
  close(master);
  close(err_pipe[0]);

  return 0;
}
