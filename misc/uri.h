#pragma once
#include <map>
#include <string>
#include <string_view>

namespace server {
namespace net {

using String = std::string;

struct URIParams : std::map<String, String> { // TODO: use absl::flat_hash_map
  using std::map<String, String>::map;
};

struct URI {
  explicit URI(String path, URIParams params) {
    mPath = path;
    mParams = params;
  }

  static URI parse(std::string_view uri);

  static String url_encode_path(std::string_view s);

  String dump() const;

  String repr() const {
    return dump();
  }

private:
  static void url_decode(String &r, std::string_view s);
  static String url_decode(std::string_view s);

  static void url_encode(String &r, std::string_view s);
  static String url_encode(std::string_view s);

  static void url_encode_path(String &r, std::string_view s);

  void dump(String &r) const;

  String mPath;
  URIParams mParams;
};

} // namespace net
} // namespace server
