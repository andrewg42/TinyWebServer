#include <server/server.h>
#include <server/std.h>

namespace webserver {

struct WebServer { // do not use singleton! log::Log is singleton. Webserver need a shorter
                   // lifetime
public:
  WebServer(int port) : m_port(port) {}
  void start() {
    net::Event_Loop event_loop(m_port);

    event_loop.loop();
  }

private:
  int m_port;
};

} // namespace webserver

static const char short_opts[] = "p:s:t:";

static const struct option long_opts[] = {
    {"port", required_argument, 0, 'p'},
    {"sql_connection_number", required_argument, 0, 's'},
    {"thread_number", required_argument, 0, 't'},
    //{"use_aio", no_argument, 0, 'a'},
    {NULL, 0, NULL, 0},
};

void sig_handler(int sig) {
  LOG_CLEANUP;

  sleep(1);
  std::exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  std::signal(SIGINT, sig_handler);
  int c;

  while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) >= 0) {
    switch (c) {
    case 'p':
      cfg_port = atoi(optarg);
      break;
    case 's':
      cfg_sql_conn_num = atoi(optarg);
      break;
    case 't':
      cfg_thread_num = atoi(optarg);
      break;
    default:
      printf("unknown option\n");
      return -1;
    }
  }

  webserver::log::Log &log = webserver::log::Log::instance();
  log.set_level(webserver::log::Log_Level::debug);

  webserver::Webserver server(cfg_port);
  server.start();

  std::exit(EXIT_SUCCESS);
}
