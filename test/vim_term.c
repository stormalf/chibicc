// Simulates Vim's term_start + err_io: 'pipe' test scenario
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

volatile sig_atomic_t child_exited = 0;

void sigchld_handler(int sig) {
  child_exited = 1;
}

int main() {
  int master, slave;
  pid_t pid;
  int err_pipe[2] = {-1, -1};

  // Create stderr pipe (like Vim's err_io: 'pipe')
  if (pipe(err_pipe) < 0) {
    perror("pipe");
    return 1;
  }

  // Open PTY
  if (openpty(&master, &slave, NULL, NULL, NULL) < 0) {
    perror("openpty");
    return 1;
  }

  // Set up SIGCHLD handler (like Vim)
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigchld_handler;
  sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  sigaction(SIGCHLD, &sa, NULL);

  pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    // Child: Vim's setup
    close(master);
    close(err_pipe[0]);

    setsid();
    ioctl(slave, TIOCSCTTY, NULL);

    // stdin -> PTY slave
    close(0);
    dup(slave);

    // stderr -> err pipe
    close(2);
    dup(err_pipe[1]);

    // stdout -> PTY slave
    close(1);
    dup(slave);

    // Close remaining fds
    close(err_pipe[1]);
    close(slave);

    execvp("sh", (char *[]){"sh", NULL});
    perror("execvp");
    _exit(1);
  }

  // Parent
  close(slave);
  close(err_pipe[1]);

  // Wait for shell to start
  usleep(200000);

  char out_buf[4096] = {0};
  char err_buf[4096] = {0};
  fd_set rfds;
  struct timeval tv;

  // Read initial output (should get prompt on err pipe)
  int iter = 0;
  while (iter < 10) {
    FD_ZERO(&rfds);
    FD_SET(master, &rfds);
    FD_SET(err_pipe[0], &rfds);
    int maxfd = (master > err_pipe[0]) ? master : err_pipe[0];
    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    int ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
    if (ret <= 0) break;

    if (FD_ISSET(master, &rfds)) {
      int n = read(master, out_buf + strlen(out_buf), sizeof(out_buf) - strlen(out_buf) - 1);
      if (n <= 0) break;
    }
    if (FD_ISSET(err_pipe[0], &rfds)) {
      int n = read(err_pipe[0], err_buf + strlen(err_buf), sizeof(err_buf) - strlen(err_buf) - 1);
      if (n <= 0) break;
    }
    iter++;
  }

  printf("=== After initial wait ===\n");
  printf("STDOUT: '%s'\n", out_buf);
  printf("STDERR: '%s'\n", err_buf);

  // Send "XXXX\r" (like Vim's term_sendkeys)
  write(master, "XXXX\r", 5);
  usleep(50000);

  // Read output (like Vim's term_wait)
  iter = 0;
  while (iter < 10) {
    FD_ZERO(&rfds);
    FD_SET(master, &rfds);
    FD_SET(err_pipe[0], &rfds);
    int maxfd = (master > err_pipe[0]) ? master : err_pipe[0];
    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    int ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
    if (ret <= 0) break;

    if (FD_ISSET(master, &rfds)) {
      int n = read(master, out_buf + strlen(out_buf), sizeof(out_buf) - strlen(out_buf) - 1);
      if (n <= 0) break;
    }
    if (FD_ISSET(err_pipe[0], &rfds)) {
      int n = read(err_pipe[0], err_buf + strlen(err_buf), sizeof(err_buf) - strlen(err_buf) - 1);
      if (n <= 0) break;
    }
    iter++;
  }

  printf("=== After sending XXXX ===\n");
  printf("STDOUT: '%s'\n", out_buf);
  printf("STDERR: '%s'\n", err_buf);

  // Wait for the error to propagate (the shell needs time to fork+exec)
  usleep(200000);

  // Read any additional output
  iter = 0;
  while (iter < 10) {
    FD_ZERO(&rfds);
    FD_SET(master, &rfds);
    FD_SET(err_pipe[0], &rfds);
    int maxfd = (master > err_pipe[0]) ? master : err_pipe[0];
    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    int ret = select(maxfd + 1, &rfds, NULL, NULL, &tv);
    if (ret <= 0) break;

    if (FD_ISSET(master, &rfds)) {
      int n = read(master, out_buf + strlen(out_buf), sizeof(out_buf) - strlen(out_buf) - 1);
      if (n <= 0) break;
    }
    if (FD_ISSET(err_pipe[0], &rfds)) {
      int n = read(err_pipe[0], err_buf + strlen(err_buf), sizeof(err_buf) - strlen(err_buf) - 1);
      if (n <= 0) break;
    }
    iter++;
  }

  printf("=== After waiting more ===\n");
  printf("STDOUT: '%s'\n", out_buf);
  printf("STDERR: '%s'\n", err_buf);

  // Check for "not found" on stderr
  int pass = 0;
  if (strstr(err_buf, "not found"))
    pass = 1;

  // Send exit and wait
  write(master, "exit\r", 5);

  int status;
  waitpid(pid, &status, 0);
  close(master);
  close(err_pipe[0]);

  printf("=== RESULT ===\n");
  if (pass)
    printf("PASS: Found 'not found' on stderr\n");
  else
    printf("FAIL: 'not found' not on stderr\n");
  printf("STDERR: '%s'\n", err_buf);
  printf("child_exited=%d status=%d\n", child_exited, status);

  return pass ? 0 : 1;
}
