#include <csignal>
#include <cstdlib>
#include <ctime>
#include <getopt.h>
#include <server/config.h>
#include <server/log/log.h>
#include <server/server.h>

int cfg_port = 2024;
int cfg_sql_conn_num = 8;
int cfg_thread_num = 8;

static char const short_opts[] = "p:s:t:";

static const struct option long_opts[] = {
  {"port", required_argument, 0, 'p'},
  {"sql_connection_number", required_argument, 0, 's'},
  {"thread_number", required_argument, 0, 't'},
  //{"use_aio", no_argument, 0, 'a'},
  {NULL, 0, NULL, 0},
};

void sig_handler(int sig) {
  LOG_CLEANUP;

  ::sleep(1);
  std::exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  std::signal(SIGINT, sig_handler);
  int c;

  while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) >= 0) {
    switch (c) {
    case 'p': cfg_port = ::atoi(optarg); break;
    case 's': cfg_sql_conn_num = ::atoi(optarg); break;
    case 't': cfg_thread_num = ::atoi(optarg); break;
    default:  printf("unknown option\n"); std::exit(EXIT_FAILURE);
    }
  }

  server::log::Log &log = server::log::Log::instance();
  log.set_level(server::log::Log_Level::debug);

  server::WebServer CSServer(cfg_port);
  CSServer.loop();

  ::sleep(1);
  std::exit(EXIT_SUCCESS);
}
