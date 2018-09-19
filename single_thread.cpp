#include <memory>
#include <cstdint>
#include <iostream>
#include <evhttp.h>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>

int main()
{
  if (!event_init())
  {
    std::cerr << "Failed to init libevent." << std::endl;
    return -1;
  }
  char const SrvAddress[] = "192.168.137.30";
  std::uint16_t SrvPort = 5555;
  std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);
  if (!Server)
  {
    std::cerr << "Failed to init http server." << std::endl;
    return -1;
  }
  auto OnReq = [](evhttp_request *req, void *)
  {
    const struct evhttp_uri *uri = evhttp_request_get_evhttp_uri(req);
    const char* query = evhttp_uri_get_query(uri);
    
    struct evkeyvalq GET;
    evhttp_parse_query_str(query, &GET);
    const char *filename = evhttp_find_header(&GET, "filename");
    // std::cout<<connection<<std::endl;

    auto *OutBuf = evhttp_request_get_output_buffer(req);
    if (!OutBuf)
      return;

    FILE *stream;
    if ((stream = fopen(filename, "r")) != NULL) {
      struct stat st;
      stat(filename, &st);
      int size = st.st_size;
      evbuffer_add_file(OutBuf, fileno(stream), 0, size);
    }
    else {
      perror("Failed to open");
    }
    // evbuffer_add_printf(OutBuf, "<html><body><center><h1>Hello World!</h1></center></body></html>");
    evhttp_send_reply(req, HTTP_OK, "", OutBuf);
  };
  evhttp_set_gencb(Server.get(), OnReq, nullptr);
  if (event_dispatch() == -1)
  {
    std::cerr << "Failed to run messahe loop." << std::endl;
    return -1;
  }
  return 0;
}