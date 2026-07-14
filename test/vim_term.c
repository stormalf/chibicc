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
#include <sys/time.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pty.h>

volatile sig_atomic_t child_exited = 0;

void sigchld_handler(int sig) {
  child_exited = 1;
}

static long now_ms(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Drain both fds into their buffers, appending whatever is ready.
static void drain_once(int master, int errfd, char *out_buf, char *err_buf,
                       int timeout_ms) {
  fd_set rfds;
  struct timeval tv;
  FD_ZERO(&rfds);
  FD_SET(master, &rfds);
  FD_SET(errfd, &rfds);
  int maxfd = (master > errfd) ? master : errfd;
  tv.tv_sec = timeout_ms / 1000;
  tv.tv_usec = (timeout_ms % 1000) * 1000;
  if (select(maxfd + 1, &rfds, NULL, NULL, &tv) <= 0)
    return;
  if (FD_ISSET(master, &rfds))
    read(master, out_buf + strlen(out_buf), 4096 - strlen(out_buf) - 1);
  if (FD_ISSET(errfd, &rfds))
    read(errfd, err_buf + strlen(err_buf), 4096 - strlen(err_buf) - 1);
}

// Keep reading until 'needle' appears on err_buf or the deadline elapses.
// A NULL needle just drains until the deadline. Robust under heavy load.
static void read_until(int master, int errfd, char *out_buf, char *err_buf,
                       const char *needle, int deadline_ms) {
  long deadline = now_ms() + deadline_ms;
  while (now_ms() < deadline) {
    drain_once(master, errfd, out_buf, err_buf, 50);
    if (needle && strstr(err_buf, needle))
      return;
  }
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

  // Read initial output (should get prompt on err pipe)
  read_until(master, err_pipe[0], out_buf, err_buf, "$", 2000);

  printf("=== After initial wait ===\n");
  printf("STDOUT: '%s'\n", out_buf);
  printf("STDERR: '%s'\n", err_buf);

  // Send "XXXX\r" (like Vim's term_sendkeys)
  write(master, "XXXX\r", 5);

  // Read output (like Vim's term_wait), keep polling until the shell has had
  // time to fork+exec and report the error. Robust under heavy parallel load.
  read_until(master, err_pipe[0], out_buf, err_buf, "not found", 3000);

  printf("=== After sending XXXX ===\n");
  printf("STDOUT: '%s'\n", out_buf);
  printf("STDERR: '%s'\n", err_buf);

  // Give any trailing output a brief chance to arrive.
  read_until(master, err_pipe[0], out_buf, err_buf, NULL, 200);

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
