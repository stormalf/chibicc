// Simulates Vim's test more precisely:
// term_sendkeys("XXXX\r") -> term_wait -> term_sendkeys("exit\r") -> term_wait
#include <stdio.h>
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

static int read_pty_method(int fd) {
  char buf[256];
  int n = read(fd, buf, sizeof(buf) - 1);
  if (n > 0) {
    buf[n] = 0;
    printf("  [read PTY: %d bytes] '%s'\n", n, buf);
    return n;
  }
  return -1;
}

static int read_pipe_method(int fd) {
  char buf[256];
  int n = read(fd, buf, sizeof(buf) - 1);
  if (n > 0) {
    buf[n] = 0;
    printf("  [read PIPE: %d bytes] '%s'\n", n, buf);
    return n;
  }
  return -1;
}

int main() {
  int master, slave;
  pid_t pid;
  int err_pipe[2] = {-1, -1};

  if (pipe(err_pipe) < 0) { perror("pipe"); return 1; }
  if (openpty(&master, &slave, NULL, NULL, NULL) < 0) { perror("openpty"); return 1; }

  pid = fork();
  if (pid < 0) { perror("fork"); return 1; }

  if (pid == 0) {
    close(master); close(err_pipe[0]);
    setsid(); ioctl(slave, TIOCSCTTY, NULL);
    close(0); dup(slave);
    close(2); dup(err_pipe[1]);
    close(1); dup(slave);
    close(err_pipe[1]); close(slave);
    execvp("sh", (char *[]){"sh", NULL});
    perror("execvp"); _exit(1);
  }

  close(slave); close(err_pipe[1]);
  usleep(200000);

  char out_buf[4096] = {0};
  char err_buf[4096] = {0};
  fd_set rfds;
  struct timeval tv;

  // Initial read (like Vim does when processing the initial terminal output)
  FD_ZERO(&rfds); FD_SET(master, &rfds); FD_SET(err_pipe[0], &rfds);
  int maxfd = (master > err_pipe[0]) ? master : err_pipe[0];
  tv.tv_sec = 0; tv.tv_usec = 10000;
  int initial_ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
  printf("Initial select returned: %d\n", initial_ret);
  if (FD_ISSET(master, &rfds)) read_pty_method(master);
  if (FD_ISSET(err_pipe[0], &rfds)) read_pipe_method(err_pipe[0]);

  // === term_sendkeys(buf, "XXXX\r") ===
  printf("\n=== Sending 'XXXX\\r' ===\n");
  int nw = write(master, "XXXX\r", 5);
  printf("write returned: %d\n", nw);

  // === term_wait(buf) ===
  printf("\n=== term_wait (10ms timeout) ===\n");
  FD_ZERO(&rfds); FD_SET(master, &rfds); FD_SET(err_pipe[0], &rfds);
  tv.tv_sec = 0; tv.tv_usec = 10000;
  int wait_ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
  printf("wait1 select returned: %d\n", wait_ret);
  if (FD_ISSET(master, &rfds)) read_pty_method(master);
  if (FD_ISSET(err_pipe[0], &rfds)) read_pipe_method(err_pipe[0]);

  // === term_sendkeys(buf, "exit\r") ===
  printf("\n=== Sending 'exit\\r' ===\n");
  nw = write(master, "exit\r", 5);
  printf("write returned: %d\n", nw);

  // === term_wait(buf) ===
  printf("\n=== term_wait #2 (10ms timeout) ===\n");
  FD_ZERO(&rfds); FD_SET(master, &rfds); FD_SET(err_pipe[0], &rfds);
  tv.tv_sec = 0; tv.tv_usec = 10000;
  wait_ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
  printf("wait2 select returned: %d\n", wait_ret);
  if (FD_ISSET(master, &rfds)) read_pty_method(master);
  if (FD_ISSET(err_pipe[0], &rfds)) read_pipe_method(err_pipe[0]);

  // Try one more read to catch anything delayed
  usleep(100000);
  printf("\n=== Final check (100ms later) ===\n");
  FD_ZERO(&rfds); FD_SET(master, &rfds); FD_SET(err_pipe[0], &rfds);
  tv.tv_sec = 0; tv.tv_usec = 10000;
  wait_ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
  printf("final select returned: %d\n", wait_ret);
  if (FD_ISSET(master, &rfds)) {
    int n = read(master, out_buf, sizeof(out_buf) - 1);
    if (n > 0) { out_buf[n] = 0; printf("  [OUT] '%s'\n", out_buf); }
  }
  if (FD_ISSET(err_pipe[0], &rfds)) {
    int n = read(err_pipe[0], err_buf, sizeof(err_buf) - 1);
    if (n > 0) { err_buf[n] = 0; printf("  [ERR] '%s'\n", err_buf); }
  }

  // Wait for child
  waitpid(pid, NULL, 0);
  close(master); close(err_pipe[0]);

  return 0;
}
